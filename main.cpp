#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Matrix {
public:

    class Element {
    public:
        int col;
        int row;
        float value;
    };

    Matrix(int x, int y)
    : rows(y)
    , cols(x) {
        for (int i = 0; i < cols; i++) { matrix.push_back(vector<float>(rows)); }
    }

    ~Matrix() {}

    void setElement(Element el) {
        if (isIndexesOk(el)) { matrix[el.col][el.row] = el.value; }
    }

    float getElement(Element el) {
        if (isIndexesOk(el)) { return matrix[el.col][el.row]; }
    }

    float calcRowSum(int vSize, int hSize, Element centralEl) {
        if (!isIndexesOk(centralEl)) { return -1; }
        if (!isFrameOk(vSize, hSize, centralEl)) { return -1; }

        float sum = 0;
        for (int i = centralEl.col - hSize/2; i < centralEl.col + hSize/2; i++) {
            sum += matrix[i][centralEl.row];
        }
        return sum;
    }

    float calcColSum(int vSize, int hSize, Element centralEl) {
        if (!isIndexesOk(centralEl)) { return -1; }
        if (!isFrameOk(vSize, hSize, centralEl)) { return -1; }

        float sum = 0;
        for (int i = centralEl.row - vSize/2; i < centralEl.row + vSize/2; i++) {
            sum += matrix[centralEl.col][i];
        }
        return sum;
    }

    int getCols() { return cols; }
    int getRows() { return rows; }

private:
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
    std::cout << "Hello, World!" << std::endl;
    return 0;
}


void generateMatrix() {
    float arr[] = {
            35.34, 35.52, 54.34, 45.34, 35.34, 76.34, 34.34, 67.34,35.34, 67.34, 87.23, 19.33,
            35.34, 43.52, 37.34, 32.34, 68.34, 34.34, 23.34, 43.34,15.34, 86.34, 67.23, 76.33,
            561.11, 385.55, 564.22, 485.43, 67.67, 67.80, 32.34, 32.34,43.34, 65.34, 87.23, 54.33,
            561.11, 385.55, 564.22, 485.43, 67.67, 67.80, 32.34, 32.34,43.34, 65.34, 87.23, 54.33,
            76.3, 99.2, 106.5
    };

    ofstream fb("data.bin");
    if (!fb.is_open()) { cerr << "Error while opening file"; }

    for (const auto el : arr) {
        fb << el;
    }

    fb.close();
}