#ifndef AUTOMATE_H
#define AUTOMATE_H

typedef struct node node;
typedef struct edge edge;
typedef struct svg svg;
typedef struct svgEdge svgEdge;
typedef struct strList strList;
typedef struct position position;

void createNode(char* id);
void createEdge(char* idfrom, char* idto);
void removeNode(char* id);
void removeEdge(char* idfrom, char* idto);
void move(int dx, int dy);
void renameObject(char* oldid, char* newid);
void editNode(char* id);
void editEdge(char* idfrom, char* idto);
void dump();
void dumpSVG(char* name);
void setLabel(char* label);
void setPosition(int x, int y);
void setColor(char* color);
void setBackgroundColor(char* color);
void setSize(int s);
void setInitial(char* dir);
void setFinal(char* dir);
void setPath(char* path);

void setNode();
void setEdge();
void doMove();

void initNode(node* n);
void initEdge(edge* e);
void addToList(char* id);

#endif