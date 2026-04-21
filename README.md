# Escape Room Manager

A C++ application developed for CS 302 (Programming Methodologies and Software Implementation) at Portland State University.

## Overview

A menu-driven system that manages an interactive escape room experience, including player turn rotation, active challenge progression, and special event scheduling. The application demonstrates advanced object-oriented design and recursive data structure implementation.

## Features

- Player management with circular linked list for continuous turn rotation
- Active challenge tracking with linear linked list for sequential puzzle progression
- Special event scheduling with STL vector for dynamic event management
- Three distinct escape experience types: Puzzle, Mystery, and Athletic
- Full menu-driven interface for game host interaction

## Technical Highlights

- Single inheritance hierarchy with abstract base class and three derived classes
- All linked list operations implemented using exclusively recursive algorithms
- Dynamic memory management with destructors, copy constructors, and assignment operators (Rule of Three)
- Mix of raw memory management (char*) and modern C++ (STL string, vector)
- Compiled warning-free with the -Wall flag

## Tech Stack

- **Language:** C++
- **Concepts:** Object-Oriented Programming, Inheritance, Polymorphism, Recursion, Dynamic Memory Management
- **Data Structures:** Circular Linked List, Linear Linked List, STL Vector

## How to Run

```bash
g++ -Wall -o escape_room *.cpp
./escape_room
```

## Author

Payal Mistry — Computer Science, Portland State University
