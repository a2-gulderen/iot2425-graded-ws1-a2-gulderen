#include <iostream>
#include <memory>
#include <string>
#include "CSVHALManager.h"
#include "GPSSensor.h"

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <csv_file> <port>" << std::endl;
        return 1;
    }
    
    std::string csvFile = argv[1];
    int port = std::stoi(argv[2]);
    
    // Create a CSVHALManager with at least one port.
    CSVHALManager manager(1);
    
    // Initialize the CSVHALManager with the CSV file.
    try {
        manager.initialise(csvFile);
    } catch (const std::exception &e) {
        std::cerr << "Error initializing CSVHALManager: " << e.what() << std::endl;
        return 1;
    }
    
    // Create and attach the GPSSensor.
    std::shared_ptr<GPSSensor> gpsSensor = std::make_shared<GPSSensor>();
    try {
        manager.attachDevice(port, gpsSensor);
    } catch (const std::exception &e) {
        std::cerr << "Error attaching device: " << e.what() << std::endl;
        return 1;
    }
    
    // Read 5 GPS readings.
    for (int i = 0; i < 5; i++) {
        try {
            std::string output = manager.readFormatted(port);
            std::cout << output << std::endl;
        } catch (const std::exception &e) {
            std::cerr << "Error reading from device: " << e.what() << std::endl;
            break;
        }
    }
    
    // Release the sensor.
    try {
        manager.releaseDevice(port);
    } catch (const std::exception &e) {
        std::cerr << "Error releasing device: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}