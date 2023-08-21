#include <bits/stdc++.h>
using namespace std;
// 6 6
// xxxooo
// ooxooo
// oxxxxo
// ooooox
// xxoxox
// xoxxox
int n, m;
char a[1001][1001];
bool visited[1001][1001];

int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};

void dfs(int i, int j)
{
    cout << i << " " << j << endl;
    a[i][j] = 'o';
    // duyệt tất cả các đỉnh
    for (int k = 0; k < 4; k++)
    {
        int i1 = i + dx[k];
        int j1 = j + dy[k];
        if (i1 >= 1 && i1 <= n && j1 >= 1 && j1 <= n && a[i1][j1] == 'x')
            dfs(i1, j1);
    }
}

void bfs(int i, int j)
{
    vector<pair<int, int>> q;
    q.push_back({i, j});
    a[i][j] = 'o';
    while (!q.empty())
    {
        pair<int, int> top = q.front();
        q.pop_back();
        // duyệt tất cả các đỉnh
        for (int k = 0; k < 4; k++)
        {
            int i1 = top.first + dx[k];
            int j1 = top.second+ dy[k];
            if (i1 >= 1 && i1 <= n && j1 >= 1 && j1 <= n && a[i1][j1] == 'x')
            {
                cout << i1 << " " << j1 << endl;
                q.push_back({i1, j1});
                a[i1][j1] = 'o';
            }
        }
    }
}
void input()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            cin >> a[i][j];
    }
    // memset(visited, false, sizeof(visited));
    int cnt = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (a[i][j] == 'x')
            {
                cout << "Thanh phan lien thong :" << cnt + 1 << " :" << endl;
                bfs(i, j);
                ++cnt;
            }
        }
    }
    cout << cnt << endl;
}
int main()
{
    input();
    return 0;
}
