/*
 * Exercise 5-9. Rewrite the routines day_of_year and month_day
 * with pointers instead of indexing.
 */


#include <stdio.h> 
static char daytab[][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year:  set day of year from month & day */
int day_of_year(int year, int month, int day)
{
	int i, leap;
	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

	/* error checking */

	if ( year < 0 || month > 12 || month < 1  || day < 1 || day > *((*(daytab+leap))+month)) {
		/* invalid input */
		return 0;
	}

	for (i = 1; i < month; i++)
		day += *((*(daytab+leap))+i);
	return day;
}

/* month_day:  set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;
	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

	if ( year < 0 || yearday < 1 || yearday >= (leap?366:365) ) {
		/* invalid input */
		*pmonth = 0;
		*pday = 0;
		return;
	}

	for (i = 1; yearday > *((*(daytab+leap))+i); i++)
		yearday -= *((*(daytab+leap))+i);

	*pmonth = i;
	*pday = yearday;
}



int main() {

	int year = 1983;
	int month = 03;
	int day = 19;

	int yearday;
	
	printf ("day_of_year(%d, %2d, %2d) = %d\n",
		year, month, day,
		yearday = day_of_year(year, month, day));

	month_day(year,yearday, &month, &day);
	printf ("month_day(%4d, %d) month = %2d, day = %2d\n", year, yearday, month, day );


	return 0;
}
