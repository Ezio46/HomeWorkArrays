#include <iostream>
#include <chrono>
using namespace std;

class SingleArray {
private:
    int* data;
    int size;
    int capacity;

public:

    // Конструктор класса
    SingleArray(const initializer_list<int>& values) {
        size = values.size();
        data = new int[size];
        int i = 0;
        for (int value : values) {
            data[i] = value;
            i++;
        }
    }

    // Деконструктор класса
    ~SingleArray() {
        delete[] data;
    }

    // Перегрузка оператора [] для получения элемента по индексу
    int& operator[](int index) {
        return data[index];
    }

    // Текущий размер массива
    int getSize() {
        return size;
    }

    void insert(int value, int index) {
        if (index < 0 || index > size) {
            throw out_of_range("Invalid index");
        }
        if (size == capacity) {
            capacity *= 2;
            int* newData = new int[capacity];
            for (int i = 0; i < index; i++) {
                newData[i] = data[i];
            }
            newData[index] = value;
            for (int i = index; i < size; i++) {
                newData[i + 1] = data[i];
            }
            delete[] data;
            data = newData;
        } else {
            for (int i = size; i > index; i--) {
                data[i] = data[i - 1];
            }
            data[index] = value;
        }
        size++;
    }

    void remove(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Invalid index");
        }
        for (int i = index; i < size - 1; i++) {
            data[i] = data[i + 1];
        }
        size--;
    }
};

class VectorArray {
private:
    int* data;
    int size;
    int capacity;

public:
    VectorArray() : data(nullptr), size(0), capacity(0) {}

    VectorArray(initializer_list<int> values) : size(values.size()), capacity(values.size()) {
        data = new int[capacity];
        int i = 0;
        for (int value : values) {
            data[i++] = value;
        }
    }

    ~VectorArray() {
        delete[] data;
    }

    int& operator[](int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Invalid index");
        }
        return data[index];
    }

    int getSize() const {
        return size;
    }

    void insert(int value, int index) {
        if (index < 0 || index > size) {
            throw out_of_range("Invalid index");
        }

        if (size == capacity) {
            int newCapacity = (capacity == 0) ? 1 : capacity * 2;
            int* newData = new int[newCapacity];
            for (int i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }

        for (int i = size; i > index; i--) {
            data[i] = data[i - 1];
        }

        data[index] = value;
        size++;
    }

    void remove(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Invalid index");
        }

        for (int i = index; i < size - 1; i++) {
            data[i] = data[i + 1];
        }

        size--;

        if (size < capacity / 2) {
            int newCapacity = capacity / 2;
            int* newData = new int[newCapacity];
            for (int i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }
    }
};

class FactorArray {
private:
    int* data;
    int size;
    int capacity;
    int factor;

public:
    FactorArray(int initialCapacity, int initialFactor) : size(0), capacity(initialCapacity), factor(initialFactor) {
        data = new int[capacity];
    }

    FactorArray(int growthFactor, initializer_list<int> values) : size(values.size()), capacity(values.size()), factor(growthFactor) {
        data = new int[capacity];
        int i = 0;
        for (int value : values) {
            data[i++] = value;
        }
    }

    ~FactorArray() {
        delete[] data;
    }

    int& operator[](int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Invalid index");
        }
        return data[index];
    }

    int getSize() const {
        return size;
    }

    void insert(int value, int index) {
        if (index < 0 || index > size) {
            throw out_of_range("Invalid index");
        }

        if (size == capacity) {
            int newCapacity = capacity * factor;
            int* newData = new int[newCapacity];
            for (int i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }

        for (int i = size; i > index; i--) {
            data[i] = data[i - 1];
        }

        data[index] = value;
        size++;
    }

    void remove(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Invalid index");
        }

        for (int i = index; i < size - 1; i++) {
            data[i] = data[i + 1];
        }

        size--;

        if (size < capacity / factor && capacity > factor) {
            int newCapacity = capacity / factor;
            int* newData = new int[newCapacity];
            for (int i = 0; i < size; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }
    }
};

class MatrixArray {
private:
    int** data;
    int* sizes;
    int capacity;
    int rows;
    int cols;

public:
    MatrixArray(int initialRows, int initialCols)
            : capacity(initialRows * initialCols), rows(initialRows), cols(initialCols) {
        sizes = new int[rows];
        data = new int*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new int[cols];
            sizes[i] = 0;
        }
    }

    ~MatrixArray() {
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
        delete[] sizes;
    }

    int& operator()(int row, int col) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw out_of_range("Invalid index");
        }
        return data[row][col];
    }

    int getRows() const {
        return rows;
    }

    int getCols() const {
        return cols;
    }

    void insert(int value, int row, int col) {
        if (row < 0 || row > rows || col < 0 || col > cols) {
            throw out_of_range("Invalid index");
        }

        if (sizes[row] == cols) {
            if (row >= rows - 1 && sizes[row] == cols) {
                capacity *= 2;
                resizeData();
            }

            for (int i = rows - 1; i > row; i--) {
                sizes[i] = sizes[i - 1];
                data[i] = data[i - 1];
            }

            sizes[row] = 0;
            data[row] = new int[cols];
            rows++;
        }

        for (int i = sizes[row]; i > col; i--) {
            data[row][i] = data[row][i - 1];
        }

        data[row][col] = value;
        sizes[row]++;
    }

    void remove(int row, int col) {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            throw out_of_range("Invalid index");
        }

        for (int i = col; i < sizes[row] - 1; i++) {
            data[row][i] = data[row][i + 1];
        }

        sizes[row]--;
        if (sizes[row] == 0) {
            delete[] data[row];

            for (int i = row; i < rows - 1; i++) {
                sizes[i] = sizes[i + 1];
                data[i] = data[i + 1];
            }

            rows--;
        }
    }

private:
    void resizeData() {
        int** newData = new int*[capacity];
        int* newSizes = new int[capacity / cols];

        for (int i = 0; i < rows; i++) {
            newData[i] = data[i];
            newSizes[i] = sizes[i];
        }

        delete[] data;
        delete[] sizes;
        data = newData;
        sizes = newSizes;
    }
};


int main() {

    // Для SingleArray
    auto start = chrono::high_resolution_clock::now();
    SingleArray singleArr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    singleArr.insert(1000, 4);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "SingleArray insert time: " << duration.count() << " microseconds" << endl;

    start = chrono::high_resolution_clock::now();
    singleArr.remove(4);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "SingleArray remove time: " << duration.count() << " microseconds" << endl;

    // Для VectorArray
    start = chrono::high_resolution_clock::now();
    VectorArray vectorArr = {1, 5, 64, 1, 0, 12, 7, 6, 1, 2, 18, 131, 534, 12, 464, 4321, 5436, 12, 645, 12};;
    vectorArr.insert(1000, 4);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "VectorArray insert time: " << duration.count() << " microseconds" << endl;

    start = chrono::high_resolution_clock::now();
    vectorArr.remove(4);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "VectorArray remove time: " << duration.count() << " microseconds" << endl;

    // Для FactorArray
    start = chrono::high_resolution_clock::now();
    FactorArray factorArr(2, {111, 22231, 34353, 48689, 525, 657, 714, 875, 914, 1074, 1641, 642, 1463, 18674, 1135, 1646, 1775, 11528, 16549, 2130});
    factorArr.insert(1000, 4);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "FactorArray insert time: " << duration.count() << " microseconds" << endl;

    start = chrono::high_resolution_clock::now();
    factorArr.remove(4);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "FactorArray remove time: " << duration.count() << " microseconds" << endl;

    // Для MatrixArray
    start = chrono::high_resolution_clock::now();
    MatrixArray matrixArr(10, 10);
    matrixArr.insert(1000, 2, 2);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "MatrixArray insert time: " << duration.count() << " microseconds" << endl;

    start = chrono::high_resolution_clock::now();
    matrixArr.remove(2, 2);
    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    cout << "MatrixArray remove time: " << duration.count() << " microseconds" << endl;

    return 0;
}
