#include <vector>
#include <list>
#include <map>
#include <queue>
#include <iostream>
#include <set>

template <typename V, typename E>
struct EdgeList {
     /*
     Edge list representation of a graph
     */
    std::vector<Edge<V,E>> members;

    EdgeList() {
        members = std::vector<Edge<V,E>>();
    }

    void insert(Edge<V,E> edge) {
        members.push_back(edge);
        int start = members.size()-1;
        while(start > 0 && edge.order < members[start-1].order) {
            members[start] = members[start-1];
            members[start-1] = edge;
            start--;
        }
    }
    bool operator<(const EdgeList<V,E> & other) const {
        for(int i = 0; i < std::min(members.size(), other.members.size()); i++) {
            if(members[i].order != other.members[i].order)
                return members[i].order < other.members[i].order;
        }
        if(other.members.size() > members.size())
            return true;
        return false;
    }
    bool operator==(const EdgeList<V,E> & other) {
        if(other.members.size() != members.size())
            return false;
        for(int i = 0; i < members.size(); i++) {
            if(members[i].order != other.members[i].order)
                return false;
        }
        return true;
    }

    void print() const {
        for(auto edge : members) {
            std::cout << edge.edge.first << " " << edge.edge.second << " " << edge.order << " " << edge.cost << std::endl;
        }
    }
};