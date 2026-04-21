/*
Payal Mistry
CS 302 - Programming Methodologies and Software Implementation
Assignment 1 - Escape Room Manager
7 April 2026
File Name: Manager_Mistry.h
//
This header defines the ChallengeNode and ChallengeList classes for the
linear linked list of active challenges, and the RoomManager class that
ties the entire application together. ChallengeList stores the sequence
of challenges players must solve, with all operations implemented
recursively. RoomManager owns the PlayerList, ChallengeList, an STL
vector of special events, and the room experience, providing the
menu-driven interface for the game host.
*/


#ifndef MANAGER_MISTRY_H
#define MANAGER_MISTRY_H
 
#include "Experience_Mistry.h"
#include "Player_Mistry.h"
#include <string>
#include <vector>
#include <iostream>
 
using namespace std;
 
 
//Node class for the linear linked list of active challenges
class ChallengeNode
{
    public:
        ChallengeNode(void);
        ChallengeNode(EscapeExperience * a_challenge);
        ChallengeNode(const ChallengeNode & source);
        ~ChallengeNode(void);
 
        //Access to the next pointer (mutable and const versions)
        ChallengeNode *& get_next(void);
        ChallengeNode * get_next(void) const;
 
        //Access to the stored challenge (mutable and const versions)
        EscapeExperience * get_challenge(void);
        const EscapeExperience * get_challenge(void) const;
 
    private:
        EscapeExperience * data;    //Base pointer 
        ChallengeNode * next;       //Next node in LLL
};
 
 
//This is the ChallengeList class includes a
//Linear linked list of active challenges in the escape room
class ChallengeList
{
    public:
        ChallengeList(void);
        ChallengeList(const ChallengeList & source);
        ChallengeList & operator=(const ChallengeList & source);
        ~ChallengeList(void);
 
        //Adds a challenge to the end, returns new challenge count
        int add_challenge(EscapeExperience * new_challenge);
 
        //Removes a challenge by position (1-based), returns true if found
        bool remove_challenge(int position);
 
        //Returns pointer to the front challenge, or nullptr if empty
        EscapeExperience * get_current_challenge(void) const;
 
        //Displays all active challenges, returns count displayed
        int display_all(void) const;
 
        //Removes all challenges, returns count removed
        int remove_all(void);
 
        //Solves and removes the front challenge, returns true if successful
        bool solve_current(void);
 
    private:
        ChallengeNode * head;   //First node (the current challenge)
        int challenge_count;    //Total active challenges
 
        //Recursive helpers
        int add_challenge(ChallengeNode *& current, EscapeExperience * new_challenge);
        bool remove_challenge(ChallengeNode *& current, int position, int current_pos);
        int display_all(ChallengeNode * current) const;
        int remove_all(ChallengeNode *& current);
        void copy_list(ChallengeNode * source, ChallengeNode *& dest);
};
 
 
//This is the RoomManager class, essentially brings everything together
class RoomManager
{
    public:
        RoomManager(void);
        ~RoomManager(void);
 
        //Sets the room's experience type, returns true if successful
        bool setup_room(EscapeExperience * room_experience);
 
        //Adds a player to turn rotation, returns new player count
        int add_player(const string & name, const string & role);
 
        //Removes a player by name, returns true if found and removed
        bool remove_player(const string & player_name);
 
        //Advances to next player's turn, returns true if successful
        bool next_turn(void);
 
        //Adds a challenge to the active sequence, returns new count
        int add_challenge(EscapeExperience * challenge);
 
        //Solves the current challenge, returns true if successful
        bool solve_challenge(void);
 
        //Schedules a special event, returns total scheduled events
        int schedule_event(EscapeExperience * event);
 
        //Triggers a special event by index, returns true if exists
        bool trigger_event(int event_index);
 
        //Displays full current state of the escape room
        void display_room_state(void) const;
 
        //Runs the main menu loop, returns 0 on exit
        int run(void);
 
    private:
        EscapeExperience * room;                //The room's experience type
        PlayerList players;                     //CLL for turn rotation
        ChallengeList challenges;               //LLL of active challenges
        vector<EscapeExperience *> special_events;  //Special events vector
};
 
#endif // MANAGER_MISTRY_H
