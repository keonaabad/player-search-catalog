#include <iostream>
#include <fstream>

using namespace std;

//a struct to hold info of a team
struct Team {
  string name;        //name of the team
  string owner;       //owner of the team
  int market_value;   //market value of the team
  int num_player;     //number of players in the team
  struct Player *p;   //an array that holds all players
  float total_ppg;    //total points per game
};

//a struct to hold info of a player
struct Player {
  string name;      //name of the player
  int age;          //age of the player
  string nation;    //nationality of the player
  float ppg;        //points per game of the player
  float fg;         //field goal percentage
};

//a struct to hold info for output type
struct output {
  int type;         //print to terminal or file
  string file_name; //name of file to print to
};


/**************************************************
 * Name: create_teams()
 * Description: This function will dynamically allocate
                an array of teams (of the requested size)
 * Parameters: int - size of the array
 * Pre-conditions: none
 * Post-conditions: a Team array of requested size is created and return
 ***********************************************/
Team* create_teams(int);


/**************************************************
 * Name: populate_team_data()
 * Description: This function will fill a single team struct 
                with information that is read in from the file
 * Parameters:  Team* - pointer to the Team array
                int - index of the Team in the array to be filled 
                ifstream& - input file to get information from
 * Pre-conditions: Team array has been allocated; 
                   provided index is less than the array size
 * Post-conditions: a Team at provided index is populated
 ***********************************************/
void populate_team_data(Team*, int, ifstream &); 


/**************************************************
 * Name: create_players()
 * Description: This function will dynamically allocate
                an array of players (of the requested size)
 * Parameters: int - size of the array
 * Pre-conditions: none
 * Post-conditions: a Player array of requested size is created and return
 ***********************************************/
Player* create_players(int);


/**************************************************
 * Name: populate_player_data()
 * Description: This function will fill a single player struct 
                with information that is read in from the file
 * Parameters:  Player* - pointer to the Player array
                int - index of the Player in the array to be filled 
                ifstream& - input file to get information from
 * Pre-conditions: Player array has been allocated; 
                   provided index is less than the array size
 * Post-conditions: a Player at provided index is populated
 ***********************************************/
void populate_player_data(Player*, int, ifstream &); 


/**************************************************
 * Name: delete_info()
 * Description: This function will  delete all the memory that was dynamically allocated
 * Parameters: Team* - the Team array
 * Pre-conditions: the provided Team array hasn't been freed yet
 * Post-conditions: the Team array, with all Players inside, is freed
 ***********************************************/
void delete_info(Team* teams, int num_teams);


/**************************************************
 * Name: ask_file_name()
 * Description: This function will ask the user which file to read from and gets rid of bad inputs
 * Parameters: &file - the ifstream object which the program uses
 * Pre-conditions: the provided ifstream object exists
 * Post-conditions: the file name which the user inputs is opened and stored as file
 ***********************************************/
string ask_file_name(ifstream &file);


/**************************************************
 * Name: compute_file()
 * Description: This function will run populate_team_data() for all teams
 * Parameters: Team* - the team array, ifstream - the ifstream/file object, int - number of teams in the team array
 * Pre-conditions: the file is open and team array is created
 * Post-conditions: the team array is filled
 ***********************************************/
void compute_file(Team* teams, ifstream &file, int num_teams);


/**************************************************
 * Name: ask_file()
 * Description: This function will ask the user if they want to print to terminal or a file and ask which file if they choose that option and checks for bad inputs
 * Parameters: none
 * Pre-conditions: none
 * Post-conditions: none
 ***********************************************/
output ask_file();


/**************************************************
 * Name: options()
 * Description: This function will ask the user what they want to do such as search by team name, find the top scorers, and search by nationality
 * Parameters: Team* - the Team array, num_teams - number of teams in the team array
 * Pre-conditions: The team array is populated
 * Post-conditions: none
 ***********************************************/
void options(Team* teams, int num_teams);


/**************************************************
 * Name: print_or_file()
 * Description: This function will either print to the terminal or a file
 * Parameters: line - what will be printed, type - whether we are printing to a file or the terminal, file_name - name of file we are printing to (if applicable)
 * Pre-conditions: Need to have determined type and file_name
 * Post-conditions: Prints to the proper place
 ***********************************************/
void print_or_file(string line, int type, string file_name);


/**************************************************
 * Name: search_team_name()
 * Description: This function will search the teams array for a specific team
 * Parameters: Teams* - teams array, name - name of team to search for, num_teams - how many teams are in the team array
 * Pre-conditions: Need to have teams array populated and name decided
 * Post-conditions: none
 ***********************************************/
void search_team_name(Team* teams, string name, int num_teams);


/**************************************************
 * Name: top_scorers()
 * Description: This function will find the top scorers on each team
 * Parameters:  Teams* - teams array, num_teams - how many teams are in the team array
 * Pre-conditions: Need to have teams array populated
 * Post-conditions: none
 ***********************************************/
void top_scorers(Team* teams, int num_teams);


/**************************************************
 * Name: search_nat()
 * Description: This function will search the teams array for a specific nationality
 * Parameters: Teams* - teams array, nationality - nationality to search for, num_teams - how many teams are in the team array
 * Pre-conditions: Need to have teams array populated and name decided
 * Post-conditions: none
 ***********************************************/
void search_nat(Team* teams, string nationality, int num_teams);


/**************************************************
 * Name: ask_options()
 * Description: Asks the user what they would like to do after opening and reading their chosen file and checks for bad inputs
 * Parameters: none
 * Pre-conditions: none
 * Post-conditions: none
 ***********************************************/
int ask_options();