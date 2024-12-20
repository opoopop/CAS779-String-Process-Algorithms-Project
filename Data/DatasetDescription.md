**n**: length of string s;

**m**: numbers of segments of subsequences

**q**: numbers of queries

**operation 1&2**: correspond to two types of queries from Problem Setting

### Test 1 to 4 include different small cases in order to prove the correctness of the algorithm.

**1:**
multi test cases; n=500; each case with 500 queries; small m(1 to 10); different possibility of operation 1&2; different lengths of segments; different gaps between segments;
different forms of string s: all with 'a'; all random characters; with the form of 'ababab...'

**2:**
multi test cases; small n(20 to 50); each case with 500 or 100 of queries; small m(1 to 3); different possibility of operation 1&2; small length of segment; small gap between segments(relatively constant); 
different forms of string s: all with 'a'; all random characters

**3:**
multi test cases; n between 200 and 400; m=1; q=1
in each of the case, create random characters of palindrome, put it at a random position inside the string s and ask for this substring as a query.

**4:**
multi test cases; different random n in a certain range; random m; q=1
in each of the case, create random characters of palindrome. then divide it into different parts and randomly put these parts into the string s. Ask for these parts. 

### Test 5 to 10 include different small cases in order to test the speed of the algorithm.

**5:**
one case; large n=1e5; large q=1e5; m=1; all with queries of operation 2;
s='aaaa....'
query for the whole string. This query is the same as a substring query.

**6:**
one case; large n=1e5; large q=1e5; m=2; all with queries of operation 2;
s='aaaa...'
query for different size of two segments of the string.

**7:**
one case; large n=1e5; large q=1e5; m between 1 to 3; different lengths of segments; different gaps between segments; all with queries of operation 2;
s='aaaa...'

**8:**
one case; large n=1e5; small q=10; large m with value (n+1)/2; all with queries of operation 2;
s='aaaa...'
the subsequence consist of all s[i] if i is odd.

**9:**
one case; large n=1e5; q=1000; large random m (around 500); different lengths of segments; different gaps between segments; all with queries of operation 2;
s='aaaa...'

**10:**
one case; large n=1e5; q=2000; m=100; different lengths of segments(relatively uneven); different gaps(relatively uneven) between segments; all with queries of operation 2;
s='aaaa...'
