// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
}

int daysLeft = dateDifference(2020, 10, 21, 2020, 11, 25);
int currentYear = 2020;
int currentMonth = 1;
int currentDay = 1;
int currentHour = 12;
int currentMinute = 25;

void loop() {
  lcd.setCursor(0,1);
  lcd.print(daysLeft);
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
  lcd.print(currentMonth);
  lcd.print("/");
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
  lcd.print(currentHour);
  lcd.print(":");
  lcd.print(currentMinute);
  lcd.print(" E");
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
  //if there are more days left until christmas
if (daysLeft > 0) {
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

//DATE DIFFERENCE
//
//


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
