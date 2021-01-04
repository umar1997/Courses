#ifndef __TREE_CPP
#define __LIST_CPP
#include "tree.h"
#include <fstream>

Tree::Tree()
{
    head=NULL;
}

Tree::Tree(string file)
{
    head=NULL;
    string item;
    ifstream infile;
    infile.open(file.c_str());
    while(!infile.eof())
    {
        getline(infile, item);
        //cout<<item<<endl;
        insert(item);
    }
}
Tree::~Tree()
{
}

void Tree::insert(string item)
{
        string y="";
        vector<string> v;
        int i=0;
        int len=item.length();
        while(i<len)
        {
            while(item[i]!='/' && i<len)
            {
                y+=item[i];
                i++;
            }
            i++;
            v.push_back(y);
            y="";
        }
//        for (int i=0; i<v.size();i++)
//            cout<< v[i]<<ends;
//        cout<<endl;
//        cout<<endl;
//

        insert1(v,0);
}

vector<string> Tree::Locate(string qry)
{
    vector<string> locate;
    TreeItem* file= search(qry, head);
    if (file!=NULL)
    {
        while(file!=NULL)
        {
            locate.push_back(file->value);
            file=file->Parent;
        }

    }
    return locate;


}

string Tree::LComAc(string a, string b)
{
    if (search(a,head)!=NULL && search(b,head)!=NULL){
    vector<string>v1= Locate(a);
    vector<string>v2= Locate(b);

    for(int i=0;i<v1.size();i++)
    {
        for (int j=0;j<v2.size();j++)
        {
            if (v1[i]==v2[j])
            {
                return v1[i];
            }

        }

    }
    }
}




TreeItem* Tree::getHead()
{
     return head;
}

int Tree::countFiles()
{
    return count1(getHead());

}

int Tree::count1(TreeItem*p)
{
    static int c=0;

    if (p== NULL)
        return c;

    while (p!=NULL)
    {

        if (p->FChild!=NULL)
            count1(p->FChild);
        else
            ++c;
        p=p->NextS;
    }
        return c;


}

void Tree::moveFolder(string fromFolder,string toFolder)
{
    TreeItem* from= search(fromFolder, getHead());
    if (from==head || from==NULL)
    {
        return;
    }

    vector<string> to =Locate(toFolder);
    for (int i=0; i<to.size();i++)
    {
        if (fromFolder==to[i])
        {
            return;
        }
    }

    TreeItem* dest= search(toFolder, getHead());
    vector<string> v= Locate(fromFolder);

    TreeItem*prev= search(v[1],getHead());

    if((prev->FChild)->value==from->value)
        prev->FChild=from->NextS;
    else
    {
        prev=prev->FChild;
        while(prev->NextS->value!=from->value)
            prev=prev->NextS;
        prev->NextS=from->NextS;

    }

    if (dest->FChild==NULL)
    {
        dest->FChild= from;
        from->Parent= dest;
        from->NextS=NULL;
    }
    else
    {
        dest=dest->FChild;
        while(dest->NextS!=NULL)
            dest=dest->NextS;

        dest->NextS=from;
        from->Parent= dest->Parent;
        from->NextS= NULL;
    }


}

TreeItem* Tree::search(string k, TreeItem* p)
{
    if (p==NULL)
        return NULL;
    if (p->value==k)
        return p;
    else
    {   TreeItem *child= search(k, p->FChild);
        TreeItem *sibling= search(k, p->NextS);

        if (child!=NULL)
            return child;
        else
            return sibling;
    }

}

void Tree::insert1(vector<string> v, int i)
{
    if (i>=v.size())
        return;

    if (search(v[i],head)==NULL && i==0)
    {
        TreeItem* newnode= new TreeItem(v[i]);
        head= newnode;
        insert1(v,++i);
    }
    else if (search(v[i],head)==NULL && i>0)
    {
        TreeItem* temp= search(v[i-1],getHead());
        TreeItem* newnode= new TreeItem(v[i]);
        if (temp->FChild==NULL)
        {
            temp->FChild= newnode;
            newnode->Parent=temp;
        }
        else
        {
            temp=temp->FChild;
            while(temp->NextS!=NULL)
                temp=temp->NextS;
            temp->NextS= newnode;
            newnode->Parent= temp->Parent;
        }
        insert1(v,++i);

    }
    else
    {
       insert1(v,++i);
    }
}

#endif

//int main()
//{
//    Tree t("input_bonus.txt");
//    t.moveFolder("Suits Season 2","CS 678");
//    t.moveFolder("White Collar","summary-1.docx");
//    vector<string> check;
//	check = t.Locate("episode1.avi");
//    for (int i=0;i<check.size();i++)
//        cout<<check[i]<<ends;
//    cout<<endl;
//
//
//
//}
