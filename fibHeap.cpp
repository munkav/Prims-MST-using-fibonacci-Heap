#include "fibHeap.hpp"
#include "common.hpp"
#include <cmath>

//function for implementing prims algorithm using fibonacci heap.
int fibHeap::fibMST( vector <vector <node*> > &adj_list, int vertex,  vector <fibNode*> &mst_list)
{

	fibNode* min ;
	int min_v ;
	int total_cost = 0;
	
	
	for(int k = 0; k < vertex; k++)
	{	
		min = removeMin();   //removing min
		min->visited = true;
		min_v = min->vertex;
		if(min_v != 0)
			mst_list.push_back(min);  //creating mst_list which will be used to print MST at the end
		total_cost = total_cost +  min->weight;
		if(min_ptr == NULL)
			break;
		for(int i = 0; i <adj_list[min_v].size();i++)
		{
			int v = adj_list[min_v][i]->vertex;  // vertex of  nodes adjacent to the currrent minimum node
			int w = adj_list[min_v][i]->weight; 
			if(!node_list[v]->visited)
				decreaseKey(v, w, min_v);
		}
	
	}
	
	return total_cost;
}

// inserting nodes in the heap after the min_ptr
void fibHeap::Insert(fibNode *node)
{
     if (node == NULL) return;

     if (min_ptr == NULL)
	 {
		 min_ptr = node->left = node->right = node;
	 }
     else
     {
		fibNode * temp = min_ptr->right;
		node->right = min_ptr->right;  
		node->left = min_ptr;   //inserting after min_ptr
		min_ptr->right = node;
		temp->left = node;
        if (node->weight < min_ptr->weight)
		{
			 min_ptr = node;
		}
     }
	 node->childcut = false;
     node->parent = NULL;
	 numNodes=numNodes+1;
}

//adding children of removed min_ptr to the top level list.
void fibHeap::Union(fibNode *child)
{
	//fibNode *Min1, *Min2, 
	fibNode *right, *addChild;
	if (child == NULL)
		return;
	 right = child;
	 addChild = right;
	 fibNode * lastChild = child->left;
	 do
	 {
		 addChild = right;
		 if(right == NULL)
			 cout<<"right NULL";
		 else
			 right = addChild->right;
		 Insert(addChild);
	 }
	 while(addChild != lastChild);
}

//Decreasing value  of a node and calling cut and cascadingCut if needed.
void fibHeap::decreaseKey(int vertex, int weight, int other_end)
{	
	

	fibNode * node = node_list[vertex];
	//fibNode * node = find(vertex);
	fibNode *parent;

     if (node==NULL || node->weight < weight)
         return ;
     
	 node->weight = weight;
	 node->other_end = other_end;
     parent = node->parent;
	
	 if (parent != NULL && node->weight < parent->weight)
     {
         cut(node, parent);
         cascading_cut(parent);
     }

	 if (node->weight < min_ptr->weight)
	 {
         min_ptr = node;
	 }


}

//Removing child from the parent and adding it to the top level list
void fibHeap ::cut(fibNode* x, fibNode*y)
{	
	fibNode * temp;
	if(x->right != x)
	{
		if(x == y->child)
		{
			y->child = x->right;
			
		}
			
			x->left->right = x->right;
			x->right->left = x->left;
		
	}
	else
	{
		y->child = NULL;
	}
	y->degree = y->degree - 1;

	temp = min_ptr->right;
	min_ptr->right = x;
	x->left = min_ptr;
	x->right = temp;
	temp->left = x;

	x->parent = NULL;
	x->childcut = false;
}

// removing parents and adding to top level list if childcut is true
void fibHeap::cascading_cut(fibNode * y)
{  
	fibNode *z = y->parent;

     while (z != NULL)
     {
         if (y->childcut == false)
         {
             y->childcut = true;
            
             z = NULL;
         }
         else
         {
             cut(y, z);
             y = z;
	     z = y->parent;
         }
     }
}


//function to find node corresponding to vertex in a heap
fibNode * fibHeap::find(int vertex){
    fibNode * temp = min_ptr;
    fibNode * t;
    do 
	{
            t = findInChild(vertex,temp);
            if ( t )
			{
                    return t;
            }
            temp = temp->right;
    } while ( temp != min_ptr );
    return NULL;
}

//Recursive Function to find node corresponding to a particular vertex.
fibNode * fibHeap::findInChild(int vertex, fibNode* parent){
       
	if ( vertex == parent->vertex )
	{      
		return parent;
    } 
	else if ( parent->child )
	{
            fibNode * temp = parent->child;
            fibNode * test;

            do 
			{
                    test = findInChild(vertex, temp);
                    if ( test != NULL )
					{
                            return test;
                    } else 
					{
                            temp = temp->right;
                    }
            } while ( temp != parent->child);
    }
    return NULL;
}



//Combining trees of equal degree after removeMin()

void fibHeap::pairwiseCombine()
{

	fibNode *x, *y, *w;

	int  i = 0;
	int d;
	vector<fibNode*> top_level_list;
	fibNode* temp;
	int top_level_count =0;
	temp = min_ptr;
	float v = numNodes;
	float D = ceil((log(v)/log(1.62))); // take D as no of log n base golden ratio for the array size.
	int degree = D;
	vector <fibNode*> A(degree);

	do
	{
		top_level_list.push_back(temp);
		if(temp->right)
		temp = temp->right;
		top_level_count++;
	}while(temp!=min_ptr);    // taking a list of top level nodes.

		 for (i=0; i < degree; i++)
			  A[i] = NULL;

		 for(i=0; i< top_level_count; i++)
		 {
			w = top_level_list[i];

			x = w;
			d = x->degree;
			w = w->right;
			while (A[d] != NULL)
			{
				 y = A[d];
				 if (y->weight < x->weight)
				 {
				 	
					fibNode * temp = y;
					y = x;
					x = temp;
				 }			
				 link(y, x);
				 A[d] = NULL;
				 d++;
			}
			A[d] = x;

		 } 
		 min_ptr = NULL;

		 for (i = 0; i < degree; i++)
			  if (A[i] != NULL)
			  {		
				  if(min_ptr == NULL)
					  min_ptr = A[i];
				  if(A[i]->weight < min_ptr->weight)
					  min_ptr = A[i];
			  }  //updating min_ptr

}


//taking out y from the rootlevel list and adding it as a child of x in pairwiseCombine
void fibHeap::link(fibNode *y, fibNode *x)
{

	 y->right->left = y->left;
     y->left->right = y->right;

     y->left = y->right = y;
     y->parent = x;

     if (x->child == NULL)
		 x->child = y;
     else
     {
         y->left = x->child;
         y->right = x->child->right;
         x->child->right = y;
         y->right->left = y;
     }
	x->degree++;

     if (y->childcut) 
     y->childcut = false;
	 
}


// Returning the current min_ptr and doing the pairwiseCombine after that.
fibNode* fibHeap::removeMin()
{
	fibNode *removedMin;
	fibNode *childmin = NULL;


     if ((removedMin = min_ptr) == NULL) 
          return NULL;

// Remove minimum node and set min_ptr to right node
     min_ptr = removedMin->right;  
     removedMin->right->left = removedMin->left;
     removedMin->left->right = removedMin->right;
     removedMin->left = removedMin->right = NULL;

     if (removedMin->child == NULL)
     {
	 if (min_ptr == removedMin)
	     min_ptr = NULL;
     }
     else if (min_ptr == removedMin)
	 {
         min_ptr = removedMin->child;
	 }
	 else
         childmin = removedMin->child;
 
     if (removedMin->child != NULL)
	 removedMin->child->parent = NULL;
     removedMin->child = removedMin->parent = NULL;
     if (childmin)
         Union(childmin);

     if (min_ptr != NULL)
         pairwiseCombine();

	 numNodes=numNodes-1;
// Return the minimum node
     return removedMin;
}

	

// Function used to create initial heap with weight of each node as MAX_INT and weight of starting node as 0.
void fibHeap::createNodes(int ver)
{
	vertices = ver;
	for(int i = 0; i < vertices  ; i++)
	{    
		 if(i == 0)
			 addNode(i,0);
		 else
			addNode(i,INT_MAX);
	}
	//printData();
}


//Function to create nodes.
void fibHeap::addNode(int v, int weight)
{
	fibNode * node = new fibNode;
	
	node->vertex = v;
	node->weight = weight;
	node->degree = 0;
	node->child = NULL;
	node->parent = NULL;
	node->right = node;
	node->left = node;
	node->other_end = 0;
	node->childcut = false;
	node->visited = false;

	Insert(node);
	node_list.push_back(node);
}

//Utility function to print created MST.
void fibHeap::printData(int total_cost,  vector <fibNode*> &mst_list)
{
	cout<<total_cost<<endl;
	int size = mst_list.size();
	for(int i = 0; i < size ;i++)
		cout<<mst_list[i]->other_end<<" "<<mst_list[i]->vertex<<endl;
}

