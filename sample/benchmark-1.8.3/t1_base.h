//
// Created by shecannotsee on 2023/2/2.
//

#ifndef GOOGLETEST_TEST_BENCHMARK_TEST_T1_BASE_H_
#define GOOGLETEST_TEST_BENCHMARK_TEST_T1_BASE_H_

#include <benchmark/benchmark.h>

namespace t1_base {

static void BM_SomeFunction(benchmark::State& state) {
  // Perform setup here
  for (auto _ : state) {
    // This code gets timed
    [](){int i=0;};
  }
}
BENCHMARK(BM_SomeFunction);

void main(int argc, char** argv) {
  // init i
  benchmark::Initialize(&argc, argv);
  // run r
  benchmark::RunSpecifiedBenchmarks();
};


};// namespace t1_base

#endif //GOOGLETEST_TEST_BENCHMARK_TEST_T1_BASE_H_
