//
//  assignment 4 - Graphs.c
//
//
//  Created by Hugh Lavery - 14313812 on 02/12/2016.
//
//

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

#define MAX_EDGES 6
#define MAX_NODES 32

int test[MAX_NODES];
char tested[MAX_NODES];
int count =0;

// adjacency list as structure for graph
//Graph structure containing node structure
//for each node
typedef struct Graph_Node{
    char data;
    bool visited;
    int num_edges;
    int edges[MAX_EDGES];
    int weight[MAX_NODES];
    
    bool is_permenant;
    int parent_index;
    int shortes_length;
    int distance;
} Graph_Node;

typedef struct Graph{
    Graph_Node node[MAX_NODES];
    int num_nodes;
} Graph;

//adding a node with no edge(directionless)
//weights must be given high value for
//my Dijkstras algorithm to work
int add_node(Graph* graph, char data){
    assert(graph);
    
    int index = graph->num_nodes;
    graph->node[index].data = data;
    graph->node[index].num_edges = 0;
    graph->node[index].is_permenant = false;
    graph->node[index].visited = false;
    graph->node[index].parent_index = -1;
    graph->node[index].shortes_length = 999;
    graph->num_nodes++;
    for(int i=0; i < MAX_NODES; i++){
        graph->node[index].weight[i] = 999999;
    }
    return index;
}

//adding an edge for a given node
//for a directionless graph
void add_edge(Graph* graph, int start_node_index,
              int end_node_index, int weight){
    assert(graph);
    //start node
    int num_edges_node1 = graph->node[start_node_index].num_edges;
    graph->node[start_node_index].edges[num_edges_node1] = end_node_index;
    graph->node[start_node_index].weight[end_node_index] = weight;
    graph->node[start_node_index].num_edges++;
    
    //end node
    int num_edges_node2 = graph->node[end_node_index].num_edges;
    graph->node[end_node_index].edges[num_edges_node2] = start_node_index;
    graph->node[end_node_index].weight[start_node_index] = weight;
    graph->node[end_node_index].num_edges++;
    //printf("edge added between index %i and %i\n", start_node_index, end_node_index);
    
}

bool dfs(Graph* graph, int start_at, char find_value);
bool find_dfs(Graph* graph, int start_at, char find_value);
void resetvisited(Graph* graph);
bool dijkstra(Graph* graph, int start_at, char find_value);

int main(){
    Graph graph;
    graph.num_nodes = 0;
    
    //creating array to hold index of each node
    int data_index[100];
    memset(&data_index, -1, sizeof(int)*100);
    
    for (int i='A'; i<='L'; i++){
        data_index[i] = add_node(&graph, (char)i);
    }
    
    //printf("data index for K is %i \n", data_index['K']);
    
    add_edge(&graph, data_index['A'], data_index['B'], 1);
    add_edge(&graph, data_index['B'], data_index['C'], 2);
    add_edge(&graph, data_index['B'], data_index['D'], 2);
    add_edge(&graph, data_index['C'], data_index['E'], 3);
    add_edge(&graph, data_index['C'], data_index['F'], 2);
    add_edge(&graph, data_index['F'], data_index['H'], 1);
    add_edge(&graph, data_index['F'], data_index['I'], 2);
    add_edge(&graph, data_index['F'], data_index['J'], 4);
    add_edge(&graph, data_index['I'], data_index['K'], 11);
    add_edge(&graph, data_index['J'], data_index['L'], 5);
    add_edge(&graph, data_index['J'], data_index['G'], 1);
    add_edge(&graph, data_index['L'], data_index['G'], 3);
    add_edge(&graph, data_index['G'], data_index['K'], 2);
    add_edge(&graph, data_index['G'], data_index['D'], 2);
    
    
    bool found = find_dfs(&graph, 0, 'X');
    found = find_dfs(&graph, data_index['K'], 'B');
    
    found = dijkstra(&graph, data_index['A'], 'X');
    found = dijkstra(&graph, data_index['A'], 'J');
    
    return 0;
}

//function 1 of 2 for DFS. I used two functions so one can
//format the output and call a function to reset the visited
//bool for each node
bool find_dfs(Graph* graph, int start_at, char find_value){
    count =0;
    //printf("test2\n");
    char start = graph->node[start_at].data;
    printf("DFS from %c:\n", start);
    bool dfsfound = false;
    dfsfound = dfs(graph, start_at, find_value);
    //printf("test3\n");
    printf("\n %c ", find_value);
    if (dfsfound == false){
        printf(" was not found in the graph\n\n");
    }
    if (dfsfound == true){
        printf(" was found in the graph\n\n");
    }
    resetvisited(graph);
    return dfsfound;
}
//recursive DFS function. Calls itself (unless it finds
//the char it is looking for) looking at each connection on each node
//(moving one direction until it can go no further and then
// coming back andpicking up where it left off).
bool dfs(Graph* graph, int start_at, char find_value){
    bool found = false;
    //printf("testdfs\n");
    char start = graph->node[start_at].data;
    printf(" %c ", start);
    
    if(start == find_value){
        printf(" target found - HALT\n");
        return true;
    }
    else{
        graph->node[start_at].visited = true;
        for(int i=0; i< graph->node[start_at].num_edges; i++){
            int testing = graph->node[start_at].edges[i];
            if( graph->node[testing].visited == false){
                found = dfs(graph, testing, find_value);
                if (found == true){
                    return found;
                }
            }
        }
        
        
    }
   
    return found;
}

//resets visited bool
void resetvisited(Graph *graph){
    for (int i = 0; i < graph->num_nodes; i++){
        graph->node[i].visited = false;
    }
}

//dijkstras algorithm. Firstly it sets all nodes as unvisited
//is_perminant = false and initalises starting distances to
//very high values except when a node is connected to the starting
//node
bool dijkstra(Graph* graph, int start_at, char find_value){
    //int que[MAX_NODES][3]; //index,parent,shortestpath
    int n = graph->num_nodes;
    int count =0, parent = 0;
    int dist[n];
    char prev[n];
    //printf("index of a is %i", start_at);
    for (int i = 0; i < n; i++){
        if(graph->node[i].data != graph->node[start_at].data){
            graph->node[i].is_permenant = false;
            graph->node[i].parent_index = ' ';
            graph->node[i].shortes_length = 99999;
            if(graph->node[start_at].weight[i] > 0){
                dist[i] = graph->node[start_at].weight[i];
                prev[i] = 'A';
            }
            else{
                dist[i] = 99999;
                prev[i] = 'A';
            }
        }
        //int index = data_index[graph->node[i].data];
        //que[i][0] = index;
    }
    
    //initalising the starting node
    graph->node[start_at].is_permenant = true;
    graph->node[start_at].parent_index = 'A';
    graph->node[start_at].shortes_length = 0;
    dist[start_at] = 0;
    count = 1;
    
    //untill all nodes have been marked perminant
    while(count < n){
        int minimumdistance = 99999;
        //find the node with shortest distance from starting node
        for(int i=0; i < n; i++){
            if(dist[i] < minimumdistance && graph->node[i].is_permenant == false){
                //printf("test 1 \n");
                minimumdistance = dist[i];
                parent = i;
            }
            
            //printf("at %c min dist: %i \n", graph->node[parent].data, minimumdistance );
            graph->node[parent].is_permenant = true;
            //check all connections from the found 'parent' node and find the shortest
            //distance to the next node (smallest weight)
            //Do this until we have a list the shortest path to each node from the root node
            for(int k =0; k< n; k++){
                if(graph->node[k].is_permenant == false){
                    if(minimumdistance + graph->node[parent].weight[k] < dist[k]){
                       // printf("test 2 \n");
                        dist[k] = minimumdistance + graph->node[parent].weight[k];
                        prev[k] = graph->node[parent].data;
                        
                    }
                    
                }
            }
        }
        
        count++;
    }
    char node;
    int pathlenth;
    int parentind;
    char parentnode;
    printf("Dijkstra path from %c length 0\n", graph->node[start_at].data);
    for(int i=0; i < n; i++){
        //print out shortest length and parent node of each node
        //marked permenant
        if(i != start_at && graph->node[i].is_permenant){
            node = graph->node[i].data;
            pathlenth = dist[i];
            parentind = graph->node[i].parent_index;
            parentnode = prev[i];
            
            printf("node: %c shortest length: %i parent: %c \n", node,pathlenth,parentnode);
            if(graph->node[i].data == find_value){
                printf(" target found - HALT\n");
                return true;
            }
        }
    }
    printf(" %c not found in the graph\n\n", find_value);
    return false;
}

