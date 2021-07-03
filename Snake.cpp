/*|In The Name Of Allah|*/
#include <Windows.h>
#include <bits/stdc++.h>

using namespace std;

const unsigned short MSB = 0x8000;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

const int N = 10;
const int M = 25;

int dx[]{1 , -1 , 0 , 0};
int dy[]{0 , 0 , 1 , -1};

char grid[N + 5][M + 5];

int backcolor;
int curDirection;
vector < pair < int , int > > worm;
vector < int > lastmovefortail;

/*
232 Φ (first head)
233 Θ (second head)
249 ∙ (tail)
42 * (bomb)
236 ∞ (food)
*/

int score;
bool eatenfood;
bool eatencolor;

bool endgame;

void print(){
     SetConsoleTextAttribute(hConsole, backcolor);
     system("CLS");
     printf("Maro | Studio presents!\n");
     printf("Snake's Score : %d\n" , score);

     if(endgame){
        puts("Game Over!");
        Beep(5555 , 1200);
        return;
     }

     for(int i = 0; i <= N; i++){
        for(int j = 0; j <= M; j++){
			if(grid[i][j] == 0)
				putchar(' ');
            putchar(grid[i][j]);
        }
        puts("");
     }
}

void eat(){
     int sz = worm.size() - 1;
     //eaten food
     if(grid[worm[0].first][worm[0].second] == char (236)){
        score++;
        int last = lastmovefortail[sz];
        eatenfood = 1;
        Beep(555 , 55);
        worm.push_back({worm[sz].first - dx[last] , worm[sz].second - dy[last]});
        lastmovefortail.push_back(last);
     }
     if(grid[worm[0].first][worm[0].second] == 'C'){
        backcolor = rand() % 15 + 1;
        eatencolor = 1;
     }
}

void putstuff(){
     int x = rand() % N + 1;
     int y = rand() % M + 1;
     if(grid[x][y] == ' ' && eatenfood){
        grid[x][y] = char(236);
        eatenfood = 0;
     }
     int nwx = rand() % N + 1;
     int nwy = rand() % M + 1;
     if(grid[nwx][nwy] == ' ' && eatencolor && score >= 5){
        grid[nwx][nwy] = '?';
        eatencolor = 0;
     }
}

void movesnake(){
     for(int i = worm.size() - 1; i > 0; i--){
        lastmovefortail[i] = lastmovefortail[i - 1];
     }
     lastmovefortail[0] = curDirection;
     for(int i = 0; i < (int)worm.size(); i++){
        int last = lastmovefortail[i];
        worm[i].first += dx[last];
        if(worm[i].first == N)
            worm[i].first = 1;
        if(worm[i].first == 0)
            worm[i].first = N - 1;
        worm[i].second += dy[last];
        if(worm[i].second == M)
            worm[i].second = 1;
        if(worm[i].second == 0)
            worm[i].second = M - 1;
     }
}

void clearsnake(){
     for(int i = 0; i < (int)worm.size(); i++){
        grid[worm[i].first][worm[i].second] = ' ';
     }
}

void putsnake(){
     char head = char(233);
     if(curDirection <= 1)
        head = char(232);
     grid[worm[0].first][worm[0].second] = head;
     for(int i = 1; i < (int)worm.size(); i++){
        if(worm[i].first == worm[0].first && worm[i].second == worm[0].second){
            endgame = true;
        }
        grid[worm[i].first][worm[i].second] = char(249);
     }
}

void readmotion(){
        bool up = GetAsyncKeyState (VK_UP) & MSB;
        bool down = GetAsyncKeyState (VK_DOWN) & MSB;
        bool left = GetAsyncKeyState (VK_LEFT) & MSB;
        bool right = GetAsyncKeyState (VK_RIGHT) & MSB;
        if(up){
            curDirection = 1;
        } else if(right){
            curDirection = 2;
        } else if(down){
            curDirection = 0;
        } else if(left){
            curDirection = 3;
        }
}

int main(){
	//corner borders
    grid[0][0] = char (218) , grid[0][M] = char(191);
    grid[N][0] = char(192) , grid[N][M] = char(217);
    for(int i = 1; i < N; i++){
        grid[i][0] = (char)179; // |
        grid[i][M] = (char)179; // |
    }
    for(int i = 1; i < M; i++){
        grid[0][i] = (char)196; // -
        grid[N][i] = (char)196; // -
    }
    backcolor = rand() % 15 + 1;
    worm.push_back({N / 2 , M / 2});
    worm.push_back({N / 2 , M / 2 - 1});
    worm.push_back({N / 2 , M / 2 - 2});
    grid[worm[0].first][worm[0].second] = char(233);
    grid[worm[1].first][worm[1].second] = char(249);
    grid[worm[2].first][worm[2].second] = char(249);
    curDirection = 2;
    lastmovefortail.push_back(2);
    lastmovefortail.push_back(2);
    lastmovefortail.push_back(2);
    eatenfood = 1;
    eatencolor = 1;
    while(!endgame){
        clearsnake();
        movesnake();
        eat();
        putsnake();
        print();
        readmotion();
        putstuff();
    }
}


