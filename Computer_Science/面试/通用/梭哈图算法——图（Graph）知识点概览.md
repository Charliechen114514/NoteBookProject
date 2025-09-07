





# 梭哈图算法——图（Graph）知识点概览

​	我们在熟悉数组，链表，树，哈希表等基本的数据结构之后，就可以准备聊聊图了。

​	图是这样的一个数据结构，它由若干个点和描述这些点之间如何连接的线组成。

> 图（Graph）是一种由**顶点（Vertex）**和**边（Edge）**组成的数据结构，用于表示实体之间的各种关系。在计算机科学与日常生活中，图被广泛用于：社交网络、网络路由、推荐系统、任务调度等场景。

​	这也就是说，他的使用是非常广泛的，上到评估交通状况，下到我们的网络路由和好友推介，基本上都是依赖图这个数据结构进行工作的。

## 几个最基本的概念

- **顶点（Vertex/Node）**：图中的基本元素，用来表示实体或对象。
- **边（Edge）**：连接两个顶点的关系，分为有向边和无向边。
  - **无向图**：边没有方向，$(u, v)$ 与 $(v, u)$ 等价。
  - **有向图**：边具有方向，$u \rightarrow v$ 与 $v \rightarrow u$ 为不同的关系。
- **权重（Weight）**：边上的值，用于表示距离、成本、容量等。
- **邻接（Adjacency）**：两个顶点之间是否存在边的关系。

## 如何表达一个图

1. **邻接矩阵（Adjacency Matrix）**

```cpp
const int MAXN = 100;
int adj[MAXN][MAXN]; // adj[i][j] = 权重, 无边时可设为 INF 或 0
```

- 时间复杂度：查询两点是否相邻 $O(1)$
- 空间复杂度：$O(V^2)$，适用于**稠密图。**

1. **邻接表（Adjacency List）**

```cpp
struct Edge { int to, weight; };
vector<Edge> adj[MAXN];
// 添加无向边：
adj[u].push_back({v, w});
adj[v].push_back({u, w});
```

- 时间复杂度：遍历所有边 $O(V + E)$
- 空间复杂度：$O(V + E)$，适用于**稀疏图。**

## 图的遍历：深度优先搜索（DFS）与广度优先搜索（BFS）

### 一、深度优先搜索（DFS）

#### 1. 原理与流程

DFS（Depth-First Search）采用“深入优先”策略：

1. 从起始顶点 `u` 出发，标记为已访问。
2. 对于 `u` 的每一个未访问邻居 `v`：
   - 递归或使用栈进入 `v`，继续执行相同操作。
3. 当 `u` 所有邻居都已访问后，回溯到上一个节点，继续处理其他分支。

这种策略下，路径会沿着一条分支一直深入，直到无法继续，再回退。

#### 2. 递归实现示例（C++）

```
// 深度优先搜索（递归版）
// adj: 图的邻接表，visited: 访问标记
void dfs(int u, const vector<vector<int>>& adj, vector<bool>& visited) {
    visited[u] = true;                     // 标记节点 u 已访问
    // 在此处处理 u，例如打印节点编号
    cout << "Visiting node " << u << endl;

    // 遍历 u 的所有邻居
    for (int v : adj[u]) {
        if (!visited[v]) {                 // 如果邻居 v 未被访问
            dfs(v, adj, visited);         // 递归访问 v
        }
    }
}

// 入口：遍历所有连通分量
void dfsAll(const vector<vector<int>>& adj) {
    int V = adj.size();
    vector<bool> visited(V, false);
    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            dfs(i, adj, visited);         // 对每个未访问节点启动一次 DFS
        }
    }
}
```

- **时间复杂度**: 每条边和顶点各访问一次，。
- **空间复杂度**: 递归栈最坏深度为 O(V)，再加上访问标记 O(V)。

### 二、广度优先搜索（BFS）

#### 1. 原理与流程

BFS（Breadth-First Search）采用“广度优先”策略：

1. 初始化队列 `Q`，将起始顶点 `s` 入队并标记为已访问。
2. 当 `Q` 不为空：
   - 弹出队首顶点 `u`。
   - 处理 `u`（如打印或记录距离）。
   - 对于 `u` 的每个未访问邻居 `v`：
     - 标记 `v` 为已访问，并将其入队 `Q`。
3. 重复直到 `Q` 为空。

这种策略保证按层次顺序访问节点，适合求解无权图的最短路径。

#### 2. 队列实现示例（C++）

```
// 广度优先搜索
// adj: 图的邻接表，visited: 访问标记
void bfs(int s, const vector<vector<int>>& adj, vector<bool>& visited) {
    queue<int> Q;
    visited[s] = true;                    // 标记起始节点已访问
    Q.push(s);                            // 起始节点入队

    while (!Q.empty()) {
        int u = Q.front(); Q.pop();      // 取出队首
        // 在此处处理 u，例如输出节点及其距离
        cout << "Visiting node " << u << endl;

        // 遍历 u 的所有邻居
        for (int v : adj[u]) {
            if (!visited[v]) {            // 如果邻居 v 未访问
                visited[v] = true;       // 标记为已访问
                Q.push(v);               // 将 v 入队，后续处理
            }
        }
    }
}

// 入口：遍历所有连通分量，并可记录从源点的最短距离
void bfsAll(const vector<vector<int>>& adj) {
    int V = adj.size();
    vector<bool> visited(V, false);
    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            bfs(i, adj, visited);
        }
    }
}
```

- **时间复杂度**: 访问所有顶点和边，。
- **空间复杂度**: 队列最坏情况存储 O(V) + 访问标记 O(V)。

一个表看看：

| 特性            | DFS                        | BFS                            |
| --------------- | -------------------------- | ------------------------------ |
| 数据结构        | 递归或栈                   | 队列                           |
| 访问顺序        | 深入一条路径至尽头，再回溯 | 按“层”逐层往外扩展             |
| 最短路径保证    | 不保证（除边权相等情况）   | 保证（无权图）                 |
| 典型应用        | 环检测、连通分量、拓扑排序 | 最短路径、层次遍历、二分图判定 |
| 递归栈/队列开销 | 最坏 O(V)                  | 最坏 O(V)                      |

**选用建议**：

- 若仅需“是否可达”或复杂结构探索，DFS 简洁；
- 若需“最短路径”或“分层次”分析，BFS 性能更优；