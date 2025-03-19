#include <fstream>
#include <string>
#include <memory>

class Logger {
public:
    Logger(const Logger&) = delete;
    
    void operator=(const Logger&) = delete;

    static Logger& getInstance();

    enum LogType { CONTROLLER, VIEW, MODEL };
    enum LogLevel { DEBUG, INFO, WARNING, ERROR };

    void log(LogType type, LogLevel level, const std::string& message);
    
    Logger& operator<<(LogType type);

    Logger& operator<<(LogLevel level);
    
    template <typename T>
    Logger& operator<<(const T& message);

private:
    Logger();
    
    ~Logger();
    
    std::ofstream& getLogFile(LogType type);
    
    std::string getFilename(LogType type) const;
    
    std::string getCurrentTime() const;
    
    std::string logLevelToString(LogLevel level) const;
    
    void checkLogFileSize(LogType type);
    
    std::ofstream controllerFile;
    std::ofstream viewFile;
    std::ofstream modelFile;
    LogType currentType;
    static constexpr std::size_t MAX_LOG_FILE_SIZE = 10 * 1024 * 1024; // 10 MB
};

template<typename T>
inline Logger& Logger::operator<<(const T& message) {
    std::ofstream& logFile = getLogFile(currentType);
    
    checkLogFileSize(currentType);
    
    logFile << message;
    
    return *this;
}
