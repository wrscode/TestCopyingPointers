#include <chrono>
#include <string>
#include <iostream>
#include <vector>
#include <numeric>
#include <cassert>

namespace benchmark
{
template<typename T>
std::string timeUnitToStr()
{
  return "";
}

template<>
std::string timeUnitToStr<std::chrono::nanoseconds>();

template<>
std::string timeUnitToStr<std::chrono::microseconds>();

template<>
std::string timeUnitToStr<std::chrono::milliseconds>();

template<>
std::string timeUnitToStr<std::chrono::seconds>();

typedef std::pair<long double, std::string> TimeUnit;

template <typename TimeT = std::chrono::milliseconds, typename ClockT = std::chrono::steady_clock>
struct Stopwatch
{
    using TimePoint = typename ClockT::time_point;
    using TimeUnit = TimeT;
    using Resolution = typename TimeUnit::rep;

    TimePoint start_;
    TimePoint end_;

public:
    void start() 
    { 
        start_ = ClockT::now(); 
    }
    
    void stop() 
    { 
      end_ = ClockT::now(); 
    }
        
    Resolution duration() const 
    {
      return std::chrono::duration_cast<TimeT>(end_ - start_).count(); 
    }
};

template< typename Stopwatch>
struct Benchmark
{
  void run(std::size_t repetitions)
  {
    measurs.clear();
    measurs.reserve(repetitions);

    for(std::size_t cnt = repetitions; 0 < cnt; --cnt)
    {
      prepareTest();
      
      Stopwatch stopwatch;
      stopwatch.start();
      
      runTest();

      stopwatch.stop();
      measurs.push_back(stopwatch.duration());
      
      clearTest();
    }
  }

  TimeUnit totalTime() const
  {
    return std::make_pair(calculateTotalTime(), timeUnitToStr<typename Stopwatch::TimeUnit>());
  }

  TimeUnit singleRunTime() const
  {
    assert(!measurs.empty());
    return {calculateTotalTime()/measurs.size() , timeUnitToStr<typename Stopwatch::TimeUnit>()};
  }

private:
  long double calculateTotalTime() const
  {
    return std::accumulate(std::begin(measurs), std::end(measurs), 0);
  }

private:
  virtual void prepareTest(){}
  virtual void runTest(){}
  virtual void clearTest(){}

private:
  using Resolution = typename Stopwatch::Resolution;
  std::vector<Resolution> measurs;
};
} //namespace benchmark

namespace std
{
std::ostream& operator<<(std::ostream& os, benchmark::TimeUnit const& timeUnit);

benchmark::TimeUnit operator/(benchmark::TimeUnit const& dividend, double const& divider);

} //namespace std