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
	robot.forward(1.0);
}

void stop(){
	cout << "Stop" << endl;
	robot.stop();
}

void backwards(){
	cout << "backwards" << endl;
	robot.backward(0.8);
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

void take_picture(){
	PicturePtr pic;
	display_writer.write("status:Taking_Picture");
	pic = robot.takePicture("jpeg", false);
	pic->savePicture("./html/pics/robot.jpg");
	web_writer.write("display_pic");
	display_writer.write("display_pic");
}

void fart(){
	Utils::play_sound("fart.wav");
	web_writer.write("flashy");
}

void clear_light(){
	robot.setLEDFront(0);
}

void send_message(){
	display_writer.write("alert:hello_world");
}

void greet(){
	string command;
	command += "speak:";
	command += robot.getName();
	display_writer.write(command);
	cout << "Greeting!" << endl;
	robot.setLEDFront(1);
	futex_manager.add_future(clear_light, 10);
	futex_manager.add_future(send_message, 4);
}

void turnLeft(){
	robot.turnRight(1.0);
}

void turnRight(){
	robot.turnLeft(1.0);
}

void set_startup(){
	display_writer.write("play_sound:macup");
}

void alarm(){
	display_writer.write("play_sound:alarm");
}

void play_sound(string arg){
	string cmd;
	cmd = "play_sound:";
	cmd += arg;
	display_writer.write(cmd);
}

void confirmcmd(string cmd, string arg){
	return;
	string cmdout;
	cmdout = "status:";
	cmdout += cmd;
	display_writer.write(cmdout);
}

void run(){

	InputReader robot_reader("input.txt");

	robot_reader.add_input("forward", forward);
	robot_reader.add_input("backwards", backwards);
	robot_reader.add_input("stop", stop);
	robot_reader.add_input_args("say", say);
	robot_reader.add_input_args("play_sound", play_sound);
	robot_reader.add_input("fart", fart);
	robot_reader.add_input("send_message", send_message);
	robot_reader.add_input("greet", greet);
	robot_reader.add_input("alarm", alarm);
	robot_reader.add_input("left", turnLeft);
	robot_reader.add_input("take_picture", take_picture);
	robot_reader.add_input("turn_left", turnLeft);
	robot_reader.add_input("right", turnRight);
	robot_reader.add_input("turn_right", turnRight);

	robot_reader.add_cb(confirmcmd);
	
	futex_manager.add_future(set_startup, 20);

	while (robot_reader.poll_updates() != -1){
		usleep(10000);
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