TARGET = ExplicitClient
OBJS = ExplicitClient.o


BINDIR = ../Debug

CXX = g++-5
CXXFLAGS = -g -Wall -std=c++11
LIB = -ldl

.PHONY : all clean run

all : clean $(TARGET)

$(TARGET) : $(OBJS)
	mkdir -p $(BINDIR)    &&    $(CXX) -o $(BINDIR)/$@ $^  $(LIB)

$.o : $.cpp
	$(CXX) $(CXXFLAGS)  -c $<   

clean : 
	rm -rf $(BINDIR)/$(TARGET) $(OBJS)

run :
	cd $(BINDIR) &&	./$(TARGET)