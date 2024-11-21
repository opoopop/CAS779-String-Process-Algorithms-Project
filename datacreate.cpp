#include<bits/stdc++.h>
typedef  long long ll;
using namespace std;
int fileNum;//文件数量;
const int mod = 998244353;
const int N = 1e6 + 1000;







struct node
{
    int l; int r;
    ll hash;
    // left and right range
    // hash value calculated by hash value
};
ll h = 1331;// base value of hash function from Rabin-Karp
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

    int length_l = pre[j][opmid] - pre[j][opl - 1];

    //length_l -= l - sub_l[j][opl];
    length_l -= max(0, sub_r[j][opmid] - mid);
    length_l -= max(0, l - sub_l[j][opl]);

    int length_r = length_now - length_l;

    if (length_l != 0)
    {

        if (opl == opmid)res += ask(j, p * 2, l, min(mid, sub_r[j][opmid]));
        else res += ask_sqe(j, p * 2, l, min(mid, sub_r[j][opmid]), length_l);

    }
    if (length_r != 0)
    {

        if ((opmid + 1 == opr && mid > sub_r[j][opmid]) || opr == opmid)
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
            // ask_sqe(0, 1, sub_l[0][1], sub_r[0][m], pre[0][m]);
            // cout<<ask_sqe(1,1,sub_l[1][1],sub_r[1][m],pre[1][m])<<" "<<ask_sqe(0, 1, sub_l[0][1], sub_r[0][m], pre[0][m])<<"\n";

            if ((m == 1 && ask(1, 1, sub_l[1][1], sub_r[1][m]) == ask(0, 1, sub_l[0][1], sub_r[0][m])) || (m != 1 && ask_sqe(1, 1, sub_l[1][1], sub_r[1][m], pre[1][m]) == ask_sqe(0, 1, sub_l[0][1], sub_r[0][m], pre[0][m])))
            {
                puts("Yes");
            }
            else
            {
                puts("No");
            }





            /*            int l, r;
            cin >> l >> r;
            //cout<<ask(1,1,l,r)<<" "<<ask(0,1,n+1-r,n+1-l)<<"\n";
            //get("abcba");
            if (ask(1, 1, l, r) == ask(0, 1, n + 1 - r, n + 1 - l))
            {
                puts("Yes");
            }
            else {
                puts("No");
            }*/

        }
    }



}

























void init() {//初始化;
    srand((unsigned)time(nullptr));//随机数设置时间种子;
    fileNum = 1;//设置文件数量;
}
//获取[0~mod)的随机数;
string title = "D:/xujcdata/5045/";
ll get(ll mod) {
    ll res = 0;
    for (int i = 1; i <= 63; i++) {
        res <<= 1;
        res = res + rand() % 2;
    }
    return res % mod;
}
void solve2()
{
    int n,q;
    cin >> n >> q;
    string s;
    cin >> s;
    s = '0' + s;
    while (q--)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int x; cin >> x; char c;
            cin >> c;
            s[x] = c;
        }
        else
        {
            int m;
            cin >> m;
            string p;
            while (m--)
            {
                int l, r;
                cin >> l >> r;
               
                p += s.substr(l, r - l + 1);
            }
            string pl = p; reverse(pl.begin(), pl.end());
            if (p == pl)
            {
                cout << "Yes\n";
            }
            else
            {
                cout << "No\n";
            }
        }
    }


    return;

}
void get_ans() {
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }

}
//随机生成输入文件;
int st = 1;
int Ed = 1;
void get_in() {// file 2
    for (int i = st; i <= Ed; i++) {
        string _filenameIn = title + to_string(i) + ".in";//拼接输入文件名;
        const char* filenameIn = _filenameIn.data();//string转化成char *;
        freopen(filenameIn, "w", stdout);//开启输出模式;
        int t = 3;
        cout << t << "\n";
        for (int k = 0; k < t; k++)
        {
            string s;
            if (k == 0)
            {

                int n = 50;
                for (int i = 0; i < n; i++)s.push_back('a');
                int q = 100;
                cout << n << " " << q << "\n";
                cout << s << "\n";

              
                while (q--)
                {
                    int rd = rand() % 45;
                    if (!rd)
                    {
                        cout << 1 << "\n" << 1 + rand() % 25 << " " << char('a' + rand() % 15) << "\n";

                    }
                    else
                    {
                        cout << '2' << "\n";
                        int m = 1 + rand() % 2;
                        cout << m << "\n";
                        int l = rand() % 10 + 1;
                        for (int i = 0; i < m; i++)
                        {
                            int r = l + 1 + rand() % 15;
                            cout << l << " " << r << "\n";
                            l = r + 1 + rand() % 15;
                        }
                    }

                }

            }
            else if (k == 1)
            {


                int n = 20;
                for (int i = 0; i < n; i++)s.push_back('a'+rand()%20);
                int q = 500;
                cout << n << " " << q << "\n";
                cout << s << "\n";

                while (q>=250)
                {
                    q--;

                    int rd = rand() % 8;
                    if (!rd)
                    {
                        cout << 1 << "\n" << 1 + rand() % 20 << " " << char('a' + rand() % 20) << "\n";

                    }
                    else
                    {
                        cout << '2' << "\n";
                        int m = 1 + rand() % 2;
                        cout << m << "\n";
                        int l = rand() % 3 + 1;
                        for (int i = 0; i < m; i++)
                        {
                            int r = l + 1 + rand() % 5;
                            cout << l << " " << r << "\n";
                            l = r + 1 + rand() % 5;
                        }
                    }

                }
                while (q--)
                {
                    int rd = rand() % 8;
                    if (!rd)
                    {
                        cout << 1 << "\n" << 1 + rand() % 25 << " " << char('b') << "\n";

                    }
                    else
                    {
                        cout << '2' << "\n";
                        int m = 1 + rand() % 2;
                        cout << m << "\n";
                        int l = rand() % 3 + 1;
                        for (int i = 0; i < m; i++)
                        {
                            int r = l + 1 + rand() % 5;
                            cout << l << " " << r << "\n";
                            l = r + 1 + rand() % 5;
                        }
                    }

                }
            }
            else
            {
                int n = 20;
                for (int i = 0; i < n; i++)s.push_back('a'+rand()%20);
                int q = 500;
                cout << n << " " << q << "\n";
                cout << s << "\n";

                while (q--)
                {
                    int rd = rand() % 2;
                    if (rd)
                    {
                        cout << '2' << "\n";
                        int m = 1 + rand() % 3;
                        cout << m << "\n";
                        int l = 1+rand() % 3;
                        for (int i = 0; i < m; i++)
                        {
                            int r = l + 1 + rand() % 2;
                            cout << l << " " << r << "\n";
                            l = r + 1 + rand() % 2;
                        }
                    }
                    else
                    {
                        cout << 1 << "\n";
                        cout << rand() % n + 1 << " " << char('a' + rand() % 20) << "\n";
                    }

                }
            }


        }
    }
}
void get_in() { //file 1
    for (int i = st; i <= Ed; i++) {
        string _filenameIn = title + to_string(i) + ".in";//拼接输入文件名;
        const char* filenameIn = _filenameIn.data();//string转化成char *;
        freopen(filenameIn, "w", stdout);//开启输出模式;
        int t = 3;
        cout << t << "\n";
        for (int k = 0; k < t; k++)
        {
            string s;
            if (k == 0)
            {

                int n = 500;
                for (int i = 0; i < n; i++)s.push_back('a');
                int q = 200;
                cout << n << " " << q << "\n";
                cout << s << "\n";

                while (q >= 150)
                {
                    q--;
                    // muti-m;short r-l;short l[i+1]-r[i] 
                    cout << '2' << "\n";
                    int m = 10 + rand() % 10;
                    cout << m << "\n";
                    int l = 1+rand() % 30;
                    for (int i = 0; i < m; i++)
                    {
                        int r = l + 1 + rand() % 10;
                        cout << l << " " << r << "\n";
                        l = r + 1 + rand() % 10;
                    }
                }
                while (q >= 100)
                {
                    q--;
                    // small m; mid r-l; mid l[i+1]-r[i]  
                    cout << '2' << "\n";
                    int m = 1 + rand() % 5;
                    cout << m << "\n";
                    int l = 1 + rand() % 50;
                    for (int i = 0; i < m; i++)
                    {
                        int r = l + 1 + rand() % 30;
                        cout << l << " " << r << "\n";
                        l = r + 1 + rand() % 30;
                    }
                }
                while (q >= 75)
                {
                    q--;
                    cout << '2' << "\n";
                    int m = 1;
                    cout << m << "\n";
                    int l = 1 + rand() % 150;
                    for (int i = 0; i < m; i++)
                    {
                        int r = l + 1 + rand() % 300;
                        cout << l << " " << r << "\n";
                        l = r + 1 + rand() % 30;
                    }
                }
                while (q >= 50)
                {
                    q--;
                    cout << '2' << "\n";
                    int m = 1;
                    cout << m << "\n";
                    int l = 200 + rand() % 150;
                    for (int i = 0; i < m; i++)
                    {
                        int r = l + 1 + rand() % 100;
                        cout << l << " " << r << "\n";
                        l = r + 1 + rand() % 30;
                    }
                }
                while (q--)
                {
                    cout << '2' << "\n";
                    int m = 1 + rand() % 3;
                    cout << m << "\n";
                    int l = rand() % 30 + 1;
                    for (int i = 0; i < m; i++)
                    {
                        int r = l + 1 + rand() % 50;
                        cout << l << " " << r << "\n";
                        l = r + 50 + rand() % 20;
                    }
                }

            }
            else if (k == 1)
            {


                int n = 500;
                for (int i = 0; i < n; i++)s.push_back('a' + i % 2);
                int q = 200;
                cout << n << " " << q << "\n";
                cout << s << "\n";

                while (q >= 150)
                {
                    q--;
                    // muti-m;short r-l;short l[i+1]-r[i] 
                    cout << '2' << "\n";
                    int m = 10 + rand() % 10;
                    cout << m << "\n";
                    int l = rand() % 30+1;
                    for (int i = 0; i < m; i++)
                    {
                        int r = l + 1 + rand() % 10;
                        cout << l << " " << r << "\n";
                        l = r + 1 + rand() % 10;
                    }
                }
                while (q >= 100)
                {
                    q--;
                    // small m; mid r-l; mid l[i+1]-r[i]  
                    cout << '2' << "\n";
                    int m = 1 + rand() % 5;
                    cout << m << "\n";
                    int l = 1 + rand() % 50;
                    for (int i = 0; i < m; i++)
                    {
                        int r = l + 1 + rand() % 30;
                        cout << l << " " << r << "\n";
                        l = r + 1 + rand() % 30;
                    }
                }
                while (q >= 75)
                {
                    q--;
                    cout << '2' << "\n";
                    int m = 1;
                    cout << m << "\n";
                    int l = 1 + rand() % 150;
                    for (int i = 0; i < m; i++)
                    {
                        int r = l + 1 + rand() % 300;
                        cout << l << " " << r << "\n";
                        l = r + 1 + rand() % 30;
                    }
                }
                while (q >= 50)
                {
                    q--;
                    cout << '2' << "\n";
                    int m = 1;
                    cout << m << "\n";
                    int l = 200 + rand() % 150;
                    for (int i = 0; i < m; i++)
                    {
                        int r = l + 1 + rand() % 100;
                        cout << l << " " << r << "\n";
                        l = r + 1 + rand() % 30;
                    }
                }
                while (q--)
                {
                    cout << '2' << "\n";
                    int m = 1 + rand() % 3;
                    cout << m << "\n";
                    int l = rand() % 30 + 1;
                    for (int i = 0; i < m; i++)
                    {
                        int r = l + 1 + rand() % 50;
                        cout << l << " " << r << "\n";
                        l = r + 50 + rand() % 20;
                    }
                }
            }
            else
            {
                int n = 500;
                for (int i = 0; i < n; i++)s.push_back('a');
                int q = 200;
                cout << n << " " << q << "\n";
                cout << s << "\n";

                while (q--)
                {
                    int op = rand() % 8;
                    if (op)
                    {
                        cout << '2' << "\n";
                        int m = 1 + rand() % 7;
                        cout << m << "\n";
                        int l = 1+rand() % 50;
                        for (int i = 0; i < m; i++)
                        {
                            int r = l + 1 + rand() % 20;
                            cout << l << " " << r << "\n";
                            l = r + 1 + rand() % 20;
                        }
                    }
                    else
                    {
                        cout << 1 << "\n";
                        cout << rand() % n + 1 << " " << char('a' + rand() % 2) << "\n";
                    }

                }
            }


        }
    }
}
//生成输出文件
void get_out() {
    for (int i = st; i <= Ed; i++) {
        string _filenameOut = title + to_string(i) + ".out";//拼接输出文件名
        string _filenameIn = title + to_string(i) + ".in";//凭借读入文件名
        const char* filenameOut = _filenameOut.data();//转换
        const char* filenameIn = _filenameIn.data();//转换
        freopen(filenameIn, "r", stdin);//开启读入模式，读取文件 filenameIn
        freopen(filenameOut, "w", stdout);//开启输出模式，输出的内容都会存在文件filenameOut
        get_ans();//调用标程 获取正确答案
    }

}
int main() {
    /*
    * 出题顺序一般是:
    * 1. 调用get_in()随机生成in文件 或者手动输入in文件
    * 2. 调用get_out读取in文件生成对应的out文件
    * 3. 上传文件即可
    */

    init();
   get_in();
    get_out();
    //cout << "down";
    return 0;
}
