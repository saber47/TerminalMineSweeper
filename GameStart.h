#include<vector>
#include<string>
class Game {
private:
	int mineN, total;
	int dimX, dimY;
	std::vector<std::vector<std::string>> board;
	std::vector<std::vector<int>> data;
	void Init();
	void PrintBoard();
	void Flip(int i,int j);
	void Mark(int i,int j);
public:
	Game();
	void Play();
	void Lose();
	void Win();
	void Quit();
};