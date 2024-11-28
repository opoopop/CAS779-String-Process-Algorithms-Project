# Table of Contents

- [Problem Setting](#problem-setting)
- [Algorithm](#algorithm)
  - [Abstract](#abstract)
  - [Preprocess Part](#preprocess-part)
  - [Substring Query and String Update](#substring-query-and-string-update)
  - [Step to Step Version](#step-to-step-version)
  - [One Step Version](#one-step-version)
  - [Block Version](#block-version)
- [Result Analysis](#result-analysis)
- [Possible Improvement](#possible-improvement)
- [Execute The Code](#execute-the-code)
- [Additional Part](#additional-part)


# CAS779 String Process Algorithms Project - Online String Subsequence Palindrome Detection


## Problem Setting

Give a string ***S*** of length ***N*** consisting of lowercase English letters.

Process ***Q*** queries(Here Q is using for facilitate testing) described below in the order they are given.

There are two types of queries:

- `1 x c` Change the *x*-th character of *S* to the lowercase English letter *c*.
- `2 m [L1,R1], [L2,R2]...[Lm,Rm]` If the subsequence which consist of M segments of S is a palindrome, print `Yes`; otherwise, print `No`.

### Input Format
Firstly input a number `T` refer to the number of test cases.

Than for each of the test case. Here, query<sub>i</sub> is the *i*-th query to be processed.

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
In the first case of sample input,we ask for the subseqnence a***ba***b***aa***ba***aa***c***ab***a which is `baaaaaab` so the output is `Yes`. 

Than we update the string into `ababacbaaacaba` and ask for the same subsequence a***ba***b***ac***ba***aa***c***ab***a which is `baacaaab` so the output is `No`.



## Algorithm
### Abstract
<img src="https://github.com/opoopop/CAS779-String-Process-Algorithms-Project/blob/main/Image/process.png" width="500" height="400" alt="Abstract">

The algorithm explanation part go through different stages shows as the picture above.

Firstly, we use [segment tree](https://en.wikipedia.org/wiki/Segment_tree)(static range tree) combine with the [hash function](https://en.wikipedia.org/wiki/Rabin%E2%80%93Karp_algorithm). The preprocess of segment tree take *O(nlogn)* of time complexity and *O(nlogn)* of space complexity. The process of update the string in each query take *O(logn)* of time complexity.

Then we introduce the substring query which will be used as a part of subsequence query. Answer this query take *O(logn)* of time complexity. Addditional, we introduce the *O(logn)* update process in this part. Then for the **Step to Step version** it takse *O(mlogn)* of time complexity for each subsequence query. The time complexity of **One step version** is not fixed but it has a lowerbound *O(logmlogn)* and according to the test it's smaller or equal to **Step to Step version**. Finally we introduce the **Block version** which can consider as a variant of **Step to Step version** and **One step version**. The time complexity of this version has a upperbound of *O(mlogn)* and the lowerbound can be lower than *O(logmlogn)*.

### Preprocess Part
In this part we introduce how to construct this segment tree combined with hash function
<img src="https://github.com/opoopop/CAS779-String-Process-Algorithms-Project/blob/main/Image/segmenttree1.png" width="850" height="400" alt="Abstract">

We construct the tree like the picture above. We continue to divide the string into two part from middle until there is a single character. In every node of the tree we don't store the string we just store a **[L,R]** refer to the index in origional string and a harsh value **v**. The depth of this tree is *O(logn)* and levels have 1,2,4,8...n of nodes, so it take *O(nlogn)* of space complexity. Here the basic value of hash function **h=10** and **'a'=1;'b'=2;'c=3'**, so how to get the hash value **v** of a certain node x, it can use the following function. Here **x.L** and **x.R** refer to the left and right children of node **x**, **len()** means the length of the string that the node represent.

$$
V_x = V_{x.L} \times h^{len(x.R)} + V_{x.R}
$$

Here is a example of how calculate the hash value of $V_{abcb}$.

<img src="https://github.com/opoopop/CAS779-String-Process-Algorithms-Project/blob/main/Image/segmenttree2.png" width="850" height="400" alt="Abstract">

$V_{ab} =V_{a} \times 10^{1} + V_{b}=12$ and $V_{cb} =V_{c} \times 10^{1} + V_{b}=13$ . Then $V_{abcb}=V_{ab} \times 10^{2} + V_{cb}=1232$

So we use a recursive way get the hash value from the bottom to the top. Calculate the hash value take *O(1)* time and the depth of this tree is *O(logn)*, there are *n* of leaves(single character node). So the time complexity of this preocess is *O(nlogn)*. Additionally, we build one more tree for the reversed version, here revere means we reverse the whole string, For example if the origional string is `abcd` we build a segment tree for `dcba`.
### Substring Query and String Update 
If give a substring we can get it's hash value through the segment tree. 

<img src="https://github.com/opoopop/CAS779-String-Process-Algorithms-Project/blob/main/Image/segmenttree3.png" width="800" height="300" alt="Abstract">

In this example if we want to calculate the hash value of string `abcbacba` it's divide into three nodes on the tree `abcb` `ac` `b`. Than we use a similar recursive way to get the result from the bottom to the top. There is a important porperty of segment tree is that a substring can be at most divided into *O(logn)* parts. So the time complexity of get a substring's hash value is *O(logn)*. As we get the hash value of this substring we calculate this string in the reversed segment tree, if they are the same than we judge it as a palindrome. 

If we want to update a character in the string we just need to change *O(logn)* of nodes on the tree beacuse a path from the bottom to the top is a simple path on the tree with it's length *O(logn)*. We can update the hash value by simply calculate it again by it's left and right children which take *O(1)*. For example if we want to change `b` these are the noodes we need to change throught the segment tree.

<img src="https://github.com/opoopop/CAS779-String-Process-Algorithms-Project/blob/main/Image/segmenttree4.png" width="800" height="300" alt="Abstract">

### Step to Step Version
Step to step version means we consider the subsequence as m separate substrings. If we have two string **x**,**y** and their hash value, we combine them together using the following equation, here **len()** means the length of the string.

$$
V_{xy} = V_x \times h^{len(y)} + V_y
$$

We combine the first two substrings together and use the string now combine with the thid one...until the last substring. The reversed version is also the same. Finally we compare this two hash values.
### One Step Version
One step version means unlike step to step version we get the hash value on the segment tree in one step. The main concept is that we use the whole subsequence to go throuth the tree. The advantage of this method is that compare with step to step version we go through one eage at most one time but when go through the eage we need a exta cost. For example. If we use step to step version we go through the edge between `abcb` and `abcbacba` twice but now we just go through it for one time. This is like we merge the paths of `a` and `cb`.

<img src="https://github.com/opoopop/CAS779-String-Process-Algorithms-Project/blob/main/Image/segmenttree5.png" width="800" height="300" alt="Abstract">

But why do we need extra cost? Because when calculate the hash value one information we need is the length of a string. We are using the leftmost **L** and rightmost **R** of the subsequence as the parameter to go through the tree. However in the subsequence there exist some 'empty' part(the part which is included in **L** and **R** but do not included in this subsequence)so we can not simply get the length we want. In order to give the length I use a prefix array which is **m** prefix value for the lengthes of substrings. For example if the susequence is [1,3], [6,7],[13,20] than the prefix array is [3,5,13]. We can use the binary search to get the part we are searching now by **L** and **R** taking *O(logm)* and use prefix array to get the length we want in *O(1)*. Also in this step we refine the **L** and **R** after go to the left and right children. Before we go through a eage and take *O(1)* to calculate the hash value. But now it cost *O(logm)*. For the detail of how to use binary search to get the part we want and how to get the length in *O(1)* please read CodeExplanation.md.

You may think that for each step we go through the tree the time complexity change from *O(1)* to *O(logm)* and we just do a search for one time. So the whole time complexity of this subsequence query algorithm is *O(logmlogn)*. But the answer is No. In a segments tree a part can be represent as *O(logn)* nodes must satisfy that this part is continous. But in our subsequence query though we still use **L** and **R** but some part inside is 'empty'. Give a example of this phenomenon. If in this tree we want a substring the `abcb` than we stop at node 'abcb' we just use one node. However now the subsequence we want is `a` `cb` we go deeper and use more nodes. So in the best condition, we divide the subsequence into *O(logn)* nodes, The total time complexity is *O(logmlogn)*.    

### Block Version
Now we go to block version. both One Step Version and Step to Step version can be considered as a special case of block version. We know divide the substrings of subsequence into different blocks equally and do one step version in each block. Finally we combine the answer of these blocks together as the  result. Step to Step version can consider as the number of block is m and in One Step version the number is one.

So now what we actually do is a trade-off. If the number of blocks is small than the length of each block is large which means we merge more paths but if we merge more path we spend more *O(logm)* instead of *O(1)*. As what we are going to show in the result analysis the choice of the number of the blocks will influence the time complexity. There is one thing we can make sure is that if the number of block is 1 than it's a Step to Step version so the time comlpexity of Block version is *O(mlogn)*. In the best condition it may be even lower than *O(logmlogn)* when m=1(One Step Version).
## Result Analysis
In order to test the result I generate 10 different dateset with standard input and output format at:
https://github.com/opoopop/CAS779-String-Process-Algorithms-Project/tree/main/Data/data
. Each dataset has different forms of data and the result for test is generated by a brute force version. The dataset prove the correct of the algorithm and test the speed. For the detail of the dataset:
https://github.com/opoopop/CAS779-String-Process-Algorithms-Project/blob/main/Data/DatasetDescription.md

First 5 dataset have small in order to prove the correctness of the algorithm and it have been proved that the result is correct. So I will only use the last 5 dataset to analysis the speed. Here I use an online jundge system to test the speed because the algorithm only take several seconds so the time of result fluctuate largely if a set a clock on local which would not happen in a online judge system. But I still test each version of algorithm for 10 time and take a average time.  

## possible improvement


## Execute The Code
## Additional Part




