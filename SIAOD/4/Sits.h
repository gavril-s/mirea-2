#ifndef SITS_H
#define SITS_H

#define SMALL_ROOM_CAPACITY 100
#define BIG_ROOM_CAPACITY 1000
#define MAX_MOVIE_NAME_LENGTH 128

#include <stdlib.h>
#include <string.h>

enum Room
{
    none = 0,
    small = 1,
    big = 2
};

extern int RoomsCapacities[3];

struct Date
{
    int day;
    int month;
    int year;

    bool operator==(Date other);
};

struct Time
{
    int seconds;
    int minutes;
    int hours;

    bool operator==(Time other);
};

struct Sit
{
    char movie_name[MAX_MOVIE_NAME_LENGTH];
    Date date;
    Time time;
    int row;
    int place;
    int room;
};

struct Sits
{
    int size;
    int first_in_big_room;
    Sit* sits;

    Sits();
    ~Sits();
    void insert(Sit sit);
    void delete_by_date(Date date);
    int free_places(char movie_name[MAX_MOVIE_NAME_LENGTH], Date date, Time time);
};

#endif