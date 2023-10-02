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
#include <algorithm>

#include "btree_utils.hpp"

template<class T>
int compute_height (typename BTree<T>::Ref t)
{
    assert(t != nullptr);
    int height = 0;
    //TODO
    height = -1;
    if(!t->is_empty()){
        int h_left = -1, h_right = -1;
        h_left = compute_height<T>(t->left());
        h_right = compute_height<T>(t->right());
        height = std::max(h_left,h_right)+1;
    }
    //
    return height;
}

template<class T>
size_t compute_size (typename BTree<T>::Ref t)
{
    assert(t != nullptr);
    size_t ret_val = 0;
    //TODO
    //Hint: when you call a template into other template maybe you need
    // to specialize the call.
    if(!t->is_empty()){
        ret_val = (compute_size<T>(t->left()) + compute_size<T>(t->right()))+1;
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
    //TODO
    //Hint: when you call a template into other template maybe you need
    // to specialize the call.
    if(not tree->is_empty())
    {
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
    //TODO
    //Hint: when you call a template into other template maybe you need
    // to specialize the call.
    if(not tree->is_empty())
    {
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
    //TODO
    //Hint: when you call a template into other template maybe you need
    // to specialize the call.
    if(!tree->is_empty()){
        retVal = retVal and postfix_process<T>(tree->left(),p);
        retVal = retVal and postfix_process<T>(tree->right(),p);
        retVal = retVal and p(tree->item());
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
    //TODO
    //Hint: think about which data structure can help you to do this kind 
    //  of traversal.
    std::queue<typename BTree<T>::Ref > q;
    q.push(tree);
    while(!q.empty() and go_on == true){
        auto subtree = q.front();
        if(!subtree->is_empty()){
            q.push(subtree->left());
            q.push(subtree->right());
            go_on = go_on and p(subtree->item());
        }
        q.pop();
    }
    //
    return go_on;
}

template <class T>
std::ostream&
print_prefix(std::ostream& out, typename BTree<T>::Ref tree)
{
    //TODO
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
    //TODO
    //You must create a lambda function with a parameter to be printed and
    //  use an infix_process to process the tree with this lambda.
    //Remember: the lambda must return true.
    auto p = [&out](T data)
    {
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
    //TODO
    //You must create a lambda function with a parameter to be printed and
    //  use a postfix_process to process the tree with this lambda.
    //Remember: the lambda must return true.
    auto p = [&out](T data)
    {
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
    //TODO
    //You must create a lambda function with a parameter to be printed and
    //  use a breadth_first_process to process the tree with this lambda.
    //Remember: the lambda must return true.
    auto p = [&out](T data)
    {
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
    //TODO
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with the prefix_process.
    //Remember: Also, the lambda must update the count variable and
    //must return True/False.
    auto p =[&it,&count](T data)
    {
        count++;
        return data!=it;
    };
    found = not prefix_process<T>(tree,p);
    //
    return found;
}

template <class T>
bool search_infix(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //TODO
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with the infix_process.
    //Remember: Also, the lambda must update the count variable and
    //must return True/False.
    auto p = [&it,&count](T data){
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
    //TODO
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with the postfix_process.
    //Remember: Also, the lambda must update the count variable and
    //must return True/False.
    auto p =[&it,&count](T data)
    {
        count++;
        return data!=it;
    };
    found = not postfix_process<T>(tree,p);
    //
    return found;
}

template <class T>
bool search_breadth_first(typename BTree<T>::Ref tree, const T& it, size_t& count)
{
    bool found = false;
    count = 0;
    //TODO
    //You must create a lambda function with a parameter to compare it to the
    // value of the element to be searched for.
    // Use the lambda with the breadth_first_process.
    //Remember: Also, the lambda must update the count variable and
    //must return True/False.
    auto p =[&it,&count](T data)
    {
        count++;
        return data!=it;
    };
    found = not breadth_first_process<T>(tree,p);
    //
    return found;
}


template<class T>
bool check_btree_in_order(typename BTree<T>::Ref const& tree)
{
    bool ret_val = true;
    //TODO
    //Hint: You can create a lambda function with a parameter to compare it with
    // the last the value seen.
    // Use the lambda with the infix_process.
    if(tree->is_empty()){
        return true;
    }else{

        auto left_subtree = tree->left();
        if(!left_subtree->is_empty()){

            auto max = tree->item();
            auto p = [&max](T data){
                return data < max;
            };
            bool check = breadth_first_process<T>(left_subtree,p);
            if(check == false){
                return false;
            }
            ret_val = ret_val and check_btree_in_order<T>(left_subtree);

        }

        auto right_subtree = tree->right();
        if(!right_subtree->is_empty()){

            auto min = tree->item();
            auto p = [&min](T data){
                return data > min;
            };
            bool check = breadth_first_process<T>(right_subtree,p);
            if(check == false){
                return false;
            }
            ret_val = ret_val and check_btree_in_order<T>(right_subtree);

        }

    }
    //
    return ret_val;
}

template<class T>
bool has_in_order(typename BTree<T>::Ref tree, T const& v)
{
    assert(check_btree_in_order<T>(tree));    
    bool ret_val = false;
    //TODO
    if(tree->is_empty()){
        return false;
    }else{
        if(v < tree->item()){
            auto subtree_left = tree->left();
            if(!subtree_left->is_empty()){
                ret_val = has_in_order<T>(subtree_left,v);
            }
        }else if(v > tree->item()){
            auto subtree_right = tree->right();
            if(!subtree_right->is_empty()){
                ret_val = has_in_order<T>(subtree_right,v);
            }
        }else{
            return true;
        }
    }
    //
    return ret_val;
}

template <class T>
void insert_in_order(typename BTree<T>::Ref tree, T const& v)
{
    assert(check_btree_in_order<T>(tree));
    //TODO
    if(tree->is_empty()){
        tree->create_root(v);
    }else{
        if(v < tree->item()){
            if(tree->left()->is_empty()){
                auto left_subtree = BTree<T>::create();
                left_subtree->create_root(v);                               
                tree->set_left(left_subtree);
            }else{
                auto aux = tree->left();
                insert_in_order<T>(aux,v);
                tree->set_left(aux);
            }
        }else if(v > tree->item()){
            if(tree->right()->is_empty()){
                auto right_subtree = BTree<T>::create();
                right_subtree->create_root(v);                               
                tree->set_right(right_subtree);
            }else{
                auto aux = tree->right();
                insert_in_order<T>(aux,v);
                tree->set_right(aux);
            }
        }
    }
    //
    assert(has_in_order<T>(tree, v));
}
