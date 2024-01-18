#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void dijkstra(const vector<vector<int>> &Matrix, const int rSISE, const int start)
{
    int time = rSISE;
    vector<pair<int, int>> cur(rSISE, pair<int, int>(INT_MAX, -1)); // Bảng độ dài từ start đến các đỉnh hiện tại
    vector<int> isTravel(rSISE, 0); // Đỉnh thứ i đã được xét chưa (thanh dọc bên trái)
    
    int v = start; //đỉnh đang xét
    cur[v] = pair<int, int>(0, v);

    while (time > 0)
    {
        isTravel[v] = 1; // Đánh dấu đỉnh v đã xét
        if (time == 1) break;

        int min = -1;
        for (int i = 0; i < rSISE; i++)
        {
            if (v == i) continue; // trùng đỉnh bỏ qua
            if (isTravel[i]) continue; // đỉnh duyệt rồi bỏ qua

            if (Matrix[v][i] != INT_MAX) // Từ v sang i được
            {
                if (cur[v].first + Matrix[v][i] < cur[i].first)
                {
                    cur[i].first = cur[v].first + Matrix[v][i];
                    cur[i].second = v;
                }
            } 

            if (min == -1)
            {
                min = i;
            }
            else if (cur[i].first < cur[min].first)
            {
                min = i;
            } 
        }

        if (time == 2)
            cout << cur[min].second << "-" << min;
        else
            cout << cur[min].second << "-" << min << ";";
            
        v = min; // lấy đỉnh có hệ số nhỏ nhất làm đỉnh xét tiếp theo
        time--;
    }

}

    
int main()
{
    fstream file("input3.txt");
    if (!file.is_open())
    {
        cerr << "Error opening file." << endl;
        return 1;
    }

    const int MAX_SIZE = 1000;
    vector<vector<int>> Matrix(MAX_SIZE, vector<int>(MAX_SIZE, INT_MAX));

    int rSIZE = 0;
    int vA = -2, vB = -2, w = 0; // các đỉnh bắt đầu từ 0 đến n - 1 (n đỉnh)
    while (vA != -1 && vB != -1)
    {
        file >> vA >> vB >> w;
        if (vA == -1 || vB == -1)
            break;

        if (max(vA, vB) > rSIZE)
            rSIZE = max(vA, vB);

        Matrix[vA][vB] = w;
    }

    rSIZE++; // n đỉnh nên + 1
    dijkstra(Matrix, rSIZE, 0);
}