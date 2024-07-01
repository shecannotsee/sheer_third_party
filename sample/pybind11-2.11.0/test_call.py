import sys
sys.path.insert(0, './cmake-build-debug')
import double_vector_1D
import double_vector_2D

A = [1.,2.,3.,4.]
B = double_vector_1D.modify(A)
print(B)

print("###################")
C = [[1,2,3,4],[5,6]]
D = double_vector_2D.modify(C)
print(D)
