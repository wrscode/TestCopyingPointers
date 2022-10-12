#pragma once

#include "benchmark.hpp"
#include "types.hpp"
#include "helper.hpp"

using Stopwatch = benchmark::Stopwatch<std::chrono::nanoseconds, std::chrono::high_resolution_clock>;

struct CopySharedVecToShareVec : benchmark::Benchmark<Stopwatch>
{
  CopySharedVecToShareVec(IntSharedPtrVec const& pSamples) : samples(pSamples){}

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

struct CopySharedVecToShareVecReserve : benchmark::Benchmark<Stopwatch>
{
  CopySharedVecToShareVecReserve(IntSharedPtrVec const& pSamples) : samples(pSamples){}
  
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

struct CopySharedVecToRawVec : benchmark::Benchmark<Stopwatch>
{
  CopySharedVecToRawVec(IntSharedPtrVec const& pSamples) : samples(pSamples){}
  
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

struct CopySharedVecToRawVecReserve : benchmark::Benchmark<Stopwatch>
{
  CopySharedVecToRawVecReserve(IntSharedPtrVec const& pSamples) : samples(pSamples){}
  
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
struct CopySharedVecToRawVecArray : benchmark::Benchmark<Stopwatch>
{
  CopySharedVecToRawVecArray(IntSharedPtrVec const& pSamples) : samples(pSamples){}

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
struct CopySharedVecToShareVecdArray : benchmark::Benchmark<Stopwatch>
{
  CopySharedVecToShareVecdArray(IntSharedPtrVec const& pSamples) : samples(pSamples){}

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

struct CopySharedVecToShareVec2 : benchmark::Benchmark<Stopwatch>
{
  CopySharedVecToShareVec2(IntSharedPtrVec const& pSrc, IntSharedPtrVec& pDst) : src(pSrc), dst{pDst}{}

  void runTest() override 
  {
    for(auto const& it : src)
      dst.push_back(it);
  }

  IntSharedPtrVec const& src;
  IntSharedPtrVec& dst;
};

/* ************************************************************************* */
/* ************************************************************************* */
template<std::size_t arrSize>
struct CopySharedToShare : benchmark::Benchmark<Stopwatch>
{
  CopySharedToShare(IntSharedPtrArr<arrSize> const& pSrc, IntSharedPtrArr<arrSize>& pDst) : src(pSrc), dst{pDst}{}

  void runTest() override 
  {
    for(auto idx = 0U; idx < arrSize; ++idx)
      dst[idx] = src[idx];
  }

  IntSharedPtrArr<arrSize> const& src;
  IntSharedPtrArr<arrSize>& dst;
};

template<std::size_t arrSize>
struct CopySharedToShareUsingIterators : benchmark::Benchmark<Stopwatch>
{
  CopySharedToShareUsingIterators(IntSharedPtrArr<arrSize> const& pSrc,
    IntSharedPtrArr<arrSize>& pDst) : src(pSrc), dst{pDst}{}

  void runTest() override 
  {
    auto sit = std::begin(src);
    auto dit = std::begin(dst);

    auto const send = std::end(src);
    for(; sit < send; ++sit, ++dit)
      *dit = *sit;
  }

  IntSharedPtrArr<arrSize> const& src;
  IntSharedPtrArr<arrSize>& dst;
};


template<std::size_t arrSize>
struct CopySharedToRaw : benchmark::Benchmark<Stopwatch>
{
  CopySharedToRaw(IntSharedPtrArr<arrSize> const& pSrc, IntRawPtrArr<arrSize>& pDst) : src(pSrc), dst{pDst}{}

  void runTest() override 
  {
    for(auto idx = 0U; idx < arrSize; ++idx)
      dst[idx] = src[idx].get();
  }

  IntSharedPtrArr<arrSize> const& src;
  IntRawPtrArr<arrSize>& dst;
};


template<std::size_t arrSize>
struct CopySharedToRawUsingIterators : benchmark::Benchmark<Stopwatch>
{
  CopySharedToRawUsingIterators(IntSharedPtrArr<arrSize> const& pSrc,
    IntRawPtrArr<arrSize>& pDst) : src(pSrc), dst{pDst}{}

  void runTest() override 
  {
    auto sit = std::begin(src);
    auto dit = std::begin(dst);

    auto const send = std::end(src);
    for(; sit < send; ++sit, ++dit)
      *dit = sit->get();
  }

  IntSharedPtrArr<arrSize> const& src;
  IntRawPtrArr<arrSize>& dst;
};

/* ************************************************************************* */
/* ************************************************************************* */
template<std::size_t callCnt>
inline void copy(IntSharedPtr const* src, IntSharedPtr* dst)
{
  (*dst) = (*src);
  copy<callCnt - 1>((src+1), (dst + 1));
}

template<>
inline void copy<1>(IntSharedPtr const* src, IntSharedPtr* dst)
{
  (*dst) = (*src);
}

template<>
inline void copy<0>(IntSharedPtr const*, IntSharedPtr*)
{

}

template<std::size_t arrSize>
struct CopySharedToShareUnwindLoop : benchmark::Benchmark<Stopwatch>
{
  CopySharedToShareUnwindLoop(IntSharedPtrArr<arrSize> const& pSrc, IntSharedPtrArr<arrSize>& pDst) : src(pSrc), dst{pDst}{}

  void runTest() override 
  {
    copy<arrSize>(&src[0], &dst[0]);
  }

  IntSharedPtrArr<arrSize> const& src;
  IntSharedPtrArr<arrSize>& dst;
};


template<std::size_t callCnt>
inline void copy(IntSharedPtr const* src, int** dst)
{
  *dst = src->get();
  copy<callCnt - 1>((src+1), (dst + 1));
}

template<>
inline void copy<1>(IntSharedPtr const* src, int** dst)
{
  *dst = src->get();
}

template<>
inline void copy<0>(IntSharedPtr const*, int**)
{

}

template<std::size_t arrSize>
struct CopySharedToRawUnwindLoop : benchmark::Benchmark<Stopwatch>
{
  CopySharedToRawUnwindLoop(IntSharedPtrArr<arrSize> const& pSrc, IntRawPtrArr<arrSize>& pDst) : src(pSrc), dst{pDst}{}

  void runTest() override 
  {
    copy<arrSize>(&src[0], &dst[0]);
  }

  IntSharedPtrArr<arrSize> const& src;
  IntRawPtrArr<arrSize>& dst;
};
