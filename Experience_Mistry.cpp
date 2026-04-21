/*
Payal Mistry
CS 302 - Programming Methodologies and Software Implementation
Assignment 1 - Escape Room Manager
10 April 2026
File Name: Experience_Mistry.cpp
 
This file implements the core inheritance hierarchy: the base class
EscapeExperience and its three derived classes PuzzleRoom, MysteryRoom,
and AdventureRoom. EscapeExperience and PuzzleRoom manage dynamic memory
via char* data members and implement the Rule of Three. MysteryRoom and
AdventureRoom use std::string so their memory management is simpler.
*/
 
#include "Experience_Mistry.h"
#include <cstring>
#include <iostream>
 
using namespace std;

//Default constructor
EscapeExperience::EscapeExperience(void)
                 :room_name(nullptr), difficulty(""), time_limit(0),
                  max_players(0)
{
}


//Parameterized constructor: sets up a room with provided values
EscapeExperience::EscapeExperience(const char * a_room_name,
                                   const string & a_difficulty,
                                   int a_time_limit, int a_max_players)
                 :room_name(nullptr), difficulty(a_difficulty),
                  time_limit(a_time_limit), max_players(a_max_players)
{
    //Perform deep copy
    if (a_room_name)
    {
        room_name = new char[strlen(a_room_name) + 1];
        strcpy(room_name, a_room_name);
    }
}


//Copy constructor: deep copies char* from source
EscapeExperience::EscapeExperience(const EscapeExperience & source)
                 :room_name(nullptr), difficulty(source.difficulty),
                  time_limit(source.time_limit), max_players(source.max_players)
{
    //Deep copy so both objects have separate memory
    if (source.room_name)
    {
        room_name = new char[strlen(source.room_name) + 1];
        strcpy(room_name, source.room_name);
    }
}


//Assignment operator: copies source into an already existing object
EscapeExperience & EscapeExperience::operator=(const EscapeExperience & source)
{
    //Prevent self-assignment (e.g. room = room)
    if (this == &source)
    {
        return *this;
    }
 
    //Free existing memory before overwriting
    delete [] room_name;
    room_name = nullptr;
 
    //Deep copy the char* from source
    if (source.room_name)
    {
        room_name = new char[strlen(source.room_name) + 1];
        strcpy(room_name, source.room_name);
    }
 
    //Copy the non-dynamic members
    difficulty = source.difficulty;
    time_limit = source.time_limit;
    max_players = source.max_players;
 
    //Returns *this to allow chaining (a = b = c)
    return *this;
}
 
 
//Destructor: frees dynamically allocated room_name
EscapeExperience::~EscapeExperience(void)
{
    delete [] room_name;
    room_name = nullptr;
}
 
 
//Starts the experience, derived classes override for specific behavior
bool EscapeExperience::start_experience(void)
{
    if (!room_name)
    {
        return false;
    }
 
    cout << "Starting experience: " << room_name << endl;
    return true;
}
 
 
//Returns progress as a percentage
//Derived classes override with their own tracking
int EscapeExperience::check_progress(void) const
{
    return 0;
}
 
 
//Displays room info, derived classes call this then add their own
void EscapeExperience::display(void) const
{
    //Check if room_name has been set
    if (room_name)
    {
        cout << "Room: " << room_name << endl;
    }
    else
    {
        cout << "Room: [unnamed]" << endl;
    }
 
    cout << "Difficulty: " << difficulty << endl;
    cout << "Time Limit: " << time_limit << " minutes" << endl;
    cout << "Max Players: " << max_players << endl;
 
    return;
}
 
 
//Compares difficulty with another experience
//Maps string to numeric value for comparison
bool EscapeExperience::is_harder_than(const EscapeExperience & other) const
{
    //Convert this room's difficulty to a number
    int this_level = 0;
    int other_level = 0;
 
    if (difficulty == "easy")
    {
        this_level = 1;
    }
    else if (difficulty == "medium")
    {
        this_level = 2;
    }
    else if (difficulty == "hard")
    {
        this_level = 3;
    }
 
    //Convert the other room's difficulty to a number
    if (other.difficulty == "easy")
    {
        other_level = 1;
    }
    else if (other.difficulty == "medium")
    {
        other_level = 2;
    }
    else if (other.difficulty == "hard")
    {
        other_level = 3;
    }
 
    //Return true if this room is harder
    return this_level > other_level;
}
 
 
//Resets experience to initial state for replay
bool EscapeExperience::reset(void)
{
    if (!room_name)
    {
        return false;
    }
 
    cout << "Resetting experience: " << room_name << endl;
    return true;
}
 
 
//Extends time limit, returns new total
int EscapeExperience::extend_time(int additional_minutes)
{
    //Only add if value is positive
    if (additional_minutes > 0)
    {
        time_limit = time_limit + additional_minutes;
    }
 
    return time_limit;
}
 
 
//Puzzle Room - derived
//Default constructor: calls base default, sets puzzle data to safe values
PuzzleRoom::PuzzleRoom(void)
           :EscapeExperience(), puzzle_description(nullptr),
            num_puzzles(0), complexity(0)
{
}
 
 
//init list
PuzzleRoom::PuzzleRoom(const char * a_room_name, const string & a_difficulty,
                       int a_time_limit, int a_max_players,
                       const char * a_puzzle_description, int a_num_puzzles,
                       int a_complexity)
           :EscapeExperience(a_room_name, a_difficulty, a_time_limit, a_max_players),
            puzzle_description(nullptr), num_puzzles(a_num_puzzles),
            complexity(a_complexity)
{
    //Deep copy the puzzle description char*
    if (a_puzzle_description)
    {
        puzzle_description = new char[strlen(a_puzzle_description) + 1];
        strcpy(puzzle_description, a_puzzle_description);
    }
}
 
 
//Copy constructor: calls base copy constructor via init list
PuzzleRoom::PuzzleRoom(const PuzzleRoom & source)
           :EscapeExperience(source), puzzle_description(nullptr),
            num_puzzles(source.num_puzzles), complexity(source.complexity)
{
    //Deep copy puzzle_description separately from base data
    if (source.puzzle_description)
    {
        puzzle_description = new char[strlen(source.puzzle_description) + 1];
        strcpy(puzzle_description, source.puzzle_description);
    }
}
 
 
//Assignment operator: handles base data first, then puzzle data
PuzzleRoom & PuzzleRoom::operator=(const PuzzleRoom & source)
{
    //Self-assignment check
    if (this == &source)
    {
        return *this;
    }
    EscapeExperience::operator=(source);
 
    //Free old puzzle description before overwriting
    delete [] puzzle_description;
    puzzle_description = nullptr;
 
    //Deep copy the new puzzle description
    if (source.puzzle_description)
    {
        puzzle_description = new char[strlen(source.puzzle_description) + 1];
        strcpy(puzzle_description, source.puzzle_description);
    }
 
    //Copy the non-dynamic puzzle members
    num_puzzles = source.num_puzzles;
    complexity = source.complexity;
 
    return *this;
}
 
 
//Destructor: only frees PuzzleRoom's own char*
PuzzleRoom::~PuzzleRoom(void)
{
    delete [] puzzle_description;
    puzzle_description = nullptr;
}
 
 
//Starts puzzle experience by calling base start then adding puzzle info
bool PuzzleRoom::start_experience(void)
{
    //Call base version to display room name
    bool started = EscapeExperience::start_experience();
 
    if (!started)
    {
        return false;
    }
 
    //Display puzzle-specific startup info
    if (puzzle_description)
    {
        cout << "First puzzle: " << puzzle_description << endl;
    }
 
    cout << "Total puzzles to solve: " << num_puzzles << endl;
    return true;
}
 
 
//Returns percentage of puzzles solved
//Temp until solve tracking is added
int PuzzleRoom::check_progress(void) const
{
    //Avoid division by zero
    if (num_puzzles == 0)
    {
        return 0;
    }
 
    return 0;
}
 
 
//Displays base info first, then puzzle-specific details
void PuzzleRoom::display(void) const
{
    EscapeExperience::display();
 
    //Add puzzle-specific details
    if (puzzle_description)
    {
        cout << "Puzzle: " << puzzle_description << endl;
    }
 
    cout << "Number of Puzzles: " << num_puzzles << endl;
    cout << "Complexity: " << complexity << "/10" << endl;
 
    return;
}
 
 
//Attempts to solve the current puzzle with a given answer
bool PuzzleRoom::solve_puzzle(const string & answer)
{
    //Can't solve with an empty answer
    if (answer.empty())
    {
        return false;
    }
 
    cout << "Checking answer: " << answer << endl;
    return true;
}
 
 
//Returns a hint based on level (1 = vague, 3 = specific)
string PuzzleRoom::get_hint(int hint_level) const
{
    //Validate hint level range
    if (hint_level < 1 || hint_level > 3)
    {
        return "";
    }
 
    //Return increasingly specific hints
    if (hint_level == 1)
    {
        return "Look around carefully.";
    }
    else if (hint_level == 2)
    {
        return "Pay attention to the patterns.";
    }
 
    return "The answer is hidden in plain sight.";
}
 
 
//Increases complexity of remaining puzzles, capped at 10
int PuzzleRoom::increase_difficulty(int amount)
{
    //Only increase if amount is positive
    if (amount > 0)
    {
        complexity = complexity + amount;
 
        //Cap at maximum of 10
        if (complexity > 10)
        {
            complexity = 10;
        }
    }
 
    return complexity;
}
 

//Mystery Room - derived
//Default constructor: calls base default, initializes mystery data
MysteryRoom::MysteryRoom(void)
            :EscapeExperience(), theme(""), total_clues(0), num_suspects(0)
{
}
 
 
//Constructor: passes shared data to base via init list
MysteryRoom::MysteryRoom(const char * a_room_name, const string & a_difficulty,
                         int a_time_limit, int a_max_players,
                         const string & a_theme, int a_total_clues,
                         int a_num_suspects)
            :EscapeExperience(a_room_name, a_difficulty, a_time_limit, a_max_players),
             theme(a_theme), total_clues(a_total_clues), num_suspects(a_num_suspects)
{
}
 
 
//Copy constructor: calls base copy constructor to handle room_name
MysteryRoom::MysteryRoom(const MysteryRoom & source)
            :EscapeExperience(source), theme(source.theme),
             total_clues(source.total_clues), num_suspects(source.num_suspects)
{
}
 
 
//Assignment operator: lets base handle its data, then copies mystery data
MysteryRoom & MysteryRoom::operator=(const MysteryRoom & source)
{
    //Self-assignment check
    if (this == &source)
    {
        return *this;
    }
 
    //Base class handles room_name deep copy
    EscapeExperience::operator=(source);
 
    //Copy mystery-specific members (no dynamic memory here)
    theme = source.theme;
    total_clues = source.total_clues;
    num_suspects = source.num_suspects;
 
    return *this;
}
 
 
//Destructor: nothing to delete, MysteryRoom uses std::string
//Base destructor handles room_name cleanup automatically
MysteryRoom::~MysteryRoom(void)
{
}
 
 
//Starts the mystery by calling base start then showing theme info
bool MysteryRoom::start_experience(void)
{
    //Call base to display room name and check setup
    bool started = EscapeExperience::start_experience();
 
    if (!started)
    {
        return false;
    }
 
    //Display mystery-specific startup info
    cout << "Mystery theme: " << theme << endl;
    cout << "Clues to find: " << total_clues << endl;
    cout << "Suspects involved: " << num_suspects << endl;
    return true;
}
 
 
//Returns percentage of clues discovered
//Temp until clue tracking is implemented
int MysteryRoom::check_progress(void) const
{
    //Avoid division by zero
    if (total_clues == 0)
    {
        return 0;
    }
 
    return 0;
}
 
 
//Displays base room info then adds mystery details
void MysteryRoom::display(void) const
{
    //Let base class handle shared info
    EscapeExperience::display();
 
    //Add mystery-specific details
    cout << "Theme: " << theme << endl;
    cout << "Total Clues: " << total_clues << endl;
    cout << "Suspects: " << num_suspects << endl;
 
    return;
}
 
 
//Records a discovered clue during gameplay
int MysteryRoom::discover_clue(const string & clue_found)
{
    //Can't discover an empty clue
    if (clue_found.empty())
    {
        return 0;
    }
 
    cout << "Clue discovered: " << clue_found << endl;
 
    //Placeholder return, will track found count later
    return 1;
}
 
 
//Accuses a suspect, returns true if correct
bool MysteryRoom::accuse_suspect(const string & suspect_name) const
{
    //Can't accuse nobody
    if (suspect_name.empty())
    {
        return false;
    }
 
    cout << "Accusing: " << suspect_name << endl;
 
    //Temp, will compare against actual culprit later
    return true;
}
 
 
//Reveals narrative context based on detail level (1-3)
string MysteryRoom::reveal_narrative(int detail_level) const
{
    //Validate detail level range
    if (detail_level < 1 || detail_level > 3)
    {
        return "";
    }
 
    //Return increasingly detailed narrative
    if (detail_level == 1)
    {
        return "Something mysterious happened here.";
    }
    else if (detail_level == 2)
    {
        return "The clues point to someone on the inside.";
    }
 
    return "The key witness was last seen near the vault.";
}
 
 
//Adventure Room - derived
//Default constructor: calls base default, initializes adventure data
AdventureRoom::AdventureRoom(void)
              :EscapeExperience(), terrain_type(""), total_areas(0),
               discovery_count(0)
{
}
 
 
//constructor that passes shared data to base via init list
AdventureRoom::AdventureRoom(const char * a_room_name, const string & a_difficulty,
                             int a_time_limit, int a_max_players,
                             const string & a_terrain_type, int a_total_areas,
                             int a_discovery_count)
              :EscapeExperience(a_room_name, a_difficulty, a_time_limit, a_max_players),
               terrain_type(a_terrain_type), total_areas(a_total_areas),
               discovery_count(a_discovery_count)
{
}
 
 
//Copy constructor: calls base copy constructor to handle room_name
AdventureRoom::AdventureRoom(const AdventureRoom & source)
              :EscapeExperience(source), terrain_type(source.terrain_type),
               total_areas(source.total_areas),
               discovery_count(source.discovery_count)
{
}
 
 
//Assignment operator: lets base handle its data, then copies adventure data
AdventureRoom & AdventureRoom::operator=(const AdventureRoom & source)
{
    //Self-assignment check
    if (this == &source)
    {
        return *this;
    }
 
    //Base class handles room_name deep copy
    EscapeExperience::operator=(source);
 
    //Copy adventure-specific members (no dynamic memory here)
    terrain_type = source.terrain_type;
    total_areas = source.total_areas;
    discovery_count = source.discovery_count;
 
    return *this;
}
 
 
//Destructor: nothing to delete, AdventureRoom uses std::string
//Base destructor handles room_name cleanup automatically
AdventureRoom::~AdventureRoom(void)
{
}
 
 
//Starts the adventure by calling base start then showing terrain info
bool AdventureRoom::start_experience(void)
{
    //Call base to display room name and check setup
    bool started = EscapeExperience::start_experience();
 
    if (!started)
    {
        return false;
    }
 
    //Display adventure-specific startup info
    cout << "Terrain: " << terrain_type << endl;
    cout << "Areas to explore: " << total_areas << endl;
    return true;
}
 
 
//Returns percentage of areas explored
//Placeholder until area tracking is implemented
int AdventureRoom::check_progress(void) const
{
    //Avoid division by zero
    if (total_areas == 0)
    {
        return 0;
    }
 
    return 0;
}
 
 
//Displays base room info then adds adventure details
void AdventureRoom::display(void) const
{
    //Let base class handle shared info
    EscapeExperience::display();
 
    //Add adventure-specific details
    cout << "Terrain: " << terrain_type << endl;
    cout << "Total Areas: " << total_areas << endl;
    cout << "Discoveries: " << discovery_count << endl;
 
    return;
}
 
 
//Explores an area by name, returns true if successful
bool AdventureRoom::explore_area(const string & area_name)
{
    //Can't explore a nameless area
    if (area_name.empty())
    {
        return false;
    }
 
    cout << "Exploring: " << area_name << endl;
    return true;
}
 
 
//Logs a discovery and increments the count
int AdventureRoom::log_discovery(const string & discovery_description)
{
    //Can't log an empty discovery
    if (discovery_description.empty())
    {
        return discovery_count;
    }
 
    //Increment and display
    discovery_count = discovery_count + 1;
    cout << "Discovery logged: " << discovery_description << endl;
 
    return discovery_count;
}
 
 
//Checks if current terrain conditions are safe to continue
bool AdventureRoom::check_terrain_safety(void) const
{
    //Can't check safety without a terrain type
    if (terrain_type.empty())
    {
        return false;
    }
 
    cout << "Checking " << terrain_type << " conditions..." << endl;
    return true;
}