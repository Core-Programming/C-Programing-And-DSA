#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define TRUE 1
#define FALSE -1

#define KEY 10000
#define BUCKET_SIZE 1000

typedef struct node node_t;
typedef node_t list_t;
typedef int status_t;
typedef struct hash_queue hash_queue_t;
typedef unsigned long long int index_t;
typedef unsigned long long int key_t;

struct node{
    key_t key;
    node_t* next;
    node_t* prev;
};

struct hash_queue{
    node_t** p_list_array;
    size_t bucket_size;
};

//Hash Queue interface functions
hash_queue_t* create_hash_queue(size_t bucket_size);
void add_key(hash_queue_t* hash_queue, key_t key);
void show_hash_queue(hash_queue_t* hash_queue);
status_t search_key(hash_queue_t* hash_queue, key_t key);
status_t remove_key(hash_queue_t* hash_queue, key_t key);
void destroy_hash_queue(hash_queue_t* hash_queue);

// Hash Queue Helper function
index_t hash(key_t key, size_t bucket_size);

// Linked List Helper function
static void generic_insert(list_t* p_beg, list_t* p_mid, list_t* p_end);
static list_t* create_list();
static list_t* get_node(key_t key);
static void* xmalloc(size_t size_in_bytes);
static list_t* find_search_node(list_t* list, key_t key);
static status_t generic_delete(list_t* p_beg, list_t* p_mid, list_t* p_end);

// Linked List interface Function 
void insert_end(node_t* list, key_t key);
void show_list(list_t* list);
status_t search_node(list_t* list, key_t key);
status_t remove_node(list_t* list, key_t key);
static void destroy_list(list_t** list);

int main(void){
    hash_queue_t* hash_queue = NULL;
    status_t status;
    key_t key[KEY];

    hash_queue = create_hash_queue(BUCKET_SIZE);
    srand(time(0));

    for(index_t index = 0; index < KEY; ++index)
        key[index] = rand();

    for(index_t index = 0; index < KEY; ++index)
        add_key(hash_queue, key[index]);

    show_hash_queue(hash_queue);

    printf("\nHash Queue Data Searching ...\n");
    for(index_t index = 0; index < KEY; ++index){
        status = search_key(hash_queue, key[index]);
        if(status == TRUE)
            printf("KEY = [%llu] is present in Hash_Queue\n", key[index]);
        else    
            printf("KEY = [%llu] is not present in Hash_Queue\n", key);
    }

    for(index_t index = 0; index < KEY; ++index){
        key_t key = rand();
        status = search_key(hash_queue, key);
        if(status == TRUE)
            printf("KEY = [%llu] is Rare in Hash_Queue\n", key);
    }

    printf("\nHash Queue Node Removing..\n");
    for(index_t index = 0; index < KEY; ++index){
        status = remove_key(hash_queue, key[index]);

        if(status == TRUE)
            printf("KEY = [%llu] Removed\n", index);
        else
            printf("KEY = [%llu] is not Removed\n", index);
    }

    printf("\nHash Queue Display\n");
    show_hash_queue(hash_queue);

    printf("\nHash Queue Destroyed\n");
    destroy_hash_queue(hash_queue);

    puts("show hash_Queue");
    show_hash_queue(hash_queue);

    puts("succeded");
    return (0);
}

static void destroy_list(list_t** list){

    list_t* ptrArray = NULL;
    list_t* run_prev = NULL;
    list_t* run = NULL;
    ptrArray = *list;
    
    run = ptrArray->next;

    while(run != ptrArray){
        run_prev = run;
        free(run_prev);
        run = run->next;
    }
    free(*list);
    *list = NULL;
}

void destroy_hash_queue(hash_queue_t* hash_queue){

    for(index_t index = 0; index < hash_queue->bucket_size; ++index){
        destroy_list(&hash_queue->p_list_array[index]);
    }
    hash_queue->p_list_array = NULL;
}
static list_t* find_search_node(list_t* list, key_t key){
    list_t* run = NULL;
    run = list->next;
    while(run != list){
        if(run->key == key)
            return run;

        run = run->next;
    }
    return NULL;
}
status_t generic_delete(list_t* p_beg, list_t* p_mid, list_t* p_end){

    p_beg->next = p_end;
    p_end->prev = p_beg;

    free(p_mid);
    p_mid = NULL;

    return(TRUE);
}
status_t remove_node(list_t* list, key_t key){
    list_t* r_node = NULL;
    r_node = find_search_node(list, key);

    if(r_node != NULL){
        return(generic_delete(r_node->prev, r_node, r_node->next));
    }
    return(FALSE);
}
status_t remove_key(hash_queue_t* hash_queue, key_t key){
    status_t status = FALSE;
    for(index_t index = 0; index < hash_queue->bucket_size; ++index){
        status = remove_node(hash_queue->p_list_array[index], key);
        if(status == TRUE)
            return(TRUE);
    }
    return (FALSE);
}

status_t search_node(list_t* list, key_t key){

    list_t* run = NULL;
    status_t status = FALSE;

    run = list->next;

    while(run != list){
        if(run->key == key)       
            return TRUE;
        run = run->next;
    }
    return FALSE;
}

status_t search_key(hash_queue_t* hash_queue, key_t key){
    status_t status = FALSE;

    for(index_t index = 0; index < hash_queue->bucket_size; ++index){
        status = search_node(hash_queue->p_list_array[index], key);

        if(status == TRUE)
            return status;
    }
    return status;
}

void show_list(list_t* list){
    list_t* run = NULL;

    run = list->next;
    printf("[HEAD]->");
    while(run != list){
        
        printf("[%llu]->", run->key);
        run = run->next;
    }
    printf("[END]\n");
}

index_t hash(key_t key, size_t bucket_size){
    return (key % bucket_size);
}
void show_hash_queue(hash_queue_t* hash_queue){

    if((hash_queue->p_list_array) == NULL){
        puts("list is empty");
        return;
    }

    for(index_t index = 0; index < hash_queue->bucket_size; ++index){
        printf("Queue bucket[%llu]\t\t", index);
        show_list(hash_queue->p_list_array[index]);
    }
}

void insert_end(node_t* list, key_t key){
    generic_insert(list->prev, get_node(key), list);
}

static void generic_insert(list_t* p_beg, list_t* p_mid, list_t* p_end){

    p_mid->next = p_end;
    p_mid->prev = p_beg;
    p_beg->next = p_mid;
    p_end->prev = p_mid; 
}

void add_key(hash_queue_t* hash_queue, key_t key){
    index_t index;
    index = hash(key, hash_queue->bucket_size); 
    insert_end(hash_queue->p_list_array[index], key);
}

hash_queue_t* create_hash_queue(size_t bucket_size){

    hash_queue_t* hash_queue = NULL;
    hash_queue = (hash_queue_t*)malloc(sizeof(hash_queue_t));
    assert(hash_queue !=NULL);
    hash_queue->bucket_size = bucket_size;
    hash_queue->p_list_array = (node_t**)malloc(bucket_size * sizeof(node_t*));
    assert(hash_queue->p_list_array != NULL);

    //Adding head node to each list 

    for(index_t index = 0; index < bucket_size; ++index){
        hash_queue->p_list_array[index] = create_list();    
    }
    return hash_queue;
}

static list_t* create_list(){
    list_t* list_node = get_node(0);
    return list_node;
}

static list_t* get_node(key_t key){
    list_t* new_node = NULL;
    new_node = (list_t*)xmalloc(sizeof(list_t));
    new_node->key = key;
    new_node->next = new_node;
    new_node->prev = new_node;
    return new_node;
}

static void* xmalloc(size_t size_in_byte){
    void* v_ptr = NULL;
    v_ptr = malloc(size_in_byte);
    assert(v_ptr != NULL);
    return v_ptr;
}