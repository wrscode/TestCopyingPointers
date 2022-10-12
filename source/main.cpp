#include "tests.hpp"

#include <iostream>
#include <iomanip>

#include <memory>
#include <algorithm>

int main()
{
  constexpr size_t sampleSize = 100;
  constexpr size_t testRepeats = 1'000;
  
  IntSharedPtrArr<sampleSize> arrSrc = helper::prepareTestArray<sampleSize>();
  IntSharedPtrArr<sampleSize> arrDst;
  IntRawPtrArr<sampleSize> arrRawDst;

  // auto samples = helper::prepareTestData(sampleSize);
  // IntSharedPtrVec out;

  // CopySharedVecToShareVec testSharedToShare{samples};
  // CopySharedVecToShareVecReserve testSharedToShareReserve{samples};
  // CopySharedVecToRawVec testSharedToRaw{samples};
  // CopySharedVecToRawVecReserve testSharedToRawReserve{samples};
  // CopySharedVecToRawVecArray<sampleSize> testSharedToRawArray{samples};
  // CopySharedVecToShareVecdArray<sampleSize> testSharedToSharedArray{samples};
  // CopySharedVecToShareVec2 t1{samples, out};

  CopySharedToShare<sampleSize>               copySharedToShare{arrSrc, arrDst};
  CopySharedToRaw<sampleSize>                 copySharedToRaw{arrSrc, arrRawDst};
  CopySharedToShareUsingIterators<sampleSize> copySharedToShareUsingIterators{arrSrc, arrDst};
  CopySharedToRawUsingIterators<sampleSize>   copySharedToRawUsingIterators{arrSrc, arrRawDst};

  // CopySharedToShareUnwindLoop<sampleSize>     t5{arrSrc, arrDst};
  // CopySharedToRawUnwindLoop<sampleSize>       t6{arrSrc, arrRawDst};
  
  // testSharedToShare.run(testRepeats);
  // testSharedToShareReserve.run(testRepeats);
  // testSharedToRaw.run(testRepeats);
  // testSharedToRawReserve.run(testRepeats);
  // testSharedToRawArray.run(testRepeats);
  // testSharedToSharedArray.run(testRepeats);
  // t1.run(testRepeats);

  copySharedToShare.run(testRepeats);
  copySharedToShareUsingIterators.run(testRepeats);
  copySharedToRawUsingIterators.run(testRepeats);
  copySharedToRaw.run(testRepeats);

  // t6.run(testRepeats);

  // std::cout << "CopySharedVecToShareVec:         " << std::fixed << std::setprecision(2) << testSharedToShare.singleRunTime()  << std::endl;
  // std::cout << "CopySharedVecToShareVecReserve:  " << std::fixed << std::setprecision(2) << testSharedToShareReserve.singleRunTime()  << std::endl;
  // std::cout << "CopySharedVecToRawVec:           " << std::fixed << std::setprecision(2) << testSharedToRaw.singleRunTime() << std::endl;
  // std::cout << "CopySharedVecToRawVecReserve:    " << std::fixed << std::setprecision(2) << testSharedToRawReserve.singleRunTime() << std::endl;
  // std::cout << "CopySharedVecToRawVecArray:      " << std::fixed << std::setprecision(2) << testSharedToRawArray.singleRunTime() << std::endl;
  // std::cout << "CopySharedVecToShareVecdArray:   " << std::fixed << std::setprecision(2) << testSharedToSharedArray.singleRunTime() << std::endl;
  // std::cout << "CopySharedVecToShareVec2:        " << std::fixed << std::setprecision(2) << t1.singleRunTime()<< std::endl;

  std::cout << "copySharedToShare:               " << std::fixed << std::setprecision(2) << copySharedToShare.singleRunTime() << std::endl;
  std::cout << "copySharedToRaw:                 " << std::fixed << std::setprecision(2) << copySharedToRaw.singleRunTime() << std::endl;

  std::cout << "copySharedToShareUsingIterators: " << std::fixed << std::setprecision(2) << copySharedToShareUsingIterators.singleRunTime() << std::endl;
  std::cout << "copySharedToRawUsingIterators:   " << std::fixed << std::setprecision(2) << copySharedToRawUsingIterators.singleRunTime() << std::endl;

  // std::cout << "CopySharedToShareUnwindLoop:     " << std::fixed << std::setprecision(2) << t5.singleRunTime() << std::endl;
  // std::cout << "CopySharedToRawUnwindLoop:       " << std::fixed << std::setprecision(2) << t6.singleRunTime() << std::endl;
}
