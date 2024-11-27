# Get the result
In this version  we can use the function directly getting the result. If **m=1** which means this is a substring, go directly to the substring query **ask()** or go to subsequence query **ask_sqe()**. If the hash value of origional and reversed version are the same output `Yes`, otherwise output `No`.  

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
