#include "common.hpp"
using namespace std;



struct mst_node  //used in simpleScheme array
{
	int vertex;
	int weight;
	int parent;
	bool visited;
};

class simpleScheme
{

public:
	void init_min_q(int , vector <mst_node*> &);
	int mst(vector <mst_node*> &, vector <mst_node*> &, vector <vector <node*> > &, int );
	void printData(int total_cost, vector <mst_node*> &mst_list);
};