#include <pybind11/pybind11.h>

#include <iostream>
#include <utility>

int add(int i, int j) {
  return i + j;
}

struct Pet {
  Pet() = delete;
  explicit Pet(const std::string &name) : name_(name) {
  }
  void setName(const std::string &name) {
    name_ = name;
  }
  auto getName() const -> const std::string & {
    return name_;
  }

  std::string name_;
};

class Person {
 private:
  std::string name_;

 public:
  Person(const std::string &name) : name_(name) {
  }
  auto get_name() const -> std::string {
    return name_;
  }

  void set_name(const std::string &name) {
    name_ = name;
  }
};

enum class NUMBER {
  ONE,
  TWO
};

static void enum_func(NUMBER n) {
  if (n==NUMBER::ONE) {
    std::cout << "1\n";
  } else if(n==NUMBER::TWO) {
    std::cout << "2\n";
  }
}

namespace py = pybind11;

PYBIND11_MODULE(sample_cpp_lib, m) {
  m.doc() = "sample_cpp_lib module";  // 可选模块

  m.def("add", &add, "A function that adds two numbers");
  m.def("add_param_def", &add, "A function that adds two numbers", py::arg("i"), py::arg("j"));
  m.def("add_default_param", &add, "A function that adds two numbers", py::arg("i") = 1, py::arg("j") = 2);

  py::class_<Pet>(m, "Pett")
      .def(py::init<const std::string &>())
      .def("setName", &Pet::setName)
      .def("getName", &Pet::getName)
      .def_readwrite("name", &Pet::name_)
      .def("__repr__", [](const Pet &a) { return "<example.Pet named '" + a.name_ + "'>"; });

  py::class_<Person>(m, "Personn")
      .def(py::init<const std::string &>())
      .def_property("name", &Person::get_name, &Person::set_name);

  // 封装枚举类
  py::enum_<NUMBER>(m, "NUMBER")
      .value("ONE", NUMBER::ONE)
      .value("TWO", NUMBER::TWO)
      .export_values();
  m.def("enum_func",&enum_func,"");
}