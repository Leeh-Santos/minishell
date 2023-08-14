# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>



typedef struct node{
    char *data;
    struct node *next;
    
}t_node;

t_node *head = NULL;

void insert(char *substr)
{
    t_node *new = malloc(sizeof(t_node));
    if (!new)
        return ;
    new->data = substr;
    new->next = NULL;

    t_node *tmp = head;

    if (!tmp){
        head = new;
        return;
    }
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;

}

void transform(char *str, char *tmp, int *i) // para cada situacao
{

    int k = 0;
    int flag = 0;
     while(str[*i] && (str[*i] >= 'a' && str[*i] <= 'z')){   /// change here
        tmp[k] = str[*i];
        (*i)++;
        k++;
        flag++;
        }
        if (flag)
            tmp[k] ='\0'; // add null aqui ver condicao, pode ser uma flag para nao sair, criando um node extra com null
      

}

char *takeit(char *str, int *i){ // condicoes gerais

    char *tmp = malloc(999 * sizeof(char));// maloca dentro das outras ou iguala
    

    while(str[*i] && (str[*i] >= 'a' && str[*i] <= 'z')){   //veri
       if(str[*i] >= 'a' && str[*i] <= 'z'){
        transform(str, tmp, i);
       }
    }
      return tmp; 
        

}

void killspc(char *str, int *i){

    while(str[*i] && str[*i] == ' '){
        (*i)++;
    }
    /*if (str[*i] == '\0')
        return 1;*/
      
}

void chama(char *str){

    int i = 0;
    
    while(str[i]){
        killspc(str, &i);
        printf("\n---%c---\n", str[i]);
        if (str[i] == '\0')
            return ;
        insert(takeit(str, &i)); // pode colocar um if se tiver substring

    }
   
}
int main(){
 
    char *x = "             vai    seu pau   no cu           v h  v outra ve z poha   l  ";
    chama(x);

    t_node *tmp = head;

    while (tmp){
        printf("%s\n", tmp->data);
        tmp = tmp->next;
    }

    return 0;
}