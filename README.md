# 📖 Get_Next_Line

![Language](https://img.shields.io/badge/Language-C-blue)
![Memory](https://img.shields.io/badge/Focus-Memory%20Management-green)
![System](https://img.shields.io/badge/System-Programming-orange)

> A low-level C function that reads a file **line by line**, demonstrating efficient buffer handling, file descriptor management, and dynamic memory control.

`get_next_line` is a core project in the **42 curriculum**, designed to teach how to interact with the operating system at a low level using **file descriptors** and **dynamic memory management**.

The goal is to implement a function capable of reading a file **one line at a time**, regardless of the file size or the buffer size.

---

## 📌 Project Description

Implement the function:

```c
char *get_next_line(int fd);
```

 This function reads from a file descriptor and returns the next line of the file each time it is called.

### Requirements

The function must:

- Read from a file descriptor

- Return one line per function call

- Include the newline character \n when present

- Work with any BUFFER_SIZE

- Return NULL when there is nothing left to read

- Avoid memory leaks

- Handle files of any size
---

## ⚙️ How the Algorithm Works

The algorithm works in four main stages:
```text
read() → buffer → stash → extract line → return line
```
### Step-by-step process

1️⃣ Read from the file descriptor using read()


2️⃣ Store the read data in a temporary buffer


3️⃣ Append that data to a static stash


4️⃣ Extract the first complete line


5️⃣ Return the line


6️⃣ Keep the remaining data for the next call

---

## 🧠 The Static Buffer Concept

The key to get_next_line is the static variable.
```c

static char *stash;
```

A static variable:

- persists between function calls

- stores leftover data after a line is returned

### Example

File content:
```bash
Hello world\nHow are you\n42
```

After the first read:
```c

stash = "Hello world\nHow are you\n42"
```

Returned line:
```bash

Hello world\n
```
Remaining stash:
```bash
How are you\n42
```
---
## 📊 Visual Algorithm Flow
```text
FILE
 │
 ▼
read(fd, buffer, BUFFER_SIZE)
 │
 ▼
BUFFER
 │
 ▼
append to STASH
 │
 ▼
Is newline found?
 │
 ├─ YES → extract line
 │        update stash
 │        return line
 │
 └─ NO → read more
```
---
## 📁 Project Structure
```repo
get_next_line/
│
├── get_next_line.c
├── get_next_line.h
│
├── get_next_line_bonus.c
├── get_next_line_bonus.h
│
└── README.md
```
### Mandatory Part

Files:

- get_next_line.c

- get_next_line.h

Handles reading from a single file descriptor.

### Bonus Part

Files:

- get_next_line_bonus.c
  
- get_next_line_bonus.h

Adds support for multiple file descriptors simultaneously.

Implementation uses an array of stashes:
```c
static char *stash[FD_MAX];
```

This allows the function to maintain a separate buffer for each file descriptor.

---

## 🔧 Key Functions Implemented

Typical helper functions include:
```
ft_strlen
```
Calculate string length.
```
ft_strjoin
```
Concatenate strings dynamically.
```
ft_strchr
```
Locate newline characters.
```
ft_substr
```
Extract a portion of a string.

These utilities allow safe manipulation of dynamically allocated strings.

---
## ▶️ Example Usage
```c
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("file.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
}
```
---
### 📄 Example Input
```bash
Hello
World
42
Network
```
### 📤 Output
```
Hello
World
42
Network
```
Each line is returned separately with every call to get_next_line.

---

## ⚡ Compilation

Compile the mandatory part:
```bash
cc -Wall -Wextra -Werror get_next_line.c
```
Compile the bonus part:
```bash
cc -Wall -Wextra -Werror get_next_line_bonus.c
```
---
## 🧩 Edge Cases Handled

The implementation correctly handles:

- Very large files

- Files without newline at the end

- Multiple file descriptors (bonus)

- BUFFER_SIZE values of any size

- Empty files

- Files containing only newline characters

---

## 🛠 Skills Developed

This project strengthens understanding of:

- System Programming

- file descriptors

- read() system call

- Memory Management

- malloc

- free

- avoiding memory leaks

- Algorithms

- incremental reading

- efficient string manipulation

- state preservation across calls

- Debugging

- segmentation faults

- buffer overflows

- memory leaks

---

## 📚 Concepts Mastered

- static variables

- dynamic memory allocation

- file descriptor management

- buffered input handling

- modular C design

## 👨‍💻 Author

# Walid Krati

### Software Engineering Student • System Programming • C

GitHub:
```url
https://github.com/wkratos77
```

⭐ If you found this project interesting, feel free to explore the implementation.
