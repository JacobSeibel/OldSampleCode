% fibonacci returns the nth fibonacci number.

fibonacci(0, 0).
fibonacci(1, 1).
fibonacci(N, R) :- (X1 is N - 1, X2 is N - 2, fibonacci(X1, I1), fibonacci(X2, I2), R is (I1 + I2)).

