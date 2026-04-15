#ifndef SERIAL_PORT_H
#define SERIAL_PORT_H

#include "SerialPort.hpp"
#include <cerrno>
#include <cstring>
#include <stdexcept>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>

int SerialPort::OpenPort(){

    const char* path_cstr = _path.c_str();
    _fd = open(path_cstr, O_RDWR | O_NOCTTY | O_NDELAY);

    
    if (_fd < 0) {
        std::cerr << "[ERROR] The port " << path_cstr << " couldn't be opened: " 
            << strerror(errno) << " (" << errno  << ")" << std::endl;
        return -1;
    } else {
        std::cout << "[INFO] The port " << path_cstr << " opened successfully" << std::endl;
    }

    if (!SetConfiguration()) {
        close(_fd);
        _fd = -1;

        throw std::runtime_error("Error in tty configuration: "
            + _path + ". " + strerror(errno) + " (" + std::to_string(errno) + ")");
    }

    return _fd;
}

bool SerialPort::SetConfiguration(){

    struct termios tty{};
    if(tcgetattr(_fd, &tty)){
        return false;
    }

    cfsetispeed(&tty, _baudrate);
    cfsetospeed(&tty, _baudrate);

    cfmakeraw(&tty);

    // Setting control flags, all flags are described in details in "man termios"
    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;
    
    tty.c_cc[VMIN] = 0;
    tty.c_cc[VTIME] = 10;

    // Setting the baudrate corresponding to the Arduino Uno (B9600) for input and output respectively
    if(tcsetattr(_fd, TCSANOW, &tty)){
        return false;
    }

    return true; 
}

ssize_t SerialPort::ReadLine(std::string& line){

    char buffer[64];

    ssize_t n = read(_fd, buffer, sizeof(buffer) - 1);

    if(n <= 0) return false;

    buffer[n] = '\0';
    _acummulator += buffer;

    size_t pos;
    pos = _acummulator.find('\n');

    if(pos == std::string::npos) return false;

    line = _acummulator.substr(0, pos);

    if (!line.empty() && line.back() == '\r') {
        line.pop_back();
    }

    _acummulator.erase(0, pos + 1);
    return true;

}

#endif
