# Table of Contents

- [Problem Setting](#problem-setting)
- [Algorithm](#algorithm)
  - [Abstract](#abstract)
  - [Preprocess Part](#preprocess-part)
  - [Substring Query and String Update](#substring-query-and-string-update)
  - [Step to Step Version](#step-to-step-version)
  - [One Step Version](#one-step-version)
  - [Block Version](#block-version)
  - [Additional Part](#additional-part)
- [Result Analysis](#result-analysis)
- [Possible Improvement](#possible-improvement)
- [Details of Implementation](#details-of-implementation)
- [Execute The Code](#execute-the-code)
- [Challenges Encountered](#challenges-encountered)


# CAS779 String Process Algorithms Project - Online String Subsequence Palindrome Detection


## Problem Setting

Give a string ***S*** of length ***N*** consisting of lowercase English letters(it can be any alphabet as long long we give each alphabet a unique number).

Process ***Q*** queries(Here Q is used for facilitate testing) described below in the order they are given.

There are two types of queries:

- `1 x c` Change the *x*-th character of *S* to the lowercase English letter *c*.
- `2 m [L1,R1], [L2,R2]...[Lm,Rm]` If the subsequence which consist of m segments of S is a palindrome, print `Yes`; otherwise, print `No`.

### Input Format
Firstly input a number `T` refer to the number of test cases.

Than for each of the test case. Here, query<sub>i</sub> is the *i*-th query to processing.

```c++
N Q
S
query[1]
query[2]
query[3]
    .
    .
    .
query[Q]
```
Each query is given in one of the following formats:
```c++
1 x c
```
```c++
2 m
L1 R1
L2 R2
  .
  .
  .
Lm Rm
```

### Output Format

Follow the problem description and print the answers `Yes` or `No` to the queries, separated by newlines.

### Sample Input
```c++
2
14 3
ababaabaaacaba
2 4
2 3
5 6
9 10
12 13
1 6 c
2 4
2 3
5 6
9 10
12 13
9 1
aefbcfaea
2 3
1 3
6 6 
8 9
```
### Sample OutInput
```c++
Yes
No
Yes
```
In the first case of sample input, we ask for the subseqnence a***ba***b***aa***ba***aa***c***ab***a which is `baaaaaab` so the output is `Yes`. 

Than we update the string into `ababacbaaacaba` and ask for the same subsequence a***ba***b***ac***ba***aa***c***ab***a which is `baacaaab` so the output is `No`.



## Algorithm
### Abstract
<img src="https://github.com/opoopop/CAS779-String-Process-Algorithms-Project/blob/main/Image/process.png" width="500" height="400" alt="Abstract">

The algorithm explanation part go through different stages, as shown in the picture above.

Firstly, we use [segment tree](https://en.wikipedia.org/wiki/Segment_tree)(static range tree) combine with the [hash function](https://en.wikipedia.org/wiki/Rabin%E2%80%93Karp_algorithm). The preprocess of segment tree take *O(nlogn)* of time complexity and *O(nlogn)* of space complexity. The process of update the string in each query take *O(logn)* of time complexity.

Then we introduce the substring query which will be used as a part of subsequence query. Answer this query take *O(logn)* of time complexity. Additional, we introduce the *O(logn)* update process in this part. Then for the **Step to Step version** it takse *O(mlogn)* of time complexity for each subsequence query. The time complexity of **One step version** is not fixed but it has a lowerbound *O(logmlogn)* and according to the test it's smaller or equal to **Step to Step version**. Finally we introduce the **Block version** which can consider as a variant of **Step to Step version** and **One step version**. The time complexity of this version has the upperbound of *O(mlogn)* and the lowerbound of *O(logmlogn)*. 

### Preprocess Part
In this part we introduce how to construct this segment tree combines with hash function
<img src="https://github.com/opoopop/CAS779-String-Process-Algorithms-Project/blob/main/Image/segmenttree1.png" width="850" height="400" alt="Abstract">

We construct the tree like the picture above. We continue to divide the string into two part from middle until there is a single character. In every node of the tree we don't store the string we just store a **[L,R]** refer to the index in origional string and a harsh value **v**. The depth of this tree is *O(logn)* and it takes *O(nlogn)* of space complexity. Here in conveience of explanation the basic value of hash function **h=10** and **'a'=1;'b'=2;'c=3'**, so how to get the hash value **v** of a certain node x, it can use the following function. Here **x.L** and **x.R** refer to the left and right child of node **x**, **len()** means the length of the string that the node represent.

$$
V_x = V_{x.L} \times h^{len(x.R)} + V_{x.R}
$$

Here is a example of how calculate the hash value of $V_{abcb}$.

<img src="https://github.com/opoopop/CAS779-String-Process-Algorithms-Project/blob/main/Image/segmenttree2.png" width="850" height="400" alt="Abstract">

$V_{ab} =V_{a} \times 10^{1} + V_{b}=12$ and $V_{cb} =V_{c} \times 10^{1} + V_{b}=32$ . Then $V_{abcb}=V_{ab} \times 10^{2} + V_{cb}=1232$

So we use a recursive way get the hash value from the bottom to the top. Calculate the hash value take *O(1)* time and the depth of this tree is *O(logn)*, there are *n* of leaves(single character nodes). So the time complexity of this preocess is *O(nlogn)*. Additionally, we build one more tree for the reversed version, here 'reverse' means we reverse the whole string, For example if the origional string is `abcd` we build a segment tree for `dcba`.
### Substring Query and String Update 
When giving a substring we can get it's hash value through the segment tree. 

<img src="https://github.com/opoopop/CAS779-String-Process-Algorithms-Project/blob/main/Image/segmenttree3.png" width="800" height="300" alt="Abstract">

In this example if we want to calculate the hash value of string `abcbacba`, the string will be divided into three nodes on the tree `abcb` `ac` `b`. Than we use a similar recursive way to get the result from the bottom to the top. There is a important porperty of segment tree is that a substring can be at most divided into *O(logn)* parts. So the time complexity of get a substring's hash value is *O(logn)*. As we get the hash value of this substring we calculate this string in the reversed segment tree, if they are the same than we judge it as a palindrome. 

If we want to update a character in the string we just need to change *O(logn)* of nodes on the tree beacuse a path from the bottom to the top is a simple path on the tree with it's length *O(logn)*. We can update the hash value by simply calculate it again by it's left and right child which take *O(1)*. For example if we want to change `b` these are the nodes we need to change on the segment tree.

<img src="https://github.com/opoopop/CAS779-String-Process-Algorithms-Project/blob/main/Image/segmenttree4.png" width="800" height="300" alt="Abstract">

### Step to Step Version
**Step to step version** means we consider the subsequence as m separate substrings. If we have two string **x**,**y** and their hash value, we combine them together using the following equation, here **len()** means the length of the string.

$$
V_{xy} = V_x \times h^{len(y)} + V_y
$$

We combine the first two substrings together and use the string now combines with the third one...until the last substring. The reversed version is also the same. Finally we compare this two hash values.
### One Step Version
**One step version** means unlike **step to step version**, we can get the hash value on the segment tree in one step. The main concept is that we use the whole subsequence to go throuth the tree. The advantage of this method is that compared with **step to step version**, we can go through one edge on the tree for at most one time, but when going through the edge we need a exta cost. For example. If we use **step to step version** we go through the edge between `abcb` and `abcbacba` twice but now we just go through it for one time. This is like we merge the paths of `a` and `cb`.

<img src="https://github.com/opoopop/CAS779-String-Process-Algorithms-Project/blob/main/Image/segmenttree5.png" width="800" height="300" alt="Abstract">

But why do we need extra cost? Because when calculate the hash value one information we need is the length of a string. We are using the leftmost **L** and rightmost **R** of the subsequence as the parameter to go through the tree. However in the subsequence there exist some 'empty' part(the part which is included in **L** and **R** but do not includ in this subsequence)so we can not simply get the length we want. In order to get the length I use a prefix array which is **m** prefix value for the lengthes of substrings. For example if the susequence is [1,3], [6,7],[13,20] than the prefix array is [3,5,13]. We can use the binary search to get the part we are searching now by **L** and **R** taking *O(logm)* time and use prefix array to get the length we want in *O(1)*. Also in this step we refine the **L** and **R** for the next recursion. Before, we go through a edge and take *O(1)* to calculate the hash value, but now it cost *O(logm)*. For the details of how to use binary search to get the part we want and how to get the length in *O(1)* please read CodeExplanation.md.

You may think that for every time of recursion the time complexity change from *O(1)* to *O(logm)* and we just do the search for one time, so the whole time complexity of this subsequence query algorithm is *O(logmlogn)*. But the answer is No. In the segments tree a part can be represent as *O(logn)* nodes must satisfy that this part is continous. But in our subsequence query though we still use **L** and **R**, some part inside is 'empty'. Give a example of this phenomenon. If in this tree we want a substring the `abcb` than we stop at node 'abcb' we just use one node. However now the subsequence we want is `a` `cb` we go deeper and use more nodes. So only in the best condition, we divide the subsequence into *O(logn)* nodes, The total time complexity is *O(logmlogn)*.    

### Block Version
Now we go to **block version**. both **One Step version** and **Step to Step version** can be considered as a special case of **block version**. In this version we divide the substrings of subsequence into different blocks equally and do **one step version** for each block. Finally, we combine the answer of these blocks together as the result. **Step to Step version** can consider as the number of block is m and in **One Step version** the number is one.

So now what we actually do is a trade-off. If the number of blocks is small than the length of each block is large which means we merge more paths but if we merge more path we spend more *O(logm)* instead of *O(1)*. As what we are going to show in the result analysis the choice of the number of the block will influence the time it spend. There is one thing we can make sure is that if the number of block is 1 than it's a **Step to Step version** so the time comlpexity of **Block version** is *O(mlogn)*, that's why *O(mlogn)* is the upperbound. When m=1 it becomes a **One Step Version**. Though the time it spend is unpredictable we know that *O(logmlogn)* is the lowerbound.

### Additional Part
For all the examples above I use **h=10** as a basic value in hash function and do not take modulo operation. But in the code all the calculation take modulo operation because the result could be out of data storage range. In order to reduce hash collision we use 1331 as basic value and 1e9+7 as the modulo value. This value has already largely deduce the possiblility of hash collusion and we can do more to reduce this possibility. The following operation is not included on the code and can be added into if needed.
Instead of use one hash value we can use a pair of number as the hash value using two different basic and modulo value. **h1=1331, h2=13331, mod1=1e9+7, mod2=998244353** is a good choice. We can use more values as the hash value, the more we use the possibility of hash collision reduced but it cost more time to calculate. I use **long long int** in my code but we can use a larger data storage range which is **int128**. Here is an code example of **int128**.

```c++
inline __int128 read(){
    __int128 x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9'){
        if(ch == '-')
            f = -1;
        ch = getchar();
    }
    while(ch >= '0' && ch <= '9'){
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}
inline void print(__int128 x){
    if(x < 0){
        putchar('-');
        x = -x;
    }
    if(x > 9)
        print(x / 10);
    putchar(x % 10 + '0');
}
__int128 n;
n=read();
```

## Result Analysis
In order to test the result I generate 10 different datesets with standard input and output in:

https://github.com/opoopop/CAS779-String-Process-Algorithms-Project/tree/main/Data/data

Each dataset has different forms of data and the result for the test is generated by a brute force version code. The dataset prove the correctness of the algorithm and test the speed. For the detail of the dataset:

https://github.com/opoopop/CAS779-String-Process-Algorithms-Project/blob/main/Data/DatasetDescription.md

First 4 datasets have small size in order to prove the correctness of the algorithm and it has been proved that the result is correct. So I will only use the last 6 datasets to analyze the speed. Here I use an online jundge system to test the speed because the algorithm only take several seconds so the time of result fluctuate largely if I set a clock inside the code and test on local which can not happen in a online judge system. But I still test each version of algorithm for 10 time and take a average time.  

| Version                                | 5.in  | 6.in  | 7.in  | 8.in  | 9.in  | 10.in |
|----------------------------------------|-------|-------|-------|-------|-------|-------|
| Step to Step version                   | 4 ms  | 2540 ms | 2696 ms | 1444 ms | 1132 ms | 656 ms |
| One Step version                       | 4 ms  | 1836 ms | 2412 ms | 1136 ms  | 920 ms  | 620 ms |
| Block version (block_num=sqrt(m))      | 4 ms  | 2522 ms | 2680 ms | 852 ms  | 760 ms  | 652 ms |

This is the test result of last 6 datasets in **5.in** becasue of this is a substring query so three versions show no differences. In **6.in** and **7.in** the **Block version** is almost the same as **step to step verison** because we select block_num=sqrt(m) and m is small, But **One step version** shows a improvement of the speed. In **8.in** and **9.in** the m is bigger and the **block version** shows better performance but in **10.in** when m=100 all of them have similar performance.

In **8.in** m is large which is equal to 5e4. We select **8.in** to show that the choice of **block_num** will influence the peformance of the algorithm. 

<img src="https://github.com/opoopop/CAS779-String-Process-Algorithms-Project/blob/main/Image/blockanalysist.png" width="540" height="350" alt="graphofperformance">

| Block Number | Time Consumption (ms) |
|--------------|-----------------------|
| 50000        | 1444                  |
| 20000        | 1868                  |
| 10000        | 1208                  |
| 5000         | 1036                  |
| 1000         | 1016                  |
| 500          | 940                   |
| 250          | 840                   |
| 100          | 1040                  |
| 1            | 1136                  |

As we can see from the result when **block_num=250** this algorithm shows much better perforamnce. 
## Possible Improvement
Here I am going to introduce two ways of possible improvement. Base on my analysis of the result the **block_num** in **Block version** should be the parameter we focus on. I use **sqrt(m)** as the value in my code but that may not the best choice. As what the result analysis shows there exist a point or some points which have minimum time consumption. How to find the best number of blocks should be a possible improvement.

The second way is that we use another way to divide the block. In my solution we only focus on dividing m substrings into blocks with equal length. What if we focus on the lengths of those substrings in stead of the number of them. I tried to design a new rule to make the block but the performance of the algorithm is not good. However, focus on the length seems more reasonable, or we can find another ways which focus on different property. 

## Details of Implementation
Detailed explanation of the algorithm:

https://github.com/opoopop/CAS779-String-Process-Algorithms-Project/blob/main/Code/CodeExplanation.md

## Execute The Code
Execute the code of algorithms with three versions:

https://github.com/opoopop/CAS779-String-Process-Algorithms-Project/blob/main/Code/Execute.md

Execute the code of create dataset:

https://github.com/opoopop/CAS779-String-Process-Algorithms-Project/blob/main/Data/Execute.md


## Challenges Encountered
For the design of alogorithm. When I have the **one step version** the time complexity become Non-fixed. So when adjust some of the part of the algorithm the result become unpredictable. As I give a **block version** there exist a parameter making the time consumption different but I can not find a common way which make **block version** perform the best in all datasets. I can just use a intuitive way to explain this phenomenon as a trade-off problem.

For the implement of algorithm. There is one part spend me some time to debug which is the function return a hash value of the whole subsequence(**ask_sqe()**). I use binary seach to locate the index and use prefix array to get the length I want. This step invlove different conditionals. Different conditions correspond to different parameters to the next recursion. The other part went well through coding as I properly use the property of hash function and segment tree.

When designing the dataset. If I just create some datasets randomly, most likely all the result we get is not a palindrome. So I create some palindrome manually and put them inside some places in the string and for each dataset I need to write a new code. I have confident the part I use for the proof of algorithm's correctness is strong but I can not make sure my large-scale dataset can really show the performance of the algorithm. My dataset do not cover all the conditions so there may exist a form of input which my algorithm can not perform well. 




