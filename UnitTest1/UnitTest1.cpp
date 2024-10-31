#include "pch.h"
#include "CppUnitTest.h"
#include <vector>
#include <limits>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

const int INF = numeric_limits<int>::max();
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

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestFloydWarshall)
        {
            // Налаштування графа
            int n = 4;
            vector<vector<int>> dist = {
                {0, 3, INF, 7},
                {8, 0, 2, INF},
                {5, INF, 0, 1},
                {2, INF, INF, 0}
            };

            vector<vector<int>> next(n, vector<int>(n, -1));
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (dist[i][j] != INF) {
                        next[i][j] = j;
                    }
                }
            }


            floydWarshall(dist, next, n);


            Assert::AreEqual(5, dist[1][0]);
            Assert::AreEqual(5, dist[0][2]);
            Assert::AreEqual(3, dist[1][3]);
            Assert::AreEqual(5, dist[3][1]);
        }

        TEST_METHOD(TestPathExists) {

            int n = 4;
            vector<vector<int>> next = {
                {0, 1, -1, -1},
                {0, 1, 2, -1},
                {2, -1, 2, 3},
                {-1, -1, -1, 3}
            };

            Assert::AreEqual(1, next[0][1]);
            Assert::AreEqual(2, next[1][2]);
            Assert::AreEqual(-1, next[0][2]);
        }
    };
}
