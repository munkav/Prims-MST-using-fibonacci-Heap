#include "common.hpp"
using namespace std;


struct fibNode  //used for Fibonacci Heap
{
	int degree;
	fibNode *child;
	int weight;
	int vertex;
	int other_end;
	fibNode * right;
	fibNode * left;
	fibNode * parent;
	bool	childcut;
	bool visited;
};


class fibHeap
{	
	
	fibNode * min_ptr;
	vector <fibNode *> node_list;
	int vertices;
	int numNodes;
public :

	fibHeap()
	{
		min_ptr = NULL;
		numNodes = 0;
	}

	
	void addNode(int v, int weight);
	void createNodes(int vertex);
	fibNode* removeMin();
	void pairwiseCombine();
	//void insertinDL(fibNode *,fibNode *);
	int fibMST( vector <vector <node *> > &, int, vector <fibNode*> &);
	void decreaseKey(int , int , int );
	fibNode* find(int);
	fibNode* findInChild(int , fibNode* );
	void cut(fibNode* x , fibNode* y);
	void cascading_cut(fibNode * y );
	void fibLink(fibNode * , fibNode * );
	void printData(int total_cost,  vector <fibNode*> &mst_list);
	void addtorootList(fibNode *x);
	void Insert(fibNode *);
	void Union(fibNode *);
	void exchange(fibNode* , fibNode* );
	void link(fibNode *, fibNode *);
	//void setVertices(int);

};
