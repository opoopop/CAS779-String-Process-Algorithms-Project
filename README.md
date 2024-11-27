# Table of Contents

- [Problem Setting](#problem-setting)
  - [op1](#dataset-describtion)
- [第二节内容](#dataset-describtion)
- [第三节内容](#section3)


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





# asda




