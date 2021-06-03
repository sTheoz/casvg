#ifndef OPERATION_H
#define OPERATION_H
#include "automate.h"
#include <stdbool.h>

char* getAlphabet(svgEdge* edges);
svgEdge* getEdgesForNode(svgEdge* le, char* node);
void clearList(svgEdge* le);
bool checkAlphabetOnEdges(svgEdge* le, char* alpha);
bool isComplete(svgEdge* edges, svg* nodes);
void updateNonCompleteColor(char* color);
void complete(svg* nodes, svgEdge* edges, char* id);
bool isDeterministic(svgEdge* edges, svg* nodes);
void updateNonDeterministicColor(char* color);
bool isAccepted(char* word);

#endif