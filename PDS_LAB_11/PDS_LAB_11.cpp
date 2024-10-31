#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
using namespace std;

const int INF = numeric_limits<int>::max();

vector<vector<int>> readGraph(const string& filename, int& n) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Не вдалося відкрити файл: " << filename << endl;
        exit(1);
    }

    int m;
    file >> n >> m;
    vector<vector<int>> distanceMatrix(n, vector<int>(n, INF));

    for (int i = 0; i < n; ++i) {
        distanceMatrix[i][i] = 0;
    }

    for (int i = 0; i < m; ++i) {
        int v, u, w;
        file >> v >> u >> w;
        distanceMatrix[v][u] = w;
    }

    file.close();
    return distanceMatrix;
}


void floydWarshall(vector<vector<int>>& dist, vector<vector<int>>& next, int n) {
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}

void printMatrix(const vector<vector<int>>& matrix, const string& outputFile) {
    ofstream outFile(outputFile);
    cout << "Матриця найкоротших відстаней:\n";

    for (const auto& row : matrix) {
        for (int dist : row) {
            if (dist == INF) {
                cout << "INF\t";
                outFile << "INF\t";
            }
            else {
                cout << dist << "\t";
                outFile << dist << "\t";
            }
        }
        cout << endl;
        outFile << endl;
    }

    outFile.close();
}


void getPath(int u, int v, const vector<vector<int>>& next) {
    if (next[u][v] == -1) {
        cout << "Немає шляху від " << u + 1 << " до " << v + 1 << endl;
        return;
    }
    vector<int> path;
    for (int at = u; at != v; at = next[at][v]) {
        if (at == -1) {
            cout << "Немає шляху\n";
            return;
        }
        path.push_back(at);
    }
    path.push_back(v);

    cout << "Шлях від " << u + 1 << " до " << v + 1 << ": ";
    for (int vertex : path) {
        cout << vertex + 1 << " ";
    }
    cout << endl;
}

int main() {
  
    string inputFile, outputFile;
    cout << "Введіть назву вхідного файлу з описом графу: ";
    cin >> inputFile;
    cout << "Введіть назву вихідного файлу для запису матриці відстаней: ";
    cin >> outputFile;

    int n;
    vector<vector<int>> distanceMatrix = readGraph(inputFile, n);
    vector<vector<int>> next(n, vector<int>(n, -1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (distanceMatrix[i][j] != INF) {
                next[i][j] = j;
            }
        }
    }

    floydWarshall(distanceMatrix, next, n);
    printMatrix(distanceMatrix, outputFile);

    int startVertex, endVertex;
    cout << "Введіть початкову вершину: ";
    cin >> startVertex;
    cout << "Введіть кінцеву вершину: ";
    cin >> endVertex;

    if (startVertex < 1 || startVertex > n || endVertex < 1 || endVertex > n) {
        cout << "Неправильний індекс вершини!" << endl;
        return -1;
    }

    getPath(startVertex - 1, endVertex - 1, next);

    return 0;
}
