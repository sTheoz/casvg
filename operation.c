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
    char* labelB;
    int j=0;

    svg* currentNode = nodes;
    while(currentNode != NULL){
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
            if((int)strlen(currentEdge->head->label) > 1){
                tempLabel = strdup(currentEdge->head->label);
                while( (found = strsep(&tempLabel,",")) != NULL ){
                    if(!inList(alphabet, found)){
                        alphabet[index] = found[0];
                        index++;
                    }
                }
            }else{
                if(!inList(alphabet, currentEdge->head->label)){
                    alphabet[index] = currentEdge->head->label[0];
                    index++;
                }
            }
        }
        currentEdge = currentEdge->next;
    }
    return alphabet;
}

char* getAlphabetForNodeDeter(svgEdge* edges, char* idNode){
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
            if((int)strlen(currentEdge->head->label) > 1){
                tempLabel = strdup(currentEdge->head->label);
                while( (found = strsep(&tempLabel,",")) != NULL ){
                    alphabet[index] = found[0];
                    index++;
                }
            }else{
                alphabet[index] = currentEdge->head->label[0];
                index++;
            }
        }
        currentEdge = currentEdge->next;
    }
    return alphabet;
}


bool isDeterministic(svgEdge* edges, svg* nodes){
    char *myLabels;
    svg* currentNode = nodes;
    int countInit=0;
    while(currentNode != NULL){
        if(strcmp(currentNode->head->init,"NULL")!=0)countInit++;
        myLabels = getAlphabetForNodeDeter(edges, currentNode->head->id);
        for(int i = 0 ; i < (int)strlen(myLabels); i++){
            for(int j = i+1 ; j < (int)strlen(myLabels) ; j++){
                if(myLabels[i] == myLabels[j])return false;
            }
        }
        currentNode = currentNode->next;
    }
    if(countInit!=1)return false;
    return true;
}

void showDeterministic(svgEdge* edges, svg* nodes, char* color){
    char *myLabels;
    svg* currentNode = nodes;
    svgEdge* currentEdge = edges;
    while(currentNode != NULL){
        myLabels = getAlphabetForNodeDeter(edges, currentNode->head->id);
        for(int i = 0 ; i < (int)strlen(myLabels); i++){
            for(int j = i+1 ; j < (int)strlen(myLabels) ; j++){
                if(myLabels[i] == myLabels[j]){
                    while(currentEdge){
                        if(strcmp(currentEdge->head->idfrom, currentNode->head->id) == 0 && strchr(currentEdge->head->label, myLabels[i])){
                            currentEdge->head->color = color;
                        }
                        currentEdge = currentEdge->next;
                    }
                }
            }
        }
        currentNode = currentNode->next;
    }
}

bool isAccepted(svgEdge* edges, svg* nodes, char* str){
    if(!isDeterministic(edges, nodes))return false;
    svg* cNode = nodes;
    char* currentNode;
    currentNode = getInitial(nodes);
    for(int i = 0 ; i < (int)strlen(str); i++){
        currentNode = getNodeByLabel(edges, currentNode, str[i]);
        if(!currentNode)return false;
    }
    while(cNode){
        if(strcmp(cNode->head->id, currentNode) == 0){
            if(strcmp(cNode->head->final, "NULL") != 0){
                return true;
            }
            return false;
        }
        cNode = cNode->next;
    }
    return false;
}

char* getNodeByLabel(svgEdge* edges, char* idfrom, char label){
    svgEdge* currentEdge = edges;
    while(currentEdge){
        if(strcmp(idfrom, currentEdge->head->idfrom) == 0 && strchr(currentEdge->head->label, label)){
            return currentEdge->head->idto;
        }
        currentEdge = currentEdge->next;
    }
    return NULL;
}

char* getInitial(svg* nodes){
    svg* currentNode = nodes;
    while(currentNode){
        if(strcmp(currentNode->head->init, "NULL") != 0){
            return currentNode->head->id;
        }
        currentNode = currentNode->next;
    }
    return NULL;
}