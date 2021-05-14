#include "drawSVG.h"
#include "automate.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void draw(char* path, svg* nl, svgEdge* el){
    FILE* fd;
    fd = fopen(strcat(path,".svg"), "w");

    if(fd == NULL){
        printf("Error!");   
        exit(1);
    }

    fprintf(fd, "<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" width=\"800\" height=\"600\" viewBox=\"0 0 800 600\">\n");
    
    drawNodes(nl, fd);
    drawEdges(el, nl, fd);

    fprintf(fd, "%s", "</svg>\n");
    fclose(fd);
}

void drawNodes(svg* nodeList, FILE* fd){
    svg* currentNode = nodeList;
    fprintf(fd, " <g stroke=\"black\" stroke-width=\"2\" fill=\"none\">\n");
    while(currentNode){
        fprintf(fd, "  <circle cx=\"%d\" cy=\"%d\" r=\"%d\" />\n", currentNode->head->posx, currentNode->head->posy, currentNode->head->size);
        currentNode = currentNode->next;
    }
    fprintf(fd, " </g>\n");
    currentNode = nodeList;
    fprintf(fd, " <g dominant-baseline=\"middle\" text-anchor=\"middle\" fill=\"black\">\n");
    while(currentNode){
        fprintf(fd,"  <text x=\"%d\" y=\"%d\">%s</text>\n", currentNode->head->posx, currentNode->head->posy, currentNode->head->id);
        currentNode = currentNode->next;
    }
    fprintf(fd, " </g>\n");
    return;
}

void drawEdges(svgEdge* edgeList, svg* nodeList, FILE* fd){
    svgEdge* currentEdge = edgeList;
    svg* currentNode;
    int sizenfrom, xnfrom, ynfrom, sizento, xnto, ynto;
    int dx, dy, lengthedge;
    fprintf(fd, " <g stroke=\"black\" stroke-width=\"2\" fill=\"none\">\n");
    while(currentEdge){
        currentNode = nodeList;
        sizenfrom= -1, xnfrom= -1, ynfrom= -1, sizento= -1, xnto= -1, ynto = -1;
        while(currentNode){
            if(strcmp(currentNode->head->id, currentEdge->head->idfrom) == 0){
                sizenfrom = currentNode->head->size;
                xnfrom = currentNode->head->posx;
                ynfrom = currentNode->head->posy;
            }
            if(strcmp(currentNode->head->id, currentEdge->head->idto) == 0){
                sizento = currentNode->head->size;
                xnto = currentNode->head->posx;
                ynto = currentNode->head->posy;
            }
            currentNode = currentNode->next;
        }
        if(sizenfrom != -1 && xnfrom != -1 && ynfrom != -1 && sizento != -1 && xnto != -1 && ynto  != -1){            
            // Transition boucle
            if( strcmp(currentEdge->head->idfrom, currentEdge->head->idto) == 0){
                fprintf(fd, "  <path d=\"M %d %d A %d %d 0 1 1 %d %d\" />\n", xnfrom+(sizenfrom/3), ynfrom+sizenfrom, sizenfrom/2, sizenfrom/2, xnfrom-(sizenfrom/3), ynfrom+sizenfrom);
                fprintf(fd, "  <path d=\"M %d %d l -11 2 m 9 9 l 2 -11\" />\n", xnfrom+(sizenfrom/3)-((sizenfrom/3)*2), ynfrom+sizenfrom);
                fprintf(fd, "  <text x=\"%d\" y=\"%d\">a</text>\n", (xnto + xnfrom)/2 , (ynto + ynfrom)/2 + sizenfrom/2*5 );
            }else{
                dx = xnto - sizento;
                dy = ynto;
                //lengthedge = sqrt(pow((xnto - xnfrom),2) + pow((ynto - ynfrom),2)) - sizenfrom - sizento;
                if(xnfrom < xnto){
                    // Transition de gauche à droite
                    fprintf(fd, "  <path d=\"M %d %d L %d %d\" />\n", xnfrom+sizenfrom , ynfrom, xnto- sizento, ynto);
                    fprintf(fd, "  <path d=\"M %d %d l -8 -8 m 0 16 l 8 -8\" />\n", xnto - sizento, ynto);
                    fprintf(fd, "  <text x=\"%d\" y=\"%d\">a</text>\n", (xnto + xnfrom)/2, (ynto + ynfrom)/2 - sizenfrom/6);
                }else if( xnfrom > xnto){
                    // Transition de droite à gauche
                    fprintf(fd, "  <path d=\"M %d %d L %d %d\" />\n", xnfrom-sizenfrom , ynfrom, xnto + sizento, ynto);
                    fprintf(fd, "  <path d=\"M %d %d l 8 8 m 0 -16 l -8 8\" />\n", xnto + sizento, ynto);
                    fprintf(fd, "  <text x=\"%d\" y=\"%d\">a</text>\n", (xnto + xnfrom)/2, (ynto + ynfrom)/2 + sizenfrom/3);
                }else if( ynfrom < ynto){
                    // Transition de haut en bas
                    fprintf(fd, "  <path d=\"M %d %d L %d %d\" />\n", xnfrom , ynfrom+sizenfrom, xnto, ynto-sizento);
                    fprintf(fd, "  <path d=\"M %d %d l 8 -8 m -16 0 l 8 8\" />\n", xnto, ynto-sizento);
                    fprintf(fd, "  <text x=\"%d\" y=\"%d\">a</text>\n", (xnto + xnfrom)/2 - sizenfrom/3, (ynto + ynfrom)/2);
                }else{
                    // Transition de bas en haut
                    fprintf(fd, "  <path d=\"M %d %d L %d %d\" />\n", xnfrom , ynfrom-sizenfrom, xnto, ynto+sizento);
                    fprintf(fd, "  <path d=\"M %d %d l -8 8 m 16 0 l -8 -8\" />\n", xnto, ynto+sizento);
                    fprintf(fd, "  <text x=\"%d\" y=\"%d\">a</text>\n", (xnto + xnfrom)/2 + sizenfrom/6, (ynto + ynfrom)/2);
                }
                
            }
        }       
        currentEdge = currentEdge->next;
    }
    fprintf(fd, " </g>\n");
}
