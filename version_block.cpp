#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const int N = 2e6 + 100;
const int mod = 1e9 + 7;
//segent tree
struct node
{
    int l; int r;
    ll hash;
    // left and right range
    // hash value calculated by hash value
};
ll h = 10;// base value of hash function from Rabin-Karp
ll H[N]; // H[i] refer to h^i

node t[2][4 * N];
ll a[N]; // a[i]=s[i] - 'a';
ll b[N]; // b[i] is the reversed version of a
int n, m;// length of string ; numbers of L,R of subsequence in queries
int pre[2][N];
// prefix of m [L,R]

vector<pair<int, int>>sub;
// S[L..R] of subseqnence

vector<int>sub_l[2];
vector<int>sub_r[2];
// every L and r in sub.


void build(int j, int p, int l, int r)// p refer to index in segment tree
{
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
    //t[p].hash = max(t[p * 2].hash, t[p * 2 + 1].hash);

    t[j][p].hash = (t[j][p * 2].hash * H[r - mid] % mod + t[j][p * 2 + 1].hash) % mod;

}
void update(int j, int p, int x, char c)
{
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
    // t[p].hash = max(t[p * 2].hash, t[p * 2 + 1].hash);
    t[j][p].hash = (t[j][p * 2].hash * H[t[j][p * 2 + 1].r - mid] % mod + t[j][p * 2 + 1].hash) % mod;
}
ll ask(int j, int p, int l, int r)
{
    ll res = 0;
    if (l <= t[j][p].l && t[j][p].r <= r)
    {
        return t[j][p].hash;

    }
    int mid = (t[j][p].l + t[j][p].r) / 2;
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
ll ask_sqe(int j, int p, int l, int r, int length_now)
{
    // l and r refer to the left and right part of origional range list
    // length refer to the total range we have now




    ll res = 0;
    int mid = (t[j][p].l + t[j][p].r) / 2;
    int opl = int(upper_bound(sub_l[j].begin(), sub_l[j].end(), l) - sub_l[j].begin() - 1);
    int opr = int(upper_bound(sub_l[j].begin(), sub_l[j].end(), r) - sub_l[j].begin() - 1);
    int opmid = int(upper_bound(sub_l[j].begin(), sub_l[j].end(), mid) - sub_l[j].begin() - 1);

    int length_l = 0;
    if (opmid > opr)
    {
        length_l = length_now;
    }
    else if (opmid < opl)
    {
        length_l = 0;
    }
    else
    {
        length_l = pre[j][opmid] - pre[j][opl - 1];
        length_l -= max(0, sub_r[j][opmid] - mid);
        length_l -= max(0, l - sub_l[j][opl]);
    }

    int length_r = length_now - length_l;

    if (length_l != 0)
    {

        if (opl == opmid)res += ask(j, p * 2, l, min(mid, sub_r[j][opmid]));
        else res += ask_sqe(j, p * 2, l, min(r, min(mid, sub_r[j][opmid])), length_l);

    }
    if (length_r != 0)
    {
        if (length_r == length_now)
        {
            if ((opmid + 1 == opr && mid > sub_r[j][opmid]) || opr == opmid)res = (res * H[length_r] % mod + ask(j, p * 2 + 1, l, r)) % mod;
            else res = (res * H[length_r] % mod + ask_sqe(j, p * 2 + 1, l, r, length_r)) % mod;
        }
        else if ((opmid + 1 == opr && mid > sub_r[j][opmid]) || opr == opmid)
        {
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
void  get(string s)
{
    ll res = 0;
    for (auto i : s) { res = res * h + i - 'a' + 1; res %= mod; }
    cout << res << "\n";
}


void solve()
{

    cin >> n;
    int q;
    cin >> q;
    string s;
    cin >> s;
    H[0] = 1;
    for (int i = 1; i <= n; i++)
    {
        a[i] = s[i - 1] - 'a' + 1;
        b[n + 1 - i] = s[i - 1] - 'a' + 1;
        H[i] = H[i - 1] * h % mod;
    }
    build(0, 1, 1, n);
    build(1, 1, 1, n);
    while (q--)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int x;
            cin >> x;
            char c;
            cin >> c;
            update(1, 1, x, c);
            update(0, 1, n + 1 - x, c);
        }
        else {

            sub = { {-1,-1} };
            sub_l[0] = { 0 }; sub_l[1] = { 0 };
            sub_r[0] = { 0 }; sub_r[1] = { 0 };
            pre[0][0] = 0; pre[1][0] = 0;


            cin >> m;
            for (int j = 1; j <= m; j++)
            {
                int l, r;
                cin >> l >> r;

                //assert(l != 0);

                if (l == sub.back().second + 1)
                {
                    sub.back().second = r;
                }
                else sub.push_back({ l,r });

            }
            m = int(sub.size()) - 1;
            for (int i = 1; i <= m; i++)
            {
                pre[1][i] = pre[1][i - 1] + sub[i].second - sub[i].first + 1;

                sub_l[1].push_back(sub[i].first);
                sub_r[1].push_back(sub[i].second);
            }
            for (int i = m; i >= 1; i--)
            {
                int PL = n + 1 - sub[i].second;
                int PR = n + 1 - sub[i].first;
                pre[0][m + 1 - i] = pre[0][m + 1 - i - 1] + PR - PL + 1;

                sub_l[0].push_back(PL);
                sub_r[0].push_back(PR);
            }

            // cut input into blocks ***************************
            vector<vector<int>>block;// index inside every vectory
            int block_num = 2;
            int block_length=m/block_num;
            ll resultl = 0, resultr = 0;
            vector<int>temp;// temporary store the index
            for (int i = 1; i <= m; i++)
            {
                if (!(i % block_length == 0))
                {
                    temp.push_back(i);
                }
                else
                {
                    block.push_back(temp);
                    temp.clear();
                    temp.push_back(i);

                }
            }
            block.push_back(temp);



            for (auto B : block)
            {

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
            // reversed value
            vector<vector<int>>block_r;
            temp.clear();
            int cp_idx = int(block.size()) - 1;
            for (int i = 1; i <= m; i++)
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
            {
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


        }
    }



}
int main() {

    /*1
    14 2
     ababaabaaacaba
          2 3
     1 3
     4 4
     14 14

     2 4
     2 3
     5 6
     9 10
     12 13



     */
    int T = 1;
    cin >> T;
    while (T--)
    {
        solve();
    }




}
