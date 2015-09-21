# make file for simple server

CXX ?= g++

CXXFLAGS ?= -Wall \
	-std=c++11 -pthread

CXXFLAGS_DEBUG := -g3 -O

CXXFLAGS_RELEASE := -O2 -DNDEBUG

#the default target is debug
all: debug

#debug section
debug: CXXFLAGS += $(CXXFLAGS_DEBUG)
debug: app

#release section
release: CXXFLAGS += $(CXXFLAGS_RELEASE)
release: app

#remove all files
clean:
	rm -f app client.o control.o user.o

app: client.o control.o user.o
	$(CXX) $^ -o $@ $(CXXFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

.PHONY: debug release clean
