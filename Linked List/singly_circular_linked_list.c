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
    struct node* next;  
}; 

/* INTERFACE FUNCTIONS */
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

/* HELPER FUNCTIONS */
void generic_insert(struct node* prev_node, struct node* new_node); 
void generic_delete(struct node* delete_node, struct node* prev_to_delete_node); 

void get_last_and_its_prev_node(
    struct node* p_list, 
    struct node** pp_last_node, 
    struct node** pp_second_to_last_node
); 

void get_node_and_its_prev_node_by_data(
    struct node* p_list, 
    int f_data, 
    struct node** pp_node, 
    struct node** pp_prev_node
); 

struct node* get_node(int new_data); 
void* xmalloc(size_t number_of_bytes); 

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

    p_list = get_node(0); 
    p_list->next = p_list; 

    return (p_list); 
}

void insert_start(struct node* p_list, int new_data)
{
    generic_insert(p_list, get_node(new_data)); 
}

void insert_end(struct node* p_list, int new_data)
{
    struct node* last_node = NULL; 
    struct node* second_to_last_node = NULL; 

    if(p_list->next == p_list)
        last_node = p_list; 
    else 
        get_last_and_its_prev_node(p_list, &last_node, &second_to_last_node); 

    generic_insert(last_node, get_node(new_data)); 
}

int insert_after(struct node* p_list, int e_data, int new_data)
{
    struct node* e_node = NULL; 
    struct node* e_node_prev = NULL; 

    get_node_and_its_prev_node_by_data(p_list, e_data, &e_node, &e_node_prev);
    if(e_node == NULL)
        return (LIST_INVALID_DATA); 
    generic_insert(e_node, get_node(new_data));
    return (SUCCESS) ; 
}

int insert_before(struct node* p_list, int e_data, int new_data)
{
    struct node* e_node = NULL; 
    struct node* e_node_prev = NULL; 

    get_node_and_its_prev_node_by_data(p_list, e_data, &e_node, &e_node_prev);
    if(e_node == NULL)
        return (LIST_INVALID_DATA); 
    generic_insert(e_node_prev, get_node(new_data));
    return (SUCCESS) ; 
}

int get_start(struct node* p_list, int* p_start_data)
{
    if(p_list->next == p_list)
        return (LIST_EMPTY); 
    *p_start_data = p_list->next->data; 
    return (SUCCESS); 
}

int get_end(struct node* p_list, int* p_end_data)
{
    struct node* run = NULL; 

    if(p_list->next == p_list)
        return (LIST_EMPTY); 

    for(run = p_list->next; run->next != p_list; run = run->next)
        ; 

    *p_end_data = run->data; 
    return (SUCCESS); 
}

int pop_start(struct node* p_list, int* p_start_data)
{
    if(p_list->next == p_list)
        return (LIST_EMPTY); 
    *p_start_data = p_list->next->data; 
    generic_delete(p_list->next, p_list); 
    return (SUCCESS); 
}

int pop_end(struct node* p_list, int* p_end_data)
{
    struct node* last_node = NULL; 
    struct node* second_to_last_node = NULL; 

    if(p_list->next == p_list)
        return (LIST_EMPTY); 

    get_last_and_its_prev_node(p_list, &last_node, &second_to_last_node); 
    *p_end_data = last_node->data; 
    generic_delete(last_node, second_to_last_node); 

    return (SUCCESS); 
}

int remove_start(struct node* p_list)
{
    if(p_list->next == p_list)
        return (LIST_EMPTY); 
    generic_delete(p_list->next, p_list); 
    return (SUCCESS); 
}

int remove_end(struct node* p_list)
{
    struct node* last_node = NULL; 
    struct node* second_to_last_node = NULL; 
    
    if(p_list->next == p_list)
        return (LIST_EMPTY); 
     if(p_list->next == p_list)
        return (LIST_EMPTY); 

    get_last_and_its_prev_node(p_list, &last_node, &second_to_last_node); 
  
    generic_delete(last_node, second_to_last_node); 

    return (SUCCESS); 
}

int remove_data(struct node* p_list, int r_data)
{
    struct node* r_node = NULL; 
    struct node* r_node_prev = NULL; 

    get_node_and_its_prev_node_by_data(p_list, r_data, &r_node, &r_node_prev); 
    if(r_node == NULL && r_node_prev == NULL)
        return (LIST_INVALID_DATA); 
    generic_delete(r_node, r_node_prev); 

    return (SUCCESS); 
}

int find(struct node* p_list, int f_data)
{
    struct node* run = NULL; 

    for(run = p_list->next; run != p_list; run = run->next)
        if(run->data == f_data)
            return (TRUE); 

    return (FALSE); 
}

int get_length(struct node* p_list)
{
    int n = 0; 
    struct node* run = NULL; 

    for(run = p_list->next; run != p_list; run = run->next)
        ++n; 

    return (n); 
}

int is_list_empty(struct node* p_list)
{
    return (p_list->next == p_list); 
}

void show_list(struct node* p_list, char* msg)
{
    struct node* run = NULL; 

    if(msg)
        puts(msg); 

    printf("[START]->"); 
    for(run = p_list->next; run != p_list; run = run->next)
        printf("[%d]->", run->data); 
    puts("[END]"); 
}

void destroy_list(struct node* p_list)
{
    struct node* run = NULL; 
    struct node* run_next = NULL;

    for(run = p_list->next; run != p_list; run = run_next)
    {
        run_next = run->next; 
        free(run); 
    }

    free(p_list); 
    p_list = NULL; 
}

void generic_insert(struct node* prev_node, struct node* new_node)
{
    new_node->next = prev_node->next; 
    prev_node->next = new_node; 
}

void generic_delete(struct node* delete_node, struct node* prev_to_delete_node)
{
    prev_to_delete_node->next = delete_node->next; 
    free(delete_node); 
    delete_node = NULL;  
}

void get_last_and_its_prev_node(
    struct node* p_list, 
    struct node** pp_last_node, 
    struct node** pp_second_to_last_node
)
{
    struct node* p_run = NULL;
    struct node* p_run_prev = NULL; 

    if(p_list->next != p_list)
    {
        p_run = p_list->next; 
        p_run_prev = p_list;  
        while(p_run->next != p_list)
        {
            p_run_prev = p_run; 
            p_run = p_run->next; 
        }
    }

    *pp_last_node = p_run; 
    *pp_second_to_last_node = p_run_prev; 
}

void get_node_and_its_prev_node_by_data(
    struct node* p_list, 
    int f_data, 
    struct node** pp_node, 
    struct node** pp_prev_node
)
{
    struct node* p_run = NULL;
    struct node* p_run_prev = NULL; 

    if(p_list->next != p_list)
    {
        p_run = p_list->next; 
        p_run_prev = p_list;  
        while(p_run != p_list)
        {
            if(p_run->data == f_data)
                break; 
            p_run_prev = p_run; 
            p_run = p_run->next; 
        }

        if(p_run == p_list)
        {
            p_run = NULL; 
            p_run_prev = NULL; 
        }
    }

    *pp_node = p_run; 
    *pp_prev_node = p_run_prev; 
}

struct node* get_node(int new_data)
{
    struct node* new_node = NULL; 

    new_node = (struct node*)xmalloc(sizeof(struct node)); 
    new_node->data = new_data; 
    new_node->next = NULL; 

    return (new_node); 
}

void* xmalloc(size_t number_of_bytes)
{
    void* ptr = NULL; 

    ptr = malloc(number_of_bytes); 
    if(ptr == NULL)
    {
        puts("AllocationError:malloc() failed"); 
        exit(EXIT_FAILURE); 
    }

    return (ptr); 
}