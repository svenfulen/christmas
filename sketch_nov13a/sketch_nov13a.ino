// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  //initialize analog pins 0-2 for button input
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
}

bool menuMode = true;

//0 for section 1
//1 for section 2
//2 for section 3
//3 for enter button
int menuSection = 0;
//0 for date menu
//1 for time menu
//2 for menu mode to be false
int cursorMenu = +

    countdown(); //counts one minute
  }
  else {
    merryChristmas();
  }
}

}

//is it christmas or not
bool isChristmas(){
  if (currentDay == 25 && currentMonth == 12){
    return true;
  }
  else {
    return false;
  }
}

//prints the date menu display
void dateMenu(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Set Date");
  lcd.setCursor(0, 1);
  if (currentMonth < 10) {
    lcd.print("0");
  }
  lcd.print(currentMonth);
  lcd.print("/");
  if (currentDay < 10) {
    lcd.print("0");
  }
  lcd.print(currentDay);
  lcd.print("/");
  lcd.print(currentYear);
  lcd.print(" E");
}

//prints the time menu display
void timeMenu(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Set Time");
  lcd.setCursor(0, 1);
  if (currentHour < 10) {
    lcd.print("0");
  }
  lcd.print(currentHour);
  lcd.print(":");
  if (currentMinute < 10) {
    lcd.print("0");
  }
  lcd.print(currentMinute);
  lcd.print("      E");
}

//prints out merry christmas message
void merryChristmas(){
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("MERRY");
  lcd.setCursor(4, 1);
  lcd.print("CHRISTMAS");
}

void countdown() {
  //if it is not christmas
if (!isChristmas()) {
  //the timer operates every one minute
  delay(60000);
  
  //if it's 23:59 then turn the clock to next day
  if (currentHour == 23 && currentMinute == 59) {
    currentHour = 0;
    currentMinute = 0;
    daysLeft = daysLeft - 1;
  }
  //if it's not 23:59 then count
  else{
    //if it's not XX:59 increment minutes
    if (currentMinute < 59) {
      currentMinute = currentMinute + 1;
    }
    //if it is XX:59 increment hours
    //if it is XX:59 set minutes to 0
    else {
      currentHour = currentHour + 1;
      currentMinute = 0;
    }
  }
}

else {
  merryChristmas(); //clock ends
}

}

void displayScreen(){
  lcd.clear();
  lcd.print(daysLeft);
  lcd.print (" DAYS");
  lcd.setCursor(0,1);
  lcd.print (24 - currentHour);
  lcd.print (" HOURS");
}







void setupMenu(){
  //gets input from the buttons
  leftButtonState = digitalRead(A2);
  middleButtonState = digitalRead(A1);
  rightButtonState = digitalRead(A0);
  
  //if menu section is 0 set date
  //if menu section is 1 set time
  if (menuSection == 0) {
    dateMenu();
    delay(100);
    }
  else if (menuSection == 1) { 
    timeMenu();
    delay(100);
    }
  
  //if middle button is pressed
  if (middleButtonState == HIGH) {
	//if the cursor is on the E
    if (cursorMenu == 3) {
		//if menu section is either 0 or 1
		if (menuSection < 2){
			menuSection = menuSection + 1;
			delay(200);
		}
		//if menu section is 2 exit menu and go to countdown
		else {
      daysLeft = dateDifference(currentYear, currentMonth, currentDay, currentYear, 11, 25);
			menuMode = false;
		}
    }
  }
  //if left button is presed
  else if (leftButtonState == HIGH) {
	  
	//if the date menu is active
	if (menuSection == 0) {
		switch (cursorMenu) {
			case 0:
        if (currentMonth < 13) {
				currentMonth = currentMonth + 1;
        }
        else { currentMonth = 1; }
				delay(200);
			break;
			case 1:
        if (currentDay < 32) {
				currentDay = currentDay + 1;
        }
        else { currentDay = 1; }
				delay(200);
			break;
			case 2:
				currentYear = currentYear + 1;
				delay(200);
			break;
			default:
      break;
	}
	}
	//if the time menu is active
	else if (menuSection == 1) {
    //sets the month correctly for date comparison
    currentMonth = currentMonth - 1;
    
		switch (cursorMenu) {
			case 0:
				if (currentHour < 24) {
					currentHour = currentHour + 1;
					delay(200);
				}
				else {
					currentHour = 0;
				}
			break;
			case 1:
				if (currentMinute < 60) {
					currentMinute = currentMinute + 1;
					delay(200);
				}
				else {
					currentMinute = 0;
          delay(200);
				}
			break;
			default:
      break;
	}

  }
  
  }
  //if right button is pressed
  else if (rightButtonState == HIGH){
	if (cursorMenu < 4) {
		cursorMenu = cursorMenu + 1;
		delay(200);
	}
	else {
		cursorMenu = 0;
		delay(200);
	}
	  
	  
  }
  
  //if no button is pressed
  else {
    //all buttons are off
    digitalWrite(A0, LOW);
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);
  }
}










//DATE DIFFERENCE
//
//

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
