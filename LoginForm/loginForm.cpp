#include <iostream>  // For Input and Output
#include <fstream>   // For File Handling
#include <windows.h> // For Sleep function
#include <sstream>   // For stringstream
#include <string>    // For string

using namespace std;

class Login {
private:
    string LoginID, Password;
public:
    Login() : LoginID(""), Password("") {}

    void setID(const string& userId) {
        LoginID = userId;
    }

    void setPassword(const string& userPassword) {
        Password = userPassword;
    }

    string getID() const {
        return LoginID;
    }

    string getPassword() const {
        return Password;
    }
};

void registration(Login& log) {
    system("cls");
    string userID, userPassword;
    cout << "\tEnter Login ID: ";
    cin >> userID;
    log.setID(userID);

    while (true) {
        cout << "\tEnter A Strong Password: ";
        cin >> userPassword;
        if (userPassword.length() >= 8) {
            log.setPassword(userPassword);
            break;
        } else {
            cout << "\tEnter Minimum 8 characters!" << endl;
        }
    }

    ofstream outFile("loginData.txt", ios::app);
    if (!outFile) {
        cout << "\tError: File Can't Open!" << endl;
    } else {
        outFile << log.getID() << " : " << log.getPassword() << endl;
        cout << "\tUser Registered Successfully!" << endl;
    }
    outFile.close();
    Sleep(3000);
}

void login() {
    system("cls");
    string loginID, loginPassword;
    cout << "\tEnter Login ID: ";
    cin >> loginID;
    cout << "\tEnter Login Password: ";
    cin >> loginPassword;

    ifstream infile("loginData.txt");
    if (!infile) {
        cout << "\tError: File Can't Open!" << endl;
    } else {
        string line;
        bool found = false;
        while (getline(infile, line)) {
            stringstream ss(line);
            string userID, userPw;
            char delimiter;
            ss >> userID >> delimiter >> userPw;
            if (loginID == userID && loginPassword == userPw) {
                found = true;
                for (int i = 0; i < 3; i++) {
                    cout << '.';
                    Sleep(800);
                }
                system("cls");
                cout << "\tWelcome To This Page!" << endl;
                break;
            }
        }
        if (!found) {
            cout << "\tError: Incorrect Login ID or Password!" << endl;
        }
        infile.close();
    }
    Sleep(5000);
}

int main() {
    Login log;
    bool exit = false;
    while (!exit) {
        system("cls"); // To hide the previous output
        int val;
        cout << "\tWelcome To Registration & Login Form" << endl;
        cout << "\t*****************************************" << endl;
        cout << "\t1. Register." << endl;
        cout << "\t2. Login." << endl;
        cout << "\t3. Exit." << endl;
        cout << "\tEnter Choice: ";
        cin >> val;
        if (val == 1) {
            registration(log);
        } else if (val == 2) {
            login();
        } else if (val == 3) {
            system("cls");
            exit = true;
            cout << "\tGood Bye!" << endl;
            Sleep(3000);
        }
        Sleep(3000);
    }
    return 0;
}
