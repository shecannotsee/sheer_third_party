//
// Created by shecannotsee on 23-12-28.
//

#include "global_test_set.h"

#include <fcntl.h>

#include <thread>
#include <mutex>

namespace sys_api {
int open_mock_return_negative_1(const char *__file, int __oflag, ...) {
  return -1;
}

int open_mock_return_0(const char *__file, int __oflag, ...) {
  return 0;
}

int open_mock_return_1(const char *__file, int __oflag, ...) {
  return 1;
}
}// namespace sys_api
TEST(t6_cpp_stub, system_function_mock) {
  // open return -1
  {
    Stub stub;
    stub.set(open, sys_api::open_mock_return_negative_1);
    int expect_negative_1 = open("example.txt", O_RDONLY);
    EXPECT_EQ(expect_negative_1, -1);
  }
  // open return 0
  {
    Stub stub;
    stub.set(open, sys_api::open_mock_return_0);
    int expect_0 = open("example.txt", O_RDONLY);
    EXPECT_EQ(expect_0, 0);
  }
  // open return 1
  {
    Stub stub;
    stub.set(open, sys_api::open_mock_return_1);
    int expect_1 = open("example.txt", O_RDONLY);
    EXPECT_EQ(expect_1, 1);
  }
}

namespace cpp_class_stub {

template<class T>
void *get_ctor_addr(bool start = true) {
  //the start vairable must be true, or the compiler will optimize out.
  if (start) {
    goto Start;
  }
  Call_Constructor:
  //This line of code will not be executed.
  //The purpose of the code is to allow the compiler to generate the assembly code that calls the constructor.
  T();
  Start:
  //The address of the line of code T() obtained by assembly
  char *p = (char * ) && Call_Constructor;//https://gcc.gnu.org/onlinedocs/gcc/Labels-as-Values.html
  //CALL rel32
  void *ret = 0;
  char pos;
  char call = 0xe8;
  do {
    pos = *p;
    if (pos == call) {
      ret = p + 5 + (*(int *) (p + 1));
    }
  } while (!ret && (++p));

  return ret;
}

template<class T>
void *get_dtor_addr(bool start = true) {
  //the start vairable must be true, or the compiler will optimize out.
  if (start) {
    goto Start;
  }
  //This line of code will not be executed.
  //The purpose of the code is to allow the compiler to generate the assembly code that calls the constructor.
  {
    T();
    Call_dtor:;;
  }
  Start:
  //The address of the line of code T() obtained by assembly
  char *p = (char * ) && Call_dtor;//https://gcc.gnu.org/onlinedocs/gcc/Labels-as-Values.html
  //CALL rel32
  void *ret = 0;
  char pos;
  char call = 0xe8;
  do {
    pos = *p;
    if (pos == call) {
      ret = p + 5 + (*(int *) (p + 1));
    }

  } while (!ret && (--p));
  return ret;
}

class foo {
 public:
  foo() { printf("I am foo_constructor\n"); }

  ~foo() { printf("I am foo_dtor\n"); }
};

class foo_mock {
 public:
  foo_mock() { printf("I am foo_mock_constructor\n"); }

  ~foo_mock() { printf("I am foo_mock_dtor\n"); }

};
}// namespace cpp_class_stub
TEST(t6_cpp_stub, constructor_mock) {
  using namespace cpp_class_stub;
  {
    foo entity;
  }
  Stub stub;
  auto foo_c = get_ctor_addr<foo>();
  auto foo_mock_c = get_ctor_addr<foo_mock>();
  stub.set(foo_c, foo_mock_c);
  auto foo_d = get_dtor_addr<foo>();
  auto foo_mock_d = get_dtor_addr<foo_mock>();
  stub.set(foo_d, foo_mock_d);
  foo entity;
}


namespace thread_stub {

template<typename T>
struct get_ctor_addr_thread {
 private:
  template<typename Tp>
  using not_same = std::__not_<std::is_same<std::__remove_cvref_t<Tp>, T>>;
 public:
  template<typename Callable,
    typename... Args,
    typename = std::_Require<not_same<Callable>>>
  void *operator()(bool start, Callable &&f, Args &&... args) {
    //the start vairable must be true, or the compiler will optimize out.
    if (start) {
      goto Start;
    }
    Call_Constructor:
    //This line of code will not be executed.
    //The purpose of the code is to allow the compiler to generate the assembly code that calls the constructor.
    T(std::forward<Callable>(f), std::forward<Args>(args)...);
    Start:
    //The address of the line of code T() obtained by assembly
    char *p = (char * ) && Call_Constructor;//https://gcc.gnu.org/onlinedocs/gcc/Labels-as-Values.html
    //CALL rel32
    void *ret = 0;
    char pos;
    char call = 0xe8;
    do {
      pos = *p;
      if (pos == call) {
        ret = p + 5 + (*(int *) (p + 1));
      }
    } while (!ret && (++p));

    return ret;
  }
};

class thread_mock {
 private:
  // _GLIBCXX_RESOLVE_LIB_DEFECTS
  // 2097.  packaged_task constructors should be constrained
  // 3039. Unnecessary decay in thread and packaged_task
  template<typename Tp>
  using not_same = std::__not_<std::is_same<std::__remove_cvref_t<Tp>,
    thread_mock>>;
 public:
  thread_mock() {
    printf("thread_mock_c success!(default)\n");
  }

  template<typename Callable,
    typename... Args,
    typename = std::_Require<not_same<Callable>>>
  explicit
  thread_mock(Callable &&f, Args &&... args) {
    printf("thread_mock_c success!(function)\n");
  }

  ~thread_mock() {
    printf("thread_mock_d success!\n");
  }
};// class thread_mock

void join_mock() {
  printf("join mock success!\n");
}

int pthread_create_mock(pthread_t *__restrict __newthread,
                        const pthread_attr_t *__restrict __attr,
                        void *(*__start_routine)(void *),
                        void *__restrict __arg) {
  static int ret = 1;
  return ret;
}

void _M_start_thread_mock(std::unique_ptr<std::thread::_State>, void (*)()) {
  printf("thread_mock_c success!(function)\n");
};

}// namespace thread_stub
TEST(t6_cpp_stub, std_thread_mock) {
  // default ctor test
  {
    Stub stub;
    // ctor
    auto std_thread_c = cpp_class_stub::get_ctor_addr<std::thread>();
    auto mock_thread_c = cpp_class_stub::get_ctor_addr<thread_stub::thread_mock>();
    stub.set(std_thread_c, mock_thread_c);
    // dtor
    auto std_thread_d = cpp_class_stub::get_dtor_addr<std::thread>();
    auto mock_thread_d = cpp_class_stub::get_dtor_addr<thread_stub::thread_mock>();
    stub.set(std_thread_d, mock_thread_d);
    // join
    stub.set(ADDR(std::thread, join), thread_stub::join_mock);

    std::thread th;
    th.join();
  }
  // overload ctor test: method 1-success
  printf("\n##### overload thread ctor test to replace the system api function #####\n");
  {
    Stub stub;
    // ctor
    stub.set(pthread_create, thread_stub::pthread_create_mock);
    stub.set(ADDR(std::thread, _M_start_thread), thread_stub::_M_start_thread_mock);
    // dtor
    auto std_thread_d = cpp_class_stub::get_dtor_addr<std::thread>();
    auto mock_thread_d = cpp_class_stub::get_dtor_addr<thread_stub::thread_mock>();
    stub.set(std_thread_d, mock_thread_d);
    // join
    stub.set(ADDR(std::thread, join), thread_stub::join_mock);

    std::function<void()> build_function = []() {
      printf("\nmock thread failed!\n");
    };
    std::thread th(build_function);
    th.join();
  }
  // overload ctor test: method 2-failed
  printf("\n##### overload thread ctor test to get overload ctor address #####\n");
  {
    std::function<void()> build_function = []() {
      printf("\nmock thread failed!\n");
    };
    Stub stub;
    // ctor
//    auto std_thread_c_special = thread_stub::get_ctor_addr_thread<std::thread>()(true, build_function);
//    auto mock_thread_c_special = thread_stub::get_ctor_addr_thread<thread_stub::thread_mock>()(true, build_function);
//    stub.set(std_thread_c_special, mock_thread_c_special);
    // dtor
    auto std_thread_d = cpp_class_stub::get_dtor_addr<std::thread>();
    auto mock_thread_d = cpp_class_stub::get_dtor_addr<thread_stub::thread_mock>();
    stub.set(std_thread_d, mock_thread_d);
    // join
    stub.set(ADDR(std::thread, join), thread_stub::join_mock);

    std::thread th(build_function);
    th.join();
  }
}

TEST(t6_cpp_stub, sleep) {
}
