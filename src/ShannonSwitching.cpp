#include "Graphs/Headers/AdjacencyLists.h"
#include "Graphs/Headers/Graph.h"
#include "Headers/GraphLexer.h"
#include <iostream>
#include <string>
#include <cassert>

int main(int argc, char ** argv) 
{
    if(argc < 2) {
        std::cout << "usage: ./ShannonSwitching <short | cut> < <filename>" << std::endl;
        return 0;
    }
    std::string mode = argv[1];
    
    assert(mode == "short" || mode == "cut");

    AdjacencyLists<int,int> graph = AdjacencyLists<int,int>(true, true);

    GraphLexer<int,int> lexer = GraphLexer<int,int>(graph);

    std::cin >> lexer;
    
    std::pair<int,int> leastEdge(0,0); // <cost,order>
    for(auto edge : graph.getEdges()) 
    {
        if( !edge.second.isProtected
            && (leastEdge.first == 0 
            || (edge.second.cost > 0 
                && edge.second.cost < leastEdge.first))) 
        {
            leastEdge.first = edge.second.cost;
            leastEdge.second = edge.second.order;
        }
    }
    std::cout << "Selected Edge: " << leastEdge.second << " Cost: " << leastEdge.first << "\n";
}