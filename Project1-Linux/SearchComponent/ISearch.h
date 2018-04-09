#pragma once
//////////////////////////////////////////////////////////////
// ISearch - interface for Component                       //
//                                                          //
// Yaodong Wang, CSE775 - Distributed Objects, Spring 2018  //
//////////////////////////////////////////////////////////////
#include <vector>

class ISearch {
public:
    virtual ~ISearch(){};
    virtual std::vector<std::string> GetResult(std::string regEx, const std::vector<std::string> &pfs) = 0;
};

extern "C" {                  // unmangled global factory
  ISearch* GlobalCreateSearch();
}