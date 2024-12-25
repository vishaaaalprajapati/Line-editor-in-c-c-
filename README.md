Project Overview: Text Editor in C++ with Undo/Redo, Search, and CRUD Operations
This project implements a basic text editor in C++ that provides essential editing features, including adding/removing lines, modifying text, searching for words, and undoing/redoing operations. The editor supports CRUD (Create, Read, Update, Delete) operations, search for specific words, and the ability to undo/redo the last few actions. The document can contain a maximum of 25 lines, and the editor supports line-based manipulation.
Key Components:
1.	Classes:
o	Position: 
	Holds the position of a word in the document, represented by lineIndex and charIndex.
o	EditorState: 
	Stores the document's state at any point, along with the action performed ('A' for Add, 'R' for Remove, 'E' for Edit).
o	TextEditor: 
	The main class implementing the text editor functionality, including adding/removing lines, searching, undo/redo, and storing document history for undo/redo operations.
2.	Text Document:
o	The document is represented as a vector of strings, where each string corresponds to a line in the document.
o	The document can hold up to 25 lines (MAX_ENTRIES), and the text editor provides various functionalities to modify the content.
3.	Operations:
o	Add Line: 
	Adds a line of text at a specified position.
	If the document is full (25 lines), it throws an exception.
o	Insert Word: 
	Inserts a word at a specific position within a line.
o	Locate Word: 
	Searches for a word in the document and returns its position (line and character index).
o	Show Document: 
	Displays all the lines in the document, including an empty line for lines that have no content.
o	Replace Word: 
	Finds and replaces a word in a specific line starting from a given character position.
o	Edit Line: 
	Modifies a line starting at a given character index by replacing the text with new content.
o	Remove Line: 
	Deletes a specified line from the document.
o	Remove Word: 
	Deletes a word from a specified line at a given position.
o	Undo/Redo: 
	Supports undoing the last 3 actions and redoing them.
	Uses two stacks (undoHistory and redoHistory) to track changes to the document and revert or restore them.
4.	Undo/Redo Mechanism:
o	Every operation (e.g., adding, editing, or removing a line or word) stores the current state of the document in an undo stack.
o	When the user undoes an action, the most recent state is restored from the undo stack.
o	When the user redoes an action, the state is moved from the redo stack back to the document.
o	This mechanism helps users reverse and reapply changes, with a history depth limited to 3 operations.
5.	Error Handling:
o	Exceptions are thrown for invalid operations (e.g., trying to add a line beyond the maximum limit, accessing invalid line indexes, etc.).
o	Try-catch blocks are used to catch and handle errors gracefully, displaying helpful messages to the user.
6.	Interactive Command-Line Interface:
o	The user can interact with the editor through the command line. The program prompts the user to choose an operation, such as adding a line, searching for a word, or undoing an action.
o	Supported commands include: 
	add: Adds a line to the document.
	find: Locates a word in the document.
	show: Displays the entire document.
	replace: Replaces a word in the document.
	remove: Deletes a line.
	undo: Reverts the last change.
	redo: Reapplies the last undone change.
	exit: Exits the editor.
7.	Data Persistence:
o	While this version of the editor does not include file I/O (saving and loading files), the document's state is maintained in memory, allowing for real-time editing and manipulation.
How the Editor Works:
1.	Document Initialization:
o	The editor initializes with an empty document, where the user can perform various operations such as adding or removing lines.
2.	Text Manipulation:
o	Text can be added at any line (within the document’s limit).
o	Words can be inserted or replaced in specific positions within lines.
o	Lines can be removed, and text within lines can be modified.
3.	Search and Navigation:
o	Users can search for a word within the document and locate its position (line number and character index).
4.	Undo/Redo:
o	Users can undo up to the last 3 actions and redo them using the undo/redo functionality. This makes it easier to correct mistakes or restore changes.
5.	Error Handling:
o	The program handles invalid inputs gracefully by throwing exceptions and printing error messages, ensuring the user can correct mistakes or understand what went wrong.
Potential Enhancements:
•	File I/O: 
o	Implement file reading and writing functionality, allowing the user to open existing files and save changes to them.
•	Search Improvements: 
o	Add case-insensitive search or regular expression support for more advanced word searching.
•	User Interface: 
o	Enhance the user interface with better navigation and more command options, potentially supporting text-based menus or external libraries like ncurses for a richer command-line experience.
•	Document Versioning: 
o	Extend the undo/redo history to include more than just the last 3 actions.
•	Multiple Undo Levels: 
o	Allow the user to undo and redo beyond a fixed limit by storing multiple states in a more advanced history mechanism
