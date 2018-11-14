# uva_11107

This problem is named "Life Form". Basic data structures used here are suffix array (SA) and height array (HA). The height array stores the length of the Longest Common Prefix between 2 suffixes adjacent in suffix array, and the formula is shown as:

HA[i]=length(lcp(suffix(SA[i-1]),suffix(SA[i])))

First, we concatenate all strings into one by adding various delimiters. Next, SA can be built by prefix-doubling method while HA is constructed with SA. Since HA has the following feature: 

LCP(i,j)=min{HA[k]|i+1≤k≤j}

we can claim that suffix SA[i] ~ SA[j] all have the same prefix of length greater than k, if and only if HA[i+1] ~ HA[j] are all greater than k. Hence, to find “the longest common string that is shared by more than half of all life forms” equals to find “the string with the biggest length k where exists an interval in HA with all values no less than k and containing more than half of life forms”. And it is possible to traverse HA by 2 rounds to figure out the biggest length first and then print the relevant string.

There are some tricks in this question. First, when we add delimiters to concatenate strings, all delimiters are required to be distinguishable and the last one should have the smallest value. And in the last step, since it is a constrained maximum problem, we can use binary search to improve efficiency.
