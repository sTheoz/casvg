#ifndef OPERATION_H
#define OPERATION_H
#include "automate.h"
#include <stdbool.h>

char* getAlphabet(svgEdge* edges);
char* getAlphabetForNode(svgEdge* edges, char* idNode);

bool checkAlphabet(char* myLabels, char* alpha);
bool isComplete(svgEdge* edges, svg* nodes);
void showComplete(svgEdge* edges, svg* nodes, char* color);
void complete(svgEdge* edges, svg* nodes, char* id, double x, double y);
char* getMissedLabels(char* myLabels, char* alphabet);

bool isDeterministic(svgEdge* edges, svg* nodes);
char* getAlphabetForNodeDeter(svgEdge* edges, char* idNode);
void showDeterministic(svgEdge* edges, svg* nodes, char* color);

bool isAccepted(svgEdge* edges, svg* nodes, char* str);
char* getNodeByLabel(svgEdge* edges, char* idfrom, char label);
char* getInitial(svg* nodes);
#endif