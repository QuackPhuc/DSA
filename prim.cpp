#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void prim(const vector<vector<int>> &Matrix, const int rSIZE, bool max)
{
	int start = 0;
	vector<int> isTravel(rSIZE, 0); // mảng xét isTravel các đỉnh đã duyệt

	isTravel[start] = 1;
	int time = rSIZE - 1;
	int weight = 0; // trọng số

	cout << "Khung: " << 0;
	while (time > 0)
	{
		int m = (max) ? INT_MIN : INT_MAX; // Nếu duyệt MaxST thì biến tạm m = INT_MIN
		int v = -1, vs = -1; // đỉnh tạm
		
		if (time == 0) break;

		for (int i = 0; i < (int) isTravel.size(); i++)
		{
			if (!isTravel[i]) continue; // Chọn đỉnh trước là các đỉnh chưa xét

			for (int j = 0; j < rSIZE; j++) // Đỉnh sau là các đỉnh chưa xét
			{
				if (isTravel[j]) continue; // Đã duyệt không xét
				if (i == j) continue;// trùng đỉnh không xét
				if (max) // M'ST
				{
					if (Matrix[i][j] > m && Matrix[i][j] != 0) //M[i][j] = 0 => ko có cạnh nối i, j với i != j
					{
						m = Matrix[i][j];
						v = j;
						vs = i;
					}
				}
				else //MST
				{
					if (m > Matrix[i][j] && Matrix[i][j] != 0)
					{
						m = Matrix[i][j];
						v = j;
						vs = i;
					}
				}
			}
		}

		isTravel[v] = 1;
		weight += m;
		time--;
		cout << ", " << v << ", " << vs << "-" << v; 
	}
	cout << "\n" << "Trọng số: " << weight << "\n";
}

int main()
{
	fstream file("input2.txt");

	const int MAX_SIZE = 1000;
	vector<vector<int>> Matrix(MAX_SIZE, vector<int>(MAX_SIZE, 0));

	int rSIZE = 0;
	int vA = -2, vB = -2, w;
	while (vA != -1 && vB != -1)
	{
		file >> vA >> vB >> w;
		if (vA == -1 || vB == -1) break;
		
		if (max(vA, vB) > rSIZE)
			rSIZE = max(vA, vB);
		
		Matrix[vA][vB] = w;
		Matrix[vB][vA] = w;
	}

	rSIZE++;
		
	prim(Matrix, rSIZE, 1); // 0: minimum spaning tree, 1 maximum
} 