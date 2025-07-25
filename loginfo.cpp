#include "loginfo.h"
#include <iostream>
#include <fstream>
#include <ctime>

void logToFile(string message) {
    if (!logFileName.empty()) {
        ofstream logFile;
        logFile.open(logFileName, ios::app); // Append mode
        if (logFile.is_open()) {
            // Add timestamp
            time_t now = time(0);
            char* dt = ctime(&now);
            string timestamp(dt);
            timestamp = timestamp.substr(0, timestamp.length() - 1); // Remove newline
            
            logFile << "[" << timestamp << "] " << message << endl;
            logFile.close();
        }
    }
}

void logM(int logLevel, string message) {
    if (logLevel & verbLevel) {
        switch(logLevel) {
        case LOG_ERR:
            cerr << message;
            break;
        default:
            cout << message;
        }
        // Also write to log file
        logToFile(message);
    }
}

void logMe(int logLevel, string message) {
    if (logLevel & verbLevel) {
        switch(logLevel) {
        case LOG_ERR:
            cerr << message << endl;
            break;
        default:
            cout << message << endl;
        }
        // Also write to log file
        logToFile(message);
    }
}
