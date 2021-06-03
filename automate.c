#include "automate.h"
#include "drawSVG.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>

struct svg* casvg;
struct svgEdge* esvg;
struct node* currentNode;
struct edge* currentEdge;
struct strList* currentStrList;
struct position* pos;

// Créer un noeud
void createNode(char* id){
    if(!currentNode){
        currentNode = (node*) malloc(sizeof(node));
    }
    currentNode->id = id;
}

// Initialise un noeud avec des valeurs de base
void initNode(node* n){
    srand(time(NULL));
    if(!n->color)n->color = "BLACK";
    if(!n->bgcolor)n->bgcolor = "none";
    if(!n->init)n->init = "NULL";
    if(!n->final)n->final = "NULL";
    if(!n->posx){
        fprintf(stderr, "%s: line :%d \n",__FILE__, __LINE__);
        fprintf(stderr, "ERREUR: Pas de position  pour le noeud %s\n", n->id);
        exit(1);    
    }
    if(!n->posy){
        fprintf(stderr, "%s: line :%d \n",__FILE__, __LINE__);
        fprintf(stderr, "ERREUR: Pas de position  pour le noeud %s\n", n->id);
        exit(1);
    }
    if(!n->size)n->size = 30;
    if(!n->label)n->label = n->id;
}

// Initialise les noeuds avec des valeurs de base
void initEdge(edge* e){
    if(!e->color)e->color = "BLACK";
    if(!e->path)e->path = "default";
    if(!e->posx)e->posx = 0;
    if(!e->posy)e->posy = 0;
}

// Créer une arrête
void createEdge(char* idfrom, char* idto){
    if(!currentEdge){
        currentEdge = (edge*) malloc(sizeof(edge));
    }
    currentEdge->idfrom = idfrom;
    currentEdge->idto = idto;
    return;
}

// Supprime un noeud de la liste
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
        fprintf(stderr, "%s: line :%d \n",__FILE__, __LINE__);
        fprintf(stderr, "Error: ID not found\n");
        exit(1);
    }
    return;
}

// Supprime une arrête de la liste
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
        fprintf(stderr, "%s: line :%d \n",__FILE__, __LINE__);
        fprintf(stderr, "Error: ID not found\n");
        exit(1);
    }
    return;
}

// Initialise les valeurs des attributs pour la commande Move
void move(double dx, double dy){
    if(!pos){
        pos = (position*) malloc(sizeof(position));
    }
    pos->x = dx;
    pos->y = dy;
    return;
}

// Bouge les noeuds de la liste currentStrList ou tous les noeuds si celle-ci est vide
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
                fprintf(stderr, "%s: line :%d \n",__FILE__, __LINE__);
                fprintf(stderr, "Error: ID not found\n");
                exit(1);
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

// Ajoute dans les id des noeuds à bouger dans currentStrList
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
    exit(1);
}

// Modifier un noeud en fonction de son id
void editNode(char* id){
    svg* cNode = casvg;
    while (cNode && strcmp(id, cNode->head->id) != 0){
        cNode = cNode->next;
    }
    if(strcmp(id, cNode->head->id) == 0){
        if(currentNode->bgcolor)cNode->head->bgcolor = currentNode->bgcolor;
        if(currentNode->color)cNode->head->color = currentNode->color;
        if(currentNode->posx)cNode->head->posx = currentNode->posx;
        if(currentNode->posy)cNode->head->posy = currentNode->posy;
        if(currentNode->label)cNode->head->label = currentNode->label;
        if(currentNode->size)cNode->head->size = currentNode->size;
        if(currentNode->init)cNode->head->init = currentNode->init;
        if(currentNode->final)cNode->head->final = currentNode->final;
        free(currentNode);
        currentNode=NULL;
        return;
    }
    free(currentNode);
    currentNode=NULL;
    fprintf(stderr, "Error: ID not found\n");
    exit(1);
}

// Modifier une arrête
void editEdge(char* idfrom, char* idto){
    svgEdge* cEdge = esvg;
    while (cEdge && (strcmp(idfrom, cEdge->head->idfrom) != 0) && (strcmp(idto, cEdge->head->idto) != 0)){
        cEdge = cEdge->next;
    }
    if((strcmp(idfrom, cEdge->head->idfrom) == 0) && (strcmp(idto, cEdge->head->idto) == 0)){
        if(currentNode->color)cEdge->head->color = currentNode->color;
        if(currentNode->posx)cEdge->head->posx = currentNode->posx;
        if(currentNode->posy)cEdge->head->posy = currentNode->posy;
        if(currentNode->label)cEdge->head->label = currentNode->label;
        if(currentEdge->path)cEdge->head->path = currentEdge->path;
        free(currentNode);
        currentNode=NULL;
        free(currentEdge);
        currentEdge=NULL;
        return;
    }
    free(currentNode);
    currentNode=NULL;
    free(currentEdge);
    currentEdge=NULL;
    fprintf(stderr, "Error: ID not found\n");
    exit(1);
}

// Afficher dans la console les infos du graphe
void dump(){
    printf("Nodes:\n");
    while(casvg){
        printf("ID: %s\n", casvg->head->id);
        printf("Color: %s\n", casvg->head->color);
        printf("Background color: %s\n", casvg->head->bgcolor);
        printf("X: %f.2\n", casvg->head->posx);
        printf("Y: %f.2\n", casvg->head->posy);
        printf("Label: %s\n", casvg->head->label);
        printf("Size: %f.2\n", casvg->head->size);
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
        printf("X: %f.2\n", esvg->head->posx);
        printf("Y: %f.2\n", esvg->head->posy);
        printf("Label: %s\n", esvg->head->label);
        printf("Path: %s\n", esvg->head->path);
        printf("========\n");
        esvg = esvg->next;
    }
    return;
}

// Dessine le SVG
void dumpSVG(char* name){
    printf("Nom du fichier: %s.svg \n",name);
    draw(name, casvg, esvg);
    return;
}

// Enregistre le label
void setLabel(char* label){
    if(!currentNode){
        currentNode = (node*) malloc(sizeof(node));
    }
    currentNode->label = label;
    return;
}

// Enregistre les positions
void setPosition(double x, double y){
    if(!currentNode){
        currentNode = (node*) malloc(sizeof(node));
    }
    currentNode->posx = x;
    currentNode->posy = y;
    return;
}

// Enregistre la couleur
void setColor(char* color){
    if(!currentNode){
        currentNode = (node*) malloc(sizeof(node));
    }
    currentNode->color = color;
    return;
}

// Enregistre la couleur de fond
void setBackgroundColor(char* color){
    if(!currentNode){
        currentNode = (node*) malloc(sizeof(node));
    }
    currentNode->bgcolor = color;
    return;
}

// Enregistre la taille
void setSize(double s){
    if(!currentNode){
        currentNode = (node*) malloc(sizeof(node));
    }
    currentNode->size = s;
    return;
}

// Enregistre la direction de la flèche initial
void setInit(char* dir){
    if(!currentNode){
        currentNode = (node*) malloc(sizeof(node));
    }
    currentNode->init = dir;
    return;
}

// Enregistre la direction de la flèche finale
void setFinal(char* dir){
    if(!currentNode){
        currentNode = (node*) malloc(sizeof(node));
    }
    currentNode->final = dir;
    return;
}

// Enregistre le code du path
void setPath(char* path){
    if(!currentEdge){
        currentEdge = (edge*) malloc(sizeof(edge));
    }
    currentEdge->path = path;
    return;
}

// Met un noeud dans la liste globale
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

// Met une arrete dans la liste globale
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

svgEdge* getEdges(){
    return esvg;
}

svg* getNodes(){
    return casvg;
}