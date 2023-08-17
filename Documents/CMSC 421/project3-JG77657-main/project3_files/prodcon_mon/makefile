CXX = gcc
CXXFLAGS = -Wall -g -lpthread -lrt

test_mon: buffer_mon.o test_mon.c
	$(CXX) buffer_mon.o test_mon.c -o test_mon $(CXXFLAGS)

buffer_mon.o: condFxn.h buffer_mon.h buffer_mon.c
	$(CXX) buffer_mon.c -c $(CXXFLAGS)

