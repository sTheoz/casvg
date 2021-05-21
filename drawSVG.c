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

    fprintf(fd, "<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" width=\"1920\" height=\"1080\" viewBox=\"0 0 1920 1080\">\n");
    fprintf(fd, "<defs><marker id='head' orient='auto' markerWidth='15' markerHeight='15' refX='8.7' refY='3'><path d='M0,0 L0,6 L9,3 z' /></marker></defs>");
    drawEdges(el, nl, fd);
    drawNodes(nl, fd);

    fprintf(fd, "%s", "</svg>\n");
    fclose(fd);
}

void drawNodes(svg* nodeList, FILE* fd){
    svg* currentNode = nodeList;
    fprintf(fd, " <g stroke=\"black\" stroke-width=\"2\" fill=\"none\">\n");
    while(currentNode){
        fprintf(fd, "  <circle cx=\"%d\" cy=\"%d\" r=\"%d\" stroke=\"%s\" fill=\"%s\"/>\n", currentNode->head->posx, currentNode->head->posy, currentNode->head->size, currentNode->head->color, currentNode->head->bgcolor);
        if(strcmp(currentNode->head->init, "NULL") != 0){
            if(strcmp(currentNode->head->init, "WEST") == 0){
                // Transition de gauche à droite
                fprintf(fd, "  <path d=\"M %d %d l %d %d\" marker-end=\"url(#head)\"/>\n", currentNode->head->posx-currentNode->head->size*2, currentNode->head->posy, currentNode->head->size, 0);
                //fprintf(fd, "  <path d=\"M %d %d l -8 -8 m 0 16 l 8 -8\"/>\n", currentNode->head->posx - currentNode->head->size, currentNode->head->posy);
            }else if( strcmp(currentNode->head->init, "EAST") == 0 ){
                // Transition de droite à gauche
                fprintf(fd, "  <path d=\"M %d %d l %d %d\" marker-end=\"url(#head)\"/>\n", currentNode->head->posx+currentNode->head->size*2 , currentNode->head->posy, -currentNode->head->size, 0);
                //fprintf(fd, "  <path d=\"M %d %d l 8 8 m 0 -16 l -8 8\" />\n", currentNode->head->posx + currentNode->head->size, currentNode->head->posy);
            }else if( strcmp(currentNode->head->init, "NORTH")==0){
                // Transition de haut en bas
                fprintf(fd, "  <path d=\"M %d %d l %d %d\"  marker-end=\"url(#head)\"/>\n", currentNode->head->posx , currentNode->head->posy-currentNode->head->size*2, 0,currentNode->head->size);
                //fprintf(fd, "  <path d=\"M %d %d l 8 -8 m -16 0 l 8 8\"  />\n", currentNode->head->posx , currentNode->head->posy - currentNode->head->size);
            }else if( strcmp(currentNode->head->init, "SOUTH")==0) {
                // Transition de bas en haut
                fprintf(fd, "  <path d=\"M %d %d l %d %d\"  marker-end=\"url(#head)\"/>\n", currentNode->head->posx , currentNode->head->posy+currentNode->head->size*2, 0,-currentNode->head->size);
                //fprintf(fd, "  <path d=\"M %d %d l -8 8 m 16 0 l -8 -8\"  />\n", currentNode->head->posx, currentNode->head->posy+ currentNode->head->size);
            }else if( strcmp(currentNode->head->init, "NORTH-WEST")==0){
                // Haut gauche
                fprintf(fd, "  <path d=\"M %d %d m 8 8 l %d %d\" marker-end=\"url(#head)\" />\n", currentNode->head->posx - currentNode->head->size*2, currentNode->head->posy-currentNode->head->size*2, currentNode->head->size,currentNode->head->size);
                //fprintf(fd, "  <path d=\"M %d %d m 8 8 l -10 6 m 10 -6 l -3 -15\"  />\n", currentNode->head->posx - currentNode->head->size, currentNode->head->posy-currentNode->head->size);
            }else if( strcmp(currentNode->head->init, "NORTH-EAST")==0){
                // Haut gauche
                fprintf(fd, "  <path d=\"M %d %d m -8 8 l %d %d\" marker-end=\"url(#head)\" />\n", currentNode->head->posx + currentNode->head->size*2, currentNode->head->posy-currentNode->head->size*2, -currentNode->head->size,currentNode->head->size);
                //fprintf(fd, "  <path d=\"M %d %d m -8 8 l 10 6 m -10 -6 l -3 -15\"  />\n", currentNode->head->posx + currentNode->head->size, currentNode->head->posy-currentNode->head->size);
            }else if( strcmp(currentNode->head->init, "SOUTH-EAST")==0){
                fprintf(fd, "  <path d=\"M %d %d m -8 -8 l %d %d\" marker-end=\"url(#head)\" />\n", currentNode->head->posx + currentNode->head->size*2, currentNode->head->posy+currentNode->head->size*2, -currentNode->head->size,-currentNode->head->size);
                //fprintf(fd, "  <path d=\"M %d %d m 8 8 l -10 6 m 10 -6 l -3 -15\"  />\n", currentNode->head->posx - currentNode->head->size, currentNode->head->posy-currentNode->head->size);
            }else if( strcmp(currentNode->head->init, "SOUTH-WEST")==0){
                fprintf(fd, "  <path d=\"M %d %d m 8 -8 l %d %d\" marker-end=\"url(#head)\" />\n", currentNode->head->posx - currentNode->head->size*2, currentNode->head->posy+currentNode->head->size*2, currentNode->head->size,-currentNode->head->size);
            }
        }
        if(strcmp(currentNode->head->final, "NULL") != 0){
            if(strcmp(currentNode->head->final, "WEST") == 0){
                // Transition de gauche à droite
                fprintf(fd, "  <path d=\"M %d %d l %d %d\" marker-end=\"url(#head)\"/>\n", currentNode->head->posx-currentNode->head->size, currentNode->head->posy, -currentNode->head->size, 0);
                //fprintf(fd, "  <path d=\"M %d %d l -8 -8 m 0 16 l 8 -8\"/>\n", currentNode->head->posx - currentNode->head->size, currentNode->head->posy);
            }else if( strcmp(currentNode->head->final, "EAST") == 0 ){
                // Transition de droite à gauche
                fprintf(fd, "  <path d=\"M %d %d l %d %d\" marker-end=\"url(#head)\"/>\n", currentNode->head->posx+currentNode->head->size , currentNode->head->posy,currentNode->head->size, 0);
                //fprintf(fd, "  <path d=\"M %d %d l 8 8 m 0 -16 l -8 8\" />\n", currentNode->head->posx + currentNode->head->size, currentNode->head->posy);
            }else if( strcmp(currentNode->head->final, "NORTH")==0){
                // Transition de haut en bas
                fprintf(fd, "  <path d=\"M %d %d l %d %d\"  marker-end=\"url(#head)\"/>\n", currentNode->head->posx , currentNode->head->posy-currentNode->head->size, 0,-currentNode->head->size);
                //fprintf(fd, "  <path d=\"M %d %d l 8 -8 m -16 0 l 8 8\"  />\n", currentNode->head->posx , currentNode->head->posy - currentNode->head->size);
            }else if( strcmp(currentNode->head->final, "SOUTH")==0) {
                // Transition de bas en haut
                fprintf(fd, "  <path d=\"M %d %d l %d %d\"  marker-end=\"url(#head)\"/>\n", currentNode->head->posx , currentNode->head->posy+currentNode->head->size, 0,currentNode->head->size);
                //fprintf(fd, "  <path d=\"M %d %d l -8 8 m 16 0 l -8 -8\"  />\n", currentNode->head->posx, currentNode->head->posy+ currentNode->head->size);
            }else if( strcmp(currentNode->head->final, "NORTH-WEST")==0){
                // Haut gauche
                fprintf(fd, "  <path d=\"M %d %d m 8 8 l %d %d\" marker-end=\"url(#head)\" />\n", currentNode->head->posx - currentNode->head->size, currentNode->head->posy-currentNode->head->size, -currentNode->head->size,-currentNode->head->size);
                //fprintf(fd, "  <path d=\"M %d %d m 8 8 l -10 6 m 10 -6 l -3 -15\"  />\n", currentNode->head->posx - currentNode->head->size, currentNode->head->posy-currentNode->head->size);
            }else if( strcmp(currentNode->head->final, "NORTH-EAST")==0){
                // Haut gauche
                fprintf(fd, "  <path d=\"M %d %d m -8 8 l %d %d\" marker-end=\"url(#head)\" />\n", currentNode->head->posx + currentNode->head->size, currentNode->head->posy-currentNode->head->size, currentNode->head->size,-currentNode->head->size);
                //fprintf(fd, "  <path d=\"M %d %d m -8 8 l 10 6 m -10 -6 l -3 -15\"  />\n", currentNode->head->posx + currentNode->head->size, currentNode->head->posy-currentNode->head->size);
            }else if( strcmp(currentNode->head->final, "SOUTH-EAST")==0){
                fprintf(fd, "  <path d=\"M %d %d m -8 -8 l %d %d\" marker-end=\"url(#head)\" />\n", currentNode->head->posx + currentNode->head->size, currentNode->head->posy+currentNode->head->size, currentNode->head->size,currentNode->head->size);
                //fprintf(fd, "  <path d=\"M %d %d m 8 8 l -10 6 m 10 -6 l -3 -15\"  />\n", currentNode->head->posx - currentNode->head->size, currentNode->head->posy-currentNode->head->size);
            }else if( strcmp(currentNode->head->final, "SOUTH-WEST")==0){
                fprintf(fd, "  <path d=\"M %d %d m 8 -8 l %d %d\" marker-end=\"url(#head)\" />\n", currentNode->head->posx - currentNode->head->size, currentNode->head->posy+currentNode->head->size, -currentNode->head->size,currentNode->head->size);
            }
        }
        currentNode = currentNode->next;
    }
    fprintf(fd, " </g>\n");
    currentNode = nodeList;
    fprintf(fd, " <g dominant-baseline=\"middle\" text-anchor=\"middle\" fill=\"black\">\n");
    while(currentNode){
        fprintf(fd,"  <text x=\"%d\" y=\"%d\">%s</text>\n", currentNode->head->posx, currentNode->head->posy, currentNode->head->label);
        currentNode = currentNode->next;
    }
    fprintf(fd, " </g>\n");
    return;
}

void drawEdges(svgEdge* edgeList, svg* nodeList, FILE* fd){
    svgEdge* currentEdge = edgeList;
    svg* currentNode;
    int sizenfrom, xnfrom, ynfrom, sizento, xnto, ynto;
    int lengthedge;
    double d, d2, d3, ratio, dx, dy, xFinal, yFinal, xa,xb,ya,yb;
    double dxB, dyB, ratio2, xInitial, yInitial;

    fprintf(fd, " <g stroke=\"black\" stroke-width=\"2\" fill=\"none\">\n");
    while(currentEdge){
        if(strcmp(currentEdge->head->path, "default") != 0){
            // Pas de vérification de conformité de la syntax pour le moment
            fprintf(fd, "%s\n", currentEdge->head->path);
        }else{
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
                    fprintf(fd, "  <path d=\"M %d %d A %d %d 0 1 1 %d %d\" stroke=\"%s\"/>\n", xnfrom+(sizenfrom/3), ynfrom+sizenfrom, sizenfrom/2, sizenfrom/2, xnfrom-(sizenfrom/3), ynfrom+sizenfrom, currentEdge->head->color);
                    fprintf(fd, "  <path d=\"M %d %d l -11 2 m 9 9 l 2 -11\" stroke=\"%s\"/>\n", xnfrom+(sizenfrom/3)-((sizenfrom/3)*2), ynfrom+sizenfrom, currentEdge->head->color);
                    fprintf(fd, "  <text x=\"%d\" y=\"%d\">%s</text>\n", (xnto + xnfrom)/2 , (ynto + ynfrom)/2 + sizenfrom/2*5 , currentEdge->head->label);
                }else{
                    xa = (double) xnfrom;
                    xb = (double) xnto;
                    ya = (double) ynfrom;
                    yb = (double) ynto;
                    d = sqrt( pow( xb - xa, 2 ) + pow( yb - ya, 2 ) );
                    d2 = d - sizento;
                    d3 = d - sizenfrom;
                    ratio = d2 / d;
                    ratio2 = d3 / d;
                    dx = (xb - xa) * ratio;
                    dy = (yb - ya) * ratio;
                    
                    dxB = (xa - xb) * ratio2;
                    dyB = (ya - yb) * ratio2;

                    xInitial = xb + dxB;
                    yInitial = yb + dyB;

                    xFinal = xa + dx;
                    yFinal = ya + dy;
                    fprintf(fd, "  <path d=\"M %f %f L %f %f\" stroke=\"%s\"/>\n",  xInitial, yInitial, xFinal, yFinal, currentEdge->head->color);

                    //lengthedge = sqrt(pow((xnto - xnfrom),2) + pow((ynto - ynfrom),2)) - sizenfrom - sizento;
                    if(xnfrom < xnto){
                        // Transition de gauche à droite
                        //fprintf(fd, "  <path d=\"M %d %d L %d %d\" stroke=\"%s\"/>\n", xnfrom+sizenfrom , ynfrom, xnto- sizento, ynto, currentEdge->head->color);
                        fprintf(fd, "  <path d=\"M %f %f l -8 -8 m 0 16 l 8 -8\" stroke=\"%s\"/>\n", xFinal, yFinal, currentEdge->head->color);
                        fprintf(fd, "  <text x=\"%f\" y=\"%f\">%s</text>\n", (xFinal + xInitial)/2, (yFinal + yInitial)/2 - sizenfrom/6, currentEdge->head->label);
                    }else if( xInitial > xFinal){
                        // Transition de droite à gauche
                        //fprintf(fd, "  <path d=\"M %f %f L %f %f\" stroke=\"%s\"/>\n", xInitial-sizenfrom , yInitial, xFinal + sizento, yFinal, currentEdge->head->color);
                        fprintf(fd, "  <path d=\"M %f %f l 8 8 m 0 -16 l -8 8\" stroke=\"%s\"/>\n", xFinal , yFinal, currentEdge->head->color);
                        fprintf(fd, "  <text x=\"%f\" y=\"%f\">%s</text>\n", (xFinal + xInitial)/2, (yFinal + yInitial)/2 + sizenfrom/3, currentEdge->head->label);
                    }else if( yInitial < yFinal){
                        // Transition de haut en bas
                        //fprintf(fd, "  <path d=\"M %f %f L %f %f\" stroke=\"%s\" />\n", xInitial , yInitial+sizenfrom, xFinal, yFinal-sizento, currentEdge->head->color);
                        fprintf(fd, "  <path d=\"M %f %f l 8 -8 m -16 0 l 8 8\" stroke=\"%s\" />\n", xFinal, yFinal, currentEdge->head->color);
                        fprintf(fd, "  <text x=\"%f\" y=\"%f\">%s</text>\n", (xFinal + xInitial)/2 - sizenfrom/3, (yFinal + yInitial)/2, currentEdge->head->label);
                    }else{
                        // Transition de bas en haut
                        //fprintf(fd, "  <path d=\"M %f %f L %f %f\" stroke=\"%s\" />\n", xInitial , yInitial-sizenfrom, xFinal, yFinal+sizento, currentEdge->head->color);
                        fprintf(fd, "  <path d=\"M %f %f l -8 8 m 16 0 l -8 -8\" stroke=\"%s\" />\n", xFinal, yFinal, currentEdge->head->color);
                        fprintf(fd, "  <text x=\"%f\" y=\"%f\">%s</text>\n", (xFinal + xInitial)/2 + sizenfrom/6, (yFinal + yInitial)/2, currentEdge->head->label);
                    }
                    
                }
            }  
        }  
        currentEdge = currentEdge->next;
    }
    fprintf(fd, " </g>\n");
}
