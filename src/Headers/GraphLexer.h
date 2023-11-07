#include "../Graphs/Headers/Graph.h"
#include <istream>
#include <string>

template<typename V, typename E>
class GraphLexer {
/**
 * This class acts as a wrapper around a graph to make reading in graphs easy.
*/
    Graph<V,E> * graph;

public:
    GraphLexer(Graph<V,E> & graph) 
    {
        this->graph = &graph;
    }

    void HandleEdge(V src, V dst, V cost, bool isProtected)
    {

            if(!graph->ContainsVertex(src))
                graph->AddVertex(src);
            if(!graph->ContainsVertex(dst))
                graph->AddVertex(dst);
            graph->AddEdge(src, dst, isProtected, cost);
    }

};

template<typename V, typename E>
std::istream & operator>>(std::istream & in, GraphLexer<V,E> & lexer) 
{
    int numProtectedEdges, numUnprotectedEdges;

    in >> numProtectedEdges;
    for(int i = 0; i < numProtectedEdges; ++i) 
    {
        V src, dst;
        E cost;
        in >> src >> dst >> cost;
        lexer.HandleEdge(src, dst, cost, true);
    }

    in >> numUnprotectedEdges;
    for(int i = 0; i < numUnprotectedEdges; ++i)
    {
        V src, dst;
        E cost;
        in >> src >> dst >> cost;
        lexer.HandleEdge(src, dst, cost, false);
    }
    return in;
}