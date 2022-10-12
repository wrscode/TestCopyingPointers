#pragma once

#include <memory>
#include <vector>
#include <array>

using IntSharedPtr = std::shared_ptr<int>;
using IntSharedPtrVec = std::vector<std::shared_ptr<int>>;

using IntRawPtrVec = std::vector<int*>;

template<std::size_t arrSize>
using IntSharedPtrArr = std::array<std::shared_ptr<int>, arrSize>;

template<std::size_t arrSize>
using IntRawPtrArr = std::array<int*, arrSize>;
