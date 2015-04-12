//@author A0115902N
#include "DateTimeInitialiser.h"

DateTimeInitialiser::DateTimeInitialiser(){
}

void DateTimeInitialiser::initialiseDate(Date& inputDate, int inputDay, int inputMonth, int inputYear){
	inputDate.insertDay(inputDay);
	inputDate.insertMonth(inputMonth);
	inputDate.insertYear(inputYear);
	inputDate.initialiseDate();
}

void DateTimeInitialiser::initialiseTime(Time& inputTime, int inputHour, int inputMinute, date inputDate){
	inputTime.insertHour(inputHour);
	inputTime.insertMinute(inputMinute);
	inputTime.initialiseTime(inputDate);
}