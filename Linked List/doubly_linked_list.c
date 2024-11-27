#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 

#define SUCCESS                 1 
#define TRUE                    1 
#define FALSE                   0 
#define LIST_INVALID_DATA       2 
#define LIST_EMPTY              3 

struct node
{ 
    int data; 
    struct node* prev; 
    struct node* next; 
}; 

struct node* create_list(void); 

void insert_start(struct node* p_list, int new_data); 
void insert_end(struct node* p_list, int new_data); 
int insert_after(struct node* p_list, int e_data, int new_data); 
int insert_before(struct node* p_list, int e_data, int new_data); 

int get_start(struct node* p_list, int* p_start_data); 
int get_end(struct node* p_list, int* p_end_data); 
int pop_start(struct node* p_list, int* p_start_data); 
int pop_end(struct node* p_list, int* p_end_data); 

int remove_start(struct node* p_list); 
int remove_end(struct node* p_list); 
int remove_data(struct node* p_list, int r_data); 

int find(struct node* p_list, int f_data); 
int get_length(struct node* p_list); 
int is_list_empty(struct node* p_list); 
void show_list(struct node* p_list, char* msg); 

void destroy_list(struct node* p_list); 

int main(void){
    struct node* p_list = NULL; 
    int data; 
    int status; 
    int length; 

    p_list = create_list(); 
    assert(p_list != NULL); 

    assert(get_start(p_list, &data) == LIST_EMPTY); 
    assert(pop_start(p_list, &data) == LIST_EMPTY); 
    assert(get_end(p_list, &data) == LIST_EMPTY); 
    assert(pop_end(p_list, &data) == LIST_EMPTY); 
    assert(remove_start(p_list) == LIST_EMPTY); 
    assert(remove_end(p_list) == LIST_EMPTY); 
    assert(get_length(p_list) == 0); 
    assert(is_list_empty(p_list) == TRUE); 
    puts("testing, get_start(), pop_start(), get_end(), pop_end(), remove_start(), remove_end() on empty list...OK"); 
    puts("testing, get_length() on empty list ... ok ");
    puts("testing, is_list_empty() on empty list ... ok"); 
    show_list(p_list, "testing, empty list"); 

    for(data = 0; data <= 40; data = data + 10)
        insert_start(p_list, data); 

    show_list(p_list, "testing, insert_start()"); 

    for(data = 50; data <= 100; data = data + 10)
        insert_end(p_list, data); 

    show_list(p_list, "testing, insert_end()"); 

    puts("testing, insert_after() for false case"); 
    status = insert_after(p_list, -300, 500); 
    assert(status == LIST_INVALID_DATA); 
    puts("testing, insert_after() false case... ok"); 

    puts("testing insert_before() for false case"); 
    status = insert_before(p_list, 8976, 500); 
    assert(status == LIST_INVALID_DATA); 
    puts("testing, insert_before() false case ... ok"); 

    puts("testing insert_after() and insert_before() for valid data"); 
    status = insert_after(p_list, 0, 1000); 
    assert(status == SUCCESS); 
    status = insert_before(p_list, 0, 2000); 
    assert(status == SUCCESS); 

    show_list(p_list, "test, insert_after(), insert_before()... ok"); 

    status = get_start(p_list, &data); 
    assert(status == SUCCESS); 
    printf("START OF LIST = %d\n", data); 
    show_list(p_list, "showing list after get_start()"); 

    status = get_end(p_list, &data); 
    assert(status == SUCCESS); 
    printf("END OF LIST = %d\n", data); 
    show_list(p_list, "showing list after get_end()"); 

    status = pop_start(p_list, &data); 
    assert(status == SUCCESS); 
    printf("START OF LIST = %d\n", data); 
    show_list(p_list, "showing list after pop_start()"); 

    status = pop_end(p_list, &data); 
    assert(status == SUCCESS); 
    printf("END OF LIST = %d\n", data); 
    show_list(p_list, "showing list after pop_end()"); 

    status = remove_start(p_list); 
    assert(status == SUCCESS); 
    show_list(p_list, "showing list after remove_start()"); 

    status = remove_end(p_list); 
    assert(status == SUCCESS); 
    show_list(p_list, "showing list after remove_end()"); 

    puts("testing, get_start(), pop_start(), get_end(), pop_end(), remove_start(), remove_end() on non-empty list...OK"); 

    length = get_length(p_list); 
    printf("length = %d\n", length); 

    puts("testing remove_data() for false case"); 
    status = remove_data(p_list, 1234); 
    assert(status == LIST_INVALID_DATA); 
    puts("testing remove data for false case ... ok"); 

    puts("testing remove_data() for success case"); 
    status = remove_data(p_list, 0); 
    assert(status == SUCCESS); 
    puts("testing remove data for success case ... ok"); 
    show_list(p_list, "showing list after removing 0"); 

    assert(is_list_empty(p_list) == FALSE); 
    puts("testing, is_list_empty() for non-empty list...ok"); 

    destroy_list(p_list); 
    p_list = NULL;

    puts("exiting from application:SUCCESS"); 
    return (EXIT_SUCCESS); 
}

struct node* create_list(void)
{
    struct node* p_list = NULL; 

    p_list = (struct node*)malloc(sizeof(struct node)); 
    if(p_list == NULL)
    {
        puts("AllocationError:malloc() failed"); 
        exit(EXIT_FAILURE); 
    }

    p_list->data = 0; 
    p_list->next = NULL; 
    p_list->prev = NULL; 

    return (p_list); 
}

void insert_start(struct node* p_list, int new_data)
{
    struct node* p_new_node = NULL; 

    p_new_node = (struct node*)malloc(sizeof(struct node)); 
    if(p_new_node == NULL)
    {
        puts("AllocationError:Error in allocating memory"); 
        exit(EXIT_FAILURE); 
    }

    p_new_node->data = new_data; 
    p_new_node->prev = p_list; 
    p_new_node->next = p_list->next; 
    if(p_list->next != NULL)
        p_list->next->prev = p_new_node; 
    p_list->next = p_new_node;
}

void insert_end(struct node* p_list, int new_data)
{
    struct node* run = NULL; 

    run = p_list; 
    while(run->next != NULL)
        run = run->next; 

    run->next = (struct node*)malloc(sizeof(struct node)); 
    if(run->next == NULL)
    {
        puts("AllocationError:Error in allocating memory"); 
        exit(EXIT_FAILURE); 
    }

    run->next->data = new_data; 
    run->next->prev = run; 
    run->next->next = NULL; 
}

int insert_after(struct node* p_list, int e_data, int new_data)
{
    struct node* e_node = NULL; 
    struct node* p_new_node = NULL; 

    e_node = p_list->next; 
    while(e_node != NULL)
    {
        if(e_node->data == e_data)
            break; 
        e_node = e_node->next; 
    }

    if(e_node == NULL)
        return (LIST_INVALID_DATA); 

    p_new_node = (struct node*)malloc(sizeof(struct node)); 
    if(p_new_node == NULL)
    {
        puts("AllocationError:malloc() failed"); 
        exit(EXIT_FAILURE); 
    }

    p_new_node->data = new_data; 
    p_new_node->next = e_node->next; 
    p_new_node->prev = e_node; 
    if(e_node->next != NULL)
        e_node->next->prev = p_new_node; 
    e_node->next = p_new_node; 

    return (SUCCESS); 
}

int insert_before(struct node* p_list, int e_data, int new_data)
{
    struct node* e_node = NULL; 
    struct node* p_new_node = NULL; 

    e_node = p_list->next; 
    while(e_node != NULL)
    {
        if(e_node->data == e_data)
            break; 
        e_node = e_node->next; 
    }

    if(e_node == NULL)
        return (LIST_INVALID_DATA); 

    p_new_node = (struct node*)malloc(sizeof(struct node)); 
    if(p_new_node == NULL)
    {
        puts("AllocationError:malloc() failed"); 
        exit(EXIT_FAILURE); 
    }

    p_new_node->data = new_data;
    p_new_node->next = e_node; 
    p_new_node->prev = e_node->prev; 
    e_node->prev->next = p_new_node; 
    e_node->prev = p_new_node; 

    return (SUCCESS); 
}

int get_start(struct node* p_list, int* p_start_data)
{
    if(p_list->next == NULL && p_list->prev == NULL)
        return (LIST_EMPTY); 
    *p_start_data = p_list->next->data; 
    return (SUCCESS); 
}

int get_end(struct node* p_list, int* p_end_data)
{
    struct node* run = NULL; 
    
    run = p_list; 
    while(run->next != NULL)
        run = run->next; 
    if(run == p_list)      
        return (LIST_EMPTY); 

    *p_end_data = run->data; 
    return (SUCCESS); 
}

int pop_start(struct node* p_list, int* p_start_data)
{
    struct node* first_node = NULL; 

    if(p_list->next == NULL && p_list->prev == NULL)
        return (LIST_EMPTY); 

    first_node = p_list->next; 
    *p_start_data = first_node->data; 

    first_node->prev->next = first_node->next; 
    if(first_node->next != NULL)
        first_node->next->prev = first_node->prev; 
    free(first_node); 
    first_node = NULL; 

    return (SUCCESS);  
}

int pop_end(struct node* p_list, int* p_end_data)
{
    struct node* run = NULL; 
    
    run = p_list; 
    while(run->next != NULL)
        run = run->next; 
    if(run == p_list)      
        return (LIST_EMPTY); 

    *p_end_data = run->data; 
    run->prev->next = NULL; 
    free(run); 
    run = NULL; 

    return (SUCCESS); 
}

int remove_start(struct node* p_list)
{
    struct node* first_node = NULL; 

    if(p_list->next == NULL && p_list->prev == NULL)
        return (LIST_EMPTY); 

    first_node = p_list->next; 
    first_node->prev->next = first_node->next; 
    if(first_node->next != NULL)
        first_node->next->prev = first_node->prev; 

    free(first_node); 
    first_node = NULL; 

    return (SUCCESS); 
}

int remove_end(struct node* p_list)
{
    struct node* run = NULL; 

    run = p_list; 
    while(run->next != NULL)
        run = run->next; 

    if(run == p_list)
        return (LIST_EMPTY); 

    run->prev->next = NULL; 
    free(run); 

    return (SUCCESS); 
}

int remove_data(struct node* p_list, int r_data)
{
    struct node* r_node = NULL; 

    r_node = p_list->next; 
    while(r_node != NULL)
    {
        if(r_node->data == r_data)
            break; 
        r_node = r_node->next; 
    }

    if(r_node == NULL)
        return (LIST_INVALID_DATA); 

    r_node->prev->next = r_node->next; 
    if(r_node->next != NULL)
        r_node->next->prev = r_node->prev; 

    free(r_node); 
    r_node = NULL; 

    return (SUCCESS); 
}

int find(struct node* p_list, int f_data)
{
    struct node* run = NULL; 

    run = p_list->next; 
    while(run != NULL)
    {
        if(run->data == f_data)
            break; 
        run = run->next; 
    }

    return (run != NULL); 
}

int get_length(struct node* p_list)
{
    int n = 0; 
    struct node* run = NULL; 

    run = p_list->next; 
    while(run != NULL)
    {
        ++n; 
        run = run->next; 
    }

    return (n); 
}

int is_list_empty(struct node* p_list)
{
    return (p_list->prev == NULL && p_list->next == NULL); 
}

void show_list(struct node* p_list, char* msg)
{
    struct node* run = NULL; 

    if(msg)
        puts(msg); 

    printf("[START]<->"); 
    run = p_list->next; 
    while(run != NULL)
    {
        printf("[%d]<->", run->data); 
        run = run->next; 
    }
    puts("[END]"); 
}

void destroy_list(struct node* p_list)
{
    struct node* run = NULL; 
    struct node* run_next = NULL; 

    run = p_list; 
    while(run != NULL)
    {
        run_next = run->next; 
        free(run); 
        run = run_next; 
    }
}