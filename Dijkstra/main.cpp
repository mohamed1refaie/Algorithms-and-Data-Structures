#include <bits/stdc++.h>
using namespace std;

const double OO = 1e5;  /// i define OO "infinity as a big number "

class graph
{
private:
    int vertices;   /// the number of the vertices in the graph
    int edges;     /// the number of the edges in the graph
    int adj[10000][10000];   /// the adjacency matrix of the graph
    double distance[100];   /// the shortest distance array from the source to every node


public:

    graph(int v=0):vertices(v),edges(0){   /// constructor set the number of vertices and initially the number of edges equals zero

        for(int i=0;i<100;i++)           /// nested loop to set the adjacency matrix all to zeros
        {
            for(int j=0;j<100;j++)
                adj[i][j]=0;
        }

    }

    int V()
    {
        return vertices;                /// getter to return the number of vertices
    }

    int E()
    {
        return edges;                 /// getter to return the number of edges
    }

    bool adjecent(int x,int y)
    {
        return adj[x][y]>0;         /// bool function to check if there is an edge between two nodes or not
    }

    vector<double> neighbors(int x)         /// function return a vector contains all the neighbors of a certain node
    {
        vector< double > vec;
        for(int i=1;i<=vertices;i++)
        {
            vec.push_back(adj[x][i]);
        }
        return vec;
    }

    vector< vector<double> >all()         /// function return a vector contains all the adjacency matrix  of the graph
    {
        vector< vector<double> > ret;
        for(int i=0;i<=vertices;i++)
        {
            for(int j=0;j<=vertices;j++){
                    ret[i].push_back(adj[i][j]);
            }
        }
        return ret;
    }


    void add(int x,int y,int cost)               ///function to add an edge between node x and node y with cost
    {
        if(cost<0)                             /// checking if the cost positive
        {
            cout<<"Cost cannon't be negative"<<endl;
            return;
        }

        if(x>=1&&x<=vertices&&y>=1&&y<=vertices){       /// checking if the x and y in the graph
            if(adj[x][y]==0)edges++;
            adj[x][y]=cost;
            adj[y][x]=cost;
        }
        else cout<<"OUT OF BOUNDRIES"<<endl;
    }

    void Delete(int x,int y)                          /// function to delete an edge from node x and node y
    {
        if(x>=1&&x<=vertices&&y>=1&&y<=vertices){        /// checking if x and y in the graph
            if(adj[x][y]!=0)edges--;
            adj[x][y]=0;
            adj[x][y]=0;
        }
         else cout<<"OUT OF BOUNDRIES"<<endl;
    }

    double get_edge_value(int x,int y)              /// getter to get the value of an edge between two nodes x and y
    {
        if(x>=1&&x<=vertices&&y>=1&&y<=vertices)          /// checking  if x and y in the graph
            return adj[x][y];
        else return -1;
    }

    int Dijkstra(int src,int dest = -1)            /// Dijkstra function to get the shortest path , giving it the source and the destination
    {
        int n = vertices;                            /// set n to the number of vertices

        vector<int> vis(n+1,0), prev(n+1, -1);            /// makr two vectors visited and previous

         for(int i=0;i<100;i++)               /// for loop to make all the distances equals to infinity (the big number)
        {
            distance[i]=OO;
        }

        distance[src] = 0;                   /// make the distance from the source to itself equal zero

        while(true) {                                  /// a while loop to check the shortest path
            double val = OO;                          /// make val equal infinity
            int idx = -1;                            /// make idx equal -1
            for(int i=1;i<=n;i++)                     /// for loop to check the node that has shortest distance till now and not visited
                if(!vis[i]&&distance[i]<val)val=distance[i],idx = i;
            if(idx==-1||idx==dest)break;              /// if i find the destination and or there's no such a node i break
            vis[idx] = 1;                           /// i visit this node
            for(int i=1;i<=n;i++)                      /// for loop to update the distances of the neighbors
                if (distance[i]>(val=distance[idx]+adj[idx][i])&&adjecent(idx,i))
                    distance[i]=val,prev[i]=idx;
        }
        return dest == -1 ? -1 : distance[dest];         /// return the distance from the source to destination
    }

        double averageDistance()                /// function compute the average distances of the graph
        {
            double sum=0;
            int adjacent_vertices=vertices;
            for(int i=1;i<=vertices;++i)
            {
                    if(distance[i]==OO) adjacent_vertices--;
                    else sum+=distance[i];
            }
            return sum/adjacent_vertices;
        }

        void Simulation(double density, double lowcost, double highcost)          /// function give a graph with a certain  density
        {
            double probability,cost;
            for(int i=1;i<=50;++i)
            {
                for(int j=i+1;j<=50;++j)
                {
                    probability=static_cast<double>(rand())/RAND_MAX;
                    if(probability<=density)
                    {
                        cost=lowcost+(highcost-lowcost)*(static_cast<double>(rand())/RAND_MAX);
                        add(i,j,cost);
                    }
                }
            }
        }


};


int main()
{

    srand(time(0));
    double sum1=0,sum2=0;
    for(int i=0;i<1000;i++)
    {
            graph g1(50);
            graph g2(50);
            g1.Simulation(0.20,1,10);
            g2.Simulation(0.40,1,10);
            g1.Dijkstra(1);
            g2.Dijkstra(1);
            sum1+=g1.averageDistance();
            sum2+=g2.averageDistance();
    }

    cout<<"average distance of a 20% Density graph with weights between 1 and 10 is "<<sum1/1000.0<<endl;
    cout<<"average distance of a 40% Density graph with weights between 1 and 10 is "<<sum2/1000.0<<endl;





    return 0;
}
