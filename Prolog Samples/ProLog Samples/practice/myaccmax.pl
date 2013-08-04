myaccmax([H|T],X) :- accummax(T,H,X).
accummax([],M,M).
accummax([H|T],N,M) :- N>H,accummax(T,N,M).
accummax([H|T],N,M) :- N=<H,accummax(T,H,M).
