CXX = g++

SRCS = $(wildcard *.cpp)
tgts = $(patsubst %.cpp,%,$(SRCS))

all : $(tgts) 
#$(tgts):$(SRCS)
%:%.cpp
	$(CXX) -o $@ $<

clean :
	rm -rf $(tgts)
