#include "Graphs/Headers/AdjacencyLists.h"
#include "Graphs/Headers/Graph.h"
#include "Graphs/Headers/LinkCutTree.h"
#include "Graphs/Headers/Network.h"
#include "Headers/GraphLexer.h"
#include <iostream>
#include <string>
#include <cassert>
#include <vector>

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
    for(auto src : graph.GetVertices())
    {
        for(auto dst : graph.GetVertices())
        {
            if(src == dst)
                continue;
            Network<int> net = Network<int>(&graph, src, dst);
            net.buildMaxFlow();
            for(auto flowEdge : net.getFlows()) // flowEdge is a pair containing an edge and a flow
            {
                if(flowEdge.second <= 0 
                    || graph.GetEdge(flowEdge.first.first, flowEdge.first.second).isProtected)
                    continue;
                edgeOccurrences[flowEdge.first] = (!edgeOccurrences[flowEdge.first]) ? 1 : edgeOccurrences[flowEdge.first] + 1;
                if(edgeOccurrences[flowEdge.first] > maxOccurrence.second)
                    maxOccurrence = flowEdge;
            }
        }
    }
    if(maxOccurrence.second == -1)
    {
        std::cout << "Could not find an edge!" << std::endl;
        return 0;
    }
    std::cout << lexer.getEdgeIndex(maxOccurrence.first.first, maxOccurrence.first.second);
}