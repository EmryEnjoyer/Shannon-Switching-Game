#include "../Graphs/Headers/Graph.h"
#include <istream>
#include <string>

template<typename V, typename E>
class GraphLexer {
/**
 * This class acts as a wrapper around a graph to make reading in graphs easy.
*/
    Graph<V,E> * graph;
    std::map<std::pair<V,V>,int> edgeIndices;

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

    int getEdgeIndex(V src, V dst)
    {
        std::cout << "source: " << src << " destination: " << dst << std::endl;
        return edgeIndices[std::pair(src,dst)];
    }

    void setEdgeIndex(std::pair<V,V> edge, int index)
    {
        edgeIndices[edge] = index;
        edgeIndices[std::pair(edge.second, edge.first)] = index;
    }
};

template<typename V, typename E>
std::istream & operator>>(std::istream & in, GraphLexer<V,E> & lexer) 
{
    int trash, numProtectedEdges, numUnprotectedEdges;

    in >> trash >> numProtectedEdges;
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
        lexer.setEdgeIndex(std::pair(src, dst), i);
        lexer.HandleEdge(src, dst, cost, false);
    }
    return in;
}