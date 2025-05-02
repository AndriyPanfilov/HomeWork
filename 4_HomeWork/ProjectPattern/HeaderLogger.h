#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <memory>

//Заданий Інтерфейс LogSink
struct LogSink {

	virtual void write(const std::string& msg) = 0;
	virtual ~LogSink() = default;

	LogSink() = default;
};

//ConsoleSink -> виведення msg на консоль (std::cout)
class ConsoleSink :public LogSink {

public:
	void write(const std::string& msg) override {
		std::cout << msg << "adress sink_  ";
	}
};

//FileSink → додає рядок msg до файлу "app.log";
class FileSink :public LogSink {
	std::ofstream fout;

public:

	void write(const std::string& msg) override {
		if (fout.is_open()) {
			fout << msg << std::endl;
			std::cout << "\""<<msg<<" This \"msg\" written only to file \"app.log\" adress sink_ ";
		}
		else std::cout << "File \"app.log\" cannot be opened\n";
	}

	FileSink() {
		fout.open("app.log", std::ios::app);
	};

	~FileSink() {
		if (fout.is_open())
			fout.close();
	}
};

//NullSink → нічого не робить;
class NullSink : public LogSink {

	void write(const std::string& msg) override {
		(void)msg;
		std::cout << "WARNING: Ignored input text: adress sink_ ";
	}
};


enum class SinkType {
	CONSOLE,
	FILE,
	NONE
};


class Logger {
public:
	static Logger& instance() {
		static Logger instance;
		return instance;
	}
	
	void set_sink(SinkType type) {
		switch (type) {
		case SinkType::CONSOLE: sink_ = std::make_unique<ConsoleSink>();  break;
		case SinkType::FILE: sink_ = std::make_unique<FileSink>(); break;
		case SinkType::NONE: sink_ = std::make_unique <NullSink>(); break;

		default:
			throw std::invalid_argument("Error type argument");
		}
	}


	
	void log(const std::string& msg) {
		if (sink_) sink_->write(msg);
	}

	void adress_sink_() const {
		std::cout << sink_ << std::endl;
	}
	

private:

	std::unique_ptr <LogSink> sink_;
	
	Logger() {
		std::unique_ptr<LogSink> sink_;
	}

	Logger(const Logger&) = delete;
	Logger& operator = (const Logger&) = delete;

};

