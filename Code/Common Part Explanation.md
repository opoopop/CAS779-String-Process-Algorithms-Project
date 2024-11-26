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

This function is used for build the segment tree. We initialize **p=1, l=1, r=n**. Each time we cut the the string now into two parts from middle and use **p** to control the index. The recursion stop when it goes to the leaf of the tree.  In this recursive function we use the hash value of left and right child to calculate the hash value in present node.  **j** is used for control if this is the reversed version.

```c++
void build(int j, int p, int l, int r)// p refer to index in segment tree
{
    // j=0, reversed one
    t[j][p].l = l;
    t[j][p].r = r;
    if (l == r)
    {
        t[j][p].hash = a[l] * j + b[l] * (1 - j);//  to the leaf

        return;
    }
    int mid = (l + r) / 2;
    // build left and right part
    build(j, p * 2, l, mid);
    build(j, p * 2 + 1, mid + 1, r);
    
	//update the hash value
    t[j][p].hash = (t[j][p * 2].hash * H[r - mid] % mod + t[j][p * 2 + 1].hash) % mod;

}
```



## Update of the character

This function is used for update s[**x**] into another character **c**. Just like building the tree we update the value recursively until the leaf which is the node of s[**x**], then use the hash value of the child to update it's parent.  **j** is used for control if this is the reversed version.

```C++
void update(int j, int p, int x, char c)
{
    // j=0, reversed one
    if (t[j][p].l == t[j][p].r)
    {
        // find the node of s[x]
        t[j][p].hash = c - 'a' + 1;
        return;
    }
    int mid = (t[j][p].l + t[j][p].r) / 2;
    // check if this node is on the left or right
    if (x <= mid)
    {
        update(j, p * 2, x, c);
    }
    else
    {
        update(j, p * 2 + 1, x, c);
    }
    
    // update hash value
    t[j][p].hash = (t[j][p * 2].hash * H[t[j][p * 2 + 1].r - mid] % mod + t[j][p * 2 + 1].hash) % mod;
}
```



## Calculate the hash value of a substring

This function is to calculate the hash value of a substring. We decompose this string into different nodes on the segment tree. Each time we cut the substring using the middle of node's left and right until the node we recurse is fully covered by the substring. Finally we get the hash value from the value that left and right part returned.  **j** is used for control if this is the reversed version.

```c++
ll ask(int j, int p, int l, int r)
{
    ll res = 0;// result hash value
    if (l <= t[j][p].l && t[j][p].r <= r)
    {
        // find a part which is fully covered
        return t[j][p].hash;

    }
    int mid = (t[j][p].l + t[j][p].r) / 2;
    // middle of this node of the segment tree
    
    // get the result by left and right part
    if (l <= mid)
    {
        res += ask(j, p * 2, l, r);
    }
    if (r > mid)
    {
        res = (res * H[min(r, t[j][p].r) - mid] % mod + ask(j, p * 2 + 1, l, r)) % mod;
    }
    return res;
}
```



## Calculate the hash value of a subsequence

This function return the hash value of a subsequence using substring query as a part of it. **length_now** means the total length of the subsequence in this recursion. We use the middle of node's left and right for the 'cut' and use binary search to quickly find the index of the segments of subsequence wihch [l,r] is smaller or equal to the current **l**, **r**, **mid** with the result of **opl**, **opr**,**opmid**. Then use the prefix array to calculate the next recursion's **length_now**. Notice that when recursing the left and right subsequence, there exist different conditions and for different conditions some parameters for next **ask_sqe()** also should change. conditions include:

1. If the subsequence now is a substring.
2. If we 'cut' at an empty part(means this index do not have the character we want) or inside a substring. 

```C++
ll ask_sqe(int j, int p, int l, int r, int length_now)
{
    // l and r refer to the left and right part of origional range list
    // length refer to the total range we have now




    ll res = 0;
    int mid = (t[j][p].l + t[j][p].r) / 2;//middle of the tree usign for the cut
    
    // use binary search to find the index of the segments of subsequence wihch [l,r] is smaller or equal to the current l, r, mid corresponds to opl, opr,opmid
    int opl = int(upper_bound(sub_l[j].begin(), sub_l[j].end(), l) - sub_l[j].begin() - 1);
    int opr = int(upper_bound(sub_l[j].begin(), sub_l[j].end(), r) - sub_l[j].begin() - 1);
    int opmid = int(upper_bound(sub_l[j].begin(), sub_l[j].end(), mid) - sub_l[j].begin() - 1);

    //calculate using this 'cut', the length of left and right part
    int length_l = 0;
    if (mid >= r)
    {
        length_l = length_now;
    }
    else if (mid < l)
    {
        length_l = 0;
    }
    else
    {
        // use prefix array to calculate the length
        length_l = pre[j][opmid] - pre[j][opl - 1];
        length_l -= max(0, sub_r[j][opmid] - mid);
        length_l -= max(0, l - sub_l[j][opl]);
    }

    int length_r = length_now - length_l;

    // if the left part exist some substrings 
    if (length_l != 0)
    {
        // if the left part now have just one substring, go for the substring query

        if (opl == opmid)res += ask(j, p * 2, l, min(mid, sub_r[j][opmid]));
        else res += ask_sqe(j, p * 2, l, min(r, min(mid, sub_r[j][opmid])), length_l);

    }
    if (length_r != 0)
    {
        if (length_r == length_now)
        {
            // if the right part still have the whole subsequence of last recursion
            if ((opmid + 1 == opr && mid > sub_r[j][opmid]) || opr == opmid)res = (res * H[length_r] % mod + ask(j, p * 2 + 1, l, r)) % mod;
            else res = (res * H[length_r] % mod + ask_sqe(j, p * 2 + 1, l, r, length_r)) % mod;
        }
        else if ((opmid + 1 == opr && mid > sub_r[j][opmid]) || opr == opmid)
        {
            // if the right part now have just one substring, go for the substring query
            if (mid + 1 <= sub_r[j][opmid])
            {
                res = (res * H[length_r] % mod + ask(j, p * 2 + 1, mid + 1, r)) % mod;
            }
            else
            {
                res = (res * H[length_r] % mod + ask(j, p * 2 + 1, sub_l[j][opmid + 1], r)) % mod;
            }
        }
        else
        {
            // if this 'cut' cut at the middle of a substring
            if (mid + 1 <= sub_r[j][opmid])
            {
                res = (res * H[length_r] % mod + ask_sqe(j, p * 2 + 1, mid + 1, r, length_r)) % mod;
            }
            else
            {
                res = (res * H[length_r] % mod + ask_sqe(j, p * 2 + 1, sub_l[j][opmid + 1], r, length_r)) % mod;
            }
        }

    }

    return res;



}
```



## Preprocess when giving a subsequence

When giving a subsequence we need to preprocess it for both origional and reversed version. To facilitate and accelerate the further process we store the [l,r] information and the prefix array of the length of [l,r]. Also we merge two segments if they adjacent to each other. 

```C++
	sub = { {-1,-1} };
			// every [l,r] of the segments

			// origional and reversed version of [l,r]
            sub_l[0] = { 0 }; sub_l[1] = { 0 };
            sub_r[0] = { 0 }; sub_r[1] = { 0 };

			// origional and reversed prefix array of [l,r]
            pre[0][0] = 0; pre[1][0] = 0;
			// pre[i] refer to sum(r[1]-l[1]+1 + r[2]-l[2]+1 ...+ r[i]-l[i]+1)


            cin >> m;
            for (int j = 1; j <= m; j++)
            {
                int l, r;
                cin >> l >> r;
                if (l == sub.back().second + 1)// merge two segments
                {
                    sub.back().second = r;
                }
                else sub.push_back({ l,r });

            }
            m = int(sub.size()) - 1;// number of substrings inside this subsequence
            for (int i = 1; i <= m; i++)
            {
                pre[1][i] = pre[1][i - 1] + sub[i].second - sub[i].first + 1;

                sub_l[1].push_back(sub[i].first);
                sub_r[1].push_back(sub[i].second);
            }
            for (int i = m; i >= 1; i--)
            {
                // reversed value
                int PL = n + 1 - sub[i].second;
                int PR = n + 1 - sub[i].first;
                pre[0][m + 1 - i] = pre[0][m + 1 - i - 1] + PR - PL + 1;

                sub_l[0].push_back(PL);
                sub_r[0].push_back(PR);
            }
```

