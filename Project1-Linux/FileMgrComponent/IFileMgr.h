#pragma once
//////////////////////////////////////////////////////////////
// IFileMgr - interface for Component                       //
//                                                          //
// Yaodong Wang, CSE775 - Distributed Objects, Spring 2018  //
//////////////////////////////////////////////////////////////

#include <vector>

class IFileMgr {
public:
    virtual ~IFileMgr(){};
    virtual void SetNamePtn(std::string name_ptn) = 0;
    virtual bool SetPath(std::string root_path) = 0;
    virtual std::string GetPath() = 0;
    virtual std::vector<std::string> GetFiles(const std::string &path) = 0;
};

extern "C" {                  // unmangled global factory
  IFileMgr* GlobalCreateFileMgr();
}