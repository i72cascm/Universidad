/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <cassert>
#include <exception>
#include <memory>
#include <iostream>
#include <queue>

#include "btree_utils.hpp"

template<class T>
int compute_height (typename BTree<T>::Ref t)
{
    assert(t != nullptr);
    int height = 0;
    //TODO (done)
    if(t->is_empty()){
        height = -1;
    }else{
        int altura_izq = -1, altura_der = -1;
        auto arbol_izq = t->left();
        auto arbol_der = t->right();
        //Calculo la altura izq
        if(!arbol_izq->is_empty()){
            altura_izq = compute_height<T>(arbol_izq);
        }
        //Calculo la altura der
        if(!arbol_der->is_empty()){
            altura_der = compute_height<T>(arbol_der);
        }
        //Calculo el maximo
        if(altura_der > altura_izq){
            height = altura_der + 1;
        }else{
            height = altura_izq + 1;
        }
    }
    //
    return height;
}

template<class T>
size_t compute_size (typename BTree<T>::Ref t)
{
    assert(t != nullptr);
    size_t ret_val = 0;
    //TODO (done)
    //Hint: when you call a template into other template maybe you need
    // to specialize the call.
    
    if(!t->is_empty()){
        size_t tam_izq = compute_size<T>(t->left());
        size_t tam_drch =  compute_size<T>(t->right());
        ret_val = 1 + tam_drch + tam_izq;
    }
    //
    return ret_val;
}

template <class T, typename Processor>
bool
prefix_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool retVal = true;
    //TODO (done)
    //Hint: when you call a template into other template maybe you need
    // to specialize the call.
    if(!tree->is_empty()){
        retVal = retVal && p(tree->item());
        retVal = retVal && prefix_process<T>(tree->left(),p);
        retVal = retVal && prefix_process<T>(tree->right(),p);
    }
    //
    return retVal;
}

template <class T, class Processor>
bool
infix_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool retVal = true;
    //TODO (done)
    //Hint: when you call a template into other template maybe you need
    // to specialize the call.
    if(!tree->is_empty()){
        retVal = retVal && infix_process<T>(tree->left(),p);
        retVal = retVal && p(tree->item());
        retVal = retVal && infix_process<T>(tree->right(),p);
    }
    //
    return retVal;
}

template <class T, class Processor>
bool
postfix_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool retVal = true;
    //TODO (done)
    //Hint: when you call a template into other template maybe you need
    // to specialize the call.
    if(!tree->is_empty()){
        retVal = retVal && postfix_process<T>(tree->left(),p);
        retVal = retVal && postfix_process<T>(tree->right(),p);
        retVal = retVal && p(tree->item());
    }
    //
    return retVal;
}


template <class T, class Processor>
bool
breadth_first_process(typename BTree<T>::Ref tree, Processor& p)
{
    assert(tree != nullptr);
    bool go_on = true;
    //TODO (done)
    //Hint: think about which data structure can help you to do this kind 
    //  of traversal.
    std::queue< typename BTree<T>::Ref > queue;
    queue.push(tree);
    while(go_on==true && !queue.empty()){
        auto sub = queue.front();
        if(!sub->is_empty()){
            queue.push(sub->left());
            queue.push(sub->right());
            go_on = p(sub->item()) && go_on;
        }
        queue.pop();
    }
    //
    return go_on;
}

template <class T>
std::ostream&
print_prefix(std::ostream& out, typename BTree<T>::Ref tree)
{
    //TODO (done)
    //You must create a lambda function with a parameter to be printed and
    //  use a prefix_process to process the tree with this lambda.
    //Remember: the lambda must return true.
    auto p = [&out](T data){
        out << data << " ";
        return true;
    };
    prefix_process<T>(tree,p);
    //
    return out;
}

template <class T>
std::ostream&
print_infix(std::ostream& out, typename BTree<T>::Ref tree)
{
    //TODO (done)
    //You must create a lambda function with a parameter to be printed and
    //  use an infix_process to process the tree with this lambda.
    //Remember: the lambda must return true.
    auto p = [&out](T data){
        out << data << " ";
        return true;
    };
    infix_process<T>(tree,p);
    //
    return out;
}

template <class T>
std::ostream&
print_postfix(std::ostream& out, typename BTree<T>::Ref tree)
{
    //TODO (done)
    //You must create a lambda function with a parameter to be printed and
    //  use a postfix_process to process the tree with this lambda.
    //Remember: the lambda must return true.
    auto p = [&out](T data){
        out << data << " ";
        return true;
    };
    postfix_process<T>(tree,p);
    //
    return out;
}

template <class T>
std::ostream&
print_breadth_first(std::ostream& out, typename BTree<T>::Ref tree)
{
    //TODO (done)
    //You must create a lambda function with a parameter to be printed and
    //  use a breadth_first_process to process the tree with this lambda.
    //Remember: the lambda must return true.
    auto p = [&out](T data){
        out << data << " ";
        return true;
    };
    breadth_first_process<T>(tree,p);
    //
    return out;
}

template <class T>
bool search_prefix(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //TODO (done)
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with the prefix_process.
    //Remember: Also, the lambda must update the count variable and
    //must return True/False.
    auto p = [it,&count](T data){
        count = count + 1;
        return data != it;
    };
    found = !prefix_process<T>(tree,p);
    //
    return found;
}

template <class T>
bool search_infix(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //TODO (done)
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with the infix_process.
    //Remember: Also, the lambda must update the count variable and
    //must return True/False.
    auto p = [it,&count](T data){
        count++;
        return data != it;
    };
    found = !infix_process<T>(tree,p);
    //
    return found;
}

template <class T>
bool search_postfix(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //TODO (done)
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with the postfix_process.
    //Remember: Also, the lambda must update the count variable and
    //must return True/False.
    auto p = [it,&count](T data){
        count++;
        return data != it;
    };
    found = !postfix_process<T>(tree,p);
    //
    return found;
}

template <class T>
bool search_breadth_first(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //TODO (done)
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with the breadth_first_process.
    //Remember: Also, the lambda must update the count variable and
    //must return True/False.
    auto p = [it,&count](T data){
        count++;
        return data != it;
    };
    found = !breadth_first_process<T>(tree,p);
    //
    return found;
}


template<class T>
bool check_btree_in_order(typename BTree<T>::Ref const& tree)
{
    bool ret_val = true;
    //TODO (done)
    //Hint: You can create a lambda function with a parameter to compare it with
    // the last the value seen.
    // Use the lambda with the infix_process.
    if(tree->is_empty()){ //Los arboles vacios y por ende las ramas vacias, estan ordenadas
        return true;
    }

    if(!tree->left()->is_empty()){
        T max = tree->item(); //guardo la variable en la que estoy para comparar
        auto p = [&max](T data_item){
            return data_item < max;
        };
        bool flag = infix_process<T>(tree->left(),p); 
        if(flag == false){
            return false;
        }
        ret_val = check_btree_in_order<T>(tree->left()) && ret_val;
    }

    if(!tree->right()->is_empty()){
        T min = tree->item();
        auto p = [&min](T data_item){
            return data_item > min;
        };
        bool flag = infix_process<T>(tree->right(),p); //infix
        if(flag == false){ //si ya sabemos que no esta en orden, podemos parar
            return false;
        }
        ret_val = check_btree_in_order<T>(tree->right()) && ret_val;
    }
    //
    return ret_val;
}

template<class T>
bool has_in_order(typename BTree<T>::Ref tree, T const& v)
{
    assert(check_btree_in_order<T>(tree));    
    bool ret_val = false;
    //TODO (done)
    if(tree->is_empty()){
        ret_val = false;
    }else{
        if(v < tree->item()){
            if(!tree->left()->is_empty()){
                ret_val = has_in_order<T>(tree->left(),v);
            }
        }else if(v > tree->item()){
            if(!tree->right()->is_empty()){
                ret_val = has_in_order<T>(tree->right(),v);
            }
        }else{
            ret_val = true;
        }
    }
    //
    return ret_val;
}

template <class T>
void insert_in_order(typename BTree<T>::Ref tree, T const& v)
{
    assert(check_btree_in_order<T>(tree));
    //TODO (done)
    if(tree->is_empty()){
        tree->create_root(v);
    }else if(v < tree->item()){
        if(tree->left()->is_empty()){
            auto left = BTree<T>::create();
            left->create_root(v);
            tree->set_left(left);  
        }else{
            insert_in_order<T>(tree->left(),v);
            tree->set_left(tree->left());
        }
    }else if(v > tree->item()){
        if(tree->right()->is_empty()){
            auto right = BTree<T>::create();
            right->create_root(v);
            tree->set_right(right); 
        }else{
            insert_in_order<T>(tree->right(),v);
            tree->set_right(tree->right());
        }
    }
    //
    assert(has_in_order<T>(tree, v));
}
