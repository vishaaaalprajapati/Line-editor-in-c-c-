#include <iostream>
#include <string>
#include <vector>
#include <stack>

class Position {
public:
    int lineIndex;
    int charIndex;
    
    Position(int line = -1, int pos = -1) : lineIndex(line), charIndex(pos) {}
};

class EditorState {
public:
    std::vector<std::string> content;
    char action;  // 'A': Add, 'R': Remove, 'E': Edit

    EditorState(const std::vector<std::string>& c, char act) 
        : content(c), action(act) {}
};

class TextEditor {
private:
    static const int MAX_ENTRIES = 25;
    static const int UNDO_DEPTH = 3;
    
    std::vector<std::string> document;
    std::stack<EditorState> undoHistory;
    std::stack<EditorState> redoHistory;

public:
    TextEditor() {
        document.reserve(MAX_ENTRIES);
    }

    void addLine(int index, const std::string& text) {
        if (document.size() >= MAX_ENTRIES) {
            throw std::runtime_error("Cannot add line: document is at capacity (25 entries max)");
        }

        while (index > document.size()) {
            document.push_back("");
        }

        storeState('A');
        if (index == document.size()) {
            document.push_back(text);
        } else {
            document.insert(document.begin() + index, text);
        }
        
        std::cout << "Line added successfully. Document size: " << document.size() << "/" << MAX_ENTRIES << std::endl;
    }

    void insertWord(const Position& pos, const std::string& word) {
        if (pos.lineIndex >= 0 && pos.lineIndex < document.size()) {
            storeState('E');
            document[pos.lineIndex].insert(pos.charIndex, word);
        }
    }

    Position locateWord(const std::string& word) {
        for (size_t i = 0; i < document.size(); ++i) {
            size_t pos = document[i].find(word);
            if (pos != std::string::npos) {
                return Position(i, pos);
            }
        }
        return Position();
    }

    void showLine(int lineIndex) const {
        if (lineIndex >= 0 && lineIndex < document.size()) {
            std::cout << "[Line " << lineIndex + 1 << ":] " 
                      << (document[lineIndex].empty() ? "(empty)" : document[lineIndex]) 
                      << std::endl;
        }
    }

    void showDocument() const {
        if (document.empty()) {
            std::cout << "Document is empty\n";
            return;
        }
        std::cout << "\nDocument contents (" << document.size() << "/" << MAX_ENTRIES << " entries):\n";
        for (size_t i = 0; i < document.size(); ++i) {
            showLine(i);
        }
    }

    void replaceWord(const Position& pos, const std::string& oldWord, 
                     const std::string& newWord) {
        if (pos.lineIndex >= 0 && pos.lineIndex < document.size()) {
            storeState('E');
            std::string& line = document[pos.lineIndex];
            size_t location = line.find(oldWord, pos.charIndex);
            if (location != std::string::npos) {
                line.replace(location, oldWord.length(), newWord);
            }
        }
    }

    void editLine(int lineIndex, int startChar, const std::string& newText) {
        if (lineIndex < 0 || lineIndex >= document.size()) {
            throw std::out_of_range("Invalid line index");
        }

        storeState('E');
        std::string& line = document[lineIndex];
        if (startChar <= line.length()) {
            line = line.substr(0, startChar) + newText;
        }
    }

    void removeLine(int lineIndex) {
        if (lineIndex < 0 || lineIndex >= document.size()) {
            throw std::out_of_range("Invalid line index");
        }

        storeState('R');
        document.erase(document.begin() + lineIndex);
        std::cout << "Line removed successfully. Document size: " << document.size() << "/" << MAX_ENTRIES << std::endl;
    }

    void removeWord(const Position& pos, const std::string& word) {
        if (pos.lineIndex >= 0 && pos.lineIndex < document.size()) {
            storeState('R');
            std::string& line = document[pos.lineIndex];
            size_t location = line.find(word, pos.charIndex);
            if (location != std::string::npos) {
                line.erase(location, word.length());
            }
        }
    }

    void undoAction() {
        if (!undoHistory.empty()) {
            redoHistory.push(EditorState(document, 'E'));
            document = undoHistory.top().content;
            undoHistory.pop();
            std::cout << "Undo completed. Document size: " << document.size() << "/" << MAX_ENTRIES << std::endl;
        } else {
            std::cout << "Nothing to undo\n";
        }
    }

    void redoAction() {
        if (!redoHistory.empty()) {
            undoHistory.push(EditorState(document, 'E'));
            document = redoHistory.top().content;
            redoHistory.pop();
            std::cout << "Redo completed. Document size: " << document.size() << "/" << MAX_ENTRIES << std::endl;
        } else {
            std::cout << "Nothing to redo\n";
        }
    }

private:
    void storeState(char action) {
        undoHistory.push(EditorState(document, action));
        while (undoHistory.size() > UNDO_DEPTH) {
            undoHistory.pop();
        }
        redoHistory = std::stack<EditorState>();
    }
};

int main() {
    TextEditor editor;
    std::string operation;

    std::cout << "Text Editor Initialized\n";
    std::cout << "Maximum document size: 25 lines\n";
    
    while (true) {
        std::cout << "\nOptions: add, find, show, replace, remove, undo, redo, exit\n";
        std::cout << "Choose an operation: ";
        std::cin >> operation;

        try {
            if (operation == "add") {
                int lineNumber;
                std::string inputText;
                std::cout << "Specify line number (1-25): ";
                std::cin >> lineNumber;
                if (lineNumber < 1 || lineNumber > 25) {
                    throw std::out_of_range("Line number must be between 1 and 25");
                }
                std::cout << "Provide text: ";
                std::cin.ignore();
                std::getline(std::cin, inputText);
                editor.addLine(lineNumber - 1, inputText);
            }
            else if (operation == "find") {
                std::string searchTerm;
                std::cout << "Input word to locate: ";
                std::cin >> searchTerm;
                Position result = editor.locateWord(searchTerm);
                if (result.lineIndex != -1) {
                    std::cout << "Located at line " << result.lineIndex + 1 
                              << ", position " << result.charIndex << std::endl;
                } else {
                    std::cout << "Word not found\n";
                }
            }
            else if (operation == "show") {
                editor.showDocument();
            }
            else if (operation == "replace") {
                int lineNum, charPos;
                std::string newText;
                std::cout << "Enter line number to replace: ";
                std::cin >> lineNum;
                std::cout << "Enter character position: ";
                std::cin >> charPos;
                std::cout << "Provide new content: ";
                std::cin.ignore();
                std::getline(std::cin, newText);
                editor.editLine(lineNum - 1, charPos, newText);
            }
            else if (operation == "remove") {
                int lineToDelete;
                std::cout << "Enter line number to delete: ";
                std::cin >> lineToDelete;
                editor.removeLine(lineToDelete - 1);
            }
            else if (operation == "undo") {
                editor.undoAction();
            }
            else if (operation == "redo") {
                editor.redoAction();
            }
            else if (operation == "exit") {
                break;
            }
            else {
                std::cout << "Invalid operation\n";
            }
        }
        catch (const std::exception& err) {
            std::cerr << "Error: " << err.what() << std::endl;
        }
    }

    return 0;
}
