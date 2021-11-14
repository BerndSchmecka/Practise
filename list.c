#include <stdio.h>
#include <stdlib.h>

typedef struct element *list;
struct element {
    int value;
    list next;
};

void append(list *lp, int n){
    list e = (list)malloc(sizeof(struct element));
    e->value = n;
    e->next = NULL;

    list tmp = (*lp);
    while(tmp->next != NULL){
        tmp = tmp->next;
    }

    tmp->next = e;
}

int main(void){
    list l = (list)malloc(sizeof(struct element));
    for (int i = 1; i <= 12; i++){
        append(&l, i);
    }

    printf("Liste l: ");
    while(l != NULL){
        printf("%d -> ", l->value);
        l = l->next;
    }
    printf("End of List\n");

    free(l);
    return 0;
}