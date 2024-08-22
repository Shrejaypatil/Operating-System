# 🕒 Process Scheduling Simulator

🪟 🐧 🍏 ![C++](https://img.shields.io/badge/C++-11/14/17/20-blue.svg) ![License](https://img.shields.io/badge/License-MIT-green.svg) ![Contributors](https://img.shields.io/badge/Contributors-Welcome-orange.svg)

## Overview
This project simulates various process scheduling algorithms in C++. It provides a command-line interface for users to select different scheduling policies and observe their effects on process execution.

## Features
- 📜 **Round Robin Scheduling**
- 🚀 **Priority Scheduling**
- ⏳ **First-Come, First-Served (FCFS)**
- 🛠️ **Custom Configuration Options**

Prerequisites
C++ Compiler: Ensure you have a C++ compiler (e.g., GCC, Clang) installed on your machine.
Clone the Repository
bash
Copy code
git clone https://github.com/your-username/process-scheduling-simulator.git
cd process-scheduling-simulator
Compile the Code
bash
Copy code
g++ index.cpp -o scheduler
Run the Simulator
bash
Copy code
./scheduler

💡 Usage
Input Parameters:

Enter the number of processes.
Input the arrival time, burst time, and optionally, the priority for each process.
View Output:

The program will display the scheduled processes in order, along with their respective times.


📚 Example
Sample Input
mathematica
Copy code
Enter number of processes: 3
Enter arrival time for process 1: 0
Enter burst time for process 1: 5
Enter priority for process 1: 2
...
Sample Output
css
Copy code
Process ID | Arrival Time | Burst Time | Priority
1          | 0            | 5          | 2
...

🧩 Keywords
Process Scheduling
Operating Systems
FCFS
SJF
Priority Scheduling
C++
