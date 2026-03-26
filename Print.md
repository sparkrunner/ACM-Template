# ACM 竞赛模板
---

## 00 基础

---
## 01 数据结构
### 树状数组
```cpp
struct Fenwick{
  int n;vector<ll> tr;
  Fenwick(int _n):n(_n),tr(_n+1){}
  void add(int x,ll v){for(;x<=n;x+=x&-x)tr[x]+=v;}
  ll ask(int x){ll res=0;for(;x;x-=x&-x)res+=tr[x];return res;}
};
```
---
## 02 图论

---
## 03 数论

---
## 04 字符串
