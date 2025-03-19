# Tile Movement Game

This repository contains my implementation of the **Tile Movement Game** for the **CS204 Advanced Programming** course.  
The project involves working with **2D matrices using vectors**, handling **file I/O**, and implementing **basic game logic** in C++.

---

## Project Description
This project is a simple **tile movement simulation** where each cell in a 2D matrix contains a character that represents movement direction. The game allows users to move tiles in their respective directions until they either hit another tile or fall off the grid.

### **How It Works**
- The program **reads a matrix from a file** and stores it in a **vector of vectors (2D vector)**.
- The user **inputs a row and column index** to select a tile.
- The tile moves **in its respective direction** (`u`, `d`, `l`, `r`).
- The tile **stops moving** when it reaches another tile or the edge of the matrix.
- The game **ends when no more moves are possible** or when the matrix is empty.
