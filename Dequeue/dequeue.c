#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h>

#define SUCCESS     1 
#define TRUE        1 
#define FALSE       0 

#define LIST_INVALID_DATA   2 
#define LIST_EMPTY          3 
#define DEQUEUE_EMPTY       LIST_EMPTY 

typedef struct node node_t; 
typedef node_t list_t; 
typedef list_t dequeue_t; 
typedef int data_t; 
typedef int status_t;  
typedef int len_t; 

struct node
{
    data_t data; 
    struct node* prev; 
    struct node* next; 
}; 

/* Queue - Interface functions */
dequeue_t* create_dequeue(void); 

status_t enqueue_front(dequeue_t* p_queue, data_t new_data); 
status_t enqueue_rear(dequeue_t* p_queue, data_t new_data); 
status_t peek_front(dequeue_t* p_queue, data_t* p_peeked_data); 
status_t peek_rear(dequeue_t* p_queue, data_t* p_peeked_data); 
status_t dequeue_front(dequeue_t* p_queue, data_t* p_dequed_data); 
status_t dequeue_rear(dequeue_t* p_queue, data_t* p_dequed_data); 
status_t is_dequeue_empty(dequeue_t* p_queue); 

status_t destroy_dequeue(dequeue_t** pp_queue);

/* List - Interface functions */

list_t* create_list(void); 

status_t insert_start(list_t* p_list, data_t new_data); 
status_t insert_end(list_t* p_list, data_t new_data); 
status_t insert_after(list_t* p_list, data_t e_data, data_t new_data); 
status_t insert_before(list_t* p_list, data_t e_data, data_t new_data); 

status_t get_start(list_t* p_list, data_t* p_start_data); 
status_t get_end(list_t* p_list, data_t* p_end_data); 

status_t pop_start(list_t* p_list, data_t* p_start_data); 
status_t pop_end(list_t* p_list, data_t* p_end_data); 

status_t remove_start(list_t* p_list);  
status_t remove_end(list_t* p_list); 
status_t remove_data(list_t* p_list, data_t r_data); 

status_t find_data(list_t* p_list, data_t f_data); 
status_t is_list_empty(list_t* p_list); 
len_t get_length(list_t* p_list); 
void show_list(list_t* p_list, char* msg); 

status_t destroy_list(list_t** pp_list); 

/* List - Helper functions */

node_t* search_node(list_t* p_list, data_t search_data); 
void generic_insert(node_t* p_beg, node_t* p_mid, node_t* p_end); 
void generic_delete(node_t* p_delete_node); 
node_t* get_node(data_t new_data); 

void* xmalloc(size_t number_of_bytes); 

int main(void)
{
    dequeue_t* p_dequeue = NULL; 
    data_t data; 
    status_t status; 
    int i; 

    p_dequeue = create_dequeue(); 

    assert(is_dequeue_empty(p_dequeue) == TRUE); 
    assert(peek_front(p_dequeue, &data) == DEQUEUE_EMPTY);
    assert(peek_rear(p_dequeue, &data) == DEQUEUE_EMPTY);
    assert(dequeue_front(p_dequeue, &data) == DEQUEUE_EMPTY);
    assert(dequeue_rear(p_dequeue, &data) == DEQUEUE_EMPTY);

    for(data = 10; data <= 50; data += 10)
    {
        status = enqueue_rear(p_dequeue, data); 
        assert(SUCCESS); 
    }

    for(data = 60; data <= 100; data += 10)
    {
        status = enqueue_front(p_dequeue, data); 
        assert(status == SUCCESS); 
    }

    status = peek_rear(p_dequeue, &data); 
    assert(status == SUCCESS); 
    printf("QUEUE REAR:%d\n", data); 

    status = peek_front(p_dequeue, &data); 
    assert(status == SUCCESS); 
    printf("QUEUE FRONT:%d\n", data); 

    for(i = 0; i < 5; ++i)
    {
        status = dequeue_front(p_dequeue, &data); 
        assert(status == SUCCESS); 
        printf("DEQUEUED FRONT:%d\n", data); 
    }

    for(i = 0; i < 5; ++i)
    {
        status = dequeue_rear(p_dequeue, &data); 
        assert(status == SUCCESS); 
        printf("DEQUEUED REAR:%d\n", data); 
    }

    assert(is_dequeue_empty(p_dequeue) == TRUE); 
    puts("DEQUEUE is empty"); 

    assert(destroy_dequeue(&p_dequeue) == SUCCESS); 
    puts("DEQUEUE is destroyed successfully"); 
    return (EXIT_SUCCESS);  
}

/* DeQueue - Interface functions */

dequeue_t* create_dequeue(void)
{
    return create_list(); 
}

status_t enqueue_front(dequeue_t* p_queue, data_t new_data)
{
    return insert_start(p_queue, new_data); 
}

status_t enqueue_rear(dequeue_t* p_queue, data_t new_data)
{
    return insert_end(p_queue, new_data); 
}

status_t peek_front(dequeue_t* p_queue, data_t* p_peeked_data)
{
    return get_start(p_queue, p_peeked_data); 
}

status_t peek_rear(dequeue_t* p_queue, data_t* p_peeked_data)
{
    return get_end(p_queue, p_peeked_data); 
}

status_t dequeue_front(dequeue_t* p_queue, data_t* p_dequed_data)
{
    return pop_start(p_queue, p_dequed_data); 
}

status_t dequeue_rear(dequeue_t* p_queue, data_t* p_dequed_data)
{
    return pop_end(p_queue, p_dequed_data); 
}

status_t is_dequeue_empty(dequeue_t* p_queue)
{
    return is_list_empty(p_queue); 
}

status_t destroy_dequeue(dequeue_t** pp_dequeue)
{
    return destroy_list(pp_dequeue); 
}

list_t* create_list(void)
{
    list_t* p_list = NULL; 

    p_list = get_node(0); 
    p_list->prev = p_list; 
    p_list->next = p_list; 

    return (p_list); 
}

status_t insert_start(list_t* p_list, data_t new_data)
{
    generic_insert(p_list, get_node(new_data), p_list->next); 
    return (SUCCESS); 
}

status_t insert_end(list_t* p_list, data_t new_data)
{
    generic_insert(p_list->prev, get_node(new_data), p_list); 
    return (SUCCESS); 
} 

status_t insert_after(list_t* p_list, data_t e_data, data_t new_data)
{   
    node_t* p_existing_node = NULL; 

    p_existing_node = search_node(p_list, e_data); 
    if(p_existing_node == NULL)
        return (LIST_INVALID_DATA); 

    generic_insert(p_existing_node, get_node(new_data), p_existing_node->next); 
    
    return (SUCCESS); 
}

status_t insert_before(list_t* p_list, data_t e_data, data_t new_data)
{
    node_t* p_existing_node = NULL; 

    p_existing_node = search_node(p_list, e_data); 
    if(p_existing_node == NULL)
        return (LIST_INVALID_DATA); 

    generic_insert(p_existing_node->prev, get_node(new_data), p_existing_node); 
    
    return (SUCCESS); 
}

status_t get_start(list_t* p_list, data_t* p_start_data)
{
    if(p_list->prev == p_list && p_list->next == p_list)
        return (LIST_EMPTY); 

    *p_start_data = p_list->next->data; 
    return (SUCCESS); 
}

status_t get_end(list_t* p_list, data_t* p_end_data)
{
    if(p_list->prev == p_list && p_list->next == p_list)
        return (LIST_EMPTY); 

    *p_end_data = p_list->prev->data; 
    return (SUCCESS); 
}

status_t pop_start(list_t* p_list, data_t* p_start_data)
{
    if(p_list->prev == p_list && p_list->next == p_list)
        return (LIST_EMPTY); 

    *p_start_data = p_list->next->data; 
    generic_delete(p_list->next); 
    return (SUCCESS); 
}

status_t pop_end(list_t* p_list, data_t* p_end_data)
{
    if(p_list->prev == p_list && p_list->next == p_list)
        return (LIST_EMPTY); 
    
    *p_end_data = p_list->prev->data; 
    generic_delete(p_list->prev); 
    return (SUCCESS); 
}

status_t remove_start(list_t* p_list)
{
    if(p_list->prev == p_list && p_list->next == p_list)
        return (LIST_EMPTY); 

    generic_delete(p_list->next); 
    return (SUCCESS);
}
status_t remove_end(list_t* p_list)
{
    if(p_list->prev == p_list && p_list->next == p_list)
        return (LIST_EMPTY); 
    generic_delete(p_list->prev); 
    return (SUCCESS); 
}

status_t remove_data(list_t* p_list, data_t r_data)
{
    node_t* p_remove_node = NULL; 

    p_remove_node = search_node(p_list, r_data); 
    if(p_remove_node == NULL)
        return (LIST_INVALID_DATA); 

    generic_delete(p_remove_node); 

    return (SUCCESS); 
}

status_t find_data(list_t* p_list, data_t f_data)
{
    node_t* p_existing_node = NULL; 

    p_existing_node = search_node(p_list, f_data); 

    return (p_existing_node != NULL); 
}

status_t is_list_empty(list_t* p_list)
{
    return (p_list->prev == p_list && p_list->next == p_list); 
}

len_t get_length(list_t* p_list)
{
    len_t N = 0; 
    node_t* p_run = NULL; 

    for(p_run = p_list->next; p_run != p_list; p_run = p_run->next)
        ++N; 

    return (N); 
}

void show_list(list_t* p_list, char* msg) 
{
    node_t* p_run = NULL; 

    if(msg != NULL)
        puts(msg); 

    printf("[START]<->"); 

    for(p_run = p_list->next; p_run != p_list; p_run = p_run->next)
        printf("[%d]<->", p_run->data); 

    puts("[END]"); 
}

status_t destroy_list(list_t** pp_list)
{
    list_t* p_list = NULL; 
    node_t* p_run = NULL; 
    node_t* p_run_next = NULL; 

    p_list = *pp_list;

    for(p_run = p_list->next; p_run != p_list; p_run = p_run_next)
    {
        p_run_next = p_run->next; 
        free(p_run); 
    }

    free(p_list); 
    p_list = NULL; 

    *pp_list = NULL; 

    return (SUCCESS); 
}

/* List - Helper functions */

node_t* search_node(list_t* p_list, data_t search_data)
{
    node_t* p_run = NULL; 

    for(p_run = p_list->next; p_run != p_list; p_run = p_run->next)
        if(p_run->data == search_data)
            return (p_run); 

    return (NULL); 
}

void generic_insert(node_t* p_beg, node_t* p_mid, node_t* p_end)
{
    p_mid->next = p_end; 
    p_mid->prev = p_beg; 
    p_beg->next = p_mid; 
    p_end->prev = p_mid; 
}

void generic_delete(node_t* p_delete_node)
{
    p_delete_node->prev->next = p_delete_node->next; 
    p_delete_node->next->prev = p_delete_node->prev;
    free(p_delete_node); 
}


node_t* get_node(data_t new_data)
{
    node_t* p_new_node = NULL; 

    p_new_node = (node_t*)xmalloc(sizeof(node_t)); 
    p_new_node->data = new_data; 
    p_new_node->prev = NULL; 
    p_new_node->next = NULL; 

    return (p_new_node); 
}

void* xmalloc(size_t number_of_bytes)
{
    void* ptr = NULL; 

    ptr = malloc(number_of_bytes); 
    if(ptr == NULL)
    {
        puts("AllocationError: Error in allocating memory"); 
        exit(EXIT_FAILURE); 
    }

    return (ptr); 
}
