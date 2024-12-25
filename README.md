# Text Editor Project

## Overview

This is a basic Text Editor implemented in C++. The program provides functionality to manage and edit text documents with multiple lines, allowing for operations such as adding, removing, editing, and searching text. Additionally, undo and redo functionalities are supported to enhance user experience.

---

## Features

1. **Core Functionalities**:
   - Add, edit, remove, and display lines in the document.
   - Locate specific words and replace them within the document.
   - Insert or remove words at specific positions.

2. **Undo/Redo Mechanism**:
   - Tracks document states with a stack-based approach.
   - Allows up to 3 levels of undo and redo operations.

3. **Document Limitations**:
   - Maximum of 25 lines in a document.
   - Validates inputs for line numbers and character positions.

4. **User Interaction**:
   - Command-line interface for real-time operations.
   - Handles operations via keywords such as `add`, `find`, `replace`, `remove`, `undo`, `redo`, and `exit`.

5. **Performance Optimization**:
   - Efficiently manages document lines using `std::vector`.
   - Leverages `std::stack` for undo and redo history.

---

## Usage

1. **Adding a Line**:
   - Specify a line number and provide the text content.

2. **Finding a Word**:
   - Input the word to search within the document.

3. **Replacing Content**:
   - Select a line and character position to replace text with new content.

4. **Undo/Redo Actions**:
   - Revert or reapply the last change made to the document.

5. **Removing a Line**:
   - Choose a line number to delete it from the document.

---

## Error Handling

- Ensures the document does not exceed the maximum line capacity.
- Catches invalid line numbers and positions during operations.
- Handles edge cases for undo/redo actions gracefully.



