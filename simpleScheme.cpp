#include "simpleScheme.hpp"
#include <iostream>


//initializing min_array for simple scheme.
void simpleScheme::init_min_q(int size, vector <mst_node*> &min_q)
{
//	heap_node* min_q[size] = new *heap_node;
	for(int i=0; i<size; i++)
	{
		mst_node * temp = new mst_node;
		temp->parent = -1;
		temp->vertex = i;
		if(i == 0)
			temp->weight = 0;
		else
			temp->weight = INT_MAX;
		temp->visited = false;
		min_q.push_back(temp);
	}
//	return min_q;
	
}


//calling mst function for simple scheme
int simpleScheme::mst(vector <mst_node*> &min_q, vector <mst_node*> &mst_list, vector <vector <node*> > &adj_list, int vertex)
{
	int len = min_q.size();
	int start = 0;
	int min_w = INT_MAX;
	int min_v = INT_MAX;
	int parent = 0;
	int temp_parent;
	long total =0;

	for(int k = 0; k < vertex; k++)
	{	
		min_w = INT_MAX;

		for(int j = 0; j < vertex; j++)   // removing min from the min_q
		{
			if((min_q[j]->weight < min_w) && (min_q[j]->visited == false))
			{
				min_w = min_q[j]->weight;
				min_v = j;
			}
		}
		mst_node * temp = new mst_node;
		temp->parent = min_q[min_v]->parent;
		temp->weight = min_w;
		temp->vertex = min_v;
		min_q[min_v]->visited  = true;
		if(min_v != 0)
			mst_list.push_back(temp);
		  
		total = total +  min_w;
		
		for(int i = 0; i <adj_list[min_v].size();i++)     // decrease Key
		{
			int v = adj_list[min_v][i]->vertex;  // vertex of the currrent minimum node
			if(!min_q[v]->visited)
			{

				if(adj_list[min_v][i]->weight < min_q[v]->weight)  // checking for the minimum weighted vertex from the current min_vertex to all the neighbours of 
																	//the current minimum vertex.
				{
					min_q[v]->weight = adj_list[min_v][i]->weight;
					min_q[v]->parent = min_v;
				}
			}
		}
  
	}
	//cout<<total<<endl;
	return total;
}

void simpleScheme::printData(int total_cost, vector <mst_node*> &mst_list)
{
	cout<<total_cost<<endl;
	int size = mst_list.size();
	for(int i = 0; i < size ;i++)
		cout<<mst_list[i]->parent<<" "<<mst_list[i]->vertex<<endl;
}