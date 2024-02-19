#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <omp.h> // Include OpenMP header

using namespace std;

// Function to initialize a matrix with random values
void initializeMatrix(int **matrix, int size)
{
#pragma omp parallel for
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            matrix[i][j] = rand() % 10; // Generate random values between 0 and 9
        }
    }
}

// Function to print a matrix to the console
void printMatrix(int **matrix, int size)
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
void writeMatrixToFile(int **matrix, int size, const char *filename)
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

// Function to perform sequential matrix multiplication with OpenMP parallelization
void openmpSequentialMatrixMultiplication(int **A, int **B, int **C, int size)
{
#pragma omp parallel for collapse(2)
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
    srand(time(0));

    int matrixSize;
    cout << "Enter the size of the matrix: ";
    cin >> matrixSize;

    // Allocate memory for matrices dynamically
    int **inputMatrix1 = new int *[matrixSize];
    int **inputMatrix2 = new int *[matrixSize];
    int **resultMatrixSequentialOpenMP = new int *[matrixSize];
    for (int i = 0; i < matrixSize; ++i)
    {
        inputMatrix1[i] = new int[matrixSize];
        inputMatrix2[i] = new int[matrixSize];
        resultMatrixSequentialOpenMP[i] = new int[matrixSize];
    }

    // Initialize matrices A and B with random values
    initializeMatrix(inputMatrix1, matrixSize);
    initializeMatrix(inputMatrix2, matrixSize);

    // Perform sequential matrix multiplication with OpenMP parallelization
    clock_t openmpSequentialStartTime = clock();
    openmpSequentialMatrixMultiplication(inputMatrix1, inputMatrix2, resultMatrixSequentialOpenMP, matrixSize);
    clock_t openmpSequentialEndTime = clock();
    double openmpSequentialExecutionTime = double(openmpSequentialEndTime - openmpSequentialStartTime) / CLOCKS_PER_SEC * 1000;

    // Print and write result of sequential multiplication with OpenMP...
    cout << "Sequential Result Matrix with OpenMP:" << endl;
    printMatrix(resultMatrixSequentialOpenMP, matrixSize);
    writeMatrixToFile(resultMatrixSequentialOpenMP, matrixSize, "sequential_result_matrix_openmp.txt");
    cout << "Sequential Execution time with OpenMP: " << openmpSequentialExecutionTime << " milliseconds" << endl;

    // Deallocate memory for matrices
    for (int i = 0; i < matrixSize; ++i)
    {
        delete[] inputMatrix1[i];
        delete[] inputMatrix2[i];
        delete[] resultMatrixSequentialOpenMP[i];
    }
    delete[] inputMatrix1;
    delete[] inputMatrix2;
    delete[] resultMatrixSequentialOpenMP;

    return 0;
}
