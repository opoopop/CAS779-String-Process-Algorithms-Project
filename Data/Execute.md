# Execute the code

Run the code from **DataCreate.cpp** to create the data.

Firstly your execute environment should follow:

https://github.com/opoopop/CAS779-String-Process-Algorithms-Project/blob/main/Code/Execute.md

Change your own path to store **.in** and **.out** document.

```c++
string title = "D:/xujcdata/5045/";
```

This is the start and end of the document if you give value like this it will create **1.in, 1.out, 2.in, 2.out**.

```c++
int st = 1;
int Ed = 2;
```

There are 10 functions to create different forms of datasets with their name from **get_in1()** to **get_in10()** correspond to the code of 10 datasets in **DatasetDescription.md**. This is one of the **get_in** function.

```c++
void get_in3() {//file 3
    for (int i = st; i <= Ed; i++) {
        string _filenameIn = title + to_string(i) + ".in";//拼接输入文件名;
        const char* filenameIn = _filenameIn.data();//string转化成char *;
        freopen(filenameIn, "w", stdout);//开启输出模式;
        int t = 20;
        cout << t << "\n";
        while(t--)// 200 of s 
        {
            string s;
            // input size q*m*2
            // solve() time complexity , upper bound q*m*log N 
                int n = 0;

                int q = 1;
                    string asks;// asked string 
                    string tp;
                    for (int j = 0; j <= 50 + rand() % 50; j++)
                    {
                        tp.push_back('a' + rand() % 20);
                        
                    }
                    asks = tp;
                    reverse(tp.begin(), tp.end());
                    asks += tp;
                   
                    for (int j = 0; j <= 30+rand()%20; j++)//50
                    {
                        s.push_back('a' + rand() % 20);
                    }
                    
                    
                int askl = 0, askr = 0;
                askl = s.size() + 1;
                askr = askl + asks.size() - 1;
                s.append(asks);
                for (int j = 0; j <= 30 + rand() % 20; j++)//50
                {
                    s.push_back('a' + rand() % 20);
                }
                n = s.size();
                cout << n << " " << q << "\n";
                cout << s << "\n";
                while (q--)
                {

                        cout << '2' << "\n";
                        int m = 1;
                        cout << m << "\n";
                        cout << askl << " " << askr << "\n";



                }

  


        }
    }
}
```

Select a **get_in()** at the end of the code and use it to create your data. Notice your data may be different from the data I create because there exist some random part. If you want to design your own data just write your own **get_in()** function follow my input and output format.

```C++
int main() {

    init();
    get_in();
    get_out();

    return 0;
}
```

**get_out()** is used for create the output document and **get_ans()** is a part of it. In my code I use a brute force version of code to get the answer.

```c++
void solve_bruteforce()
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
        solve_bruteforce();
    }

}
```
If you want to run the data I create on https://github.com/opoopop/CAS779-String-Process-Algorithms-Project/tree/main/Data/data just comment out the **get_in()** line and remember to use a new name of file to store the result in case of it cover my **.out** file. Finally compare your result with my result through **.out** document.
```C++
int main() {

    init();
    //get_in();
    get_out();

    return 0;
}
```
