% mylen computes the length of a list

mylen([], 0).
mylen([H|T], L) :- mylen(T, R), L is (R + 1).
