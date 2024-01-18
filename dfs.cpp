
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

void dfs(const vector<vector<int>> &Matrix,const int rSIZE, const int &start)
{
	vector<int> isTravel(rSIZE, 0);

	stack<int> graph;
	graph.push(start);
	isTravel[start] = 1;

	while (!graph.empty())
	{
		int v = graph.top();
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
	/*
	fstream file("input.txt");
	if (!file.is_open())
	{
		cerr << "Error opening file." << endl;
		return 1;
	}

	const int MAX_SIZE = 1000;
	vector<vector<int>> Matrix(MAX_SIZE, vector<int>(MAX_SIZE, 0));

	int start;
	file >> start;
	
	int rSIZE = 0;
	int a = -2, b = -2;
	while (a != -1 && b != -1)
	{
		file >> a >> b;
		if (a == -1 || b == -1) break;
		
		if (max(a, b) > rSIZE)
			rSIZE = max(a, b);
		
		Matrix[a][b] = 1;
		Matrix[b][a] = 1;
	}
	rSIZE++; 

	*/


	// Đọc từ ma trận kề
	const int MAX_SIZE = 1000;
	vector<vector<int>> Matrix(MAX_SIZE, vector<int>(MAX_SIZE, 0));
	int rSIZE, start = 0;

	fstream file1("input4.txt");
	file1 >> rSIZE;
	for (int i = 0; i < rSIZE; i++)
		for (int j = 0; j < rSIZE; j++)
			file1 >> Matrix[i][j];

	

	dfs(Matrix, rSIZE, start);
} 