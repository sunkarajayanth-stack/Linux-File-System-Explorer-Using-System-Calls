# Linux File System Explorer Using System Calls

## 1. Project Title

Linux File System Explorer Using System Calls

---

## 2. Project Description

Linux File System Explorer is a command-line based file management application developed in C for Linux systems.

The project provides a simple interface for exploring and managing files and directories through Linux system calls and system-level interfaces.

Instead of depending entirely on high-level file management utilities, the project demonstrates how Linux applications interact with the operating system kernel through system calls.

---

## 3. Objectives

The main objectives of this project are:

- To understand Linux file system operations.
- To understand the concept of file descriptors.
- To demonstrate Linux system calls.
- To explore directories programmatically.
- To obtain file metadata.
- To perform basic file management operations.
- To implement recursive file searching.
- To understand the interaction between user programs and the Linux kernel.

---

## 4. Features

The project provides the following features:

1. List directory contents
2. Change directory
3. Navigate to the parent directory
4. Display file information
5. Read file contents
6. Create files
7. Create directories
8. Delete files
9. Delete empty directories
10. Rename files and directories
11. Recursively search for files
12. Display the current working directory

---

## 5. Technologies Used

### Programming Language

C

### Operating System

Linux / Ubuntu

### Compiler

GCC

### Development Environment

Linux Terminal / Ubuntu / WSL

### Build Tool

Make

---

## 6. System Calls and Linux Interfaces Used

| System Call / Interface | Purpose |
|---|---|
| open() | Opens files and directories |
| read() | Reads data from files |
| write() | Writes data to standard output |
| close() | Closes file descriptors |
| getcwd() | Obtains the current working directory |
| chdir() | Changes the current directory |
| stat() | Obtains file metadata |
| mkdir() | Creates a directory |
| rmdir() | Removes an empty directory |
| unlink() | Deletes a file |
| rename() | Renames a file or directory |
| getdents64 | Reads directory entries |

---

## 7. Project Structure

```text
Linux-File-System-Explorer/
│
├── main.c
├── explorer.c
├── explorer.h
├── directory.c
├── directory.h
├── file_operations.c
├── file_operations.h
├── search.c
├── search.h
├── Makefile
└── README.md
