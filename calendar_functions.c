#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calendar.h"

Event events[MAX_EVENTS];
int event_count = 0;
int next_id = 1;

void save_events()
{
    FILE *file = fopen(DATA_FILE, "w");
    if (file == NULL)
    {
        printf("Error saving file.\n");
        return;
    }

    fprintf(file, "%d\n%d\n", event_count, next_id);

    for (int i = 0; i < event_count; i++)
    {
        fprintf(file, "%d;%s;%s;%s;%s;%s;%s\n",
                events[i].id,
                events[i].title,
                events[i].date,
                events[i].start_time,
                events[i].end_time,
                events[i].location,
                events[i].note);
    }

    fclose(file);
}

void load_events()
{
    FILE *file = fopen(DATA_FILE, "r");
    if (file == NULL)
    {
        return;
    }

    fscanf(file, "%d\n%d\n", &event_count, &next_id);

    for (int i = 0; i < event_count; i++)
    {
        char line[500];

        fgets(line, sizeof(line), file);

        char *token = strtok(line, ";");
        events[i].id = atoi(token);

        token = strtok(NULL, ";");
        strcpy(events[i].title, token);

        token = strtok(NULL, ";");
        strcpy(events[i].date, token);

        token = strtok(NULL, ";");
        strcpy(events[i].start_time, token);

        token = strtok(NULL, ";");
        strcpy(events[i].end_time, token);

        token = strtok(NULL, ";");
        strcpy(events[i].location, token);

        token = strtok(NULL, ";\n");
        strcpy(events[i].note, token);
    }

    fclose(file);
}

void add_event()
{
    if (event_count >= MAX_EVENTS)
    {
        printf("Calendar is full.\n");
        return;
    }

    Event *e = &events[event_count];
    e->id = next_id++;

    printf("Enter event title: ");
    fgets(e->title, MAX_STRING, stdin);
    e->title[strcspn(e->title, "\n")] = 0;

    printf("Enter date (MM/DD/YYYY): ");
    fgets(e->date, MAX_STRING, stdin);
    e->date[strcspn(e->date, "\n")] = 0;

    printf("Enter start time: ");
    fgets(e->start_time, MAX_STRING, stdin);
    e->start_time[strcspn(e->start_time, "\n")] = 0;

    printf("Enter end time: ");
    fgets(e->end_time, MAX_STRING, stdin);
    e->end_time[strcspn(e->end_time, "\n")] = 0;

    printf("Enter location: ");
    fgets(e->location, MAX_STRING, stdin);
    e->location[strcspn(e->location, "\n")] = 0;

    printf("Enter note: ");
    fgets(e->note, MAX_STRING, stdin);
    e->note[strcspn(e->note, "\n")] = 0;

    event_count++;
    save_events();

    printf("Event added successfully. ID: %d\n", e->id);
}

void view_events()
{
    if (event_count == 0)
    {
        printf("No events found.\n");
        return;
    }

    printf("\n%-4s %-20s %-12s %-10s %-10s %-15s %-20s\n",
           "ID", "Title", "Date", "Start", "End", "Location", "Note");
    printf("-------------------------------------------------------------------------------\n");

    for (int i = 0; i < event_count; i++)
    {
        printf("%-4d %-20s %-12s %-10s %-10s %-15s %-20s\n",
               events[i].id,
               events[i].title,
               events[i].date,
               events[i].start_time,
               events[i].end_time,
               events[i].location,
               events[i].note);
    }
}

void update_event()
{
    if (event_count == 0)
    {
        printf("No events to update.\n");
        return;
    }

    int id;
    printf("Enter event ID to update: ");
    scanf("%d", &id);
    getchar();

    int found = -1;

    for (int i = 0; i < event_count; i++)
    {
        if (events[i].id == id)
        {
            found = i;
            break;
        }
    }

    if (found == -1)
    {
        printf("Event not found.\n");
        return;
    }

    Event *e = &events[found];
    char temp[MAX_STRING];

    printf("Current title: %s\n", e->title);
    printf("Enter new title (press Enter to keep current): ");
    fgets(temp, MAX_STRING, stdin);
    if (strcmp(temp, "\n") != 0)
    {
        temp[strcspn(temp, "\n")] = 0;
        strcpy(e->title, temp);
    }

    printf("Current date: %s\n", e->date);
    printf("Enter new date (press Enter to keep current): ");
    fgets(temp, MAX_STRING, stdin);
    if (strcmp(temp, "\n") != 0)
    {
        temp[strcspn(temp, "\n")] = 0;
        strcpy(e->date, temp);
    }

    printf("Current start time: %s\n", e->start_time);
    printf("Enter new start time (press Enter to keep current): ");
    fgets(temp, MAX_STRING, stdin);
    if (strcmp(temp, "\n") != 0)
    {
        temp[strcspn(temp, "\n")] = 0;
        strcpy(e->start_time, temp);
    }

    printf("Current end time: %s\n", e->end_time);
    printf("Enter new end time (press Enter to keep current): ");
    fgets(temp, MAX_STRING, stdin);
    if (strcmp(temp, "\n") != 0)
    {
        temp[strcspn(temp, "\n")] = 0;
        strcpy(e->end_time, temp);
    }

    printf("Current location: %s\n", e->location);
    printf("Enter new location (press Enter to keep current): ");
    fgets(temp, MAX_STRING, stdin);
    if (strcmp(temp, "\n") != 0)
    {
        temp[strcspn(temp, "\n")] = 0;
        strcpy(e->location, temp);
    }

    printf("Current note: %s\n", e->note);
    printf("Enter new note (press Enter to keep current): ");
    fgets(temp, MAX_STRING, stdin);
    if (strcmp(temp, "\n") != 0)
    {
        temp[strcspn(temp, "\n")] = 0;
        strcpy(e->note, temp);
    }

    save_events();
    printf("Event updated successfully.\n");
}

void delete_event()
{
    if (event_count == 0)
    {
        printf("No events to delete.\n");
        return;
    }

    int id;
    printf("Enter event ID to delete: ");
    scanf("%d", &id);
    getchar();

    int found = -1;

    for (int i = 0; i < event_count; i++)
    {
        if (events[i].id == id)
        {
            found = i;
            break;
        }
    }

    if (found == -1)
    {
        printf("Event not found.\n");
        return;
    }

    for (int i = found; i < event_count - 1; i++)
    {
        events[i] = events[i + 1];
    }

    event_count--;
    save_events();

    printf("Event deleted successfully.\n");
}

void search_events()
{
    if (event_count == 0)
    {
        printf("No events found.\n");
        return;
    }

    char search_term[MAX_STRING];
    int found = 0;

    printf("Enter search term: ");
    fgets(search_term, MAX_STRING, stdin);
    search_term[strcspn(search_term, "\n")] = 0;

    printf("\n%-4s %-20s %-12s %-10s %-10s %-15s %-20s\n",
           "ID", "Title", "Date", "Start", "End", "Location", "Note");
    printf("-------------------------------------------------------------------------------\n");

    for (int i = 0; i < event_count; i++)
    {
        if (strstr(events[i].title, search_term) ||
            strstr(events[i].date, search_term) ||
            strstr(events[i].location, search_term) ||
            strstr(events[i].note, search_term))
        {

            printf("%-4d %-20s %-12s %-10s %-10s %-15s %-20s\n",
                   events[i].id,
                   events[i].title,
                   events[i].date,
                   events[i].start_time,
                   events[i].end_time,
                   events[i].location,
                   events[i].note);
            found++;
        }
    }

    if (found == 0)
    {
        printf("No matching events found.\n");
    }
    else
    {
        printf("\nFound %d matching event(s).\n", found);
    }
}

void check_conflicts()
{
    if (event_count < 2)
    {
        printf("Not enough events to check for conflicts.\n");
        return;
    }

    int conflict_found = 0;

    for (int i = 0; i < event_count; i++)
    {
        for (int j = i + 1; j < event_count; j++)
        {
            if (strcmp(events[i].date, events[j].date) == 0)
            {
                if (strcmp(events[i].start_time, events[j].start_time) == 0)
                {
                    printf("Conflict found between Event ID %d and Event ID %d on %s at %s\n",
                           events[i].id, events[j].id, events[i].date, events[i].start_time);
                    conflict_found = 1;
                }
            }
        }
    }

    if (!conflict_found)
    {
        printf("No conflicts found.\n");
    }
}