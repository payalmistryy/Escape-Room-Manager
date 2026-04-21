/*
Payal Mistry
CS 302 - Programming Methodologies and Software Implementation
Assignment 1 - Escape Room Manager
7 April 2026
File Name: Player_Mistry.h

This header file defines the Player class and the circular linked list (CLL)
used for player turn rotation. Player represents an individual participant.
PlayerNode wraps a Player for use in the CLL. PlayerList manages the CLL 
with insert, remove, display, retrieve, and remove-all operations,
all implemented recursively. The circular structure naturally supports 
endless turn rotation.
*/

#ifndef PLAYER_MISTRY_H
#define PLAYER_MISTRY_H
 
#include <string>
#include <iostream>
 
using namespace std;
 
//One player in escape roomn
class Player
{
    public:
        Player(void);
        Player(const string & a_name, const string & a_role, int a_score);
 
         //Displays player's info
        void display(void) const;              
        //Adds points to score, returns updated total
        int add_points(int points_earned);      
       
        //Changes the player's role, returns true if successful
        bool change_role(const string & new_role);       
        //Returns true if this player's name matches the given name
        bool matches_name(const string & name_to_match) const; 
 
    private:
        string name;    //player's display name
        string role;    //current role (leader, investigator, etc)
        int score;      //cumulative score
};
 
 
//Node class for the circular linked list of players
class PlayerNode
{
    public:
        PlayerNode(void);
        PlayerNode(const Player & a_player);
        PlayerNode(const PlayerNode & source);
        ~PlayerNode(void);
 
        //Access to the next pointer (mutable and const versions)
        PlayerNode *& get_next(void);
        PlayerNode * get_next(void) const;
 
        //Access to the stored player data (mutable and const versions)
        Player & get_player(void);
        const Player & get_player(void) const;
 
    private:
        Player data;        //player stored in this node
        PlayerNode * next;  //next node in the CLL
};
 
 
//Circular linked list managing player turn rotation
class PlayerList
{
    public:
        PlayerList(void);
        PlayerList(const PlayerList & source);
        PlayerList & operator=(const PlayerList & source);
        ~PlayerList(void);
 
        //Adds a player to rotation, returns new player count
        int add_player(const Player & new_player);
        //Removes a player via name, returns true if found and removed
        bool remove_player(const string & player_name);
 
        //Advances to the next player's turn, returns true if successful
        bool advance_turn(void);
        //Copies matching player into found_player, returns true if found
        bool retrieve_player(const string & player_name, Player & found_player) const;
 
        //Displays all players in rotation order, returns count displayed
        int display_all(void) const;
        //Removes all players, returns count removed
        int remove_all(void);
        //Displays whose turn it currently is, returns true if list not empty
        bool display_current(void) const;
 
    private:
        PlayerNode * rear;      //points to last node
        PlayerNode * current;   //tracks whose turn it is
        int player_count;       //total number of players in list
 
        //Recursive helpers
        int display_all(PlayerNode * current, PlayerNode * rear) const;
        bool remove_player(PlayerNode *& current, const string & player_name,
                           PlayerNode * rear);
        bool retrieve_player(PlayerNode * current, const string & player_name,
                             Player & found_player, PlayerNode * rear) const;
        int remove_all(PlayerNode *& current, PlayerNode * rear);
        void copy_list(PlayerNode * source_current, PlayerNode * source_rear,
                       PlayerNode *& dest_rear);
        //Recursive helper for finding the node whose next pointer == rear
        PlayerNode * find_prev_of_rear(PlayerNode * current,
                                       PlayerNode * rear) const;
};
 
#endif // PLAYER_MISTRY_H
