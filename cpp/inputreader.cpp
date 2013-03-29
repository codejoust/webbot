
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

class WebWriter {
public:
	const char *filename;
	WebWriter(const char *filenamein) : filename(filenamein){

	};
	WebWriter(string filename) : filename(filename.c_str()){

	};
	void write(string input){
		cout << "Writing file " << input << endl;
		ofstream outfile;
		outfile.open(filename, fstream::app);
		outfile << input << endl;
		outfile.close();
	}
};



class InputReader {
public:
	const char* filename;
	map<string, void(*)()>       fn_map;
	map<string, void(*)(string)> fn_map_args;
	
	time_t last_mtime;

	InputReader(string filenamein) : filename(filenamein.c_str()), last_mtime(0) {
		
	}
	InputReader(const char* filenamein) : filename(filenamein), last_mtime(0) {
		
	}

	bool has_changed(){
		struct stat attrib;
		stat(filename, &attrib);
		bool ret = (attrib.st_mtime != last_mtime);
		last_mtime = attrib.st_mtime;
		//cout << "mtime: " << last_mtime << " ret: " << ret << endl;
		return ret;
	}

	int poll_updates(){

		if (has_changed()){
			// read file
			string cmd;
			string args;
			ifstream readerin(filename);

			/*
			// go to end of the file
			readerin.seekg(0, readerin.end);
			
			// unget last line
			readerin.unget();
			readerin.unget();

			while(readerin.peek() != '\n'){
				readerin.unget();
			}
			*/

			// discard created time.
			getline(readerin, args, ',');
			getline(readerin, cmd,  ',');
			getline(readerin, args, '\n');

			//cout << "reading in - cmd: " << cmd  << ", args: " << args << endl;

			readerin.close();
			check_input(cmd, args);
			ofstream readclear(filename, ios::trunc);
			readclear.close();

		}
		
		return 0;
	}

	void check_input(string input, string args){
		if (args.size() > 0 && fn_map_args[input]){
			fn_map_args[input](args);
		} else if (fn_map[input]){
			cout << "got input " << input << endl;
			fn_map[input]();
		}
	}

	void add_input(string match, void(*fn_ptr)()){
		fn_map[match] = fn_ptr;
	}

	void add_input_args(string match, void(*fn_ptr)(string)){
		fn_map_args[match] = fn_ptr;
	}

};