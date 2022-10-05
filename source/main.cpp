#include "benchmark.hpp"

#include <iostream>
#include <iomanip>

#include <random>
#include <memory>
#include <algorithm>

#include <vector>
#include <array>

using IntSharedPtr = std::shared_ptr<int>;
using IntSharedPtrVec = std::vector<std::shared_ptr<int>>;
using IntRawPtrVec = std::vector<int*>;

using Stopwatch = benchmark::Stopwatch<std::chrono::nanoseconds, std::chrono::high_resolution_clock>;

struct TestSharedToShare : benchmark::Benchmark<Stopwatch>
{
  TestSharedToShare(IntSharedPtrVec const& pSamples) : samples(pSamples){}

  void prepareTest() override
  {
    output.reserve(0);
  }

  void runTest() override 
  {
    for(auto const& sample : samples)
      output.push_back(sample);
  }
  
  // void clearTest() override
  // {
  //   output.clear();
  // }

  IntSharedPtrVec const& samples;
  IntSharedPtrVec output;
};

struct TestSharedToShareReserve : benchmark::Benchmark<Stopwatch>
{
  TestSharedToShareReserve(IntSharedPtrVec const& pSamples) : samples(pSamples){}
  
  void prepareTest() override
  {
    output.reserve(samples.size());
  }

  void runTest() override 
  {
    for(auto const& sample : samples)
      output.push_back(sample);
  }
  
  // void clearTest() override
  // {
  //   output.clear();
  // }

  IntSharedPtrVec const& samples;
  IntSharedPtrVec output;
};

struct TestSharedToRaw : benchmark::Benchmark<Stopwatch>
{
  TestSharedToRaw(IntSharedPtrVec const& pSamples) : samples(pSamples){}
  
  void prepareTest() override
  {
    output.reserve(0);
  }

  void runTest() override 
  {
    for(auto const& sample : samples)
      output.push_back(sample.get());
  }
  
  // void clearTest() override
  // {
  //   output.clear();
  // }

  IntSharedPtrVec const& samples;
  IntRawPtrVec output;
};

struct TestSharedToRawReserve : benchmark::Benchmark<Stopwatch>
{
  TestSharedToRawReserve(IntSharedPtrVec const& pSamples) : samples(pSamples){}
  
  void prepareTest() override
  {
    output.reserve(samples.size());
  }

  void runTest() override 
  {
    for(auto const& sample : samples)
      output.push_back(sample.get());
  }
  
  // void clearTest() override
  // {
  //   output.clear();
  // }

  IntSharedPtrVec const& samples;
  IntRawPtrVec output;
};


template<std::size_t size>
struct TestSharedToRawArray : benchmark::Benchmark<Stopwatch>
{
  TestSharedToRawArray(IntSharedPtrVec const& pSamples) : samples(pSamples){}

  void runTest() override 
  {
    auto cit = std::begin(output);

    for(auto const& sample : samples)
    {
      *cit = sample.get();
      ++cit;
    }  
  }
  
  // void clearTest() override
  // {
  //   output.clear();
  // }

  IntSharedPtrVec const& samples;
  std::array<int*, size> output;
};

template<std::size_t size>
struct TestSharedToSharedArray : benchmark::Benchmark<Stopwatch>
{
  TestSharedToSharedArray(IntSharedPtrVec const& pSamples) : samples(pSamples){}

  void runTest() override 
  {
    auto cit = std::begin(output);

    for(auto const& sample : samples)
    {
      *cit = sample;
      ++cit;
    }  
  }
  
  // void clearTest() override
  // {
  //   output.clear();
  // }

  IntSharedPtrVec const& samples;
  std::array<IntSharedPtr, size> output;
};

IntSharedPtrVec prepareTestData(std::size_t size)
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(0, 1000);

  IntSharedPtrVec result;
  result.reserve(size);

  for(std::size_t cnt = size; 0 < cnt; --cnt)
    result.push_back(std::make_shared<int>(distr(gen)));

  return result;
}

int main()
{
  constexpr size_t sampleSize = 100'000;
  constexpr size_t testRepeats = 100;
  
  auto samples = prepareTestData(sampleSize);

  TestSharedToShare testSharedToShare{samples};
  TestSharedToShareReserve testSharedToShareReserve{samples};
  TestSharedToRaw testSharedToRaw{samples};
  TestSharedToRawReserve testSharedToRawReserve{samples};
  TestSharedToRawArray<sampleSize> testSharedToRawArray{samples};
  TestSharedToSharedArray<sampleSize> testSharedToSharedArray{samples};

  testSharedToShare.run(testRepeats);
  testSharedToShareReserve.run(testRepeats);
  testSharedToRaw.run(testRepeats);
  testSharedToRawReserve.run(testRepeats);
  testSharedToRawArray.run(testRepeats);
  testSharedToSharedArray.run(testRepeats);

  std::cout << "SharedToShare:        " << std::fixed << std::setprecision(2) << testSharedToShare.singleRunTime()/sampleSize  << std::endl;
  std::cout << "SharedToShareReserve: " << std::fixed << std::setprecision(2) << testSharedToShareReserve.singleRunTime()/sampleSize  << std::endl;
  std::cout << "SharedToRaw:          " << std::fixed << std::setprecision(2) << testSharedToRaw.singleRunTime()/sampleSize  << std::endl;
  std::cout << "SharedToRawReserve:   " << std::fixed << std::setprecision(2) << testSharedToRawReserve.singleRunTime()/sampleSize  << std::endl;
  std::cout << "SharedToRawArray:     " << std::fixed << std::setprecision(2) << testSharedToRawArray.singleRunTime()/sampleSize  << std::endl;
  std::cout << "SharedToSharedArray:  " << std::fixed << std::setprecision(2) << testSharedToSharedArray.singleRunTime()/sampleSize  << std::endl;
}
