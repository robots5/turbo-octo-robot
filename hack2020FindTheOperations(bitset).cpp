#include <iostream>
#include <vector>
#include <string>         // std::string
#include <bitset>         // std::bitset
using namespace std;
const int N = 401;
int gauss (vector < bitset<N> > a, int n, int m, bitset<N> & ans) {
	 for (int i = 0; i < n; i++) {
        int row = -1;
        for (int j = i; j < n; j++)
            if (a[j][i]) {
                row = j;
                break;
            }
        if (row == -1) continue;
        if (!a[i][i])
			a[i] ^= a[row];
        for (int k = i; k < n; k++)
			if (k != i && a[k][i] == 1)
				a[k] ^= a[i];
    }
	for (int i = 0; i < n; i++)
        if (a[i][n]) {
            int ok = 0;
            for (int j = 0; j < n; j++)
                if (a[i][j]) {
                    ok = 1;
                    break;
                }
            if (!ok) return 0;
        }

    for (int i = n - 1; i >= 0; i--) 
	{
       if (a[i][i] == 0 && a[i][n] == 1) 
		   return 0;
	ans[i] = a[i][n];

	if (ans[i]){
		for (int j = i - 1; j >= 0; j--)
				a[j][n] = a[j][n] ^ a[j][i];
	}
    }

    return 1;
}

int main()
{
	//freopen ("input.txt","r",stdin);
	int n,d;
	cin >> n >> d;
	vector<bitset<N> > A(n * n);
	//cout << A[0];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int row = i * n + j;
			bool v;
			cin >> v;
			A[row][n * n] = v; // b - vector added to a matrix end column

			//mantheton distance
			for (int x = 0; x < n; x++)
			{
				for (int y = 0; y < n; y++)
				{
					if (abs(x - i) + abs(y - j) <= d)
					{
						A[row][x * n + y] = true;
					}
				}
			}
		}
	}

	bitset<N> ans;
	int res = gauss (A,n * n,n * n,ans);
	if (!res) cout << "Impossible" << endl;
	else {
		cout << "Possible" << endl;
		int cnt = 0;
		for (int i = 0; i < n * n; i++)
			cnt += ans[i];
		cout << cnt << endl;

		for (int i = 0; i < n * n; i++)
			if (ans[i]) cout << i / n << " " << i % n << endl;
	}
	return 0;
}