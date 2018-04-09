# Text-Search-Component
**credit** - [James Fawcett](http://ecs.syr.edu/faculty/fawcett/handouts/cse775/Lectures/Project1-S2018.htm#top)

## Purpose:
Components are usually relatively small pieces of software built as libraries that expose an interface for accessing functionality and an object factory that allows a client to initialize the software by creating internal objects without binding to concrete definitions. Often a component provides to a client the means to manage the lifetime of internal objects and to specify that the component is no longer needed so it's binary library may be unloaded by the process.

Microsoft developed, in the 90's, a Windows platform technology it calls the Component Object Model (COM) that is based on components. Its use is pervasive throughout their product ecosystem, e.g., Windows, the .Net framework, Office, IIS and many of its other enterprise server technologies.

In this project we will develop a Text Search program using components on both Windows and the Linux operating system. For the Windows-based program we will use the Microsoft COM technology. Linux does not support COM so we will build our own component infrastructure for that environment.

## Requirements:
- Shall be implemented in C++11 using Visual Studio 2017 for the COM-on-Windows program and g++ ver 5.3 for the Components-on-Linux program1.
- Shall, on each platform, provide a console application that, given on the command line: a regular-expression search string, a path, and a set of file name patterns, identifies by name and path all those files matching one or more of the patterns and which contain an instance of the search string. It does this using the services of two components, described below.
- The previous requirement shall be interpreted to include all common text formats, e.g., *.txt, *.h, *.cpp, *.cs, etc. It optionally2 will also be interpreted to include Microsoft Word doc and docx files on Windows. And, it optionally2 will also be interpreted to include Libre Office Writer odf files on Linux.
- Shall provide a text search component that accepts a fully qualified file name and regular-expression text pattern. If the file matches the text pattern in one or more locations, it returns a list of line numbers where the matches occur. If no matches occur, it returns an empty list.
- Shall provide a FileMgr component that finds the fully qualified names of all files residing in a directory tree rooted at a specified path and matching one or more of the filename patterns. It exposes these results by providing a get(...) method that retrieves each result from an internal thread-safe blocking queue, and returns the result with a success code of true. When its search has ended, the get(...) method returns a success code with value false.
- Shall use a Powershell script on windows and a Bash script on Linux to demonstrate that the application, and its components, implement their required functionality. The combination of scripts and console applications should clearly show the initial requests, the output of the FileMgr, and the output of the file search processing.
## What you need to know:
In order to successfully meet these requirements you will:
> - use both Ubuntu and Windows
> - Know or learn how C++ classes and class hierarchies work, C++11 threading, and how to design interfaces and object factories.
> - How COM works and how to use the Microsoft ATL libraries.
