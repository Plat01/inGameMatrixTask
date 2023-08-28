#include <iostream>
#include <fstream>
#include <vector>

class DFSProcessor {
private:
    using Matrix = std::vector<std::vector<int>>;
    using Coordinate = std::pair<int, int>;

    Matrix mat;
    std::vector<Coordinate> neighbors;
    int ctr = 0;

    void dfs(int x, int y, int label) {
        mat[x][y] = label;
        for (const auto& neighbor : neighbors) {
            int new_x = x + neighbor.first;
            int new_y = y + neighbor.second;
            if (new_x >= 0 && new_x < mat.size() && new_y >= 0 && new_y < mat[0].size() && mat[new_x][new_y] == 1) {
                dfs(new_x, new_y, label);
            }
        }
    }

    std::vector<Coordinate> generateNeighborCoordinates() {
        std::vector<Coordinate> neighbors;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i != 0 || j != 0)
                    neighbors.emplace_back(i, j);
            }
        }
        return neighbors;
    }

public:
    DFSProcessor(int rows, int cols) : mat(rows, std::vector<int>(cols)), neighbors(generateNeighborCoordinates()) {}

    void loadMatrixFromStream(std::ifstream& inputFile) {
        for (auto & i : mat) {
            for (int & j : i) {
                inputFile >> j;
            }
        }
    }

    void processDFS() {
        for (int i = 0; i < mat.size(); ++i) {
            for (int j = 0; j < mat[0].size(); ++j) {
                if (mat[i][j] == 1) {
                    this->ctr--;
                    dfs(i, j, ctr);
                }
            }
        }
    }

    void printMatrix() {
        for (const auto& row : mat) {
            for (const auto& elem : row) {
                std::cout << elem << "\t";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void getCtr(){
        std::cout << abs(ctr) << std::endl;
    }
};

int main() {
    std::ifstream inputFile("../tests/test3.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Could not open the file." << std::endl;
        return 1;
    }

    int rows, cols;
    inputFile >> rows >> cols;

    DFSProcessor processor(rows, cols);
    processor.loadMatrixFromStream(inputFile);
    processor.printMatrix();
    processor.processDFS();
    processor.printMatrix();
    processor.getCtr();

    inputFile.close();
    return 0;
}




