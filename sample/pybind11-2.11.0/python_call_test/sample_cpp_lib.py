import sys
sys.path.insert(0, '../cmake-build-debug')

import sample_cpp_lib

# show doc
# help(sample_cpp_lib)

print("add                        -> 2:", sample_cpp_lib.add(1,1))
print("add_param_def              -> 4:", sample_cpp_lib.add_param_def(2,2))
print("add_default_param(default) -> 3:", sample_cpp_lib.add_default_param())
print("add_default_param          -> 6:", sample_cpp_lib.add_default_param(3,3))

p = sample_cpp_lib.Pett("Jack")
print("getName ->  Jack:", p.getName())
p.setName("Marry")
print("getName -> Marry:", p.getName())
print(".name   -> Marry:", p.name)
p.name = "Jack"
print(".name   ->  Jack:", p.name)
print(p)
print(p.__repr__())

person = sample_cpp_lib.Personn("Jack")
print(".name   ->  Jack:", person.name)
person.name = "Marry"
print(".name   -> Marry:", person.name)

enum_test = sample_cpp_lib.NUMBER.ONE
print(enum_test)
sample_cpp_lib.enum_func(enum_test)
enum_test = sample_cpp_lib.NUMBER.TWO
print(enum_test)
sample_cpp_lib.enum_func(enum_test)


