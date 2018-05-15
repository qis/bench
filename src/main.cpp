#include <benchmark/benchmark.h>
#include <bcrypt/bcrypt.h>

const auto g_hash = bcrypt::hash("test");

static void bcrypt_hash(benchmark::State& state) {
  for (const auto _ : state) {
    const auto hash = bcrypt::hash("test");
    benchmark::DoNotOptimize(hash);
  }
}
BENCHMARK(bcrypt_hash)->Iterations(10)->Unit(benchmark::kMillisecond);

static void bcrypt_verify(benchmark::State& state) {
  for (const auto _ : state) {
    const auto ok = bcrypt::verify("test", g_hash);
    benchmark::DoNotOptimize(ok);
  }
}
BENCHMARK(bcrypt_verify)->Iterations(10)->Unit(benchmark::kMillisecond);

int main(int argc, char** argv) {
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
}
