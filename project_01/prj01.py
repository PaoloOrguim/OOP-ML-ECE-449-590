import numpy as np
import easynn as nn

# Create a numpy array of 10 rows and 5 columns.
# Set the element at row i and column j to be i+j.
def Q1():
    rows = 10
    cols = 5

    # Create uninitialized numpy array as per numpy.org documentation
    array = np.empty([rows, cols], dtype = int) # Empty array

    for i in range(rows):
        for j in range(cols):
            array[i, j] = i + j # The indices start at 0 it seems

    return array

# Add two numpy arrays together.
def Q2(a, b):
    return a + b

# Multiply two 2D numpy arrays using matrix multiplication.
def Q3(a, b):
    # @ operator to multiply the matrices
    return a @ b

# For each row of a 2D numpy array, find the column index
# with the maximum element. Return all these column indices.
def Q4(a):
    # From:
    # docs.vultr.com/python/third-party/numpy/argmax
    return np.argmax(a, axis = 1)

# Solve Ax = b.
def Q5(A, b):
    # Solving for x using algorith found on this thread at stackoverflow:
    # Matrix multiplication, solve Ax = b solve for x
    return np.dot(np.linalg.inv(A), b)

# Return an EasyNN expression for a+b.
def Q6():
    # [Lecture 3] EasyNN-1.pdf
    a = nn.Input("a")
    b = nn.Input("b")
    return (a+b)

# Return an EasyNN expression for a+b*c.
def Q7():
    # [Lecture 3] EasyNN-1.pdf
    a = nn.Input("a")
    b = nn.Input("b")
    c = nn.Input("c")
    return (a+b*c)

# Given A and b, return an EasyNN expression for Ax+b.
def Q8(A, b):
    A = nn.Const(A)
    b = nn.Const(b)
    x = nn.Input("x")
    return (A * x + b)

# Given n, return an EasyNN expression for x**n.
def Q9(n):
    x = nn.Input("x")

    if n == 0:
        return 1
    
    aux = x
    for i in range(1, n):
        aux = aux * x
        
    return aux

# Return an EasyNN expression to compute
# the element-wise absolute value |x|.
def Q10():
    relu = nn.ReLU()
    x = nn.Input("x")
    return (relu(x) + relu(-x)) # if x < 0 then relu(-x) = |x| else relu(x) = |x|
