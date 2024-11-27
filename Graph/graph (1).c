#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 

#define SUCCESS             1 
#define G_INVALID_VERTEX    2 
#define G_INVALID_EDGE      3 
#define G_VERTEX_EXISTS     4 
#define G_EDGE_EXISTS       5 
#define G_INCONSISTENT      6 

typedef int vertex_t; 
typedef int status_t; 

typedef struct hnode hnode_t; 
typedef hnode_t hlist_t; 

typedef struct vnode vnode_t; 
typedef vnode_t vlist_t; 

typedef struct graph graph_t; 

struct hnode{   
    vertex_t v; 
    vnode_t* pv; 
    struct hnode* prev; 
    struct hnode* next; 
}; 

struct vnode{
    vertex_t v; 
    hlist_t* ph_list; 
    struct vnode* prev; 
    struct vnode* next; 
}; 

struct graph{
    vlist_t* pv_list; 
    size_t number_of_vertices; 
    size_t number_of_edges; 
}; 

graph_t* create_graph(void); 
status_t add_vertex(graph_t* g, vertex_t v); 
status_t remove_vertex(graph_t* g, vertex_t v); 
status_t add_edge(graph_t* g, vertex_t v_start, vertex_t v_end); 
status_t remove_edge(graph_t* g, vertex_t v_start, vertex_t v_end); 
void show_graph(graph_t* g); 
status_t destroy_graph(graph_t** pp_g);
size_t get_number_of_vertices(graph_t* g); 
size_t get_number_of_edges(graph_t* g); 

vlist_t* v_create_list(void); 
void v_generic_insert(vnode_t* pv_start, vnode_t* pv_mid, vnode_t* pv_end); 
void v_generic_delete(vnode_t* pv_delete_node); 
vnode_t* v_search_node(vlist_t* pv_list, vertex_t v); 
vnode_t* v_get_node(vertex_t v); 

hlist_t* h_create_list(void); 
void h_generic_insert(hnode_t* ph_start, hnode_t* ph_mid, hnode_t* ph_end); 
void h_generic_delete(hnode_t* ph_delete_node); 
hnode_t* h_search_node(hlist_t* ph_list, vertex_t v); 
hnode_t* h_get_node(vertex_t v, vnode_t* pv); 

void* xmalloc(size_t size_in_bytes); 

int main(void){

    return (EXIT_SUCCESS); 
}

graph_t* create_graph(void){
    graph_t* g = NULL; 

    g = (graph_t*)xmalloc(sizeof(graph_t)); 
    g->pv_list = v_create_list();
    g->number_of_vertices = 0;  
    g->number_of_edges = 0; 

    return (g); 
}

status_t add_vertex(graph_t* g, vertex_t v){
    v_generic_insert(g->pv_list->prev, v_get_node(v), g->pv_list); 
    g->number_of_vertices += 1; 
    return (SUCCESS); 
}

status_t remove_vertex(graph_t* g, vertex_t v){

}

status_t add_edge(graph_t* g, vertex_t v_start, vertex_t v_end){
    vnode_t* pv_start = NULL; 
    vnode_t* pv_end = NULL; 
    hnode_t* ph_start_in_end = NULL; 
    hnode_t* ph_end_in_start = NULL; 

    pv_start = v_search_node(g->pv_list, v_start); 
    if(pv_start == NULL)
        return (G_INVALID_VERTEX); 

    pv_end = v_search_node(g->pv_list, v_end); 
    if(pv_end == NULL)
        return (G_INVALID_VERTEX); 

    ph_start_in_end = h_search_node(pv_end->ph_list, v_start); 
    ph_end_in_start = h_search_node(pv_start->ph_list, v_end); 

    if(ph_end_in_start && ph_start_in_end)
        return (G_EDGE_EXISTS); 

    if((ph_end_in_start != NULL) ^ (ph_start_in_end != NULL))
        return (G_INCONSISTENT); 

    h_generic_insert(pv_start->ph_list->prev, h_get_node(v_end, pv_end), pv_start->ph_list); 
    h_generic_insert(pv_end->ph_list->prev, h_get_node(v_start, pv_start), pv_end->ph_list); 
    g->number_of_edges += 1; 

    return (SUCCESS); 
}

status_t remove_edge(graph_t* g, vertex_t v_start, vertex_t v_end){

}

void show_graph(graph_t* g){

}

status_t destroy_graph(graph_t** pp_g){

}

size_t get_number_of_vertices(graph_t* g){
    return (g->number_of_vertices); 
}

size_t get_number_of_edges(graph_t* g){
    return (g->number_of_edges); 
}

vlist_t* v_create_list(void){
    vlist_t* pv_list = NULL; 

    pv_list = (vnode_t*)xmalloc(sizeof(vnode_t)); 
    pv_list->v = 0; 
    pv_list->ph_list = NULL; 
    pv_list->prev = pv_list; 
    pv_list->next = pv_list; 

    return (pv_list); 
}

void v_generic_insert(vnode_t* pv_start, vnode_t* pv_mid, vnode_t* pv_end){
    pv_mid->next = pv_end; 
    pv_mid->prev = pv_start; 
    pv_start->next = pv_mid; 
    pv_end->prev = pv_mid; 
}

void v_generic_delete(vnode_t* pv_delete_node){
    pv_delete_node->prev->next = pv_delete_node->next; 
    pv_delete_node->next->prev = pv_delete_node->prev; 
    free(pv_delete_node); 
}

vnode_t* v_search_node(vlist_t* pv_list, vertex_t v){
    vnode_t* run = NULL; 

    for(run = pv_list->next; run != pv_list; run = run->next)
        if(run->v == v)
            return (run); 

    return (NULL); 
}

vnode_t* v_get_node(vertex_t v){
    vnode_t* pv_node = NULL; 

    pv_node = (vnode_t*)xmalloc(sizeof(vnode_t)); 
    pv_node->v = v; 
    pv_node->ph_list = h_create_list();
    pv_node->prev = NULL; 
    pv_node->next = NULL; 

    return (pv_node); 
}

hlist_t* h_create_list(void){
    hlist_t* ph_new_list = NULL; 

    ph_new_list = h_create_list(); 
    ph_new_list->v = 0; 
    ph_new_list->pv = NULL; 
    ph_new_list->prev = ph_new_list; 
    ph_new_list->next = ph_new_list; 

    return (ph_new_list); 
}

void h_generic_insert(hnode_t* ph_start, hnode_t* ph_mid, hnode_t* ph_end){
    ph_mid->next = ph_end; 
    ph_mid->prev = ph_start; 
    ph_start->next = ph_mid; 
    ph_end->prev = ph_mid; 
}

void h_generic_delete(hnode_t* ph_delete_node){
    ph_delete_node->prev->next = ph_delete_node->next; 
    ph_delete_node->next->prev = ph_delete_node->prev; 
    free(ph_delete_node); 
}

hnode_t* h_search_node(hlist_t* ph_list, vertex_t v){
    hnode_t* run = NULL; 

    for(run = ph_list->next; run != ph_list; run = run->next)
        if(run->v == v)
            return (run); 

    return (NULL); 
}

hnode_t* h_get_node(vertex_t v, vnode_t* pv){
    hnode_t* ph_new_node = NULL;

    ph_new_node = (hnode_t*)xmalloc(sizeof(hnode_t)); 
    ph_new_node->v = v; 
    ph_new_node->pv = pv; 
    ph_new_node->prev = NULL; 
    ph_new_node->next = NULL; 

    return (ph_new_node); 
}

void* xmalloc(size_t size_in_bytes){
    void* ptr = NULL; 

    ptr = malloc(size_in_bytes); 
    if(ptr == NULL){
        puts("malloc():AllocationError"); 
        exit(EXIT_FAILURE); 
    }

    return (ptr); 
}