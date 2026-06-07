# Urban Analysis System

A comprehensive C++ application for analyzing urban data using both array-based and linked list-based data structures.

## Project Structure

```
├── src/
│   ├── array_program/       # Array-based implementation
│   │   ├── analysis.cpp/h   # Data analysis functionality
│   │   ├── experiments.cpp/h # Experimental operations
│   │   ├── globals.cpp/h    # Global variables and constants
│   │   ├── menu.cpp/h       # User interface menu
│   │   ├── searching.cpp/h  # Search operations
│   │   ├── sorting.cpp/h    # Sorting operations
│   │   ├── utils.cpp/h      # Utility functions
│   │   └── resident.h       # Resident data structure
│   ├── linked_list/         # Linked list implementation
│   │   ├── Helper.cpp/hpp   # Helper functions
│   │   ├── linkedList.cpp   # Main linked list logic
│   │   └── LinkedList.hpp   # Linked list header
│   └── main.cpp             # Main entry point
├── data/                    # Dataset files
│   ├── dataset1-cityA.csv
│   ├── dataset2-cityB.csv
│   └── dataset3-cityC.csv
└── build/                   # Compiled executables and object files

## Features

- **Array-based Data Structure**: Efficient array operations for urban data management
- **Linked List Implementation**: Alternative data structure for comparison
- **Search & Sorting**: Multiple search and sorting algorithms
- **Data Analysis**: Statistical analysis and reporting capabilities
- **Interactive Menu**: User-friendly interface for operations

## Compilation

```bash
# Compile array program
g++ -o build/array_program src/array_program/*.cpp

# Compile linked list program
g++ -o build/linked_list src/linked_list/*.cpp
```

## Usage

Run the compiled executable:

```bash
./build/array_program
# or
./build/linked_list
```

## Files Overview

### Array Program
- `analysis.cpp/h`: Data analysis functions
- `experiments.cpp/h`: Experimental features
- `searching.cpp/h`: Search algorithms
- `sorting.cpp/h`: Sorting algorithms
- `menu.cpp/h`: Interactive menu system
- `utils.cpp/h`: Utility functions

### Linked List Program
- `linkedList.cpp`: Core linked list implementation
- `Helper.cpp`: Support functions

### Data Files
- CSV format datasets for three cities (A, B, C)
- Used for testing and analysis

## Author
APU Data Structure Assignment - Year 2 Semester 2

## License
Academic Use Only
