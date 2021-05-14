#include "automate.h"
#include "drawSVG.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

struct svg* casvg;
struct svgEdge* esvg;
struct node* currentNode;
struct edge* currentEdge;
struct strList* currentStrList;
struct position* pos;

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
    if(!n->size)n->size = 30;
    if(!n->label)n->label = n->id;
}

void initEdge(edge* e){
    if(!e->color)e->color = "BLACK";
    if(!e->path)e->path = "default";
    if(!e->posx)e->posx = 0;
    if(!e->posy)e->posy = 0;
}

void createEdge(char* idfrom, char* idto){
    if(!currentEdge){
        currentEdge = (edge*) malloc(sizeof(edge));
    }
    currentEdge->idfrom = idfrom;
    currentEdge->idto = idto;
    return;
}

void removeNode(char* id){
    svg* currentNodeList = casvg;
    svg* prevNode = NULL;
    while(currentNodeList && (strcmp(currentNodeList->head->id, id) != 0 )){
        prevNode = currentNodeList;
        currentNodeList = currentNodeList->next;
    }
    if(strcmp(currentNodeList->head->id, id) == 0 ){
        if((currentNodeList->next != NULL) && (prevNode != NULL)){
            prevNode->next = currentNodeList->next;
        }else if(!prevNode && currentNodeList->next){
            casvg = currentNodeList->next;
        }else if(prevNode && !currentNodeList->next){
            prevNode->next = NULL;
        }
        free(currentNodeList);
        currentNodeList = NULL;
    }else{
        fprintf(stderr, "Error: ID not found\n");
    }
    return;
}

void removeEdge(char* idfrom, char* idto){
    svgEdge* currentEdgeList = esvg;
    svgEdge* prevEdge = NULL;
    while(currentEdgeList && ((strcmp(currentEdgeList->head->idfrom, idfrom) != 0 ) || (strcmp(currentEdgeList->head->idto, idto) != 0 ) )){
        prevEdge = currentEdgeList;
        currentEdgeList = currentEdgeList->next;
    }
    if((strcmp(currentEdgeList->head->idfrom, idfrom) == 0 ) && (strcmp(currentEdgeList->head->idto, idto) == 0 ) ){
        if((currentEdgeList->next != NULL) && (prevEdge != NULL)){
            prevEdge->next = currentEdgeList->next;
        }else if(!prevEdge && currentEdgeList->next){
            esvg = currentEdgeList->next;
        }else if(prevEdge && !currentEdgeList->next){
            prevEdge->next = NULL;
        }
        free(currentEdgeList);
    }else{
        fprintf(stderr, "Error: ID not found\n");
    }
    return;
}

void move(int dx, int dy){
    if(!pos){
        pos = (position*) malloc(sizeof(position));
    }
    pos->x = dx;
    pos->y = dy;
    return;
}

void doMove(){
    if(!currentStrList){
        svg* currentSvg = casvg;
        while(currentSvg){
            currentSvg->head->posx = currentSvg->head->posx + pos->x;
            currentSvg->head->posy = currentSvg->head->posy + pos->y;
            currentSvg = currentSvg->next;
        }
    }else{
        svg* currentSvg;
        char* currentID;
        strList* prevList;
        while(currentStrList){
            currentID = currentStrList->val;
            currentSvg = casvg;
            while((currentSvg != NULL) && (strcmp(currentSvg->head->id, currentID)!=0)){
                currentSvg = currentSvg->next;
            }
            if(strcmp(currentSvg->head->id, currentID)==0){       
                currentSvg->head->posx = currentSvg->head->posx + pos->x;
                currentSvg->head->posy = currentSvg->head->posy + pos->y;
            }else{
                fprintf(stderr,"Error: ID not found");
            }
            prevList = currentStrList;
            currentStrList = currentStrList->next;
            free(prevList);
        }
    }
    free(pos);
    pos = NULL;
    return;
}

void addToList(char* id){
    strList* list = (strList*) malloc(sizeof(strList));
    list->val = id;
    list->next = NULL;
    if(!currentStrList){
        currentStrList = list;
    }else{
        strList* strList = currentStrList;
        while(strList->next != NULL){
            strList = strList->next;
        }
        strList->next = list;
    }
    return;
}

// Rename node without change edges with the old name
void renameObject(char* oldid, char* newid){
    svg* currentNode = casvg;
    while(currentNode && currentNode->next && (strcmp(currentNode->head->id, oldid) != 0)){
        currentNode = currentNode->next;
    }
    if(strcmp(currentNode->head->id, oldid) == 0){
        currentNode->head->id = newid;
        return;
    }
    fprintf(stderr, "Error: ID not found\n");
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
    while(esvg){
        printf("ID From: %s\n", esvg->head->idfrom);
        printf("ID To: %s\n", esvg->head->idto);
        printf("Color: %s\n", esvg->head->color);
        printf("X: %d\n", esvg->head->posx);
        printf("Y: %d\n", esvg->head->posy);
        printf("Label: %s\n", esvg->head->label);
        printf("Path: %s\n", esvg->head->path);
        printf("========\n");
        esvg = esvg->next;
    }
    return;
}

void dumpSVG(char* name){
    name = name+1;
    name[strlen(name)-1] = '\0';
    printf("Nom du fichier: %s.svg \n",name);
    draw(name, casvg, esvg);
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

void setPath(char* path){
    if(!currentEdge){
        currentEdge = (edge*) malloc(sizeof(edge));
    }
    currentEdge->path = path;
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
    return;
}

void setEdge(){
    if(currentNode->label)currentEdge->label = currentNode->label;
    if(currentNode->color)currentEdge->color = currentNode->color;
    if(currentNode->posx)currentEdge->posx = currentNode->posx;
    if(currentNode->posy)currentEdge->posy = currentNode->posy;
    initEdge(currentEdge);
    svgEdge* newsvg = (svgEdge*) malloc(sizeof(svgEdge));
    newsvg->next = NULL;
    newsvg->head = currentEdge;
    if(!esvg){
        esvg = newsvg;
    }else{
        svgEdge* currentsvg = esvg;
        while(currentsvg->next != NULL){
            currentsvg = currentsvg->next;
        }
        currentsvg->next = newsvg;
    }
    currentNode = NULL;
    currentEdge = NULL;
    return;
}
