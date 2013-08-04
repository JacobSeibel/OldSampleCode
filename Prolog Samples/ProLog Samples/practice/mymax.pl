mymax([X],X).
mymax([X|Y],Z) :- mymax(Y,W),W>X,Z is W.
mymax([X|Y],Z) :- mymax(Y,W), W=<X,Z is X.

