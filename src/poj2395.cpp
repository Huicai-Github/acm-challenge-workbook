/*
 * POJ 2395: Out of Hay
 * 题意：从待选的路里面选出若干将所有点连通，求选出的边里最长边的最小值。
 * 类型：最小生成树
 * 算法：要使得树的最长边最小，那么每次确定的边都应是待选边里最小的，即最小生成树。对应Kruskal算法优先队列取最小值，再用并查集判断连接。
 */

#include <cstdio>
#include <queue>
#include <iostream>

using namespace std;

struct E{
  E() {}
  E(int uu, int vv, int cc): u(uu), v(vv), c(cc) {}
  bool operator > (const E& e) const {
    return c > e.c;
  }
  int u, v, c;
};

int fa[2010];
priority_queue<E, vector<E>, greater<E> > pq;

int find(int x) {
  if(x == fa[x]) return x;
  return fa[x] = find(fa[x]);
}

int Kruskal(int n) {
  for(int i = 1; i <= n; ++i) {
    fa[i] = i;
  }
  int cnt = 1;
  int ans = 0;

  while(cnt < n && !pq.empty()) {
    const E& e = pq.top();
    int u, v, c;
    u = e.u;
    v = e.v;
    c = e.c;
    pq.pop();

    u = find(u);
    v = find(v);
    if(u == v) continue;
    fa[u] = v;
    ans = c;
    ++cnt;
  }
  if(cnt < n) {
    return -1;
  } else {
    return ans;
  }
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  while(m--) {
    int u, v, c;
    scanf("%d%d%d", &u, &v, &c);
    pq.push(E(u, v ,c));
  }
  printf("%d\n", Kruskal(n));
  return 0;
}