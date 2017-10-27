#include<iostream>
#include<iomanip>
#include<string>
using namespace std;

// Function Prototypes
void showMenu();
void showDashBoard();
void readDashBoard(string, string, int, double, double);
double updateTotalDistanceTraveled(double, int, int, const int);
double calculateIntervalsDistanceTraveled(double &, int, int, const int);
string setDriveFunction(char);
string setCruise(int);
string setState(char, int);
int setCurrentSpeed(char, int, const int);

int main(){
	const int DELTA = 5; // CHANGE_IN_SPEED
	const int TIME_INTERVAL = 1; // Time elapsed for each interval
	int currentSpeed = 0, previousSpeed = 0;
	double intervalDistance = 0, totalDistanceFeet = 0;
	const int SIZE = 21; // size of demoArray
	char demoArray[] = { 'c', 'c', 'c', 'a', 'a', 'a', 'a', 'a', 'c', 'c', 'c', 'c', 'c', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b' };
	string funct, st;
	char input, command;

	showMenu();
	showDashBoard();

	do{
		cout << "Command: ";
		cin >> input;
		/*
		while (input > 1){
		cout << "Enter a single character Command";
		cin >> input;
		}
		*/
		command = tolower(input); // converts any upper case input to lower case

		previousSpeed = currentSpeed;  // sets current speed to previous speed

		switch (command){
		case 'a':
			currentSpeed = setCurrentSpeed(command, currentSpeed, DELTA);  // increases current speed by constant
			st = setState(command, currentSpeed);
			break;

		case 'b':
			currentSpeed = setCurrentSpeed(command, currentSpeed, DELTA);
			st = setState(command, currentSpeed);
			break;

		case 'c':
			currentSpeed = currentSpeed;
			st = setState(command, currentSpeed); 
			break;

		case 'd':
			// clears screen and initialize values to 0 for demo
			system("CLS");
			currentSpeed = 0;
			previousSpeed = 0;
			intervalDistance = 0;
			totalDistanceFeet = 0;

			showDashBoard();  // display column headings for demo

			for (int count = 0; count < SIZE; count++){
				// set current speed to previous speed
				previousSpeed = currentSpeed;

				if (demoArray[count] == 'a'){
					currentSpeed = setCurrentSpeed(demoArray[count], currentSpeed, DELTA);
					st = setState(demoArray[count], currentSpeed);
				}

				else if (demoArray[count] == 'b'){
					// if current speed is above 0, decement by delta 
					currentSpeed = setCurrentSpeed(demoArray[count], currentSpeed, DELTA);

					// determines vehcile state based upon current speed
					st = setState(demoArray[count], currentSpeed);
				}

				else if (demoArray[count] == 'c'){
					currentSpeed = currentSpeed;
					// sets state to stopped if current speed = 0
					st = setState(demoArray[count], currentSpeed);
				}

				// calculate distance of interval and get total feet traveled (returned by reference variable)  
				intervalDistance = calculateIntervalsDistanceTraveled(totalDistanceFeet, previousSpeed, currentSpeed, TIME_INTERVAL);

				// show the current values in columns
				readDashBoard(setDriveFunction(demoArray[count]), st, currentSpeed, intervalDistance, totalDistanceFeet);

			}
			cout << endl << endl;
			break;

		case 'h':
			showMenu();
			break;

		case 'q':
			break;

		default: cout << "Unrecognizable input, please try again.\n" << endl;

		} 
		intervalDistance = calculateIntervalsDistanceTraveled(totalDistanceFeet, previousSpeed, currentSpeed, TIME_INTERVAL);

		if ((command == 'a' || command == 'b' || command == 'c')){
			readDashBoard(setDriveFunction(command), st, currentSpeed, intervalDistance, totalDistanceFeet);
		}
	} while (command != 'q');
	return 0;
}

// displays menu of key strokes
void showMenu(){
	system("CLS");
	cout << "Supported Commands : \n";
	cout << "\t\t" << setw(10) << "a\t\taccelerate.\n";
	cout << "\t\t" << setw(10) << "b\t\tbrake.\n";
	cout << "\t\t" << setw(10) << "c\t\tcruise.\n";
	cout << "\t\t" << setw(9) << "d\t\tdemo.\n"; // setw(9) set due to margin displaying off by one
	cout << "\t\t" << setw(10) << "h\t\tprint this help text.\n";
	cout << "\t\t" << setw(10) << "q\t\tquit (end the program).\n" << endl;
}

// displays DashBoard headings
// headings reflect vehicle action, vehicle state, current speed of vehicle derived from user input and current speed
// headings interval distance and total Feet (Miles) traveled derived from functions calculateIntervalsDistanceTraveled and updateTotalDistanceTraveled
void showDashBoard(){
	cout << endl << setprecision(1) << fixed;
	cout << setw(13) << "Function" << setw(16) << "Current State" << setw(17) << "Current Speed " << setw(20) << " Interval Distance ";
	cout << setw(21) << " Total Feet (Miles)\n" << endl;
	return;
}

// takes char command (user input) 
// returns 1 of 3 strings to display for output under the function heading/column
// string represents user input / action on vehicle
string setDriveFunction(char command){
	if (command == 'a')
		return "Accelerate"; 
	else if (command == 'b')
		return "Brake";
	else
		return "Cruise";
}

// takes char command (user input), int and const to determine current speed for 1 of 3 options.  
// returns new user speed for acclerating, checks for 0 mph before reducing speed when brake is applied
// will always maintain current speed when cruise is selected
int setCurrentSpeed(char command, int currentSpeed, const int DELTA){
	if (command == 'a')
		return currentSpeed + DELTA;  // increases current speed by constant
	else if (command == 'b'){
		if (currentSpeed > 0)
			return currentSpeed - DELTA; // decreases current speed by constant
		else
			return 0;  // indicative of current speed already being at 0 mph
	}
	else
		return currentSpeed;  // maintains (no change in) current speed, ie Cruising
}

// takes char command (user input) and int current speed, determines 1 of 4 simulation states of vehicle
// if user input "accelerate", always will accelerate. if ui "brake" checks if stopped before braking is declared
// if ui "cruise", also checks if stopped before cruising is declared.
string setState(char command, int currentSpeed){
	if (command == 'a')
		return "Accelerating";
	else if (command == 'b'){
		// determines vehcile state based upon current speed
		if (currentSpeed == 0)
			return "Stopped"; // state equals stopped
		else
			return "Braking"; // state equals braking
	}
	else
		if (currentSpeed == 0)  // maintains current speed but discriminates between cruising state and stopped state
			return "Stopped";
		else
			return "Cruising";
}

// readDashBoard shows new/active data of current data for each new "drive" 
// formats output to display under each heading on the dashboard.  sets width and spacing between variables and 
// calculates/converts feet to miles
// driveCommandArray, state, current speed derived from accelerate, brake and command code.
// interval traveled and total Distance feet/traveled derived from corresponding functions
void readDashBoard(string driveCommandArray, string state, int currSpeed, double intervalTraveled, double totalDistInFeet){
	cout << setw(13) << driveCommandArray << setw(16) << state << setw(16) << currSpeed << setw(20) << intervalTraveled << setw(13);
	cout << totalDistInFeet << " (" << setprecision(3) << totalDistInFeet * 0.00018939 << ")" << setprecision(1) << endl;
	return;
}

// this function is called in "calculateIntervalsDistanceTraveled function"
// calculates total approximate distance traveled
// it takes previous total feet traveled, previous speed and current speed and the constant time interval
// computes average speed mph, converts to avg fps (feet per second) 
// and multiplies by the constant time interval for distance of current time interval
// then adds the previous total feet traveled with the current interval feet traveled for new total feet traveled

double updateTotalDistanceTraveled(double totalFeetTraveled, int previousSpeed, int currentSpeed, const int TIME_INTERVAL){
	double averageSpeed = (previousSpeed + currentSpeed) / 2.0;
	double averageSpeed_FeetPerSecond = averageSpeed * (5280.0 / 3600.0);
	double intervalFeetTraveled = averageSpeed_FeetPerSecond * TIME_INTERVAL;
	totalFeetTraveled = totalFeetTraveled + intervalFeetTraveled;
	return totalFeetTraveled;
}

// this function calculates new total distance traveled 
// it takes previous total distance, previous speed, current speeds and a constant time interval. 
// total distance is passed by reference (automatically updating original arguement variable)
// new total distance in feet is returned 
double calculateIntervalsDistanceTraveled(double &totalDistanceFeet, int previousSpeed, int currentSpeed, const int TIME_INTERVAL){
	double previousDistanceTraveled = totalDistanceFeet; // to store previous distance traveled
	totalDistanceFeet = updateTotalDistanceTraveled(totalDistanceFeet, previousSpeed, currentSpeed, TIME_INTERVAL); // call to updateTotalDistanceTraveled Function to get current distance traveled
	double intervalTraveled = totalDistanceFeet - previousDistanceTraveled; // calculate current interval traveled
	return intervalTraveled;
}
