% msplit returns two lists divided from a single list in preparation
% for merge sort.

msplit([], [], []).
msplit([X], [X], []).
msplit([X,Y|T], L1, L2) :- msplit(T, I1, I2), L1 = [X|I1], L2 = [Y|I2].
