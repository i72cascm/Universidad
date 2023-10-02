/**
 * @file trie_node.cpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */

#include <cassert>
#include <sstream>
#include <cstdint>

#include "trie_node.hpp"

TrieNode::TrieNode (bool is_key_state)
{
    //TODO (done)
    isKey_ = is_key_state;
    //
    assert(is_key()==is_key_state);
    assert(!current_exists());
};

TrieNode::Ref TrieNode::create(bool is_key_state)
{
    return std::make_shared<TrieNode>(is_key_state);
}

TrieNode::~TrieNode()
{}

bool TrieNode::is_key() const
{
    bool ret_val = true;
    //TODO (done)
    ret_val = isKey_;
    //
    return ret_val;
}

bool
TrieNode::has(char k) const
{
    bool ret_v = false;
    //TODO (done)
    auto it = dict_.find(k);
    if (it == dict_.end())
    {
        ret_v = false;
    }else{
        ret_v = true;
    }
    //
    return ret_v;
}

TrieNode::Ref
TrieNode::child(char k) const
{
    assert(has(k));
    TrieNode::Ref node = nullptr;
    //TODO (done)
    auto value = dict_;

    node = value[k];
    //
    return node;
}

bool
TrieNode::current_exists() const
{
    bool ret_val = true;
    //TODO (done)
    bool aux;
    if (curr_ != nullptr){

        for(auto i = dict_.begin(); i != dict_.end(); i++){
            
            if(i->second == curr_){
                aux = true;
            }

        }

    }else{

        aux = false;
    }
    ret_val = aux;
    //
    return ret_val;
}

TrieNode::Ref
TrieNode::current_node() const
{
    assert(current_exists());
    TrieNode::Ref node = nullptr;
    //TODO (done)
    node = curr_;
    //
    return node;
}

char
TrieNode::current_symbol() const
{
    assert(current_exists());
    char symbol = 0;
    //TODO (done)
    for (auto i = dict_.begin(); i != dict_.end(); i++){
        
        if (i->second == curr_){
            symbol = i->first;
        }

    }
    //
    return symbol;
}

void
TrieNode::set_is_key_state(bool new_state)
{
    //TODO (done)
    isKey_ = new_state;
    //
    assert(is_key()==new_state);
}

bool
TrieNode::find_child(char s)
{
    bool found = false;
    //TODO (done)
    auto value = dict_.find(s);
    if(value == dict_.end()){
        found = false;
        curr_ = nullptr;
    }else{
        found = true;
        curr_ = value->second;
    }
    //
    assert(found || !current_exists());
    assert(!found || current_symbol()==s);
    return found;
}

void
TrieNode::goto_first_child()
{
    //TODO (done)
    curr_ = dict_.begin()->second;
    //
}

void
TrieNode::goto_next_child()
{
    assert(current_exists());
    //TODO (done)
    for (auto i = dict_.begin(); i != dict_.end(); i++){

        if (i->second == curr_){
            i++;
            if (i != dict_.end()){
                curr_ = i->second;
                
            }else{

                curr_ = nullptr;
            }

        }

    }
    //
}

void
TrieNode::set_child(char k, Ref node)
{
    assert(node != nullptr);
    //TODO  (done)
    dict_[k] = node;
    curr_ = node;
    //
    assert(current_symbol()==k);
    assert(current_node()==node);
}

std::ostream&
TrieNode::fold(std::ostream& out) const
{
    //TODO (done)
    //Hint: review c++ input/output manipulators at
    //      https://en.cppreference.com/w/cpp/io/manip
    out << "[";
    out << " ";
    if (!is_key()){
        out << "F";
    }else{
        out << "T";
    }

    for (auto i = dict_.begin(); i != dict_.end(); i++){

        out << " " << std::hex << (uint16_t)i->first << " ";

        i->second->fold(out);
    }
    out << " ";
    out << "]";
    //
    return out;
}

TrieNode::Ref TrieNode::create(std::istream& in) noexcept(false)
{
    TrieNode::Ref node = nullptr;
    //TODO (done)
    std::string aux;
    in >> aux;
    if (aux != "["){
        throw std::runtime_error("Wrong input format");
    }

    in >> aux;
    if (aux == "F"){
        node = TrieNode::create(false);
    }else if(aux == "T"){
        node = TrieNode::create(true);
    }else{
        throw std::runtime_error("Wrong input format");
    }

    while(in >> aux && aux != "]") {
        node->set_child(char(std::stoi(aux,nullptr,16)),TrieNode::create(in));
    }

    if(aux != "]"){
        throw std::runtime_error("Wrong input format");
    }
    //
    return node;
}
