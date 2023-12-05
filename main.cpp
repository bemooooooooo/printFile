#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>

struct Options {
    int64_t lines = INT32_MAX;
    char delimiter = '\n';
    bool tail = false;
    char* filename = nullptr;
};

int GetLength(char* str) {
    int len = 0;
    while (str[++len] != '\0');
    return len - 1;
}

char* CutString(int begin, int end, char* str) {
    int len = end - begin;
    if (end > begin) {
        int index = 0;
        char* result = new char[len + 1];
        for (int i = begin; i < end; i++) {
            result[index++] = str[i];
        }
        result[index] = '\0';
        return result;
    } else {
        return nullptr;
    }
}

bool Compare(const char* str1, const char* str2) {
    if (str1 == nullptr && str2 == nullptr) {
        return false;
    }
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return false;
        }
        ++str1;
        ++str2;
    }
    return true;
}

void ErrorHandler(const char* error) {
    std::cerr << error;
    exit(EXIT_FAILURE);
}

bool IsNumeric(char* str) {
    int len = GetLength(str);
    for (int i = 0; i < len; ++i) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

char SpecialCharacters(char* delimeter) {
    if (!strcmp(delimeter, "'\\n'")) {
        return '\n';
    } else if (!strcmp(delimeter, "'\\t'")) {
        return '\t';
    } else if (!strcmp(delimeter, "'\\b'")) {
        return '\b';
    } else if (!strcmp(delimeter, "'\\r'")) {
        return '\r';
    } else if (!strcmp(delimeter, "'\\\\'")) {
        return '\\';
    } else if (!strcmp(delimeter, "'\\''")) {
        return '\'';
    } else if (!strcmp(delimeter, "'\\?'")) {
        return '\?';
    } else if (!strcmp(delimeter, "'\"'")) {
        return '\"';
    } else {
        if (GetLength(delimeter) <= 3) {
            return delimeter[1];
        } else {
            ErrorHandler("Input correct delimiter");
        }
    }
}

void GetOption(int argc, char** argv, Options& options, std::ifstream input) {
    bool changes_flag = false;
    for (int i = 1; i < argc - 1; ++i) {
        char* pEnd;
        char* check_lines;
        char check_delim;
        // short options
        if (Compare(argv[i], "-l") && i+1<argc) {
            check_lines = argv[i + 1];
            ++i;

            if (IsNumeric(check_lines)) {
                changes_flag = true;
                options.lines = strtol(check_lines, &pEnd, 10);
            } else {
                ErrorHandler("Input correct number of lines.");
            }
        } else if (Compare(argv[i], "-t") && i + 1 < argc) {
            changes_flag = true;
            options.tail = true;
        } else if (Compare(argv[i], "-d") && i + 1 < argc) {
            check_delim = SpecialCharacters(argv[i + 1]);
            ++i;
            if (check_delim) {
                changes_flag = true;
                options.delimiter = check_delim;
            }
        }
        // long options
        else if (Compare(CutString(0, 8, argv[i]), "--lines=")) {
            check_lines = CutString(8, GetLength(argv[i]), argv[i]);
            if (IsNumeric(check_lines)) {
                changes_flag = true;
                options.lines = strtol(check_lines, &pEnd, 10);
            } else {
                ErrorHandler("Input correct number of lines.");
            }
        } else if (Compare(CutString(0, 6, argv[i]), "--tail")) {
            changes_flag = true;
            options.tail = true;
        } else if (Compare(CutString(0, 12, argv[i]), "--delimiter=")) {
            check_delim = SpecialCharacters(CutString(12, GetLength(argv[i]), argv[i]));
            if (check_delim) {
                changes_flag = true;
                options.delimiter = check_delim;
            }
        //check filename
        } else {
            input.open(argv[i]);
            if (input.is_open())
            {
                options.filename = argv[i];
            }
            else
            {
                ErrorHandler("Input incorrect file name.");
            }
        }
    }
    if (argc > 2 && argc < 6 && !changes_flag){
        ErrorHandler("Input incorrect arguments.");
    } else if (argc >= 6 && !changes_flag) {
        ErrorHandler("Too many arguments.");
    }
}

void Print(const Options& options, std::ifstream input) {
    long long delimeter_counter = 0;
    input.open(options.filename, std::ios_base::ate);
    if (!input.is_open()) {
        ErrorHandler("Input incorrect file name.");
    }
    char temp_char;
    std::streampos pos = input.tellg();
    if (!options.tail) {
        for (int i = 0; i <= pos && delimeter_counter < options.lines; ++i) {
            input.seekg(i, std::ios_base::beg);
            temp_char = input.get();
            if (temp_char == options.delimiter) {
                delimeter_counter++;
            }
            std::cout << temp_char;
        }
    }
    else {
        long long start = 0;
        for (int i = 1; i <= pos && delimeter_counter < options.lines; ++i) {
            input.seekg(-i, std::ios_base::end);
            temp_char = input.get();
            if (temp_char == options.delimiter) {
                start = -i;
                delimeter_counter++;
            }
        }
        input.seekg(start, std::ios_base::end);
        while (!input.eof()) {
            temp_char = input.get();
            std::cout << temp_char;
        }
    }
}
 
int main(int argc, char** argv) {
    std::ifstream in;
    Options options;
    GetOption(argc, argv, options);
    Print(options, in);
}
