#include <iostream>
#include <fstream>
#include <vector>

int** createArr(int x, int y);
void printArr(int **arr, int x, int y);
void findSpots(int **arr, int x, int y);
void dsf(int **arr, int x, int y, int x_size, int y_size, const std::vector<std::pair<int, int>>& coordinates, int counter);
std::vector<std::pair<int, int>> makeCardinalPoints();

int main() {
    std::ifstream inputFile("../tests/test3.txt");

    if (!inputFile.is_open()) {
        std::cerr << "Could not open the file." << std::endl;
        return 1;
    }

    // Save the original cin buffer and redirect to the input file
    std::streambuf* origCinBuffer = std::cin.rdbuf();
    std::cin.rdbuf(inputFile.rdbuf());

    int x_size, y_size;
    std::cin >> x_size >> y_size;
    int **arr = createArr(x_size, y_size);
    printArr(arr, x_size, y_size);

    std::vector<std::pair<int, int>> cardPairs = makeCardinalPoints();

    int ctr = 0;

    for (int i = 0; i < y_size; ++i) {
        for (int j = 0; j < x_size; ++j) {
            if (arr[i][j] == 1){
                ctr--;
                dsf(arr, i, j, x_size, y_size, cardPairs, ctr);
            }
        }
    }

    printArr(arr, x_size, y_size);

    std::cout << abs(ctr);


    // Restore the original cin buffer
    std::cin.rdbuf(origCinBuffer);

    inputFile.close();

    return 0;
}

int** createArr(int x, int y){
    int **arr = new int *[y];
    for (int i = 0; i < y; ++i) {
        arr[i] = new int [x];
        for (int j = 0; j < x; ++j) {
            int el;
            std::cin >> el;
            arr[i][j] = el;
        }
    }

    return arr;
}

void printArr(int **arr, int x, int y){
    for (int i = 0; i < y; ++i) {
        for (int j = 0; j < x; ++j) {
            std::cout << arr[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void dsf(int **arr, int x, int y, int x_size, int y_size, const std::vector<std::pair<int, int>>& coordinates, int counter) {
    arr[x][y] = counter;
    for (auto c: coordinates) {
        int new_x = x + c.first;
        int new_y = y + c.second;
        if (new_x >= 0 && new_x < x_size && new_y >= 0 && new_y < y_size && arr[new_x][new_y] == 1) {
//            printArr(arr, x_size, y_size);
            dsf(arr, new_x, new_y, x_size, y_size, coordinates, counter);
        }
    }
}

std::vector<std::pair<int, int>> makeCardinalPoints() {

    std::vector<std::pair<int, int>> cardPoints;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i != 0 || j != 0)
                cardPoints.emplace_back(i, j);
        }
    }
    return cardPoints;
}




