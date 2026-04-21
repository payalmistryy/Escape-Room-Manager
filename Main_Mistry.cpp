/*
Payal Mistry
CS 302 - Programming Methodologies and Software Implementation
Assignment 1 - Escape Room Manager
18 April 2026
File Name: Main_Mistry.cpp

This file provides the entry point for the Escape Room Manager. It
constructs a RoomManager and hands control to its menu-driven run()
loop, which exercises every member function of the core hierarchy
through the game-host application.
*/

#include "Manager_Mistry.h"


//Entry point of the escape room manager
int main(void)
{
    RoomManager the_manager;

    the_manager.run();
    return 0;
}
