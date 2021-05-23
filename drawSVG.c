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
    fprintf(fd, "<defs><marker id='head' orient='auto' markerWidth='10' markerHeight='10' refX='8.7' refY='3'><path d='M0,0 L0,6 L9,3 z' /></marker></defs>");
    drawEdges(el, nl, fd);
    drawNodes(nl, fd);

    fprintf(fd, "%s", "</svg>\n");
    fclose(fd);
}

void drawNodes(svg* nodeList, FILE* fd){
    svg* currentNode = nodeList;
    fprintf(fd, " <g stroke=\"black\" stroke-width=\"2\" fill=\"none\">\n");
    while(currentNode){
        fprintf(fd, "  <circle cx=\"%.2f\" cy=\"%.2f\" r=\"%.2f\" stroke=\"%s\" fill=\"%s\"/>\n", currentNode->head->posx, currentNode->head->posy, currentNode->head->size, currentNode->head->color, currentNode->head->bgcolor);
        if(strcmp(currentNode->head->init, "NULL") != 0){
            if(strcmp(currentNode->head->init, "WEST") == 0){
                // Transition de gauche à droite
                fprintf(fd, "  <path d=\"M %.2f %.2f l %.2f %.2f\" marker-end=\"url(#head)\"/>\n", currentNode->head->posx-currentNode->head->size*2, currentNode->head->posy, currentNode->head->size, 0.0);
            }else if( strcmp(currentNode->head->init, "EAST") == 0 ){
                // Transition de droite à gauche
                fprintf(fd, "  <path d=\"M %.2f %.2f l %.2f %.2f\" marker-end=\"url(#head)\"/>\n", currentNode->head->posx+currentNode->head->size*2 , currentNode->head->posy, -currentNode->head->size, 0.0);
            }else if( strcmp(currentNode->head->init, "NORTH")==0){
                // Transition de haut en bas
                fprintf(fd, "  <path d=\"M %.2f %.2f l %.2f %.2f\"  marker-end=\"url(#head)\"/>\n", currentNode->head->posx , currentNode->head->posy-currentNode->head->size*2, 0.0,currentNode->head->size);
            }else if( strcmp(currentNode->head->init, "SOUTH")==0) {
                // Transition de bas en haut
                fprintf(fd, "  <path d=\"M %.2f %.2f l %.2f %.2f\"  marker-end=\"url(#head)\"/>\n", currentNode->head->posx , currentNode->head->posy+currentNode->head->size*2, 0.0,-currentNode->head->size);
            }else if( strcmp(currentNode->head->init, "NORTH-WEST")==0){
                // Haut gauche
                fprintf(fd, "  <path d=\"M %.2f %.2f m 8 8 l %.2f %.2f\" marker-end=\"url(#head)\" />\n", currentNode->head->posx - currentNode->head->size*2, currentNode->head->posy-currentNode->head->size*2, currentNode->head->size,currentNode->head->size);
            }else if( strcmp(currentNode->head->init, "NORTH-EAST")==0){
                // Haut gauche
                fprintf(fd, "  <path d=\"M %.2f %.2f m -8 8 l %.2f %.2f\" marker-end=\"url(#head)\" />\n", currentNode->head->posx + currentNode->head->size*2, currentNode->head->posy-currentNode->head->size*2, -currentNode->head->size,currentNode->head->size);
            }else if( strcmp(currentNode->head->init, "SOUTH-EAST")==0){
                fprintf(fd, "  <path d=\"M %.2f %.2f m -8 -8 l %.2f %.2f\" marker-end=\"url(#head)\" />\n", currentNode->head->posx + currentNode->head->size*2, currentNode->head->posy+currentNode->head->size*2, -currentNode->head->size,-currentNode->head->size);
            }else if( strcmp(currentNode->head->init, "SOUTH-WEST")==0){
                fprintf(fd, "  <path d=\"M %.2f %.2f m 8 -8 l %.2f %.2f\" marker-end=\"url(#head)\" />\n", currentNode->head->posx - currentNode->head->size*2, currentNode->head->posy+currentNode->head->size*2, currentNode->head->size,-currentNode->head->size);
            }
        }
        if(strcmp(currentNode->head->final, "NULL") != 0){
            if(strcmp(currentNode->head->final, "WEST") == 0){
                // Transition de gauche à droite
                fprintf(fd, "  <path d=\"M %.2f %.2f l %.2f %.2f\" marker-end=\"url(#head)\"/>\n", currentNode->head->posx-currentNode->head->size, currentNode->head->posy, -currentNode->head->size, 0.0);
            }else if( strcmp(currentNode->head->final, "EAST") == 0 ){
                // Transition de droite à gauche
                fprintf(fd, "  <path d=\"M %.2f %.2f l %.2f %.2f\" marker-end=\"url(#head)\"/>\n", currentNode->head->posx+currentNode->head->size , currentNode->head->posy,currentNode->head->size, 0.0);
            }else if( strcmp(currentNode->head->final, "NORTH")==0){
                // Transition de haut en bas
                fprintf(fd, "  <path d=\"M %.2f %.2f l %.2f %.2f\"  marker-end=\"url(#head)\"/>\n", currentNode->head->posx , currentNode->head->posy-currentNode->head->size, 0.0,-currentNode->head->size);
            }else if( strcmp(currentNode->head->final, "SOUTH")==0) {
                // Transition de bas en haut
                fprintf(fd, "  <path d=\"M %.2f %.2f l %.2f %.2f\"  marker-end=\"url(#head)\"/>\n", currentNode->head->posx , currentNode->head->posy+currentNode->head->size, 0.0,currentNode->head->size);
            }else if( strcmp(currentNode->head->final, "NORTH-WEST")==0){
                // Haut gauche
                fprintf(fd, "  <path d=\"M %.2f %.2f m 8 8 l %.2f %.2f\" marker-end=\"url(#head)\" />\n", currentNode->head->posx - currentNode->head->size, currentNode->head->posy-currentNode->head->size, -currentNode->head->size,-currentNode->head->size);
            }else if( strcmp(currentNode->head->final, "NORTH-EAST")==0){
                // Haut gauche
                fprintf(fd, "  <path d=\"M %.2f %.2f m -8 8 l %.2f %.2f\" marker-end=\"url(#head)\" />\n", currentNode->head->posx + currentNode->head->size, currentNode->head->posy-currentNode->head->size, currentNode->head->size,-currentNode->head->size);
            }else if( strcmp(currentNode->head->final, "SOUTH-EAST")==0){
                fprintf(fd, "  <path d=\"M %.2f %.2f m -8 -8 l %.2f %.2f\" marker-end=\"url(#head)\" />\n", currentNode->head->posx + currentNode->head->size, currentNode->head->posy+currentNode->head->size, currentNode->head->size,currentNode->head->size);
            }else if( strcmp(currentNode->head->final, "SOUTH-WEST")==0){
                fprintf(fd, "  <path d=\"M %.2f %.2f m 8 -8 l %.2f %.2f\" marker-end=\"url(#head)\" />\n", currentNode->head->posx - currentNode->head->size, currentNode->head->posy+currentNode->head->size, -currentNode->head->size,currentNode->head->size);
            }
        }
        currentNode = currentNode->next;
    }
    fprintf(fd, " </g>\n");
    currentNode = nodeList;
    fprintf(fd, " <g dominant-baseline=\"middle\" text-anchor=\"middle\" fill=\"black\">\n");
    while(currentNode){
        fprintf(fd,"  <text x=\"%.2f\" y=\"%.2f\">%s</text>\n", currentNode->head->posx, currentNode->head->posy, currentNode->head->label);
        currentNode = currentNode->next;
    }
    fprintf(fd, " </g>\n");
    return;
}

void drawEdges(svgEdge* edgeList, svg* nodeList, FILE* fd){
    svgEdge* currentEdge = edgeList;
    svg* currentNode;
    double sizenfrom, sizento;
    double d, d2, d3, ratio, dx, dy, xFinal, yFinal, xa,xb,ya,yb;
    double dxB, dyB, ratio2, xInitial, yInitial;
    char* substr;
    fprintf(fd, " <g stroke=\"black\" stroke-width=\"2\" fill=\"none\">\n");
    while(currentEdge){
        currentNode = nodeList;
        sizenfrom= -1, sizento= -1, xa=-1, ya=-1,xb=-1, yb=-1;
        while(currentNode){
            if(strcmp(currentNode->head->id, currentEdge->head->idfrom) == 0){
                sizenfrom = currentNode->head->size;
                xa = currentNode->head->posx;
                ya = currentNode->head->posy;
            }
            if(strcmp(currentNode->head->id, currentEdge->head->idto) == 0){
                sizento = currentNode->head->size;
                xb = currentNode->head->posx;
                yb = currentNode->head->posy;
            }
            currentNode = currentNode->next;
        }
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
        if(strcmp(currentEdge->head->path, "default") != 0){
            // Pas de vérification de conformité de la syntax pour le moment
            if((substr = strstr(currentEdge->head->path, "@sx"))){
                sprintf(substr, "%.3f", xInitial);
            }
            if((substr = strstr(currentEdge->head->path, "@sy"))){
                sprintf(substr, "%.3f", yInitial);
            }
            if((substr = strstr(currentEdge->head->path, "@dx"))){
                sprintf(substr, "%.3f", xFinal);
            }
            if((substr = strstr(currentEdge->head->path, "@dy"))){
                sprintf(substr, "%.3f", yFinal);
            }
            fprintf(fd, "%s\n", currentEdge->head->path);
        }else{
            if(xa != -1 && ya != -1 && ya != -1 && sizento != -1 && xb != -1 && yb  != -1){            
                // Transition boucle
                if( strcmp(currentEdge->head->idfrom, currentEdge->head->idto) == 0){
                    fprintf(fd, "  <path d=\"M %.2f %.2f A %.2f %.2f 0 1 1 %.2f %.2f\" stroke=\"%s\"/>\n", xa+(sizenfrom/3), ya+sizenfrom, sizenfrom/2, sizenfrom/2, xa-(sizenfrom/3), ya+sizenfrom, currentEdge->head->color);
                    fprintf(fd, "  <path d=\"M %.2f %.2f l -11 2 m 9 9 l 2 -11\" stroke=\"%s\"/>\n", xa+(sizenfrom/3)-((sizenfrom/3)*2), ya+sizenfrom, currentEdge->head->color);
                    fprintf(fd, "  <text x=\"%.2f\" y=\"%.2f\">%s</text>\n", (xb + xa)/2 , (yb + ya)/2 + sizenfrom/2*5 , currentEdge->head->label);
                }else{
                    fprintf(fd, "  <path d=\"M %f %f L %f %f\" stroke=\"%s\" marker-end=\"url(#head)\" />\n",  xInitial, yInitial, xFinal, yFinal, currentEdge->head->color);
                    if(xa < xb){
                        // Transition de gauche à droite
                        fprintf(fd, "  <text x=\"%f\" y=\"%f\">%s</text>\n", (xFinal + xInitial)/2, (yFinal + yInitial)/2 - sizenfrom/6, currentEdge->head->label);
                    }else if( xInitial > xFinal){
                        // Transition de droite à gauche
                        fprintf(fd, "  <text x=\"%f\" y=\"%f\">%s</text>\n", (xFinal + xInitial)/2, (yFinal + yInitial)/2 + sizenfrom/3, currentEdge->head->label);
                    }else if( yInitial < yFinal){
                        // Transition de haut en bas
                        fprintf(fd, "  <text x=\"%f\" y=\"%f\">%s</text>\n", (xFinal + xInitial)/2 - sizenfrom/3, (yFinal + yInitial)/2, currentEdge->head->label);
                    }else{
                        // Transition de bas en haut
                        fprintf(fd, "  <text x=\"%f\" y=\"%f\">%s</text>\n", (xFinal + xInitial)/2 + sizenfrom/6, (yFinal + yInitial)/2, currentEdge->head->label);
                    }
                    
                }
            }  
        }  
        currentEdge = currentEdge->next;
    }
    fprintf(fd, " </g>\n");
}
