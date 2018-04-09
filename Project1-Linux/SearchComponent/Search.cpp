// Search.cpp : Implementation of ISearch
// Yaodong Wang, CSE775 - Distribted Objects, Spring 2018
/*
* Module Operations
* =================
* GetResult : return files and line number that match the paramter regEx
*   if find matched files, it uses c++ fstream to read line
*   by line, and return the file pathSpec and line number that 
*   matched regex text.
*
* Required Files:
* ===============
*	ISearch.h
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

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
#include "ISearch.h"

class Search : public ISearch {
public:
    Search();
    virtual ~Search();
    virtual std::vector<std::string> GetResult(std::string regEx, const std::vector<std::string> &pfs) override;
};

// --- < init/ destructor > ----

Search::Search() {}

Search::~Search() {}

// --- < get line number of matched regex from retrieved filenames > ---

std::vector<std::string> Search::GetResult(std::string regEx, const std::vector<std::string> &pfs) {
    std::vector<std::string> res;
    std::ifstream ifs;
    std::string line;
    std::smatch m;
	std::regex rx(regEx);
    for(const auto &f: pfs) {
        ifs.open(f);
        if(!ifs) continue;
        std::string fres = "\n\tfile  : " + f;
        std::stringstream ss("");
        int cnt = 0;
        while(std::getline(ifs, line)) {
            ++cnt;
            if(std::regex_search(line, m, rx)) {
                ss << "\n\t line# : " << std::to_string(cnt);
            }
        }
        ifs.close();
        
        fres += ss.str().empty()? "\n\t line# : null": ss.str();
        res.push_back(fres);
    }
    return res;
}

// --- < Global Factory > ---

ISearch* GlobalCreateSearch() {
    return new Search();
}