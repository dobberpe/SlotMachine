#include "Logger.h"

#include <chrono>
#include <iomanip>
#include <sstream>
#include <filesystem>

Logger& Logger::getInstance() {
	static Logger logger;
	return logger;
}

void Logger::log(LogType type, LogLevel level, const std::string& message) {

	std::ofstream& logFile = getLogFile(type);
	if (!logFile.is_open()) {
		throw std::runtime_error("Error: Log file is closed");
	}

	logFile << "[" << getCurrentTime() << "] "
		<< "[" << logLevelToString(level) << "] "
		<< message << std::endl;
}

Logger& Logger::operator<<(LogType type) {
	currentType = type;
	return *this;
}

Logger& Logger::operator<<(LogLevel level) {
	std::ofstream& logFile = getLogFile(currentType);

	checkLogFileSize(currentType);

	logFile << "[" << getCurrentTime() << "] "
		<< "[" << logLevelToString(level) << "] ";

	return *this;
}

Logger::Logger() {
	createDirectoryIfNotExist();

	controllerFile.open("logs/controller.log", std::ios::app);
	viewFile.open("logs/view.log", std::ios::app);
	modelFile.open("logs/model.log", std::ios::app);

	if (!controllerFile || !viewFile || !modelFile) {
		throw std::runtime_error("Error: couldn't open log file");
	}

	currentType = CONTROLLER;
}

Logger::~Logger() {
	if (controllerFile.is_open()) controllerFile.close();
	if (viewFile.is_open()) viewFile.close();
	if (modelFile.is_open()) modelFile.close();
}

void Logger::createDirectoryIfNotExist() {
	if (!std::filesystem::exists("logs")) {
		if (!std::filesystem::create_directory("logs")) {
			throw std::runtime_error("Error: Couldn't create logs directory");
		}
	}
}

std::ofstream& Logger::getLogFile(LogType type) {
	switch (type) {
		case CONTROLLER: return controllerFile;
		case VIEW: return viewFile;
		case MODEL: return modelFile;
		default: throw std::runtime_error("Error: Unknown log type");
	}
}

std::string Logger::getFilename(LogType type) const {
	switch (type) {
	case CONTROLLER: return "logs/controller.log";
		case VIEW: return "logs/view.log";
		case MODEL: return "logs/model.log";
		default: throw std::runtime_error("Error: Unknown log type");
	}
}

std::string Logger::getCurrentTime() const {
	auto now = std::chrono::system_clock::now();
	auto time_t_now = std::chrono::system_clock::to_time_t(now);
	std::tm tm_time{};

#ifdef _WIN32
	localtime_s(&tm_time, &time_t_now); // Windows
#else
	localtime_r(&time_t_now, &tm_time); // Linux/macOS
#endif
	std::ostringstream oss;
	oss << std::put_time(&tm_time, "%Y-%m-%d %H:%M:%S");

	return oss.str();
}

std::string Logger::logLevelToString(LogLevel level) const {
	switch (level) {
		case DEBUG: return "DEBUG";
		case INFO: return "INFO";
		case WARNING: return "WARNING";
		case ERROR: return "ERROR";
		default: return "UNKNOWN";
	}
}

void Logger::checkLogFileSize(LogType type) {
	std::string filename = getFilename(type);

	if (std::filesystem::exists(filename) &&
		std::filesystem::file_size(filename) >= MAX_LOG_FILE_SIZE) {
		std::ofstream logFile(filename, std::ios::trunc);
		logFile << "[LOG RESET] File size exceeded " << MAX_LOG_FILE_SIZE <<
			" bytes.\n";
	}
}

