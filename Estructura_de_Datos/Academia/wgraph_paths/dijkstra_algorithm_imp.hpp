/**
 * @file dijkstra_algorithm_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once
#include <cassert>
#include <tuple>
#include <queue>
#include <limits>
#include <functional>

#include "dijkstra_algorithm.hpp"


template<class T>
void dijkstra_algorithm(typename WGraph<T>::Ref g,
                        std::vector<size_t>& predecessors,
                        std::vector<float>& distances)
{
    assert(g->has_current_node());

    //TODO
    //Hint: initialize distances with inf.
    //Hint: Initialize the vector of predecessors so that each vertex is a
    //      predecessor of itself.
    //Hint: use the the template tuple para represent edges. Set the fields so
    //      the tuples will be sorted properly.
    //      @see: https://en.cppreference.com/w/cpp/utility/tuple
    // Hint: you can use the keyword "using" to create an alias "Tuple"
    predecessors = std::vector<size_t>();
    distances = std::vector<float>(g->size(), std::numeric_limits<float>::infinity());

    for(size_t i = 0; i < g->size(); i++){
        predecessors.push_back(i);
    }

    std::priority_queue<std::tuple<float,size_t,size_t>,
                        std::vector<std::tuple<float,size_t,size_t>>,
                        std::greater<std::tuple<float,size_t,size_t>>> q;
    std::tuple<float,size_t,size_t> t;
    typename WNode<T>::Ref u, v, p;

    typename WNode<T>::Ref start = g->current_node();

    q.push(std::make_tuple(0.0, start->label(), start->label()));

    while(!q.empty()){
        t = q.top();
        u = g->node(std::get<1>(t));

        if(!g->node(u->label())->is_visited()){
            predecessors[u->label()] = std::get<2>(t);
            distances[u->label()] = std::get<0>(t);
            u->set_visited(true);
            g->goto_node(u);

            while(g->has_current_edge()){
                v = g->current_edge()->other(u);

                if(!g->node(v->label())->is_visited()){
                    q.push(std::make_tuple(distances[u->label()]+g->current_weight(), v->label(), u->label()));
                }

                g->goto_next_edge();
            }


        }

        q.pop();

    }

    //
}


inline std::list<size_t>
dijkstra_path(size_t src, size_t dst,
              std::vector<size_t>const& predecessors)
{
    assert(src<predecessors.size());
    assert(dst<predecessors.size());
    assert(predecessors[src]==src);
    std::list<size_t> path;
    //TODO

    size_t aux = dst;

    path.push_front(aux);

    while(predecessors[aux] != aux){

        aux = predecessors[aux];

        path.push_front(aux);

    }
    
    //
    return path;
}

