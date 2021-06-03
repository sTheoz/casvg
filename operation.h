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

void updateNonCompleteColor(char* color);
bool isDeterministic(svgEdge* edges, svg* nodes);
void updateNonDeterministicColor(char* color);
bool isAccepted(char* word);

#endif