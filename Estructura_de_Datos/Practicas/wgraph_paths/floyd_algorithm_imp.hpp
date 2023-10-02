/**
 * @file floyd_algorithm_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <utility>
#include <stack>
#include "floyd_algorithm.hpp"

#ifdef __VERBOSE__
#include <iostream>
#include <iomanip>
extern int Verbose_level;
#endif

template<class T>
void floyd_algorithm(const typename WGraph<T>::Ref g, FMatrix::Ref& D,
                     IMatrix::Ref& I)
{
    D = g->weight_matrix();
    I = IMatrix::create(g->size(), g->size(), -1);

    //TODO (done): Codify the Floyd algorithm.
    for(size_t x = 0; x < g -> size(); x++){

        for(size_t y = 0; y < g -> size(); y++){

            for(size_t z = 0; z < g -> size(); z++){

                if(D->get(y,z) > D->get(y,x)+D->get(x,z)){

                    D->set(y,z,D->get(y,x)+D->get(x,z));
                    I->set(y,z,x);

                }

            }

        }

    }
    
    //
}

void pathing(size_t u, size_t v, IMatrix::Ref I, std::list<size_t> & path){
    int aux = I->get(u,v);
    if (aux != -1){
        pathing(u, aux, I, path); 
        pathing(aux, v, I, path); 
    }else{ 
        path.push_back(u); 
    }
}

std::list<size_t> floyd_path(size_t src, size_t dst, IMatrix::Ref I)
{
    //Prec: distance (u,v) < inf
    std::list<size_t> path;

    //TODO (done): Find the path. 
    //Hint: Think first. Is it necessary to build a binary tree? or it
    //is enough to do an first-depth search using an iterative approach with
    //a stack of pairs (u,v).
    path.resize(0);
    pathing(src,dst,I,path);
    path.push_back(dst);
    
    
    //
    return path;
}




