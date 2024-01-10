#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void mainMenu(); // main menu function prototype

class Flight {
private:
	string flightNum, departure, arrival, departureDate, departureTime;
public:
	void setFlightNum(string fnm){ flightNum = fnm; };
	void setDeparture(string dep){ departure = dep; };
	void setArrival(string arr){ arrival = arr; };
	void setDepartureDate(string dDate){ departureDate = dDate; };
	void setDepartureTime(string dTime){ departureTime = dTime; };

	string getFlightNum(){ return flightNum; };
	string getDeparture(){ return departure; };
	string getArrival(){ return arrival; };
	string getDepartureDate(){ return departureDate; };
	string getDepartureTime(){ return departureTime; };

	int seat[6][3] = { {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0} };               // row and col 0 is unused, 0 = vacant, nonzero = customerID (taken)

	friend ifstream& operator>>(ifstream& in, Flight& f){
		in >> f.flightNum;
		in >> f.departure;
		in >> f.arrival;
		in >> f.departureDate;
		in >> f.departureTime;
		for(int i = 1; i <= 5; i++){
			in >> f.seat[i][1] >> f.seat[i][2];
		}
		return in;
	}

	friend ofstream& operator<<(ofstream& os, Flight& f){
		os << f.flightNum << " ";
		os << f.departure << " ";
		os << f.arrival << " ";
		os << f.departureDate << " ";
		os << f.departureTime << endl;
		for(int i = 1; i <= 5; i++){
			os << f.seat[i][1] << " " << f.seat[i][2];
			if(i != 5) os << endl;
		}
		return os;
	}
};

class Customer {
private: 
	string fname, lname, address, phone;
public: 
	void setFname(string fn){ fname = fn; }
	void setLname(string ln){ lname = ln; }
	void setAddress(string ad){ address = ad; }
	void setPhone(string ph){ phone = ph; }

	string getFname(){ return fname; }
	string getLname(){ return lname; }
	string getAddress(){ return address; }
	string getPhone(){ return phone; }

	friend ifstream& operator>>(ifstream& in, Customer& c){
		getline(in, c.fname);
		getline(in, c.lname);
		getline(in, c.address);
		getline(in, c.phone);
		return in;
	}

	friend ofstream& operator<<(ofstream& os, Customer& c){
		os << c.fname << endl;
		os << c.lname << endl;
		os << c.address << endl;
		os << c.phone;
		return os;
	}
};

vector<Flight> vFlight;  // flight information inside
vector<Customer> vCustomer; // customer information inside

ifstream flightFile_IN;
ofstream flightFile_OUT;

Flight tempFlight;
void createFlight(){ // initialization of flight information
	flightFile_IN.open("flight_file.txt");
	if(flightFile_IN){
		while(!flightFile_IN.eof()){
			flightFile_IN >> tempFlight;
			vFlight.push_back(tempFlight);
		}
	}
	flightFile_IN.close();
}

void saveFlight(){ // saving of flight information
	flightFile_OUT.open("flight_file.txt");
	for(int i = 0; i < vFlight.size(); i++){
		flightFile_OUT << vFlight[i];
		if(i != vFlight.size() - 1) flightFile_OUT << endl;
	}
	flightFile_OUT.close();
}

ifstream customerFile_IN;
ofstream customerFile_OUT;

Customer tempCustomer;
void createCustomer(){ // initialization of customer information
	customerFile_IN.open("customer_file.txt");
	if(customerFile_IN){
		while(!customerFile_IN.eof()){
			customerFile_IN >> tempCustomer;
			vCustomer.push_back(tempCustomer);
		}
	}
	customerFile_OUT.close();
}

void saveCustomer(){ // saving of customer information
	customerFile_OUT.open("customer_file.txt");
	if(customerFile_OUT.is_open()){
		for(int i = 0; i < vCustomer.size(); i++){
			customerFile_OUT << vCustomer[i];
			if(i != vCustomer.size() - 1) customerFile_OUT << endl;
		}
		customerFile_OUT.close();
	}
}

// ticket sale function - customer requests a ticket
void ticketSale(){
	cout << "\nAvailable Flights: \n";
	for(int i = 0; i < vFlight.size(); i++){
		cout << i+1 << ". " << vFlight[i].getFlightNum() << " " << vFlight[i].getDeparture() << " --> " << vFlight[i].getArrival() << " " << vFlight[i].getDepartureDate() << " " << vFlight[i].getDepartureTime() << endl;
	}
	cout << "\nPlease select your flight: [1..." << vFlight.size() << "]: ";
	int flightChoice; cin >> flightChoice;
	cout << endl;
	cout << flightChoice << ". " << vFlight[flightChoice-1].getFlightNum() << " " << vFlight[flightChoice-1].getDeparture() << " --> " << vFlight[flightChoice-1].getArrival() << " " << vFlight[flightChoice-1].getDepartureDate() << " " << vFlight[flightChoice-1].getDepartureTime() << endl;
	for(int i = 1; i <= 5; i++){
		cout << "\t" << vFlight[flightChoice-1].seat[i][1] << " " << vFlight[flightChoice-1].seat[i][2] << endl;
	}
	cout << "Please select your seat [row#,col#]: ";
	int rowChoice, colChoice; cin >> rowChoice >> colChoice;
	if(vFlight[flightChoice-1].seat[rowChoice][colChoice] != 0){
		cout << "Seat is already taken. Please select another seat.\n";
		ticketSale();
	}
	cout << "Please choose the customer number from the following list, or enter -1 to add a new customer: \n";

	for(int i = 0; i < vCustomer.size(); i++){
		cout << i+1 << ". " << vCustomer[i].getFname() << " " << vCustomer[i].getLname() << " " << vCustomer[i].getAddress() << " " << vCustomer[i].getPhone() << endl;
	}
	cout << "Please select your customer: [1...]: ";
	int cChoice; cin >> cChoice;
	if(cChoice == -1){
		// create new customer
		Customer newCustomer;
		cin.ignore();
		string temp;
		cout << "First name: "; getline(cin, temp); newCustomer.setFname(temp);
		cout << "Last name: "; getline(cin, temp); newCustomer.setLname(temp);
		cout << "Address: "; getline(cin, temp); newCustomer.setAddress(temp);
		cout << "Phone: "; getline(cin, temp); newCustomer.setPhone(temp); 
		vCustomer.push_back(newCustomer);
		cChoice = vCustomer.size();
	} else if(cChoice < -1 || cChoice > vCustomer.size()+1){
		cout << "Invalid choice entered. Please try again. \n";
		ticketSale();
	}
	vFlight[flightChoice-1].seat[rowChoice][colChoice] = cChoice;
	cout << flightChoice << ". " << vFlight[flightChoice-1].getFlightNum() << " " << vFlight[flightChoice-1].getDeparture() << " --> " << vFlight[flightChoice-1].getArrival() << " " << vFlight[flightChoice-1].getDepartureDate() << " " << vFlight[flightChoice-1].getDepartureTime() << endl;
	for(int i = 1; i <= 5; i++){
		cout << "\t" << vFlight[flightChoice-1].seat[i][1] << " " << vFlight[flightChoice-1].seat[i][2] << endl;
	}

	cout << "Your reservation is confirmed. Press m to return to the main menu: \n";
	char temp; cin >> temp;
	mainMenu();
}

void retrieveFlightInfo(){ // retrieve flight info - canceled flight. 
	cout << "Enter the flight number of the flight you are trying to access. \n";
	for(int i = 0; i < vFlight.size(); i++){
		cout << i+1 << ". " << vFlight[i].getFlightNum() << " " << vFlight[i].getDeparture() << " ---> " << vFlight[i].getArrival() << " " << vFlight[i].getDepartureDate() << " " << vFlight[i].getDepartureTime() << endl;
	}
	int choice; cin >> choice;
	if(choice < 0 || choice > vFlight.size()){
		cout << "Invalid choice entered. Please try again. \n";
		retrieveFlightInfo();
	}

	for(int r = 1; r <= 5; r++){
		for(int c = 1; c <= 2; c++){
			if(vFlight[choice-1].seat[r][c] != 0){
				cout << "Seat " << r << c << " is taken by customer " << vCustomer[choice-1].getFname() << " " << vCustomer[choice-1].getLname() << " with phone number " << vCustomer[choice-1].getPhone() << " and address " << vCustomer[choice-1].getAddress() << endl;
			}
		}
	}
	cout << "Canceled flight " << vFlight[choice-1].getFlightNum() << ". \n";
	vFlight.erase(vFlight.begin()+choice-1);
}

void createNewFlight(){ // create new flight, pass parameters
	Flight tempF;
	cout << "Enter the details of your new flight: \n";
	string prefix = "FN", temp;
	cout << "Enter flight number: "; cin >> temp; tempF.setFlightNum(prefix + temp);
	cout << "Enter flight origin: "; cin >> temp; tempF.setDeparture(temp);
	cout << "Enter flight destination: "; cin >> temp; tempF.setArrival(temp);
	cout << "Enter flight date (YYYY-MM-DD): "; cin >> temp; tempF.setDepartureDate(temp);
	cout << "Enter flight time (HH:MM): "; cin >> temp; tempF.setDepartureTime(temp);
	vFlight.push_back(tempF);
	cout << "New flight successfully entered. Returning to the main menu. \n";
	mainMenu();
}

void reservationCancellation(){ // cancel reservation
	cout << "Please select the customer whose reservation you would like to cancel: \n";
	for(int i = 0; i < vCustomer.size(); i++){
		cout << i+1 << ". " << vCustomer[i].getFname() << " " << vCustomer[i].getLname() << endl;
	}	
	cout << endl;
	cout << "Please enter your choice: ";
	int choice; cin >> choice;
	if(choice < 0 || choice > vCustomer.size()){
		cout << "Invalid choice entered. Please try again. \n";
		reservationCancellation();
	}
	cout << endl;

	cout << "Please select your flight: \n";
	for(int i = 0; i < vFlight.size(); i++){
		cout << i+1 << ". " << vFlight[i].getFlightNum() << " " << vFlight[i].getDeparture() << " ---> " << vFlight[i].getArrival() << " " << vFlight[i].getDepartureDate() << " " << vFlight[i].getDepartureTime() << endl;
	}
	cout << "Enter your choice: ";
	int fchoice; cin >> fchoice;
	if(fchoice < 0 || fchoice > vFlight.size()){
		cout << "Invalid choice entered. Please try again. \n";
		reservationCancellation();
	}
	bool flag = false;
	for(int r = 1; r <= 5; r++){
		for(int c = 1; c <= 2; c++){
			if(vFlight[fchoice-1].seat[r][c] == choice){
				vFlight[fchoice-1].seat[r][c] = 0;
				flag = true;
				cout << "Reservation successfully cancelled. Returning to the main menu. \n";
				mainMenu();
			}
		}
	}

	if(!flag){
		cout << "Reservation not found / not canceled. Returning to the main menu. \n";
		mainMenu();
	}
}

void printManifest(){ // print flight manifest
	cout << "Please select your flight: \n";
	for(int i = 0; i < vFlight.size(); i++){
		cout << i+1 << ". " << vFlight[i].getFlightNum() << " " << vFlight[i].getDeparture() << " ---> " << vFlight[i].getArrival() << " " << vFlight[i].getDepartureDate() << " " << vFlight[i].getDepartureTime() << endl;
	}
	cout << endl;
	cout << "Enter your choice: ";
	int fchoice; cin >> fchoice;
	if(fchoice < 0 || fchoice > vFlight.size()){
		cout << "Invalid choice entered. Please try again. \n";
		printManifest();
	}
	cout << "Passenger Manifest for Flight " << vFlight[fchoice-1].getFlightNum() << ": \n";
	for(int r = 1; r <= 5; r++){
		for(int c = 1; c <= 2; c++){
			if(vFlight[fchoice-1].seat[r][c] != 0){
				cout << "Seat " << r << " " << c << " is booked by customer " << vCustomer[fchoice].getFname() << " " << vCustomer[fchoice].getLname() << ". \n";
			} else {
				cout << "Seat " << r << " " << c << " is empty." << endl;
			}
		}
	}
	cout << "\n Manifest printed. Returning to main menu." << endl;
	mainMenu();
}

void getCustomerDetails(){
	cout << "Please select the customer whose details you would like to access: \n";
	for(int i = 0; i < vCustomer.size(); i++){
		cout << i+1 << ". " << vCustomer[i].getFname() << " " << vCustomer[i].getLname() << endl;
	}
	cout << "Please make a selection: ";
	int choice; cin >> choice;
	if(choice < 0 || choice > vCustomer.size()){
		cout << "Invalid choice entered. Please try again. \n";
		getCustomerDetails();
	}
	cout << endl;
	cout << "Please select the flight you would like to access: \n";
	for(int i = 0; i < vFlight.size(); i++){
		cout << i+1 << ". " << vFlight[i].getFlightNum() << " " << vFlight[i].getDeparture() << " ---> " << vFlight[i].getArrival() << " " << vFlight[i].getDepartureDate() << " " << vFlight[i].getDepartureTime() << endl;
	}
	cout << "Please make a selection: ";
	int fchoice; cin >> fchoice;
	if(fchoice < 0 || fchoice > vFlight.size()){
		cout << "Invalid choice entered. Please try again. \n";
		getCustomerDetails();
	}

	bool flag = false;
	for(int r = 1; r <= 5; r++){
		for(int c = 1; c <= 2; c++){
			if(vFlight[fchoice-1].seat[r][c] == fchoice){
				cout << "Seat " << r << " " << c << " is assigned to you." << endl;
				flag = true;
				cout << "Returning to the main menu. \n";
				mainMenu();
			}
		}
	}

	if(!flag){
		cout << "You do not have a booking for this flight. Returning to main menu. \n";
		mainMenu();
	}
}

void mainMenu(){
	cout << "\t             Fly-By-Night Airlines             \n";
	cout << "\t                   MAIN MENU                   \n";
	cout << "\t===============================================\n";
	cout << "\t 1. Ticket Sales                               \t \n";
	cout << "\t 2. Reservation Cancellation                   \t \n";
	cout << "\t 3. Retrieve Flight Information                \t \n";
	cout << "\t 4. Create Flight                              \t \n";
	cout << "\t 5. Print Passenger Manifest                   \t \n";
	cout << "\t 6. Cancel Flight                              \t \n";
	cout << "\t 7. Exit                                       \t \n";
	cout << "Please select your choice [1,2...7]: ";
	int choice; cin >> choice;
	switch(choice){
		case 1: { // sell a ticket
			ticketSale();
			break;
		}
		case 2: { // cancel a reservation
			reservationCancellation();
			break;
		}
		case 3: { // retrieve a customer's reservation information
			getCustomerDetails();
			break;
		}
		case 4: { // create a new flight - different from the initialization function createFlight()
			createNewFlight();
			break;
		}
		case 5: { // print a flight's passenger manifest
			printManifest();
			break;
		}
		case 6: { // cancel a flight, print passenger list
			retrieveFlightInfo();
			break;
		}
		case 7: { // exit
			cout << "Thank you for choosing Fly-By-Night Airlines! \n";
			exit(0); // alternate to return 0 due to switch case
			break;
		} 
		default: { // invalid entry
			cout << "Invalid choice entered. Please try again. \n";
			mainMenu();
			break;
		}
	}
}

int main() {
	// Initialization
	createFlight();
	createCustomer();

	// Main menu function (main program builds off here)
	mainMenu();

	// Save details about flight/customer for future use of the program
	saveFlight();
	saveCustomer();
	return 0;
}
