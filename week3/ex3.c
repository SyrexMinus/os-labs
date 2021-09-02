#include <stdio.h>
#include <stdlib.h>

#define LIST_SIZE 10


struct node {
    int data;
    struct node * next;
};

void print_list(struct node * linked_list) {
    if(linked_list) {
        struct node * current_node = linked_list;
        printf("%d ", current_node->data);
        while(current_node->next) {
            current_node = current_node->next;
            printf("%d ", current_node->data);
        }
    }
    printf("\n");
}

void insert_node(struct node * new_node, struct node * prev_node) {
    struct node * after_new_node = prev_node->next;
    prev_node->next = new_node;
    new_node->next = after_new_node;
}

int delete_node(struct node * head, struct node * del_node) {
    /* returns 0 if deletion was successful
     * returns 1 if del_node is not in list */
    struct node * current_node = head;
    while(current_node->next && current_node->next != del_node) {
        current_node = current_node->next;
    }
    if(!current_node->next) {
        return 1;
    }
    current_node->next = del_node->next;

    return 0;
}

int main() {
    struct node head_node;
    head_node.data = -1;

    struct node * linked_list = &head_node;

    struct node * last_node = &head_node;
    struct node * fifth_node;
    for(int i = 0; i < LIST_SIZE-1; i++) {
        struct node * new_node = (struct node *) malloc(sizeof(struct node));
        new_node->data = i;
        last_node->next = new_node;
        last_node = last_node->next;

        if(i==3) {
            fifth_node = new_node;
        }
    }
    last_node->next = NULL;

    print_list(linked_list);

    struct node new_node;
    new_node.data = 42;
    insert_node(&new_node, fifth_node);

    print_list(linked_list);

    delete_node(linked_list, &new_node);

    print_list(linked_list);

    return 0;
}
