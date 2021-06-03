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

void showComplete(svgEdge* edges, svg* nodes, char* color){
    char* alphabet, *myLabels;
    alphabet = getAlphabet(edges);
    svg* currentNode = nodes;
    svgEdge* listEdges;
    while(currentNode != NULL){
        printf("Noeud: %s\n",currentNode->head->id);
        myLabels = getAlphabetForNode(edges, currentNode->head->id);
        if(strcmp(currentNode->head->final, "NULL") == 0){
            if(!checkAlphabet(myLabels, alphabet)){
                setBackgroundColor(color);
                editNode(currentNode->head->id);
            }
        }
        currentNode = currentNode->next;
    }
    return true;
}

void complete(svgEdge* edges, svg* nodes, char* id, double x, double y){
    setPosition(x,y);
    createNode(id);
    setNode();

    char* alphabet, *myLabels;
    alphabet = getAlphabet(edges);
    
    char* labelAlpha;
    labelAlpha = malloc(sizeof(char)*strlen(alphabet)*2);
    int j=0;
    for(int i = 0 ; i < strlen(alphabet); i++){
        labelAlpha[j] = alphabet[i];
        j++;
        labelAlpha[j] = ',';
        j++;
    }
    labelAlpha[j-1]='\0';
    setLabel(labelAlpha);
    createEdge(id, id); 
    setEdge();

    svg* currentNode = nodes;
    svgEdge* listEdges;
    while(currentNode != NULL){
        printf("Noeud: %s\n",currentNode->head->id);
        myLabels = getAlphabetForNode(edges, currentNode->head->id);
        if(strcmp(currentNode->head->final, "NULL") == 0){
            if(!checkAlphabet(myLabels, alphabet)){
                /*
                Get les lettres manquantes
                Créer un label avec
                Créer l'arrete avec le label qui va de currentNode  vers le noeud id
                */

            }
        }
        currentNode = currentNode->next;
    }
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
            if(!inList(alphabet, currentEdge->head->label)){
                printf("Je met %s\n", currentEdge->head->label);
                alphabet[index] = currentEdge->head->label[0];
                index++;
            }
        }
        currentEdge = currentEdge->next;
    }
    printf("alpha :  %s\n", alphabet);
    return alphabet;
}
