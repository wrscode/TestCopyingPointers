#pragma once

#include "types.hpp"

#include <random>

namespace helper
{
template<size_t sampeSize>
std::array<IntSharedPtr, sampeSize> prepareTestArray()
{
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(0, 1000);

  std::array<IntSharedPtr, sampeSize> result;

  for(std::size_t cnt = 0U; cnt < result.size(); ++cnt)
    result[cnt] = std::make_shared<int>(distr(gen));

  return result;
}

static IntSharedPtrVec prepareTestData(std::size_t size)
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
} //namespace helper
