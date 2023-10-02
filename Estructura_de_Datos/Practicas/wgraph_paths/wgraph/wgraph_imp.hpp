/**
 * @file graph_utils_imp.hpp
 *
 * CopyRight F. J. Madrid-Cuevas <fjmadrid@uco.es>
 *
 * Sólo se permite el uso de este código en la docencia de las asignaturas sobre
 * Estructuras de Datos de la Universidad de Córdoba.
 *
 * Está prohibido su uso para cualquier otro objetivo.
 */
#pragma once

#include <string>

#include "wgraph.hpp"

/** GraphNode implementation **/

template <class T>
WNode<T>::WNode(size_t label, T const &v)
{
    // TODO (done)
    _item = v;
    _visited = false;
    _label = label;
    
    //
    assert(item() == v);
    assert(!is_visited());
}

template <class T>
T WNode<T>::item() const
{
    T ret_v;
    // TODO (done)

    ret_v = _item;

    //
    return ret_v;
}

template <class T>
size_t WNode<T>::label() const
{
    size_t ret_v = 0;
    // TODO (done)

    ret_v = _label;

    //
    return ret_v;
}

template <class T>
bool WNode<T>::is_visited() const
{
    bool ret_v = false;
    // TODO (done)

    ret_v = _visited;

    //
    return ret_v;
}

template <class T>
void WNode<T>::set_item(T const &v)
{
    // TODO (done)

    _item = v;

    //
    assert(item() == v);
}

template <class T>
void WNode<T>::set_visited(bool new_st)
{
    // TODO (done)

    _visited = new_st;

    //
    assert(new_st || !is_visited());
    assert(!new_st || is_visited());
}

/** GraphEdge implementation **/

template <class T, class E>
WEdge<T, E>::WEdge(NodeRef u, NodeRef v, FMatrix::Ref wmat)
{
    // TODO (done)
    
    _v = v;
    _u = u;
    _wmat = wmat;

    //
}

template <class T, class E>
E WEdge<T, E>::weight() const
{
    E ret_val = std::numeric_limits<float>::infinity();
    // TODO (done)

    ret_val = _wmat->get(_u->label(), _v->label());

    //
    return ret_val;
}

template <class T, class E>
bool WEdge<T, E>::has(NodeRef const &n) const
{
    bool ret_val = false;
    // TODO (done)
    if (n == _u || n == _v){
        ret_val = true;
    }

    //
    return ret_val;
}

template <class T, class E>
typename WEdge<T, E>::NodeRef WEdge<T, E>::other(NodeRef const &n) const
{
    assert(has(n));
    NodeRef ret_val;
    // TODO (done)

    if (n == _v){
        ret_val = _u;
    }else{
        ret_val = _v;
    }

    //
    return ret_val;
}

template <class T, class E>
typename WEdge<T, E>::NodeRef WEdge<T, E>::first() const
{
    NodeRef ret_val;
    // TODO (done)

    ret_val = _u;

    //
    return ret_val;
}

template <class T, class E>
typename WEdge<T, E>::NodeRef WEdge<T, E>::second() const
{
    NodeRef ret_val;
    // TODO (done)

    ret_val = _v;

    //
    return ret_val;
}

template <class T, class E>
void WEdge<T, E>::set_weight(E const &v)
{
    // TODO (done)

    _wmat->set(_u->label(), _v->label(), v);

    //
    assert(weight() == v);
}

/** WGraph implementation **/
template <class T>
WGraph<T>::WGraph(size_t capacity, float default_weight)
{
    assert(capacity > 0);

    // TODO (done)
    // Remember: this a weighted graph, so all the nodes are connected with
    //           infinite weight by default.
    
    _size = 0;
    _nodes = std::vector<NodeRef>(capacity);
    _a_mat = FMatrix::create(capacity, capacity, default_weight);

    _curr_node = capacity + 1;
    _curr_edge = capacity + 1;

    //

    assert(is_empty());
    assert(!has_current_node());
    assert(!has_current_edge());
}

template <class T>
bool WGraph<T>::is_empty() const
{
    bool ret_v = true;
    // TODO (done)
    if(_size == 0){
        ret_v = true;
    }else{
        ret_v = false;
    }

    //
    assert(!ret_v || size() == 0);
    return ret_v;
}

template <class T>
bool WGraph<T>::is_full() const
{
    bool ret_v = true;
    // TODO (done)
    if (_size != _nodes.capacity()){
        ret_v = false;
    }else{
        ret_v = true;
    }

    //
    assert(!ret_v || size() == capacity());
    return ret_v;
}

template <class T>
size_t WGraph<T>::size() const
{
    size_t ret_v = 0;
    // TODO (done)

    ret_v = _size;

    //
    return ret_v;
}

template <class T>
size_t WGraph<T>::capacity() const
{
    size_t ret_v = 0;
    // TODO (done)

    ret_v = _nodes.size();

    //
    return ret_v;
}

template <class T>
bool WGraph<T>::has(NodeRef u) const
{
    assert(u != nullptr);
    bool ret_v = true;
    // TODO (done)

    if(_nodes[u->label()] == u && u->_label < capacity()){
        ret_v = true;
    }else{
        ret_v = false;
    }

    //
    assert(!ret_v || (u->label() < capacity() && node(u->label()) == u));
    return ret_v;
}

template <class T>
bool WGraph<T>::are_adjacent(NodeRef u, NodeRef v) const
{
    assert(has(u) && has(v));
    bool ret_v = false;
    // TODO (done)
    // Remember: this a Weighted graph so a node u is adjacent to v if the
    //           edge's weight is less than infinite.
    //  Hint: use std::numeric_limits<float> facet to get infinite as float value.

    if(_a_mat[u->label()][v->label()]<std::numeric_limits<float>::infinity()){
        ret_v = true;
    }else{
        ret_v = false;
    }

    //
    return ret_v;
}

template <class T>
bool WGraph<T>::has_current_node() const
{
    bool ret_v = false;
    // TODO (done)
    // Hint: use attribute _size to mark "end".
    
    if(_curr_node < _size){
        ret_v = true;
    }else{
        ret_v = false;
    }

    //
    return ret_v;
}

template <class T>
typename WGraph<T>::NodeRef WGraph<T>::current_node() const
{
    assert(has_current_node());
    NodeRef ret_v;
    // TODO (done)
    ret_v =_nodes[_curr_node];

    //
    return ret_v;
}

template <class T>
bool WGraph<T>::has_current_edge() const
{
    bool ret_v = false;
    // TODO (done)
    // Remember: first it must exist a current node.
    // Hint: use value size() to mark "end".
    if (has_current_node()){
        if(_curr_edge < _size){
            ret_v = true;
        }else{
            ret_v = false;
        }
    }else{
        ret_v = false;
    }

    //
    assert(!ret_v || has_current_node());
    return ret_v;
}

template <class T>
float WGraph<T>::current_weight() const
{
    assert(has_current_edge());
    float ret_v = 0.0;
    // TODO (done)

    ret_v = weight(_nodes[_curr_node], _nodes[_curr_edge]);

    //
    assert(ret_v < std::numeric_limits<float>::infinity());
    return ret_v;
}

template <class T>
FMatrix::Ref WGraph<T>::weight_matrix() const
{
    FMatrix::Ref mat;
    // TODO (done)

    mat = _a_mat;

    //
    return mat;
}

template <class T>
float WGraph<T>::weight(size_t u_label, size_t v_label) const
{
    assert(u_label < size());
    assert(v_label < size());
    float ret_v = 0.0;
    // TODO (done)

    float aux = _a_mat->get(u_label, v_label);
    ret_v = aux;

    //
    assert(ret_v == weight(node(u_label), node(v_label)));
    return ret_v;
}

template <class T>
float WGraph<T>::weight(NodeRef u, NodeRef v) const
{
    assert(has(u));
    assert(has(v));
    float ret_v = 0.0;
    // TODO (done)
    float aux = _a_mat->get(u->label(), v->label());
    ret_v = aux;

    //
    return ret_v;
}

template <class T>
typename WGraph<T>::EdgeRef WGraph<T>::edge(NodeRef u, NodeRef v) const
{
    assert(has(u));
    assert(has(v));
    EdgeRef ret_v = nullptr;
    // TODO (done)

    ret_v = std::shared_ptr<WEdge<T,float>>(new WEdge<T, float>(u, v, _a_mat));

    //
    assert(ret_v->first() == u);
    assert(ret_v->second() == v);
    assert(ret_v->weight() == weight(u, v));
    return ret_v;
}

template <class T>
typename WGraph<T>::EdgeRef WGraph<T>::edge(size_t u_label, size_t v_label) const
{
    assert(u_label < size());
    assert(v_label < size());
    EdgeRef ret_v = nullptr;
    // TODO (done)
    // Hint: use the static method WEdge::create().

    ret_v = std::shared_ptr<WEdge<T, float>>(new WEdge<T,float>(node(u_label), node(v_label),_a_mat));

    //
    assert(ret_v->first()->label() == u_label);
    assert(ret_v->second()->label() == v_label);
    assert(ret_v->weight() == weight(u_label, v_label));
    return ret_v;
}

template <class T>
typename WGraph<T>::EdgeRef WGraph<T>::current_edge() const
{
    assert(has_current_edge());
    EdgeRef ret_v = nullptr;
    // TODO (done)
    // Hint: use the static method WEdge::create().
    ret_v = std::shared_ptr<WEdge<T,float>>(new WEdge<T,float>(node(_curr_node), node(_curr_edge), _a_mat));

    //
    assert(ret_v->first() == current_node() && ret_v->weight() < std::numeric_limits<float>::infinity());
    return ret_v;
}

template <class T>
typename WGraph<T>::NodeRef WGraph<T>::node(size_t label) const
{
    assert(label < size());
    NodeRef n;
    // TODO (done)
    n = _nodes[label];

    //
    return n;
}

template <class T>
void WGraph<T>::set_visited(bool state)
{
    // TODO (done)
    //  Remember: we only have visited flag in nodes, no one in edges.
    for (int i = 1; i <= _size; i++){
        _nodes[i]->set_visited(state);
    }
    //
}

template <class T>
void WGraph<T>::goto_first_node()
{
    assert(!is_empty());
    // TODO (done)
    // Remember: the edge's cursor must be initialized too.
    _curr_node = 0;
    if (has_current_node()){
        goto_first_edge();
    }
    //
    assert(!has_current_edge() || current_edge()->first() == current_node());
    assert(!has_current_edge() ||
           current_weight() < std::numeric_limits<float>::infinity());
}

template <class T>
void WGraph<T>::goto_first_edge()
{
    assert(has_current_node());
    // TODO (done)
    //  Remember: we consider here edges with weight < infinite.
    _curr_edge = 0;
    while (_curr_edge < _size && weight(_curr_node,_curr_edge)==std::numeric_limits<float>::infinity()){
        _curr_edge = _curr_edge+1;
    }
    //
    assert(!has_current_edge() || current_edge()->first() == current_node());
    assert(!has_current_edge() ||
           current_weight() < std::numeric_limits<float>::infinity());
}

template <class T>
void WGraph<T>::goto_next_node()
{
    assert(has_current_node());
    // TODO (done)
    //  Remember: you must update the edge cursor too.
    _curr_node = _curr_node + 1;
    if (has_current_node()){
        goto_first_edge();
    }
    //
    assert(has_current_node() || !has_current_edge());
    assert(!has_current_edge() || (current_edge()->first() == current_node()));
    assert(!has_current_edge() ||
           current_weight() < std::numeric_limits<float>::infinity());
}

template <class T>
void WGraph<T>::goto_next_edge()
{
    assert(has_current_edge());
    // TODO (done)
    //  Remember: we consider here edges with weight < infinite.
    do
    {
        _curr_edge = _curr_edge + 1;
    } while ((_curr_edge<_size) && (_a_mat->get(_curr_node, _curr_edge)==std::numeric_limits<float>::infinity()));
    //
    assert(!has_current_edge() || current_edge()->first() == current_node());
    assert(!has_current_edge() ||
           current_weight() < std::numeric_limits<float>::infinity());
}

template <class T>
void WGraph<T>::goto_node(NodeRef u)
{
    assert(has(u));
    // TODO (done)
    //  Remember: update edge cursor too.

    goto_first_edge();
    _curr_node = u->label();
    
    //
    assert(!has_current_edge() || current_edge()->first() == u);
    assert(!has_current_edge() ||
           current_weight() < std::numeric_limits<float>::infinity());
}

template <class T>
void WGraph<T>::goto_edge(NodeRef u, NodeRef v)
{
    assert(has(u));
    assert(has(v));
    assert(weight(u, v) < std::numeric_limits<float>::infinity());
    // TODO (done)
    // Remember: node and edge cursors must be initialized too.

    _curr_edge=v->label();
    _curr_node=u->label();
    
    //
    assert(current_node() == u);
    assert(current_edge()->first() == u);
    assert(current_edge()->second() == v);
    assert(current_weight() == weight(u, v));
}

template <class T>
void WGraph<T>::goto_edge(EdgeRef e)
{
    assert(has(e->first()));
    assert(has(e->second()));
    assert(e->weight() < std::numeric_limits<float>::infinity());
    // TODO (done)
    // Remember: node and edge cursors must be initialized too.

    goto_edge(e->first(), e->second());

    //
    assert(current_node() == e->first());
    assert(current_edge()->second() == e->second());
    assert(current_weight() == e->weight());
}

template <class T>
typename WGraph<T>::NodeRef WGraph<T>::find_node(typename T::key_t const &key)
{
    assert(!is_empty());
    NodeRef ret_v = nullptr;
    // TODO (done)
    //  Remember: update node and edge cursors.
    //  Remember: The item.key() is used to look for.
    goto_first_node();
    while (has_current_node()){
        if (current_node()->item()== key){
            ret_v = current_node();
            break;
        }
        goto_next_node();
    }
    //
    assert((ret_v == nullptr) || (has_current_node() && current_node() == ret_v));
    assert(!has_current_node() || current_node()->item() == key);
    assert(!has_current_edge() || current_edge()->first() == current_node());
    return ret_v;
}

template <class T>
typename WGraph<T>::NodeRef WGraph<T>::find_next_node(typename T::key_t const &key)
{
    assert(!is_empty());
    NodeRef ret_v = nullptr;
    // TODO (done)
    //  Remember: update node and edge cursors.
    //  Remember: The item.key() is used to look for.
    for (int i = _curr_node; i < _size; i++){
        if (_nodes[i]->item() == key){
            ret_v = _nodes[i];
            goto_node(ret_v);
            break;
        }
    }
    //
    assert((ret_v == nullptr) || (has_current_node() && current_node() == ret_v));
    assert(!has_current_node() || current_node()->item() == key);
    assert(!has_current_edge() || current_edge()->first() == current_node());
    return ret_v;
}

template <class T>
void WGraph<T>::set_current_weight(float new_w)
{
    assert(has_current_edge());
    // TODO (done)
    //  Remember: set infinite as new weight invalidates edge_cursor.

    _a_mat->set(_curr_node, _curr_edge, new_w);

    //
    assert(new_w < std::numeric_limits<float>::infinity() || !has_current_edge());
}

template <class T>
void WGraph<T>::set_weight(size_t u_label, size_t v_label, float new_w)
{
    assert(u_label < size());
    assert(v_label < size());
    // TODO (done)
    // Remember: set infinite as new weight could invalidate the edge cursor if it is currently points to this edge.

    _a_mat->set(u_label, v_label, new_w);

    //
    assert(new_w == weight(u_label, v_label));
    assert(!has_current_edge() || current_weight() < std::numeric_limits<float>::infinity());
}

template <class T>
void WGraph<T>::set_weight(NodeRef u, NodeRef v, float new_w)
{
    assert(has(u));
    assert(has(v));
    // TODO (done)
    //  Remember: set infinite as new weight could invalidate the edge cursor if it is currently points to this edge.

    _a_mat->set(u->label(), v->label(), new_w);

    //
    assert(weight(u, v) == new_w);
    assert(!has_current_edge() || current_weight() < std::numeric_limits<float>::infinity());
}

template <class T>
void WGraph<T>::add_node(T const &v)
{
    assert(!is_full());
    // TODO (done)
    //  Remember: update node and edge cursors.
    _curr_node =_size;
    _curr_edge =_size + 1;
    _nodes[_size]=WNode<T>::create(_size,v);
    _size = _size+1;
    //
    assert(has_current_node());
    assert(!has_current_edge());
}

template <class T>
std::ostream &
WGraph<T>::fold(std::ostream &out) const
{
    // TODO (done)
    // Hint: the Matrix template has a fold method.
    out << "[ " << capacity() << " "<< size() << " ";
    for (size_t n = 0; n < size(); ++n){
        out << node(n)->item() << " ";
    }
    std::vector<typename WGraph<T>::EdgeRef> edges;
    weight_matrix() -> fold(out);
    out << " ]";

    //
    return out;
}

template <class T>
WGraph<T>::WGraph(std::istream &input) noexcept(false)
{
    // TODO (done)
    // Remember: capacity is the max number of nodes that the graph could have.
    //           size is the current number of nodes (size <= capacity).
    // Hint: The Matrix template has a unfold method.
    std::string token;
    T item;
    size_t cap, nod;
    input >> token; 
    input >> cap;
    input >> nod;
    _size = nod;

    for (size_t n = 0; n < nod; ++n){
        input >> item;
        _nodes.push_back(WNode<T>::create(n,item));
    }

    _a_mat = Matrix<float>::create(input);
    _curr_node = _size;
    _curr_edge = _size;
    //
    assert(!has_current_node());
    assert(!has_current_edge());
}

template <class T>
typename WGraph<T>::Ref WGraph<T>::create(std::istream &input)
{
    return std::make_shared<WGraph<T>>(input);
}

template <class T>
typename WGraph<T>::Ref create_wgraph(std::istream &in) noexcept(false)
{
    assert(in);
    typename WGraph<T>::Ref graph = nullptr; // The returned graph.

    // TODO (done)
    // Remember: Throw std::runtime_error("Wrong graph") when detecting a wrong
    //           input format.
    // Remember: key_t type is used to give the edge's ends.

    // TODO (done)
    // First: Determine if it is directed or undirected.
    std::string t;
    if (!in){
        return nullptr;
    }
    in >> t;
    //

    // TODO (done)
    // Second: get the number of nodes and create a wgraph with this capacity.
    size_t node;
    if (!in){
        return nullptr;
    }        
    in >> node;
    //

    // TODO (done)
    // Third: load the N T data items and adding the nodes.
    graph.reset(new WGraph<T>(node));
    T item;
    for (size_t n = 0; n < node; ++n){
        if (!in){
            return nullptr;
        }

        in >> item;
        graph->add_node(item);
    }
    //

    // TODO (done)
    // Fourth: load the number of edges.
    size_t edges;
    in >> edges;
    //

    // TODO (done)
    // Fifth: load the N edges.
    // Remember: Use T::key_t type to load the edge's ends.
    // Remember: if the input graph is UNDIRECTED we simulated this with a WGraph
    //           duplicating each input edge (u,v) making too the (v,u) edge with same weight
    //           with the same weight.
    for (size_t e = 0; e < edges; ++e){
        typename T::key_t u, v;
        float w;
        in >> u >> v >> w;
        graph->set_weight(graph->find_node(u), graph->find_node(v), w);
        if (t != "DIRECTED"){
            graph->set_weight(graph->find_node(v), graph->find_node(u), w);
        }
            
    }
    //

    return graph;
}