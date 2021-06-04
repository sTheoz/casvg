#include "operation.h"
#include "automate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isComplete(svgEdge* edges, svg* nodes){
    char* alphabet, *myLabels;
    alphabet = getAlphabet(edges);
    svg* currentNode = nodes;
    while(currentNode != NULL){
        printf("Noeud: %s\n",currentNode->head->id);
        myLabels = getAlphabetForNode(edges, currentNode->head->id);
        if(strcmp(currentNode->head->final, "NULL") == 0){
            if(!checkAlphabet(myLabels, alphabet)){
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
}

void complete(svgEdge* edges, svg* nodes, char* id, double x, double y){
    setPosition(x,y);
    createNode(id);
    setNode();
    char* alphabet, *myLabels, *missedLab;
    alphabet = getAlphabet(edges);
    char* labelAlpha, *labelB;
    int j=0;

    svg* currentNode = nodes;
    while(currentNode != NULL){
        printf("Noeud: %s\n",currentNode->head->id);
        myLabels = getAlphabetForNode(edges, currentNode->head->id);
        if(strcmp(currentNode->head->final, "NULL") == 0){
            if(!checkAlphabet(myLabels, alphabet)){
                missedLab = getMissedLabels(myLabels, alphabet);
                labelB = (char*) malloc(sizeof(char)*(int)strlen(missedLab)*2);
                j=0;
                for(int i = 0 ; i < (int)strlen(missedLab); i++){
                    labelB[j] = missedLab[i];
                    j++;
                    labelB[j] = ',';
                    j++;
                }
                labelB[j-1]='\0';
                setLabel(strdup(labelB));
                createEdge(currentNode->head->id, id);
                setEdge();
                free(labelB);
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

char* getMissedLabels(char* myLabels, char* alphabet){
    char* missedChar;
    bool isIn;
    int index=0;
    missedChar = (char*) malloc(sizeof(char) * strlen(alphabet));
    for(int i = 0; i < (int)strlen(alphabet); i++){
        isIn = false;
        for(int j = 0 ; j < (int)strlen(myLabels); j++){
            if(alphabet[i] == myLabels[j])isIn=true;
        }
        if(!isIn){
            missedChar[index] = alphabet[i];
            index++;
        };
    }
    missedChar[index] = '\0';
    printf("Missed char %s\n", missedChar);
    return missedChar;
}


bool checkAlphabet(char* myLabels, char* alpha){
    bool isIn;
    for(int i = 0; i < (int)strlen(alpha); i++){
        isIn = false;
        for(int j = 0 ; j < (int)strlen(myLabels); j++){
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
        printf("currentEdges: %s to %s\n", currentEdges->head->idfrom, currentEdges->head->idto);
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
    char* alphabet, *found;
    int index=0, sizeAlpha = 40;
    alphabet = (char*) malloc(sizeof(char) * sizeAlpha);
    for(int i = 0 ; i < sizeAlpha ; i++){
        alphabet[i] = '\0';
    }
    char* tempLabel;
    while(currentEdge != NULL){
        if(strcmp(currentEdge->head->idfrom, idNode)==0){
            printf("idfrom : %s to %s\n", currentEdge->head->idfrom, currentEdge->head->idto);
            if((int)strlen(currentEdge->head->label) > 1){
                tempLabel = strdup(currentEdge->head->label);
                while( (found = strsep(&tempLabel,",")) != NULL ){
                    if(!inList(alphabet, found)){
                        printf("Je met %s\n", found);
                        alphabet[index] = found[0];
                        index++;
                    }
                }
            }else{
                if(!inList(alphabet, currentEdge->head->label)){
                    printf("Je met %s\n", currentEdge->head->label);
                    alphabet[index] = currentEdge->head->label[0];
                    index++;
                }
            }
        }
        currentEdge = currentEdge->next;
    }
    return alphabet;
}
