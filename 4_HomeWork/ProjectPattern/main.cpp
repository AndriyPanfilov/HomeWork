#include "HeaderLogger.h"
#include<iostream>

int main(int argc, char* argv[]) {

	std::string argvStr {};
	std::string msg {};

	SinkType sinkType_ = SinkType::CONSOLE;

	if (argc !=2) {
		msg = "No parameter was entered. Default text output to console: ";
		argvStr = "console";
	}
	else {
		argvStr = argv[1];
		//Цикл переведення string argument y нижній регістр (при помилковому ввденні)
		for (int i(0); i < argvStr.size(); i++) {
			argvStr[i] = std::tolower(argvStr[i]);
		}	
	}
	

	if (argvStr == "console") {
		msg = "Outputting text to the console: ";
	}
	else if (argvStr == "file") {
		msg = "Entering text into file app.log ";
		sinkType_ = SinkType::FILE;
	}
	else if (argvStr == "none") {
		msg = "Attention! No action is being performed: ";
		sinkType_ = SinkType::NONE;
	}
	else {
		std::cout << "Warning: Invalid argument" << std::endl;
		return 0;
	}
	
	Logger::instance().set_sink(sinkType_);

	std::string tempMsg{};
	tempMsg = "Test msg_1: " + msg + ":";
	Logger::instance().log(tempMsg);
	Logger::instance().adress_sink_();

	tempMsg = "Test msg_2: " + msg + ":";
	Logger::instance().log(tempMsg);
	Logger::instance().adress_sink_();

	tempMsg = "Test msg_3: " + msg + ":";
	Logger::instance().log(tempMsg);
	Logger::instance().adress_sink_();	
	
	system("pause");
	
}