#ifndef DRAWSVG_H
#define DRAWSVG_H
#include "automate.h"
#include <stdio.h>

void draw(char* path, svg* nl, svgEdge* el);
void drawNodes(svg* nodeList, FILE* fd);
void drawEdges(svgEdge* edgeList, svg* nodeList, FILE* fd);

#endif