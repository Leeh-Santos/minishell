# include <stdio.h>
# include <stdlib.h>

typedef struct node
{
    char *data;
    int index;
    struct node *next;

}t_node;

t_node  *node(void){
    static t_node node;
    return (&node);
}

void insert(char *data, t_node **head, int index){

    
    t_node *node = malloc(sizeof(t_node));
    node->data = data;
    node->next = NULL;
    node->index = index;

    t_node *tmp = *head;
    if (!tmp){
        *head = node;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = node;
    
}


int main(){

    int x, i = 0;
    char *data;
    struct node *head = NULL;
    
    printf("manda o tamanho do lista");
    scanf("%d", &x);

    while(i < x){
        printf("input data for node %d : ", i + 1);
        scanf("%s", data);
        insert(data, &head, i);
        i++;
    }

    t_node *tmp1 = head;

   // printf("%d",tmp1->data);

    printf("\n\n printado lista \n\n");
    while (tmp1){
        printf("%s -> index %d  ", tmp1->data, tmp1->index);
        tmp1 = tmp1->next;
    }

   
    return 0;
}   