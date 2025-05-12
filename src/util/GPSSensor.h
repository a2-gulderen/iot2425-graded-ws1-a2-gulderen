#ifndef GPSSENSOR_H
#define GPSSENSOR_H

#include "hal/ISensor.h"  // Adjust the include path if needed
#include <ctime>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>

class GPSSensor : public ISensor {
private:
    time_t currentTime;
public:
    GPSSensor() {
        // Initialize currentTime with the actual system time.
        currentTime = std::time(nullptr);
    }
    
    virtual ~GPSSensor() = default;
    
    // Returns the starting column index for CSV data.
    virtual int getId() const override {
        return 0;
    }
    
    // GPS sensor uses 2 columns: latitude and longitude.
    virtual int getDimension() const override {
        return 2;
    }
    
    // Format the CSV row data with the actual current date/time.
    virtual std::string format(const std::vector<uint8_t>& reading) override {
        // Convert the vector<uint8_t> into a string.
        std::string data(reading.begin(), reading.end());
        size_t commaPos = data.find(',');
        std::string lat = (commaPos != std::string::npos) ? data.substr(0, commaPos) : data;
        std::string lon = (commaPos != std::string::npos) ? data.substr(commaPos + 1) : "";
        
        // Create a buffer large enough for the timestamp.
        char buffer[64];
        std::tm* timeinfo = std::localtime(&currentTime);
        std::strftime(buffer, sizeof(buffer), "[%Y-%m-%d %H:%M:%S]", timeinfo);
        
        std::ostringstream oss;
        oss << buffer << " GPS: " << lat << "; " << lon;
        
        // Increment time by 5 seconds for the next reading.
        currentTime += 5;
        return oss.str();
    }
};

#endif // GPSSENSOR_H