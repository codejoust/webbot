#include <deque>

struct FutexRun {
	int at_step;
	void (*cb_fn)();
};

class FutexManager {
public:
	deque<FutexRun*> runs;
	int steps;

	void add_future(void (*cb_fn)(), int in_steps){
		FutexRun *newrun = new FutexRun();
		runs.push_front(newrun);
	}
	void step(){
		steps++;
		for (deque<FutexRun*>::iterator currun = runs.begin(); currun != runs.end(); currun++){
			if ((*currun)->at_step == steps){
				(*currun)->cb_fn();
				runs.erase(currun);
			}
		}
	}
	
};