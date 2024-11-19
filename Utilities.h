#ifndef UTILITIES_H
#define UTILITIES_H

class Utilities {
public:
    static char** SplitJSON(const char* input, unsigned int& messageCount);
    static void FreeMessages(char** messages, unsigned int messageCount);
};

#endif // UTILITIES_H
