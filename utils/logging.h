#ifndef LOGGING_H
#define LOGGING_H


namespace logg
{
    // debug 0 - in concole in every loop
    // info 1 - game events
    // error 2

    void print(std::string message, int level)
    {
        if(level >= LOGGING)
        {
            std::cout << message << std::endl;
        }

    }
}



















#endif