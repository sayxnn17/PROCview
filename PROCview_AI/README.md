# PROCview – AI Generated Version

## Description

This folder contains the AI generated implementation of the PROCview assignment.

The aim of this program is to create a custom Linux command called **my_ps** which combines the outputs of the commands `ps aux` and `ps -eLf`. The code was generated using an AI tool based on the assignment problem statement. This version is submitted to compare how AI structures the solution compared to the manually written code.

---


## How the Program Works

The program runs both Linux commands using `system()` and saves their outputs into text files. It then opens those files and reads the required process information using file handling functions. The data from both commands is compared using PID and merged together. The final combined output is written into another file and displayed on the terminal.

---

## Concepts Used

- `system()` → to execute Linux commands  
- `fopen()`, `fscanf()`, `fprintf()` → file handling  
- Structures → storing process details  
- PID matching → merging data  

---

## Files Included

- `ai_code.c` → AI generated source code  
- `ai_prompt.txt` → prompt used  
- `README.md` → documentation  

---

## Purpose

This AI version is submitted to:

- Compare AI vs manual coding style  
- Observe structural differences  
- Understand AI generated logic flow  
- Study modular implementation approach
