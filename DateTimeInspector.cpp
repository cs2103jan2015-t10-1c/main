//@author A0100750Y
#include "DateTimeInspector.h"

DateTimeInspector::DateTimeInspector(){
}

bool DateTimeInspector::dateIsValid(int day, int month, int year){
	bool isValid = false;
	if (day > 0 && month > 0 && year > 0 ){
		if (day <= 31 && month <= 12){
			date d (year, month, day);
			isValid = true;
		}
	}
	return isValid;
}

bool DateTimeInspector::timeIsValid (int hour, int minute){
	bool isValid = false;
	if (hour >= 0 && minute >=0){
		if (hour < 24 && minute < 60){
			isValid = true;
		}
	}
	return isValid;
}