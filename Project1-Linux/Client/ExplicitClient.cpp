/////////////////////////////////////////////////////////////
// ExplicitClient.cpp - load dll on demand                 //
//                    -  Demo for project                  //
//                                                         //
// Yaodong Wang, CSE775 - Distributed Objects, Spring 2018 //
/////////////////////////////////////////////////////////////

#include <dlfcn.h>  // get access to dlopen and dlsym
#include <iostream>
#include <string>
#include <stdexcept>
#include "../FileMgrComponent/IFileMgr.h"
#include "../SearchComponent/ISearch.h"


int main()
{
    std::cout << "\n  Linux Search Component Demo";
    std::cout << "\n ================================\n";
    try {
        void* hFileMgr = dlopen("./libFileMgr.so", RTLD_LAZY); 
        if(!hFileMgr) throw std::runtime_error("\n    handle to dll libFileMgr failed");
        void* hSearch = dlopen("./libSearch.so", RTLD_LAZY);
        if(!hSearch) throw std::runtime_error("\n    handle to dll libSearch failed");

        typedef IFileMgr*(*GCreateFileMgr)();
        typedef ISearch*(*GCreateSearch)();
        GCreateFileMgr gCreateFileMgr = (GCreateFileMgr)dlsym( hFileMgr, "GlobalCreateFileMgr" );
        GCreateSearch gCreateSearch = (GCreateSearch) dlsym( hSearch, "GlobalCreateSearch" );
        if(!gCreateFileMgr || !gCreateSearch) throw std::runtime_error("\n     failed to acquire create function");
        IFileMgr *pFM = gCreateFileMgr();
        
        std::vector<std::string> names = {"*.h", "*.c", "*.cpp", "*.txt", "*.cs", "*.hpp"};
        for(auto name: names) pFM->SetNamePtn(name);
        std::cout << "\n\n       client setup dir = \"../demoDir\"\n";
        if( !pFM->SetPath("../demoDir") ) {
            throw std::runtime_error("\n    set invalid path");
        }
        std::vector<std::string> pathFiles = pFM->GetFiles(pFM->GetPath());
        
        std::cout << "\n\n\n retrieved file paths : ";
        for(auto p: pathFiles) std::cout << "\n\t  " << p;


        ISearch *pS = gCreateSearch();
        std::string regEx = "\\b(sub)([^ ]*)";
        std::cout << "\n\n   --- < test case : searching " << regEx << " > ---\n";
        auto res = pS->GetResult(regEx, pathFiles);
        std::cout << "\n\n   --- get result from Search Component ---\n";
        for(const auto &r: res ) {
            std::cout << r << "\n";
        }
        dlclose(hFileMgr);
        dlclose(hSearch);
    } catch(std::exception &ex) {
        std::cout << ex.what() << "\n";
    }

    std::cout << "\n\n";
}