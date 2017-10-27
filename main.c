#include <stdio.h>
#include <mem.h>
#include "linkedlists.h"


typedef struct DFA_MATRIX {
    int Itable[3];
    int Ftable[3];
    int transition[3][2];
} DFA_MATRIX;


typedef struct DFA_LINKEDLIST {
    int Itable[3];
    int Ftable[3];
    node* transition[3];
} DFA_LINKEDLIST;

typedef struct NFA_LINKEDLIST {
    int Itable[3];
    int Ftable[3];
    nodeN* transition[3];
}NFA_LINKEDLIST;

DFA_MATRIX dfa1;
DFA_LINKEDLIST dfa2;
NFA_LINKEDLIST nfa1;

int f(char);
int checkMatrix(char*,DFA_MATRIX);
int transitionMatrix(DFA_MATRIX, char, int);
int checkLinkedList(char*,DFA_LINKEDLIST);
int transitionLinkedList(DFA_LINKEDLIST, char, int);
int checkNFA(char*,NFA_LINKEDLIST, int, int);


int main() {

    dfa1.Itable[0]=1;
    dfa1.Itable[1]=0;
    dfa1.Itable[2]=0;

    dfa1.Ftable[0]=0;
    dfa1.Ftable[1]=0;
    dfa1.Ftable[2]=1;

    dfa1.transition[0][0]=1;
    dfa1.transition[0][1]=-1;
    dfa1.transition[1][0]=2;
    dfa1.transition[1][1]=1;
    dfa1.transition[2][0]=2;
    dfa1.transition[2][1]=1;

    dfa2.Itable[0]=1;
    dfa2.Itable[1]=0;
    dfa2.Itable[2]=0;

    dfa2.Ftable[0]=0;
    dfa2.Ftable[1]=0;
    dfa2.Ftable[2]=1;

    int transition00[2] = {f('a'),1};
    int transition10[2] = {f('a'),2};
    int transition11[2] = {f('b'),1};
    int transition20[2] = {f('a'),2};
    int transition21[2] = {f('b'),1};
    dfa2.transition[0]=create(transition00,NULL);
    dfa2.transition[1]=create(transition10,NULL);
    append(dfa2.transition[1],transition11);
    dfa2.transition[2]=create(transition20,create(transition21,NULL));


    nfa1.Itable[0]=1;
    nfa1.Itable[1]=0;
    nfa1.Itable[2]=0;

    nfa1.Ftable[0]=0;
    nfa1.Ftable[1]=0;
    nfa1.Ftable[2]=1;

    int Ntranistion0a0[1] = {1};
    int Ntransition1a0[1]={2};
    int Ntransition1a1[1]={1};
    int Ntransition1b0[1]={1};
    int Ntransition2a0[1]={2};
    int Ntransition2b0[1]={1};
    node* node0a = create(Ntranistion0a0,NULL);
    nfa1.transition[0]=createN(f('a'),node0a,NULL);
    node* node1a = create(Ntransition1a0,create(Ntransition1a1,NULL));
    node* node1b = create(Ntransition1b0,NULL);
    nfa1.transition[1]=createN(f('a'),node1a,createN(f('b'),node1b,NULL));
    node* node2a = create(Ntransition2a0,NULL);
    node* node2b = create(Ntransition2b0,NULL);
    nfa1.transition[2]=createN(f('a'),node2a,createN(f('b'),node2b,NULL));





    char* word1 = "ab";
    char* word2 = "aaba";

    printf("\n%i",checkMatrix(word1,dfa1));
    printf("\n%i",checkMatrix(word2,dfa1));

    printf("\n%i",checkLinkedList(word1,dfa2));
    printf("\n%i",checkLinkedList(word2,dfa2));

    printf("\n%i",checkNFA(word1,nfa1,0,0));
    printf("\n%i",checkNFA(word2,nfa1,0,0));





}

int f(char c){
    if (c == 'a')return 0;
    if (c == 'b') return 1;
    return -1;
}



int transitionMatrix (DFA_MATRIX dfa,char c,int state){
    return dfa.transition[state][f(c)];
}

int checkMatrix(char* string,DFA_MATRIX dfa){
    int i;
    int flag;
    int state ;
    int x;
    for (int j = 0; j < 3; ++j) {
        if (dfa.Itable[j]==1){
            i = 0;
            flag = 1;
            state = j;
            while (string[i]!= '\0'){
                x = transitionMatrix(dfa,string[i],state);
                if (x >= 0) {
                    state = x;
                    i++;
                } else {
                    flag = -1;
                    break;
                }
            }
            if (flag == 1 && dfa.Ftable[state] == 1){
                return 1;
            }
        }
    }
    return -1;

}

int transitionLinkedList(DFA_LINKEDLIST dfa,char c,int state){
    node* result = search(dfa.transition[state],f(c));
    if(result == NULL){
        return -1;
    }
    else {
        return result->data[1];
    }
}

int checkLinkedList(char* string,DFA_LINKEDLIST dfa){
    int i;
    int flag;
    int state ;
    int x;
    for (int j = 0; j < 3; ++j) {
        if (dfa.Itable[j]==1){
            i = 0;
            flag = 1;
            state = j;
            while (string[i]!= '\0'){
                x = transitionLinkedList(dfa,string[i],state);
                if (x >= 0) {
                    state = x;
                    i++;
                } else {
                    flag = -1;
                    break;
                }
            }
            if (flag == 1 && dfa.Ftable[state] == 1){
                return 1;
            }
        }
    }
    return -1;

}

int checkNFA(char* string,NFA_LINKEDLIST nfa,int i,int state){
//    printf("%i",i,state);
    if (string[i]=='\0'){
        return nfa.Ftable[state];
    }
    nodeN *tempN = searchN(nfa.transition[state], f(string[i]));
    node* temp;
    if (tempN != NULL) {
        temp = tempN->values;
    } else {
        temp = NULL;
    }
    while (temp!=NULL){

        if(checkNFA(string,nfa,i+1,temp->data[0])==1){
            return 1;
        }
        temp=temp->next;
    }
    return -1;
}


