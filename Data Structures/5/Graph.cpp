#ifndef GRAPH__CPP
#define GRAPH__CPP
#include "Graph.h"
#include <fstream>
#include <string>
#include <climits>

using namespace std;

bool operator == (edge a, edge b)
{
	if(a.weight==b.weight)
		return true;
	return false;
}

bool operator < (edge a, edge b)
{
	if(a.weight<b.weight)
		return true;
	return false;

}

bool operator > (edge a, edge b)
{
	if(a.weight>b.weight)
		return true;
	return false;

}
bool operator < (node a, node b)
{
	if(a.dist<b.dist)
		return true;
	return false;

}

bool operator > (node a, node b)
{
	if(a.dist>b.dist)
		return true;
	return false;

}

Graph::Graph(char* file)
{
	ifstream inFile;
	inFile.open(file);
	string x;
	float one, two;

	inFile>>x;
	//cout<<x<<endl;
	while(!inFile.eof()){
		inFile>>x;
		
		if (x== "ARCS")
			break;

		inFile>>one;
		inFile>>two;

		node* n= new node;
		n->name=x;
		n->x = one;
		n->y = two;
		cities.push_back(n);

	//	cout<<n->name<<" "<<n->x<<" "<<n->y<<endl;
	}

	string p1, p2;
	float num;

	//cout<<endl;
	//cout<<x<<endl;
	while(inFile>>p1){
		
		//inFile>>p1;
		
		inFile>>p2;
		inFile>>num;
		
		edge e;
		e.Origin = getCity(p1);
		e.Dest= getCity(p2);
		e.weight= num;

		getCity(p1)->edges.push_back(e);

		edge e2; //bi-directional
		e2.Origin= getCity(p2);
		e2.Dest= getCity(p1);
		e2.weight = num;

		getCity(p2)->edges.push_back(e2);


		arcs.push_back(e);
		//arcs.push_back(e2);
		
		//cout<<e.Origin->name<<" "<<e.Dest->name<<" "<<e.weight<<endl;
	}

	inFile.close();

	// for(int i=0;i<cities.size();i++)
	// {	
	// 	cout<<cities[i]->name<<endl;
	// 	int j=0;
	// 	for(j;j<cities[i]->edges.size();j++)
	// 	{	
	// 		cout<<cities[i]->edges[j].Origin->name<<" "<<cities[i]->edges[j].Dest->name<<endl;
	// 	}
	// 	cout<<endl;
	// }

}
node* Graph::getCity(string s)
{
	bool check=false;
	int size1= cities.size();
	int i=0;
	for(i;i<size1;i++)
	{
		if(cities[i]->name == s)
		{ 	
			check= true;
			break;
		}			
	}

	if (check)
		return cities[i];
	else
		return NULL;
}
void Graph::display(node* temp)
{
	if(temp->visit){
		//cout<<"a"<<endl;
		return;
	}

	cout << "AT: " << temp->name;
	temp->visit = 1;
	for(int i=0; i< temp->edges.size(); i++)
	{
		if(!temp->edges[i].Origin->visit || !temp->edges[i].Dest->visit)
		cout << "->" << temp->edges[i].weight << endl;
		display(temp->edges[i].Origin);
		display(temp->edges[i].Dest);
	}
}
vector<node*> Graph::Prims()
{
}
vector<node*> Graph::Kruskal()
{
	pqueue<edge> p(arcs);

	int cities_len =cities.size();
	
	vector<tree> bigset;
	tree elem;
	for(int i=0;i<cities_len;i++)
	{
		elem.treeS.insert(cities[i]);
		bigset.push_back(elem);
		elem.treeS.clear();
	}	

	int pos1=-2000;
	int pos2=-2000;

	vector<edge> mst;
	int e_counter=0;
	while(!p.isEmpty() && e_counter<cities_len-1)
	{
		edge e= p.ExtractMin();

		int i=0;
		while(i<bigset.size())
		{
			if(bigset[i].treeS.find(e.Origin)!=bigset[i].treeS.end())
			{
				pos1=i;
				break;
			}
			else
				i++;
		}

		i=0;
		while(i<bigset.size())
		{
			if(bigset[i].treeS.find(e.Dest)!=bigset[i].treeS.end())
			{
				pos2=i;
				break;
			}
			else 
				i++;
		}		

		if(pos1==pos2)
		{

		}
		else{
			mst.push_back(e);
			cout<<e.Origin->name<<" "<<e.Dest->name<<" "<<e.weight<<endl;
			mergeKruskal(bigset,pos1,pos2);

			e_counter++;
		}
				
	}

	float mst_total=0;
	for(int i=0;i<mst.size();i++)
		mst_total+=mst[i].weight;
	cout<<mst_total<<endl;
	
	for(int i=0;i<cities_len;i++)
		cities[i]->edges.clear();

	for(int i=0;i<mst.size();i++)
	{
		mst[i].Origin->edges.push_back(mst[i]);

		edge two;
		two.Origin=mst[i].Dest;
		two.Dest=mst[i].Origin;
		two.weight=mst[i].weight;

		mst[i].Dest->edges.push_back(two);
	}
	
	return cities;
}

void Graph::mergeKruskal(vector<tree> &bigset, int pos1, int pos2)
{
	for (set<node*>::const_iterator p = bigset[pos2].treeS.begin();p != bigset[pos2].treeS.end(); ++p)
    	bigset[pos1].treeS.insert(*p);

	
	for(int p=pos2;p<bigset.size()-1;p++)
	{
		bigset[p]=bigset[p+1];
	}
	bigset.pop_back();

	//return bigset;
}



int Graph::minvertice(vector<node*> vec)
{
	float min = 2147483647;
	int index= 2147483647;
	
	for(int i=0;i<vec.size();i++)
	{
		if(vec[i]->dist<min)
		{
			min=vec[i]->dist;
			index=i;
		}
	}
	//cout<<"change "<<vec[index]->name<<vec[index]->dist<<endl;
	return index;
}


vector<string> Graph::Dijkstra(string city, string destination, float &d)
{
	node* orig_c= getCity(city);
	int cities_len= cities.size();
	int x=0;
	while(x<cities_len)
	{
		if(cities[x]==orig_c)
			cities[x]->dist=0;
		else
			cities[x]->dist= INT_MAX;

		cities[x]->visit=0;
		cities[x]->prev=NULL;
		x++;
	}

	vector<node*> vertices;
	for(int i=0;i<cities_len;i++)
		vertices.push_back(cities[i]);

	while(!vertices.empty())
	{
		int index=minvertice(vertices);
		node* v= vertices[index];
		v->visit=1;
		//cout<<v->name<<endl;
		
		for(int p=index;p<vertices.size()-1;p++)
		{
			vertices[p]=vertices[p+1];
		}
		vertices.pop_back();
		
		int i=0;
		float new_phone_who_dis;
		while(i<v->edges.size())
		{	
			if(v->edges[i].Dest->visit==0)
			{
				new_phone_who_dis = v->dist + v->edges[i].weight;
				if(v->edges[i].Dest->dist>new_phone_who_dis){
					v->edges[i].Dest->prev=v;
					v->edges[i].Dest->dist= new_phone_who_dis;
				}
				else
				{
					//cout<<"here"<<endl;
				}
			}
			i++;		
		}

	}
	
	vector<string> dijkstra;
	//cout<<"REVERSE PATH: "; 
	node* dest_c= getCity(destination);
	while(dest_c)
	{	
		dijkstra.push_back(dest_c->name);
		//cout<<dest_c->name<<" ";
		dest_c=dest_c->prev;
	}
	d= getCity(destination)->dist;
	cout<<endl<<endl<<"DIJKSTRA'S SHORTEST PATH: "<<endl;
	vector<string> dijkstra2;
	for(int i=dijkstra.size()-1;i>=0;i--){
		dijkstra2.push_back(dijkstra[i]);
		cout<<dijkstra[i]<<" "<<" ";
	}

	return dijkstra;
	
}


// int main()
// {
// 	cout<<"start"<<endl;
// 	char buf[256];
// 	cin >> buf;
// 	Graph *g= new Graph(buf);
// 	cout<<endl;
// 	// cout<<g->getCity("LasVegas")->x<<endl;
// 	g->Kruskal();
// }

#endif
