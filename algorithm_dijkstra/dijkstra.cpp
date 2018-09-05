#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

const uint64_t maxDIST = 1000000000;

int main()
{
  int n, edgesNum, edgeIndex, edgeWeight;

  /*
   cout << "Enter number of vertices " << endl;
   cin >> n;
  */

  ifstream file;
  file.open("data.txt");
  file >> n;
  cout << "Graph contains "<< n << " vertices. " << endl << endl;
  vector <vector < pair<int, int> > > graph(n);
  for(int i = 0; i < n; ++i)
    {
      file >> edgesNum;
        for(int j = 0; j < edgesNum; ++j)
	      {
	        file >> edgeIndex >> edgeWeight;
	        graph[i].push_back(make_pair(edgeIndex-1, edgeWeight));
	      }
    }

  //print vertices and edge length
  
  for(int i = 0; i < n; ++i)
    {
      cout << "Vertex number " << i+1 << " connected to: " << endl;
        for(const auto& x: graph[i])
	      {
	        cout << x.first + 1 << " , edge length: " << x.second << endl;
	      }
    }

  int initVert;

  cout << "\n" <<"Enter initial vertex " << endl;
  cin >> initVert;

  vector<int> distance(n, maxDIST);
  vector<bool> visited(n, false);
  vector<int> parents(n);
  distance[initVert-1] = 0;
  for(int i = 0; i < n; ++i)
    {
      int currVert = -1;
      for(int j = 0; j < n; ++j)
	      if(!visited[j] && (currVert == -1 || distance[j] < distance[currVert]))
	        currVert = j;
      
      if(distance[currVert] == maxDIST)
	      break;
      visited[currVert] = true;

      for(const auto& edge: graph[currVert])
	    {
	      int probEdge = edge.first;
	      int probDist = edge.second;
	      if(distance[currVert] + probDist < distance[probEdge])
	      {
	        distance[probEdge] = distance[currVert] + probDist;
	        parents[probEdge] = currVert;
	      }
	    }
    }

  for(int i = 0; i < distance.size(); ++i)
    {
      if(distance[i] == maxDIST)
	      cout << "No ways to vertex number " << i+1 << " !" << endl;
      else
	    {
	      cout << "Distance from " << initVert << " to " << i+1 << " is " << distance[i] << endl;
	      //path to each vertex
	  
	      vector<int> path;
	      int temp = i;
	      for(int vert = temp; vert != initVert-1; vert = parents[vert])
	        path.push_back(vert);
	      path.push_back(initVert-1);
	      reverse(path.begin(), path.end());
	      cout << "Path from initial vertex to vertex number " << temp+1 << " is " << "\n";
	      for(auto it : path)
	        if(it != temp)
		        cout << "vertex " << it+1 << " --> ";
	        else
		        cout << "vertex " << it+1 << endl << endl;	 
	    }
    }

  return 0;
}
