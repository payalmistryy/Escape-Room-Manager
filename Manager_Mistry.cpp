/*
Payal Mistry
CS 302 - Programming Methodologies and Software Implementation
Assignment 1 - Escape Room Manager
18 April 2026
File Name: Manager_Mistry.cpp

This file implements the ChallengeNode and ChallengeList classes (a
linear linked list of active challenges), and the RoomManager class
which ties the application together. ChallengeList stores pointers to
EscapeExperience objects so it can hold any derived room type through
polymorphism. All repetitive list operations (add, remove by position,
display, remove-all, copy) are implemented recursively. RoomManager
owns the list of players (CLL), the list of active challenges (LLL),
an STL vector of special events, and the room's experience object, and
provides the menu-driven game host interface.
*/

#include "Manager_Mistry.h"
#include <string>

using namespace std;

//ChallengeNode Implementation
//Default constructor: no challenge, no next
ChallengeNode::ChallengeNode(void)
              :data(nullptr), next(nullptr)
{

}


//Data constructor: stores a pointer to an EscapeExperience
//ChallengeNode takes ownership of the pointer
ChallengeNode::ChallengeNode(EscapeExperience * a_challenge)
              :data(a_challenge), next(nullptr)
{

}


//Copy constructor: shallow copies the data pointer
ChallengeNode::ChallengeNode(const ChallengeNode & source)
              :data(source.data), next(nullptr)
{
    
}


//Destructor: which deletes the owned EscapeExperience
ChallengeNode::~ChallengeNode(void)
{
    delete data;
    data = nullptr;
    next = nullptr;
}


//Mutable reference access to next pointer so the list can rewire links
ChallengeNode *& ChallengeNode::get_next(void)
{
    return next;
}


//Const version: read-only access for const contexts
ChallengeNode * ChallengeNode::get_next(void) const
{
    return next;
}


//Mutable access to the stored challenge pointer
EscapeExperience * ChallengeNode::get_challenge(void)
{
    return data;
}


//Const version: read-only access for const contexts
const EscapeExperience * ChallengeNode::get_challenge(void) const
{
    return data;
}

//Challenge list
//Default constructor: empty LLL 
ChallengeList::ChallengeList(void)
              :head(nullptr), challenge_count(0)
{
}


//Copy constructor: deep-copies the source list's challenges
ChallengeList::ChallengeList(const ChallengeList & source)
              :head(nullptr), challenge_count(0)
{
    //Nothing to copy if source is empty
    if (source.head == nullptr)
    {
        return;
    }

    //Recursive deep copy 
    copy_list(source.head, head);
    challenge_count = source.challenge_count;
}


//Assignment operator - clears this list, then deep-copies from source
ChallengeList & ChallengeList::operator=(const ChallengeList & source)
{
    if (this == &source)
    {
        return *this;
    }

    //Release 
    remove_all();

    //If source is empty, leave empty
    if (source.head == nullptr)
    {
        return *this;
    }

    //Deep copy every node from source
    copy_list(source.head, head);
    challenge_count = source.challenge_count;
    return *this;
}


//Destructor frees every node
ChallengeList::~ChallengeList(void)
{
    remove_all();
}


//Adds a challenge at end of LLL, returns updated count
int ChallengeList::add_challenge(EscapeExperience * new_challenge)
{
    if (new_challenge == nullptr)
    {
        return challenge_count;
    }

    //Recursive append to the private helper
    challenge_count = add_challenge(head, new_challenge);
    return challenge_count;
}


//Recursive helper to add a challenge
int ChallengeList::add_challenge(ChallengeNode *& current,
                                 EscapeExperience * new_challenge)
{
    //Base case
    if (current == nullptr)
    {
        current = new ChallengeNode(new_challenge);
        return challenge_count + 1;
    }

    //Recursive case
    return add_challenge(current->get_next(), new_challenge);
}


//Removes the challenge at the given 1-based position
bool ChallengeList::remove_challenge(int position)
{
    bool removed = false;

    //Check position against current count
    if (position < 1 || position > challenge_count || head == nullptr)
    {
        return false;
    }

    //Recursive case
    removed = remove_challenge(head, position, 1);
    if (removed)
    {
        challenge_count = challenge_count - 1;
    }
    return removed;
}


//Recursive helper to help delink the challenge node
bool ChallengeList::remove_challenge(ChallengeNode *& current,
                                     int position, int current_pos)
{
    ChallengeNode * to_delete = nullptr;

    //Base case
    if (current == nullptr)
    {
        return false;
    }

    //Base case to start delete process
    if (current_pos == position)
    {
        to_delete = current;
        current = current->get_next();  
        delete to_delete;               //free
        return true;
    }

    //Recursive case
    return remove_challenge(current->get_next(), position, current_pos + 1);
}


//Returns the pointer to the front challenge, or null if empty
EscapeExperience * ChallengeList::get_current_challenge(void) const
{
    if (head == nullptr)
    {
        return nullptr;
    }

    return head->get_challenge();
}


//Displays every active challenge in order, returns count 
int ChallengeList::display_all(void) const
{
    if (head == nullptr)
    {
        cout << "No active challenges." << endl;
        return 0;
    }

    cout << "--- Active Challenges ---" << endl;
    return display_all(head);
}


//Recursive helper: prints each node's challenge info
int ChallengeList::display_all(ChallengeNode * current) const
{
    //Base case
    if (current == nullptr)
    {
        return 0;
    }

    //Display current node's challenge using polymorphic call
    if (current->get_challenge() != nullptr)
    {
        cout << "---" << endl;
        current->get_challenge()->display();
    }

    //Recursive case: 1 plus current plus the rest of the list
    return 1 + display_all(current->get_next());
}


//Removes every challenge from list, returns number removed
int ChallengeList::remove_all(void)
{
    int removed = 0;

    if (head == nullptr)
    {
        return 0;
    }

    removed = remove_all(head);
    challenge_count = 0;
    return removed;
}


//Recursive helper: deletes post order, then this node
int ChallengeList::remove_all(ChallengeNode *& current)
{
    int removed_below = 0;
    ChallengeNode * to_delete = nullptr;

    //Base case
    if (current == nullptr)
    {
        return 0;
    }

    //Recursive case
    removed_below = remove_all(current->get_next());

    //Deleting this node 
    to_delete = current;
    current = nullptr;
    delete to_delete;
    return 1 + removed_below;
}


//Removes the front challenge 
bool ChallengeList::solve_current(void)
{
    if (head == nullptr)
    {
        return false;
    }

    cout << "Solving current challenge..." << endl;
    return remove_challenge(1);
}


//Recursive helper: clones every EscapeExperience in source list into dest
void ChallengeList::copy_list(ChallengeNode * source, ChallengeNode *& dest)
{
    EscapeExperience * base_ptr = nullptr;
    EscapeExperience * cloned = nullptr;
    const PuzzleRoom * puzzle_src = nullptr;
    const MysteryRoom * mystery_src = nullptr;
    const AdventureRoom * adventure_src = nullptr;

    //Base case
    if (source == nullptr)
    {
        return;
    }

    //Clone challenge by down casting
    //dynamic_cast returns null if the cast is invalid
    base_ptr = const_cast<EscapeExperience *>(source->get_challenge());
    puzzle_src = dynamic_cast<const PuzzleRoom *>(base_ptr);
    if (puzzle_src != nullptr)
    {
        cloned = new PuzzleRoom(*puzzle_src);
    }
    else
    {
        mystery_src = dynamic_cast<const MysteryRoom *>(base_ptr);
        if (mystery_src != nullptr)
        {
            cloned = new MysteryRoom(*mystery_src);
        }
        else
        {
            adventure_src = dynamic_cast<const AdventureRoom *>(base_ptr);
            if (adventure_src != nullptr)
            {
                cloned = new AdventureRoom(*adventure_src);
            }
        }
    }

    //Wrap the clone in a new node at current position
    dest = new ChallengeNode(cloned);

    //Recursive case
    copy_list(source->get_next(), dest->get_next());
    return;
}


//Default constructor: everything is empty
RoomManager::RoomManager(void)
            :room(nullptr)
{
}


//Destructor: frees room object and event
RoomManager::~RoomManager(void)
{
    unsigned int index = 0;

    //Delete the current room experience
    delete room;
    room = nullptr;

    //Delete every scheduled special event 
    for (index = 0; index < special_events.size(); index = index + 1)
    {
        delete special_events[index];
        special_events[index] = nullptr;
    }
    special_events.clear();
}


//Sets the room experience, deleting any previous one first
bool RoomManager::setup_room(EscapeExperience * room_experience)
{
    if (room_experience == nullptr)
    {
        return false;
    }

    delete room;
    room = room_experience;
    return true;
}


//Creates and adds a new player with given name and role
int RoomManager::add_player(const string & name, const string & role)
{
    Player a_new_player(name, role, 0);
    return players.add_player(a_new_player);
}


//Removes a player by name from rotation
bool RoomManager::remove_player(const string & player_name)
{
    return players.remove_player(player_name);
}


//Advances the turn tracker, then displays who is up next
bool RoomManager::next_turn(void)
{
    bool advanced = false;

    advanced = players.advance_turn();
    if (advanced)
    {
        players.display_current();
    }
    return advanced;
}


//Adds a challenge to sequence 
int RoomManager::add_challenge(EscapeExperience * challenge)
{
    return challenges.add_challenge(challenge);
}


//Removes the current front challenge 
bool RoomManager::solve_challenge(void)
{
    return challenges.solve_current();
}


//Schedules a special event by appending it to vector
int RoomManager::schedule_event(EscapeExperience * event)
{
    if (event == nullptr)
    {
        return static_cast<int>(special_events.size());
    }

    special_events.push_back(event);
    return static_cast<int>(special_events.size());
}


//Triggers a special event at the given 0-based index
bool RoomManager::trigger_event(int event_index)
{
    EscapeExperience * triggered = nullptr;

    //Validate index
    if (event_index < 0
        || event_index >= static_cast<int>(special_events.size()))
    {
        return false;
    }

    //Run the event
    triggered = special_events[event_index];
    cout << "\n*** Triggering Special Event ***" << endl;
    triggered->start_experience();

    //Remove from vector
    delete triggered;
    special_events.erase(special_events.begin() + event_index);
    return true;
}


//Displays the current state of the escape room
void RoomManager::display_room_state(void) const
{
    unsigned int index = 0;

    cout << "\n--Escape Room State--" << endl;

    //Room experience
    cout << "\n[Room Experience]" << endl;
    if (room == nullptr)
    {
        cout << "No room has been set up yet." << endl;
    }
    else
    {
        room->display();
    }

    //Players
    cout << "\n[Players]" << endl;
    players.display_all();
    players.display_current();

    //Active challenges
    cout << "\n[Active Challenges]" << endl;
    challenges.display_all();

    //Special events 
    cout << "\n[Scheduled Special Events: "
         << special_events.size() << "]" << endl;
    for (index = 0; index < special_events.size(); index = index + 1)
    {
        cout << "Event #" << index << ":" << endl;
        special_events[index]->display();
    }

    cout << "-----------------------------------\n" << endl;
    return;
}


//Helper that prints the menu locally
static void print_menu(void)
{
    cout << "\n-----Escape Room Menu-----" << endl;
    cout << "1.  Set up the room experience" << endl;
    cout << "2.  Add a player to rotation" << endl;
    cout << "3.  Remove a player from rotation" << endl;
    cout << "4.  Advance to next player's turn" << endl;
    cout << "5.  Show current player" << endl;
    cout << "6.  Display all players" << endl;
    cout << "7.  Add an active challenge" << endl;
    cout << "8.  Solve current challenge" << endl;
    cout << "9.  Display active challenges" << endl;
    cout << "10. Schedule a special event" << endl;
    cout << "11. Trigger a special event by index" << endl;
    cout << "12. Display full room state" << endl;
    cout << "13. Clear everything" << endl;
    cout << "14.  Quit" << endl;
    cout << "Choice: ";
    return;
}


//Helper: creates an EscapeExperience based on user's type selection
static EscapeExperience * build_experience(void)
{
    int type_choice = 0;
    string room_name = "";
    string difficulty = "";
    int time_limit = 0;
    int max_players = 0;
    string extra_string = "";
    int extra_int_1 = 0;
    int extra_int_2 = 0;
    EscapeExperience * built = nullptr;

    //get info
    cout << "Experience type: 1=Puzzle  2=Mystery  3=Adventure: ";
    cin >> type_choice;
    cin.ignore(100, '\n');

    cout << "Room name: ";
    getline(cin, room_name);
    cout << "Difficulty (easy/medium/hard): ";
    getline(cin, difficulty);
    cout << "Time limit (minutes): ";
    cin >> time_limit;
    cout << "Max players: ";
    cin >> max_players;
    cin.ignore(100, '\n');

    if (type_choice == 1)
    {
        cout << "Puzzle description: ";
        getline(cin, extra_string);
        cout << "Number of puzzles: ";
        cin >> extra_int_1;
        cout << "Complexity (1-10): ";
        cin >> extra_int_2;
        cin.ignore(100, '\n');
        built = new PuzzleRoom(room_name.c_str(), difficulty, time_limit,
                               max_players, extra_string.c_str(),
                               extra_int_1, extra_int_2);
    }
    else if (type_choice == 2)
    {
        cout << "Mystery theme: ";
        getline(cin, extra_string);
        cout << "Total clues: ";
        cin >> extra_int_1;
        cout << "Number of suspects: ";
        cin >> extra_int_2;
        cin.ignore(100, '\n');
        built = new MysteryRoom(room_name.c_str(), difficulty, time_limit,
                                max_players, extra_string,
                                extra_int_1, extra_int_2);
    }
    else if (type_choice == 3)
    {
        cout << "Terrain type: ";
        getline(cin, extra_string);
        cout << "Total areas: ";
        cin >> extra_int_1;
        cout << "Starting discovery count: ";
        cin >> extra_int_2;
        cin.ignore(100, '\n');
        built = new AdventureRoom(room_name.c_str(), difficulty, time_limit,
                                  max_players, extra_string,
                                  extra_int_1, extra_int_2);
    }
    else
    {
        cout << "Invalid type selection." << endl;
    }

    return built;
}


//Main menu loop - returns 0 on clean exit
int RoomManager::run(void)
{
    int choice = -1;
    string name_buffer = "";
    string role_buffer = "";
    int index_buffer = 0;
    EscapeExperience * built = nullptr;

    cout << "\n~~~ Welcome to the Escape Room Manager ~~~\n" << endl;

    print_menu();
    cin >> choice;
    cin.ignore(100, '\n');

    //Loop until user chooses 14 to quit
    while (choice != 14)
    {
        if (choice == 1)
        {
            built = build_experience();
            if (built != nullptr && setup_room(built))
            {
                cout << "Room experience set." << endl;
            }
        }
        else if (choice == 2)
        {
            cout << "Player name: ";
            getline(cin, name_buffer);
            cout << "Player role: ";
            getline(cin, role_buffer);
            cout << "Total players now: "
                 << add_player(name_buffer, role_buffer) << endl;
        }
        else if (choice == 3)
        {
            cout << "Name of player to remove: ";
            getline(cin, name_buffer);
            if (remove_player(name_buffer))
            {
                cout << "Removed." << endl;
            }
            else
            {
                cout << "No player with that name." << endl;
            }
        }
        else if (choice == 4)
        {
            if (!next_turn())
            {
                cout << "No players in rotation." << endl;
            }
        }
        else if (choice == 5)
        {
            players.display_current();
        }
        else if (choice == 6)
        {
            players.display_all();
        }
        else if (choice == 7)
        {
            built = build_experience();
            if (built != nullptr)
            {
                cout << "Total active challenges: "
                     << add_challenge(built) << endl;
            }
        }
        else if (choice == 8)
        {
            if (!solve_challenge())
            {
                cout << "No active challenges to solve." << endl;
            }
        }
        else if (choice == 9)
        {
            challenges.display_all();
        }
        else if (choice == 10)
        {
            built = build_experience();
            if (built != nullptr)
            {
                cout << "Scheduled. Total events: "
                     << schedule_event(built) << endl;
            }
        }
        else if (choice == 11)
        {
            cout << "Event index to trigger: ";
            cin >> index_buffer;
            cin.ignore(100, '\n');
            if (!trigger_event(index_buffer))
            {
                cout << "Invalid index." << endl;
            }
        }
        else if (choice == 12)
        {
            display_room_state();
        }
        else if (choice == 13)
        {
            players.remove_all();
            challenges.remove_all();
            cout << "All players and challenges cleared." << endl;
        }
        else
        {
            cout << "Invalid choice." << endl;
        }

        print_menu();
        cin >> choice;
        cin.ignore(100, '\n');
    }

    //goodbye message
    cout << "Goodbye!" << endl;
    return 0;
}
