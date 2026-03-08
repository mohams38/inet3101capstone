#ifndef CALENDAR_H
#define CALENDAR_H

#define MAX_EVENTS 100
#define MAX_STRING 100
#define DATA_FILE "calendar_data.txt"

typedef struct
{
    int id;
    char title[MAX_STRING];
    char date[MAX_STRING];
    char start_time[MAX_STRING];
    char end_time[MAX_STRING];
    char location[MAX_STRING];
    char note[MAX_STRING];
} Event;

extern Event events[MAX_EVENTS];
extern int event_count;
extern int next_id;

void save_events();
void load_events();
void add_event();
void view_events();
void update_event();
void delete_event();
void search_events();
void check_conflicts();

#endif