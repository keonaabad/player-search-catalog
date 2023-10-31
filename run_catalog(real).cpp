/*********************************************************************
** Program Filename: catalog.cpp
** Author: Keona Abad
** Date: 10/29/23
** Description: A catalog of basketball team and player information sourced
from a text file entered by the user. User can choose what information is outputted.
User can search by team, players' nationality, or the highest scorer from each team.
Additionally, the user can choose to quit, and the program will run until they choose to do so.
** Input: Name of file to source team and player information from
4 search options, input 1-4
1: Enter team name
3: Input desired nationality
** Output: If the user chooses 1 for search input - output a prompt to search for any specific team, then -
output team name, team information, list of players
If the user chooses 2 for search input - output the top scorer of each team and their points per game
If the user chooses 3 for search input - output the choice to search by nationality. Then, output each player of
that nationality and their age.
If the user inputs an invalid information file source, output an error message.
If the user inputs an invalid team name, output an error message.
If the user inputs an invalid nationality, output an error message.
*********************************************************************/




#include "catalog.h"

using namespace std;



/*********************************************************************
** Program Filename: main.cpp
** Author:
** Date:
** Description: This program reads data from a file, processes it to create teams, and provides various options for user interaction.
** Input: A file containing team data.
** Output: Various options for interacting with the team data.
*********************************************************************/
int main() {
    ifstream file;
    string file_name = ask_file_name(file); // Ask the user for the file name.
    int num_teams;
    file >> num_teams;
    Team* teams = create_teams(num_teams); // Create an array of teams based on the number of teams read from the file.
    compute_file(teams, file, num_teams); // Compute team data from the file.
    file.close();

    options(teams, num_teams); // Provide options for user interaction with the team data.
    delete_info(teams, num_teams); // Delete memory allocated for teams.
    return 0;
}