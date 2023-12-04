#include "../helper.hpp"

vector<vector<char>> getMatrix(const vector<string>& input, const int dim, const char blank) {
    vector matrix(dim, vector(dim, ' '));
    for (int r = 0; r < dim; ++r) {
        for (int c = 0; c < dim; ++c) {
            if (input[r].at(c) == '.') matrix[r][c] = blank;
            else matrix[r][c] = input[r].at(c);
        }
    }
    return matrix;
}

template<typename T>
void printMatrix(const vector<vector<T>>& matrix) {
    const int dim = static_cast<int>(matrix.size());

    cout << "\t\t";
    for (int c = 0; c < dim; ++c)
        cout << c << "\t";
    cout << "\n\n";

    for (int r = 0; r < dim; ++r) {
        cout << r << "\t";
        for (int c = 0; c < dim; ++c) {
            cout << "\t" << matrix[r][c] << "";
        }
        cout << "\n";
    }
}

/// https://stackoverflow.com/questions/1489830/efficient-way-to-determine-number-of-digits-in-an-integer
int numDigits(int n) {
    n = abs(n);
    return (n < 10 ? 1 :
        (n < 100 ? 2 :
        (n < 1000 ? 3 :
        (n < 10000 ? 4 :
        (n < 100000 ? 5 :
        (n < 1000000 ? 6 :
        (n < 10000000 ? 7 :
        (n < 100000000 ? 8 :
        (n < 1000000000 ? 9 : 10)))))))));
}

bool checkRowNumber(const int n, const int row, const int col, const int dim, const vector<vector<char>>& matrix,
                    const char blank,
                    vector<vector<int>>& gears) {
    const int digits = numDigits(n);
    const int startCol = col - digits - 1 >= 0 ? col - digits - 1 : 0;
    const int startRow = row - 1 >= 0 ? row - 1 : 0;
    const int endRow = row + 1 < dim ? row + 1 : dim - 1;
    const int endCol = col <= dim - 1 ? col : dim - 1;
    for (int r = startRow; r <= endRow; ++r) {
        for (int c = startCol; c <= endCol; ++c) {
            if (!isdigit((matrix[r][c])) && matrix[r][c] != blank) {
                if (matrix[r][c] == '*') {
                    if (gears[r][c] == 0) gears[r][c] = -n;
                    else gears[r][c] *= -n;
                }
                return true;
            }
        }
    }
    return false;
}

int getRowNumbers(const vector<char>& row, const int r, const int dim, const vector<vector<char>>& matrix,
                  const char blank,
                  vector<vector<int>>& gears) {
    int total = 0;
    stringstream stream;

    for (int c = 0; c < dim; ++c) {
        if (isdigit(row[c])) stream << row[c];
        if (!isdigit(row[c]) || c == dim - 1) {
            if (!stream.str().empty()) {
                int const n = stoi(stream.str());
                if (isdigit(row[c]) && c == dim - 1) c++ /* Woohoo, c++ */;
                if (checkRowNumber(n, r, c, dim, matrix, blank, gears)) {
                    total += n;
                }
            }
            stringstream().swap(stream); // clears the stream, i.e. deletes buffer and resets error state
        }
    }
    return total;
}

void part2(const vector<string>& input, const int lineCount, const vector<vector<int>>& gears) {
    constexpr char blank = ' ';
    vector<vector<char>> matrix = getMatrix(input, lineCount, blank);
    // printMatrix(gears);
    int sum = 0;
    for (const vector<int>& r: gears) {
        for (int const n: r) {
            sum += n > 0 ? n : 0;
        }
    }
    cout << sum << "\n";
}

void part1(const vector<string>& input, const int lineCount, vector<vector<int>>& gears) {
    constexpr char blank = ' ';
    const vector<vector<char>> matrix = getMatrix(input, lineCount, blank);
    int total = 0;
    for (int row = 0; row < lineCount; ++row) {
        total += getRowNumbers(matrix[row], row, lineCount, matrix, blank, gears);
    }
    // printMatrix(matrix);
    cout << total << "\n";
}

int main() {
    auto const filename = "input03";
    auto const lineCount = getLineCount(filename);
    auto const input = getInput(filename, lineCount);
    auto gears(vector(lineCount, vector(lineCount, 0)));

    auto t1 = Clock::now();
    part1(input, lineCount, gears); // 535078
    auto t2 = Clock::now();
    cout << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << " μs\n";

    t1 = Clock::now();
    part2(input, lineCount, gears); // 75312571
    t2 = Clock::now();
    cout << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << " μs\n";
}
