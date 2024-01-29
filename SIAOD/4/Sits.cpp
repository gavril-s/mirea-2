#include "Sits.h"

int RoomsCapacities[3] = {
    0,
    SMALL_ROOM_CAPACITY,
    BIG_ROOM_CAPACITY
};

bool Date::operator==(Date other)
{
    return (this->day   == other.day   &&
            this->month == other.month &&
            this->year  == other.year);
}

bool Time::operator==(Time other)
{
    return (this->hours   == other.hours   &&
            this->minutes == other.minutes &&
            this->seconds == other.seconds);
}

Sits::Sits()
{
    size = 0;
    first_in_big_room = 0;
    sits = nullptr;
}

Sits::~Sits()
{
    free(sits);
}

void Sits::insert(Sit sit)
{
    if (size == 0)
    {
        sits = (Sit*) malloc(sizeof(*sits) * (size + 1));
    }
    else
    {
        sits = (Sit*) realloc(sits, sizeof(*sits) * (size + 1));
    }
    size++;

    if (sit.room == Room::big)
    {
        for (int i = size - 1; i > first_in_big_room; i--)
        {
            sits[i] = sits[i - 1];
        }
        sits[first_in_big_room] = sit;
    }
    else if (sit.room == Room::small)
    {
        for (int i = size - 1; i > 0; i--)
        {
            sits[i] = sits[i - 1];
        }
        first_in_big_room++;
        sits[0] = sit;
    }
}

void Sits::delete_by_date(Date date)
{
    for (int i = 0; i < size; i++)
    {
        if (sits[i].date == date)
        {
            for (int j = i; j < size; j++)
            {
                sits[j] = sits[j + 1];
            }

            sits = (Sit*) realloc(sits, sizeof(*sits) * (size - 1));
            size--;
            if (i < first_in_big_room)
            {
                first_in_big_room--;
            }

            i--;
        }
    }
}

int Sits::free_places(char movie_name[MAX_MOVIE_NAME_LENGTH], Date date, Time time)
{
    int not_free = 0;

    for (int i = 0; i < size; i++)
    {
        if (strcmp(sits[i].movie_name, movie_name) == 0&&
            sits[i].date == date &&
            sits[i].time == time)
        {
            not_free++;
        }
    }

    return RoomsCapacities[Room::small] +
           RoomsCapacities[Room::big] - not_free;
}