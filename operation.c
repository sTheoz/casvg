#include "operation.h"
#include "automate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isComplete(svgEdge* edges, svg* nodes){
    char* alphabet;
    alphabet = getAlphabet(edges);
    svg* currentNode = nodes;
    svgEdge* listEdges;
    printf("ALOOOOOOO\n");
    while(currentNode != NULL){
        if(strcmp(currentNode->head->final, "NULL") != 0){
            printf("Noeud : %s \n", currentNode->head->id);
            listEdges = getEdgesForNode(edges, currentNode->head->id);
            printf("1\n");
            if(!checkAlphabetOnEdges(listEdges, alphabet))return false;
            printf("2\n");
            clearList(listEdges);
            printf("3\n");
        }
        currentNode = currentNode->next;
    }
    return true;
}

bool inList(char* l, char* c){
    int i = 0;
    if(!l)return false;
    while(l[i] != '\0'){
        if(l[i] == c[0]){
            return true;
        }
        i++;
    }
    return false;
}

void clearList(svgEdge* le){
    svgEdge* currentEdge = le;
    svgEdge* predEdge;
    while(currentEdge != NULL){
        predEdge = currentEdge;
        currentEdge = currentEdge->next;
        free(predEdge);
    }
}

bool checkAlphabetOnEdges(svgEdge* le, char* alpha){
    svgEdge* currentEdge = le;
    char c;
    int size, i;
    bool isIn;
    size = strlen(alpha);
    for(i = 0; i < size; i++){
        isIn = false;
        currentEdge = le;
        while(currentEdge != NULL){
            printf("%s\n", currentEdge->head->label);
            if(inList(alpha, currentEdge->head->label))isIn= true;
            currentEdge = currentEdge->next;
        }
        if(!isIn)return false;
    }
    return true;
}


svgEdge* getEdgesForNode(svgEdge* le, char* node){
    svgEdge* listEdges;
    listEdges = (svgEdge*) malloc(sizeof(svgEdge));
    svgEdge* rootEdges = listEdges;
    svgEdge* currentEdge = le;
    while(currentEdge != NULL){
        /*printf("ras le cul %s pour %s \n",currentEdge->head->idfrom, node);
        printf("ras le cul %s\n",currentEdge->head->label);*/
        if(strcmp(currentEdge->head->idfrom, node) == 0){
           if(listEdges->head != NULL){
               listEdges->next = (svgEdge*) malloc(sizeof(svgEdge));
               listEdges = listEdges->next;
               listEdges->next = NULL;
           }
           listEdges->head = currentEdge->head;

        }
        currentEdge = currentEdge->next;
    }
    if(rootEdges->head == NULL)return NULL;
    /*printf("WTF\n");
    while(rootEdges != NULL){
        if(rootEdges->head == NULL){
            printf("YO\n");
        }
        printf("roooott %s \n", rootEdges->head->label);
        rootEdges=rootEdges->next;
    }*/
    return rootEdges;
}

char* getAlphabet(svgEdge* edges){
    char* alphabet;
    int index = 0, sizeAlpha = 40;
    alphabet = (char*) malloc(sizeof(char) * sizeAlpha);
    for(int i = 0 ; i < sizeAlpha ; i++){
        alphabet[i] = '\0';
    }
    svgEdge* currentEdges = edges;
    while(currentEdges != NULL){
        if(!inList(alphabet, currentEdges->head->label)){
            alphabet[index] = currentEdges->head->label[0];
            index++;
        }
        currentEdges = currentEdges->next;
    }
    return alphabet;
}
