/*
Payal Mistry
CS 302 - Programming Methodologies and Software Implementation
Assignment 1 - Escape Room Manager
7 April 2026
File Name: Experience_Mistry.h

This header file defines the core inheritance hierarchy for
the Escape Room Manager. The base class titled EscapeExperience
includes shared room attributes like name, difficulty, time limit,
max players. This file contains the 3 derived classes - PuzzleRoom,
MysteryRoom, AdventureRoom that extend the base to model
fundamentally different experience types. The base class and PuzzleRoom
each include one char * data member. 
*/

#ifndef EXPERIENCE_MISTRY_H
#define EXPERIENCE_MISTRY_H

#include <string>
#include <iostream>

using namespace std;

//This is the EscapeExperience class which
//includes the shared foundation for all escape room experiences
class EscapeExperience
{
	public:
		EscapeExperience(void);
		EscapeExperience(const char * a_room_name, const string & a_difficulty, 
			int a_time_limit, int a_max_players);
		EscapeExperience(const EscapeExperience & source);
		EscapeExperience & operator=(const EscapeExperience & source);
		virtual ~EscapeExperience(void);

		//Start escape room experience
		virtual bool start_experience(void);
	
		//Returns current progress (percentage)
		virtual int check_progress(void) const;

		//Displays current experience info
		virtual void display(void) const;
	
		//Returns true if experience is harder than the one passed
		bool is_harder_than(const EscapeExperience & other) const;

		//Resets experience for replay
		bool reset(void);

		//Extends time limit by given minutes, returns total
		int extend_time(int additional_minutes);

	private:
		char * room_name;	//dynamically allocated char *
		string difficulty;	//easy, medium, hard
		int time_limit;		//time max
		
	protected: 
		int max_players;   	//max players allowed
};


//Derived class: logic challenges, problem solving experience
class PuzzleRoom : public EscapeExperience
{
	public:
		PuzzleRoom(void);
		PuzzleRoom(const char * a_room_name, const string & a_difficulty,
			int a_time_limit, int a_max_players, const char * a_puzzle_description,
			int a_num_puzzles, int a_complexity);
		PuzzleRoom(const PuzzleRoom & source);
		PuzzleRoom & operator=(const PuzzleRoom & source);
		~PuzzleRoom(void);

		bool start_experience(void);
		int check_progress(void) const;
		void display(void) const;

		//Attempts to solve current puzzle
		bool solve_puzzle(const string & answer);
	
		//Returns a hint (levels 1-3)
		string get_hint(int hint_level) const;

		//Increases difficulty of remaining puzzle, returns updated rating
		int increase_difficulty(int amount);

	private:
		char * puzzle_description; 	//dynamically allocated char *
		int num_puzzles;		//total puzzles
		int complexity;			//rating between 1-10
};


//Derived class: storytelling, clues, and investigation
class MysteryRoom : public EscapeExperience
{
    public:
        MysteryRoom(void);
        MysteryRoom(const char * a_room_name, const string & a_difficulty,
                    int a_time_limit, int a_max_players,
                    const string & a_theme, int a_total_clues,
                    int a_num_suspects);
        MysteryRoom(const MysteryRoom & source);
        MysteryRoom & operator=(const MysteryRoom & source);
        ~MysteryRoom(void);
 
        bool start_experience(void);
        int check_progress(void) const;
        void display(void) const;
 
        //Records a discovered clue, returns total clues found so far
        int discover_clue(const string & clue_found);
 
        //Accuses a suspect, returns true if the accusation is correct
        bool accuse_suspect(const string & suspect_name) const;
 
        //Reveals context, detail_level (1-3) controls depth
        string reveal_narrative(int detail_level) const;
 
    private:
        string theme;       //overarching narrative theme
        int total_clues;    //total clues needed to solve the mystery
        int num_suspects;   //number of suspects involved
};
 
 
//Derived class: exploration, terrain navigation, and discovery
class AdventureRoom : public EscapeExperience
{
    public:
        AdventureRoom(void);
        AdventureRoom(const char * a_room_name, const string & a_difficulty,
                      int a_time_limit, int a_max_players,
                      const string & a_terrain_type, int a_total_areas,
                      int a_discovery_count);
        AdventureRoom(const AdventureRoom & source);
        AdventureRoom & operator=(const AdventureRoom & source);
        ~AdventureRoom(void);
 
        bool start_experience(void);
        int check_progress(void) const;
        void display(void) const;
 
        //Explores an area by name, returns true if successful
        bool explore_area(const string & area_name);
 
        //Logs a discovery, returns updated discovery count
        int log_discovery(const string & discovery_description);
 
        //Checks if terrain conditions are safe to continue
        bool check_terrain_safety(void) const;
 
    private:
        string terrain_type;    //ex: cave, jungle, ruins, etc
        int total_areas;        //total areas available to explore
        int discovery_count;    //discoveries made so far
};
 
#endif // EXPERIENCE_MISTRY_H
 	

