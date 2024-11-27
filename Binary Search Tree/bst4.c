#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 

/* Symbolic constants */
#define SUCCESS             1 
#define TRUE                1 
#define FALSE               0 
#define BST_INVALID_DATA    2 
#define BST_EMPTY           3 
#define BST_NO_SUCCESSOR    4 
#define BST_NO_PREDECESSOR  5 

/* typedefs */
typedef int data_t; 
typedef int status_t; 

typedef struct bst_node bst_node_t; 
typedef struct bst bst_t; 

/* structure layouts */
struct bst_node{
    data_t data; 
    struct bst_node* left; 
    struct bst_node* right; 
    struct bst_node* parent; 
}; 

struct bst{
    bst_node_t* root_node; 
    size_t number_of_elements; 
}; 

/* Interface Routines */
bst_t* create_bst(void); 
status_t insert_bst(bst_t* p_bst, data_t new_data); 
status_t search_bst(bst_t* p_bst, data_t s_data);
status_t remove_bst(bst_t* p_bst, data_t r_data); 
void inorder(bst_t* p_bst); 
void preorder(bst_t* p_bst); 
void postorder(bst_t* p_bst); 
status_t get_inorder_successor(bst_t* p_bst, data_t e_data, data_t* p_succ_data); 
status_t get_inorder_predecessor(bst_t* p_bst, data_t e_data, data_t* p_pred_data); 
status_t get_max(bst_t* p_bst, data_t* p_max_data); 
status_t get_min(bst_t* p_bst, data_t* p_min_data); 
status_t destroy_bst(bst_t** pp_bst); 

/* Auxillary Routines */
static void inorder_nodelevel(bst_node_t* root_node); 
static void preorder_nodelevel(bst_node_t* root_node); 
static void postorder_nodelevel(bst_node_t* root_node); 
static bst_node_t* search_nodelevel(bst_node_t* root_node, data_t s_data);
static bst_node_t* inorder_successor_nodelevel(bst_node_t* e_node); 
static bst_node_t* inorder_predecessor_nodelevel(bst_node_t* e_node); 
static void destroy_nodelevel(bst_node_t* root_node); 

static bst_node_t* get_node(data_t new_data); 
static void* xmalloc(size_t size_in_bytes); 

int main(void){
    bst_t* p_bst = NULL; 
    data_t arr[] = {100, 50, 150, 25, 175, 65, 130, 5}; 
    data_t min_data, max_data, succ_data, pred_data; 
    status_t status; 
    size_t i; 
    

    p_bst = create_bst(); 

    for(i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i){
        status = insert_bst(p_bst, arr[i]); 
        assert(status == SUCCESS); 
    }

    puts("INORDER:"); 
    inorder(p_bst); 

    puts("PREORDER:"); 
    preorder(p_bst); 

    puts("POSTORDER:"); 
    postorder(p_bst); 

    for(i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i){
        status = search_bst(p_bst, arr[i]); 
        assert(status == TRUE);
        printf("%d is found in BST\n", arr[i]);  
    }

    status = search_bst(p_bst, -10); 
    assert(status == FALSE); 

    status = search_bst(p_bst, 61); 
    assert(status == FALSE); 

    status = search_bst(p_bst, 0); 
    assert(status == FALSE); 

    status = search_bst(p_bst, 125); 
    assert(status == FALSE);

    puts("-10, 61, 0, 125 are not in BST");  

    status = get_max(p_bst, &max_data); 
    assert(status == SUCCESS); 
    printf("MAX_DATA = %d\n", max_data); 

    status = get_min(p_bst, &min_data); 
    printf("MIN DATA = %d\n", min_data); 

    status = get_inorder_successor(p_bst, 50, &succ_data); 
    assert(status == SUCCESS); 
    printf("INORDER SUCCESSOR of 50 is %d\n", succ_data); 

    status = get_inorder_successor(p_bst, 175, &succ_data); 
    assert(status == BST_NO_SUCCESSOR); 
    puts("175 has no successor because its max val"); 

    status = get_inroder_predecessor(p_bst, 50, &pred_data); 
    assert(status == SUCCESS); 
    printf("INORDER PREDECESSOR of 50 is %d\n", pred_data); 

    status = get_inroder_predecessor(p_bst, 5, &pred_data); 
    assert(status == BST_NO_PREDECESSOR); 
    puts("INRODER PREDECESSOR of 5 does not exist because its a min val"); 

    puts("AT START OF REMOVE"); 
    inorder(p_bst); 
    for(i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i){
        status = remove_bst(p_bst, arr[i]); 
        assert(status == SUCCESS);
        printf("%d is removed from BST\n", arr[i]);
        puts("REMAINING ELEMENTS IN BST"); 
        inorder(p_bst);   
    }

    status = destroy_bst(&p_bst); 
    assert(status == SUCCESS && p_bst == NULL); 

    puts("PROGRAM ENDS SUCCESSFULLY"); 
    return (EXIT_SUCCESS); 
}

bst_t* create_bst(void){
    bst_t* p_bst = NULL; 

    p_bst = (bst_t*)xmalloc(sizeof(bst_t)); 
    p_bst->root_node = NULL;
    p_bst->number_of_elements = 0; 

    return (p_bst); 
}

status_t insert_bst(bst_t* p_bst, data_t new_data){
    bst_node_t* new_node = NULL; 
    bst_node_t* run = NULL; 

 
    if(p_bst->root_node == NULL){
        p_bst->root_node = get_node(new_data); 
        p_bst->number_of_elements += 1; 
        return (SUCCESS); 
    }

    new_node = get_node(new_data); 
    run = p_bst->root_node; 
    while(TRUE){
        if(new_data <= run->data){
            if(run->left == NULL){
                run->left = new_node; 
                run->left->parent = run; 
                break; 
            }
            else{
                run = run->left; 
            }
        }
        else{
            if(run->right == NULL){
                run->right = new_node; 
                run->right->parent = run; 
                break; 
            }
            else{
                run = run->right; 
            }
        }
    }

    p_bst->number_of_elements += 1; 
    return (SUCCESS); 

}

status_t search_bst(bst_t* p_bst, data_t s_data){
    bst_node_t* p_node = NULL; 

    p_node = search_nodelevel(p_bst->root_node, s_data); 
    return (p_node != NULL); 
}

status_t remove_bst(bst_t* p_bst, data_t r_data){
    bst_node_t* z = NULL; 
    bst_node_t* y = NULL; 

    z = search_nodelevel(p_bst->root_node, r_data); 
    if(z == NULL)
        return (BST_INVALID_DATA); 

    if(z->left == NULL){
        if(z->parent == NULL)
            p_bst->root_node = z->right; 
        else if(z->parent->left == z)
            z->parent->left = z->right; 
        else 
            z->parent->right = z->right; 
        
        if(z->right != NULL)
            z->right->parent = z->parent; 
    }
    else if(z->right == NULL){
        if(z->parent == NULL)
            p_bst->root_node = z->left; 
        else if(z->parent->left == z)
            z->parent->left = z->left; 
        else 
            z->parent->right = z->left; 
        
        z->left->parent = z->parent; 
    }
    else{
        y = z->right; 
        while(y->left != NULL)
            y = y->left; 
        
        if(y != z->right){
            y->parent->left = y->right; 
            if(y->right != NULL)
                y->right->parent = y->parent; 

            y->right = z->right; 
            y->right->parent = y; 
        }

        y->left = z->left; 
        y->left->parent = y; 

        if(z->parent == NULL)
            p_bst->root_node = y; 
        else if(z->parent->left == z)
            z->parent->left = y; 
        else 
            z->parent->right = y; 

        y->parent = z->parent;
    }

    free(z); 
    z = NULL; 

    p_bst->number_of_elements -= 1; 
    return (SUCCESS); 
}


void inorder(bst_t* p_bst){
    printf("[START]<->"); 
    inorder_nodelevel(p_bst->root_node); 
    puts("[END]"); 
}

void preorder(bst_t* p_bst){
    printf("[START]<->"); 
    preorder_nodelevel(p_bst->root_node); 
    puts("[END]"); 
}

void postorder(bst_t* p_bst){
    printf("[START]<->"); 
    postorder_nodelevel(p_bst->root_node); 
    puts("[END]"); 
}

status_t destroy_bst(bst_t** pp_bst){
    bst_t* p_bst = *pp_bst; 
    destroy_nodelevel(p_bst->root_node); 
    *pp_bst = NULL; 
    return (SUCCESS); 
}

status_t get_inorder_successor(bst_t* p_bst, data_t e_data, data_t* p_succ_data){
    bst_node_t* e_node = NULL; 
    bst_node_t* e_succ_node = NULL; 

    e_node = search_nodelevel(p_bst->root_node, e_data); 
    if(e_node == NULL) 
        return (BST_INVALID_DATA); 

    e_succ_node = inorder_successor_nodelevel(e_node); 
    if(e_succ_node == NULL)
        return (BST_NO_SUCCESSOR); 

    *p_succ_data = e_succ_node->data; 
    return (SUCCESS); 
}

status_t get_inroder_predecessor(bst_t* p_bst, data_t e_data, data_t* p_pred_data){
    bst_node_t* e_node = NULL; 
    bst_node_t* e_pred_node = NULL; 

    e_node = search_nodelevel(p_bst->root_node, e_data); 
    if(e_node == NULL)
        return (BST_INVALID_DATA); 

    e_pred_node = inorder_predecessor_nodelevel(e_node); 
    if(e_pred_node == NULL)
        return (BST_NO_PREDECESSOR);

    *p_pred_data = e_pred_node->data; 
    return (SUCCESS); 
}

status_t get_max(bst_t* p_bst, data_t* p_max_data){
    bst_node_t* run = NULL; 

    if(p_bst->root_node == NULL)
        return (BST_EMPTY); 

    run = p_bst->root_node; 
    while(run->right != NULL)
        run = run->right; 

    *p_max_data = run->data; 
    return (SUCCESS); 
}

status_t get_min(bst_t* p_bst, data_t* p_min_data){
    bst_node_t* run = NULL; 

    if(p_bst->root_node == NULL)
        return (BST_EMPTY); 

    run = p_bst->root_node; 
    while(run->left != NULL)
        run = run->left; 

    *p_min_data = run->data; 
    return (SUCCESS); 
}

static bst_node_t* search_nodelevel(bst_node_t* root_node, data_t s_data){
    bst_node_t* run = NULL; 

    run = root_node; 
    while(run != NULL){
        if(s_data == run->data)
            return (run); 
        else if(s_data < run->data)
            run = run->left; 
        else 
            run = run->right; 
    }

    return (NULL); 
}

static void inorder_nodelevel(bst_node_t* root_node){
    if(root_node != NULL){
        inorder_nodelevel(root_node->left); 
        printf("[%d]<->", root_node->data); 
        inorder_nodelevel(root_node->right); 
    }
}

static void preorder_nodelevel(bst_node_t* root_node){
    if(root_node != NULL){
        printf("[%d]<->", root_node->data); 
        preorder_nodelevel(root_node->left); 
        preorder_nodelevel(root_node->right); 
    }
}

static void postorder_nodelevel(bst_node_t* root_node){
    if(root_node != NULL){
        postorder_nodelevel(root_node->left); 
        postorder_nodelevel(root_node->right); 
        printf("[%d]<->", root_node->data); 
    }
}

static bst_node_t* inorder_successor_nodelevel(bst_node_t* p_node){
    bst_node_t* z = NULL; 
    bst_node_t* y = NULL; 
    bst_node_t* x = NULL; 

    z = p_node; 
    if(z->right != NULL){
        x = z->right; 
        while(x->left != NULL)
            x = x->left; 
        return (x); 
    }

    x = z; 
    y = x->parent; 
    while(y != NULL && x == y->right){
        x = y; 
        y = x->parent; 
    }

    return (y); 
}

static bst_node_t* inorder_predecessor_nodelevel(bst_node_t* p_node){
    bst_node_t* z = NULL; 
    bst_node_t* y = NULL; 
    bst_node_t* x = NULL; 

    z = p_node; 
    if(z->left != NULL){
        x = z->left; 
        while(x->right != NULL)
            x = x->right; 
        return (x); 
    }

    x = z; 
    y = x->parent; 
    while(y != NULL && y->left == x){
        x = y; 
        y = x->parent; 
    }

    return (y); 
}

static void destroy_nodelevel(bst_node_t* root_node){
     if(root_node != NULL){
        destroy_nodelevel(root_node->left); 
        destroy_nodelevel(root_node->right); 
        free(root_node);  
    }
}

static bst_node_t* get_node(data_t new_data){
    bst_node_t* p_new_node = NULL; 

    p_new_node = (bst_node_t*)xmalloc(sizeof(bst_node_t)); 
    p_new_node->data = new_data; 
    p_new_node->left = NULL; 
    p_new_node->right = NULL; 
    p_new_node->parent = NULL; 

    return (p_new_node); 
} 

static void* xmalloc(size_t size_in_bytes){
    void* ptr = NULL; 

    ptr = malloc(size_in_bytes); 
    if(ptr == NULL){
        puts("Error in allocating memory"); 
        exit(EXIT_FAILURE); 
    }

    return (ptr); 
}