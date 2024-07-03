#include <eigen3/Eigen/Dense>
#include <iostream>

int main() {
  // 使用Eigen命名空间
  using namespace Eigen;

  // 定义两个2x2矩阵并初始化
  Matrix2d mat1;
  mat1 << 1, 2, 3, 4;

  Matrix2d mat2;
  mat2 << 5, 6, 7, 8;

  // 矩阵相加
  Matrix2d sum = mat1 + mat2;
  std::cout << "Matrix sum:\n" << sum << std::endl;

  // 矩阵乘法
  Matrix2d product = mat1 * mat2;
  std::cout << "Matrix product:\n" << product << std::endl;

  // 矩阵转置
  Matrix2d transpose = mat1.transpose();
  std::cout << "Matrix transpose:\n" << transpose << std::endl;

  return 0;
}
