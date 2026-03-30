#include <iostream>
#include <iomanip>
using namespace std;

void inputMatrix(int rows, int cols, double** matrix) {
    cout << "Enter elements of the matrix:\n";
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            cin >> matrix[i][j];
}
void printMatrix(int rows, int cols, double** matrix) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j)
            cout << matrix[i][j] << " ";
        cout << "\n";
    }
}
double** addMatrix(int r1, int c1, double** A, int r2, int c2, double** B) {
    if (r1 != r2 || c1 != c2) {
        cerr << "Error: Matrices must have same dimensions for addition.\n";
        return nullptr;
    }
    double** result = new double*[r1];
    for (int i = 0; i < r1; ++i) result[i] = new double[c1];
    for (int i = 0; i < r1; ++i)
        for (int j = 0; j < c1; ++j)
            result[i][j] = A[i][j] + B[i][j];
    return result;
}
double** subtractMatrix(int r1, int c1, double** A, int r2, int c2, double** B) {
    if (r1 != r2 || c1 != c2) {
        cerr << "Error: Matrices must have same dimensions for subtraction.\n";
        return nullptr;
    }
    double** result = new double*[r1];
    for (int i = 0; i < r1; ++i) result[i] = new double[c1];
    for (int i = 0; i < r1; ++i)
        for (int j = 0; j < c1; ++j)
            result[i][j] = A[i][j] - B[i][j];
    return result;
}
double** multiplyMatrix(int r1, int c1, double** A, int r2, int c2, double** B) {
    if (c1 != r2) {
        cerr << "Error: Incompatible dimensions for multiplication.\n";
        return nullptr;
    }
    double** result = new double*[r1];
    for (int i = 0; i < r1; ++i) result[i] = new double[c2];
    for (int i = 0; i < r1; ++i)
        for (int j = 0; j < c2; ++j)
            for (int k = 0; k < c1; ++k)
                result[i][j] += A[i][k] * B[k][j];
    return result;
}
void freeMatrix(int rows, double** matrix) {
    for (int i = 0; i < rows; ++i) delete[] matrix[i];
    delete[] matrix;
}

int main() {
    int r1, c1, r2, c2;
    double** A, ** B, ** result;

    cout << "Enter number of rows for matrix 1: "; cin >> r1;
    cout << "Enter number of columns for matrix 1: "; cin >> c1;
    A = new double*[r1];
    for (int i = 0; i < r1; ++i) A[i] = new double[c1];
    inputMatrix(r1, c1, A);

    cout << "Enter number of rows for matrix 2: "; cin >> r2;
    cout << "Enter number of columns for matrix 2: "; cin >> c2;
    B = new double*[r2];
    for (int i = 0; i < r2; ++i) B[i] = new double[c2];
    inputMatrix(r2, c2, B);

    char op;
    cout << "Enter operator (+, -, *): ";
    cin >> op;

    switch (op) {
        case '+':
            result = addMatrix(r1, c1, A, r2, c2, B);
            break;
        case '-':
            result = subtractMatrix(r1, c1, A, r2, c2, B);
            break;
        case '*':
            result = multiplyMatrix(r1, c1, A, r2, c2, B);
            break;
        default:
            cerr << "Invalid operator.\n";
            return 1;
    }
    if (result) {
        cout << "Resulting matrix:\n";
        printMatrix(r1, c2, result);
    }
    freeMatrix(r1, A);
    freeMatrix(r2, B);
    if (result) freeMatrix(r1, result);

    return 0;
}
