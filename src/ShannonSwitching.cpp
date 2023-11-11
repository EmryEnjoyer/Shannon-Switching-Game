#include "Graphs/Headers/AdjacencyLists.h"
#include "Graphs/Headers/Graph.h"
#include "Graphs/Headers/LinkCutTree.h"
#include "Headers/GraphLexer.h"
#include <iostream>
#include <string>
#include <cassert>
#include <vector>

int main(int argc, char ** argv)
{
    TreeNode<int,int> root(1, 3);
    TreeNode<int,int> a(2,3, &root);
    TreeNode<int,int> b(3,3, &root);
    TreeNode<int,int> c(5,17,&a);

    std::vector<TreeNode<int,int> *> roots = std::vector<TreeNode<int,int> *>();
    roots.push_back(&root);

    LinkCutTree<int> lkt = LinkCutTree<int>(roots);
    lkt.access(lkt.getSplayNode(c.key));
    
}

// int main(int argc, char ** argv) 
// {
//     if(argc < 2) {
//         std::cout << "usage: ./ShannonSwitching <short | cut> < <filename>" << std::endl;
//         return 0;
//     }
//     std::string mode = argv[1];
//     
//     assert(mode == "short" || mode == "cut");
// 
//     AdjacencyLists<int,int> graph = AdjacencyLists<int,int>(true, true);
// 
//     GraphLexer<int,int> lexer = GraphLexer<int,int>(graph);
// 
//     std::cin >> lexer;
//     
//     std::pair<int,int> leastEdge(0,0); // <cost,order>
//     for(auto edge : graph.getEdges()) 
//     {
//         if( !edge.second.isProtected
//             && (leastEdge.first == 0 
//             || (edge.second.cost > 0 
//                 && edge.second.cost < leastEdge.first))) 
//         {
//             leastEdge.first = edge.second.cost;
//             leastEdge.second = edge.second.order;
//         }
//     }
//     std::cout << "Selected Edge: " << leastEdge.second << " Cost: " << leastEdge.first << "\n";
// }