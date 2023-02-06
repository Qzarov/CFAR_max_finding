#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

void generateMatrix();
bool isTresholdExceeding( float sb, float ss, float th, float v);

class Matrix {
public:

    class Element {
    public:
        //explicit Element(float _value)
        //    : value(_value), col(0), row(0) { }

        Element(int _col, int _row)
            : value(0), col(_col), row(_row) { }

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

    Matrix(int _cols, int _rows, const string& path)
        : Matrix(_cols, _rows) {
        cout << "source path: " << path << endl;
        scanFromFile(path);
    }

    ~Matrix() = default;

    void  setElement(Element el) {
        if (isIndexesOk(el)) { matrix[el.col][el.row] = el.value; }
        else { cerr << "Index isn't OK (setElement)\n"; }
    }
    float getElement(int _col, int _row) const {
        Element el(_col, _row);
        if (isIndexesOk(el)) { return matrix[el.col][el.row]; }
        else {
            cerr << "Index isn't OK (getElement)\n";
            return el.value;
        }
    }

    float calcRectangleSum(int vSize, int hSize, Element centralEl) const {
        float sum = 0;
        if (!isFrameOk(vSize, hSize, centralEl)) {
            cerr << "Frame isn't OK (calcRectangleSum)\n";
            return sum;
        }

        for (int i = centralEl.row - vSize/2; i <= centralEl.row + vSize/2; i++) {
            Element el(centralEl.col, i, centralEl.value);
            sum += calcRowSum(vSize, hSize, el);
        }
        return sum;
    }

    void scanFromFile(const string& path) {
        fstream fb(path);
        if (fb.is_open()) {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    fb >> matrix[i][j];
                }
            }
        } else {
            cerr << "Path isn't OK (scanFromFile)\n";
        }
    }

    void print() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

private:
    float calcRowSum(const int vSize, const int hSize, const Element& centralEl) const {
        if (!isIndexesOk(centralEl)) {
            cerr << "Index isn't OK (calcRowSum)\n";
            return 0;
        }
        if (!isFrameOk(vSize, hSize, centralEl)) {
            cerr << "Frame isn't OK (calcRowSum)\n";
            return 0;
        }

        float sum = 0;
        for (int i = centralEl.col - hSize/2; i <= centralEl.col + hSize/2; i++) {
            sum += matrix[i][centralEl.row];
        }
        return sum;
    }

    float calcColSum(const int vSize, const int hSize, const Element& centralEl) const {
        if (!isIndexesOk(centralEl)) {
            cerr << "Index isn't OK (calcColSum)\n";
            return 0;
        }
        if (!isFrameOk(vSize, hSize, centralEl)) {
            cerr << "Frame isn't OK (calcColSum)\n";
            return 0;
        }

        float sum = 0;
        for (int i = centralEl.row - vSize/2; i <= centralEl.row + vSize/2; i++) {
            sum += matrix[centralEl.col][i];
        }
        return sum;
    }

    bool isFrameOk(const int vSize, const int hSize, const Element& centralEl) const {
        if (centralEl.row - vSize / 2 < 0)       { return false; }
        if (centralEl.row + vSize / 2 >= rows)   { return false; }
        if (centralEl.col - hSize / 2 < 0)       { return false; }
        if (centralEl.col + hSize / 2 >= cols)   { return false; }
        return true;
    }

    bool isIndexesOk(const Element& el) const {
        if (el.col < cols && el.row < rows) { return true; }
        else { return false; }
    }

    int cols, rows;
    vector<vector<float>> matrix;

};

int main() {
    std::cout << "Hello, Vector!" << std::endl;

    int x, y;
    cout << "Enter X and Y: ";
    cin >> x, y;

    int xb, yb, xs, ys;
    cout << "Enter Xb and Yb: ";
    cin >> xb >> yb;
    cout << "Enter Xs and Ys: ";
    cin >> xs >> ys;

    const float err = 0.01;
    int sq = xb * yb - xs * ys;
    float th = pow((1 / err), (1 / sq));

    string path;
    cout << "Enter path to file: ";
    cin >> path;
    Matrix matrix(x, y, path);

    Matrix sb(x, y), ss(x, y);
    cout << "Exceeding points (value, row, column)";
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            Matrix::Element el(j, i);
            el.value = matrix.getElement(j, i);
            Matrix::Element elSb(j, i, matrix.calcRectangleSum(yb, xb, el));
            sb.setElement(elSb);
            Matrix::Element elSs(j, i, matrix.calcRectangleSum(ys, xs, el));
            sb.setElement(elSs);

            if (abs(elSb.value) < 0.001 || abs(elSs.value) < 0.001) {
                continue;
            }

            if (isTresholdExceeding(elSb.value, elSs.value, th, el.value)) {
                cout << "exceed: " << el.value << " " << el.row << " " << el.col << "\n";
            }
        }
    }

    return 0;
}

bool isTresholdExceeding(const float sb, const float ss,
                         const float th, const float v) {
    return (sb - ss) * th < v;
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

    ofstream fb("data.txt");
    if (!fb.is_open()) { cerr << "Error while opening file"; }

    for (const auto el : arr) {
        fb << el << " ";
    }

    fb.close();
}