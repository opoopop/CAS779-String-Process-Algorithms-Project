# Common Part Explanation



This document explain the common part of different versions of algorithm which is the part related to search on the segment tree using hash function and other algorithms.



## Parameter settings

The meaning of each parameter shows on code comments.

We build two segments tree so some of the parameters include a reversed version which include one more dimension. In the whole code, ***j=0*** refer to the reversed version.

```c++
const int N = 2e6 + 100;
const int mod = 1e9 + 7;
//segent tree
struct node
{
    int l; int r;
    ll hash;
    // left and right range
    // hash value calculated by hash function
};
ll h = 1331;// base value of hash function 
ll H[N]; // H[i] refer to h^i

node t[2][4 * N];//node inside segment tree, reversed node included
ll a[N]; // a[i]=s[i] - 'a'; turn a character into a Inteager
ll b[N]; // b[i] is the reversed version of a
int n, m;// length of string ; numbers of segments in subsequence in queries
int pre[2][N];
// prefix array of segments in subsequence, reversed value included

vector<pair<int, int>>sub;
// segments with index of S[L..R] in subseqnence

vector<int>sub_l[2];
vector<int>sub_r[2];
// every L and R in sub, reversed value included
```

## Tree building

This function is used for build the segment tree. We initialize ***p=1, l=1, r=n***. Each time we cut the the string now into two parts from middle and use p to control the index. The recursion stop when it goes to the leaf of the tree.  In this recursive function we use the hash value of left and right child to calculate the hash value in present node.  ***j*** is used for control is this is the reversed one.

```c++
void build(int j, int p, int l, int r)// p refer to index in segment tree
{
    // j=0, reversed one
    t[j][p].l = l;
    t[j][p].r = r;
    if (l == r)
    {
        t[j][p].hash = a[l] * j + b[l] * (1 - j);

        return;
    }
    int mid = (l + r) / 2;
    build(j, p * 2, l, mid);
    build(j, p * 2 + 1, mid + 1, r);

    t[j][p].hash = (t[j][p * 2].hash * H[r - mid] % mod + t[j][p * 2 + 1].hash) % mod;

}
```

## Update of the character

This function is used for update s[**x**] into character **c**. Just like building the tree we update the value recursively until the leaf which is the node of s[**x**], then use the hash value of the child to update it's parent.

```C++
void update(int j, int p, int x, char c)
{
    // j=0, reversed one
    if (t[j][p].l == t[j][p].r)
    {
        t[j][p].hash = c - 'a' + 1;
        return;
    }
    int mid = (t[j][p].l + t[j][p].r) / 2;
    if (x <= mid)
    {
        update(j, p * 2, x, c);
    }
    else
    {
        update(j, p * 2 + 1, x, c);
    }

    t[j][p].hash = (t[j][p * 2].hash * H[t[j][p * 2 + 1].r - mid] % mod + t[j][p * 2 + 1].hash) % mod;
}
```

