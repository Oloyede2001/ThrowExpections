#include <iostream>

class InvalidCharacterException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid start character";
    }
};

class InvalidRangeException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid offset range";
    }
};

char character(char start, int offset) {
    if (!isalpha(start)) {
        throw InvalidCharacterException();
    }

    char target = start + offset;
    if (!isalpha(target) || abs(offset) >= 26) {
        throw InvalidRangeException();
    }

    return target;
}

int main() {
    try {
        std::cout << "character('a', 1) should return 'b'. Result: " << character('a', 1) << std::endl;
        std::cout << "character('a', -1) should throw an invalidRangeException. Result: ";
        character('a', -1); // This line should throw an exception, not print anything
        std::cout << "character('Z', -1) should return 'Y'. Result: " << character('Z', -1) << std::endl;
        std::cout << "character('?', 5) should throw an invalidCharacterException. Result: ";
        character('?', 5); // This line should throw an exception, not print anything
        std::cout << "Do not allow upper- and lower-case transitions.  character('A', 32) should throw an exception, not return 'a'. Result: ";
        character('A', 32); // This line should throw an exception, not print anything
    } catch (const InvalidCharacterException& e) {
        std::cerr << "Caught InvalidCharacterException: " << e.what() << std::endl;
    } catch (const InvalidRangeException& e) {
        std::cerr << "Caught InvalidRangeException: " << e.what() << std::endl;
    }

    return 0;
}

