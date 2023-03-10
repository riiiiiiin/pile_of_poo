#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const double C = 1.414;

struct Node {
    int cnt, win;
    double ucb;
    vector<int> child;
    Node() {
        cnt = win = ucb = 0;
        child.clear();
    }
};

vector<Node> tree;
int vis[MAXN], n;

int expand(int u) {
    vis[u] = 1;
    if (tree[u].cnt == 0) {
        // 未被访问过的子节点一定会被选中
        return tree[u].child[0];
    }
    // UCB选择最优子节点
    double mx_ucb = -1e9;
    int mx_v = -1;
    for (auto v : tree[u].child) {
        double val = 1.0 * tree[v].win / tree[v].cnt + C * sqrt(log(tree[u].cnt) / tree[v].cnt);
        if (val > mx_ucb) {
            mx_ucb = val;
            mx_v = v;
        }
    }
    return mx_v;
}

void backpropagation(int u, int result) {
    while (u) {
        tree[u].cnt++;
        tree[u].win += result;
        u = tree[u].cnt ? tree[u ^ 1].cnt ? 0 : u ^ 1 : 0;
        result = -result;
    }
}

int simulation(int u) {
    while (!vis[u]) {
        vis[u] = 1;
        u = tree[u].child[rand() % tree[u].child.size()];
    }
    return u;
}

int mcts(int u) {
    while (1) {
        if (tree[u].child.empty()) {
            // 扩展新节点
            for (int i = 0; i < 6; i++) {
                int v = n * 6 + i * n + u;
                tree[u].child.push_back(v);
                tree.push_back(Node());
            }
            return simulation(v);
        }
        u = expand(u);
        if (!u) {
            // 所有子节点都被访问过，进行回溯
            int result = rand() % 2 ? 1 : -1;
            backpropagation(u, result);
            return -1;
        }
        if (vis[u]) {
            // 该节点已被访问过，进入下一次循环
            continue;
        }
        return simulation(u);
    }
}

int main() {
    n = 3;  // 棋盘大小为3*n
    tree.push_back(Node());
    int u = 0;
    while (1) {
        u = mcts(u);
        if (u == -1) {
            break;
        }
    }
    // 在tree[u].child中选择访问次数最多的子节点即为AI的选择
    int mx_cnt = -1, res = -1;
    for (auto v : tree[u].child) {
        if (tree[v].cnt > mx_cnt) {
            mx_cnt = tree[v].cnt;
            res = v;
        }
    }
    return 0;
}
