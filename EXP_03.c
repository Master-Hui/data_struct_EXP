#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define max_dis 100000

typedef char vextype[20];
typedef struct {
    int N, E;//N是顶点数，E是边数
    int **matrix;//储存邻接矩阵
    vextype *vertex;//存储节点的名字
} Graph;

Graph createGraph(int n);
int isConnected(Graph g);
void nodeDegree(Graph g, int *node_degree);
double clusteringCoefficient(Graph g);
int dijkstra(Graph g, int start, int end, int *path);
void printPath(int d, int *diameter_path, Graph g);
void DFS(Graph g, int i, int *visited, int *count);
int DFSTraverse(Graph g);

/**
 * 创建一个节点数为n的图
 * @param n 节点个数
 * @return 返回这个图
 */
Graph createGraph(int n) {
    int i, j;
    Graph g;
    g.N = n;
    g.matrix = (int **) malloc(sizeof(int *) * g.N);
    for (i = 0; i < n; i++) {
        g.matrix[i] = (int *) malloc(sizeof(int) * g.N);
    }
    for (i = 0; i < g.N; i++) {
        for (j = 0; j < g.N; j++) {
            g.matrix[i][j] = max_dis;
        }
    }
    for (i = 0; i < g.N; i++) {
        g.matrix[i][i] = 0;
    }
    for(i=0;i<g.N;i++)
    {
        for(j=0;j<g.N;j++)
            g.matrix[i][j]=0;
    }
    g.vertex = (vextype *) malloc(sizeof(vextype) * g.N);
    return g;
}

/**
 * 根据距离d和路径数组path输出路径，这样就不需要路径的节点数也能正确输出路径
 * @param d 路径长度
 * @param diameter_path 储存路径的数组
 * @param g 图
 */
void printPath(int d, int *diameter_path, Graph g)
{
    int k = 0;
    int path_length = 0;
    printf("Path: ");
    do {
        printf("%s->", g.vertex[diameter_path[k]]);
        path_length += g.matrix[diameter_path[k]][diameter_path[k + 1]];
        k++;
    } while (path_length < d);
    printf("%s\n", g.vertex[diameter_path[k]]);
}

void DFS(Graph g, int i, int *visited, int *count) {
    visited[i] = 1;
    *count += 1;
    int j;
    for (j = 0; j < g.N; j++) {
        if (0 != g.matrix[i][j] && max_dis != g.matrix[i][j] && 0 == visited[j]) {
            DFS(g, j, visited, count);
        }
    }
}

int DFSTraverse(Graph g) {
    int i;
    int count = 0;
    int *visited = (int *) malloc(sizeof(int) * g.N);
    for (i = 0; i < g.N; i++)
    {
        visited[i] = 0;
    }
    DFS(g, 0, visited, &count);
    free(visited);
    return count;
}

/**
 * 判断图是否连通
 * @param g 图
 * @return 连通返回1，否则返回0
 */
int isConnected(Graph g) {
    int i=0,flag=0,count=0;

    int* visited = (int *) malloc(sizeof(int) * g.N);
    for(i = 0;i<g.N;i++)
    {
        visited[i]=0;
    }
    DFS(g,0,visited,&count);
    free(visited);
    if (count == g.N)
        flag = 1;
    return flag;
    //TODO
}

/**
 * 计算每个点的度
 * @param g 图
 * @param node_degree 将每个点的度写到这个数组中
 */
void nodeDegree(Graph g, int *node_degree) {
   for(int k = 0;k<g.N;k++)//node_degree初始化
   {
       node_degree[k]=0;
   }
   for(int i = 0;i<g.N;i++)
   {
       for(int j = 0;j<g.N;j++)
       {
           if(g.matrix[i][j]!=0)
            node_degree[i]++;
       }
   }
    //TODO
}

/**
 * 计算图的聚类系数
 * @param g 图
 * @return 返回聚类系数
 */
double clusteringCoefficient(Graph g) {
    double node_coff=0,graph_coff=0;//分别为节点聚类系数，图的聚类系数
    int edge[max_dis]={0};
    int i=0,l=0,k=0;
    for(int i=0;i<g.N;i++)
    {
        k=0;
        for(int j =0;j<g.N;j++)//与一节点所连边数
        {
            if(g.matrix[i][j]!=0)
                edge[k++]=j;
        }
        for(int q=0;q<k;q++)//相邻节点所连边数
        {
            for(int p=q;p<k;p++)
            {
                if(g.matrix[edge[q]][edge[p]]!=0)
                    node_coff++;
            }
        }
        if(k>1)
            node_coff = node_coff/((double)k*((double)k-1)/2);//计算该节点的聚类系数
        graph_coff+=node_coff;
        node_coff=0;

    }
    graph_coff = graph_coff/g.N;
    return graph_coff;
    //TODO
}

/**
 * 使用dijkstra算法计算单源最短路径
 * @param g 图
 * @param start 起点
 * @param end 终点
 * @param path 从start到end的路径, [start,...,end]
 * @return 路径长度
 */
int dijkstra(Graph g, int start, int end, int *path)
{
    int INF = 60000;
    int dis[max_dis]={0};//节点最短路径
    int prev[max_dis]={0};//前驱结点
    int temp,i,j,k,min;

    for(i=0;i<g.N;i++)
    {
        prev[i]=start;
        dis[i]=g.matrix[start][i];//最短路径初始化
        if(dis[i]==0&&i!=start)
            dis[i]=INF;
    }
    for(i=1;i<g.N;i++)
    {
        for(j=0;j<g.N;j++)
        {
            if(dis[j]<INF)
            {
                min = dis[j];
                k=j;
            }
        }
        for(j=0;j<g.N;j++)
        {
            temp = (g.matrix[k][j]==INF?INF:(min+g.matrix[k][j]));
            if(dis[j]>temp)
            {
                dis[j]=temp;
                prev[j]=k;
            }
        }
    }
    i=0;
    path[i++]=end;
    do
    {
        path[i++]=prev[end];
        end=prev[end];
        printf("%d\n",path[i-1]);
    }while(prev[end]!=start);
    return dis[end];


    //TODO
}

int main() {
    int node_num;
    int edge_num;
    int ca = 1;
    if (freopen("stu.in", "r", stdin) == NULL) {
        printf("There is an error in reading file stu.in");
    }
    while (scanf("%d %d\n", &node_num, &edge_num) != EOF) {
        printf("\ncase %d:\n", ca++);
        int start_idx, end_idx, weight;
        Graph g = createGraph(node_num);
        for(int i = 0; i < node_num; i++) {
            sprintf(g.vertex[i], "%d", i);
        }
        for (int i = 0; i < edge_num; i++) {
            scanf("%d %d %d\n", &start_idx, &end_idx, &weight);
            g.matrix[start_idx][end_idx] = weight;
            g.matrix[end_idx][start_idx] = weight;
        }

        printf("connected: %d\n", isConnected(g));

        int *degree = (int *)malloc(sizeof(int) * g.N);
        nodeDegree(g, degree);
        printf("degree distribution:\n");
        for(int i=0; i<g.N; i++)
        {
            printf("node%s:%d,", g.vertex[i], degree[i]);
        }
        printf("\n");
        free(degree);

        double c = clusteringCoefficient(g);
        printf("clustering coefficient:%f\n", c);

        if(isConnected(g))
        {
            int *short_path = (int *)malloc(sizeof(int) * g.N);
            int dis = dijkstra(g, 1, 3, short_path);
            printf("the shortest path between 1 and 3: %d\n", dis);
            printPath(dis, short_path, g);
            free(short_path);
        }
    }
    return 0;
}
