
#include <iostream>

using namespace std;


void place_atoms(int board_size, int** atoms_position, int number_of_atoms) {//wylosowanie pozycji atomow
    int* atoms;
    atoms = new int[number_of_atoms];
    
    int current_index = 0;
   
    while (number_of_atoms > current_index) {    
        bool test = true;
        int rng = rand() % (board_size*board_size);                         
        for (int i = 0; i < number_of_atoms; i++) {
            if (atoms[i] == rng) {
                test = false; break;
            }                               
        }
        if (test) {
            atoms[current_index] = rng;
            current_index++;
        }        
    }
    for (int n = 0; n < number_of_atoms; n++) {
       int j = atoms[n] % board_size;
       int i= atoms[n]/board_size;
      
       atoms_position[i][j] = 1;
    }
    
    delete[] atoms;
}

class Board {
public:
    int current_position_x;
    int current_position_y;
    int score;
    int** atoms_position;
    int board_size;
    int number_of_atoms;
    int number_of_marks;
    int true_board_size;
    
    int** marks;
    int** shots;

    int* hit_number;
    char* hit_type;
    int board_type;
    int current_hit;
   


    void new_Board(int x, int y,int board_size) {//tworzenie nowej gry
        srand(static_cast<unsigned>(time(NULL)));
        this->current_hit = 0;
        this->number_of_marks = 0;
        this->score = 0;
        this->board_type = 0;
        this->current_position_x = x;
        this->current_position_y = y;
        this->board_size = board_size;
        this->true_board_size = board_size + 2;        
       
        
        atoms_position = new int* [board_size];
        marks = new int* [true_board_size];
        

        for (int i = 0; i < board_size; i++) {
            atoms_position[i] = new int[board_size];                        
            for (int j = 0; j < board_size; j++) {
                atoms_position[i][j] = 0;                                
            }
        }

        for (int i = 0; i < true_board_size; i++) {          
            marks[i] = new int[true_board_size];
            for (int j = 0; j < true_board_size; j++) {              
                marks[i][j] = 0;
            }
        }

        hit_type = new char[(board_size * 4)];
        hit_number = new int[(board_size * 4)];
        for (int i = 0; i < (board_size * 4); i++) {
            hit_type[i] = ' ';
            hit_number[i] = 0;
        }
        if (board_size == 5) {
            number_of_atoms = 3;
        }
        else if (board_size == 8) {
            number_of_atoms = 5;
        }
        else {            
            number_of_atoms = 8;
        }
        place_atoms(this->board_size, this->atoms_position,this->number_of_atoms);

    }

    bool check_if_on_board() {//sprawdzanie czy gracz nie wychodzi poza plansze
        if (current_position_x == 0 || current_position_x == (true_board_size-1) || current_position_y == 0 || current_position_y == (true_board_size - 1)) {
            return false;
        }
        else {
            return true;
        }
    }

    void place_marks() {//rozmieszczanie znacznikow
        if (check_if_on_board()&&this->number_of_marks<this->number_of_atoms) {
            int i = this->current_position_x;
            int j = this->current_position_y;
            this->marks[i][j] = 1;
            this->number_of_marks++;
        }
       
    }
    void new_atoms(int temp) {//zwieksza liczbe atomow 
        this->number_of_atoms = temp;
        for (int i = 0; i < board_size; i++) {          
            for (int j = 0; j < board_size; j++) {
                atoms_position[i][j] = 0;               
            }
        }
        place_atoms(this->board_size, this->atoms_position, this->number_of_atoms);
    }
};
string draw_player_and_marks(Board& blackbox,int current_line, int current_column) {//wyswietlanie gracza z markami
    if (blackbox.current_position_x==current_line && blackbox.current_position_y == current_column) {
        return "x";
      }
    else if (blackbox.marks[current_line][current_column] == 1) {
        return "o";
    }
    else {
        return " ";
    }
}
string draw_end(Board& blackbox, int current_line, int current_column) {//wyswietlanie plaszny koncowej i help
    if (blackbox.board_type == 1) {//plansza koncowa
        if (blackbox.marks[current_line][current_column] == 1 && blackbox.atoms_position[current_line][current_column] == 1) {//tak powinmno byc blackbox.marks[current_line+1][current_column+1]
            blackbox.score++;
            return "O";
        }
        else if (blackbox.marks[current_line][current_column] == 1 && blackbox.atoms_position[current_line][current_column] == 0) {//tak powinmno byc blackbox.marks[current_line+1][current_column+1]
            return "X";
        }
        else if (blackbox.marks[current_line][current_column] == 0 && blackbox.atoms_position[current_line][current_column] == 1) {//tak powinmno byc blackbox.marks[current_line+1][current_column+1]
            return "A";
        }
        else {
            return " ";
        }
    }
    else {//help
        if ( blackbox.atoms_position[current_line][current_column] == 1) {
        return "A";
        }
        else if (blackbox.marks[current_line][current_column] == 1) {
            return "o";
        }
        else {
            return " ";
        }
    }
}
void draw_top(Board& blackbox) {//gora planszy
     
        for (int i = 0; i < 5; i++) {
            cout << "    " << char(179);
            for (int j = 0; j < blackbox.board_size; j++) {
                if (i == 0) {
                    cout << blackbox.hit_type[j] << char(179);
                }
                if (i == 1) {
                    cout << blackbox.hit_number[j] << char(179);
                }
                if (i == 2 || i == 4) {
                    cout << char(196)<<char(197);
                }
                if (i == 3) {
                    if (blackbox.board_type == 0) { 
                        cout << draw_player_and_marks(blackbox, 0, j + 1) << char(179);
                    }
                    else if (blackbox.board_type == 1 || blackbox.board_type == 2) {
                        cout  << " "<< char(179);
                    }
                }
            }
            cout << endl;
        }
    
    
}
void draw_bottom(Board& blackbox) {//dol planszy
    
        for (int i = 0; i < 5; i++) {
            cout << "    " << char(179);
            for (int j = 0; j < blackbox.board_size; j++) {
                if (i == 4) {
                    cout << blackbox.hit_type[3 * blackbox.board_size + j] << char(179);
                }
                if (i == 3) {
                    cout << blackbox.hit_number[3 * blackbox.board_size + j] << char(179);
                }
                if (i == 0 || i == 2) {
                    cout << char(196) << char(197);
                }
                if (i == 1) {
                    
                    if (blackbox.board_type == 0) {
                        cout << draw_player_and_marks(blackbox, blackbox.true_board_size - 1, j + 1) << char(179);
                    }
                    else if (blackbox.board_type == 1 || blackbox.board_type == 2) {
                        cout << " "<< char(179);
                    }
                }
            }
            cout << endl;
        }
        
        for (int j = 0; j < blackbox.board_size; j++) {
            if (j == 0) {
                cout <<"    " << char(192);
            }
            else if (j == blackbox.board_size - 1) {
                cout << char(196) << char(193) << char(196) << char(217);
            }
            else {
                cout << char(196)<<char(193);
            }
        }
        cout << endl;
    
}
void draw_line(Board& blackbox, int& current_line) {//rysuje pojedyncza linie
    if (blackbox.board_type == 0) {
        for (int i = 0; i < blackbox.board_size + 1; i++) {
            if (i == 0) {
                cout << blackbox.hit_type[blackbox.board_size + current_line] << blackbox.hit_number[blackbox.board_size + current_line] << char(179) << draw_player_and_marks(blackbox, current_line + 1, i) << char(179);
            }
            else if (i == blackbox.board_size) {
                cout << draw_player_and_marks(blackbox, current_line + 1, i) << char(179) << draw_player_and_marks(blackbox, current_line + 1, i + 1) << char(179) << blackbox.hit_number[2 * blackbox.board_size + current_line] << blackbox.hit_type[2 * blackbox.board_size + current_line];
            }
            else {
                cout << draw_player_and_marks(blackbox, current_line + 1, i) << char(179);
            }
        }
        cout << endl;
    }
    else if (blackbox.board_type == 1|| blackbox.board_type == 2) {
        for (int i = 0; i < blackbox.board_size + 1; i++) {
            if (i == 0) {
                cout << blackbox.hit_type[blackbox.board_size + current_line] << blackbox.hit_number[blackbox.board_size + current_line] << char(179) << " "<< char(179);
            }
            else if (i == blackbox.board_size) {
                cout << draw_end(blackbox, current_line, i-1) << char(179) << " "<< char(179) << blackbox.hit_number[2 * blackbox.board_size + current_line] << blackbox.hit_type[2 * blackbox.board_size + current_line];
            }
            else {
                cout << draw_end(blackbox, current_line, i-1) << char(179);
            }
        }
        cout << endl;
    }
}



void display_normal_board(Board& blackbox) {
    
    draw_top(blackbox);
    for (int current_line = 0; current_line < blackbox.board_size; current_line++) {
        draw_line(blackbox, current_line);
    }
    draw_bottom(blackbox);
}
void display_end_board(Board& blackbox) {
    draw_top(blackbox);
    for (int current_line = 0; current_line < blackbox.board_size; current_line++) {
        draw_line(blackbox, current_line);
    }
    draw_bottom(blackbox);
    cout << "wynik:" << blackbox.score;
    system("pause");
}
void display_help_board(Board& blackbox) {
    draw_top(blackbox);
    for (int current_line = 0; current_line < blackbox.board_size; current_line++) {
        draw_line(blackbox, current_line);
    }
    draw_bottom(blackbox);
   
}
void display_board(Board& blackbox) {//typ planszy 
    system("cls");
    if (blackbox.board_type==0) {
        display_normal_board(blackbox);
       }
    else if (blackbox.board_type == 1) {
        display_end_board(blackbox);
    }
    else {
        display_help_board(blackbox);
        char a;
        cin >> a;
        blackbox.board_type = 0;
    }
}







void start_menu(Board& blackbox) {
    system("cls");
    while (1) {
        
        char n;        
        cout << "Witam w grze black-box" << endl;
        cout << "Wybierz rozmiar planszy:" << endl;
        cout << "1.5x5" << endl;
        cout << "2.8x8 " << endl;
        cout << "3.10x10" << endl;
        cin >> n;
        if (n == '1' ) {
            blackbox.new_Board(2, 0, 5); break;
        }
        else if (n == '2') {
            blackbox.new_Board(2, 0, 8); break;
        }
        else if (n == '3') {
            blackbox.new_Board(2, 0, 10); break;
        }
        else {
            system("cls");
            cout << "1wybierz ponownie " << endl;
        }
    }
    while (1) {
        system("cls");
        char n;
        cout << "Czy chxcesz zmienic liczbe atomow?" << endl;
        cout << "1.Tak" << endl;
        cout << "2.Nie" << endl;
        cin >> n;
        if (n == '1') {
            int temp;
            cout << endl << "podaj ilosc:";
            cin >> temp;
            blackbox.new_atoms(temp);
            break;
        }
        if (n == '2') {
            break;
        }
        else {
        system("cls");
        cout << "wybierz ponownie " << endl;
        }
    }
}

void menu(Board& blackbox, bool& restart) {//menu podpunkt 2
    system("cls");
    char menu;
    while (1) {

        cout << "opcje:" << endl;
        cout << "1.Wroc do gry " << endl;
        cout << "q/Q.Wyjdz do menu glownego" << endl;      
        cout << "H/h.Help " << endl;
        cout << "k/p.Zakoncz " << endl;
        cin >> menu;
        if (menu == 'q'|| menu == 'Q') {
            restart = true; break;
        }
        else if (menu == '1') {
            break;
        }
        else if (menu == 'H' || menu == 'h') {
            blackbox.board_type = 2; break;
        }
        else if (menu == 'k'|| menu == 'p') {
            blackbox.board_type = 1; break;
        }
        else {
            system("cls");
            cout << "wybierz ponownie ";
        }
    }
}

void player_move(Board& blackbox, string command) {//przemieszczenie gracza
    if (command == "w" || command == "W") {
        if (blackbox.current_position_x>0 && !(blackbox.current_position_x - 1 == 0 && (blackbox.current_position_y == blackbox.true_board_size - 1 || blackbox.current_position_y == 0))) {
            blackbox.current_position_x--;
        }       
    }
    else if (command == "a" || command == "A") {
        if (blackbox.current_position_y > 0 && !(blackbox.current_position_y - 1 == 0 && (blackbox.current_position_x == blackbox.true_board_size - 1 || blackbox.current_position_x == 0))) {
            blackbox.current_position_y--;
        }
    }
    else if (command == "s" || command == "S") {
        if (blackbox.current_position_x < (blackbox.true_board_size-1) && !(blackbox.current_position_x + 1 == blackbox.true_board_size-1 && (blackbox.current_position_y == blackbox.true_board_size - 1 || blackbox.current_position_y == 0))) {
            blackbox.current_position_x++;
        }
    }
    else {
        if (blackbox.current_position_y < (blackbox.true_board_size - 1) && !(blackbox.current_position_y + 1 == blackbox.true_board_size - 1 && (blackbox.current_position_x == blackbox.true_board_size - 1 || blackbox.current_position_x == 0))) {
            blackbox.current_position_y++;
        }
    }
}

void shot_check(Board& blackbox, int& shot_position_x, int& shot_position_y, char& direction,int x,int y,bool& end_of_shot ) {
    if (direction == 'W') {
        if (blackbox.atoms_position[shot_position_x][shot_position_y] == 1) {    
            blackbox.hit_type[3 * blackbox.board_size + y-1] = 'H';
            end_of_shot = true;
        }
        else if (shot_position_x - 1==0) {
            blackbox.hit_number[shot_position_y] = blackbox.current_hit + 1;
            end_of_shot = true;
        }
        //end of shot=true czy koniec strzalu
        else if (blackbox.atoms_position[shot_position_x][shot_position_y +1] == 1)  {
            direction = 'A';
            shot_position_x++;
        }
        else if (blackbox.atoms_position[shot_position_x][shot_position_y -1] == 1) {
            direction = 'D';
            shot_position_x++;
        }
        else {
            shot_position_x--;
        }
        //przemieszczenie pozycji strzalu 
    }
    else if (direction == 'S') {
        if (blackbox.atoms_position[shot_position_x][shot_position_y] == 1) {
            blackbox.hit_type[y - 1] = 'H';
            end_of_shot = true;
        }
        else if (shot_position_x +1 == blackbox.board_size) {
            blackbox.hit_number[3 * blackbox.board_size + shot_position_y] = blackbox.current_hit + 1;
            end_of_shot = true;
        }
        else if (blackbox.atoms_position[shot_position_x ][shot_position_y + 1] == 1) {
            direction = 'A';
            shot_position_x--;
        }
        else if (blackbox.atoms_position[shot_position_x ][shot_position_y - 1] == 1) {
            direction = 'D';
            shot_position_x--;
        }
        else {
            shot_position_x++;
        }

    }

    else if (direction == 'A') {
        if (blackbox.atoms_position[shot_position_x ][shot_position_y] == 1) {
            blackbox.hit_type[2 * blackbox.board_size + x-1] = 'H';
            end_of_shot = true;
        }
        else if (shot_position_y - 1 == 0) {
            blackbox.hit_number[blackbox.board_size + shot_position_x] = blackbox.current_hit + 1;
            end_of_shot = true;
        }
       /* else if (blackbox.atoms_position[shot_position_x + 1][shot_position_y] == 1) {
            direction = 'S';
            shot_position_y--;
        }
        else if (blackbox.atoms_position[shot_position_x-1][shot_position_y ] == 1) {
            direction = 'W';
            shot_position_y--;
        }*/
        else {
            shot_position_y--;
        }

    }
    else if (direction == 'D') {
        if (blackbox.atoms_position[shot_position_x ][shot_position_y] == 1) {
            blackbox.hit_type[blackbox.board_size + x-1] = 'H';
            end_of_shot = true;
        }
        else if (shot_position_y+1 ==  blackbox.board_size) {
            blackbox.hit_number[2* blackbox.board_size + shot_position_x] = blackbox.current_hit + 1;
            end_of_shot = true;
        }
        /*else if (blackbox.atoms_position[shot_position_x + 1][shot_position_y] == 1) {
            direction = 'S';
            shot_position_y++;
        }
        else if (blackbox.atoms_position[shot_position_x - 1][shot_position_y] == 1) {
            direction = 'W';
            shot_position_y++;
        }*/
        else {
            shot_position_y++;
        }
    }

}
void shot(Board& blackbox) {//to sie nie nadaje powinenes sprawdzac odbicie w funkcji shot_check bo wychodzisz poza tablice pozycji gdzie moze sprawidzic pozycje atomow 
    int x = blackbox.current_position_x;
    int y = blackbox.current_position_y;
    
    int shot_position_x;
    int shot_position_y;

    bool end_of_shot = false;


    
    if (x == 0 || y == 0 || x == blackbox.true_board_size - 1 || y == blackbox.true_board_size - 1) {//umiejscowanie pozycji strzalu i sprawdzenie czy mozna oddac strzał
        
        char direction;
        if (x == 0) {
            direction = 'S';
            shot_position_x=0;
            shot_position_y=y-1;
            blackbox.hit_number[y-1] = blackbox.current_hit + 1;
            if (blackbox.atoms_position[shot_position_x][shot_position_y] == 1) {
                blackbox.hit_type[y - 1] = 'H';


            }
            else if (blackbox.atoms_position[shot_position_x][shot_position_y+1] == 1 && blackbox.atoms_position[shot_position_x][shot_position_y - 1] == 1) {
                blackbox.hit_type[y - 1] = 'R';
            }
            else {
                while (!end_of_shot) {
                    shot_check(blackbox, shot_position_x, shot_position_y, direction, x, y, end_of_shot);
                }
            }
        }
        else if (y == 0) {
            direction = 'D';
            shot_position_x = x - 1;
            shot_position_y = 0;
            blackbox.hit_number[blackbox.board_size + x-1] = blackbox.current_hit + 1;
            if (blackbox.atoms_position[shot_position_x][shot_position_y] == 1) {
                blackbox.hit_type[blackbox.board_size + x-1] = 'H';
            }

            else if (blackbox.atoms_position[shot_position_x+1][shot_position_y] == 1 && blackbox.atoms_position[shot_position_x-1][shot_position_y] == 1) {
                blackbox.hit_type[blackbox.board_size + shot_position_x] = 'R';

            }
            else {
                while (!end_of_shot) {
                    shot_check(blackbox, shot_position_x, shot_position_y, direction, x, y, end_of_shot);
                }
            }
        }
        else if (x == blackbox.true_board_size - 1) {
            direction = 'W';
            shot_position_x = blackbox.board_size-1;
            shot_position_y = y - 1;
            blackbox.hit_number[3 * blackbox.board_size + shot_position_y] = blackbox.current_hit + 1;
            if (blackbox.atoms_position[shot_position_x][shot_position_y] == 1) {
                blackbox.hit_type[3 * blackbox.board_size + shot_position_y] = 'H';
            }
            else if (blackbox.atoms_position[shot_position_x][shot_position_y + 1] == 1 && blackbox.atoms_position[shot_position_x][shot_position_y - 1] == 1) {
                blackbox.hit_type[3 * blackbox.board_size + shot_position_y] = 'R';
            }
            else {
                while (!end_of_shot) {
                    shot_check(blackbox, shot_position_x, shot_position_y, direction, x, y, end_of_shot);
                }
            }
        }
        else if (y == blackbox.true_board_size - 1) {
            direction = 'A';
            shot_position_x = x - 1;
            shot_position_y = blackbox.board_size - 1;
            blackbox.hit_number[2 * blackbox.board_size + shot_position_x] = blackbox.current_hit + 1;
            if (blackbox.atoms_position[shot_position_x][shot_position_y] == 1) {
                blackbox.hit_type[2 * blackbox.board_size + shot_position_x] = 'H';
            }

            else if (blackbox.atoms_position[shot_position_x+1][shot_position_y] == 1 && blackbox.atoms_position[shot_position_x-1][shot_position_y] == 1) {
                blackbox.hit_type[2 * blackbox.board_size + shot_position_x] = 'R';
            }
            else {
                while (!end_of_shot) {
                    shot_check(blackbox, shot_position_x, shot_position_y, direction, x, y, end_of_shot);
                }
            }
        }
        
        blackbox.current_hit++;
    }

       

       
    
    
}

void check_command(Board& blackbox, string command,bool& restart) {
    if (command == "w" || command == "W" || command == "a" || command == "A" || command == "s" || command == "S" || command == "d" || command == "D") {
        player_move(blackbox, command);
    }
    if (command == "v" ) {
        shot(blackbox);
    }
    if (command == "o") {
        blackbox.place_marks();
    }
    if (command == "m") {
        menu(blackbox, restart);
    }
    else if (command == "k" || command == "p") {
        blackbox.board_type = 1; 
    }
}

void black_box() {
    bool restart = false;
    Board blackbox;
    string command;
    start_menu(blackbox);
    while (1) {
        display_board(blackbox);
        cin >> command;
        check_command(blackbox,command,restart);
        if (restart) {
            start_menu(blackbox);
        }
    }
}







int main()
{
    
    
    
    black_box();
    return 0;
}
