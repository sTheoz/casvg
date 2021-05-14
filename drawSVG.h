#ifndef DRAWSVG_H
#define DRAWSVG_H
#include "automate.h"

void draw(char* path, svg* nl, svgEdge* el);
void drawNodes(svg* nodeList);
void drawEdges(svgEdge* edgeList);

#endif