# C++ Ray-Casting Renderer

This project is a simple ray-casting renderer written in C++. It simulates how rays interact with a sphere in a 3D space and outputs a basic image showing the rendered scene.

## Features
- Ray-sphere intersection calculations
- Basic rendering with a single sphere and background color
- Output image in **PPM** format

## Requirements
You need a **C++ compiler** (e.g., `g++`) to compile and run the program.

## How to Compile and Run

1. **Compile the code** using a C++ compiler:
   ```bash
   g++ ray_casting.cpp -o ray_casting
   ```

2. **Run the program**:
   ```bash
   ./ray_casting
   ```

3. The program will generate an image file called `output.ppm` in the project folder. You can open this file using any image viewer that supports the PPM format.


## Folder Structure

```
project-folder/
│
├── ray_casting.cpp       # The main C++ source code file
└── README.md             # This README file
```

## Example Output

The program creates an image called `output.ppm` that displays:
- A red sphere in the center of the image.
- A blue background to simulate the sky.

