#include "Utilities.h"
#include <cstring> // Для работы с C-строками

char** Utilities::SplitJSON(const char* input, unsigned int& messageCount) {
    messageCount = 0;
    unsigned int maxMessages = 10; // Ограничение на количество сообщений
    char** messages = new char* [maxMessages]; // Динамический массив указателей на строки

    size_t startObject = 0, open = 0, close = 0;
    bool withinString = false;

    for (size_t i = 0; i < strlen(input); ++i) {
        if (input[i] == '"') {
            withinString = !withinString;
        }

        if (input[i] == '{' && !withinString) {
            if (open == 0) startObject = i;
            ++open;
        }
        else if (input[i] == '}' && !withinString) {
            ++close;
        }

        if (open > 0 && open == close) {
            // Выделяем память для строки и копируем подстроку с использованием strncpy_s
            size_t messageLength = i - startObject + 1;
            messages[messageCount] = new char[messageLength + 1];
            strncpy_s(messages[messageCount], messageLength + 1, input + startObject, messageLength);
            messages[messageCount][messageLength] = '\0'; // Завершаем строку нулевым символом

            ++messageCount;

            // Если достигнут предел сообщений, увеличиваем его
            if (messageCount >= maxMessages) {
                maxMessages *= 2;
                char** newMessages = new char* [maxMessages];
                for (unsigned int j = 0; j < messageCount; ++j) {
                    newMessages[j] = messages[j];
                }
                delete[] messages;
                messages = newMessages;
            }

            open = close = 0;
        }
    }

    return messages;
}

// Освобождаем память для сообщений
void Utilities::FreeMessages(char** messages, unsigned int messageCount) {
    for (unsigned int i = 0; i < messageCount; ++i) {
        delete[] messages[i];
    }
    delete[] messages;
}
