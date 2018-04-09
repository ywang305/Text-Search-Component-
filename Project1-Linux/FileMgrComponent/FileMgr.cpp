// FileMgr.cpp : Implementation of IFileMgr
// Yaodong Wang, CSE775 - Distribted Objects, Spring 2018
/*
* Module Operations
* =================
* SetNamePtn specifies name pattern to filter files from directory tree
*
* SetPath sets current path
*
* GetFiles retrieves qualified file path-name in a directory
* tree,  wiith recursive dir searching method
*
* Required Files:
* ===============
*	"IFileMgr.h"
*	"FileSystem.h"
*
* Build Process:
* ==============
* - refer to local Makefile
*
* Maintenance History
* ===================
* 13 Mar 2018
* - first release
*
*/

#include <vector>
#include <unordered_set>
#include <iostream>
#include <string>
#include "IFileMgr.h"
#include "FileSystem.h"
using namespace FileSystem;

class FileMgr : public IFileMgr {
public:
    FileMgr();
    virtual ~FileMgr();
    virtual void SetNamePtn(std::string name_ptn) override;
    virtual bool SetPath(std::string root_path) override;
    virtual std::string GetPath() override;
    virtual std::vector<std::string> GetFiles(const std::string &path) override;
private:
    Directory *pD;
    std::unordered_set<std::string> name_set;
    std::string root;
};

// --- < initialized with Directory object > ---

FileMgr::FileMgr() : pD(new Directory()) {}

FileMgr::~FileMgr() {
    if(pD)  delete pD;
}

// ---- < path : root of dir tree > ----

bool FileMgr::SetPath(std::string root_path) {
    bool hr = true;
    try {
        root = Path::getFullFileSpec(root_path);
        auto found = root_path.find('/');
        if(found==std::string::npos) {
            root += "/" + root_path;
        }
        else {
            root += root_path.substr(found);
        }
        std::cout << "\n       FileMgr:: set internal root as = " << root  << "\n";
    } catch (std::exception &e) {
        std::cout << e.what() <<"\n";
        hr = false;
    }
    return hr;
}

// ---- < get fullSpec path > ----

std::string FileMgr::GetPath() {
    return root;
}

// --- < keep file name patterns > ---

void FileMgr::SetNamePtn(std::string name_ptn) {
    name_set.insert(name_ptn);
    std::cout << "\n   FileMgr adds a filename pattern : " << name_ptn <<"\n";
}

// --- < DFS recursively search directory tree for files specified in name pattents > ---
//   param path is fullSpec path, return fullPath + filename

std::vector<std::string> FileMgr::GetFiles(const std::string &path) {
    std::vector<std::string> pathFiles;
    
    // searching files

    for(const auto &ptn: name_set) {
        std::vector<std::string> files = pD->getFiles(path, ptn);
        for(const auto &fname: files) {
            pathFiles.push_back(path + "/" + fname);
        }
    }

    // searching dirs

    for(const auto &dir : pD->getDirectories(path)) {
        auto subPathFiles = GetFiles(path + "/" + dir);
        pathFiles.insert(pathFiles.end(), subPathFiles.begin(), subPathFiles.end());
    }
    pathFiles.empty()? std::cout << "\n      FileMgr:: S_FALSE for " << path : 
                    std::cout << "\n\     FileMgr:: S_OK for " << path;
    return pathFiles;
}

// --- < Global Factory > ---

IFileMgr* GlobalCreateFileMgr() {
    return new FileMgr();
}

// ----- test stub -----

#ifdef TEST_FM
int main() {
    IFileMgr* fm = GlobalCreateFileMgr();
    fm->SetPath("../dmoDir");
    fm->SetNamePtn("CLSID*");
    auto fullSpecs = fm->GetFiles(fm->GetPath());
    for(auto fs: fullSpecs) {
        std::cout << fs << std::endl;
    }
}
#endif