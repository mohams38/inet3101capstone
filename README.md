# Calendar Management System

This project is a basic calendar management system made in C. The program lets users add, view, update, delete, and search for events. It also saves the event data to a text file so the information is still there when the program is opened again.

## Problem Statement

The problem this project solves is keeping track of events in a simple way. Instead of writing things down manually, the user can store events in the program and manage them through a menu.

## Features

- Add a new event
- View all events
- Update an event
- Delete an event
- Search for events
- Check for simple conflicts
- Save events to a file
- Load events from a file

## File Structure

- `main.c` - runs the program and shows the menu
- `calendar.h` - has the struct, constants, and function declarations
- `calendar_functions.c` - has the main functions for the program
- `Makefile` - compiles the program
- `calendar_data.txt` - stores the event data

## Event Fields

Each event has:
- ID
- Title
- Date
- Start time
- End time
- Location
- Note

## Menu

```text
   Calendar Management System
1. Add Event
2. View Events
3. Update Event
4. Delete Event
5. Search Events
6. Check Conflicts
0. Exit

Design Details

I kept this project simple and split it into a few files so it would be easier to follow. The program uses a struct for each event and an array to store the events in memory while the program is running. It uses file I/O to save the events into a text file and load them back in when the program starts again

Pros and Cons 

Pros
    Simple and easy to use
    Uses basic C concepts from class
    Data saves after closing the program
    Organized into separate files

Cons
    Limited to a maximum number of events
    Have to remeber which id it is 

Future Improvements

If I kept working on it I would probably improve the conflict checking, make the search better, add more event details
