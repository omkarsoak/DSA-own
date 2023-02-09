/*This program contains hard coded data of rainfall(in mm) for the years 2015-19
This program will calculate:-
the total rainfall for each year
the yearly average rainfall for all years combined
the monthly average rainfall for each month*/

#include <stdio.h>
#include <stdlib.h>

//constants declared here using #define
#define YEARS 5
#define MONTHS 12

int main()
{
    //declaring array
    //rows correspond to YEARS and columns to MONTHS
    //initializing rainfall data(in mm) for years 2015-19
   float rainfall[YEARS][MONTHS] =
                             {
                                 {25,34,45,56,67,66,45,33,45,66,12,55},
                                 {34,35,65,57,87,12,42,32,75,56,16,25},
                                 {23,64,46,66,69,06,40,83,49,26,72,85},
                                 {25,33,65,76,27,56,38,76,89,12,12,27},
                                 {86,57,78,45,78,99,45,12,21,63,12,84}
                             };
   int year,month;
   float yearly_total,all_years_total;

   //Calculating total rainfall for each year

   printf("YEAR \t\t YEARLY RAINFALL(in mm) \n");

    for (year=0,all_years_total=0; year<YEARS; year++)
    {
        for (month=0,yearly_total=0; month<MONTHS; month++)
        {
            yearly_total = yearly_total + rainfall[year][month];
        }

        printf("%d \t\t %.2f \n", 2015 + year,yearly_total);

        all_years_total = all_years_total + yearly_total;
    }

    printf("\nThe yearly average is: %.2f\n",all_years_total/YEARS);

    //Calculating monthly averages

    printf("\nMONTHLY AVERAGES\n\n");
    printf("JAN   FEB   MAR   APR   MAY   JUN   JUL   AUG   SEP   OCT   NOV   DEC\n");
    float monthly_total;

    for (month=0,monthly_total=0; month < MONTHS; month++)
    {
        for (year=0; year < YEARS; year++)
        {
            monthly_total = monthly_total + rainfall[year][month];
        }
    printf("%.1f ",monthly_total/YEARS);
    }
     printf("\n");
    return 0;
}
