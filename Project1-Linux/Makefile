TARGET = ExplicitClient

EXECDIR = ./Client
LIBDIR1 = ./FileMgrComponent
LIBDIR2 = ./SearchComponent
BINDIR = ./Debug


.PHONY : all clean build run   

all : clean build run

clean : 
	cd $(LIBDIR1) && $(MAKE) clean
	cd $(LIBDIR2) && $(MAKE) clean
	cd $(EXECDIR) && $(MAKE) clean

build :
	cd $(LIBDIR1) && $(MAKE)
	cd $(LIBDIR2) && $(MAKE)
	cd $(EXECDIR) && $(MAKE)

run:
	cd $(EXECDIR) && $(MAKE) run
