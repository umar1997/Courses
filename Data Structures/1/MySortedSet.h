#include "LinkedList.cpp"


template <class T>
class MySortedSet
{
public:
	MySortedSet();
	~MySortedSet();
	ListItem<T>* getListHead(); //must return head of the container
	int insert(T ele);
	int deleteEle(T ele);
	int isEmpty();
 	int isMember(T ele);
  	int isEqual(MySortedSet<T>* anotherset);
	int isSubset(MySortedSet<T>* anotherset); //anotherset is a subset of this set?
	int count();
	MySortedSet<T>* setUnion(MySortedSet<T>* anotherset);
	MySortedSet<T>* setIntersection(MySortedSet<T>* anotherset);
	MySortedSet<T>* setDifference(MySortedSet<T>* anotherset);
	void print();
private:
	LinkedList<T> container;
};
