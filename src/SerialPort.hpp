#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string>
#include <iostream>

class SerialPort{
    public:

        SerialPort(const std::string& path, speed_t baudrate)
            : _path(path), _baudrate(baudrate) {}

        ~SerialPort() { 
            if (_fd != -1) {
                std::cout << "[INFO] Closing the port" << std::endl;
                close(_fd); 
                _fd = -1;
            }
        }

        int OpenPort();
        ssize_t ReadLine(std::string&);
        ssize_t WriteData();

    private:
        bool SetConfiguration();

        std::string _path = "";
        speed_t _baudrate = B9600;
        int _fd = -1;
        std::string _acummulator;
};
