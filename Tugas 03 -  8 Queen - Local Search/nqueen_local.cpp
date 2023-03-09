#include <iostream>
#include <math.h>
#define N 8
using namespace std;


// Fungsi utilitas untuk menata array "papan"
// dan array "state" secara random untuk mendapat
// starting point untuk algoritma
void configureRandomly(int board[][N], int* state){

	// Seed untuk fungsi random
	// Menggunakan fungsi srand() untuk menginisialisasi
	// random number generator (rand())
	srand(time(0));

	// Iterasi melalui index kolom
	for (int i = 0; i < N; i++) {

		// Mendapat index baris random
		state[i] = rand() % N;

		// Menaruh ratu di papan catur
		// berdasar tempat yang didapat
		board[state[i]][i] = 1;
	}
}

// Fungsi untuk mencetak papan catur
void printBoard(int board[][N]){

	for (int i = 0; i < N; i++) {
		cout << " ";
		for (int j = 0; j < N; j++) {
			cout << board[i][j] << " ";
		}
		cout << "\n";
	}
}

// Fungsi untuk mencetk state array
void printState(int* state){

	for (int i = 0; i < N; i++) {
		cout << " " << state[i] << " ";
	}
	cout << endl;
}

// Fungsi untuk membandingkan array
// return true jika sama dan false jika tidak
bool compareStates(int* state1, int* state2){

	for (int i = 0; i < N; i++) {
		if (state1[i] != state2[i]) {
			return false;
		}
	}
	return true;
}

// Fungsi untuk mengisi array "papan" dengan value
void fill(int board[][N], int value){

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			board[i][j] = value;
		}
	}
}

// Fungsi untuk menghitung nilai objektif dari state (ratu saling menyerang) 
int calculateObjective(int board[][N], int* state){

	// Untuk setiap ratu dalam kolom, di cek ratu lain yang berada
	// di garis serang ratu, jika ditemukan maka increment variable attacking

	// Jumlah ratu yang saling menyerang, diinisialisasikan dengan 0
	int attacking = 0;

	// Variabel untuk mengindex baris dan kolom tertentu di papan
	int row, col;

	for (int i = 0; i < N; i++) {

		// Pada setiap kolom 'i', ratu diletakkan di baris 'state[i]',
		// sesuai definisi dari state kita

		// Ke kiri dari baris yang sama (baris tetap sama dan kolom berkurang)
		row = state[i], col = i - 1;
		while (col >= 0 && board[row][col] != 1){
			col--;
		}
		if (col >= 0 && board[row][col] == 1) {
			attacking++;
		}

		// Ke kanan dari baris yang sama (baris tetap sama dan kolom bertambah)
		row = state[i], col = i + 1;
		while (col < N
			&& board[row][col] != 1) {
			col++;
		}
		if (col < N
			&& board[row][col] == 1) {
			attacking++;
		}

		// Diagonal ke kiri atas (baris dan kolom berkurang bersamaan)
		row = state[i] - 1, col = i - 1;
		while (col >= 0 && row >= 0
			&& board[row][col] != 1) {
			col--;
			row--;
		}
		if (col >= 0 && row >= 0
			&& board[row][col] == 1) {
			attacking++;
		}

		// Diagonal ke kanan bawah (baris dan kolom bertambah bersamaan)
		row = state[i] + 1, col = i + 1;
		while (col < N && row < N
			&& board[row][col] != 1) {
			col++;
			row++;
		}
		if (col < N && row < N
			&& board[row][col] == 1) {
			attacking++;
		}

		// Diagonal ke kiri bawah (kolom berkurang dan baris bertambah)
		row = state[i] + 1, col = i - 1;
		while (col >= 0 && row < N
			&& board[row][col] != 1) {
			col--;
			row++;
		}
		if (col >= 0 && row < N
			&& board[row][col] == 1) {
			attacking++;
		}

		// Diagonal ke kanan atas (kolom bertambah fan baris berkurang)
		row = state[i] - 1, col = i + 1;
		while (col < N && row >= 0
			&& board[row][col] != 1) {
			col++;
			row--;
		}
		if (col < N && row >= 0
			&& board[row][col] == 1) {
			attacking++;
		}
	}

	// Mengembalikan pasangan
	return (int)(attacking / 2);
}

// Fungsi yang membuat susunan papan berdasarkan state yang diberikan
void generateBoard(int board[][N],
				int* state)
{

	fill(board, 0);
	for (int i = 0; i < N; i++) {
		board[state[i]][i] = 1;
	}
}

// Fungsi yang menyalin isi state2 ke state1
void copyState(int* state1, int* state2)
{

	for (int i = 0; i < N; i++) {
		state1[i] = state2[i];
	}
}

// Fungsi ini mendapat tetangga dari state saat ini yang memiliki nilai objektif
// paling kecil dari tetangga yang lain maupun state saat ini
void getNeighbour(int board[][N], int* state)
{

	// Deklarasi dan inisialisasi papan optimal dan state optimal
	// dengan papan saat ini dan state sebagai starting point

	int opBoard[N][N];
	int opState[N];

	copyState(opState, state);
	generateBoard(opBoard, opState);

	// Inisialisasi objective value optimal
	int opObjective = calculateObjective(opBoard, opState);

	// Deklarasi dan inisialisasi papan sementara dan state
	// untuk perhitungan
	int NeighbourBoard[N][N];
	int NeighbourState[N];

	copyState(NeighbourState, state);
	generateBoard(NeighbourBoard, NeighbourState);
 
	// Iterasi melalui semua tetangga yang mungkin di papan
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {

			// Kondisi untuk melewati state saat ini

			if (j != state[i]) {

				//Inisialisasi tetangga sementara dengan tetangga saat ini
				NeighbourState[i] = j;
				NeighbourBoard[NeighbourState[i]][i]
					= 1;
				NeighbourBoard[state[i]][i]
					= 0;

				// Menghitung value objektif dari tetangga
				int temp
					= calculateObjective(
						NeighbourBoard,
						NeighbourState);

				// Membandingkan temp dan tetangga objektif optimal dan jika
				// temp kurang dari optimal maka diperbarui
				if (temp <= opObjective) {
					opObjective = temp;
					copyState(opState, NeighbourState);
					generateBoard(opBoard, opState);
				}

				// Kembali ke susunan awal untuk iterasi selanjutnya
				NeighbourBoard[NeighbourState[i]][i]
					= 0;
				NeighbourState[i] = state[i];
				NeighbourBoard[state[i]][i] = 1;
			}
		}
	}

	// Menyalin papan optimal dan state yang ada di papan saat ini
	copyState(state, opState);
	fill(board, 0);
	generateBoard(board, state);
}

// Fungsi untuk melakukan hill climbing
void hillClimbing(int board[][N], int* state)
{

	// Deklarasi dan inisialisasi papan tetangga dan state dengan papan saat
	// ini dan state sebagai starting point
	int neighbourBoard[N][N] = {};
	int neighbourState[N];

	copyState(neighbourState, state);
	generateBoard(neighbourBoard,
				neighbourState);

	do {

		// Menyalin papan dan state tetangga ke papan dan state saat ini,
		// karena tetangga menjadi current setelah loncatan
		copyState(state, neighbourState);
		generateBoard(board, state);

		// Mendapatkan tetangga optimal

		getNeighbour(neighbourBoard, neighbourState);

		if (compareStates(state, neighbourState)) {

			// Jika tetangga dan current sama maka tidak ada tetangga optimal, sehingga 
			// mencetak output dan mengakhiri loop
			printBoard(board);
			break;
		}
		else if (calculateObjective(board, state) == calculateObjective(neighbourBoard, neighbourState)) {

			// Jika tetangga dan current tidak sama tetapi objektifnya sama maka kita 
			// lompat ke tetangga random 

			// Tetangga random
			neighbourState[rand() % N] = rand() % N;
			generateBoard(neighbourBoard, neighbourState);
		}

	} while (true);
}

int main()
{
	int state[N] = {};
	int board[N][N] = {};

	// Mendapat starting point dengan menyusun papan secara random
	configureRandomly(board, state);

	// Melakukan hill climbing pada papan yang dihasilkan
	hillClimbing(board, state);

	return 0;
}
