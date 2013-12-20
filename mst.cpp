#include "fibHeap.hpp"
#include "simpleScheme.hpp"


void dfs(vector <vector <node*> > &adj_list,vector <bool> &visited, int u, int n)
{
	visited[u] = true;
	for(int i =0; i< adj_list[u].size(); i++)
	{
		int v = adj_list[u][i]->vertex;
		if(!visited[v])
			dfs(adj_list,visited,v,n);
	}
	//return count;
}
		
bool check_connected(vector <vector <node*> > &adj_list, int vertices)
{
	vector <bool> visited;

	for(int j =0; j < vertices; j++) 
		visited.push_back(bool());

	 dfs(adj_list, visited, 0, vertices);

	for(int j =0; j < vertices; j++) 
	{
		if(visited[j] == false)
			return false;
	}

	return true;

}
bool createRandomGraph(vector <vector <node*> > &adj_list, int vertices, int density)
{
	int i =0;
	int vertex1, vertex2, weight ,edge_count = 0;
	srand(time(0));
	float d = (float)density/100;
	long long final_edge_count = d*vertices*(vertices - 1)/2;
	if (final_edge_count < (vertices-1))    // checking for configuration for which connected graph is not possible
	{	
		cout<<"connected graph not possible for this value of vertices and density" <<endl;
		return false;
	}
	set<int>  :: iterator it1;
	vector<set<int> > edges;
	int number =0 ;
	for(int j =0; j < vertices; j++) 
			edges.push_back(set<int>());

	bool already_inserted ;
	do
	{
		for(int j =0; j < vertices; j++) 
		{
			adj_list[j].clear();
			edges[j].clear();
		}
		edge_count = 0;
		
		do
		{
			number++;
			vertex1 = rand()%vertices;
			vertex2 = rand()%vertices;
			weight = (rand()%1001);
			it1 = edges[vertex1].find(vertex2);
			already_inserted = false;
			
			if(it1 != edges[vertex1].end())
			{
				if(*it1  == vertex2)
					already_inserted = true;
			}



			if((already_inserted == false) && (vertex1 != vertex2))
			{
				edges[vertex1].insert(vertex2);
				edges[vertex2].insert(vertex1);
				node * temp1 = new node;
				node * temp2 = new node;
				temp1-> vertex = vertex2;
				temp1-> weight = weight;
				temp2->vertex  = vertex1;
				temp2->weight = weight;
				adj_list[vertex1].push_back(temp1);
				adj_list[vertex2].push_back(temp2);
				edge_count++;
				 //edge_count++;
					//break;

			}
		}while(final_edge_count != edge_count);
	}while(!check_connected(adj_list,vertices));
	cout<<number;
	return true;

}





int main(int argc, char * argv[])
{   
	int v1,v2,w,i = 0,input_type = 1;
	int vertices, edges, total_cost_s,total_cost_f, mst_mode = 0, density;
	clock_t start,time_f,time_s;
	ifstream infile;
	char * fileName;
	if(!(strcmp(argv[1],"-f")) || !(strcmp(argv[1],"-s")))
	{
		fileName = argv[2];
		infile.open(fileName, ifstream::in);
		infile>>vertices>>edges;
	}
	else
	{
		vertices = atoi(argv[2]);
		density = atoi(argv[3]);
	}
	simpleScheme *s = new simpleScheme();
	fibHeap *f = new fibHeap();
//	f->setVertices(vertices);
	vector <vector <node*> > adj_list(vertices);    // to store adjacency_list
	vector <mst_node*> min_q;                      //array used for simple scheme
	vector <mst_node*> mst_list;				  // array used for storing mst built in simple scheme	
	vector <fibNode*> fibMst_list;				 // array used for storing mst built in Fibonacci scheme
	
	for(int j=0;j<vertices;j++)
	{    
		adj_list.push_back( vector<node*>() ); 
	}
	
	
	if(!(strcmp(argv[1],"-f")) || !(strcmp(argv[1],"-s")))
	{
		
		while(infile >>v1>>v2>>w)  // reading from file and creating Adjacentcy list nodes
		{

			node * temp1 = new node;
			node * temp2 = new node;
			temp1-> vertex = v2;
			temp1-> weight = w;
			temp2->vertex  = v1;
			temp2->weight = w;
			adj_list[v1].push_back(temp1);
			adj_list[v2].push_back(temp2);
			//i+=3;
		}
	
		if(!strcmp(argv[1],"-s"))
		{
		
			s->init_min_q(vertices, min_q);
			total_cost_s = s->mst(min_q,mst_list,adj_list,vertices);      // calling prims algo for simple scheme
			s->printData(total_cost_s,mst_list);

		}
		else if (!strcmp(argv[1],"-f"))
		{
			
			f->createNodes(vertices);
			total_cost_f = f->fibMST(adj_list, vertices,fibMst_list);  //calling prims algo for Fib scheme
			f->printData(total_cost_f,fibMst_list);
		}

	}
	else if (!strcmp(argv[1],"-r"))
	{
		

		//cout<<"start"<<clock();

		bool graphStatus = createRandomGraph(adj_list, vertices , density);

	/*	for(i=0; i< 10;i++)
		{
			cout <<" "<< i<<" ";
			for(int j = 0; j <adj_list[i].size();j++)
				cout<<adj_list[i][j]->vertex<<" "<<adj_list[i][j]->weight<<" ";
			cout<<endl;
		}*/
		if(graphStatus)
		{
			start = clock();
			
			s->init_min_q(vertices, min_q);
			total_cost_s = s->mst(min_q,mst_list,adj_list,vertices);  // calling prims algo for simple scheme
			time_s = clock()-start;
			
			s->printData(total_cost_s,mst_list);
			
			cout<<"simple end"<<endl;
			
			start = clock();	
			f->createNodes(vertices);
			total_cost_f = f->fibMST(adj_list, vertices,fibMst_list);		 //calling prims algo for Fib scheme
			f->printData(total_cost_f,fibMst_list);
			cout<<"Cost of Simple Scheme " <<total_cost_s<<endl;
			cout<<"Cost of Fibonacci Scheme " <<total_cost_f<<endl;
			cout <<"Time Taken by Simple Scheme" <<" "<<time_s<<endl;
			cout <<"Time Taken by Fibonacci Scheme" <<" "<<clock()-start<<endl;
			
		}
		//cout<<"end"<<clock();
	}

   	    


	return 0;
	
}
