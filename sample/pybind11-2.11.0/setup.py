from setuptools import setup, find_packages
from setuptools.extension import Extension
import os

# 假设 decode_buffer.so 文件位于 build 文件夹
package_data = {'': ['./cmake-build-debug/double_vector_1D.cpython-310-x86_64-linux-gnu.so']}

setup(
    name='double_vector_1D',  # 包名称
    version='0.1',
    description='A Python package for decoding buffer using C++',
    author='Your Name',
    author_email='your.email@example.com',
    packages=find_packages(),  # 查找包
    include_package_data=True,  # 包含 .so 文件u
    package_data=package_data,  # 指定.so文件路径
)
