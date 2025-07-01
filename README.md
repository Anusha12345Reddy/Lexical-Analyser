# Lexical-Analyser

📘 Lexical Analyzer Project – Explanation

The Lexical Analyzer is a command-line based utility built in C that scans a source code file and breaks it down into meaningful tokens — the very first step in any compiler’s front-end processing. This project emulates how a compiler identifies basic building blocks such as keywords, identifiers, constants, operators, and symbols from raw source code.

The program reads an input `.c` or `.txt` file line by line, processes each character, and classifies sequences of characters into tokens based on predefined lexical rules. These tokens are then categorized and displayed with detailed type information. It handles edge cases like multi-character operators (`>=`, `!=`), number formats, and ignores white spaces or comments.

Key capabilities include:

- Identifies and classifies:
  - Keywords (e.g., `int`, `while`)
  - Identifiers (e.g., variable names)
  - Constants (numbers)
  - Operators (`+`, `-`, `==`, etc.)
  - Special symbols (`;`, `{}`, `()` etc.)
- Handles single-line and multi-line comments
- Uses a deterministic, rule-based scanning algorithm
- Cleanly separates scanning logic into modular functions

This project closely mirrors how a real-world compiler breaks input into lexemes and showcases the fundamental concept of lexical analysis in language processing. It’s a foundational exercise in compiler design and teaches crucial aspects of parsing and state-based token classification.

🔹 What This Project Showcases:

- Core understanding of compiler front-end design (lexical phase)
- Finite-state machine logic and token classification
- String manipulation and buffer-based file handling in C
- Modular coding for scalable language processing tools
