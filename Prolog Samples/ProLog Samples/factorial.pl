% factorial returns the factorial of a number

factorial(1, 1).
factorial(X, R) :- N is X - 1, factorial(N, I), R is X * I.
