/*
Payal Mistry
CS 302 - Programming Methodologies and Software Implementation
Assignment 1 - Escape Room Manager
17 April 2026
File Name: Player_Mistry.cpp

This file implements the Player, PlayerNode, and PlayerList classes.
Player holds a single participant's data (name, role, score).
PlayerNode wraps a Player so it can live in the circular linked list.
PlayerList owns the CLL that rotates turns among the players. All
repetitive operations (display, remove by name, retrieve, remove-all,
copy) are implemented recursively. The CLL uses a rear pointer, so
the first node is always rear->next.
*/

#include "Player_Mistry.h"

using namespace std;

//Player Implementation
//Default constructor: empty name and role, score set to zero
Player::Player(void)
       :name(""), role(""), score(0)
{

}


//Constructor: builds a player with provided values
Player::Player(const string & a_name, const string & a_role, int a_score)
       :name(a_name), role(a_role), score(a_score)
{

}


//Displays player's name, role, and score 
void Player::display(void) const
{
    cout << "Player: " << name
         << " | Role: " << role
         << " | Score: " << score << endl;

    return;
}


//Adds points (only if positive) and returns the new total
int Player::add_points(int points_earned)
{
    if (points_earned > 0)
    {
        score = score + points_earned;
    }

    //return updated score
    return score;
}


//Changes the player's role, returns false if given empty string
bool Player::change_role(const string & new_role)
{
    //Reject empty roles
    if (new_role.empty())
    {
        return false;
    }

    role = new_role;
    return true;
}


//Returns true if this player's name matches the given name
bool Player::matches_name(const string & name_to_match) const
{
    return (name == name_to_match);
}


//PlayerNode Implementation
//Default constructor: empty player
PlayerNode::PlayerNode(void)
           :data(), next(nullptr)
{
}


//Data constructor: wraps an existing Player
PlayerNode::PlayerNode(const Player & a_player)
           :data(a_player), next(nullptr)
{
}


//Copy constructor: copies data only
PlayerNode::PlayerNode(const PlayerNode & source)
           :data(source.data), next(nullptr)
{
}


//Destructor: does not delete next, PlayerList owns the chain
PlayerNode::~PlayerNode(void)
{
    next = nullptr;
}


//Returns a reference to the next pointer so callers can rewire links
PlayerNode *& PlayerNode::get_next(void)
{
    return next;
}


//Const version: read-only access to next for const contexts
PlayerNode * PlayerNode::get_next(void) const
{
    return next;
}


//Returns a reference to the stored Player (mutable)
Player & PlayerNode::get_player(void)
{
    return data;
}


//Const version: read-only access for const contexts
const Player & PlayerNode::get_player(void) const
{
    return data;
}


//PlayerList Implementation
//Default constructor: empty CLL with no rear and no current turn
PlayerList::PlayerList(void)
           :rear(nullptr), current(nullptr), player_count(0)
{
}


//Copy constructor: deep copies every node from source's CLL
PlayerList::PlayerList(const PlayerList & source)
           :rear(nullptr), current(nullptr), player_count(0)
{
    if (source.rear == nullptr)
    {
        return;
    }

    //Recursively copy 
    copy_list(source.rear->get_next(), source.rear, rear);

    //Match source's count
    player_count = source.player_count;
    current = rear->get_next();
}


//Assignment operator releases existing list, then deep-copies source
PlayerList & PlayerList::operator=(const PlayerList & source)
{
    if (this == &source)
    {
        return *this;
    }

    //Wipe out current contents before overwriting
    remove_all();

    if (source.rear == nullptr)     //nothing to copy
    {
        return *this;
    }

    //Recursive deep copy
    copy_list(source.rear->get_next(), source.rear, rear);
    player_count = source.player_count;
    current = rear->get_next();

    return *this;
}


//Destructor: frees every node 
PlayerList::~PlayerList(void)
{
    remove_all();
}


//Adds a player at the rear of the CLL 
int PlayerList::add_player(const Player & new_player)
{
    PlayerNode * new_node = new PlayerNode(new_player);

    //Empty list
    if (rear == nullptr)
    {
        new_node->get_next() = new_node;
        rear = new_node;
        current = new_node;
    }
    else
    {
        //Link new node after rear, making it the new rear
        new_node->get_next() = rear->get_next();
        rear->get_next() = new_node;
        rear = new_node;
    }

    player_count = player_count + 1;
    return player_count;
}


//Removes a player by name, returns true if a matching node was found
bool PlayerList::remove_player(const string & player_name)
{
    bool removed = false;
    PlayerNode * to_delete = nullptr;
    PlayerNode * prev_of_rear = nullptr;

    //Empty list
    if (rear == nullptr)
    {
        return false;
    }

    //Only the rear exists
    if (rear == rear->get_next())
    {
        if (rear->get_player().matches_name(player_name))
        {
            delete rear;
            rear = nullptr;
            current = nullptr;
            player_count = 0;
            removed = true;
        }
        return removed;
    }

    //Special case: rear is the match, pointer update
    if (rear->get_player().matches_name(player_name))
    {
        to_delete = rear;
        prev_of_rear = find_prev_of_rear(rear->get_next(), rear);

        //Previous becomes new rear, its next points to old first
        prev_of_rear->get_next() = rear->get_next();
        rear = prev_of_rear;

        //If turn tracker pointed to the deleted node
        if (current == to_delete)
        {
            current = rear->get_next();
        }
        delete to_delete;
        player_count = player_count - 1;
        return true;
    }

    //Rear does not match, recursive removal of a middle node
    if (current != nullptr && current->get_player().matches_name(player_name))
    {
        current = current->get_next();
    }
    removed = remove_player(rear->get_next(), player_name, rear);
    if (removed)
    {
        player_count = player_count - 1;
    }
    return removed;
}


//Recursive helper traverses from first node toward rear exclusively
bool PlayerList::remove_player(PlayerNode *& current_ptr,
                               const string & player_name,
                               PlayerNode * rear_ptr)
{
    PlayerNode * to_delete = nullptr;

    //Base case, walked all the way to rear without finding a match
    if (current_ptr == rear_ptr)
    {
        return false;
    }

    //This node matches - unlink and delete
    if (current_ptr->get_player().matches_name(player_name))
    {
        to_delete = current_ptr;
        //Reassigning 
        current_ptr = current_ptr->get_next();
        delete to_delete;
        return true;
    }

    //Recursive case
    return remove_player(current_ptr->get_next(), player_name, rear_ptr);
}


//Advances turn to the next player in rotation
bool PlayerList::advance_turn(void)
{
    if (current == nullptr)
    {
        return false;
    }

    current = current->get_next();
    return true;
}


//Copies the matching player's data into found_player if it exists
bool PlayerList::retrieve_player(const string & player_name,
                                 Player & found_player) const
{
    if (rear == nullptr)
    {
        return false;
    }

    return retrieve_player(rear->get_next(), player_name, found_player, rear);
}


//Recursive helper: walks until rear (inclusive) looking for the name
bool PlayerList::retrieve_player(PlayerNode * current_ptr,
                                 const string & player_name,
                                 Player & found_player,
                                 PlayerNode * rear_ptr) const
{
    //Check current node
    if (current_ptr->get_player().matches_name(player_name))
    {
        found_player = current_ptr->get_player();
        return true;
    }

    //Base case, reached rear without a match
    if (current_ptr == rear_ptr)
    {
        return false;
    }

    //Recursive case
    return retrieve_player(current_ptr->get_next(), player_name,
                           found_player, rear_ptr);
}


//Displays every player in turn-rotation order, returns count shown
int PlayerList::display_all(void) const
{
    if (rear == nullptr)
    {
        cout << "No players in the rotation." << endl;
        return 0;
    }

    cout << "--- Players (in turn order) ---" << endl;
    return display_all(rear->get_next(), rear);
}


//Recursive helper: displays each node once inclusively
int PlayerList::display_all(PlayerNode * current_ptr,
                            PlayerNode * rear_ptr) const
{
    //Display current node 
    current_ptr->get_player().display();

    //Base case
    if (current_ptr == rear_ptr)
    {
        return 1;
    }

    //Recursive case
    return 1 + display_all(current_ptr->get_next(), rear_ptr);
}


//Removes every player from the list, returns number removed
int PlayerList::remove_all(void)
{
    int removed = 0;

    if (rear == nullptr)
    {
        return 0;
    }

    removed = remove_all(rear->get_next(), rear);

    //Reset all list state to empty
    rear = nullptr;
    current = nullptr;
    player_count = 0;
    return removed;
}


//Recursive helper: deletes current node recursively
int PlayerList::remove_all(PlayerNode *& current_ptr, PlayerNode * rear_ptr)
{
    PlayerNode * to_delete = current_ptr;
    PlayerNode * next_saved = current_ptr->get_next();

    //Base case
    if (current_ptr == rear_ptr)
    {
        delete to_delete;
        return 1;
    }

    delete to_delete;
    return 1 + remove_all(next_saved, rear_ptr);
}


//Displays who is currently taking their turn
bool PlayerList::display_current(void) const
{
    if (current == nullptr)
    {
        cout << "No current player - the rotation is empty." << endl;
        return false;
    }
    
    //print current turn
    cout << "Current turn: ";
    current->get_player().display();
    return true;
}


//Recursive helper: copies every node from source into destination CLL
void PlayerList::copy_list(PlayerNode * source_current,
                           PlayerNode * source_rear,
                           PlayerNode *& dest_rear)
{
    PlayerNode * new_node = nullptr;

    if (source_current == nullptr)
    {
        return;
    }

    //Allocating new node holding the same player
    new_node = new PlayerNode(source_current->get_player());

    if (dest_rear == nullptr)
    {
        //First node in destination
        new_node->get_next() = new_node;
        dest_rear = new_node;
    }
    else
    {
        //Insert at rear
        new_node->get_next() = dest_rear->get_next();
        dest_rear->get_next() = new_node;
        dest_rear = new_node;
    }

    //Base case
    if (source_current == source_rear)
    {
        return;
    }

    //Recursive case
    copy_list(source_current->get_next(), source_rear, dest_rear);
    return;
}


//Recursive helper: returns the node whose next pointer equals rear
PlayerNode * PlayerList::find_prev_of_rear(PlayerNode * current_ptr,
                                           PlayerNode * rear_ptr) const
{
    //Base case
    if (current_ptr->get_next() == rear_ptr)
    {
        return current_ptr;
    }

    //Recursive case
    return find_prev_of_rear(current_ptr->get_next(), rear_ptr);
}
