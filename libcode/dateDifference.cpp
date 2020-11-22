
/*Days are defined 0-6, 0 being Sunday and 6 being Saturday.*/

//Returns true if it is a leap year
bool isLeapYear(int year) {
	//if the year is 
	if (year % 4 == 0 || year % 400 == 0) {
		if (year % 100 == 0) {
			return false;
		}
		else {
			return true;
		}
	}
	else {
		return false;
	}
}

int daysInMonth[12]{ 31,28,31,30,31,30,31,31,30,31,30,31 };

/*
yearA & yearB should be a 4-digit int
monthA should be an int 0-11
date A: yearA, monthA, dayA
date B: yearB, monthB, dayB
*/

int dateDifference(int yearA, int monthA, int dayA, int yearB, int monthB, int dayB) {

	int daysBetweenDates = 0; //each operation adds to this var
	int fullYearsBetween = (yearB - yearA) - 1; //the number of years between dates that are not yearA or yearB

	//determine if both dates are in the same year
	if (yearA == yearB) {
		if (isLeapYear(yearA)) { daysInMonth[1] = 29; }

		//adds remaining days in monthA to daysBetweenDates
		daysBetweenDates = daysBetweenDates + (daysInMonth[monthA] - dayA);

		//adds the days in months between date A and date B
		for (int i = monthA + 1; i < monthB; i++) {
			daysBetweenDates = daysBetweenDates + daysInMonth[i];
		}

		//adds the number of days remaining to get to date B
		daysBetweenDates = daysBetweenDates + dayB;

		return daysBetweenDates;
	}

	//if both dates are in different years
	else {
		if (isLeapYear(yearA)) { daysInMonth[1] = 29; }//sets days in february to 29 if it is a leap year
		//adds remaining days of monthA to daysBetweenDates
		daysBetweenDates = daysBetweenDates + (daysInMonth[monthA] - dayA);

		//adds remaining days in yearA to daysBetweenDates
		for (int i = monthA + 1; i < 12; i++) {
			//find how many days are left in the first year
			daysBetweenDates = daysBetweenDates + daysInMonth[i];
		}

		//find out how many days are between the full years between yearA and yearB
		//if there are no full years between yearA and yearB, it won't run
		if (fullYearsBetween > 0) {
			for (int i = yearA + 1; i < yearB; i++) {
				if (isLeapYear(i)) {
					daysBetweenDates = daysBetweenDates + 366;
				}
				else {
					daysBetweenDates = daysBetweenDates + 365;
				}
			}
		}

		daysInMonth[1] = 28;//resets february to 28 days

		if (isLeapYear(yearB)) { daysInMonth[1] = 29; }
		for (int i = 0; i < monthB; i++) {
			daysBetweenDates = daysBetweenDates + daysInMonth[i];
		}

		daysBetweenDates = daysBetweenDates + dayB;

		return daysBetweenDates;
	}

}
