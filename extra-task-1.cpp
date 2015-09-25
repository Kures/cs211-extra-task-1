#include<iostream>
#include<cassert> 
#include<cmath> 


//Return the number of seconds later that a time in seconds
//time_2 is than a time in seconds time_1.
double seconds_difference(double time_1, double time_2)
{
	return time_2 - time_1;	
}

//Return the number of hours later that a time in seconds
//time_2 is than a time in seconds time_1.
double hours_difference(double time_1, double time_2)
{
	return seconds_difference(time_1, time_2) / 3600;
}

//Return the total number of hours in the specified number
//of hours, minutes, and seconds.
double to_float_hours(int hours, int minutes, int seconds)
{
	return hours_difference(0, hours * 3600 + minutes * 60 + seconds) ;	
}

//hours is a number of hours since midnight.Return the
//hour as seen on a 24 - hour clock.
double to_24_hour_clock(double hours)
{
	double x = hours;
	while (x >= 24.0)
		x -= 24;
	return x;
}



double get_hours(double seconds)
{
	int x = seconds;
	while (x >= 24 * 3600)
		x -= 24 * 3600;
	return x / 3600;
}


double get_minutes(double seconds)
{
	int x = seconds;
	int y = get_hours(seconds);
	return (x - 3600 * y) / 60;
}

double get_seconds(double seconds)
{
	return seconds - get_hours(seconds) * 3600 - get_minutes(seconds) * 60;
}

//Return time at UTC + 0, where utc_offset is the number of hours away from
//UTC + 0.
double time_to_utc(int utc_offset, double time)
{
	double x;
	if (utc_offset > 0.00001)
		x = time - abs(utc_offset);
	else 
	if (utc_offset < 0.00001)
		x = time + abs(utc_offset);

	while (x >=  24)
		x -= 24;

	return abs(x);	
}

//Return UTC time in time zone utc_offset.
double time_from_utc(int utc_offset, double time)
{
	double x;
	if (utc_offset > 0.00001)
		x = time + abs(utc_offset);
	else
	if (utc_offset < 0.00001)
		x = time - abs(utc_offset);

	while (x <= 0)
		x += 24;
	if (abs(x - 24.0) < 0.00001)
		x = 0.0;
	return abs(x);
	
}



using namespace std;

int main()
{
	setlocale(0, "Russian");

	cout << "Начало теста seconds_difference." << endl;
	assert(seconds_difference(1800.0, 3600.0) == 1800.0, "Test 1.");
	assert(seconds_difference(3600.0, 1800.0) == -1800.0, "Test 2.");
	assert(seconds_difference(1800.0, 1800.0) == 0.0, "Test 3.");
	cout << "Тест seconds_difference пройден." << endl;

	cout << "Начало теста hours_difference." << endl;
	assert(hours_difference(1800.0, 3600.0) == 0.5, "Test 1.");
	assert(hours_difference(3600.0, 1800.0) == -0.5, "Test 2.");
	assert(hours_difference(1800.0, 1800.0) == 0, "Test 3.");
	assert(hours_difference(1800.0, 2160.0) == 0.1, "Test 4.");
	cout << "Тест hours_difference пройден." << endl;	

	cout << "Начало теста to_float_hours." << endl;
	assert(to_float_hours(0, 15, 0) == 0.25, "Test 1.");
	assert(to_float_hours(2, 45, 9) == 2.7525, "Test 2.");
	assert(to_float_hours(1, 0, 36) == 1.01, "Test 3.");
	cout << "Тест to_float_hours пройден." << endl;

	cout << "Начало теста to_24_hour_clock." << endl;
	assert(to_24_hour_clock(24) == 0.0, "Test 1.");
	assert(to_24_hour_clock(48) == 0.0, "Test 2.");
	assert(to_24_hour_clock(25) == 1.0, "Test 3.");
	assert(to_24_hour_clock(4) == 4.0, "Test 4.");
	assert(to_24_hour_clock(28.5) == 4.5, "Test 5.");
	cout << "Тест to_24_hour_clock пройден." << endl;	

	cout << "Начало теста time_to_utc." << endl;
	assert(time_to_utc(+0, 12.0) == 12.0, "Test 1.");
	assert(time_to_utc(+1, 12.0) == 11.0, "Test 2.");
	assert(time_to_utc(-1, 12.0) == 13.0, "Test 3.");
	assert(time_to_utc(-11, 18.0) == 5.0, "Test 4.");
	assert(time_to_utc(-1, 0.0) == 1.0, "Test 5.");
	assert(time_to_utc(-1, 23.0) == 0.0, "Test 6.");
	cout << "Тест time_to_utc пройден." << endl;

	cout << "Начало теста time_from_utc." << endl;
	assert(time_from_utc(+0, 12.0) == 12.0, "Test 1.");
	assert(time_from_utc(+1, 12.0) == 13.0, "Test 2.");
	assert(time_from_utc(-1, 12.0) == 11.0, "Test 3.");
	assert(time_from_utc(+6, 6.0) == 12.0, "Test 4.");
	assert(time_from_utc(-7, 6) == 23.0, "Test 5.");
	assert(time_from_utc(-1, 0.0) == 23.0, "Test 6.");
	assert(time_from_utc(-1, 23.0) == 22.0, "Test 7.");
	assert(time_from_utc(+1, 23.0) == 0.0, "Test 8.");
	cout << "Тест time_from_utc пройден." << endl;

	cout << "Все тесты пройдены." << endl;

	system("pause");

}
