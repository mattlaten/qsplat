#include <iostream>
#include <string>

class logger {
    public:
        logger() {}
        ~logger() {}

        inline void info(std::string message) {
            std::cout << "INFO: " << message << std::endl;
        }
        
        inline void err(std::string message) {
            std::cout << "ERROR: " << message << std::endl;
        }
    private:

};
