#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h>

#define SUCCESS     1 
#define TRUE        1 
#define FALSE       0 

#define LIST_INVALID_DATA   2 
#define LIST_EMPTY          3 
#define STACK_EMPTY         LIST_EMPTY 

typedef struct node node_t; 
typedef node_t list_t; 
typedef list_t stack_t;     
typedef int data_t; 
typedef int status_t;  
typedef int len_t; 

struct node
{
    data_t data; 
    struct node* prev; 
    struct node* next; 
}; 

/* Stack - Interface functions */
stack_t* create_stack(void); 
status_t push(stack_t* p_stack, data_t new_data); 
status_t top(stack_t* p_stack, data_t* p_top_data); 
status_t pop(stack_t* p_stack, data_t* p_poped_data); 
status_t is_stack_empty(stack_t* p_stack); 
status_t destroy_stack(stack_t** pp_stack); 

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
    stack_t* p_stack = NULL; 
    data_t data; 
    status_t status; 

    p_stack = create_stack();

    status = is_stack_empty(p_stack); 
    if(status == TRUE)
        puts("The stack is empty at the start"); 

    status = top(p_stack, &data); 
    if(status == STACK_EMPTY)
        puts("Cannot top from empty stack"); 

    status = pop(p_stack, &data); 
    if(status == STACK_EMPTY)
        puts("Cannot pop from empty stack"); 

    for(data = 1; data <= 50; ++data)
    {
        status = push(p_stack, data); 
        assert(status == SUCCESS); 
    }

    status = top(p_stack, &data); 
    printf("TOP OF STACK = %d\n", data); 

    while(is_stack_empty(p_stack) == FALSE)
    {
        status = pop(p_stack, &data); 
        assert(status == SUCCESS); 
        printf("POPED DATA = %d\n", data); 
    }

    status = destroy_stack(&p_stack); 
    assert(status == SUCCESS && p_stack == NULL); 

    return (EXIT_SUCCESS); 
}

stack_t* create_stack(void)
{
    return create_list(); 
}

status_t push(stack_t* p_stack, data_t new_data)
{
    return insert_end(p_stack, new_data); 
}

status_t top(stack_t* p_stack, data_t* p_top_data)
{
    return get_end(p_stack, p_top_data); 
}

status_t pop(stack_t* p_stack, data_t* p_poped_data)
{
    return pop_end(p_stack, p_poped_data); 
}

status_t is_stack_empty(stack_t* p_stack)
{
    return is_list_empty(p_stack); 
}

status_t destroy_stack(stack_t** pp_stack)
{
    return destroy_list(pp_stack); 
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
