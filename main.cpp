#include <bits/stdc++.h>
#include <windows.h>

char tmp_field[18][40];
char original[18][40];
char field[18][40] = {
    "+XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX+",
    "|                                     |",
    "|                                     |",
    "|XX   XXXXX       XXXXXXXX   XXXXXXXXX|",
    "|     |           XXXXXXXX   XXXXXXXXX|",
    "| |   |XXX|  |    XXX        |        |",
    "| |   |XXX|  |    XXX    |   |        |",
    "| |   |XXX|  |    XXX    |   |        |",
    "| |          |XX         |   |        |",
    "| |XXXXX     |XX                      |",
    "|            |XX   XXXXXXX            |",
    "|XXXXXXXXX                   XXXXXXXXX|",
    "|XXXXXXXXX    XXXXXXXXXXXX            |",
    "|        |    |          |   |XXXXXXXX|",
    "|                                     |",
    "|                                     |",
    "|                                     |",
    "+XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX+"
};

void Showfield() {
    for (int i = 0; i < 18; i++) {
        printf("%s\n", field[i]);
    }
}

void set_coor(short x, short y) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = {
        x,
        y
    };
    SetConsoleCursorPosition(hStdout, position);
}

class Entity {
 private:
    int x;
    int y;

 public:
	Entity(int x, int y) {
		this -> x = x;
		this -> y = y;
	}
    void move_x(int p) {
        if (field[y][x + p] == ' ')
            x += p;
    }
    void move_y(int p) {
        if (field[y + p][x] == ' ')
            y += p;
    }
    void move(int p, int q) {
        x += p;
        y += q;
    }
    int get_x() {
        return x;
    }
    int get_y() {
        return y;
    }
    void draw(char p) {
        field[x][y] = p;
        set_coor(x, y);
        printf("%c", p);
    }
};

struct walk {
    short walk_count;
    short x;
    short y;
    short back;
};

struct target {
    short x;
    short y;
};

target walk_queue[10000];
int count = 0;
walk BFSArray[10000];
int size_Arr = 0;

void AddArray(int x, int y, int wc, int back) {
    if (tmp_field[y][x] == ' ' || tmp_field[y][x] == '.') {
        tmp_field[y][x] = 'X';
        walk tmp;
        tmp.x = x;
        tmp.y = y;
        tmp.walk_count = wc;
        tmp.back = back;
        BFSArray[size_Arr] = tmp;
        size_Arr += 1;
    }
}

void FindPath(int sx, int sy, int x, int y) {
    memcpy(tmp_field, field, sizeof(field));
    size_Arr = 0;
    walk tmp;
    tmp.x = sx;
    tmp.y = sy;
    tmp.walk_count = 0;
    tmp.back = -1;
    BFSArray[size_Arr] = tmp;
    size_Arr += 1;

    int i = 0;
    while (i < size_Arr) {
        if (BFSArray[i].x == x && BFSArray[i].y == y) {
            count = 0;
            target tmp2;
            while (BFSArray[i].walk_count != 0) {
                tmp2.x = BFSArray[i].x;
                tmp2.y = BFSArray[i].y;
                walk_queue[count] = tmp2;
                count++;
                i = BFSArray[i].back;
            }
            break;
        }
        AddArray(BFSArray[i].x + 1, BFSArray[i].y, BFSArray[i].walk_count + 1, i);
        AddArray(BFSArray[i].x - 1, BFSArray[i].y, BFSArray[i].walk_count + 1, i);
        AddArray(BFSArray[i].x, BFSArray[i].y + 1, BFSArray[i].walk_count + 1, i);
        AddArray(BFSArray[i].x, BFSArray[i].y - 1, BFSArray[i].walk_count + 1, i);
        i++;
    }
    size_Arr = 0;
}

int main() {
    memcpy(original, field, 18 * 40 * sizeof(char));
    int x = 15;
    int y = 16;
    int old_x;
    int old_y;
    int ex = 1;
    int ey = 1;
    int pts = 0;
    int play = 1;
    while (play == 1) {
        std::cout << "\n\nDo you want to play?\n1: Yes \n0: No\n";
        std::cin >> play;
        if (play == 0)
            return 0;
        std::cout << "Instruction:\n1. Use your arrow Keys to move your Pac-man (P)\n2. Eat the dots produced by the Eater (E) to gain poins\n3. Don't get caught by the Eater (E)\n\n";
        std::cout << "Select mode: \nH -> Hard\nN -> Normal\nE -> Easy\n\nInput : ";
        char diffi;
        int speedmod = 3;
        std::cin >> diffi;
        if (diffi == 'N')
            speedmod = 2;
        else if (diffi == 'H')
            speedmod = 1;
        system("cls");
        x = 15;
        y = 16;
        ex = 1;
        ey = 1;
        pts = 0;
        play = 1;
        memcpy(field, original, 18 * 40 * sizeof(char));
        Showfield();
        set_coor(x, y);
        std::cout << "P";
        int frame = 0;
        FindPath(ex, ey, x, y);
        while (true) {
            set_coor(x, y);
            std::cout << " ";
            old_x = x;
            old_y = y;
            if (GetAsyncKeyState(VK_UP)) {
                if (field[y - 1][x] == '.') {
                    y--;
                    pts++;
                } else if (field[y - 1][x] == ' ')
                    y--;
            }
            if (GetAsyncKeyState(VK_DOWN)) {
                if (field[y + 1][x] == '.') {
                    y++;
                    pts++;
                } else if (field[y + 1][x] == ' ')
                    y++;
            }
            if (GetAsyncKeyState(VK_LEFT)) {
                if (field[y][x - 1] == '.') {
                    x--;
                    pts++;
                } else if (field[y][x - 1] == ' ')
                    x--;
            }
            if (GetAsyncKeyState(VK_RIGHT)) {
                if (field[y][x + 1] == '.') {
                    x++;
                    pts++;
                } else if (field[y][x + 1] == ' ')
                    x++;
            }
            if (old_x != x || old_y != y) {
                FindPath(ex, ey, x, y);
            }
            set_coor(x, y);
            std::cout << "P";
            field[ey][ex] = '.';
            set_coor(ex, ey);
            std::cout << ".";
            if (frame % speedmod == 0 && count != 0) {
                ex = walk_queue[count - 1].x;
                ey = walk_queue[count - 1].y;
                count--;
            }
            set_coor(ex, ey);
            std::cout << "E";
            if (ex == x && ey == y) {
                break;
            }
            set_coor(40, 18);
            set_coor(40, 1);
            std::cout << pts;
            Sleep(100);
            frame++;
        }
        system("cls");
        std::cout << "You have lost this round. \nYour score is : " << pts;
    }
}