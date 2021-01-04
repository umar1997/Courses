#include "MySortedSet.h"

template <class T>
MySortedSet<T>::MySortedSet()
{
    ListItem<T>* point=getListHead();
    point=NULL;
}

template <class T>
MySortedSet<T>::~MySortedSet()
{


}

template <class T>
ListItem<T>* MySortedSet<T>::getListHead()
{
    ListItem<T>* point=container.getHead();
    return point;
}

template <class T>
int MySortedSet<T>::insert(T ele)
{
    bool check=false;
    ListItem<T> *find1= getListHead();
    while(find1!=NULL)
    {
        if (find1->value == ele)
        {
            check=true;
            break;
        }
        else
            find1=find1->next;
    }
    if (check==true)
        return 0;
    else
    {
        if (getListHead()==NULL || ele<getListHead()->value)
        container.insertAtHead(ele);
        else
        {
        ListItem<T> *n= getListHead();
        bool check=false;
        while(n !=NULL)
        {
            if (n->value>ele)
            {
                check=true;
                break;
            }
            else
                n=n->next;
        }
        if (check==false)
            container.insertAtTail(ele);
        else
        {
            ListItem<T> *temp= new ListItem<T>(ele);
            temp->next=n;
            temp->prev=n->prev;
            n->prev->next= temp;
            n->prev=temp;
        }
        return 1;
    }
    }


}

template <class T>
int MySortedSet<T>::deleteEle(T ele)
{
    bool check1=false;
    ListItem<T> *find1= getListHead();
    while(find1!=NULL)
    {
        if (find1->value == ele)
        {
            check1=true;
            break;
        }
        else
            find1=find1->next;
    }
    if (check1==false)
        return 0;
    else
    {
        if(getListHead()==NULL){}
        else
        {
            bool check=false;
            ListItem<T>* temp= getListHead();
            while(temp!=NULL)
            {
                if (temp->value==ele)
                {
                    //cout<<"found1"<<endl;
                    check=true;
                    break;
                }
                else
                    temp=temp->next;
            }

            if (check==true)
            {
                if(temp==getListHead())
                    container.deleteHead();
                else if(temp->next==NULL)
                    container.deleteTail();
                else
                {
                //cout<<"found"<<endl;
                ListItem<T>* p= temp->prev;
                ListItem<T>* n= temp->next;

                p->next=n;
                n->prev=p;
                delete temp;
                }
            }

        }
        return 1;
    }

}

template <class T>
int MySortedSet<T>::isEmpty()
{
    ListItem<T>*temp=getListHead();
    if (temp==NULL)
        return 1;
    else
        return 0;

}

template <class T>
int MySortedSet<T>::isMember(T ele)
{
    bool check=false;
    ListItem<T> *find1= getListHead();
    while(find1!=NULL)
    {
        if (find1->value == ele)
        {
            check=true;
            break;
        }
        else
            find1=find1->next;
    }
    if (check==true)
        return 1;
    else
        return 0;


}

template <class T>
int MySortedSet<T>::isEqual(MySortedSet<T>* anotherset)
{
    ListItem<T> *temp1= getListHead();
    ListItem<T> *temp2= anotherset->getListHead();
    bool check=true;
    if(temp1==NULL && temp2==NULL)
        return 1;
    else if (temp1==NULL || temp2==NULL)
        return 0;
    else{
    if (container.length()!= anotherset->container.length())
        return 0;
    while(temp1!=NULL && temp2!=NULL)
    {
        if (temp1->value !=temp2->value)
        {
            return 0;
        }
        else
        {
            temp1=temp1->next;
            temp2=temp2->next;
        }
    }
    return 1;
    }

}

template <class T>
int MySortedSet<T>::isSubset(MySortedSet<T>* anotherset)
{


    ListItem<T> *temp1= getListHead();
    ListItem<T> *temp2= anotherset->getListHead();
    //int len= anotherset->container.length();
    bool check=true;
    if (temp1==NULL &&temp2!=NULL)
        return 0;
    else if(temp2==NULL)
        return 1;
    else
    {
    bool subset=true;
    while(temp2!=NULL){
    while(temp1!=NULL)
    {
        if (temp1->value != temp2->value)
        {
            temp1=temp1->next;
        }
        else
            break;
    }
    if (temp1==NULL)
    {
        subset=false;
        break;
    }
    temp2=temp2->next;
    }
    if (subset==false)
        return 0;
    else
        return 1;

    }

}

template <class T>
MySortedSet<T>* MySortedSet<T>::setUnion(MySortedSet<T>* anotherset)
{
    MySortedSet<T>* ret=new MySortedSet;
    ListItem<T> *list1= getListHead();
    while(list1!=NULL)
    {
        ret->insert(list1->value);
        list1=list1->next;
    }
    ListItem<T> *list2= anotherset->getListHead();
    while(list2!=NULL)
    {
        bool check=false;
        ListItem<T> *find1= getListHead();
        while(find1!=NULL)
        {
            if (find1->value == list2->value)
            {
                check=true;
                break;
            }
            else
                find1=find1->next;
        }
        if (check==false)
            ret->insert(list2->value);
        list2=list2->next;
        //if list2->val NOT IN ret, then insert

    }
    return ret;


}

template <class T>
MySortedSet<T>* MySortedSet<T>::setIntersection(MySortedSet<T>* anotherset)
{
    MySortedSet<T> *ret= new MySortedSet;

    if(this->isEmpty()==1)
        return this;
    else if(anotherset->isEmpty()==1)
        return anotherset;
    else
    {
        ListItem<T>*list1= getListHead();
        ListItem<T>*compare= anotherset->getListHead();

        while(list1!=NULL)
        {
            while(compare!=NULL)
            {
                if(list1->value==compare->value)
                {
                    ret->insert(list1->value);
                    break;
                }
                compare=compare->next;
            }
            compare=anotherset->getListHead();
            list1=list1->next;
        }
    }
    return ret;


}

template <class T>
MySortedSet<T>* MySortedSet<T>::setDifference(MySortedSet<T>* anotherset)
{
    if(isEmpty()==1)
        return this;
    else{
    MySortedSet<T>* ret=new MySortedSet;

    ListItem<T> *find1= anotherset->getListHead();
    ListItem<T> *temp1= getListHead();

    bool check1=false;
    while(temp1!=NULL)
    {
        while(find1!=NULL)
        {
            if (find1->value == temp1->value)
            {
                check1=true;
                break;
            }
            else
                find1=find1->next;
        }
        if (check1==false)
        {
            ret->insert(temp1->value);
        }
        check1=false;
        find1=anotherset->getListHead();
        temp1=temp1->next;
    }


//    temp1= anotherset->getListHead();
//    find1= getListHead();
//    check1=false;
//    while(temp1!=NULL)
//    {
//        while(find1!=NULL)
//        {
//            if (find1->value == temp1->value)
//            {
//                check1=true;
//                break;
//            }
//            else
//                find1=find1->next;
//        }
//        if (check1==false){
//
//            ret->insert(temp1->value);
//        }
//        check1=false;
//        find1=getListHead();
//        temp1=temp1->next;
//    }
    return ret;
    }
}

template <class T>
void MySortedSet<T>::print()
{
    if(isEmpty()==0)
    {


    ListItem<T>*temp=getListHead();

    while(temp!=NULL)
    {
        cout<<temp->value<<ends;
        temp=temp->next;
    }}
    cout<<endl;
}

template <class T>
int MySortedSet<T>::count()
{
    if(container.head!=NULL)
        return container.length();
    else
        return 0;
}

/*int main()
{
    MySortedSet<int> a;
    cout<<a.isEmpty();
    //a.insert(1);
    //a.insert(2);
    //a.insert(3);
    //a.insert(4);
    //a.deleteEle(5);
    //a.print();
    MySortedSet<int> b;
    //b.insert(1);
    //b.insert(2);
    //b.insert(3);

    b.print();
    a.setDifference(&b);
    return 0;
}*/

