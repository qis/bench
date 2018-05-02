#include <algorithm>
#include <numeric>
#include <string>
#include <cstring>

const auto str = []() {
  std::string str;
  str.resize(1024);
  std::iota(str.begin(), str.end(), '\0');
  return str;
}();

static void bench_copy(benchmark::State& state) {
  std::vector<char> buffer;
  buffer.resize(str.size() + 1);
  for (auto _ : state) {
    std::copy(str.begin(), str.end(), buffer.begin());
  }
}
BENCHMARK(bench_copy);

static void bench_string_copy(benchmark::State& state) {
  std::string buffer;
  buffer.resize(str.size() + 1);
  for (auto _ : state) {
    buffer = str;
  }
}
BENCHMARK(bench_string_copy);

static void bench_memcpy(benchmark::State& state) {
  std::vector<char> buffer;
  buffer.resize(str.size() + 1);
  for (auto _ : state) {
    std::memcpy(buffer.data(), str.data(), str.size());
  }
}
BENCHMARK(bench_memcpy);


BENCHMARK_MAIN();
