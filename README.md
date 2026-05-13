# C Task Manager CLI

A lightweight command-line task management application written in pure C for Linux environments.

This project was created to practice low-level programming concepts including:
- file I/O
- pointer manipulation
- string parsing
- memory-safe buffer handling
- command-line application design

The application stores tasks in local text files and supports task creation, listing, updating, and completion tracking directly from the terminal.

---

# Motivation

The goal of this project was to strengthen core C programming skills and better understand memory management, file handling, and CLI application architecture at a lower level than modern high-level frameworks typically expose.

---

# Features

- Create, edit and delete new lists
- Add new tasks
- Display active tasks
- Mark tasks as completed
- Persistent file-based storage
- Automatic task reindexing
- Lightweight terminal workflow
- No external dependencies

---

# Technologies

- C
- GCC
- Standard C Library
- Linux CLI environment

---

# Project Structure

```text
.
├── main.c
├── tasks.txt
├── done.txt
└── README.md
```

---

# Future Improvements

- Command-line arguments (todo add, todo done, todo list)
- Colored terminal output
- Task priorities
- Due dates
- Modular architecture using .h and .c files
- Makefile support
- Linux package installation
- ncurses interface
