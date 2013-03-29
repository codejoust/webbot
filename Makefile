bin/runner: ./cpp/*.cpp 
	g++ `myro-cpp-config --cflags` ./cpp/webbot.cpp `myro-cpp-config --libs` -o bin/runner


