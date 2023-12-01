#include "Graphs/Headers/AdjacencyLists.h"
#include "Graphs/Headers/Graph.h"
#include "Graphs/Headers/LinkCutTree.h"
#include "Graphs/Headers/Network.h"
#include "Headers/GraphLexer.h"
#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#define INFINITY 1000000000

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

    int dist[numVerts][numVerts];
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

    std::map<std::pair<int,int>, float> edgeOccurrences;
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
                if(flowEdge.second <= 0 
                    || graph.GetEdge(flowEdge.first.first, flowEdge.first.second).isProtected)
                    continue;
                float increment = flowEdge.second;
                edgeOccurrences[flowEdge.first] = (!edgeOccurrences[flowEdge.first]) ? increment 
                    : edgeOccurrences[flowEdge.first] + increment;
                if(edgeOccurrences[flowEdge.first] < maxOccurrence.second || maxOccurrence.second == -1 )
                    maxOccurrence = flowEdge;
            }
        }
    }
    if(maxOccurrence.second == -1)
    {
        std::cout << "Could not find an edge!" << std::endl;
        return 0;
    }
    std::cout << lexer.getEdgeIndex(maxOccurrence.first.first, maxOccurrence.first.second) << "\n";
    // std::cout << "score: " << score(&graph) << "\n";
}