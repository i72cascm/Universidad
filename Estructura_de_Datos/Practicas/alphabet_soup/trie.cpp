/**
 * @file trie.cpp
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
#include "trie.hpp"

Trie::Trie()
{
    //TODO (done)
    
    prefix_ = "";
    root_ = nullptr;

    //
    assert(is_empty());
}

Trie::Ref Trie::create()
{    
    return std::make_shared<Trie>();
}

Trie::Trie(TrieNode::Ref root_node, std::string const& pref)
{
    //TODO (done)
    
    prefix_ = pref;
    root_ = root_node;

    //
    assert(prefix() == pref);
}

Trie::Ref Trie::create(TrieNode::Ref root_node, std::string const& prefix)
{
    //We cannot use std::make_shared here
    //because the constructor is protected.
    typename Trie::Ref trie ( new Trie(root_node, prefix));
    return trie;
}

Trie::Ref Trie::create(std::istream& in) noexcept(false)
{
    Trie::Ref trie = nullptr;
    //TODO


    //
    return trie;
}

bool
Trie::is_empty() const
{
    bool ret_v=true;
    //TODO (done)
    if(root_ == nullptr){
        ret_v = true;
    }else{
        ret_v = false;
    }
    //
    return ret_v;
}

std::string
Trie::prefix() const
{
    std::string ret_val = "";
    //TODO (done)
    ret_val = prefix_;
    //
    return ret_val;
}

bool
Trie::is_key() const
{
    assert(!is_empty());
    bool ret_val = true;
    //TODO (done)
    ret_val = root_->is_key();
    //
    return ret_val;
}


TrieNode::Ref
Trie::root() const
{
    TrieNode::Ref node = nullptr;
    //TODO (done)
    node = root_;
    //
    return node;
}

bool
Trie::has(std::string const& k) const
{
    assert(!is_empty());
    bool found = false;
    //TODO (done)
    //Hint: use find_node() to do this.
    //Remember: The Trie can have a prefix==k but does not store the key k.    
    auto aux = find_node(k);
    if(aux != nullptr and aux->is_key()){
        found = true;
    }
    //
    return found;
}

static void
preorder_traversal(TrieNode::Ref node, std::string prefix,
                   std::vector<std::string> & keys)
{
    //TODO (done)
    //Remember: node->is_key() means the prefix is a key too.
    if(node->is_key()){
        keys.push_back(prefix);
    }

    node->goto_first_child();

    while(node->current_exists()){
        preorder_traversal(node->current_node(), prefix + node->current_symbol(), keys);
        
        node->goto_next_child();
    }
    //
}


void
Trie::retrieve(std::vector<std::string>& keys) const
{
    assert(!is_empty());
    //TODO (done)
    //Remember add the subtrie's prefix to the retrieve keys.
    preorder_traversal(root_, prefix(), keys);
    //
}

Trie::Ref
Trie::child(std::string const& pref) const
{
    assert(!is_empty());
    Trie::Ref ret_v = Trie::create();
    //TODO (done)
    //Hint: use find_node() to do this.
    auto aux = root_;

    for(auto i : pref){
        if(!aux->find_child(i)){
            return ret_v;
        }
        aux = aux->child(i);
    }

    ret_v->root_ = aux;
    ret_v->prefix_ = prefix_ + pref;
    //
    assert(ret_v != nullptr);
    return ret_v;
}

bool
Trie::current_exists() const
{
    assert(!is_empty());
    bool ret_val = false;
    //TODO (done)
    ret_val = root_->current_exists();
    //
    return ret_val;
}

Trie::Ref
Trie::current() const
{
    assert(current_exists());
    Trie::Ref trie = nullptr;
    //TODO (done)
    trie = create(root_->current_node(), prefix_ + current_symbol());
    //
    return trie;
}

char
Trie::current_symbol() const
{
    assert(current_exists());
    char symbol = 0;
    //TODO (done)
    if(root_->current_exists()){
        symbol = root_->current_symbol();
    }
    //
    return symbol;
}

void
Trie::insert(std::string const& k)
{
    assert(k != "");
    //TODO (done)
    if(root_ == nullptr){
        root_ = TrieNode::create(false);
    }else{}

    auto aux = root_;

    for(size_t i = 0; i < k.size(); i++){
        if (aux->has(k[i])){
            aux = aux->child(k[i]);
        }else{
            auto node = TrieNode::create(false);
            aux->set_child(k[i], node);
            aux = node;
        }
    }
    aux->set_is_key_state(true);
    //
    assert(!is_empty());
    assert(has(k));
}

TrieNode::Ref
Trie::find_node(std::string const& pref) const
{
    assert(!is_empty());
    TrieNode::Ref node;
    //TODO (done)
    //Remember: the prefix "" must return the trie's root node.
    node = root_;
    size_t i = 0;
    while (node != nullptr && i < pref.size()){
        if (!node->has(pref[i])){
            node = nullptr;
        }else{
            node = node->child(pref[i]);
            i++;
        }
    }
    //
    return node;
}

std::ostream&
Trie::fold(std::ostream& out) const
{
    //TODO



    //
    return out;
}

bool
Trie::find_symbol(char symbol)
{
    assert(!is_empty());
    bool found = false;
    //TODO (done)
    found = root_->find_child(symbol);
    //
    assert(!found || current_exists());
    assert(found || !current_exists());
    assert(!current_exists() || current_symbol()==symbol);
    return found;
}

void
Trie::goto_first_symbol()
{
    assert(!is_empty());
    //TODO (done)
    root_->goto_first_child();
    //
    assert(!current_exists() ||
           current()->prefix()==prefix()+current_symbol());
}

void
Trie::goto_next_symbol()
{
    assert(current_exists());
    //TODO (done)
    root_->goto_next_child();
    //
}
