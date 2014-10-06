#include <time.h>
#include <iostream>
#include <string>
using namespace std;
class Player{
public:
    int str = 1, str_mod, ac, hp, dex = 1, dex_mod, intel = 1, intel_mod, con = 1, con_mod, wis = 1, wis_mod, cha = 1, cha_mod;
    int xp = 0;
    int level = 1;
    int available_stats[6] = {16,14,13,12,11,10};
    void set_stats();
    void set_stats(int,int,int,int,int,int);
    void take_damage(int);
    bool check_stat(int);
    void print_avail_stats();
    void set_enemy_stats(int,int,int);
    void user_fight(int,int,int);
    void scenario(string,string,string,string,int,int,int);
};
//Player's stat mod, stat Player's going up against (used for finding whether something hits/skill checks)
int roll_check(int x, int y){ 
    int roll = (rand() % 20) + x;
    //cout << "You rolled " << roll << ". \n";
    if (roll + x>=y){
        printf("Successful! ");
        return 1;
    }
    else {
        printf("Unsuccessful. \n");
        return 0;
    }
}
int find_damage(int t,int x){ //return from roll_check, str_mod;
    int damage;
    if (t==1){
        damage = (rand() % 8) + x;
        cout << "A hit of " << damage << " damage. \n";
    }
    else if(t==0) {
        damage = 0;
    }
    return damage;
}
bool Player::check_stat(int x){ // stat being checked
    bool check = false;
    for (int i = 0; i<6; i++){
        if (x == available_stats[i]){
            available_stats[i]=0;
            check = true;
        }
    }
    return check;
};
void Player::print_avail_stats(){
    printf("Available stats: ");
    for (int i = 0; i<6; i++){
        if (available_stats[i] != 0){
            cout << available_stats[i] << " ";
        }
    }
    printf(" \n");
}
void Player::set_stats(){
    ac = 16;
    hp = 20;
    print_avail_stats();
    printf("Enter a number for strength: ");
    while(check_stat(str)==false){
        cin >> str;
    }
    print_avail_stats();
    printf("Enter a number for dexterity: ");
    while(check_stat(dex)==false){
        cin >> dex;
    }
    print_avail_stats();
    printf("Enter a number for intelligence: ");
    while(check_stat(intel)==false){
        cin >> intel;
    }
    print_avail_stats();
    printf("Enter a number for constitution: ");
    while(check_stat(con)==false){
        cin >> con;
    }
    print_avail_stats();
    printf("Enter a number for wisdom: ");
    while(check_stat(wis)==false){
        cin >> wis;
    }
    print_avail_stats();
    printf("Enter a number for charisma: ");
    while(check_stat(cha)==false){
        cin >> cha;
    }
    str_mod = (str - 9) / 2;
    dex_mod = (dex - 9) / 2;
    intel_mod = (intel - 9) / 2;
    con_mod = (con - 9) / 2;
    wis_mod = (wis -9) / 2;
    cha_mod = (cha - 9) / 2;
}
void Player::set_stats(int a, int b, int c, int d, int e, int f){ //str dex intel con wis cha
    str = a;
    dex = b;
    intel = c;
    con = d;
    wis = e;
    cha = f;
    str_mod = (str - 9) / 2;
    dex_mod = (dex - 9) / 2;
    intel_mod = (intel - 9) / 2;
    con_mod = (con - 9) / 2;
    wis_mod = (wis -9) / 2;
    cha_mod = (cha - 9) / 2;
}
void Player::set_enemy_stats(int x, int y, int z){ //str, ac, hp
    str = x;
    ac = y;
    hp = z;
    str_mod = (str - 9) / 2;
}
void Player::take_damage(int x){ //damage he's taking
    hp = hp - x;
}
void Player::user_fight(int x, int y, int z){ //enemy str,ac,hp
    string choice;
    Player enemy;
    enemy.set_enemy_stats(x,y,z);
    while((hp >= 0) || (enemy.hp >= 0)){
        printf("Press 1 to fight, and 2 to run away.");
        cin >> choice;
        if (choice == "1"){
            printf("You attempt to hit the enemy. \n");
            enemy.take_damage(find_damage(roll_check(str_mod, enemy.ac),str_mod));
            if(enemy.hp <= 0){
                printf("Success!  The enemy died! \n");
                break;
            }
            printf("The enemy attempts to hit you. \n");
            take_damage(find_damage(roll_check(enemy.str_mod, ac),enemy.str_mod));
            if (hp <= 0){
                printf("You died. \n");
                break;
            }
        }
        else if(choice == "2"){
            if(roll_check(dex_mod,20)==1){
                break;
            }
            else{
                printf("The enemy attempts to hit you. \n");
                take_damage(find_damage(roll_check(enemy.str_mod, ac),enemy.str_mod));
                if (hp <= 0){
                    printf("You died. \n");
                    break;
                }
            }
        }
        else{
            printf("Please enter a valid number.");
        }
    }
}
//string b = story text, string a = "check" or "fight" or "choice",
//if fight, then enemy str, ac, hp
// check, c = failure text, d = success text, x = user's stat y = other num, z = health subtraction
 //if failed
void Player::scenario(string a, string b, string c, string d, int x, int y, int z){
    cout << b << " \n";                                              
    if (a == "check"){                                              
        if (roll_check(x,y) == 1){                                
            cout << d;
        }
        else {
            cout << c << "  You lost " << z << " health. \n";
            hp = hp - z;
        }
    }
    if(a == "fight"){
        user_fight(x,y,z);
    }
}
int main(){
    srand(time(NULL));
    Player user;
    user.set_stats();
    return 0;
}
