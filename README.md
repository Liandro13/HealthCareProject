<h1 align="center">🏥 HealthCareProject</h1>
<p align="center">
  Console-based medical clinic management system built in C
</p>
<p align="center">
  <img src="https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white"/>
  <img src="https://img.shields.io/badge/Platform-Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white"/>
  <img src="https://img.shields.io/badge/Status-Completed-brightgreen?style=for-the-badge"/>
</p>

---

## 📋 About

**HealthCareProject** is a console application that simulates a medical clinic management system. It handles doctors and patients with per-doctor waiting queues, and persists all data to files automatically.

## ✨ Features

- **Doctor Management** — register, list, and remove doctors
- **Patient Management** — register, list, and remove patients
- **Waiting Queue** — add/remove patients from a doctor's queue and call the next one
- **Reports** — view the doctor with the most patients
- **Data Persistence** — all data is saved automatically to files after every change

## 🛠️ Tech Stack

| Technology | Description |
|---|---|
| C | Main language |
| Linked Lists | Data structure for doctors and patients |
| File I/O | Data persistence |
| Visual Studio Code | Development IDE |

## 📂 Project Structure

```
HealthCareProject/
├── main.c              # Entry point and data loading
├── funcoes.c           # Business logic (CRUD, queues, persistence)
├── menus.c             # ASCII menu interface
├── headers/
│   ├── funcoes.h
│   └── menus.h
└── data/               # Persisted data files
```

## 🚀 Getting Started

**Prerequisites:** GCC or Visual Studio Code with C/C++ extension

```bash
# Compile
gcc main.c funcoes.c menus.c -o healthcare

# Run
./healthcare
```

Or open the project in VS Code and use the **Run** button.

## 📌 Notes

- Interface in Portuguese
- Sorted insertion by code
- Data saved after every modification