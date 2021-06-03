#ifndef OPERATION_H
#define OPERATION_H
#include "automate.h"
#include <stdbool.h>

char* getAlphabet(svgEdge* edges);
char* getAlphabetForNode(svgEdge* edges, char* idNode);

svgEdge* getEdgesForNode(svgEdge* le, char* node);
void clearList(svgEdge* le);
bool checkAlphabet(char* myLabels, char* alpha);
bool isComplete(svgEdge* edges, svg* nodes);
void updateNonCompleteColor(char* color);
void complete(svg* nodes, svgEdge* edges, char* id);
bool isDeterministic(svgEdge* edges, svg* nodes);
void updateNonDeterministicColor(char* color);
bool isAccepted(char* word);

#endif