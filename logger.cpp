#include <iostream>
#include <string>

class Logger {
    public:
        Logger() {}
        ~Logger() {}

        info(string message) {
            cout << "INFO: " << message << endl;
        }
        
        err(string message) {
            cout << "ERROR: " << message << endl;
        }
    private:

}
