#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct node{
    int data;
    struct node *next;
};

struct node *add_to_empty(int data){
    struct node *ptr = malloc(sizeof(struct node));
    ptr->data = data;
    ptr->next = NULL;
    
    return ptr;
}

void add_at_end(struct node *head, int data){
    struct node *ptr = malloc(sizeof(struct node));
    ptr->data = data;
    ptr->next = NULL;

    struct node *temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = ptr;
}

struct node *create_ll(struct node *head){
    int n, data, i = 2;
    printf("\nEnter the number of elements that you want in your list: ");
    scanf("%d", &n);

    if(n <= 0) return head;

    printf("\nEnter the element number 1: ");
    scanf("%d", &data);
    head = add_to_empty(data);

    while(i <= n){
        printf("Enter the element number %d: ", i);
        scanf("%d", &data);
        add_at_end(head, data);
        i++;
    }

    return head;
}

void print(struct node *head){
    struct node *temp = head;
    while(temp != NULL){
        printf("%d", temp->data);
        if(temp->next != NULL){
            printf("->");
        }
        temp = temp->next;
    }
}

struct node *deletion(struct node *head, int st_pos, int last_pos, bool *ptr_bool){
    struct node *temp = head;
    int count = 0;
    while(temp != NULL){
        count++;
        temp = temp->next;
    }
    printf("\n---Deletion Results---\n\nStart Position: %d\n", st_pos);
    printf("Last Position: %d\n", last_pos);
    if(st_pos <= 0 || last_pos <= 0){
        printf("Invalid Position Input to Delete...\n*st_pos and last_pos must be greater than 0!");  
    }
    else if(st_pos > count || last_pos > count){
        printf("Invalid Position Input to Delete...\n*st_pos and last_pos must be lesser than node count!");
    }
    else if(st_pos > last_pos){
        printf("Invalid Position Input to Delete...\n*last_pos must be equal or greater than st_pos!");
    }
    else{
        if(st_pos == 1 && last_pos == 1){
            struct node *temp = head;
            head = head->next;
            free(temp);
            temp = NULL;
        }
        else if(st_pos == 1 && last_pos > 1){
            struct node *temp = head;
            while(last_pos >= 1){
                temp = head;
                head = head->next;
                free(temp);
                temp = NULL;
                last_pos--;
            }
        }
        else{
            struct node *temp = head, *temp2 = NULL, *ptr = NULL;
            int i = st_pos - 1;
            while(i > 1){
                temp = temp->next;
                i--;
            }
            ptr = temp;
            temp = temp->next;
            temp2 = temp;

            int net = (last_pos - st_pos) + 1;
            while(net >= 1){
                temp = temp2;
                temp2 = temp2->next;
                free(temp);
                temp = NULL;
                net--;
            }
            ptr->next = temp2;
        }
        *ptr_bool = true;
    }
    return head;
}

int main(){
    struct node *head = NULL;

    do{
        head = create_ll(head);
        if(head == NULL){
            printf("ENTER A VALID NUMBER!\n");
        }
    }while(head == NULL);

    printf("\nThe List Before Deletion=> ");
    print(head); printf("\n\n");

    int count = 1;
    while(true){
        int st_pos, last_pos;
        printf("---%d. Deletion---\n\nEnter First Position (Enter -1 to quit!): ", count); scanf("%d", &st_pos);
        if(st_pos == -1) break;
        printf("Enter Last Position: "); scanf("%d", &last_pos);

        bool check = false;
        bool *ptr_bool = &check;
        head = deletion(head, st_pos, last_pos, ptr_bool);

        if(*ptr_bool == true && head != NULL){
            printf("The List After Deletion No. %d=> ", count++); 
            print(head);
        }
        else if(head == NULL){
            printf("=> There is no remaining data in the list!\n\n");
            break;
        }
        printf("\n\n\n");
    }
    return 0;
}