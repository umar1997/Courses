#include <iostream>
#include "sorts.cpp"
#include <fstream>
#include <vector>
#include <time.h>
#include <algorithm>

#include <thread>
#include <chrono>
#include <future>



using namespace std;

bool timeOut;

promise<bool> done;
void timer(future<bool> done_future){
    std::chrono::seconds span (4);
    if(done_future.wait_for(span) == std::future_status::timeout) {
        timeOut = true;
    }
}

void test(vector<long> entries, promise<bool> done_future){
    using namespace std::chrono;
    high_resolution_clock::time_point timeStart = high_resolution_clock::now();;

    vector<long> result = QuickSortArray(entries);
    if(timeOut){
        cout << "Timed Out Test Failed" << endl;
        return;
    }
    bool isSorted = true;
    
    sort(entries.begin(),entries.end());

    for(int i=0;i<entries.size();i++){
        if(entries[i] != result[i]){
            cout << "OUTPUT NOT SORTED TEST FAILED EXITING!" << endl;
            return;
        }
    }




    done_future.set_value(true);
    high_resolution_clock::time_point timeEnd = high_resolution_clock::now();;
    duration<double> totalTime = duration_cast<duration<double>>(timeEnd - timeStart);
    cout << "TEST PASSED IN : " << totalTime.count() << " SECONDS."<<endl;
}

int main(){
    vector<long> entries;
    srand(time(NULL));

    for(int i=0;i<1000000;i++){
        entries.push_back(-1000000 + rand()%2000000);
    }

    timeOut = false;
    
    future<bool> done_future = done.get_future();
    thread first (timer, move(done_future));
    test(entries, move(done));
    first.join();
    return 0;
}