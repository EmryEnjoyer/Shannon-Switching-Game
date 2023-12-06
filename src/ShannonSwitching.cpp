#include "Graphs/Headers/AdjacencyLists.h"
#include "Graphs/Headers/Graph.h"
#include "Graphs/Headers/LinkCutTree.h"
#include "Graphs/Headers/Network.h"
#include "Headers/GraphLexer.h"
#include <iostream>
#include <string>
#include <cassert>
#include <vector>

#define INFINITY 1000000

// int main(int argc, char ** argv)
// {
//     TreeNode<int,int> root(1, 3);
//     TreeNode<int,int> a(2,3, &root);
//     TreeNode<int,int> b(3,3, &root);
//     TreeNode<int,int> c(5,17,&a);
// 
//     std::vector<TreeNode<int,int> *> roots = std::vector<TreeNode<int,int> *>();
//     roots.push_back(&root);
// 
//     LinkCutTree<int> lkt = LinkCutTree<int>(roots);
//     lkt.access(lkt.getSplayNode(c.key));
//     
// }

int score(Graph<int,int> * graph)
{
    std::vector<int> verts = graph->GetVertices();
    int numVerts = verts.size();

    long int dist[numVerts][numVerts];
    for(int i = 0; i < numVerts; ++i)
        for(int j = 0; j < numVerts; j++)
        {
            auto ec = graph->GetEdge(verts[i], verts[j]);
            if(i == j)
                dist[i][j] = 0;
            else if(ec.cost > 0)
                dist[i][j] = ec.cost;
            else
                dist[i][j] = INFINITY;
        }
    
    for(int k = 0; k < numVerts; ++k)
        for(int i = 0; i < numVerts; ++i)
            for(int j = 0; j < numVerts; ++j)
                if(dist[i][j] > dist[i][k] + dist[k][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
    
    int score = 0;
    for(int i = 0; i < numVerts; ++i)
        for(int j = 0; j < numVerts; ++j)
            score += dist[i][j];
    return score;
}

int main(int argc, char ** argv) 
{
    // if(argc < 2) {
    //     std::cout << "usage: ./ShannonSwitching <short | cut> < <filename>" << std::endl;
    //     std::cout << argc << std::endl;
    //     for(int i = 0; i < argc; ++i)
    //     {
    //         std::cout << argv[i] << std::endl;
    //     }
    //     return 0;
    // }
    // std::string mode = argv[1];
    // 
    // assert(mode == "short" || mode == "cut");

    AdjacencyLists<int,int> graph = AdjacencyLists<int,int>(false, true);

    GraphLexer<int,int> lexer = GraphLexer<int,int>(graph);

    std::cin >> lexer;
    std::map<std::pair<int,int>, int> edgeOccurrences;
    std::pair<std::pair<int,int>,int> maxOccurrence(std::pair(-1,-1),-1);
    std::set<std::pair<int,int>> visited;
    for(auto src : graph.GetVertices())
    {
        for(auto dst : graph.GetVertices())
        {
            if(visited.count(std::pair(src,dst)) > 0)
                break;
            if(src == dst)
                continue;
            visited.insert(std::pair(src,dst));
            visited.insert(std::pair(dst,src));
            Network<int> net = Network<int>(&graph, src, dst);
            net.buildMaxFlow();
            for(auto flowEdge : net.getFlows()) // flowEdge is a pair containing an edge and a flow
            {
                if(flowEdge.second == 0 
                    || graph.GetEdge(flowEdge.first.first, flowEdge.first.second).isProtected)
                    continue;
                edgeOccurrences[flowEdge.first] = (!edgeOccurrences[flowEdge.first]) ? 1 : edgeOccurrences[flowEdge.first] + 1;
                if(edgeOccurrences[flowEdge.first] > maxOccurrence.second)
                    maxOccurrence = std::pair(flowEdge.first, edgeOccurrences[flowEdge.first]);
            }
        }
    }

    for(auto occurrenceData : edgeOccurrences)
    {
        if(occurrenceData.second == maxOccurrence.second
            && graph.GetEdge(occurrenceData.first.first, occurrenceData.first.second).cost < graph.GetEdge(maxOccurrence.first.first, maxOccurrence.first.second).cost)
            maxOccurrence = occurrenceData;
    }

    // std::cout << "cost: " << score(&graph) << std::endl;

    if(maxOccurrence.second == -1)
    {
        std::pair<std::pair<int,int>, EdgeCost<int>> minEdge = std::pair(std::pair(0,0), EdgeCost(0,0,true));
        for(auto edge : graph.getEdges())
        {
            if(!edge.second.isProtected 
                && (minEdge.second.isProtected 
                    || edge.second.cost < minEdge.second.cost))
            {
                minEdge = edge;
            }
        }
        std::cout << lexer.getEdgeIndex(minEdge.first.first, minEdge.first.second) << std::endl;
        return 0;
    }
    std::cout << lexer.getEdgeIndex(maxOccurrence.first.first, maxOccurrence.first.second);
}