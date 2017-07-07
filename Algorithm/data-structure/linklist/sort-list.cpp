#include <stdio.h>
#include <stdlib.h>

struct ListNode{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

void Insertion_list(ListNode *head){


}


ListNode *Create_list(FILE *fd, int n){
   
    ListNode *head;
    int t;
    for(int i=0; i<n; ++i){
        fscanf(fd, "%d", &t);
        ListNode *ln = (ListNode *)malloc(sizeof(ListNode));
        
    }
}

void Destory_list(ListNode *head){
    ListNode *tmp = head;
    //Destory link list 
    while(tmp){
        free(tmp)
        tmp = head->next;
        head = tmp;
    }
}

int main(int argc, char* argv[]){

    int n,i,t;

    ListNode *list = NULL;
    FILE *fd = fopen("input", "r+");
    while(fscanf(fd, "%d", &n) != EOF){
        ListNode *list = Create_list(n);
   
         
        Destory_list(list);
    }
    return 0;
}
