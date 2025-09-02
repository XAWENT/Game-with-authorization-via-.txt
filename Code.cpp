#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <functional>
#include <vector>
#include <conio.h>


using namespace std;
bool reg_palyer = false;
string login_player;
/*
    
  registr или reg <Логин> <Пароль>

  login или log <Логин> <Пароль>

  op <Логин>
  deop <Логин>

  password <Старый пароль> <Новый пароль>

  words
       add :
        <Слово>     
        <Подсказка>
       reset

  start


*/
int words_num = 0;
int player_points = 0;
int end_point = 0;
string account_point = "";

void number(string word_cnt) {

    player_points = stoi(word_cnt);


}
string hash_pass = "";
string hash_code(string pass) {
    string code="";
    
    for (int i = 0; i < pass.size(); i++) {
        hash<char> hash_string;
        code += hash_string(pass[i]);
    }

    return code;

}

int glob_point_pl = 0;
void global_points(string account_point) {
    glob_point_pl = 0;
    
    end_point = 0;
    int total_points = 0;
    total_points = 0;


    bool detect = false;

    ifstream fin_point;
    string path_point = "History_games.txt";
    fin_point.open(path_point);
    if (!fin_point.is_open()) {
        cout << "Error!" << endl;
    }
    else {
        string check;
        while (!fin_point.eof()) {
            check = "";
            getline(fin_point, check);
            if (detect) {
                number(check);
                end_point += player_points;
                detect = false;
            }
            if (check == account_point) {
                 detect = true;
            }
        }
    }
    fin_point.close();

    glob_point_pl = end_point;
}

void list_player_point() {
    

    int Points[50];
    string Logins[50];

    for (int j = 0; j < 50; j++) {
        Points[j] = 0;
        Logins[j] = "";
    }


    
        ifstream fin;
        string path = "Accounts.txt";
        fin.open(path);

        string word_cnt;
        bool detect = false;
        int i = 0;
        while (!fin.eof()) {

            word_cnt = "";
            getline(fin, word_cnt);
            
            if (detect) {

                detect = false;
                Logins[i] = word_cnt;
                global_points(word_cnt);
                Points[i] = glob_point_pl;
                i++;

            }
            if (word_cnt == "$/Login/$") detect = true;


        }

        fin.close();
    
        for (int now = 0; now < 50; now++) {
            for (int now = 0; now < 50; now++) {
                if (Points[now] < Points[now+1]) {
                    int c = 0;
                    string c2 = "";
                    c = Points[now];
                    c2 = Logins[now];
                    Points[now] = Points[now + 1];
                    Logins[now] = Logins[now + 1];
                    Points[now + 1] = c;
                    Logins[now + 1] = c2;
                }
            }
        }
    for (int k = 0; k < 50; k++) if (Logins[k] != "") cout << endl << Logins[k] << " " << Points[k];

}


void reg() {

    cout << endl<< "Registration: ";

    string login;
    string password;
    
    bool end = false;
    bool reg = false;
    while (!end) {
        bool check_log = false;
        cout << endl;
        cout << endl << "Login: ";
        cin >> login;
        cout << endl << "Password: ";
        cin >> password;






        ifstream fin_log;
        string path_log = "Accounts.txt";
        fin_log.open(path_log);

        string word_cnt;
        bool detect = false;
        while (!fin_log.eof()) {
            
            word_cnt = "";
            getline(fin_log, word_cnt);
            if (detect) {
                if (login == word_cnt) {
                    check_log = true;
                    detect = false;
                }
            }
            if (word_cnt == "$/Login/$" and !check_log) detect = true;

            
        }
        fin_log.close();

        
        

        if (!check_log) {
            ofstream fout;
            string path = "Accounts.txt";
            fout.open(path, ofstream::app);
            if (!fout.is_open()) {
                cout << endl << "Error!" << endl;
            }
            else {
                cout << endl << "You have successfully registered." << endl ;
                string words_enter = "";
                bool detect = false;
                while (!end) {
                    fout << "\n";
                    fout << "$/Login/$" << "\n";
                    fout << login << "\n";
                    fout << "$/Password/$" << "\n";
                    fout << hash_code(password) << "\n";
                    end = true;
                }


            }
            fout.close();
        }
        else {
            cout << endl << "There is already such a login!" << endl << endl;
        }
    }




}

void account() {
    

    cout << endl << "Authorization: ";

    string login;
    string password;
    bool check_log = false;
    bool check_pass = false;
    bool end = false;
    while (!end) {
        cout << endl;
        cout << endl << "Login: ";
        cin >> login;
        cout << endl << "Password: ";
        cin >> password;

        ifstream fin;
        string path = "Accounts.txt";
        fin.open(path);

        string word_cnt;
        bool detect = false;
        bool detect2 = false;
        while (!fin.eof()) {
            word_cnt = "";
            getline(fin, word_cnt);
            if (detect) {
                if (login == word_cnt) {
                    check_log = true;
                    detect = false;
                }
            }
            if (word_cnt == "$/Login/$" and !check_log) detect = true;

            if (check_log) {
                if (detect2) {
                    if (hash_code(password) == word_cnt) {
                        reg_palyer = true;
                        login_player = login;
                        check_pass = true;
                        detect2 = false;
                        cout << endl << "You have successfully logged into your account <" << login << ">." << endl;
                        break;
                    }
                }
                if (word_cnt == "$/Password/$" and check_log) detect2 = true;
            }
        }
        fin.close();
        if (!check_log or !check_pass) {
            cout << endl << "Authorization failed!" << endl ;
            cout << endl << "If you do not have an account, you can register by entering 'reg <login> <password>' or 'register <login> <password>'." << endl;
            
        }
        end = true;
    }

    


}

void words() {
    string choose = "";
    cout << "Type 'add' to add a words." << endl;
    cout << "Enter 'delete' to delete all words." << endl;
    cout << "Enter 0 to end the input." << endl << endl;


    bool end = false;
    while (!end){
        cin >> choose;
        if (choose == "add") {
            ofstream fout;
            string path = "Words.txt";
            fout.open(path, ofstream::app);
            if (!fout.is_open()) {
                cout << "Error!" << endl;
            }
            else {
                string w = "";
                fout << "\n";
                string words_enter = "";
                while (words_enter != "0" and words_num < 15) {
                    cout << "Enter the word." << endl;
                    cin >> words_enter;
                    if (words_enter == "0") break;
                    w = words_enter;
                    fout << "\n";
                    cout << "Enter a hint." << endl;
                    cin >> words_enter;
                    if (words_enter == "0") break;
                    fout << w;
                    fout << "\n";
                    fout << words_enter;
                    fout << "\n";
                    words_num++;

                };

            }
            fout.close();
        }
        else if (choose == "delete") {
            ofstream fout;
            string path = "Words.txt";
            fout.open(path);
            if (!fout.is_open()) {
                cout << "Error!" << endl;
            }
            else {
                fout << "";
            }
            fout.close();
        }
        end = true;
    }
    
    
}


void game() {
    

        




    

    //Здесь был XAWENT

    

      
        cout << "\t\t\tWelcome to Word Jumble!\n\n";
        cout << "Unscramblе the letters to make a word. \n";
        cout << "Enter 'hint' for а hint. \n";
        cout << "Enter 'quit' to quit the round. \n\n";

        bool game = true;

        int global_max_point = 0, global_point = 0;


        for (int round = 0; round < 5; round++) {

            string WORDS[15];
            string HINTS[15];

            ifstream fin;
            string path = "Words.txt";
            fin.open(path);
            int nw = 0;
            string word_loc;
            int cnt = 0;
            words_num = 0;
            for (int i = 0; !fin.eof(); i++) {
                word_loc = "";
                getline(fin, word_loc);

                if (cnt == 0 and word_loc != "") WORDS[nw] = word_loc;
                if (cnt == 1 and word_loc != "") HINTS[nw] = word_loc;
                if (cnt == 1 and word_loc != "") nw++;
                if (cnt == 1 and word_loc != "") words_num++;
                if (cnt == 1 and word_loc != "") cnt = 0;
                else if(word_loc != "") cnt++;
                

            }
            fin.close();

            
            srand(static_cast<unsigned int>(time(0)));
            int choice = (rand() % words_num);
            string theWord = WORDS[choice];
            string theHint = HINTS[choice];



            string jumble = theWord;
            int length = jumble.size();
            while (jumble == theWord) {
                for (int i = 0; i < length; ++i) {
                    int index1 = (rand() % length);
                    int index2 = (rand() % length);
                    char temp = jumble[index1];
                    jumble[index1] = jumble[index2];
                    jumble[index2] = temp;
                }
            }

            int jumble_size = jumble.size();
            int point_size = jumble_size / 2;
            int point = point_size;
            int max_point = point;
            if (point == 0) point++;
            global_max_point += max_point;



            cout << endl << "The jumble is: " << jumble;
            string guess;
            cout << "\n\nYour guess: ";
            cin >> guess;
            while ((guess != theWord) && (guess != "quit")) {
                if (guess == "hint") {
                    cout << theHint;
                    point -= 1;
                }
                else cout << "Sorry. that's not it. ";
                cout << "\n\nYour guess: ";
                if (point > 0) point -= 1;
                cin >> guess;

            }


            global_point += point;
            if (guess == theWord) cout << "\nThat's it! You guessed it!\n" << "\nYour points: " << point << " / " << max_point << "\n";

        }
        cout << "\nYour total points: " << global_point << " / " << global_max_point << "\n";
        cout << "\nThanks for playing.\n";

        ofstream fout_history;
        string path_hystory = "History_games.txt";
        fout_history.open(path_hystory, ofstream::app);
        if (!fout_history.is_open()) {
            cout << "Error!" << endl;
        }
        else {
            fout_history << "\n"  << "\n" << login_player << "\n" << global_point;
        }

    }





int main()
{

    cout << "\n" << "Enter <reg> or <register> to register.";
    cout << "\n" << "Enter <log> or <login> for authorization.";
 
    cout << "\n" << "Enter <leave> to log out of your account.";
    cout << "\n" << "Enter <quit> or <exit> to exit.";

    cout << "\n" << "Type <word> or <words> to edit the words.";
    cout << "\n" << "Enter <point> or <points> or <stat> to view the player's points.";

    cout << "\n" << "Enter <start> or <game> to start the game." << endl;
    bool end = false;
    string action = "";
    while (!end) {
        cout << endl;
        action = "";
        cin >> action;
        
        

        if (action == "exit" or action == "quit") {
            end = true;
        }
        if (action == "points" or action == "point" or action == "stat") {
            list_player_point();
        }

        if ((action == "log" or action == "login") and !reg_palyer) account();
        if ((action == "word" or action == "words") and reg_palyer) words();
        if ((action == "leave" ) and reg_palyer) {
            cout << endl << "You have logged out of your account." << endl;
            reg_palyer = false;
            login_player = "";
        }
        if((action == "reg" or action == "register") and !reg_palyer) reg();
        if ((action == "game" or action == "start") and reg_palyer) {
            game();
        }
        
    }
    
}