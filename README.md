# Student Record System

A  C-based student record management system that utilizes Binary Search Trees (BST) and Linked Lists for efficient data storage, retrieval, and manipulation.

## 📋 Table of Contents
- [🎯 Overview](#-overview)
- [✨ Features](#-features)
- [📐 Data Structures](#-data-structures)
- [📁 File Structure](#-file-structure)
- [🚀 Installation & Setup](#-installation--setup)
- [💻 Usage](#-usage)
- [📖 Menu Options](#-menu-options)
- [🔧 Technical Details](#-technical-details)
- [📊 Algorithm Complexity](#-algorithm-complexity)
- [👨‍💻 Author](#-author)

## 🎯 Overview

This Student Record System is a console-based application written in C that provides a complete solution for managing student information in an educational institution. The system combines the efficiency of Binary Search Trees for fast data access with the flexibility of Linked Lists for sorted data presentation.

The program reads student data from a file (`students.txt`) and provides various operations including insertion, deletion, searching, updating, and sorting functionalities.

## ✨ Features

### Core Functionalities
- **Student Registration**: Add new students with complete information
- **Search & Update**: Find students by ID and modify their information
- **Alphabetical Listing**: Display all students sorted by name
- **City-based Filtering**: List students from a specific city/address
- **Class Organization**: View students grouped by their class ID
- **Student Removal**: Delete student records
- **Data Persistence**: Save all data back to file
- **Interactive Menu**: User-friendly console interface

### Data Management
- **Persistent Storage**: Automatic file I/O operations
- **Data Validation**: Input validation for student information
- **Memory Management**: Proper allocation and deallocation of memory
- **Error Handling**: Comprehensive error checking and user feedback

## 📐 Data Structures

### Binary Search Tree (BST)
- **Primary Storage**: Main data structure for storing student records
- **Key**: Student ID (unique identifier)
- **Efficiency**: O(log n) average case for search, insert, and delete operations
- **Ordering**: Maintains students sorted by ID for efficient access

### Doubly Linked List
- **Temporary Storage**: Used for sorting and filtering operations
- **Sorting Support**: Enables merge sort implementation
- **Flexibility**: Allows bidirectional traversal

### Student Record Structure
```c
struct tnode {
    int ID;                      // Unique student identifier
    char name[1000];            // Student name
    char address[1000];         // Student address/city
    int classID;                // Class identifier
    char date_of_enrollment[15]; // Enrollment date
    BST right;                  // Right child pointer
    BST left;                   // Left child pointer
};
```

## 📁 File Structure

```
Student-Record-System/
├── P3_1210733_OsaidNur_1.c    # Main source code
├── students.txt               # Student data file (18 student records)
├── project 3.pdf             # Project specifications
└── README.md                 # This documentation
```

## 🚀 Installation & Setup

### Prerequisites
- GCC compiler or any C compiler
- Windows operating system
- Basic understanding of C programming

### Compile and Run
```bash
# Compile the program
gcc -o student_system P3_1210733_OsaidNur_1.c

# Run the program
student_system.exe
```

### Data File Format
The `students.txt` file contains student records in the following format:
```
StudentID    StudentName    ClassID    Address         EnrollmentDate
27           Mahmoud        722        Mecca           2023-05-04
63           Ahmed          431        Cairo           2023-09-24
83           Abdelrahman    1572       Tunis           2023-09-08
105          Fatima         987        Jeddah          2023-11-13
149          Osaid          2793       Tripoli         2023-01-09
173          Sara           372        Amman           2023-05-16
...          ...            ...        ...             ...
```

**Current Dataset**: The system comes with 18 pre-loaded student records from various cities across the Middle East and North Africa.

### Sample Data
The system includes diverse student records such as:
- **Student 27**: Mahmoud from Mecca (Class 722)
- **Student 149**: Osaid from Tripoli (Class 2793) 
- **Student 173**: Sara from Amman (Class 372)
- **Student 4087**: Mohammed from Riyadh (Class 1192)

Cities represented: Mecca, Cairo, Tunis, Jeddah, Tripoli, Amman, Alexandria, Khartoum, Muscat, Beirut, Medina, Doha, Jerusalem, Algiers, Khobar, Dammam, Dubai, and Riyadh.

## 💻 Usage

The program will automatically load the existing 18 student records from `students.txt` when it starts.

### Sample Session
```
***************** Welcome to the School system ***********************
choose the operation (1-8)
1- Insert a Student
2- Search / Update Info. For a student
3- list all Students sorted by name
4- list Students that lives a specific city
5- list all Students by their classes
6- Delete A student
7- Save all data to the file
8- Exit
```

## 📖 Menu Options

### 1. Insert a Student
- Add new student with ID, name, class ID, address, and enrollment date
- Automatically maintains BST ordering by student ID
- Prevents duplicate IDs

### 2. Search / Update Student Information
- Search by student ID
- Display current information
- Update individual fields:
  - Name
  - Address
  - Class ID
  - Enrollment date

### 3. List All Students (Sorted by Name)
- Displays all students alphabetically by name
- Uses merge sort algorithm for efficient sorting
- Shows complete student information in tabular format

### 4. List Students by City
- Filter students by address/city
- Input city name to see all residents
- Results automatically sorted by name

### 5. List Students by Classes
- Groups students by class ID
- Shows each class separately
- Students within each class are sorted by name

### 6. Delete a Student
- Remove student record by ID
- Maintains BST structure after deletion
- Provides confirmation message

### 7. Save Data to File
- Writes all current data to `students.txt`
- Data saved in ID order (in-order BST traversal)
- Ensures data persistence

### 8. Exit Program
- Graceful program termination
- Automatic memory cleanup

## 🔧 Technical Details

### Algorithms Implemented

#### Binary Search Tree Operations
- **Insertion**: O(log n) average, O(n) worst case
- **Search**: O(log n) average, O(n) worst case  
- **Deletion**: O(log n) average, O(n) worst case
- **Traversal**: O(n) for in-order traversal

#### Merge Sort Implementation
- **Time Complexity**: O(n log n) in all cases
- **Space Complexity**: O(n)
- **Stability**: Maintains relative order of equal elements
- **Application**: Used for sorting by name and class ID

#### Memory Management
- Dynamic allocation for all data structures
- Proper deallocation to prevent memory leaks
- Error checking for allocation failures

### File I/O Operations
- **Reading**: Parses student data from text file
- **Writing**: Formats and saves data in readable format
- **Error Handling**: Checks for file access issues

## 📊 Algorithm Complexity

| Operation | Average Case | Worst Case | Best Case |
|-----------|-------------|------------|-----------|
| Insert Student | O(log n) | O(n) | O(1) |
| Search Student | O(log n) | O(n) | O(1) |
| Delete Student | O(log n) | O(n) | O(1) |
| Sort by Name | O(n log n) | O(n log n) | O(n log n) |
| Sort by Class | O(n log n) | O(n log n) | O(n log n) |
| Save to File | O(n) | O(n) | O(n) |

## 👨‍💻 Author

- **Osaid Nur**

