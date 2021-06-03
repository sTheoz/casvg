#include "operation.h"
#include "automate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isComplete(svgEdge* edges, svg* nodes){
    char* alphabet, *myLabels;
    alphabet = getAlphabet(edges);
    svg* currentNode = nodes;
    svgEdge* listEdges;
    while(currentNode != NULL){
        printf("Noeud: %s\n",currentNode->head->id);
        myLabels = getAlphabetForNode(edges, currentNode->head->id);
        if(strcmp(currentNode->head->final, "NULL") == 0){
            if(!checkAlphabet(myLabels, alphabet)){
                printf("Oui je suis faux ! \n");
                return false;
            }
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

bool checkAlphabet(char* myLabels, char* alpha){
    bool isIn;
    for(int i = 0; i < strlen(alpha); i++){
        isIn = false;
        for(int j = 0 ; j < strlen(myLabels); j++){
            if(alpha[i] == myLabels[j])isIn=true;
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

char* getAlphabetForNode(svgEdge* edges, char* idNode){
    svgEdge* currentEdge = edges;
    char* alphabet;
    int index=0, sizeAlpha = 40;
    alphabet = (char*) malloc(sizeof(char) * sizeAlpha);
    for(int i = 0 ; i < sizeAlpha ; i++){
        alphabet[i] = '\0';
    }
    while(currentEdge != NULL){
        if(strcmp(currentEdge->head->idfrom, idNode)==0){
            printf("Je met %s\n", currentEdge->head->label);
            alphabet[index] = currentEdge->head->label[0];
            index++;
        }
        currentEdge = currentEdge->next;
    }
    printf("alpha :  %s\n", alphabet);
    return alphabet;
}
