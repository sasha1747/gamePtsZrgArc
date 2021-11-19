#include <vector>
#include <string>
#include <iostream>
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;
class MyLog {
private:
	vector<string> logs;
public:
	MyLog() {}
	void makeNewLog(string com) {
		logs.push_back(com);
	}
	vector<string> outputLogsToFile() {
		return logs;
	}
	vector<string> outputLogsToConsole() {
		return logs;
	}
};


class Log {
public:
	virtual ~Log() {}
	virtual string LogToFile() = 0;
	virtual string LogToConsole() = 0;
};

class Adapter : public Log
{
public:
	Adapter(MyLog* p) : p_myLog(p) {
	}
	~Adapter() {
		delete p_myLog;
	}
	string LogToFile()override {
		stringstream ss;
		vector<string>logs = p_myLog->outputLogsToFile();
		for (auto x : logs) {
			ss << x;
			ss << endl;
		}
		string res;
		//ss >> res;
		string str;
		while (getline(ss, str)) {
			res += str;
			res += "\n";
		}
		return res;
	}
	string LogToConsole()override {
		stringstream ss;
		vector<string>logs = p_myLog->outputLogsToConsole();
		for (auto x : logs) {
			ss << x;
			ss << endl;
		}
		string res;
		//ss >> res;
		string str;
		while (getline(ss, str)) {
			res += str;
			res += "\n";
		}
		return res;
	}
private:
	MyLog* p_myLog;
};
