# 📂 C Binary File Management System

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue.svg" alt="Language">
</p>

An optimized, low-level binary data management system implemented in pure C. This project simulates a custom binary file format (`.oflu`) using **Structure Packing**, **Pointer Arithmetic**, and **Direct Block I/O**, allowing for highly compact storage and efficient database-like CRUD operations on structural data.

---

## 📌 Table of Contents
- [Core Features](#-core-features)
- [Architecture & Memory Layout](#-architecture--memory-layout)
- [File Manipulation Breakdown](#-file-manipulation-breakdown)
- [Getting Started](#-getting-started)
- [CLI Operations](#-cli-operations)
- [License](#-license)

---

## ✨ Core Features

* **Zero-Padding Compression:** Prevents memory alignment gaps via compiler directives, ensuring minimum storage footprint.
* **$O(1)$ Item Counting:** Computes total element counts instantly using file pointer tell operations without exhausting the disk with loops.
* **In-Memory Pointer Filtering:** Utilizes advanced pointer mechanics (`newDatas++`) to perform lightning-fast deletion buffers.
* **High-Throughput Block I/O:** Drastically cuts disk overhead by utilizing raw `fread` and `fwrite` operations directly over complete memory sheets.

---

## 🧠 Architecture & Memory Layout

By default, modern C compilers align struct structures to 4 or 8-byte boundaries (Structure Padding), creating dead memory gaps. This project utilizes `#pragma pack(push, 1)` to crush down structural alignments.



### 📊 Data Footprint Math
- **`struct Vector`:** 3 elements $\times$ 8 bytes (`double`) = **24 bytes**
- **`struct MyFile`:** 1 element $\times$ 4 bytes (`int`) + 24 bytes (`Vector`) = **28 bytes**

```c
#pragma pack(push, 1)
struct Vector {
    double x;
    double y;
    double z;
};

struct MyFile {
    int id;
    struct Vector position;
};
#pragma pack(pop)
