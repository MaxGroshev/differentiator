#pragma once
#define DEBUG
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_ASSERT.h"

//---------------------------------------------------------------------------------------------------------

struct node_t
{
    const char* shape     = "Mrecord";
    const char* fillcolor = "#eed8cd";
    const char* style     = "filled";
    const char* fontcolor = "#31032A";
    const char* fontname  = "Calibri";
    const char* color     = "white";
    const char* margin    = "";
    const char* label     = "";
};

struct edge_t
{
    const char* constraint = "true";
    const char* fillcolor  = "#8DB6CD";
    const char* style      = "";
    const char* fontcolor  = "";
    const char* fontname   = "Calibri";
    const char* color      = "#8DB6CD";
    const char* label      = "";
};

struct data_stat_t
{
    size_t capacity;
    size_t size;
    int*   head;
    size_t tail;
};

struct dump_graph_t
{
    const char*         orientation = "";
    const char*         splines = "true";
    struct node_t*      nodes;
    struct edge_t*      edges;
    struct data_stat_t  info;
    int                 print_log = 0;
    size_t              node_size;
    size_t              node_capacity;
    size_t              edge_size;
    size_t              edge_capacity;
};

//--------------------------------------------------------------------------------------------------------------------------

void init_graph      (FILE* graphviz, dump_graph_t* graph_dump_set);
void make_node       (FILE* graphviz, dump_graph_t* graph_dump_set, int* node_address, struct node_t nodes, int* right, int* left, int value);
void make_edge       (FILE* graphviz, dump_graph_t* graph_dump_set, int* node_from, int* node_to, struct edge_t edges);
void resize_struct   (dump_graph_t* graph_dump_set);
void print_def_info  (FILE* graphviz, dump_graph_t* graph_dump_set);
void run_graphviz    (FILE* graphviz, FILE* html_logs, dump_graph_t* graph_dump_set);

