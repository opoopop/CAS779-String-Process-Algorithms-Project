## Table of Contents

- [Common Part Explanation](#common-part-explanation)
  - [Parameter settings](#parameter-settings)
  - [Tree building](#tree-building)
  - [Update of the character](#update-of-the-character)
  - [Calculate the hash value of a substring](#calculate-the-hash-value-of-a-substring)
  - [Calculate the hash value of a subsequence](#calculate-the-hash-value-of-a-subsequence)
  - [Preprocess inside a query](#preprocess-inside-a-query)
- [Step To Step Version Explanation](#step-to-step-version-explanation)
- [One Step Version Explanation](#one-step-version-explanation)
- [Block Version Explanation](#block-version-explanation)

# Common Part Explanation



This part explain the common part of different versions of algorithms which is the part related to search on the segment tree using hash function and other algorithms.



## Parameter settings

The meaning of each parameter shows on code comments.

We build two segments tree so some of the parameters include a reversed version which include one more dimension. In the whole code, **j=0** refer to the reversed version.

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

This function is used for build the segment tree. We initialize **p=1, l=1, r=n**. Each time we cut the the string now into two parts from middle and use **p** to control the index(**p*2** means the left child and **p*2+1** means the right one). The recursion stop when it goes to the leaf of the tree.  In this recursive function we use the hash value of left and right child to calculate the hash value in the present node.  **j** is used for control if this is the reversed version.

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

This function is to calculate the hash value of a substring. We decompose this string into different nodes on the segment tree. Each time we divide the substring using the middle of node's left and right parameter until the node we recurse is fully covered by the substring. Finally we get the hash value from the value that left and right part returned.  **j** is used for control if this is the reversed version.

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

This function return the hash value of a subsequence using substring query as a part of it. **length_now** means the total length of the subsequence in this recursion. We use the middle of node's left and right for the 'cut' and use binary search to quickly find the index of the segments of subsequence wihch [l,r] is smaller or equal to the current **l**, **r**, **mid** with the result of **opl**, **opr**,**opmid**. Then use the prefix array to calculate the next recursion's **length_now**(**length_l** and **length_r**). Notice that when recursing the left and right subsequence, there exist different conditions and for different conditions some parameters for next **ask_sqe()** also should change. conditions include:

1. If the subsequence now is a substring.
2. If we 'cut' at an empty part(means this index do not have the character we want) or inside a substring.
3. There have different relative position relationship between the position we 'cut' and the subsequence.

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



## Preprocess inside a query

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

# Step To Step Version Explanation
Consider this subsequence consist of **m** substrings. Calculate the hash value of each substring and connect them step to step.

```c++
ll vl = 0, vr = 0;
//result of origional and reversed version
for (int i = 1; i <= m; i++)
{
	vl = vl * H[sub_r[1][i] - sub_l[1][i]+1] % mod + ask(1, 1, sub_l[1][i], sub_r[1][i]);
	vl %= mod;
}
for (int i = 1; i <= m; i++)
{
	vr = vr * H[sub_r[0][i] - sub_l[0][i]+1] % mod + ask(0, 1, sub_l[0][i], sub_r[0][i]);
	vr %= mod;
}
if (vl==vr)
{
	puts("Yes");
}
else
{
	puts("No");
}
```
# One Step Version Explanation
In this version  we can use a function directly getting the result. If **m=1** which means this is a substring, go directly to the substring query **ask()** or go to subsequence query **ask_sqe()**. If the hash value of origional and reversed version are the same output `Yes`, otherwise output `No`.  

```c++
if ((m == 1 && ask(1, 1, sub_l[1][1], sub_r[1][m]) == ask(0, 1, sub_l[0][1], sub_r[0][m])) || (m != 1 && ask_sqe(1, 1, sub_l[1][1], sub_r[1][m], pre[1][m]) == ask_sqe(0, 1, sub_l[0][1], sub_r[0][m], pre[0][m])))
{
	puts("Yes");
}
else
{
	puts("No");
}
```
# Block Version Explanation
In block version we divide m substrings of this subsequence into **block_num**(a preset parameter, in this code is 100) of different blocks. Then calculate the final hash value going through these blocks' value.

```c++
// cut input into blocks ***************************
vector<vector<int>>block;// index inside every vectory
int block_num = min(100,m);// number of blocks
int block_length=m/block_num;//length of each block
ll resultl = 0, resultr = 0;// result of origional and reversed version hash value
vector<int>temp;// temporary store the index
for (int i = 1; i <= m; i++)// divide m substrings into blocks
{
    if (!(i % block_length == 0))
    {
        temp.push_back(i);
    }
    else
    {
       if(temp.size()) block.push_back(temp);
        temp.clear();
        temp.push_back(i);

    }
}
if(temp.size())block.push_back(temp);



for (auto B : block)
{// calculate the hash value going through different blocks

    ll length_now = pre[1][B.back()] - pre[1][B[0] - 1];
    resultl = resultl * H[length_now] % mod;
    if (B.size() == 1)
    {
        resultl += ask(1, 1, sub[B[0]].first, sub[B.back()].second);
    }
    else
    {
        resultl += ask_sqe(1, 1, sub[B[0]].first, sub[B.back()].second, length_now);
    }
    resultl %= mod;

}
// reversed version
vector<vector<int>>block_r;
temp.clear();
int cp_idx = int(block.size()) - 1;
for (int i = 1; i <= m; i++)// use the size of origional version to get the reversed version's blocks
{
    temp.push_back(i);
    if (temp.size() == block[cp_idx].size())
    {
        block_r.push_back(temp);
        temp.clear();
        cp_idx--;
    }
}


for (auto B : block_r)
{// reversed version hash value
    ll length_now = pre[0][B.back()] - pre[0][B[0] - 1];
    resultr = resultr * H[length_now] % mod;
    if (B.size() == 1)
    {
        resultr += ask(0, 1, sub_l[0][B[0]], sub_r[0][B.back()]);
    }
    else
    {
        resultr += ask_sqe(0, 1, sub_l[0][B[0]], sub_r[0][B.back()], length_now);
    }
    resultr %= mod;

}

if (resultl == resultr)
{
    puts("Yes");
}
else
{
    puts("No");
}
```
