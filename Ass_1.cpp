// Design and implement Parallel Breadth First Search and Depth First Search based on existing
// algorithms using OpenMP. Use a Tree or an undirected graph for BFS and DFS .

#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

class Graph
{
    public:

    int vertices;
    int edges;
    // int vertices = 4;
    // vector<vector<int>> graph = {{1, 2}, {0, 2, 3}, {0, 1, 3}, {1, 2}};
    vector<bool> visited;

    vector<vector<int>> graph;
    void initialize_graph()
    {
        cout<<"Enter the number of vertices in a graph: -";
        cin>>vertices;
        for(int i = 0; i<vertices; i++)
        {
            cout<<"Enter the vertices to which the vertex "<<i<<" is connected (if not print -1) \n";
            int a;
            vector<int> g;
            do{
                cout<<"Enter: -";
                cin>>a;
                if(a != -1)
                {
                    g.push_back(a);
                }
            }while(a!= -1);
            graph.push_back(g);
        }
    }
    void printGraph()
    {
        for(int i = 0; i<vertices; i++)
        {
            cout<<i<<" ==> ";
            for(auto j = graph[i].begin(); j!= graph[i].end(); j++)
            {
                cout<<*j<<" ";
            }
            cout<<endl;
        }
    }
    void initialize_visited()
    {
        visited.assign(vertices, false);
    }
    void seq_bfs(int i)
    {
        queue<int> q;
        double start = omp_get_wtime();
        q.push(i);
        visited[i] = true;
        while(!q.empty())
        {
            int a = q.front();
            q.pop();
            cout<<a<< " ";
            for(auto j = graph[a].begin(); j!= graph[a].end(); j++)
            {
                if(visited[*j] == false)
                {
                    q.push(*j);
                    visited[*j] = true;
                }
            }
        }
        double end = omp_get_wtime();
        cout<<"\n The required of sequential BFS is "<<end-start<<endl;
    }
    void parallel_bfs(int i)
    {
        queue<int> q;
        double start = omp_get_wtime();
        q.push(i);
        visited[i] = true;
        while(!q.empty())
        {
            int a = q.front();
            #pragma omp critical
            q.pop();
            cout<<a<< " ";
            #pragma omp parallel for
            for(auto j = graph[a].begin(); j!= graph[a].end(); j++)
            {
                if(visited[*j] == false)
                {
                    #pragma omp critical
                    q.push(*j);
                    visited[*j] = true;
                }
            }
        }
        double end = omp_get_wtime();
        cout<<"\n The required of parallel BFS is "<<end-start<<endl;
    }
    void seq_dfs(int i)
    {
        stack<int> q;
        double start = omp_get_wtime();
        q.push(i);
        visited[i] = true;
        while(!q.empty())
        {
            int a = q.top();
            q.pop();
            cout<<a<< " ";
            for(auto j = graph[a].begin(); j!= graph[a].end(); j++)
            {
                if(visited[*j] == false)
                {
                    q.push(*j);
                    visited[*j] = true;
                }
            }
        }
        double end = omp_get_wtime();
        cout<<"\n The required of sequential DFS is "<<end-start<<endl;
    }
    void parallel_dfs(int i)
    {
        stack<int> q;
        double start = omp_get_wtime();
        q.push(i);
        visited[i] = true;
        while(!q.empty())
        {
            int a = q.top();
            #pragma omp critical
            q.pop();
            cout<<a<< " ";
            #pragma omp parallel for
            for(auto j = graph[a].begin(); j!= graph[a].end(); j++)
            {
                if(visited[*j] == false)
                {
                    #pragma omp critical
                    q.push(*j);
                    visited[*j] = true;
                }
            }
        }
        double end = omp_get_wtime();
        cout<<"\n The required of parallel DFS is "<<end-start<<endl;
    }
};

int main()
{
    Graph g;
    g.initialize_graph();
    g.printGraph();
    g.initialize_visited();
    g.seq_bfs(0);
    g.initialize_visited();
    g.parallel_bfs(0);
     g.initialize_visited();
    g.seq_dfs(0);
    g.initialize_visited();
    g.parallel_dfs(0);
    return 0;
}