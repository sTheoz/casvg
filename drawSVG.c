#include "drawSVG.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

void draw(char* path, svg* nl, svgEdge* el){
    FILE* fd;
    fd = fopen(strcat(path,".svg"), "w");

    if(fd == NULL){
        printf("Error!");   
        exit(1);
    }

    fprintf(fd, "%s", "<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" width=\"800\" height=\"600\" viewBox=\"0 0 800 600\">\n");
    drawNodes(nl);
    drawEdges(el);
    fprintf(fd, "%s", "</svg>\n");
    fclose(fd);
}

void drawEdges(svgEdge* edgeList){

}

void drawNodes(svg* nodeList){
    return;
}
