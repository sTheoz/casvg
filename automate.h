#ifndef AUTOMATE_H
#define AUTOMATE_H

typedef struct node node;
typedef struct edge edge;
typedef struct svg svg;
typedef struct svgEdge svgEdge;
typedef struct strList strList;
typedef struct position position;

struct node
{
    char* id;
    double posx;
    double posy;
    char* label;
    char* color;
    char* bgcolor;
    double size;
    char* init;
    char* final;
};

struct edge{
    char* idfrom;
    char* idto;
    char* label;
    char* path;
    char* color;
    double posx;
    double posy;
};

struct svg{
    struct node* head;
    struct svg* next;
};

struct svgEdge{
    struct edge* head;
    struct svgEdge* next;
};

struct strList{
    char* val;
    struct strList* next;
};

struct position{
    double x;
    double y;
};

void createNode(char* id);
void createEdge(char* idfrom, char* idto);
void removeNode(char* id);
void removeEdge(char* idfrom, char* idto);
void move(double dx, double dy);
void renameObject(char* oldid, char* newid);
void editNode(char* id);
void editEdge(char* idfrom, char* idto);
void dump();
void dumpSVG(char* name);
void setLabel(char* label);
void setPosition(double x, double y);
void setColor(char* color);
void setBackgroundColor(char* color);
void setSize(double s);
void setInit(char* dir);
void setFinal(char* dir);
void setPath(char* path);

void setNode();
void setEdge();
void doMove();

void initNode(node* n);
void initEdge(edge* e);
void addToList(char* id);

svgEdge* getEdges();
svg* getNodes();

#endif