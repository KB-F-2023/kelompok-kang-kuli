#include <bits/stdc++.h>
using namespace std;
#define N 3

struct Node
{
	Node* parent;   //parent node

	int mat[N][N];
	int x, y;       //koordinat tile kosong
	int cost;       //jarak tile ke posisinya yg benar
	int level;      //jumlah move yang telah dilakukan
};

//fungsi untuk mencetak puzzle
int printMatrix(int mat[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			printf("%d ", mat[i][j]);
		printf("\n");
	}
}

// Fungsi untuk mengalokasikan node baru
Node* newNode(int mat[N][N], int x, int y, int newX,
			int newY, int level, Node* parent)
{
	Node* node = new Node;

	// set pointer untuk path ke root
	node->parent = parent;

	// copy data dari parent node ke current node
	memcpy(node->mat, mat, sizeof node->mat);

	// menggeser tile sebayak 1
	swap(node->mat[x][y], node->mat[newX][newY]);

	// set jumlah dari tile yang tidak pada tempatnya
	node->cost = INT_MAX;

	// set jumlah move yang telah dilakukan
	node->level = level;

	// mengupdate koordinat xy yang baru
	node->x = newX;
	node->y = newY;

	return node;
}

// bawah, kiri, atas, kanan
int row[] = { 1, 0, -1, 0 };
int col[] = { 0, -1, 0, 1 };

//fungsi untuk menghitung cost/jarak
int calculateCost(int initial[N][N], int final[N][N])
{
	int count = 0;
	for (int i = 0; i < N; i++)
	for (int j = 0; j < N; j++)
		if (initial[i][j] && initial[i][j] != final[i][j])
		count++;
	return count;
}

// fungsi untuk mengecek apakah koordinat tile kosong safe untuk diproses
int isSafe(int x, int y)
{
	return (x >= 0 && x < N && y >= 0 && y < N);
}

// print path dari root node ke destination node
void printPath(Node* root)
{
	if (root == NULL)
		return;
	printPath(root->parent);
	printMatrix(root->mat);

	printf("\n");
}

// membandingkan objek untuk menyusun urutan
struct comp
{
	bool operator()(const Node* lhs, const Node* rhs) const
	{
		return (lhs->cost + lhs->level) > (rhs->cost + rhs->level);
	}
};

//fungsi untuk menyelesaikan puzzle NxN
void solve(int initial[N][N], int x, int y,
		int final[N][N])
{
	// membuat priority queue untuk menyimpan live nodes dari
	// search tree;
	priority_queue<Node*, std::vector<Node*>, comp> pq;

	// membuat root node dan menghitung costnya
	Node* root = newNode(initial, x, y, x, y, 0, NULL);
	root->cost = calculateCost(initial, final);

	// menambahkan root ke daftar live nodes;
	pq.push(root);

	// mencari live node dengan cost paling sedikit,
	// menambahkan node childnya ke list live node dan
	// akhirnya dihapus dari list.
	while (!pq.empty())
	{
		// Mencari live node dengan estimasi cost paling sedikit
		Node* min = pq.top();

		// node yang ditemukan dihapus dari list live node
		pq.pop();

		// jika min merupakan jawabannya
		if (min->cost == 0)
		{
			// print path dari root ke destination;
			printPath(min);
			return;
		}

		// dilakukan untuk setiap child dari min
		// maksimal 4 child tiap node
		for (int i = 0; i < 4; i++)
		{
			if (isSafe(min->x + row[i], min->y + col[i]))
			{
				// membuat child node dan menghitung
				// costnya
				Node* child = newNode(min->mat, min->x,
							min->y, min->x + row[i],
							min->y + col[i],
							min->level + 1, min);
				child->cost = calculateCost(child->mat, final);

				// Masukkan child ke list live node
				pq.push(child);
			}
		}
	}
}

int main()
{

    //initial state
	int initial[N][N] =
	{
		{1, 2, 5},
		{3, 4, 0},
		{6, 7, 8}
	};
	
    //final state
	int final[N][N] =
	{
		{0, 1, 2},
		{3, 4, 5},
		{6, 7, 8}
	};
    
    //koordinat tile kosong
	int x = 1, y = 2;

	solve(initial, x, y, final);

	return 0;
}

