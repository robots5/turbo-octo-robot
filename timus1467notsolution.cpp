#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
const double EPS = 1e-9;
int gauss (vector < vector<double> > a, vector<double> & ans) { // e-maxx.ru/algo Gauss
	int n = (int) a.size();
	int m = (int) a[0].size() - 1;
	vector<int> where (m, -1);
	for (int col=0, row=0; col<m && row<n; ++col) {
		int sel = row;
		for (int i=row; i<n; ++i){
			if (abs (a[i][col]) > abs (a[sel][col]))
				sel = i;
		}
		if (abs (a[sel][col]) < EPS)
			continue;
		for (int i=col; i<=m; ++i){
			swap (a[sel][i], a[row][i]);
		}
		where[col] = row;
 
		for (int i=0; i<n; ++i){
			if (i != row) {
				double c = a[i][col] / a[row][col];
				for (int j=col; j<=m; ++j)
					a[i][j] -= a[row][j] * c;
			}
		}
		++row;
	}
 
	ans.assign (m, 0);
	for (int i=0; i<m; ++i)
		if (where[i] != -1)
			ans[i] = a[where[i]][m] / a[where[i]][i];
	for (int i=0; i<n; ++i) {
		double sum = 0;
		for (int j=0; j<m; ++j)
			sum += ans[j] * a[i][j];
		if (abs (sum - a[i][m]) > EPS)
			return 0;
	}
 
	for (int i=0; i<m; ++i)
		if (where[i] == -1)
			return 0;
	return 1;
}

double P(int k,int n)
{
	double sum = 0;
	for (int i = 1; i <= n; i++)
		sum += pow(double(i),k);
	return sum;
}

int main()
{
	//for timus 1467. Sum of Degrees. This is not full solution, just shown how to apply Gauss
	int k;
	cin >> k;
	int m = k + 2;
	vector<vector<double> > matrix(m,vector<double>(m + 1));
	for (int i = 0; i < m; i++) // b vector
		matrix[i][m] = P(k,i);
	for (int n = 0; n < m; n++) // a matrix
	{
		for (int k = 0; k < m; k++)
		{
			matrix[n][k] = pow(double(n),k);
		}
	}
	vector<double> ans;
	gauss (matrix,ans);
	for (int i = 0; i < ans.size(); i++)
		cout << ans[ans.size() - i - 1] << " ";
	// for first test case, it return 0.5 0.5 0
	// quite right, but we need       1/2 1/2 0/1 
	// so in order to solve this problem need some work:)
	return 0;
}