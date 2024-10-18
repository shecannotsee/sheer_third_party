from setuptools import setup

setup(
    name="double_vector_1D",
    version="0.1.0",
    author="Your Name",
    description="A pybind11 example plugin for modifying a list of doubles",
    packages=["double_vector_1D"],
    package_data={"double_vector_1D": ["double_vector_1D.cpython-310-x86_64-linux-gnu.so"]},
    include_package_data=True,
    zip_safe=False,
)
