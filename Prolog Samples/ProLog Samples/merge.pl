% merge puts two sorted lists into a single sorted list.

merge([],[],[]).
merge([X],[],[X]).
merge([],[X],[X]).
merge([X|T1], [Y|T2], L) :- X =< Y, merge(T1, T2, I), L = [X,Y|I].
merge([X|T1], [Y|T2], L) :- Y < X, merge(T1, T2, I), L = [Y,X|I].
