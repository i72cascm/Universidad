/**
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once


#include <sstream>
#include <stdexcept>
#include <cassert>

#include "slist.hpp"

template <class T>
SNode<T>::SNode (T const& it)
{
    //TODO (done)
    _item = it;
    _next = nullptr;
    //
    assert(!has_next());
}

template <class T>
SNode<T>::SNode (T const& it, SNode<T>::Ref& next)
{
    //TODO (done)
    _item = it;
    _next = next;
    //
}

template <class T>
SNode<T>::~SNode()
{
    //TODO (done)
    //hint: if std::shared_ptr is used for the references, nothing todo.

    //
}

template <class T>
typename SNode<T>::Ref SNode<T>::create(T const& it, SNode<T>::Ref next)
{
    return std::make_shared<SNode<T>> (it, next);
}

template <class T>
T SNode<T>::item() const
{
    T it;
    //TODO (done)
    it = _item;
    //
    return it;
}

template <class T>
bool SNode<T>::has_next() const
{
    bool has = false;
    //TODO (done)
    if(_next != nullptr){
        has = true;
    }
    //
    return has;
}

template <class T>
typename SNode<T>::Ref SNode<T>::next() const
{
    SNode<T>::Ref n;
    //TODO (done)
    n = _next;
    //
    return n;
}

template <class T>
void SNode<T>::set_item(const T& new_it)
{
    //TODO (done)
    _item = new_it;
    //
    assert(item()==new_it);
}

template <class T>
void SNode<T>::set_next(SNode<T>::Ref n)
{
    //TODO (done)
    _next = n;
    //
    assert(n == next());
}

template<class T>
SList<T>::SList ()
{
    //TODO (done)
    _size = 0;
    _head = nullptr;
    _current = nullptr;
    //
    assert(is_empty());
}

template<class T>
SList<T>::~SList()
{
    //TODO (done)

    //punteros inteligentes se borran solos

    //

}

template<class T>
typename SNode<T>::Ref SList<T>::head() const
{
    typename SNode<T>::Ref h;
    //TODO (done)
    h = _head;
    //
    return h;
}

template<class T>
typename SList<T>::Ref SList<T>::create()
{
    return std::make_shared<SList<T>> ();
}

template<class T>
typename SList<T>::Ref SList<T>::create(std::istream& in) noexcept(false)
{
    auto list = SList<T>::create();
    std::string token;
    in >> token;

    //TODO
    //Hint: use std::istringstream to convert from "string" to template
    // parameter T type.
    // Throw std::runtime_error("Wrong input format.") exception when an input
    // format error was found.

    if(token == "[]"){
        return list;
    }else if(token == "]"){
        throw std::runtime_error("Wrong input format.");
    }
    else if(token == "["){
        while(in >> token and token != "]"){
            std::istringstream convert(token);
            T new_item;
            convert >> new_item;
            for (size_t i = 0; i < token.size(); i++){
                if (not std::isdigit(token[i])){
                    throw std::runtime_error("Wrong input format.");
                    return list;
                }
            }
            if(list->is_empty()){
                list->insert(new_item);
            }
            else{
                if(list->has_next()){
                    list->goto_next();
                }
                list->insert(new_item);
            }
        }

        if(token != "]"){
            throw std::runtime_error("Wrong input format.");
        }
    }
    else{
        throw std::runtime_error("Wrong input format.");
    }
    //
    return list;
}

template<class T>
bool SList<T>::is_empty () const
{
    bool ret_val = true;
    //TODO (done)
    if (size() != 0){
        ret_val = false;
    }
    //
    return ret_val;
}

template<class T>
size_t SList<T>::size () const
{
    size_t ret_val = 0;
    //TODO (done)
    ret_val = _size;
    //
    return ret_val;
}

template<class T>
T SList<T>::front() const
{
    assert(!is_empty());
    T f;
    //TODO (done)
    f = _head->item();
    //
    return f;
}

template<class T>
T SList<T>::current() const
{    
    assert(! is_empty());
    T c;
    //TODO (done)
    c = _current->item();
    //
    return c;
}

template<class T>
bool SList<T>::has_next() const
{
    assert(!is_empty());
    bool ret_val = false;
    //TODO (done)
    if(_current->has_next()){
        ret_val = true;
    }
    //
    return ret_val;
}

template<class T>
T SList<T>::next() const
{
    assert(has_next());
    T ret_val = false;
    //TODO (done)
    ret_val = _current->next()->item();
    //
    return ret_val;
}


template<class T>
bool SList<T>::has(T const& it) const
{
    bool found = false;
    //TODO (done)
    //Hint: you can reuse SList::find() but you must remember to restore 
    // the old the cursor position. In this way we assure not modify the state of the list.
    //Hint: use const_cast<> to remove constness of this.
    typename SNode<T>::Ref aux = _head;

    if(aux->item() == it){
        found = true;
    }
    while(aux->has_next()){
        aux = aux->next();
        if(aux->item()==it){
            found = true;
        }
    }
    //
    return found;
}

template<class T>
void SList<T>::fold(std::ostream& out) const
{
    //TODO (done)
    auto aux = _head;
    if(!is_empty()){
        out << "[ ";
        while(aux != nullptr){
            out << aux->item();
            out << " ";
            aux = aux->next();
        }
        out << "]";
    }else{
        out << "[]";
    }
    //
}

template<class T>
void SList<T>::set_current(T const& new_v)
{
    assert(!is_empty());
    //TODO (done)
    _current->set_item(new_v);
    //
    assert(current()==new_v);
}


template<class T>
void SList<T>::push_front(T const& new_it)
{
#ifndef NDEBUG
    size_t old_size = size();
#endif
    //TODO (done)
    //Remeber to update current if current is in the head.
    typename SNode<T>::Ref aux;

    if(!is_empty()){
        aux = SNode<T>::create(new_it, _head);
    }else{
        aux = SNode<T>::create(new_it);
    }

    _size++;
    _head = aux;
    _current = _head;
    //
    assert(front()==new_it);
    assert(size() == (old_size+1));
}

template<class T>
void SList<T>::insert(T const& new_it)
{
#ifndef NDEBUG
    bool old_is_empty = is_empty();
    size_t old_size = size();
    T old_item;
    if (!old_is_empty)
        old_item = current();
#endif
    //TODO (done)
    if(is_empty()){
        push_front(new_it);
    }
    else if(!is_empty()){
        typename SNode<T>::Ref aux = SNode<T>::create(new_it, _current->next());
        _current->set_next(aux);
        _size++;
    }
    //
    assert(!old_is_empty || (front()==new_it && current()==new_it));
    assert(old_is_empty || (old_item == current() && has_next() && next()==new_it));
    assert(size()==(old_size+1));
}

template<class T>
void SList<T>::pop_front()
{
    assert(!is_empty());
#ifndef NDEBUG
    size_t old_size = size();
    auto old_head_next = head()->next();
#endif
    //TODO (done)
    _head = _head->next();
    _size--;
    //
    assert(is_empty() || head() == old_head_next);
    assert(size() == (old_size-1));
}


template<class T>
void SList<T>::remove()
{
    assert(!is_empty());
#ifndef NDEBUG
    size_t old_size = size();
    bool old_has_next = has_next();
    T old_next;
    if (has_next())
        old_next=next();
#endif
    //TODO (done)
    //Case 1: current is the head.

    if(_current == _head){
        _head = _head->next();
        _current = _head;
        _size--;
    }

    //Case 2: remove in a middle position.

    if(_current->next() != nullptr && _current != _head){
        auto _previous = _head;
        while (_previous->next() != _current){
            _previous = _previous->next();
        }
        _previous->set_next(_current->next());
        _current = _previous->next();
        _size--;
    }

    //Case 3: remove the last element.
    //Remenber to locate previous of prev_.

    if(_current->next() == nullptr && _current != _head){
        auto _previous  = _head;
        while (_previous->next() != _current){
            _previous = _previous->next();
        }
        _previous->set_next(nullptr);
        _current = _previous;
        _size--;
    }

    //
    assert(!old_has_next || current()==old_next);
    assert(size() == (old_size-1));
}

template<class T>
void SList<T>::goto_next()
{
    assert(has_next());
#ifndef NDEBUG
    auto old_next = next();
#endif
    //TODO (done)
    _current = _current->next();
    //
    assert(current()==old_next);
}

template<class T>
void SList<T>::goto_first()
{
    assert(!is_empty());
    //TODO (done)
    _current = _head;
    //
    assert(current()==front());
}

template<class T>
bool SList<T>::find(T const& it)
{
    assert(!is_empty());
    bool found = false;
    //TODO (done)
    auto _previous = _head;
    _current = _head;

    while (_current != nullptr and current() != it){
        _previous = _current;
        _current = _current->next();
    }

    if (_current != nullptr){
        found = true;
    }else{
        _current = _previous;
    }
    //
    assert(!found || current()==it);
    assert(found || !has_next());
    return found;
}

template<class T>
bool SList<T>::find_next(T const& it)
{
    assert(has_next());
    bool found = false;
    //TODO (done)
    goto_next();

    while(_current != nullptr && _current->item() != it){
        _current = _current->next();
    }

    if(_current != nullptr){
        found = true;
    }
    //
    assert(!found || current()==it);
    assert(found || !has_next());
    return found;
}

