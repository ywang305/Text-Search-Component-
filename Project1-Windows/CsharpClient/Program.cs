///////////////////////////////////////////////////////////////////////
// CSharp Client - creates FileMgr and Search, hooks together, and uses //
//                                                                      //
// Yaodong Wang, CSE775 - Distributed Objects, Spring 2018              //
// C# Client for calling ATLCOM SerachComponent						    //
//   and indirectly calling FileMgrComponent						    //
//																	    //
//  Package Operations:												    //
//  -------------------------										    //
//  This client console is  provided to demo Search COM uses FileMgr    //
//  COM. Search text regular express function is implemented by c++     //
//  <regex> in Search COM, and file retriving recursion is implemented  //
//  by FileInfo class integred with FileMgr COM.					    //
//																	    //
//////////////////////////////////////////////////////////////////////////
/*
*	note
*	-----------
*	1. built using X86, not ANY cpu
*	   Reference -> add  FileMgrComponentLib, SearchComponentLib
*
*	2. conversion between BSTR and wstring
*		wstring wstr = wstring(bstr)
*		BSTR bstr = CComBSTR(wstr.c_str())
*	3. CComBSTR constor
*		CComBSTR regexp = L"CLSID"
*		CComBSTR path(L"../foobar");
*		
*	* Maintenance History
* ===================
* 12 Mar 2018
* - first release, bug referring to (Exception from HRESULT: 0x80010105 (RPC_E_SERVERFAULT)
*/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CsharpClient
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.Write("\n  CSE775 Project #1 , C# client");
            Console.Write("\n ================================\n");

            try
            {
                // create FileMgr
                FileMgrComponentLib.IFileManager refFM = new FileMgrComponentLib.FileManager();
                refFM.SetReadPath("./demoDir");

                // create TextSearch
                SearchComponentLib.ITextSearch refTS = new SearchComponentLib.TextSearch();
                refTS.SetFileMgrIF(refFM);

                {
                    Console.WriteLine("\n  --- < test case 1, regex = \"CLSID*\"> ---");
                    Console.WriteLine(" ...............................................\n");
                    string [] res = (string []) refTS.SearchLineNum("CLSID*");
                    Console.WriteLine("\n   get result:");
                    foreach(var r in res)
                    {
                        Console.WriteLine("      {0}", r);
                    }
                }
                {
                    Console.WriteLine("\n\n  --- < test case 1, regex = \"\\b(sub)([^ ]*)*\"> ---");
                    Console.WriteLine(" ...........................................................\n");
                    string[] res = (string[])refTS.SearchLineNum("\\b(sub)([^ ]*)");
                    Console.WriteLine("\n   get result:");
                    foreach (var r in res)
                    {
                        Console.WriteLine("      {0}", r);
                    }
                }

            } catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
            
            Console.Write("\n\n");
        }
    }
}
