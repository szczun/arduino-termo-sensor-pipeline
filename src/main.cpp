#include "SerialPort.hpp"
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <ostream>
#include <unistd.h>

std::string timestamp(){
    const auto now = std::chrono::system_clock::now();
    const std::time_t t_c = std::chrono::system_clock::to_time_t(now);

    std::string s = std::ctime(&t_c);
    s.pop_back();
    return s;
}

int main(){

    SerialPort device("/dev/ttyACM0", B9600);
    int fd = device.OpenPort();

    char buffer[64];
    std::string line = "";

    std::ofstream logFile("../logs/sensor.log", std::ios::app);

    while(true){
        if(!device.ReadLine(line)) continue;

        std::string outLog = timestamp() + " [INFO] " + line;
        std::cout << outLog << std::endl;
        if(logFile.is_open()) logFile << outLog << "\n" << std::flush;
    }
}
