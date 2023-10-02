/**
 * @file rbtree_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once
#include <algorithm>
#include <cmath>
#include <cassert>
#include <limits>

#include "rbtree.hpp"

/****
 * RBTNode class implementation.
 ****/

template <class T>
RBTNode<T>::RBTNode(T const &it,
                    RBTNode<T>::Color c,
                    RBTNode<T>::Ref p,
                    RBTNode<T>::Ref l,
                    RBTNode<T>::Ref r)
{
    // TODO (done)
    color_ = c;
    parent_ = p;
    right_ = r;
    left_ = l;
    item_ = it;
    
    //
    assert(item() == it);
    assert(color() == c);
    assert(parent() == p);
    assert(left() == l);
    assert(right() == r);
}

template <class T>
typename RBTNode<T>::Ref RBTNode<T>::create(T const &it,
                                            RBTNode<T>::Color color,
                                            RBTNode<T>::Ref parent,
                                            RBTNode<T>::Ref left,
                                            RBTNode<T>::Ref right)
{
    auto ref = RBTNode<T>::Ref(new RBTNode<T>(it, color, parent, left, right));
    ref->this_ = ref;
    return ref;
}

template <class T>
RBTNode<T>::~RBTNode()
{
    // TODO (done)
    // Hint: Think, is it needed to do anything?.

    //
}

template <class T>
T RBTNode<T>::item() const
{
    T value;
    // TODO (done)
    value = item_;
    //
    return value;
}

template <class T>
typename RBTNode<T>::Ref RBTNode<T>::parent() const
{
    RBTNode<T>::Ref node;
    // TODO (done)
    node = parent_;
    //
    return node;
}

template <class T>
typename RBTNode<T>::Ref RBTNode<T>::left() const
{
    RBTNode<T>::Ref node;
    // TODO (done)
    node = left_;
    //
    return node;
}

template <class T>
typename RBTNode<T>::Ref RBTNode<T>::right() const
{
    RBTNode<T>::Ref node;
    // TODO (done)
    node = right_;
    //
    return node;
}

template <class T>
typename RBTNode<T>::Ref RBTNode<T>::child(int idx) const
{
    assert(idx == 0 || idx == 1);
    RBTNode<T>::Ref node;
    // TODO
    
    //
    assert(idx == 0 || node == right());
    assert(idx == 1 || node == left());
    return node;
}

template <class T>
typename RBTNode<T>::Color RBTNode<T>::color() const
{
    RBTNode<T>::Color color = BLACK;
    // TODO (done)
    color = color_;
    //
    return color;
}

template <class T>
const typename RBTNode<T>::Ref &RBTNode<T>::This() const
{
    return this_;
}

template <class T>
typename RBTNode<T>::Ref RBTNode<T>::This()
{
    return this_;
}

template <class T>
void RBTNode<T>::set_item(const T &new_it)
{
    // TODO (done)
    item_ = new_it;
    //
    assert(item() == new_it);
}

template <class T>
void RBTNode<T>::set_color(RBTNode<T>::Color new_color)
{
    // TODO (done)
    color_ = new_color;
    //
    assert(color() == new_color);
}

template <class T>
void RBTNode<T>::set_parent(RBTNode<T>::Ref new_parent)
{
    // TODO (done)
    parent_ = new_parent;
    //
    assert(parent() == new_parent);
}

template <class T>
void RBTNode<T>::set_left(Ref new_child)
{
    // TODO (done)
    // Remember to update the parent link of new_child too.
    left_ = new_child;

    if(new_child){
        new_child->set_parent(This());
    }
    //
    assert(left() == new_child);
    assert(!new_child || new_child->parent() == This());
}

template <class T>
void RBTNode<T>::set_right(RBTNode<T>::Ref new_child)
{
    // TODO (done)
    // Remember to update the parent link of new_child too.
    right_ = new_child;

    if(new_child){
        new_child->set_parent(This());
    }
    //
    assert(right() == new_child);
    assert(!new_child || new_child->parent() == This());
}

template <class T>
void RBTNode<T>::set_child(int idx, RBTNode<T>::Ref new_child)
{
    assert(idx == 0 || idx == 1);
    // TODO
    // Remember to update the parent link of new_child too.
    
    //
    assert(idx == 0 || new_child == right());
    assert(idx == 1 || new_child == left());
    assert(!new_child || new_child->parent() == This());
}

/***
 * RBTree class implementation.
 ***/

template <class T>
RBTree<T>::RBTree()
{
    // TODO (done)
    parent_ = nullptr;
    
    current_ = nullptr;
    root_ = nullptr;
    //
    assert(is_a_binary_search_tree());
    assert(is_a_rbtree());
    assert(is_empty());
}

template <class T>
RBTree<T>::RBTree(T const &item)
{
    // TODO (done)
    current_ = root_;

    parent_ = nullptr;

    root_ = RBTNode<T>::create(item, RBTNode<T>::RED);
    
    //
    assert(is_a_binary_search_tree());
    assert(is_a_rbtree());
    assert(!is_empty());
}

template <class T>
const typename RBTree<T>::Ref &RBTree<T>::This() const
{
    return this_;
}

template <class T>
typename RBTree<T>::Ref RBTree<T>::This()
{
    return this_;
}

template <class T>
typename RBTree<T>::Ref RBTree<T>::create()
{
    auto ref = Ref(new RBTree<T>());
    ref->this_ = ref;
    return ref;
}

template <class T>
typename RBTree<T>::Ref RBTree<T>::create(T const &item)
{
    auto ref = Ref(new RBTree<T>(item));
    ref->this_ = ref;
    return ref;
}

template <class T>
typename RBTree<T>::Ref RBTree<T>::create(std::istream &in) noexcept(false)
{
    auto tree = RBTree<T>::create();
    std::string token;
    // TODO (done)
    // Hint: use the recursive definition of a tree to unfold.
    
    in >> token;
    
    if(token == "["){
        T aux;
        in >> aux;
        in >> token;
        if(token == "N"){
            tree = RBTree<T>::create(RBTNode<T>::create(aux,RBTNode<T>::BLACK));
        }else{
            tree = RBTree<T>::create(RBTNode<T>::create(aux,RBTNode<T>::RED));
        }
        auto leftTree = RBTree<T>::create(in);
        auto rightTree = RBTree<T>::create(in);
        tree->set_left(leftTree);
        tree->set_right(rightTree);
        in >> token;
    }else if(token != "[]"){
        throw std::runtime_error("Wrong input format");
    }
    
    if(not in){
        throw std::runtime_error("Wrong input format");
    }

    //
    tree->this_ = tree;
    if (!tree->is_a_binary_search_tree())
        throw std::runtime_error("It is not a binary search tree");
    else if (!tree->is_a_rbtree())
        throw std::runtime_error("It is not an rbtree");
    return tree;
}

template <class T>
RBTree<T>::~RBTree()
{
    // TODO
    // Hint: Think, is it needed to do anything?.

    //
}
#ifdef __ONLY_BSTREE__
/**
 * @brief Create an perfectly balanced BSTree by inserting the median of
 *        an ordered sub sequence data[begin, end).
 * @param data is the ordered sequence of values.
 * @param begin,
 * @param end specify a [begin, end) indexing interval of array data to use.
 * @pre 0 <= begin <= end <=data.size()
 * @pre begin==end || data[begin]<data[end];
 */
template <class T>
void create_inserting_median(std::vector<T> const &data,
                             size_t begin,
                             size_t end,
                             typename RBTree<T>::Ref &tree)
{
    assert(begin <= end);
    assert(end <= data.size());
    assert(begin == end || data[begin] <= data[end - 1]);

    // TODO
    // Hint: if (end==begin) none thing must be done (it is an empty sub array)
    //  else, insert the median in the tree and (recursively) process
    //  the two sub sequences [begin, median_idx) and [median_idx+1, end)
    if ((end-begin) >= 1){
        tree->insert(data[begin+((end-begin)/2)]);
        create_inserting_median(data, begin, (((end-begin)/2)+begin),tree);
        create_inserting_median(data, (((end-begin)/2)+begin)+1,end,tree);
    }
    //
}

template <class T>
typename RBTree<T>::Ref
create_perfectly_balanced_bstree(std::vector<T> &data)
{
    typename RBTree<T>::Ref tree = RBTree<T>::create();
    // TODO
    // Remember: the empty tree is perfectly balanced.
    // Remember: first, an ordered sequence (using < order) of values is needed.
    // Then you should use the above create_inserting_median function
    // on a empty tree to recursively create the perfectly balanced bstree.
    std::sort(data.begin(),data.end());
    create_inserting_median(data,0,data.size(),tree);
    //
    assert(tree != nullptr);
    return tree;
}
#endif //__ONLY_BSTREE__

template <class T>
bool RBTree<T>::is_empty() const
{
    bool empty = false;
    // TODO (done)
    if(root_ == nullptr){
        empty = true;
    }
    //
    return empty;
}

template <class T>
T RBTree<T>::item() const
{
    assert(!is_empty());
    T value;
    // TODO (done)

    value = root_->item();
    //
    return value;
}

template <class T>
std::ostream &RBTree<T>::fold(std::ostream &out) const
{
    // TODO (done)
    // Hint: use the recursive definition of a tree to fold it.
    if(!is_empty()){

        out << "[ " << item();
        if(root_->color() == 0){
            out << " B ";
        }else{
            out << " R ";
        }
        left()->fold(out);
        out << " ";
        right()->fold(out);
        out << " ]";
    }else{
        out << "[]";
    }

    //
    return out;
}

template <class T>
bool RBTree<T>::current_exists() const
{
    bool exists = false;
    // TODO (done)
    if(current_ != nullptr){
        exists = true;
    }
    //
    return exists;
}

template <class T>
T RBTree<T>::current() const
{
    assert(current_exists());
    T value;
    // TODO (done)
    value = current_->item();
    //
    return value;
}

template <class T>
int RBTree<T>::current_level() const
{
    assert(current_exists());
    int level = 0;
    // TODO (done)
    // Hint: follow the chain of parents' links.
    auto cur = current_->parent();
    if(cur != nullptr){
        while (cur != nullptr){
            level++;
            cur = cur->parent();
        }
    }else{
        level = 0;
    }
    //  
    return level;
}

template <class T>
typename RBTree<T>::Ref RBTree<T>::left() const
{
    assert(!is_empty());
    typename RBTree<T>::Ref subtree = nullptr;
    // TODO (done)
    // Hint: use the protected method to create a tree given the root node.
    if(root_->left() != nullptr){
        subtree = RBTree<T>::create(RBTNode<T>::create(root_->left()->item(), RBTNode<T>::RED, nullptr,root_->left()->left(),root_->left()->right()));

    }else{
        subtree = RBTree<T>::create();
    }
    //
    return subtree;
}

template <class T>
typename RBTree<T>::Ref RBTree<T>::right() const
{
    assert(!is_empty());
    typename RBTree<T>::Ref subtree = nullptr;
    // TODO (done)
    // Hint: use the protected method to create a tree given the root node.
    if(root_->right() != nullptr){
        subtree = RBTree<T>::create(RBTNode<T>::create(root_->right()->item(), RBTNode<T>::RED, nullptr,root_->right()->left(),root_->right()->right()));

    }else{
        subtree = RBTree<T>::create();
    }
    //
    return subtree;
}

template <class T>
size_t compute_size(typename RBTree<T>::Ref const &tree)
{
    assert(tree != nullptr);
    int s = 0;
    // TODO (done)
    // Hint: use the recursive implementation.
    if(!tree->is_empty()){
        s = 1;
        s = s + compute_size<T>(tree->left());
        s = s + compute_size<T>(tree->right());
    }else{
        s = 0;
    }
    //
    return s;
}

template <class T>
int compute_height(typename RBTree<T>::Ref const &tree)
{
    assert(tree != nullptr);
    int h = -1;
    // TODO (done)
    // Hint: use the recursive implementation.
    if(tree->is_empty()){
        h = -1;
    }else{
        int left = -1, right = -1;
        auto leftTree = tree->left();
        auto rightTree = tree->right();


        if (!leftTree->is_empty()){
            left = compute_height<T>(leftTree);
        }
        if (!rightTree->is_empty()){
            right = compute_height<T>(rightTree);
        }

        if(left < right){
            h = right + 1;
        }else{
            h = left + 1;
        }
    }
    //
    return h;
}

template <class T>
bool RBTree<T>::has(const T &k) const
{
#ifndef NDEBUG
    bool old_current_exists = current_exists();
    T old_current;
    if (old_current_exists)
        old_current = current();
#endif

    bool found = true;

    // TODO (done)
    // Hint: you can reuse the search method for this but in this case you will
    //       need to use "const_cast" to remove constness of "this" and
    //       save/restore the old state of current before returning.
    auto aux = this->root_;
    for(int i = 0; i == i; i++){
        if(aux->item() > k){
            if (aux->left() == nullptr){
                found = false;
                break;
            }else{
                aux = aux->left();
                found = true;
            }
        }else if(aux->item() < k ){
            if (aux->right() == nullptr){
                found = false;
                break;
            }else{
                aux = aux->right();
                found = true;
            }
        }else{
            found = true;
            break;
        }
    } 
    //
#ifndef NDEBUG
    assert(!old_current_exists || old_current == current());
#endif
    return found;
}

/**
 * @brief infix process of a node.
 * The Processor must allow to be used as a function with a parameter  (the
 * item to be processed) and returning true if the process must continue or
 * false if not.
 * @param node is the node to be processed.
 * @param p is the Processor.
 * @return true if all the tree was in-fix processed.
 */
template <class T, class Processor>
bool infix_process(typename RBTNode<T>::Ref node, Processor &p)
{
    bool retVal = true;
    // TODO
    // Remember: if node is nullptr return true.

    //
    return retVal;
}

template <class T>
bool RBTree<T>::is_a_binary_search_tree() const
{
    bool is_bst = true;
    // TODO
    // Remember: a empty tree is a binary search tree.
    //
    // Remember: for a non empty binary search tree, the in-fix traversal from
    // the root node must follow an ordered sequence of items.
    //
    // Remember: use a lambda function with signature '(T v) -> bool' to
    //  implement the Processor.
    //

    //
    return is_bst;
}

template <class T>
bool RBTree<T>::meet_red_invariant() const
{
#ifdef __ONLY_BSTREE__
    return true;
#else
    bool is_met = true;
    // TODO
    // Remember: A red node must not have a red child.
    // Remember: An empty tree meets the invariant.

    //
    return is_met;
#endif
}

template <class T>
bool RBTree<T>::meet_black_invariant() const
{
#ifdef __ONLY_BSTREE__
    return true;
#else
    bool is_met = true;
    // TODO
    // Remember: The number of black nodes for each path from root to any leaf must be equal.
    // Hint: use a lambda function to travel the tree.

    //
    return is_met;
#endif
}

template <class T>
bool RBTree<T>::is_a_rbtree() const
{
#ifdef __ONLY_BSTREE__
    return true;
#else
    assert(meet_red_invariant());
    assert(meet_black_invariant());
    return true;
#endif
}

template <class T>
void RBTree<T>::create_root(T const &v)
{
    assert(is_empty());
    // TODO
    
    //
    assert(is_a_binary_search_tree());
    assert(is_a_rbtree());
    assert(!is_empty());
    assert(item() == v);
}

template <class T>
bool RBTree<T>::search(T const &k)
{
    bool found = false;
    // TODO (done)
    parent_ = nullptr;
    current_ = root_;    
    while (current_ != nullptr && !found){
        if (current_->item() != k){
            parent_ = current_;
            if (current_->item() < k){
                current_ = current_->right();
            }else{
                current_ = current_->left();
            }
        }else{
            found = true;
        }
    }
    //
    assert(!found || current() == k);
    assert(found || !current_exists());
    return found;
}

template <class T>
void RBTree<T>::insert(T const &k)
{
    // //Check invariants.
    assert(is_a_binary_search_tree());
    assert(is_a_rbtree());

    if (!search(k))
    {
        // TODO (done)
        // Remember: a new node is always RED.
        if (!is_empty()){
            current_ = RBTNode<T>::create(k, RBTNode<T>::RED);
            if (parent_->item() < k){
                parent_->set_right(current_);
                
            }else{
                parent_->set_left(current_);
            }       
        }else{
            parent_ = nullptr;
            current_ = RBTNode<T>::create(k, RBTNode<T>::RED);
            root_ = current_;
        }

        //

        assert(check_parent_chains());
        make_red_black_after_inserting();
        assert(check_parent_chains());
        assert(check_min_max_branch_length());
    }
    //

    // Check invariants.
    assert(is_a_binary_search_tree());
    assert(is_a_rbtree());

    // check postconditions.
    assert(current_exists());
    assert(current() == k);
}

template <class T>
void RBTree<T>::remove()
{
    // check preconditions.
    assert(current_exists());

#ifndef NDEBUG
    // the invariants only must be checked for the first recursive call.
    // We use a static variable to count the recursion levels.
    // see section "Static variables in a Function" in
    // Ref https://www.geeksforgeeks.org/static-keyword-cpp/ for more info.
    static int recursion_count = 0;
    recursion_count++;
    if (recursion_count == 1)
    {
        // Check invariants.
        assert(is_a_binary_search_tree());
        assert(is_a_rbtree());
    }
#endif // NDEBUG

    bool replace_with_subtree = true;
    typename RBTNode<T>::Ref subtree;

    // TODO (done)
    //  Check which of BSTree cases 0,1,2,3 we have (see theoretical class slides).
    if (current_->right()==nullptr && current_->left()==nullptr){
        subtree = nullptr;
    }else if (current_->left()==nullptr){
        subtree = current_->right();
    }else if (current_->right()==nullptr){
        subtree = current_->left();
    }else{
        replace_with_subtree = false;
    }
    //

    if (replace_with_subtree)
    {
        // TODO (done)
        // Manage cases 0,1,2
        if (parent_ == nullptr){
            root_ = subtree;
        }else if (current_ == parent_->left()){
            parent_->set_left(subtree);
        }else if (current_ == parent_->right()){
            parent_->set_right(subtree);
        }            
        //
        assert(check_parent_chains());
        make_red_black_after_removing(subtree);
        assert(check_parent_chains());
        assert(check_min_max_branch_length());

        set_current_node(nullptr);
    }
    else
    {
        // TODO
        // Manage case 3.
        auto aux = current_;

        find_inorder_successor();

        aux->set_item(current_->item());

        remove();

        aux = nullptr;
        //
    }

#ifndef NDEBUG
    // We come back so the recursion count must be decreased.
    recursion_count--;
    assert(recursion_count >= 0);
    if (recursion_count == 0)
    {
        // Only check for the last return.
        // Check invariants.
        assert(is_a_binary_search_tree());
        assert(is_a_rbtree());

        // Check postconditions.
        assert(!current_exists());
    }
#endif
}

template <class T>
RBTree<T>::RBTree(typename RBTNode<T>::Ref root_node)
{
    // TODO (done)
    parent_ = nullptr;
    current_ = nullptr;
    root_ = root_node;
    
    //
    assert(!current_exists());
}

template <class T>
typename RBTree<T>::Ref RBTree<T>::create(typename RBTNode<T>::Ref root)
{
    // Note: we can not use std:make_shared here because the
    //  constructor with a root node is private.
    Ref ref = Ref(new RBTree<T>(root));
    ref->this_ = ref;
    return ref;
}

template <class T>
void RBTree<T>::set_left(Ref subtree)
{
    assert(!is_empty());

    // TODO (done)
    if(!subtree->is_empty()){
        auto aux = RBTNode<T>::create(subtree->root_->item(),subtree->root_->color(),root_,subtree->root_->left(),subtree->root_->right());
        root_->set_left(aux);
    }
    //

    assert(subtree->is_empty() || left()->item() == subtree->item());
    assert(!subtree->is_empty() || left()->is_empty());
}

template <class T>
void RBTree<T>::set_right(Ref subtree)
{
    assert(!is_empty());

    // TODO (done)
    if(!subtree->is_empty()){
        auto aux = RBTNode<T>::create(subtree->root_->item(),subtree->root_->color(),root_,subtree->root_->left(),subtree->root_->right());
        root_->set_right(aux);
    }
    //
    assert(subtree->is_empty() || right()->item() == subtree->item());
    assert(!subtree->is_empty() || right()->is_empty());
}

template <class T>
typename RBTNode<T>::Ref RBTree<T>::current_node() const
{
    typename RBTNode<T>::Ref node = nullptr;
    // TODO (done)
    node = current_;
    //
    return node;
}

template <class T>
void RBTree<T>::set_current_node(typename RBTNode<T>::Ref new_curr)
{
    // TODO (done)
    current_ = new_curr;
    //
    assert(new_curr == current_node());
}

template <class T>
typename RBTNode<T>::Ref RBTree<T>::root_node() const
{
    typename RBTNode<T>::Ref node = nullptr;
    // TODO (done)
    node = root_;
    //
    return node;
}

template <class T>
void RBTree<T>::set_root_node(typename RBTNode<T>::Ref new_root)
{
    // TODO (done)
    root_ = new_root;
    //
    assert(new_root == root_node());
}

template <class T>
typename RBTNode<T>::Ref RBTree<T>::parent_node() const
{
    typename RBTNode<T>::Ref node = nullptr;
    // TODO (done)
    node = parent_;
    //
    return node;
}

template <class T>
void RBTree<T>::find_inorder_successor()
{
    assert(current_exists());
    assert(is_a_binary_search_tree());
#ifndef NDEBUG
    T old_curr = current();
#endif
    // TODO (done)
    parent_ = current_;
    current_ = current_->right();
    while(current_->left()){
        parent_ = current_;
        current_ = current_->left();
    }
    //
    assert(current_exists() && current_node()->left() == nullptr);
#ifndef NDEBUG
    assert(current() > old_curr);
#endif
}

template <class T>
typename RBTNode<T>::Ref
RBTree<T>::rotate(typename RBTNode<T>::Ref P,
                  int dir)
{
    assert(P != nullptr);
    assert(dir == 0 || dir == 1);
    assert(P->child(1 - dir) != nullptr);
    typename RBTNode<T>::Ref N = P->child(1 - dir); // the child to promote.
#ifdef __DEBUG__
    if (__DEBUG__ > 1)
        std::clog << "Rotating to " << (dir == 0 ? "left" : "right") << " on key " << P->item() << std::endl;
#endif
    // TODO
    // Remember update links to parents.
    // Hint: you can see wikipedia: https://en.wikipedia.org/wiki/Tree_rotation

    //
    return N;
}

template <class T>
void RBTree<T>::make_red_black_after_inserting()
{
#ifdef __ONLY_BSTREE__
    return;
#else
    // TODO
    // Hint: @see https://www.geeksforgeeks.org/insertion-in-red-black-tree/

    typename RBTNode<T>::Ref N = current_node();
    typename RBTNode<T>::Ref P = parent_node();
    typename RBTNode<T>::Ref G; // Grandparent.
    typename RBTNode<T>::Ref U; // Uncle.
    int g_p_dir; //Granddad to parent direction.
    int p_n_dir; //Parent to N direction.

    if (P == nullptr)
    {
        //TODO: Case 0:

        //
    }

    while (P != nullptr)
    {
        if (P->color() == RBTNode<T>::BLACK)
        {
            //TODO Case 1: reqs 3 and 4 are met.

            //
        }

        // From here P is red.

        //TODO: update G, g_p_dir, U.

        //

        if (U != nullptr && U->color() == RBTNode<T>::RED)
        {
            //TODO Case 2:

            //
        }
        else
        {
            //Case 3:

            //TODO: update p_n_dir

            //
            if (g_p_dir != p_n_dir)
            {
                // TODO: cases 3c (LR) 3d (RL)

                //
            }
            // TODO: cases 3a (LL) 3b (RR)

            //
            return;
        }
        P = N->parent();
    }
#endif
}
template <class T>
void RBTree<T>::make_red_black_after_removing(typename RBTNode<T>::Ref V)
{

#ifdef __ONLY_BSTREE__
    return;
#else
    typename RBTNode<T>::Ref N = current_node(); // The removed node.
    typename RBTNode<T>::Ref P = parent_node();
    assert(!P || (P->child(0)==V || P->child(1)==V)); //V replaced to N

    if (P == nullptr)
    {
        // Case 1: empty tree.

        //
        return;
    }
    assert(P->child(0) == V || P->child(1) == V);
    int p_n_dir = (P->child(0)==V) ? 0 : 1; // Direction from P to N (0 Left, 1 Right)    

    if (N->color() == RBTNode<T>::RED || (V != nullptr && V->color() == RBTNode<T>::RED))
    {
        // TODO: case 2 (N or V is red)

        //
        return;
    }

    
    typename RBTNode<T>::Ref S; // Sibling of N
    typename RBTNode<T>::Ref C; // Close nephew of N
    typename RBTNode<T>::Ref D; // Distant nephew of N

    // Case 3: N and V are black.
    while (P != nullptr)
    {
        // TODO update S, D, C according to p_n_dir
        // Remember: S could be void.
        
        //

        if (S == nullptr || S->color() == RBTNode<T>::BLACK)
        {
            //Case 3.1: N, V and S are black

            if ((C && C->color() == RBTNode<T>::RED) ||
                (D && D->color() == RBTNode<T>::RED))
            {
                // Case 3.1a (at least one nephew is red)
                if (D == nullptr || D->color() == RBTNode<T>::BLACK)
                {
                    // TODO: case 3.1a when only C is red (RL, LR)
                    // Remember update new D and S.

                    //
                }
                // TODO: case 3.1a when D is Red (RR, LL)

                //
                return;
            }
            else
            {
                // Case 3.1b C y D are black.
                if (P->color() == RBTNode<T>::RED)
                {
                    // TODO: Case 3.1b (parent is RED)

                    //
                    return;
                }
                else
                {
                    // TODO: Case 3.1b (parent is black)
                    // Remember: we must go up one level, so
                    // update N, P, and p_n_dir according (if new P<>Void).

                    //
                }
                //
            }
        }
        else
        {
            // TODO: Case 3.2: N,V are black, S is red

            //
        }
    }
    return;
#endif
}

template <class T>
bool RBTree<T>::check_parent_chains()
{
    if (!is_empty())
    {
        std::function<void(typename RBTNode<T>::Ref, std::vector<T>)> go_down;
        go_down = [&go_down](typename RBTNode<T>::Ref node, std::vector<T> branch) -> void
        {
            if (node->left() != nullptr || node->right() != nullptr)
            {
                branch.push_back(node->item());
                if (node->left())
                    // go down by the left
                    go_down(node->left(), branch);
                if (node->right())
                    // go down by the right
                    go_down(node->right(), branch);
            }
            else
            {
                // The node is a leaf node, so check the branch
                // to the tree root node.
                typename RBTNode<T>::Ref parent = node->parent();
                int idx = static_cast<int>(branch.size()) - 1;
                while (parent && idx >= 0)
                {
                    assert(parent->item() == branch[idx]);
                    --idx;
                    parent = parent->parent();
                }
                assert(idx == -1 && parent == nullptr);
            }
        };
        std::vector<T> branch;
        go_down(root_node(), branch);
    }
    return true;
}

template <class T>
std::tuple<size_t, size_t>
compute_min_max_branch_length(typename RBTree<T>::Ref tree)
{
    assert(tree != nullptr);
    size_t min_path_l = 0;
    size_t max_path_l = 0;
    // TODO
    //  Hint: you can use a lambda function with prototype:
    //  std::function<void(typename RBTree<T>::Ref subt, size_t & min, size_t & max, size_t curr_l)>
    //  to recursive go down through the tree.
    //  Each new recursion increases the level in the tree. When a subtree is empty
    //  you have achieved a leaf of a branch and the current level is the
    //  branch length. Update the min/max values according before returning from
    //  this recursion.
    //  See: https://stackoverflow.com/questions/2067988/recursive-lambda-functions-in-c11
    //  to study a similar case.

    std::function<void(typename RBTree<T>::Ref, size_t &, size_t &, size_t)> go_down;
    go_down = [&go_down](typename RBTree<T>::Ref subtree, size_t &min_path_l,
                         size_t &max_path_l, size_t current_level) -> void
    {
        assert(!subtree->is_empty());
        auto left = subtree->left();
        auto right = subtree->right();
        if (left->is_empty() && right->is_empty())
        {
            min_path_l = std::min(min_path_l, current_level);
            max_path_l = std::max(max_path_l, current_level);
        }
        else
        {
            if (!left->is_empty())
                go_down(left, min_path_l, max_path_l, current_level + 1);
            if (!right->is_empty())
                go_down(right, min_path_l, max_path_l, current_level + 1);
        }
    };
    if (!tree->is_empty())
    {
        min_path_l = std::numeric_limits<size_t>::max();
        max_path_l = 0;
        go_down(tree, min_path_l, max_path_l, 0);
    }
    //

    return std::make_tuple(min_path_l, max_path_l);
}

template <class T>
bool RBTree<T>::check_min_max_branch_length() const
{
#ifdef __ONLY_BSTREE__
    return true;
#else
    size_t min_path_l, max_path_l;
    std::tie(min_path_l, max_path_l) = compute_min_max_branch_length<T>(This());
    return (max_path_l + 1) <= (2 * (min_path_l + 1));
#endif
}