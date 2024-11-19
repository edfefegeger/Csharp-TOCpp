#include "Utilities.h"

std::vector<std::string> Utilities::SplitJSON(const std::string& input) {
    std::vector<std::string> messages;
    size_t startObject = 0, open = 0, close = 0;
    bool withinString = false;

    for (size_t i = 0; i < input.size(); ++i) {
        if (input[i] == '"') withinString = !withinString;

        if (input[i] == '{' && !withinString) {
            if (open == 0) startObject = i;
            ++open;
        }
        else if (input[i] == '}' && !withinString) {
            ++close;
        }

        if (open > 0 && open == close) {
            messages.emplace_back(input.substr(startObject, i - startObject + 1));
            open = close = 0;
        }
    }
    return messages;
}
