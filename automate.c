#include "automate.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct node
{
    char* id;
    int posx;
    int posy;
    char* label;
    char* color;
    char* bgcolor;
    int size;
    char* init;
    char* final;
};

struct edge{
    char* idfrom;
    char* idto;
    char* label;
    char* path;
    char* color;
    int posx;
    int posy;
};

struct svg{
    struct node* head;
    struct svg* next;
};

struct svg* casvg;
struct node* currentNode;

void createNode(char* id){
    if(!currentNode){
        currentNode = (node*) malloc(sizeof(node));
    }
    currentNode->id = id;
}

void initNode(node* n){
    if(!n->color)n->color = "BLACK";
    if(!n->bgcolor)n->bgcolor = "WHITE";
    if(!n->init)n->init = "WEST";
    if(!n->final)n->final = "EAST";
    if(!n->posx)n->posx = 0;
    if(!n->posy)n->posy = 0;
    if(!n->size)n->size = 1;
    if(!n->label)n->label = n->id;
}

void createEdge(char* idfrom, char* idto){
    return;
}

void removeNode(char* id){
    return;
}

void removeEdge(char* idfrom, char* idto){
    return;
}

void move(int dx, int dy){
    return;
}

void moveWID(char* id, int dx, int dy){
    return;
}

void moveWIDs(char** tab, int dx, int dy){
    return;
}

void renameObject(char* oldid, char* newid){
    return;
}

void editNode(char* id){
    return;
}

void editEdge(char* idfrom, char* idto){
    return;
}

void dump(){
    printf("Nodes:\n");
    while(casvg){
        printf("ID: %s\n", casvg->head->id);
        printf("Color: %s\n", casvg->head->color);
        printf("Background color: %s\n", casvg->head->bgcolor);
        printf("X: %d\n", casvg->head->posx);
        printf("Y: %d\n", casvg->head->posy);
        printf("Label: %s\n", casvg->head->label);
        printf("Size: %d\n", casvg->head->size);
        printf("Final: %s\n", casvg->head->final);
        printf("Initial: %s\n", casvg->head->init);
        printf("========\n");
        casvg = casvg->next;
    }
    printf("Edges:\n");
    return;
}

void dumpSVG(char* name){
    printf("Nom du fichier: %s.svg \n",name);
    return;
}

void setLabel(char* label){
    if(!currentNode){
        currentNode = (node*) malloc(sizeof(node));
    }
    currentNode->label = label;
    return;
}

void setPosition(int x, int y){
    if(!currentNode){
        currentNode = (node*) malloc(sizeof(node));
    }
    currentNode->posx = x;
    currentNode->posy = y;
    return;
}

void setColor(char* color){
    if(!currentNode){
        currentNode = (node*) malloc(sizeof(node));
    }
    currentNode->color = color;
    return;
}

void setBackgroundColor(char* color){
    if(!currentNode){
        currentNode = (node*) malloc(sizeof(node));
    }
    currentNode->bgcolor = color;
    return;
}

void setSize(int s){
    if(!currentNode){
        currentNode = (node*) malloc(sizeof(node));
    }
    currentNode->size = s;
    return;
}

void setInitial(char* dir){
    if(!currentNode){
        currentNode = (node*) malloc(sizeof(node));
    }
    currentNode->init = dir;
    return;
}

void setFinal(char* dir){
    if(!currentNode){
        currentNode = (node*) malloc(sizeof(node));
    }
    currentNode->final = dir;
    return;
}

void setNode(){
    initNode(currentNode);
    svg* newsvg = (svg*) malloc(sizeof(svg));
    newsvg->next = NULL;
    newsvg->head = currentNode;
    if(!casvg){
        casvg = newsvg;
    }else{
        svg* currentsvg = casvg;
        while(currentsvg->next != NULL){
            currentsvg = currentsvg->next;
        }
        currentsvg->next = newsvg;
    }
    currentNode = NULL;
    /*
    printf("%s\n", currentNode->color);
    printf("%s\n", currentNode->bgcolor);
    printf("%s\n", currentNode->id);
    printf("%d\n", currentNode->posx);
    printf("%d\n", currentNode->posy);
    printf("%s\n", currentNode->label);
    printf("%d\n", currentNode->size);
    printf("%s\n", currentNode->final);
    printf("%s\n", currentNode->init);*/
    return;
}
