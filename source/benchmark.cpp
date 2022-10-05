#include "benchmark.hpp"

namespace benchmark
{
template<>
std::string timeUnitToStr<std::chrono::nanoseconds>()
{
  return "ns";
}

template<>
std::string timeUnitToStr<std::chrono::microseconds>()
{
  return "us";
}

template<>
std::string timeUnitToStr<std::chrono::milliseconds>()
{
  return "ms";
}

template<>
std::string timeUnitToStr<std::chrono::seconds>()
{
  return "s";
}
} //namespace benchmark


namespace std
{
std::ostream& operator<<(std::ostream& os, benchmark::TimeUnit const& timeUnit)
{
  return os << timeUnit.first << " " << timeUnit.second;
}

benchmark::TimeUnit operator/(benchmark::TimeUnit const& dividend, double const& divider)
{
  benchmark::TimeUnit result;
  result.first = dividend.first/divider;
  result.second = dividend.second;
  return result;
}

} //namespace std