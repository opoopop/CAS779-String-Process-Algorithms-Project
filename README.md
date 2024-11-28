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
- [Test Dataset](#test-dataset)
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

Then we introduce the substring query which will be used as a part of subsequence query. Answer this query take *O(logn)* of time complexity. Addditional, we introduce the *O(logn)* update process in this part. Then for the **Step to Step version** it takse *O(mlogn)* of time complexity for each subsequence query. The complexity of **One step version** is not fixed but according to the test it's smaller or equal to **Step to Step version**. Finally we introduce the **Block version** which can consider as a variant of **Step to Step version** and **One step version**. The time complexity of this version has a upperbound of *O(mlogn)* and a lowerbound of *O(logmlogn)*.

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

So we use a recursive way get the hash value from the bottom to the top. Calculate the hash value take *O(1)* time and the depth of this tree is *O(logn)*, there are *n* of leaves(single character node). So the time complexity of this preocess is *O(nlogn)*.
### Substring Query and String Update 


### Step to Step Version
### One Step Version
### Block Version

## Result Analysis
## possible improvement

## Test Dataset
## Execute The Code
## Additional Part




