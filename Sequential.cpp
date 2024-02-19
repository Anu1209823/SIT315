﻿#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function to initialize a matrix with random values
void initializeMatrix(int** matrix, int size)
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            matrix[i][j] = rand() % 10; // Generate random values between 0 and 9
        }
    }
}

// Function to print a matrix to the console
void printMatrix(int** matrix, int size)
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Function to write a matrix to a file
void writeMatrixToFile(int** matrix, int size, const char* filename)
{
    ofstream outputFile(filename);
    if (!outputFile.is_open())
    {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            outputFile << matrix[i][j] << " ";
        }
        outputFile << endl;
    }

    outputFile.close();
    cout << "Matrix written to file: " << filename << endl;
}

// Function to perform matrix multiplication
void matrixMultiplication(int** A, int** B, int** C, int size)
{
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            C[i][j] = 0;
            for (int k = 0; k < size; ++k)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main()
{
    // Set the starting point for getting random numbers 
    // based on the current time, so we get different random numbers each time we run the program
    srand(time(0));

    int size;
    cout << "Enter the size of the matrix: ";
    cin >> size;

    // Allocate memory for matrices dynamically
    int** A = new int*[size];
    int** B = new int*[size];
    int** C = new int*[size];
    for (int i = 0; i < size; ++i)
    {
        A[i] = new int[size];
        B[i] = new int[size];
        C[i] = new int[size];
    }

    // Initialize matrices A and B with random values
    initializeMatrix(A, size);
    initializeMatrix(B, size);

    // Print matrices A and B
    cout << "Matrix A:" << endl;
    printMatrix(A, size);
    cout << endl;

    cout << "Matrix B:" << endl;
    printMatrix(B, size);
    cout << endl;

    // Write matrices A and B to files
    writeMatrixToFile(A, size, "matrixA.txt");
    writeMatrixToFile(B, size, "matrixB.txt");

    // Start timing matrix multiplication
    clock_t startTime = clock();

    // Perform matrix multiplication
    matrixMultiplication(A, B, C, size);

    // End timing
    clock_t endTime = clock();

    // Calculate execution time in milliseconds
    double executionTime = double(endTime - startTime) / CLOCKS_PER_SEC * 1000;

    // Print the result matrix C
    cout << "Result Matrix C:" << endl;
    printMatrix(C, size);
    cout << endl;

    // Print the execution time
    cout << "Execution time (excluding initialization and writing to file): " << executionTime << " milliseconds" << endl;

    // Write the result matrix C to a file
    writeMatrixToFile(C, size, "matrixC.txt");

    // Deallocate memory for matrices
    for (int i = 0; i < size; ++i)
    {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
    }
    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}