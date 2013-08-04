del(X, [], []).
del(X, [X|Tail], Tail).
del(X, [H|Tail], [H|Y]) :- del(X, Tail, Y).

