#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class Matrix {
private:
    int size;
    std::vector<std::vector<int>> data;

public:
    // Constructor to initialize a square matrix of given size
    Matrix(int n = 0) : size(n), data(n, std::vector<int>(n, 0)) {}

    // Function to load matrix data from a file
    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            file >> size; // assuming the first value is the size of the matrix
            data.resize(size, std::vector<int>(size, 0));
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    file >> data[i][j];
                }
            }
            file.close();
        } else {
            std::cerr << "Error: Unable to open file.\n";
        }
    }

    // Function to display the matrix in a user-friendly format
    void display() const {
        for (const auto& row : data) {
            for (int val : row) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
        }
    }

    // Operator overloading for matrix addition
    Matrix operator+(const Matrix& other) const {
        if (size != other.size) {
            std::cerr << "Error: Matrices must be the same size for addition.\n";
            return Matrix(); // Return an empty matrix
        }

        Matrix result(size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                result.data[i][j] = this->data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // Operator overloading for matrix multiplication
    Matrix operator*(const Matrix& other) const {
        if (size != other.size) {
            std::cerr << "Error: Matrices must be the same size for multiplication.\n";
            return Matrix(); // Return an empty matrix
        }

        Matrix result(size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                result.data[i][j] = 0;
                for (int k = 0; k < size; ++k) {
                    result.data[i][j] += this->data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    // Function to calculate the sum of the main and secondary diagonals
    int sumDiagonals() const {
        int mainDiagonal = 0, secondaryDiagonal = 0;
        for (int i = 0; i < size; ++i) {
            mainDiagonal += data[i][i];
            secondaryDiagonal += data[i][size - 1 - i];
        }
        return mainDiagonal + secondaryDiagonal;
    }

    // Function to swap two rows in the matrix
    void swapRows(int row1, int row2) {
        if (row1 >= 0 && row1 < size && row2 >= 0 && row2 < size) {
            std::swap(data[row1], data[row2]);
        } else {
            std::cerr << "Error: Row indices out of bounds.\n";
        }
    }
};

// Main function to demonstrate usage
int main() {
    Matrix matrixA, matrixB;

    // Load matrices from files
    matrixA.loadFromFile("matrix_input.txt");
    matrixB.loadFromFile("matrix_input.txt"); // Assuming we load same file for demonstration

    std::cout << "Matrix A:\n";
    matrixA.display();

    std::cout << "Matrix B:\n";
    matrixB.display();

    // Matrix addition
    Matrix sumMatrix = matrixA + matrixB;
    std::cout << "\nSum of Matrix A and Matrix B:\n";
    sumMatrix.display();

    // Matrix multiplication
    Matrix productMatrix = matrixA * matrixB;
    std::cout << "\nProduct of Matrix A and Matrix B:\n";
    productMatrix.display();

    // Sum of diagonals
    int diagonalSum = matrixA.sumDiagonals();
    std::cout << "\nSum of main and secondary diagonals of Matrix A: " << diagonalSum << std::endl;

    // Swap rows
    matrixA.swapRows(0, 1);
    std::cout << "\nMatrix A after swapping rows 0 and 1:\n";
    matrixA.display();

    return 0;
}
