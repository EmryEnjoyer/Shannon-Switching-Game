#include "AdjacencyLists.h"
#include "Graph.h"
#include <iostream>
#include <map>
#include <utility>
#include <queue>
#include <stack>
#include <set>

#ifndef NETWORK_H
#define NETWORK_H

template <typename V>
class Network
{
    Graph<V,int> * underlyingGraph;
    V source;
    V destination;

    std::map<std::pair<V,V>, int> residualCapacities;
    std::map<std::pair<V,V>, int> flows;
    
public:
    Network(Graph<V,int> * underlyingGraph, V src, V dst)
    {
        this->underlyingGraph = underlyingGraph;
        source = src;
        destination = dst;

        bool haveFoundDestination = false;
        std::queue<V> todo = std::queue<V>();
        todo.push(src);
        while(!todo.empty())
        {
            V front = todo.front();
            todo.pop();
            for(auto neighbor : underlyingGraph->GetNeighbors(front))
            {
                if(!residualCapacities[std::pair(front, neighbor)])
                {
                    todo.push(neighbor);

                    residualCapacities[std::pair(front, neighbor)] = underlyingGraph->GetEdge(front, neighbor).cost;
                    residualCapacities[std::pair(neighbor, front)] = -residualCapacities[std::pair(front,neighbor)];
                }
            }
        }
    }

    AdjacencyLists<std::pair<V, int>,int> getLevelGraph()
    {
        AdjacencyLists<std::pair<V,int>,int> levelGraph = AdjacencyLists<std::pair<V,int>,int>(true, false);
        std::map<V,int> levelMap;

        std::queue<std::pair<V,int>> todo = std::queue<std::pair<V,int>>();
        
        todo.push(std::pair(source,0));
        while(!todo.empty())
        {
            std::pair<V,int> top = todo.front();
            todo.pop();

            if(!levelMap[top.first])
            {
                levelMap[top.first] = top.second;
                levelGraph.AddVertex(top);
            }
            for(auto vert : underlyingGraph->GetNeighbors(top.first))
            {
                if(!levelMap[vert])
                {
                    todo.push(std::pair(vert, top.second+1));
                    levelGraph.AddVertex(std::pair(vert, top.second+1));
                    levelMap[vert] = top.second+1;
                }
                if(levelMap[vert] > top.second 
                && residualCapacities[std::pair(top.first, vert)] > 0)
                {
                    levelGraph.AddEdge(top, std::pair(vert, levelMap[vert]), false);
                }
            }
        }

        return levelGraph;
    }

    std::vector<V> performDFS(Graph<std::pair<V,int>,int> & levelGraph) 
    {

        std::stack<std::pair<V, int>> todo = std::stack<std::pair<V, int>>();
        std::set<V> visited;

        std::map<V,V> parentMap;

        todo.push(std::pair(source, 0));
        visited.insert(todo.top().first);
        while(!todo.empty() && !parentMap[destination])
        {
            std::pair<V,int> top = todo.top();
            todo.pop();
            for(auto vert : levelGraph.GetNeighbors(top))
            {
                if(vert.first == destination)
                {
                    parentMap[destination] = top.first;
                }
                else if(vert.second > top.second && visited.count(vert.first) == 0)
                {
                    todo.push(vert);
                    visited.insert(vert.first);
                    parentMap[vert.first] = top.first;
                }
            }
        }

        if(!parentMap[destination])
            return std::vector<V>();
        
        std::vector<V> returnValue;
        returnValue.push_back(destination);
        while(parentMap[returnValue.back()])
        {
            returnValue.push_back(parentMap[returnValue.back()]);
        }
        return returnValue;
    }

    void buildMaxFlow()
    {
        while(true)
        {
            auto levelGraph = getLevelGraph();
            std::vector<V> path = performDFS(levelGraph);
            if(path.size() == 0)
            {
                break; // We aren't conencted.
            }
            
            while(path.size() > 0)
            {
                int bottleneckValue = -1;
                std::stack<std::pair<V,V>> pathCuts;
                for(int i = 0; i < path.size() - 1; ++i)
                {
                    std::pair<V,V> edge = std::pair(path[i+1],path[i]);
                    if(bottleneckValue < 0 || residualCapacities[edge] < bottleneckValue)
                        bottleneckValue = residualCapacities[edge];
                    levelGraph.RemoveEdge(std::pair(edge.first, path.size() - i - 2), 
                                          std::pair(edge.second, path.size() - i - 1));
                    pathCuts.push(edge);
                }
                while(!pathCuts.empty())
                {
                    auto top = pathCuts.top();
                    pathCuts.pop();
                    residualCapacities[top] -= bottleneckValue; // Guaranteed to be greater than or equal to 0
                    flows[top] += bottleneckValue;
                    flows[std::pair(top.second, top.first)] -= bottleneckValue;
                    residualCapacities[std::pair(top.second, top.first)] = flows[top];
                }

                path = performDFS(levelGraph);
            }
        }
    }

    void printFlows()
    {
        for(auto pair : flows)
        {
            if(pair.second > 0)
                std::cout << pair.first.first << " -> " 
                        << pair.first.second 
                        << " [label=\"" 
                        << pair.second 
                        << "\"]\n";
        }
    }

    std::map<std::pair<V,V>, int> getFlows() {return flows;}

};
#endif