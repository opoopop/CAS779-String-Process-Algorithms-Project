# Table of Contents

- [Problem Setting](#problem-setting)
- [Algorithm](#algorithm)
  - [Abstract](#abstract)
  - [Preprocess Part](#preprocess-part)
  - [Substring Query](#substring-query)
  - [Step to Step Version](#step-to-step-version)
  - [One Step Version](#one-step-version)
  - [Block Version](#block-version)
- [Result Analysis](#result-analysis)
- [Possible Improvement](#possible-improvement)
- [Test Dataset](#test-dataset)
- [Execute The Code](#execute-the-code)


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

Firstly, we use [segment tree](https://en.wikipedia.org/wiki/Segment_tree)(static range tree) combine with the [hash function](https://en.wikipedia.org/wiki/Rabin%E2%80%93Karp_algorithm). Additional, the process of update the string will be introduced int this part because this preocess are the same among different versions of the algorithm. The preprocess of segment tree take *O(nlogn)* of time complexity and *O(nlogn)* of space complexity. The process of update the string in each query take *O(logn)* of time complexity.

Then we introduce the substring query which will be used as a part of subsequence query. Answer this query take *O(logn)* of time complexity.
Then the **Step to Step version** take *O(mlogn)* of time complexity for each subsequence query. The complexity of **One step version** is not fixed but according to the test it's smaller or equal to **Step to Step version**. Finally we introduce the **Block version** which can consider as a variant of **Step to Step version** and **One step version**. The time complexity of this version has a upperbound of *O(mlogn)* and a lowerbound of *O(logmlogn)*.

### Preprocess Part
### Substring Query
### Step to Step Version
### One Step Version
### Block Version

## Result Analysis
## possible improvement

## Test Dataset
## Execute The Code




