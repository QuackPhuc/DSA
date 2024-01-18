#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

void bfs(const vector<vector<int>> &Matrix, const int rSIZE, const int start)
{
	vector<int> isTravel(rSIZE, 0); // Mảng xem đỉnh i đã duyệt chưa, isTravel[i] = 1, i đã duyệt

	queue<int> graph;
	graph.push(start);
	isTravel[start] = 1; // Các đỉnh nhập theo thứ tự từ 0 đến n - 1

	while (!graph.empty())
	{
		int v = graph.front(); // vetex - đỉnh đang xét
		isTravel[v] = 1;
		graph.pop();

		if (v == start)
			cout << v;
		else
			cout << " " << v;

		for (int i = 0; i < rSIZE; i++)
		{
			if (Matrix[v][i] != 0 && isTravel[i] == 0)
			{
				graph.push(i);
				isTravel[i] = 1;
			}
		}
	}
	cout << "\n";
}

int main()
{
	vector<vector<int>> Matrix = { {0, 4, 0, 0, 0, 0, 0, 8, 0},
								   {4, 0, 8, 0, 0, 0, 0, 11, 0},
								   {0, 8, 0, 0, 0, 0, 0, 0, 2},
								   {0, 0, 0, 0, 9, 14, 0, 0, 0},
								   {0, 0, 0, 9, 0, 10, 0, 0, 0},
								   {0, 0, 0, 14, 10, 0, 2, 0, 0},
								   {0, 0, 0, 0, 0, 2, 0, 1, 0},
								   {8, 11, 0, 0, 0, 0, 1, 0, 7},
								   {0, 0, 2, 0, 0, 0, 0, 7, 0} };
	int size = Matrix.size();
	int start = 0;
	bfs(Matrix, size, start);
} 