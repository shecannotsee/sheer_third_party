#### 1.Building dependencies

```shell
chmod +x build_dependencies.sh
./build_dependencies.sh
```



#### 2.Convert C++code to Python interface

```shell
mkdir cmake-build-debug
cd cmake-build-debug
cmake ..
make -j8
```

 

#### 3.Calling with Python

```sh
python3 test_call.py
```

