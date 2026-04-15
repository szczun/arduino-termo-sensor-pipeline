# Arduino Termo Sensor Pipeline

[![Arduino Reader Workflow](https://github.com/szczun/arduino-termo-sensor-pipeline/actions/workflows/ci.yml/badge.svg)](https://github.com/szczun/arduino-termo-sensor-pipeline/actions/workflows/ci.yml)

## About the project

The purpose of this project is dedicated for reading the data sent by Arduino Uno coupled with the TinkerKit Thermistor Module. Data is collected via UART serial communication, logged to a file with timestamps, and validated through an automated CI/CD pipeline with Python unit and integration tests.
This project runs on **Linux OS** only.

## Project structure
```
arduino-sensor-pipeline/
├── src/            # C++ source files (SerialPort class, main entry point)
├── log_parser/     # Python parser for processing log files
├── tests/          # Pytest unit and integration tests
│   └── fixtures/   # Sample log files for testing
├── logs/           # Runtime logs generated during execution (gitignored)
├── sketch/         # Arduino sketch
└── .github/        # CI/CD pipeline
```

## Prerequisites
- Linux OS
- g++ compiler
- CMake 3.10+
- Python 3.8+
- Arduino Uno
- Arduino IDE / Arduino CLI

## Getting started
```bash
git clone https://github.com/szczun/arduino-termo-sensor-pipeline
cd arduino-termo-sensor-pipeline
mkdir build && cd build
cmake ..
make
```

NOTE: If you are not able to run the code, because of the denied permissions, you have to manually add yourself to the dialout group
```bash
sudo usermod -aG dialout $USER
```
After that reload the terminal. You can also check if the command line worked by typing
```bash
groups
```

## Running the tests
If you don't have the pytest framework installed on your local machine, then you should do it by using following command
```bash
pip install pytest
```
After the successful installation process you can run the tests
```bash
pytest tests/
```
