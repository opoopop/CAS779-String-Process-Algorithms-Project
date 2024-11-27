## 目录

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

Follow the instructions and print the answers `Yes` or `No` to the queries, separated by newlines.

### Sample Input

## Dataset describtion:

n: length of origional string s;
m: numbers of segments of subsequences queries
q: numbers of queries
operation 1:
operation 2: 
https://github.com/opoopop/CAS779-String-Process-Algorithms-Project/blob/main/datacreate.cpp
### Test 1 to 4 include different small cases in order to prove the correctness of algorithm.

**1:**
multi test cases; n=500; each case with 500 queries; small m(1 to 10); different possibility of update operation; different lengths of segmenst; differents gaps between segments;
different forms of string s: all with 'a'; all random characters; with the form of 'ababab...'

**2:**
multi test cases; small n(20 to 50); each case with 500 or 100 of queries; small m(1 to 3); different possibility of update operation; small length of segment; small gap between segments(relatively constant); 
different forms of string s: all with 'a'; all random characters

**3:**
multi test cases; n between 200 and 400; m=1; q=1
in each of the case, create random characters of palidrome, put it at a random position inside the string s and ask for this substring as a query.

**4:**
multi test cases; different random n in a certain range; random m; q=1
in each of the case, create random characters of palidrome. then cut it into different parts and randomly put these parts into string s. ask for these parts. 

### Test 5 to 10 include different small cases in order to test the speed of the algorithm.

**5:**
one case; large n=1e5; large q=1e5; m=1; all with queries of operation 2;
s='aaaa....'
query for the whole string which the same as a substring query.

**6:**
one case; large n=1e5; large q=1e5; m=2; all with queries of operation 2;
s='aaaa...'
query for different two segments of string.

**7:**
one case; large n=1e5; large q=1e5; m between 1 to 3; different lengths of segmenst; differents gaps between segments;all with queries of operation 2;
s='aaaa...'

**8:**
one case; large n=1e5; small q=10; large m between with value (n+1)/2; all with queries of operation 2;
s='aaaa...'
the subsequence consist of all s[i] if i is odd.

**9:**
one case; large n=1e5; q=1000; large random m (around 500); different lengths of segmenst; differents gaps between segments;all with queries of operation 2;
s='aaaa...'

## Input format:

First line contain a number T means the number of test cases.

In each of the case:

First line contain the length of string n and the number of queries q.

In each of the query:

First a  number op means the choice of operation.

If op  = 1:

Than a number x and a character c. Update the character in position x into character c.

If op=2:

First a number m means the number of segments of this subsequence. Than m lines of two number of L and R means the position of this segment start from L and ends at R.



# asda




