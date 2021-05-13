#ifndef AUTOMATE_H
#define AUTOMATE_H

typedef struct node node;
typedef struct svg svg;

void createNode(char* id);
void createEdge(char* idfrom, char* idto);
void removeNode(char* id);
void removeEdge(char* idfrom, char* idto);
void move(int dx, int dy);
void moveWID(char* id, int dx, int dy);
void moveWIDs(char** tab, int dx, int dy);
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
void setNode();


void initNode(node* n);

#endif