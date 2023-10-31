/*********************************************************************
** Program Filename: main.cpp
** Author:
** Date:
** Description: A program to read and analyze sports team data from a file and provide various options for user queries.
** Input: The program reads data from an input file specified by the user.
** Output: The program can print the results to the terminal or write them to a file.
*********************************************************************/

#include "catalog.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

/*********************************************************************
** Function: create_teams
** Description: Allocates memory for an array of Team objects.
** Parameters: size - the number of teams to create
** Pre-Conditions: None
** Post-Conditions: A dynamically allocated array of Team objects is returned.
*********************************************************************/
Team* create_teams(int size){
    Team* teams = new Team[size];
    return teams;
}

/*********************************************************************
** Function: create_players
** Description: Allocates memory for an array of Player objects.
** Parameters: size - the number of players to create
** Pre-Conditions: None
** Post-Conditions: A dynamically allocated array of Player objects is returned.
*********************************************************************/
Player* create_players(int size){
    Player* players = new Player[size];
    return players;
}

/*********************************************************************
** Function: populate_player_data
** Description: Reads player data from a file and populates a Player object.
** Parameters: players - the array of Player objects, index - the index to populate, file - input file stream
** Pre-Conditions: The file is open, and the index is valid.
** Post-Conditions: The Player object at the specified index is populated with data from the file.
*********************************************************************/
void populate_player_data(Player* players, int index, ifstream &file){
    string name, nation;
    int age;
    float ppg, fg;
    file >> name >> age >> nation >> ppg >> fg;
    players[index].name = name;
    players[index].age = age;
    players[index].nation = nation;
    players[index].ppg = ppg;
    players[index].fg = fg;
}

/*********************************************************************
** Function: populate_team_data
** Description: Reads team data from a file and populates a Team object.
** Parameters: teams - the array of Team objects, index - the index to populate, file - input file stream
** Pre-Conditions: The file is open, the index is valid, and Player objects for the team are allocated.
** Post-Conditions: The Team object at the specified index is populated with data from the file.
*********************************************************************/
void populate_team_data(Team* teams, int index, ifstream &file){
    string name, owner;
    int market_value, num_player;
    float total_ppg = 0;
    file >> name >> owner >> market_value >> num_player;
    teams[index].name = name;
    teams[index].owner = owner;
    teams[index].market_value = market_value;
    teams[index].num_player = num_player;
    Player* p = create_players(num_player);
    for(int i = 0; i < num_player; i++){
        populate_player_data(p, i, file);
        total_ppg += p[i].ppg;
    }
    teams[index].p = p;
    teams[index].total_ppg = total_ppg;
}

/*********************************************************************
** Function: compute_file
** Description: Reads team data from a file and populates an array of Team objects.
** Parameters: teams - the array of Team objects, file - input file stream, num_teams - the number of teams
** Pre-Conditions: The file is open, and the num_teams is valid.
** Post-Conditions: The array of Team objects is populated with data from the file.
*********************************************************************/
void compute_file(Team* teams, ifstream &file, int num_teams){
    for(int i = 0; i < num_teams; i++){
        populate_team_data(teams, i, file);
    }
}

/*********************************************************************
** Function: ask_file_name
** Description: Asks the user for the input file name and opens the file.
** Parameters: file - input file stream
** Pre-Conditions: None
** Post-Conditions: The input file is successfully opened, and its name is returned.
*********************************************************************/
string ask_file_name(ifstream &file){
    string name;
    cout << "What is the file name?: " << endl;
    cin >> name;
    cout << endl;
    file.open(name);
    while(!file.is_open()){
        cout << "Invalid file input!" << endl;
        cout << "What is the file name?: " << endl;
        cin >> name;
        cout << endl;
        file.open(name);
    }
    return name;
}

/*********************************************************************
** Function: ask_file
** Description: Asks the user whether to print results to the terminal or a file.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: Returns an output struct containing the user's choice and, if applicable, the file name.
*********************************************************************/
output ask_file(){
    output out;
    string name;
    int type;
    cout << "Would you like to print to the terminal or a file? (1: terminal, 2: file): ";
    cin >> type;
    cout << endl;
    while(type < 1 || type > 2){
        cout << "Invalid input!" << endl;
        cout << "Would you like to print to the terminal or a file? (1: terminal, 2: file): ";
        cin >> type;
        cout << endl;
    }
    out.type = type;
    if(type == 2){
        cout << "What file would you like to write to?: " << endl;
        cin >> name;
        out.file_name = name;
    }
    return out;
}

/*********************************************************************
** Function: print_or_file
** Description: Prints a line to the terminal or writes it to a file.
** Parameters: line - the line to print, type - output type (1: terminal, 2: file), file_name - name of the output file
** Pre-Conditions: None
** Post-Conditions: The line is printed to the terminal or written to the file as specified by the user.
*********************************************************************/
void print_or_file(string line, int type, string file_name){
    if(type == 1){
        cout << line << endl;
    }
    else{
        ofstream file;
        file.open(file_name, ios::out | ios::app);
        file << line << endl;
        file.close();
    }
}

/*********************************************************************
** Function: search_team_name
** Description: Searches for a team by name and prints its information.
** Parameters: teams - the array of Team objects, name - the team name to search, num_teams - the number of teams
** Pre-Conditions: None
** Post-Conditions: Team information is printed to the terminal or written to a file as specified by the user.
*********************************************************************/
void search_team_name(Team* teams, string name, int num_teams){
    output out = ask_file();
    int type = out.type;
    string file_name = out.file_name;
    for(int i = 0; i < num_teams; i++){
        if(!teams[i].name.compare(name)){
            print_or_file("Owner: " + teams[i].owner, type, file_name);
            print_or_file("Market Value: " + to_string(teams[i].market_value), type, file_name);
            print_or_file("Players: " + to_string(teams[i].num_player), type, file_name);
            print_or_file("Total PPG" + to_string(teams[i].total_ppg), type, file_name);
            for(int j = 0; j < teams[i].num_player; j++){
                print_or_file("Name: " + teams[i].p[j].name + " Age: " + to_string(teams[i].p[j].age) + " Nation: " + teams[i].p[j].nation + " PPG: " + to_string(teams[i].p[j].ppg) + " FG: " + to_string(teams[i].p[j].fg), type, file_name);
            }
        }
    }
}

/*********************************************************************
** Function: top_scorers
** Description: Finds and prints the top scorers for each team.
** Parameters: teams - the array of Team objects, num_teams - the number of teams
** Pre-Conditions: None
** Post-Conditions: Top scorers for each team are printed to the terminal or written to a file as specified by the user.
*********************************************************************/
void top_scorers(Team* teams, int num_teams){
    output out = ask_file();
    int type = out.type;
    string file_name = out.file_name;
    print_or_file("Top Scorers:", type, file_name);
    for(int i = 0; i < num_teams; i++){
        Player topScorer = teams[i].p[0];
        for(int j = 0; j < teams[i].num_player; j++){
            if(teams[i].p[j].ppg > topScorer.ppg){
                topScorer = teams[i].p[j];
            }
        }
        print_or_file(teams[i].name + " " + topScorer.name + " " + to_string(topScorer.ppg), type, file_name);
    }
}

/*********************************************************************
** Function: search_nat
** Description: Searches for players of a specific nationality and prints their information.
** Parameters: teams - the array of Team objects, nationality - the nationality to search for, num_teams - the number of teams
** Pre-Conditions: None
** Post-Conditions: Player information matching the nationality is printed to the terminal or written to a file as specified by the user.
*********************************************************************/
void search_nat(Team* teams, string nationality, int num_teams){
    output out = ask_file();
    int type = out.type;
    string file_name = out.file_name;
    print_or_file("Nationality: " + nationality, type, file_name);
    for(int i = 0; i < num_teams; i++){
        for(int j = 0; j < teams[i].num_player; j++){
            if(!teams[i].p[j].nation.compare(nationality)){
                print_or_file("Name: " + teams[i].p[j].name + " Age: " + to_string(teams[i].p[j].age), type, file_name);
            }
        }
    }
}

/*********************************************************************
** Function: ask_options
** Description: Asks the user for the desired program option.
** Parameters: None
** Pre-Conditions: None
** Post-Conditions: Returns the user's choice of program option.
*********************************************************************/
int ask_options(){
    int option;
    cout << "What would you like to do?" << endl;
    cout << "1. Search by team name" << endl;
    cout << "2. Find top scorers" << endl;
    cout << "3. Search by nationality" << endl;
    cout << "4. Quit" << endl;
    cin >> option;
    cout << endl;
    while(option < 1 || option > 4){
        cout << "Invalid input!" << endl;
        cout << endl;
        cout << "What would you like to do?" << endl;
        cout << "1. Search by team name" << endl;
        cout << "2. Find top scorers" << endl;
        cout << "3. Search by nationality" << endl;
        cout << "4. Quit" << endl;
        cin >> option;
        cout << endl;
    }
    return option;
}

/*********************************************************************
** Function: options
** Description: Provides program options based on user input.
** Parameters: teams - the array of Team objects, num_teams - the number of teams
** Pre-Conditions: None
** Post-Conditions: Executes the user-selected program option.
*********************************************************************/
void options(Team* teams, int num_teams){
    int option = ask_options();
    int loops = 0;
    do{
        if(loops != 0){
            option = ask_options();
        }
        if(option == 1){
            string team;
            cout << "What team would you like to find?: ";
            cin >> team;
            cout << endl;
            search_team_name(teams, team, num_teams);
        }
        else if(option == 2){
            top_scorers(teams, num_teams);
        }
        else if(option == 3){
            string nationality;
            cout << "What nationality would you like to search for?";
            cin >> nationality;
            cout << endl;
            search_nat(teams, nationality, num_teams);
        }
        loops++;
    } while(option != 4);
}

/*********************************************************************
** Function: delete_info
** Description: Deallocates memory and sets pointers to nullptr for Player and Team objects.
** Parameters: teams - the array of Team objects, num_teams - the number of teams
** Pre-Conditions: None
** Post-Conditions: Memory is deallocated, and pointers are set to nullptr.
*********************************************************************/
void delete_info(Team* teams, int num_teams){
    for(int i = 0; i < num_teams; i++){
        delete [] teams[i].p;
        teams[i].p = nullptr;
    }
    delete [] teams;
    teams = nullptr;
}