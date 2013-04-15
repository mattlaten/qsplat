#include <iostream>
#include <string>

class Logger {
    public:
        Logger() {}
        ~Logger() {}

        inline info(string message) {
            cout << "INFO: " << message << endl;
        }
        
        inline err(string message) {
            cout << "ERROR: " << message << endl;
        }
    private:

}
