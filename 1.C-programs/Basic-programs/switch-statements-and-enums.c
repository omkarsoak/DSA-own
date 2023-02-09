#include <stdio.h>
#include <stdlib.h>

int main()
{
    enum weekday {Sunday,Monday,Tuesday,Wednesday,Thursday,Friday,Saturday};
    enum weekday today;
    today = Monday;
    switch (today)
    {
        case Sunday:
        printf("today is sunday");
        break;
        case Monday:
        printf("today is monday");
        break;
        case Tuesday:
        printf("today is tuesday");
        break;
        case Wednesday:
        printf("today is wednesday");
        break;
        case Thursday:
        printf("today is thursday");
        break;
        case Friday:
        printf("today is friday");
        break;
        case Saturday:
        printf("today is saturday");
        break;
        default:
        printf("get lost");

    }

    return 0;
}
