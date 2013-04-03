#include <deque>

class FutexRun {
public:
	FutexRun(){

	}
	FutexRun(void (*cb_fn)(), long int in_steps) : cb_fn(cb_fn), at_step(in_steps) {

	}
	long int at_step;
	void (*cb_fn)();
};

class FutexManager {
public:
	deque<FutexRun> runs;
	long int steps;

	FutexManager(){
		steps = 0;
	}

	~FutexManager(){

	}

	void add_future(void (*cb_fn)(), int in_steps){
		runs.push_front(FutexRun(cb_fn, (long int)in_steps + steps));
	}
	void step(){
		steps++;
		for (deque<FutexRun>::iterator currun = runs.begin(); currun != runs.end(); currun++){
			if ((*currun).at_step == steps){
				cout << "Running callback" << endl;
				(*currun).cb_fn();
				//runs.erase(currun);
			}
		}
	}
	
};