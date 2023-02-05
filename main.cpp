#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Matrix {
public:

    class Element {
    public:
        Element(float _value)
            : value(_value) { }
        Element(int _col, int _row, float _value)
            : value(_value), col(_col), row(_row) { }

        int col;
        int row;
        float value;
    };

    Matrix(int _cols, int _rows)
    : rows(_rows), cols(_cols) {
        for (int i = 0; i < cols; i++) { matrix.push_back(vector<float>(rows)); }
    }

    Matrix(int _cols, int _rows, string path) : Matrix(_cols, _rows) {
        scanFromFile(path);
    }

    ~Matrix() {}

    void  setElement(Element el) {
        if (isIndexesOk(el)) { matrix[el.col][el.row] = el.value; }
    }
    float getElement(Element el) {
        if (isIndexesOk(el)) { return matrix[el.col][el.row]; }
    }

    int getCols() { return cols; }
    int getRows() { return rows; }

    float calcSquareSum(int vSize, int hSize, Element centralEl) {
        float sum = 0;
        for (int i = centralEl.row - vSize/2; i <= centralEl.row + vSize/2;) {
            sum += calcRowSum(vSize, hSize, matrix[centralEl.col][i]);
        }
        return sum;
    }

    void scanFromFile(string path) {
        fstream fb(path);
        if (fb.is_open()) {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    fb << matrix[i][j];
                }
            }
        }
    }

    void print() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << matrix[i][j] << " ";
            }
        }
        cout << endl;
    }

private:
    float calcRowSum(int vSize, int hSize, Element centralEl) {
        if (!isIndexesOk(centralEl)) { return -1; }
        if (!isFrameOk(vSize, hSize, centralEl)) { return -1; }

        float sum = 0;
        for (int i = centralEl.col - hSize/2; i <= centralEl.col + hSize/2; i++) {
            sum += matrix[i][centralEl.row];
        }
        return sum;
    }

    float calcColSum(int vSize, int hSize, Element centralEl) {
        if (!isIndexesOk(centralEl)) { return -1; }
        if (!isFrameOk(vSize, hSize, centralEl)) { return -1; }

        float sum = 0;
        for (int i = centralEl.row - vSize/2; i <= centralEl.row + vSize/2; i++) {
            sum += matrix[centralEl.col][i];
        }
        return sum;
    }

    bool isFrameOk(int vSize, int hSize, Element centralEl) {
        if (centralEl.row - vSize /2 < 0)       { return false; }
        if (centralEl.row + vSize /2 >= rows)   { return false; }
        if (centralEl.col - hSize /2 < 0)       { return false; }
        if (centralEl.col + hSize /2 >= cols)   { return false; }
        return true;
    }

    bool isIndexesOk(Element el) {
        if (el.col < cols && el.row < rows) { return true; }
        else { return false; }
    }

    int cols, rows;
    vector<vector<float>> matrix;

};

int main() {
    std::cout << "Hello, Vector!" << std::endl;
    int i = 9;


    return 0;
}


void generateMatrix() {
    float arr[] = {
            10.1,10.1, 10.1, 10.1, 10.1,
            10.1,10.1, 10.1,10.1, 10.1,
            10.1,10.1,10.1,10.1,10.1,
            10.1,10.1,10.1,10.1,10.1,
            10.1,10.1,10.1,10.1,10.1,
            10.1,10.1,10.1,10.1,10.1,
            10.1,10.1,10.1,10.1,10.1,
            10.1,10.1,10.1,10.1,10.1,
            10.1,10.1,10.1,10.1,10.1,
            10.1,10.1,10.1,10.1,10.1,
    };

    ofstream fb("data.bin");
    if (!fb.is_open()) { cerr << "Error while opening file"; }

    for (const auto el : arr) {
        fb << el;
    }

    fb.close();
}