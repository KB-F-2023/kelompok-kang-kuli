#include <bits/stdc++.h>
using namespace std;
#define mp make_pair
#define fr front
#define fi first
#define sc second
#define endl '\n'

set <string> vis;
int getPos(int idx, int dest);
void bfs(string state, string goals);


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	string state = "312045678";
	string goals ="012345678";
	
	bfs(state, goals);
	return 0;
}

int getPos(int idx, int dest) {
	int row = idx / 3;
	int col = idx % 3;
	
	if(dest == 0)
		return (col == 0 ? -1 : 3 * row + col - 1);		// Kiri
	else if(dest == 1)
		return (col == 2 ? -1 : 3 * row + col + 1);		// Kanan
	else if(dest == 2)
		return (row == 0 ? -1 : 3 * (row - 1) + col);	// Atas
	else
		return (row == 2 ? -1 : 3 * (row + 1) + col);	// Bawah
}

void bfs(string state, string goals) {
	queue <pair<string, int> > q;
	q.push(mp(state, 0));
	
	while(!q.empty()) {
		string cur = q.fr().fi;
		int step = q.fr().sc;
		
		for(int i = 0; i <= 2; ++i){
			for(int j = 0; j <= 2; ++j){
				cout << cur[3*i+j] << " ";
			}
			cout << endl;
		}
		cout << "step : " << step << endl << endl;
		
		if(!vis.count(cur))
			vis.insert(cur);
		q.pop();
		
		if(cur == goals){
			cout << step << endl;
			return;
		}
		int null = -1;
		
		for(int i = 0; i < 9; ++i){
			if(cur[i] == '0'){
				null = i;
				break;
			}
		}
		for(int i = 0; i < 4; ++i) {
			string nextStr = cur;
			int nextPos = getPos(null, i);
			
			if(nextPos != -1){
				swap(nextStr[null], nextStr[nextPos]);
			}
			if(!vis.count(nextStr))
			{
				vis.insert(nextStr);
				q.push(mp(nextStr, step + 1));
			}
		}
	}	
}


