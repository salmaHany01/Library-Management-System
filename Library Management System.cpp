#include<iostream>
#include<fstream>
#include<string>
#include<stdio.h>
#define maxcontacts 3
using namespace std;
struct date {
	int day = 0, month = 0, year = 0;
};
struct librarian {
	string username;
	string password;
};
struct user {
	int id = 0;
	string name;
	string email;
	string userPassword;
	string acc_type;
	date creationDate;
	string contactNumber[maxcontacts] = {};
};
struct bookData {
	string title;
	int productionYear = 0;
	int numOfCopies = 0;
	string category;
	int edition = 0;
}books;// see the changes
void updateBookRecord();
void signUpStaff(librarian& staff);
void login(librarian& staff);
void saveData(user& keepUserData);
void user_signup(user& newUser);
void search(string title, int pubYear, bookData& booksInfo);
void weeklyDisplay(user& userData);
int main() {
	librarian staff;
	user client;
	int choice = 0;
	int userPick = 0;
	int librarianPick = 0;
	cout << "Welcome!!" << endl;
	while (true) {
		cout << "Complete: " << endl;
		cout << "1. Librarian 2. New User 3.Menu" <<
			endl;
		cin >> choice;
		if (choice == 1) {
			while (true) {
				cout << "Would you like to: " << endl << "1.Signup 2.Log in 3.Exit" << endl;
					cin >> librarianPick;
				if (librarianPick == 1) {
					signUpStaff(staff);
					break;
				}
				else if (librarianPick == 2) {
					login(staff);
					break;
				}
				else if (librarianPick == 3)
					break;
			}
		}
		else if (choice == 2) {
			cout << "You will need to sign up first. Ask the staff for help to proceed this action." << endl << endl;
					user_signup(client);
			break;
		}
		else if (choice == 3)
			break;
		else {
			cout << "Invalid choice. Please try again." <<
				"=====================" << endl;
			continue;
		}
	}
	while (true) {
		cout << "=================================================="
			<< endl;
		cout << "Menu:" << endl;
		cout << "1. Search for a book" << endl;
		cout << "2. Buy a book" << endl;
		cout << "3. Display the weekly new users" << endl;
		cout << "4. Exit" << endl;
		string titleRequested = { 0 };
		char accountType = { 0 };
		cin >> userPick;
		if (userPick == 1) {
			int searchAnswer = 0;
			int publicationYear = 0;
			string searchTitle = { 0 };
			cout << "Search by the: " << endl;
			cout << "1.Title 2.Production Year" << endl;
			cin >> searchAnswer;
			cout << "Search: ";
			if (searchAnswer == 1)
				cin >> searchTitle;
			else if (searchAnswer == 2)
				cin >> publicationYear;
			else
				cout << "Invalid entry." << endl;
			search(searchTitle, publicationYear, books);
		}
		else if (userPick == 2) {
			cout << "Enter your account type:" << endl;
			cout << "Enter l for librarian or s for student or g for guest: ";
					cin >> accountType;
			if (accountType == 'l') {
				cout << "Enter the title of the book: ";
				cin >> titleRequested;
				ifstream infoForBooks;
				infoForBooks.open("books' data.txt");
				while (infoForBooks >> books.title >>
					books.numOfCopies >> books.productionYear >> books.category >>
					books.edition) {
					if (titleRequested == books.title)
						cout << "Checking the number of copies..."
						<< endl;
					if (books.numOfCopies >= 2) {
						cout << "A copy is available. You can buy one." << endl;
							updateBookRecord();
					}
					else {
						cout << "Sorry, no copies available." <<
							endl;
					}
				}
			}
			else
				cout << "This service isn't available for your account type." << endl;
		}
		else if (userPick == 3) {
			weeklyDisplay(client);
		}
		else if (userPick == 4) {
			break;
		}
	}
	return 0;
}
void updateBookRecord() {
	fstream infoForBooks;
	fstream temporary;
	infoForBooks.open("books' data", ios::in);
		temporary.open("temp.txt", ios::out);
	while (infoForBooks >> books.title >> books.numOfCopies >>
		books.productionYear >> books.category >> books.edition) {
		books.numOfCopies--;
		temporary << books.title << books.numOfCopies <<
			books.productionYear << books.category << books.edition;
	}
	infoForBooks.close();
	temporary.close();
	infoForBooks.open("books' data", ios::out);
	temporary.open("temp.txt", ios::in);
	while (temporary >> books.title >> books.numOfCopies >>
		books.productionYear >> books.category >> books.edition) {
		infoForBooks << books.title << books.numOfCopies <<
			books.productionYear << books.category << books.edition;
	}
	infoForBooks.close();
	temporary.close();
	remove("temp.txt");
}
void signUpStaff(librarian& staff) {
	cout << "Enter your ID or username: ";
	cin >> staff.username;
	cout << "Enter your password: ";
	cin >> staff.password;
	if (staff.password.size() < 8) {
		cout << "Your password must be at least 8 characters. Please try again." << endl;
			cout << "Enter your password: ";
		cin >> staff.password;
	}
	cout << "You have been signed in." << endl << "================"
		<< endl;
}
void login(librarian& staff) {
	string username, password;
	cout << "Enter your username: ";
	cin >> username;
	cout << "Enter your password: ";
	cin >> password;
	if (username == staff.username && password == staff.password) {
		cout << "You are logged in successively." << endl <<
			"================" << endl;
		system("pause");
	}
	else {
		cout << "Trouble logging you in. Please try again." << endl
			<< "================" << endl;
		system("pause");
	}
}
void saveData(user& keepUserData) {
	ofstream userInfo;
	userInfo.open("users' data.txt", ios::out);
	userInfo << keepUserData.id << ' ' << keepUserData.name << ' ' << keepUserData.email << ' ';
		userInfo << keepUserData.userPassword << ' ' <<
		keepUserData.acc_type << ' ';
	userInfo << keepUserData.creationDate.day << ' / ' <<
		keepUserData.creationDate.month << ' / ' <<
		keepUserData.creationDate.year << ' ';
	for (int i = 0; i <= 3; i++) {
		userInfo << keepUserData.contactNumber[i] << endl;
	}
	userInfo.close();
}
void user_signup(user& newUser) {
	cout << "Enter the ID of the user: ";
	cin >> newUser.id;
	cin.ignore();
	cout << "Enter your name: ";
	getline(cin, newUser.name);
	cout << "Enter an active e-mail to the user: ";
	cin >> newUser.email;
	cout << "Create a password to the account: ";
	cin >> newUser.userPassword;
	while (newUser.userPassword.size() < 8) {
		cout << "Password should at least have 8 characters." <<
			endl;
		cout << "Please try again." << endl << endl;
		cout << "Create a password: ";
		cin >> newUser.userPassword;
	}
	cout << "Choose the account type either student or guest: ";
	cin >> newUser.acc_type;
	cout << "Enter the account creation date: ";
	cin >> newUser.creationDate.day >> newUser.creationDate.month >>
		newUser.creationDate.year;
	cout << "Enter an active contact number(s) [maximum 3 numbers]: ";
	cin >> newUser.contactNumber[0];
	if (newUser.contactNumber[0].size() < 11) {
		cout << "You entered a wrong format. Please try again." <<
			endl;
		cout << "Enter a contact number: ";
		cin >> newUser.contactNumber[0];
	}
	char answer = { 0 };
	int max = 1;
		do {
			cout << "Would you like to add more contact numbers? " << "(Y:Yes or N : No)" << endl;
				cout << "Your answer: ";
			cin >> answer;
			if (answer == 'y' || answer == 'Y') {
				for (int i = 1; i < 3; i++) {
					cout << "Enter the other contact number: ";
					cin >> newUser.contactNumber[i];
					if (newUser.contactNumber[i].size() < 11) {
						cout << "You entered a wrong format. Please try again." << endl;
							cout << "Enter the contact number: ";
						cin >> newUser.contactNumber[i];
					}
					max++;
					break;
				}
			}
			else if (answer == 'n' || answer == 'N') {
				cout << "Thanks!" << endl;
				break;
			}
			else {
				cout << "Invalid entry." << endl;
				continue;
			}
		} while (max <= 3);
		saveData(newUser);
}
void search(string title, int pubYear, bookData& booksInfo) {
	ifstream searchBooks;
	searchBooks.open("books' data");
	while (searchBooks >> booksInfo.title >> booksInfo.numOfCopies >>
		booksInfo.productionYear >> booksInfo.category >> booksInfo.edition) {
		if (title == booksInfo.title || pubYear ==
			booksInfo.productionYear)
			cout << "The book is avialable." << endl;
		else
			cout << "Sorry. This book isn't available in the library for now." << endl;
	}
	searchBooks.close();
}
void weeklyDisplay(user& userData) {
	int currentDay, currentMonth, currentYear;
	cout << "Please Enter today's date (day, month, year): ";
	cin >> currentDay >> currentMonth >> currentYear;
	int resultingDay = 0, resultingMonth = 0;
	
		if (currentYear == userData.creationDate.year) {
			resultingDay = currentDay - 7;
			if (resultingDay <= 0) {
				resultingMonth = currentMonth - 1;
				if (resultingMonth == 1 || resultingMonth == 3 ||
					resultingMonth == 5 || resultingMonth == 7 || resultingMonth == 8 ||
					resultingMonth == 10 || resultingMonth == 12)
					resultingDay = 31 + resultingDay;
				else if (resultingDay == 4 || resultingDay == 6 ||
					resultingDay == 9 || resultingDay == 11)
					resultingDay = 30 + resultingDay;
				else
					resultingDay = 28 + resultingDay;
			}
			else
				resultingMonth = currentMonth;
		}
		else
			cout << "No new accounts were created through the past week."
			<< endl;
	if (resultingDay == userData.creationDate.day && resultingMonth ==
		userData.creationDate.month && currentYear ==
		userData.creationDate.year) {
		cout << "The information of the users who created accounts through the past week : " << endl;
			cout << "Information is displayed as (ID | Name | E-mail | Account type | creation Date | Contact numbers)." << endl;
			cout << userData.id << " | " << userData.name << " | " <<
			userData.email << " | " << userData.acc_type << " | ";
		cout << userData.creationDate.day << "/" <<
			userData.creationDate.day << "/" << userData.creationDate.day << endl;
		cout << "Contact numbers:" << endl;
		for (int i = 0; i <= 3; i++)
			cout << userData.contactNumber[i] << endl;
	}
}