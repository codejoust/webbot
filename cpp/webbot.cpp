#include <iostream>
#include <fstream>
#include <map>
#include <unistd.h>
#include <cstdlib>
#include <ctime>
using namespace std;

#include <Myro.h>
#include <Robot.h>
#include "inputreader.cpp"
#include "utils.cpp"
#include "futex.cpp"

#define ROBOT

WebWriter web_writer("output.txt");
WebWriter display_writer("display.txt");
FutexManager futex_manager;

void forward(){
	cout << "Moving Forward" << endl;
	robot.forward(0.9);
}

void stop(){
	cout << "Stop" << endl;
	robot.stop();
}

void backwards(){
	cout << "backwards" << endl;
	robot.backward(0.5);
}

void dobeep(){
	robot.beep(0.2, rand() % 600 + 300);
}

void say(string args){
	cout << "Saying: " << args << endl;
	robot.beep(0.2, 600);
	futex_manager.add_future(dobeep, 1);
	futex_manager.add_future(dobeep, 3);
}

void fart(){
	Utils::play_sound("fart.wav");
	web_writer.write("flashy");
}

void clear_light(){
	robot.setLEDFront(0);
}

void greet(){
	string command;
	command += "speak:'";
	command += robot.getName();
	web_writer.write(command);
	cout << "Greeting!" << endl;
	robot.setLEDFront(1);
	futex_manager.add_future(clear_light, 10);
}

void run(){

	InputReader robot_reader("input.txt");

	robot_reader.add_input("forward", forward);
	robot_reader.add_input("backwards", backwards);
	robot_reader.add_input("stop", stop);
	robot_reader.add_input_args("say", say);
	robot_reader.add_input("fart", fart);
	robot_reader.add_input("greet", greet);

	while (robot_reader.poll_updates() != -1){
		usleep(200000);
		futex_manager.step();
	}

}

int main(int argc, char **argv){

	if (argc <= 1){
		cout << "No Serial Port Declared (pass as arg 1)" << endl;
		return -1;
	}

	connect(argv[1]);

	Utils::init_rand();
	
	run();
	
	return 0;
}