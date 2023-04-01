#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <fstream>

using namespace std;

// Functions
void initializeArrays();

void loadAdminRecordFromFile();
void writeAdminRecordInFile();
void appendDoctorRecordInFile(int idx);
void loadDoctorRecordsFromFile();
void writeAllDoctorRecordsInFile();
void appendPatientRecordInFile(int idx);
void loadPatientRecordsFromFile();
void writeAllPatientRecordsInFile();
void appendMedicineRecordInFile(int idx);
void loadMedicineRecordsFromFile();
void writeAllMedicineRecordsInFile();
string parsing(string line, int number);

void printHeader();
void printSubHeader(string heading);
void printNewScreen(string subHeader);
string loginScreen();
string loginValidation(string Username, string Password);

string printAdminMenu();
bool validateAdminMenuInput(string choice);
string chooseAdminFunctionality(string menuChoice);
void addRecordAdmin();
void removeRecordAdmin();
void shiftUserRecordIndexes(int recordNumber);
void viewRecordsAdmin();
void searchRecordAdmin();
void viewAllRecordsAdmin();
void viewDispensaryInventory();
void updateDispensaryInventory();
void updateMedicine();
void addMedicine();
void viewMedicinePrices();
void updateMedicinePrices();
void viewDoctorSchedules();
void addPatientBill();
void updatePatientBill();
void updateDoctorSalary();
void addDoctorRecord();
void addPatientRecord();
void viewHospitalServiceReviews();

string printDoctorMenu();
bool validateDoctorMenuInput(string choice);
string chooseDoctorFunctionality(string menuChoice);
string printSessionEndScreen(string logoutChoice);
void viewPatientRecords();
void searchPatientRecord();
void viewAllPatientRecords();
void diagnosePatient();
void prescribeMedicine();
bool validateMedicineInput(string MedicinePrescribed);
void viewMySchedule();
void orderTest();
void viewTestResult();
void addTestResult();
void scheduleAppointment();
bool validateDate(string date);
bool validateMonth(string month);
bool validateYear(string year);
void cancelAppointment();
string doctorAppointmentPresent(int registrationNumber);
void editAppointment();

string printPatientMenu();
bool validatePatientMenuInput(string choice);
string choosePatientFunctionality(string menuChoice);
void viewOwnRecord();
void editPersonalDetails();
void editUsername();
void editPassword();
void viewPatientDiagnosis();
void viewPatientPrescription();
void viewPatientTest();
void viewPatientAppointment();
void viewPatientBill();
void viewPatientTestResult();
void giveReview();
void inputReview();
bool validateReviewInput(string input);

string inputLogoutChoice();
bool validateLogoutChoice(string logoutChoice);

bool isPasswordUnique(string Password);
bool validateUsername(string Username);
bool validateNumericInput(string input);
int assignRegistrationNumber();
int searchRecord(int RegistrationNumber);
void displayRecord(int idx);
void printRecordNotFoundScreen();
void printNoRecordFoundScreen();
void printInvalidInputScreen();
void printPasswordInUseScreen();
void printInvalidUsernameScreen();
void useRedColour();
void useWhiteColour();

// Variables and Arrays
const int userArrSize = 100;
int currentUsers = 1;
string usernames[userArrSize];
string passwords[userArrSize];
string userRoles[userArrSize];
int registrationNumbers[userArrSize];

int loggedInIndex;
string loggedInUser;
string loggedInPassword;
string loggedInUserRole;
int loggedInRegistrationNumber;

int currentMedicines = 0;
string medicineAmounts[userArrSize];
string medicineNames[userArrSize];
string medicinePrices[userArrSize];

string patientBills[userArrSize];
string diseases[userArrSize];
string prescribedMedicines[userArrSize];
string prescribedMedicineAmounts[userArrSize];
string orderedTests[userArrSize];
string testResults[userArrSize];
string appointmentDates[userArrSize];
string appointmentDoctorRegistrationNumbers[userArrSize];

string doctorSalaries[userArrSize];
string scheduledAppointmentDoctor[userArrSize];

string hospitalReviewStatements[userArrSize];
string hosptialReviewStars[userArrSize];

main()
{
    string UserRole, nextStep;
    string menuChoice;
    initializeArrays();
    loadAdminRecordFromFile();
    loadDoctorRecordsFromFile();
    loadPatientRecordsFromFile();
    loadMedicineRecordsFromFile();
loginScreen:
    UserRole = loginScreen();
    if (UserRole == "Admin")
    {
    adminMenuScreen:
        menuChoice = printAdminMenu();
        nextStep = chooseAdminFunctionality(menuChoice);
        if (nextStep == "menuScreen")
        {
            goto adminMenuScreen;
        }
        else if (nextStep == "loginScreen")
        {
            goto loginScreen;
        }
    }
    else if (UserRole == "Doctor")
    {
    doctorMenuScreen:
        menuChoice = printDoctorMenu();
        nextStep = chooseDoctorFunctionality(menuChoice);
        if (nextStep == "menuScreen")
        {
            goto doctorMenuScreen;
        }
        else if (nextStep == "loginScreen")
        {
            goto loginScreen;
        }
    }
    else if (UserRole == "Patient")
    {
    patientMenuScreen:
        menuChoice = printPatientMenu();
        nextStep = choosePatientFunctionality(menuChoice);
        if (nextStep == "menuScreen")
        {
            goto patientMenuScreen;
        }
        else if (nextStep == "loginScreen")
        {
            goto loginScreen;
        }
    }
}

void initializeArrays()
{
    // Used to initialize global arrays at the start of the program.
    usernames[0] = "Ashhad";
    passwords[0] = "123";
    userRoles[0] = "Admin";
    registrationNumbers[0] = 1;
    for (int idx = 0; idx < userArrSize; idx++)
    {
        patientBills[idx] = "-1";
    }
    for (int idx = 0; idx < userArrSize; idx++)
    {
        orderedTests[idx] = "Not Ordered Yet";
    }
    for (int idx = 0; idx < userArrSize; idx++)
    {
        testResults[idx] = "Null";
    }
    for (int idx = 0; idx < userArrSize; idx++)
    {
        prescribedMedicines[idx] = "No Prescription Yet";
    }
    for (int idx = 0; idx < userArrSize; idx++)
    {
        prescribedMedicineAmounts[idx] = "-1";
    }
    for (int idx = 0; idx < userArrSize; idx++)
    {
        diseases[idx] = "No Diagnosis Yet";
    }
    for (int idx = 0; idx < userArrSize; idx++)
    {
        hosptialReviewStars[idx] = "-1";
    }
    for (int idx = 0; idx < userArrSize; idx++)
    {
        hospitalReviewStatements[idx] = "Null";
    }
    for (int idx = 0; idx < userArrSize; idx++)
    {
        appointmentDoctorRegistrationNumbers[idx] = "-1";
    }
    for (int idx = 0; idx < userArrSize; idx++)
    {
        scheduledAppointmentDoctor[idx] = "No";
    }
    for (int idx = 0; idx < userArrSize; idx++)
    {
        appointmentDates[idx] = "Null";
    }
}

void loadAdminRecordFromFile()
{
    // Used to load the admin record from text file to arrays.
    string line;
    fstream file;
    file.open("admin.txt", ios::in);
    while (getline(file, line))
    {
        userRoles[0] = parsing(line, 1);
        usernames[0] = parsing(line, 2);
        passwords[0] = parsing(line, 3);
        registrationNumbers[0] = stoi(parsing(line, 4));
    }
    file.close();
}

void writeAdminRecordInFile()
{
    // Used to write complete admin record to text file.
    fstream file;
    file.open("admin.txt", ios::out);
    file << userRoles[0] << ",";
    file << usernames[0] << ",";
    file << passwords[0] << ",";
    file << registrationNumbers[0];
    file.close();
}

void appendDoctorRecordInFile(int idx)
{
    // Used to add a doctor record to text file.
    fstream file;
    file.open("doctors.txt", ios::app);
    file << userRoles[idx] << ",";
    file << usernames[idx] << ",";
    file << passwords[idx] << ",";
    file << registrationNumbers[idx] << ",";
    file << doctorSalaries[idx] << ",";
    file << scheduledAppointmentDoctor[idx] << ",";
    file << hosptialReviewStars[idx] << ",";
    file << hospitalReviewStatements[idx] << "\n";
    file.close();
}

void loadDoctorRecordsFromFile()
{
    // Used to load all doctor records from text file to arrays.
    string line;
    fstream file;
    file.open("doctors.txt", ios::in);
    while (getline(file, line))
    {
        userRoles[currentUsers] = parsing(line, 1);
        usernames[currentUsers] = parsing(line, 2);
        passwords[currentUsers] = parsing(line, 3);
        registrationNumbers[currentUsers] = stoi(parsing(line, 4));
        doctorSalaries[currentUsers] = parsing(line, 5);
        scheduledAppointmentDoctor[currentUsers] = parsing(line, 6);
        hosptialReviewStars[currentUsers] = parsing(line, 7);
        hospitalReviewStatements[currentUsers] = parsing(line, 8);
        currentUsers++;
    }
    file.close();
}

void writeAllDoctorRecordsInFile()
{
    // Used to re-write all doctor records in text file.
    fstream file;
    file.open("doctors.txt", ios::out);
    for (int idx = 0; idx < currentUsers; idx++)
    {
        if (userRoles[idx] == "Doctor")
        {
            file << userRoles[idx] << ",";
            file << usernames[idx] << ",";
            file << passwords[idx] << ",";
            file << registrationNumbers[idx] << ",";
            file << doctorSalaries[idx] << ",";
            file << scheduledAppointmentDoctor[idx] << ",";
            file << hosptialReviewStars[idx] << ",";
            file << hospitalReviewStatements[idx] << "\n";
        }
    }
    file.close();
}

void appendPatientRecordInFile(int idx)
{
    // Used to add a patient record in text file.
    fstream file;
    file.open("patients.txt", ios::app);
    file << userRoles[idx] << ",";
    file << usernames[idx] << ",";
    file << passwords[idx] << ",";
    file << registrationNumbers[idx] << ",";
    file << patientBills[idx] << ",";
    file << orderedTests[idx] << ",";
    file << testResults[idx] << ",";
    file << diseases[idx] << ",";
    file << prescribedMedicines[idx] << ",";
    file << prescribedMedicineAmounts[idx] << ",";
    file << appointmentDates[idx] << ",";
    file << appointmentDoctorRegistrationNumbers[idx] << ",";
    file << hosptialReviewStars[idx] << ",";
    file << hospitalReviewStatements[idx] << "\n";
    file.close();
}

void loadPatientRecordsFromFile()
{
    // Used to load all patient records from text file to arrays.
    string line;
    fstream file;
    file.open("patients.txt", ios::in);
    while (getline(file, line))
    {
        userRoles[currentUsers] = parsing(line, 1);
        usernames[currentUsers] = parsing(line, 2);
        passwords[currentUsers] = parsing(line, 3);
        registrationNumbers[currentUsers] = stoi(parsing(line, 4));
        patientBills[currentUsers] = parsing(line, 5);
        orderedTests[currentUsers] = parsing(line, 6);
        testResults[currentUsers] = parsing(line, 7);
        diseases[currentUsers] = parsing(line, 8);
        prescribedMedicines[currentUsers] = parsing(line, 9);
        prescribedMedicineAmounts[currentUsers] = parsing(line, 10);
        appointmentDates[currentUsers] = parsing(line, 11);
        appointmentDoctorRegistrationNumbers[currentUsers] = parsing(line, 12);
        hosptialReviewStars[currentUsers] = parsing(line, 13);
        hospitalReviewStatements[currentUsers] = parsing(line, 14);
        currentUsers++;
    }
    file.close();
}

void writeAllPatientRecordsInFile()
{
    // Used to re-write all patient records to text file.
    fstream file;
    file.open("patients.txt", ios::out);
    for (int idx = 0; idx < currentUsers; idx++)
    {
        if (userRoles[idx] == "Patient")
        {
            file << userRoles[idx] << ",";
            file << usernames[idx] << ",";
            file << passwords[idx] << ",";
            file << registrationNumbers[idx] << ",";
            file << patientBills[idx] << ",";
            file << orderedTests[idx] << ",";
            file << testResults[idx] << ",";
            file << diseases[idx] << ",";
            file << prescribedMedicines[idx] << ",";
            file << prescribedMedicineAmounts[idx] << ",";
            file << appointmentDates[idx] << ",";
            file << appointmentDoctorRegistrationNumbers[idx] << ",";
            file << hosptialReviewStars[idx] << ",";
            file << hospitalReviewStatements[idx] << "\n";
        }
    }
    file.close();
}

void appendMedicineRecordInFile(int idx)
{
    // Used to add a Medicine Record in text file.
    fstream file;
    file.open("medicines.txt", ios::app);
    file << medicineNames[idx] << ",";
    file << medicinePrices[idx] << ",";
    file << medicineAmounts[idx] << "\n";
    file.close();
}

void loadMedicineRecordsFromFile()
{
    // Used to load all medicine records from text file to arrays.
    string line;
    fstream file;
    file.open("medicines.txt", ios::in);
    while (getline(file, line))
    {
        medicineNames[currentMedicines] = parsing(line, 1);
        medicinePrices[currentMedicines] = parsing(line, 2);
        medicineAmounts[currentMedicines] = parsing(line, 3);
        currentMedicines++;
    }
    file.close();
}

void writeAllMedicineRecordsInFile()
{
    // Used to re-write all medicine records to text file.
    fstream file;
    file.open("medicines.txt", ios::out);
    for (int idx = 0; idx < currentMedicines; idx++)
    {
        file << medicineNames[idx] << ",";
        file << medicinePrices[idx] << ",";
        file << medicineAmounts[idx] << "\n";
    }
    file.close();
}

string parsing(string line, int num)
{
    // Used to seperate each value from a complete record coming from text file.
    int count = 1;
    string temp = "";
    for (int i = 0; i < line.length(); i++)
    {
        if (line[i] == ',')
        {
            count++;
        }
        else if (count == num)
        {
            temp = temp + line[i];
        }
    }
    return temp;
}

void printHeader()
{
    // Used to print the header of the application.
    cout << endl;
    useRedColour();
    cout << "************************************************************************************************************************" << endl;
    cout << "********************************************** ";
    useWhiteColour();
    cout << "Hospital Management System ";
    useRedColour();
    cout << "**********************************************" << endl;
    cout << "************************************************************************************************************************" << endl;
    cout << endl;
    useWhiteColour();
}

void printSubHeader(string heading)
{
    // Used to print the subheader of the application.
    cout << heading << endl;
    useRedColour();
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << endl;
    useWhiteColour();
}

void printNewScreen(string subHeader)
{
    // Used to print the header and subheader of a new screen.
    system("cls");
    printHeader();
    printSubHeader(subHeader);
}

string loginScreen()
{
    // Used to print the login screen of the application.
    string Username, Password, UserRole = "invalid";
    while (UserRole == "invalid")
    {
        printNewScreen("Login Screen");
        cout << "Test Account:" << endl;
        cout << endl;
        cout << "Username: " << usernames[0] << endl;
        cout << "Password: " << passwords[0] << endl;
        cout << "Role    : " << userRoles[0] << endl;
        cout << endl;
        cout << "Use this account to login initially. More accounts can be added by admin after logging in." << endl;
        cout << endl;
        cout << "Enter username: ";
        cin >> ws;
        getline(cin, Username);
        cout << "Enter password: ";
        cin >> ws;
        getline(cin, Password);
        UserRole = loginValidation(Username, Password);
        if (UserRole == "invalid")
        {
            useRedColour();
            cout << endl;
            cout << "Invalid Username or Password" << endl;
            cout << "Please Try Again" << endl;
            useWhiteColour();
            cout << endl;
            cout << "Press any key to continue....." << endl;
            getch();
        }
    }
    return UserRole;
}

string loginValidation(string Username, string Password)
{
    // Used to validate the username and password.
    string loggedInUserRole = "invalid";
    for (int idx = 0; idx < userArrSize; idx++)
    {
        if ((Username == usernames[idx]) && (Password == passwords[idx]))
        {
            loggedInIndex = idx;
            loggedInUser = usernames[idx];
            loggedInPassword = passwords[idx];
            loggedInRegistrationNumber = registrationNumbers[idx];
            loggedInUserRole = userRoles[idx];
            break;
        }
    }
    return loggedInUserRole;
}

string printAdminMenu()
{
    // Used to print the admin's menu.
PrintAdminMenu:
    bool isInputCorrect;
    string choice;
    printNewScreen("Admin Menu");
    cout << "1.           View my own Record" << endl;
    cout << "2.           Edit my Credentials" << endl;
    cout << "3.           Add a new record" << endl;
    cout << "4.           Remove an old record" << endl;
    cout << "5.           View records" << endl;
    cout << "6.           View dispensary inventory" << endl;
    cout << "7.           Update dispensary inventory" << endl;
    cout << "8.           View prices of medicines" << endl;
    cout << "9.           Update prices of medicines" << endl;
    cout << "10.          View doctors' schedules" << endl;
    cout << "11.          Add a patient's bill" << endl;
    cout << "12.          Update a patient's bill" << endl;
    cout << "13.          Update a doctor's salary" << endl;
    cout << "14.          View hospital service reviews" << endl;
    cout << "15.          Logout" << endl;
    cout << endl;
    cout << "Enter your choice:   ";
    cin >> ws;
    getline(cin, choice);
    isInputCorrect = validateNumericInput(choice);
    if (isInputCorrect == true)
    {
        isInputCorrect = validateAdminMenuInput(choice);
    }
    if (isInputCorrect == false)
    {
        printInvalidInputScreen();
        goto PrintAdminMenu;
    }
    return choice;
}

bool validateAdminMenuInput(string choice)
{
    // Used to validate the input in Admin menu screen.
    bool isInputCorrect = false;
    if (stoi(choice) >= 1 && stoi(choice) <= 15)
    {
        isInputCorrect = true;
    }
    return isInputCorrect;
}

string chooseAdminFunctionality(string menuChoice)
{
    // Used to choose which admin function is to be executed.
    string nextStep, logoutChoice;
    if (menuChoice == "1")
    {
        viewOwnRecord();
        nextStep = "menuScreen";
    }
    if (menuChoice == "2")
    {
        editPersonalDetails();
        nextStep = "menuScreen";
    }
    if (menuChoice == "3")
    {
        addRecordAdmin();
        nextStep = "menuScreen";
    }
    else if (menuChoice == "4")
    {
        removeRecordAdmin();
        nextStep = "menuScreen";
    }
    else if (menuChoice == "5")
    {
        viewRecordsAdmin();
        nextStep = "menuScreen";
    }
    else if (menuChoice == "6")
    {
        viewDispensaryInventory();
        nextStep = "menuScreen";
    }
    else if (menuChoice == "7")
    {
        updateDispensaryInventory();
        nextStep = "menuScreen";
    }
    else if (menuChoice == "8")
    {
        viewMedicinePrices();
        nextStep = "menuScreen";
    }
    else if (menuChoice == "9")
    {
        updateMedicinePrices();
        nextStep = "menuScreen";
    }
    else if (menuChoice == "10")
    {
        viewDoctorSchedules();
        nextStep = "menuScreen";
    }
    else if (menuChoice == "11")
    {
        addPatientBill();
        nextStep = "menuScreen";
    }
    else if (menuChoice == "12")
    {
        updatePatientBill();
        nextStep = "menuScreen";
    }
    else if (menuChoice == "13")
    {
        updateDoctorSalary();
        nextStep = "menuScreen";
    }
    else if (menuChoice == "14")
    {
        viewHospitalServiceReviews();
        nextStep = "menuScreen";
    }
    else if (menuChoice == "15")
    {
        logoutChoice = inputLogoutChoice();
        printNewScreen("Logout");
        nextStep = printSessionEndScreen(logoutChoice);
    }
    return nextStep;
}

void addRecordAdmin()
{
    // Used to add a new record by an admin.
AddRecordAdmin:
    string choice;
    printNewScreen("Add a new Record");
    cout << endl;
    cout << "Whose record would you like to enter?" << endl;
    cout << "1.      Doctor" << endl;
    cout << "2.      Patient" << endl;
    cout << endl;
    cout << "Enter your choice:   ";
    cin >> ws;
    getline(cin, choice);
    if (choice == "1")
    {
        addDoctorRecord();
    }
    else if (choice == "2")
    {
        addPatientRecord();
    }
    else
    {
        printInvalidInputScreen();
        goto AddRecordAdmin;
    }
}

void addDoctorRecord()
{
    // Used to add a doctor's record.
AddDoctorRecord:
    bool isInputCorrect;
    printNewScreen("Add Doctor's Record");
    cout << "Enter name: ";
    cin >> ws;
    getline(cin, usernames[currentUsers]);
    isInputCorrect = validateUsername(usernames[currentUsers]);
    if (isInputCorrect == false)
    {
        printInvalidUsernameScreen();
        goto AddDoctorRecord;
    }
    cout << "Enter account password: ";
    cin >> ws;
    getline(cin, passwords[currentUsers]);
    isInputCorrect = isPasswordUnique(passwords[currentUsers]);
    if (isInputCorrect == false)
    {
        printPasswordInUseScreen();
        goto AddDoctorRecord;
    }
    cout << "Enter current salary: ";
    cin >> ws;
    getline(cin, doctorSalaries[currentUsers]);
    isInputCorrect = validateNumericInput(doctorSalaries[currentUsers]);
    if (isInputCorrect == false)
    {
        printInvalidInputScreen();
        goto AddDoctorRecord;
    }
    userRoles[currentUsers] = "Doctor";
    registrationNumbers[currentUsers] = assignRegistrationNumber();
    appendDoctorRecordInFile(currentUsers);
    currentUsers++;
    cout << endl;
    cout << "Doctor's Record successfully added" << endl;
    cout << endl;
    cout << "Press any key to continue....." << endl;
    getch();
}

void addPatientRecord()
{
    // Used to add a patient's record.
AddPatientRecord:
    bool isInputCorrect;
    printNewScreen("Add Patient's Record");
    cout << "Enter name: ";
    cin >> ws;
    getline(cin, usernames[currentUsers]);
    isInputCorrect = validateUsername(usernames[currentUsers]);
    if (isInputCorrect == false)
    {
        printInvalidUsernameScreen();
        goto AddPatientRecord;
    }
    cout << "Enter account password: ";
    cin >> ws;
    getline(cin, passwords[currentUsers]);
    isInputCorrect = isPasswordUnique(passwords[currentUsers]);
    if (isInputCorrect == false)
    {
        printPasswordInUseScreen();
        goto AddPatientRecord;
    }
    userRoles[currentUsers] = "Patient";
    registrationNumbers[currentUsers] = assignRegistrationNumber();
    appendPatientRecordInFile(currentUsers);
    currentUsers++;
    cout << endl;
    cout << "Patient's Record successfully added" << endl;
    cout << endl;
    cout << "Press any key to continue....." << endl;
    getch();
}

void printPasswordInUseScreen()
{
    // Used to show on screen that given password is already in use.
    useRedColour();
    cout << endl;
    cout << "This Password is already in use" << endl;
    cout << endl;
    cout << "Please try Again." << endl;
    useWhiteColour();
    cout << endl;
    cout << "Press any key to continue.....";
    getch();
}

void removeRecordAdmin()
{
    // Used to remove a record by an admin.
RemoveRecordAdmin:
    printNewScreen("Remove Record");
    string RegistrationNumber;
    int idx;
    bool isInputCorrect;
    cout << "Enter the registration number of the user: ";
    cout << endl;
    cout << "Registration Number:       ";
    cin >> ws;
    getline(cin, RegistrationNumber);
    isInputCorrect = validateNumericInput(RegistrationNumber);
    if (isInputCorrect == false)
    {
        printInvalidInputScreen();
        goto RemoveRecordAdmin;
    }
    idx = searchRecord(stoi(RegistrationNumber));
    displayRecord(idx);
    if (idx == -1)
    {
        printRecordNotFoundScreen();
        goto RemoveRecordAdmin;
    }
    else
    {
        shiftUserRecordIndexes(idx);
        currentUsers--;
        writeAllPatientRecordsInFile();
        writeAllDoctorRecordsInFile();
        cout << endl;
        cout << "Record successfully removed" << endl;
        cout << endl;
        cout << "Press any key to continue....." << endl;
        getch();
    }
}

void shiftUserRecordIndexes(int recordNumber)
{
    // Used to remove a complete record from arrays.
    for (int idx = recordNumber; idx < currentUsers; idx++)
    {
        usernames[idx] = usernames[idx + 1];
        passwords[idx] = passwords[idx + 1];
        userRoles[idx] = userRoles[idx + 1];
        registrationNumbers[idx] = registrationNumbers[idx + 1];
        appointmentDates[idx] = appointmentDates[idx + 1];
        appointmentDoctorRegistrationNumbers[idx] = appointmentDoctorRegistrationNumbers[idx + 1];
        patientBills[idx] = patientBills[idx + 1];
        prescribedMedicines[idx] = prescribedMedicines[idx + 1];
        prescribedMedicineAmounts[idx] = prescribedMedicineAmounts[idx + 1];
        diseases[idx] = diseases[idx + 1];
        orderedTests[idx] = orderedTests[idx + 1];
        testResults[idx] = testResults[idx + 1];
        scheduledAppointmentDoctor[idx] = scheduledAppointmentDoctor[idx + 1];
        doctorSalaries[idx] = doctorSalaries[idx + 1];
        hosptialReviewStars[idx] = hosptialReviewStars[idx + 1];
    }
}

void viewRecordsAdmin()
{
    // Used to view records by admin.
    string choice;
ViewRecordsAdmin:
    printNewScreen("View Records");
    cout << endl;
    cout << "What do you want to do?" << endl;
    cout << endl;
    cout << "1.     Search a particular record" << endl;
    cout << "2.     View all records" << endl;
    cout << endl;
    cout << "Enter your choice: ";
    cin >> ws;
    getline(cin, choice);
    if (choice == "1")
    {
        searchRecordAdmin();
    }
    else if (choice == "2")
    {
        viewAllRecordsAdmin();
    }
    else
    {
        printInvalidInputScreen();
        goto ViewRecordsAdmin;
    }
}

void searchRecordAdmin()
{
    // Used to search and view the details of a particular record by admin.
SearchRecordAdmin:
    int index;
    string RegistrationNumber;
    bool isInputCorrect;
    printNewScreen("Search a Particular Record");
    cout << endl;
    cout << "Enter the registration number of the record you want to search" << endl;
    cout << endl;
    cout << "Registration Number: ";
    cin >> ws;
    getline(cin, RegistrationNumber);
    isInputCorrect = validateNumericInput(RegistrationNumber);
    if (isInputCorrect == false)
    {
        printInvalidInputScreen();
        goto SearchRecordAdmin;
    }
    index = searchRecord(stoi(RegistrationNumber));
    if (userRoles[index] == "Doctor")
    {
        cout << endl;
        cout << "Record successfully found" << endl;
        displayRecord(index);
        cout << "Press any key to continue.....";
        getch();
    }
    if (userRoles[index] == "Patient")
    {
        cout << endl;
        cout << "Record successfully found" << endl;
        displayRecord(index);
        cout << endl;
        cout << "Press any key to continue.....";
        getch();
    }
    if (index == -1)
    {
        printRecordNotFoundScreen();
        goto SearchRecordAdmin;
    }
}

void viewAllRecordsAdmin()
{
    // Used to view all currently stored records by an admin.
    bool recordFound = false;
    printNewScreen("View all Records");
    for (int idx = 0; idx < currentUsers; idx++)
    {
        if (userRoles[idx] == "Doctor")
        {
            recordFound = true;
            displayRecord(idx);
        }
        else if (userRoles[idx] == "Patient")
        {
            recordFound = true;
            displayRecord(idx);
        }
    }
    if (recordFound == false)
    {
        printNoRecordFoundScreen();
    }
    cout << endl;
    cout << "Press any key to continue.....";
    getch();
}

void viewDispensaryInventory()
{
    // Used to view the inventory of the dispensary.
    printNewScreen("View Dispensary Inventory");
    for (int i = 0; i < currentMedicines; i++)
    {
        cout << medicineNames[i] << " : " << medicineAmounts[i] << endl;
    }
    if (currentMedicines <= 0)
    {
        printNoRecordFoundScreen();
    }
    cout << endl;
    cout << "Press any key to continue........" << endl;
    getch();
}

void updateDispensaryInventory()
{
    // Used to update the inventory of the dispensary.
updateInventory:
    string choice;
    printNewScreen("Update Dispensary Inventory");
    cout << "What would you like to do?" << endl;
    cout << endl;
    cout << "1. Update the amount of a medicine" << endl;
    cout << "2. Add a new medicine to the inventory" << endl;
    cout << endl;
    cout << "Enter your choice: ";
    cin >> ws;
    getline(cin, choice);
    if (choice == "1")
    {
        updateMedicine();
    }
    else if (choice == "2")
    {
        addMedicine();
    }
    else
    {
        printInvalidInputScreen();
        goto updateInventory;
    }
}

void updateMedicine()
{
    // Used to update the amount of a particular medicine in the inventory.
updateMedicine:
    int amountToAdd;
    string medicineToUpdate, UpdatedAmount;
    bool isInputCorrect;
    if (currentMedicines >= 1)
    {
        printNewScreen("Update Medicine Amount");
        for (int i = 0; i < currentMedicines; i++)
        {
            cout << i + 1 << ".  " << medicineNames[i] << endl;
        }
        cout << endl;
        cout << "Which medicine to update?     :        ";
        cin >> ws;
        getline(cin, medicineToUpdate);
        isInputCorrect = validateNumericInput(medicineToUpdate);
        if (isInputCorrect == true)
        {
            isInputCorrect = validateMedicineInput(medicineToUpdate);
        }
        cout << endl;
        if (isInputCorrect == true)
        {
            cout << "Current number of " << medicineNames[stoi(medicineToUpdate) - 1] << ":         " << medicineAmounts[stoi(medicineToUpdate) - 1] << endl;
            cout << endl;
        EnterUpdatedAmount:
            cout << "What is the updated amount of " << medicineNames[stoi(medicineToUpdate) - 1] << "?" << endl;
            cin >> ws;
            getline(cin, UpdatedAmount);
            isInputCorrect = validateNumericInput(UpdatedAmount);
            if (isInputCorrect == false)
            {
                printInvalidInputScreen();
                cout << endl;
                cout << endl;
                goto EnterUpdatedAmount;
            }
            cout << endl;
            medicineAmounts[stoi(medicineToUpdate) - 1] = UpdatedAmount;
            cout << "Number of " << medicineNames[stoi(medicineToUpdate) - 1] << " successfully updated" << endl;
            cout << endl;
            cout << "Updated number of " << medicineNames[stoi(medicineToUpdate) - 1] << ":         " << medicineAmounts[stoi(medicineToUpdate) - 1] << endl;
            cout << endl;
            cout << "Press any key to continue........" << endl;
            writeAllMedicineRecordsInFile();
            getch();
        }
        else
        {
            printInvalidInputScreen();
            goto updateMedicine;
        }
    }
    else if (currentMedicines <= 0)
    {
        printNoRecordFoundScreen();
        cout << endl;
        cout << "Press any key to continue.....";
        getch();
    }
}

void addMedicine()
{
    // Used to add a new medicine to the inventory.
    bool isInputCorrect;
    printNewScreen("Add new Medicine");
    cout << "Enter the name of the medicine you would like to add:  ";
    cin >> ws;
    getline(cin, medicineNames[currentMedicines]);
EnterMedicineAmount:
    cout << "Enter the amount of medicine:  ";
    cin >> ws;
    getline(cin, medicineAmounts[currentMedicines]);
    isInputCorrect = validateNumericInput(medicineAmounts[currentMedicines]);
    if (isInputCorrect == false)
    {
        printInvalidInputScreen();
        cout << endl;
        cout << endl;
        goto EnterMedicineAmount;
    }
EnterMedicinePrice:
    cout << "Enter the price of the medicine:   ";
    cin >> medicinePrices[currentMedicines];
    isInputCorrect = validateNumericInput(medicinePrices[currentMedicines]);
    if (isInputCorrect == false)
    {
        printInvalidInputScreen();
        cout << endl;
        cout << endl;
        goto EnterMedicinePrice;
    }
    cout << endl;
    cout << medicineNames[currentMedicines] << " successfully added to the dispensary inventory" << endl;
    cout << endl;
    appendMedicineRecordInFile(currentMedicines);
    currentMedicines++;
    cout << "Press any key to continue.....";
    getch();
}

void viewMedicinePrices()
{
    // Used to view the prices of all medicines in the inventory.
    printNewScreen("View Medicine Prices");
    for (int i = 0; i < currentMedicines; i++)
    {
        cout << medicineNames[i] << "   :   Rs. " << medicinePrices[i] << endl;
    }
    if (currentMedicines <= 0)
    {
        printNoRecordFoundScreen();
    }
    cout << endl;
    cout << "Press any key to continue........";
    getch();
}

void updateMedicinePrices()
{
    // Used to update the price of a particular medicine.
UpdateMedicinePrices:
    string medicineToUpdate;
    bool isInputCorrect;
    if (currentMedicines >= 1)
    {
        printNewScreen("Update Medicine Prices");
        for (int i = 0; i < currentMedicines; i++)
        {
            cout << i + 1 << ".  " << medicineNames[i] << endl;
        }
        cout << endl;
        cout << "Which medicine's price to update?     :        ";
        cin >> ws;
        getline(cin, medicineToUpdate);
        isInputCorrect = validateNumericInput(medicineToUpdate);
        if (isInputCorrect == true)
        {
            isInputCorrect = validateMedicineInput(medicineToUpdate);
        }
        if (isInputCorrect == false)
        {
            printInvalidInputScreen();
            goto UpdateMedicinePrices;
        }
        cout << endl;
        cout << "Current price of " << medicineNames[stoi(medicineToUpdate) - 1] << "     :        Rs. " << medicinePrices[stoi(medicineToUpdate) - 1] << endl;
        cout << endl;
    EnterNewPrice:
        string newPrice;
        cout << "What do you want the new price for " << medicineNames[stoi(medicineToUpdate) - 1] << " to be?" << endl;
        cin >> ws;
        getline(cin, newPrice);
        isInputCorrect = validateNumericInput(newPrice);
        if (isInputCorrect == false)
        {
            printInvalidInputScreen();
            cout << endl;
            cout << endl;
            goto EnterNewPrice;
        }
        medicinePrices[stoi(medicineToUpdate) - 1] = newPrice;
        cout << endl;
        cout << "Price of " << medicineNames[stoi(medicineToUpdate) - 1] << " successfully updated" << endl;
        cout << endl;
        cout << "New price of " << medicineNames[stoi(medicineToUpdate) - 1] << ": "
             << "Rs. " << medicinePrices[stoi(medicineToUpdate) - 1] << endl;
        cout << endl;
        cout << "Press any key to continue........" << endl;
        writeAllMedicineRecordsInFile();
        getch();
    }
    else if (currentMedicines <= 0)
    {
        printNoRecordFoundScreen();
        cout << endl;
        cout << "Press any key to continue.....";
        getch();
    }
}

void viewDoctorSchedules()
{
    // Used by admins to view doctors' schedules by an admin.
    printNewScreen("View Doctors' Schedules");
    for (int idx = 0; idx < currentUsers; idx++)
    {
        if (userRoles[idx] == "Doctor")
        {
            cout << endl;
            cout << "Dr. " << usernames[idx] << ":" << endl;
            if (scheduledAppointmentDoctor[idx] == "Yes")
            {
                for (int j = 0; j < currentUsers; j++)
                {
                    if (appointmentDoctorRegistrationNumbers[j] == to_string(registrationNumbers[idx]))
                    {
                        cout << endl;
                        cout << "Appointment Date: " << appointmentDates[j] << endl;
                        cout << "Patient Name    : " << usernames[j] << endl;
                        cout << endl;
                    }
                }
            }
            else if (scheduledAppointmentDoctor[idx] == "No")
            {
                cout << endl;
                cout << "No Appointment Scheduled" << endl;
                cout << endl;
            }
        }
    }
    cout << "Press any key to continue.....";
    getch();
}

void addPatientBill()
{
    // Used to enter a patient's bill to the system.
AddPatientBill:
    printNewScreen("Add Patient's Bill");
    string RegistrationNumber;
    int idx;
    bool isInputCorrect;
    cout << "Enter the registration number of the patient: ";
    cout << endl;
    cout << "Registration Number:       ";
    cin >> ws;
    getline(cin, RegistrationNumber);
    isInputCorrect = validateNumericInput(RegistrationNumber);
    if (isInputCorrect == false)
    {
        printInvalidInputScreen();
        goto AddPatientBill;
    }
    cout << endl;
    idx = searchRecord(stoi(RegistrationNumber));
    if (userRoles[idx] == "Patient")
    {
        cout << endl;
        cout << "Record Successfully Found" << endl;
        cout << endl;
        if (patientBills[idx] == "-1")
        {
        EnterBill:
            string bill;
            cout << "Enter the amount: ";
            cin >> ws;
            getline(cin, bill);
            isInputCorrect = validateNumericInput(bill);
            if (isInputCorrect == false)
            {
                printInvalidInputScreen();
                cout << endl;
                cout << endl;
                goto EnterBill;
            }
            patientBills[idx] = bill;
            cout << endl;
            cout << "Patient's Bill has been successfully added" << endl;
            cout << endl;
            cout << usernames[idx] << "'s bill: Rs. " << patientBills[idx] << endl;
            cout << endl;
            cout << "Press any key to continue........" << endl;
            getch();
            writeAllPatientRecordsInFile();
        }
        else if (patientBills[idx] != "-1")
        {
            cout << usernames[idx] << "'s bill has already been added." << endl;
            cout << endl;
            cout << "Press any key to continue........";
            getch();
        }
    }
    else
    {
        printRecordNotFoundScreen();
        goto AddPatientBill;
    }
}

void updatePatientBill()
{
    // Used to update a patient's bill in the database.
UpdatePatientBill:
    printNewScreen("Update Patient's Bill");
    string RegistrationNumber;
    int idx;
    bool isInputCorrect;
    cout << "Enter the registration number of the patient: ";
    cout << endl;
    cout << "Registration Number:       ";
    cin >> ws;
    getline(cin, RegistrationNumber);
    isInputCorrect = validateNumericInput(RegistrationNumber);
    if (isInputCorrect == false)
    {
        printInvalidInputScreen();
        goto UpdatePatientBill;
    }
    cout << endl;
    idx = searchRecord(stoi(RegistrationNumber));
    if (userRoles[idx] == "Patient")
    {
        if (stoi(patientBills[idx]) >= 0)
        {
            string newBill;
            cout << usernames[idx] << "'s Current Bill :   Rs. " << patientBills[idx] << endl;
            cout << endl;
        EnterNewBill:
            cout << "Enter new bill:" << endl;
            cin >> ws;
            getline(cin, newBill);
            isInputCorrect = validateNumericInput(newBill);
            if (isInputCorrect == false)
            {
                printInvalidInputScreen();
                cout << endl;
                cout << endl;
                goto EnterNewBill;
            }
            patientBills[idx] = newBill;
            cout << endl;
            cout << usernames[idx] << "'s bill has been successfully updated" << endl;
            cout << endl;
            cout << usernames[idx] << "'s Updated Bill :   Rs. " << patientBills[idx] << endl;
            cout << endl;
            cout << "Press any key to continue........" << endl;
            getch();
            writeAllPatientRecordsInFile();
        }
        else
        {
            cout << usernames[idx] << "'s bill has not been added yet." << endl;
            cout << endl;
            cout << "Press any key to continue........" << endl;
            getch();
        }
    }
    else
    {
        printRecordNotFoundScreen();
        goto UpdatePatientBill;
    }
}

void updateDoctorSalary()
{
    // Used to update the salary of a doctor in the database.
UpdateDoctorSalary:
    printNewScreen("Update Doctor's salary");
    string RegistrationNumber;
    int idx;
    bool isInputCorrect;
    cout << "Enter the registration number of the doctor: ";
    cout << endl;
    cout << "Registration Number:       ";
    cin >> ws;
    getline(cin, RegistrationNumber);
    isInputCorrect = validateNumericInput(RegistrationNumber);
    if (isInputCorrect == false)
    {
        printInvalidInputScreen();
        goto UpdateDoctorSalary;
    }
    idx = searchRecord(stoi(RegistrationNumber));
    cout << endl;
    if (userRoles[idx] == "Doctor")
    {
    EnterNewSalary:
        string newSalary;
        cout << usernames[idx] << "'s Current Salary :   Rs. " << doctorSalaries[idx] << endl;
        cout << endl;
        cout << "Enter new salary     :   ";
        cin >> ws;
        getline(cin, newSalary);
        isInputCorrect = validateNumericInput(newSalary);
        if (isInputCorrect == false)
        {
            printInvalidInputScreen();
            cout << endl;
            cout << endl;
            goto EnterNewSalary;
        }
        doctorSalaries[idx] = newSalary;
        cout << endl;
        cout << usernames[idx] << "'s salary has been successfully updated" << endl;
        cout << endl;
        cout << usernames[idx] << "'s Updated Salary :   Rs. " << doctorSalaries[idx] << endl;
        cout << endl;
        cout << "Press any key to continue........" << endl;
        getch();
        writeAllDoctorRecordsInFile();
    }
    else
    {
        printRecordNotFoundScreen();
        goto UpdateDoctorSalary;
    }
}

void viewHospitalServiceReviews()
{
    // Used by the admin to view the reviews on hospital services given by doctors and patients.
    bool reviewFound = false;
    printNewScreen("View Hospital Service Reviews");
    for (int idx = 0; idx < currentUsers; idx++)
    {
        if (userRoles[idx] == "Doctor" || userRoles[idx] == "Patient")
        {
            reviewFound = true;
            cout << usernames[idx] << "(" << userRoles[idx] << "):" << endl;
            if (stoi(hosptialReviewStars[idx]) >= 1)
            {
                cout << hosptialReviewStars[idx] << " Stars" << endl;
                cout << "\"" << hospitalReviewStatements[idx] << "\"" << endl;
            }
            else
            {
                cout << "No Review Added Yet" << endl;
            }
            cout << endl;
        }
    }
    if (reviewFound == false)
    {
        useRedColour();
        cout << endl;
        cout << "No Review Found" << endl;
        cout << endl;
        useWhiteColour();
    }
    cout << "Press any key to continue.....";
    getch();
}

string printDoctorMenu()
{
    // Used to print the doctor's menu screen and input the functionality required by the user.
PrintDoctorMenu:
    bool isInputCorrect;
    string choice;
    printNewScreen("Doctor Menu");
    cout << "1.           View my own Record" << endl;
    cout << "2.           Edit my Credentials" << endl;
    cout << "3.           View patient's records" << endl;
    cout << "4.           Diagnose patient" << endl;
    cout << "5.           Prescribe medicine to patients" << endl;
    cout << "6.           View schedule" << endl;
    cout << "7.           Give review on hospital services" << endl;
    cout << "8.           Order test for patient" << endl;
    cout << "9.           View test result of patients" << endl;
    cout << "10.          Add test result of patients" << endl;
    cout << "11.          Schedule an appointment" << endl;
    cout << "12.          Cancel an appointment" << endl;
    cout << "13.          Change an appointment date" << endl;
    cout << "14.          Logout" << endl;
    cout << endl;
    cout << "Enter your choice:   ";
    cin >> ws;
    getline(cin, choice);
    isInputCorrect = validateNumericInput(choice);
    if (isInputCorrect == true)
    {
        isInputCorrect = validateDoctorMenuInput(choice);
    }
    if (isInputCorrect == false)
    {
        printInvalidInputScreen();
        goto PrintDoctorMenu;
    }
    return choice;
}

bool validateDoctorMenuInput(string choice)
{
    // Used to validate the input from doctor menu.
    bool isInputCorrect = false;
    if (stoi(choice) >= 1 && stoi(choice) <= 14)
    {
        isInputCorrect = true;
    }
    return isInputCorrect;
}

string chooseDoctorFunctionality(string menuChoice)
{
    // Used to choose which doctor functionality to execute next.
    string nextStep, logoutChoice;
    if (menuChoice == "1")
    {
        viewOwnRecord();
        nextStep = "menuScreen";
    }
    else if (menuChoice == "2")
    {
        editPersonalDetails();
        nextStep = "menuScreen";
    }
    if (menuChoice == "3")
    {
        viewPatientRecords();
        nextStep = "menuScreen";
    }
    else if (menuChoice == "4")
    {
        diagnosePatient();
        nextStep = "menuScreen";
    }
    else if (menuChoice == "5")
    {
        prescribeMedicine();
        nextStep = "menuScreen";
    }
    else if (menuChoice == "6")
    {
        viewMySchedule();
        nextStep = "menuScreen";
    }
    else if (menuChoice == "7")
    {
        giveReview();
        nextStep = "menuScreen";
    }
    else if (menuChoice == "8")
    {
        orderTest();
        nextStep = "menuScreen";
    }
    else if (menuChoice == "9")
    {
        viewTestResult();
        nextStep = "menuScreen";
    }
    else if (menuChoice == "10")
    {
        addTestResult();
        nextStep = "menuScreen";
    }
    else if (menuChoice == "11")
    {
        scheduleAppointment();
        nextStep = "menuScreen";
    }
    else if (menuChoice == "12")
    {
        cancelAppointment();
        nextStep = "menuScreen";
    }
    else if (menuChoice == "13")
    {
        editAppointment();
        nextStep = "menuScreen";
    }
    else if (menuChoice == "14")
    {
        logoutChoice = inputLogoutChoice();
        printNewScreen("Logout");
        nextStep = printSessionEndScreen(logoutChoice);
    }
    return nextStep;
}

string printSessionEndScreen(string logoutChoice)
{
    // Used to print goodbye screen at the end of a user's session.
    string nextStep;
    cout << "Thank you for using the application" << endl;
    cout << endl;
    if (logoutChoice == "1")
    {
        cout << "You have been successfully logged out" << endl;
        cout << endl;
        cout << "Press any key to continue....." << endl;
        getch();
        nextStep = "loginScreen";
    }
    else if (logoutChoice == "2")
    {
        cout << "The program has been terminated" << endl;
        cout << endl;
        cout << "Press any key to continue....." << endl;
        nextStep = "endProgram";
        getch();
    }
    return nextStep;
}

void viewPatientRecords()
{
    // Used to view patient records by doctor.
    string choice;
ViewRecordsAdmin:
    printNewScreen("View Patient Records");
    cout << endl;
    cout << "What do you want to do?" << endl;
    cout << endl;
    cout << "1.     Search a particular record" << endl;
    cout << "2.     View all records" << endl;
    cout << endl;
    cout << "Enter your choice: ";
    cin >> ws;
    getline(cin, choice);
    if (choice == "1")
    {
        searchPatientRecord();
    }
    else if (choice == "2")
    {
        viewAllPatientRecords();
    }
    else
    {
        printInvalidInputScreen();
        goto ViewRecordsAdmin;
    }
}

void searchPatientRecord()
{
    // Used to search a particular record by admin.
SearchPatientRecord:
    printNewScreen("Search a particular Patient's Record");
    cout << endl;
    string RegistrationNumber;
    int idx;
    bool isInputCorrect;
    cout << "Enter the registration number of the patient: ";
    cout << endl;
    cout << "Registration Number:       ";
    cin >> ws;
    getline(cin, RegistrationNumber);
    isInputCorrect = validateNumericInput(RegistrationNumber);
    if (isInputCorrect == false)
    {
        printInvalidInputScreen();
        goto SearchPatientRecord;
    }
    idx = searchRecord(stoi(RegistrationNumber));
    if (userRoles[idx] == "Patient")
    {
        cout << endl;
        cout << "Record successfully found" << endl;
        cout << endl;
        displayRecord(idx);
        cout << endl;
        cout << "Press any key to continue.....";
        getch();
    }
    else
    {
        printRecordNotFoundScreen();
        goto SearchPatientRecord;
    }
}

void viewAllPatientRecords()
{
    // Used to view all patient records.
    printNewScreen("View all Patient Records");
    bool patientRecordPresent = false;
    for (int idx = 0; idx < currentUsers; idx++)
    {
        if (userRoles[idx] == "Patient")
        {
            patientRecordPresent = true;
            displayRecord(idx);
            cout << endl;
        }
    }
    if (patientRecordPresent == false)
    {
        cout << endl;
        cout << "No Patient Record Found" << endl;
        cout << endl;
    }
    cout << "Press any key to continue.....";
    getch();
}

void diagnosePatient()
{
    // Used to enter a patient's disease in the database.
DiagnosePatient:
    printNewScreen("Diagnose Patient");
    string RegistrationNumber;
    int idx;
    bool isInputCorrect;
    cout << "Enter the registration number of the patient: ";
    cout << endl;
    cout << "Registration Number:       ";
    cin >> ws;
    getline(cin, RegistrationNumber);
    isInputCorrect = validateNumericInput(RegistrationNumber);
    if (isInputCorrect == false)
    {
        printInvalidInputScreen();
        goto DiagnosePatient;
    }
    idx = searchRecord(stoi(RegistrationNumber));
    if (userRoles[idx] == "Patient")
    {
        cout << endl;
        cout << "Record successfully found" << endl;
        cout << endl;
        cout << "Enter the patient's disease:   ";
        cin >> ws;
        getline(cin, diseases[idx]);
        cout << endl;
        cout << usernames[idx] << " successfully diagnosed with " << diseases[idx] << endl;
        cout << endl;
        cout << "Press any key to continue........" << endl;
        getch();
        writeAllPatientRecordsInFile();
    }
    else
    {
        printRecordNotFoundScreen();
        goto DiagnosePatient;
    }
}

void prescribeMedicine()
{
    // Used to prescribe medicine to a patient.
PrescribeMedicine:
    printNewScreen("Prescribe Medicine to Patient");
    if (currentMedicines > 0)
    {
        string RegistrationNumber, MedicineToPrescribe;
        int idx;
        bool isInputCorrect;
        cout << "Enter the registration number of the patient: ";
        cout << endl;
        cout << "Registration Number:       ";
        cin >> ws;
        getline(cin, RegistrationNumber);
        isInputCorrect = validateNumericInput(RegistrationNumber);
        if (isInputCorrect == false)
        {
            printInvalidInputScreen();
            goto PrescribeMedicine;
        }
        idx = searchRecord(stoi(RegistrationNumber));
        if (userRoles[idx] == "Patient")
        {
            cout << endl;
            cout << "Record successfully found" << endl;
            cout << endl;
            for (int i = 0; i < currentMedicines; i++)
            {
                cout << i + 1 << ". " << medicineNames[i] << endl;
            }
        MedicineInput:
            cout << endl;
            cout << "Which medicine to prescribe?     :        ";
            cin >> ws;
            getline(cin, MedicineToPrescribe);
            isInputCorrect = validateNumericInput(MedicineToPrescribe);
            if (isInputCorrect == true)
            {
                isInputCorrect = validateMedicineInput(MedicineToPrescribe);
            }
            if (isInputCorrect == false)
            {
                printInvalidInputScreen();
                cout << endl;
                cout << endl;
                goto MedicineInput;
            }
            prescribedMedicines[idx] = medicineNames[stoi(MedicineToPrescribe) - 1];
        EnterMedicineAmount:
            cout << "Enter amount  :   ";
            cin >> ws;
            getline(cin, prescribedMedicineAmounts[idx]);
            isInputCorrect = validateNumericInput(prescribedMedicineAmounts[idx]);
            if (isInputCorrect == false)
            {
                printInvalidInputScreen();
                cout << endl;
                cout << endl;
                goto EnterMedicineAmount;
            }
            cout << endl;
            cout << "Medicine successfully prescribed" << endl;
            cout << endl;
            cout << "Press any key to continue........" << endl;
            getch();
            writeAllPatientRecordsInFile();
        }
        else
        {
            printRecordNotFoundScreen();
            goto PrescribeMedicine;
        }
    }
    else
    {
        useRedColour();
        cout << "No Medicine Available." << endl;
        useWhiteColour();
        cout << endl;
        cout << "Press any key to continue.....";
        getch();
    }
}

bool validateMedicineInput(string MedicinePrescribed)
{
    // Used to validate medicine input.
    bool isInputValid = false;
    if (stoi(MedicinePrescribed) >= 1 && stoi(MedicinePrescribed) <= currentMedicines)
    {
        isInputValid = true;
    }
    return isInputValid;
}

void viewMySchedule()
{
    // Used by doctors to view their schedule
    printNewScreen("View my Schedule");
    if (scheduledAppointmentDoctor[loggedInIndex] == "Yes")
    {
        for (int j = 0; j < currentUsers; j++)
        {
            if (appointmentDoctorRegistrationNumbers[j] == to_string(loggedInRegistrationNumber))
            {
                cout << endl;
                cout << "Appointment Date: " << appointmentDates[j] << endl;
                cout << "Patient Name    : " << usernames[j] << endl;
                cout << endl;
            }
        }
    }
    else if (scheduledAppointmentDoctor[loggedInIndex] == "No")
    {
        cout << endl;
        cout << "No Appointment Scheduled" << endl;
        cout << endl;
    }
    cout << "Press any key to continue.....";
    getch();
}

void orderTest()
{
    // Used to order a test for a patient.
OrderTest:
    printNewScreen("Order Test");
    string RegistrationNumber;
    int idx;
    bool isInputCorrect;
    cout << "Enter the registration number of the patient: ";
    cout << endl;
    cout << "Registration Number:       ";
    cin >> ws;
    getline(cin, RegistrationNumber);
    isInputCorrect = validateNumericInput(RegistrationNumber);
    if (isInputCorrect == false)
    {
        printInvalidInputScreen();
        goto OrderTest;
    }
    idx = searchRecord(stoi(RegistrationNumber));
    if (userRoles[idx] == "Patient")
    {
        cout << endl;
        cout << "Record successfully found" << endl;
        cout << endl;
        cout << "Enter test:   ";
        cin >> ws;
        getline(cin, orderedTests[idx]);
        cout << endl;
        cout << orderedTests[idx] << " Test successfully ordered for " << usernames[idx] << endl;
        cout << endl;
        cout << "Press any key to continue........" << endl;
        getch();
        writeAllPatientRecordsInFile();
    }
    else
    {
        printRecordNotFoundScreen();
        goto OrderTest;
    }
}

void viewTestResult()
{
    // Used to view the test results of a patient.
ViewTestResult:
    printNewScreen("View Test Result");
    string RegistrationNumber;
    int idx;
    bool isInputCorrect;
    cout << "Enter the registration number of the patient: ";
    cout << endl;
    cout << "Registration Number:       ";
    cin >> ws;
    getline(cin, RegistrationNumber);
    isInputCorrect = validateNumericInput(RegistrationNumber);
    if (isInputCorrect == false)
    {
        printInvalidInputScreen();
        goto ViewTestResult;
    }
    idx = searchRecord(stoi(RegistrationNumber));
    if (userRoles[idx] == "Patient")
    {
        cout << endl;
        cout << "Record successfully found" << endl;
        cout << endl;
        if (orderedTests[idx] != "Null")
        {
            cout << "Ordered Test:   " << orderedTests[idx] << " Test" << endl;
            cout << endl;
            if (testResults[idx] != "Null")
            {
                cout << "Test result:     " << testResults[idx] << endl;
            }
            else if (testResults[idx] == "Null")
            {
                cout << "Test Result has not been uploaded yet" << endl;
            }
        }
        else if (orderedTests[idx] == "Null")
        {
            cout << "No test has been ordered for this patient" << endl;
        }
        cout << endl;
        cout << "Press any key to continue........" << endl;
        getch();
    }
    else
    {
        printRecordNotFoundScreen();
        goto ViewTestResult;
    }
}

void addTestResult()
{
    // Used to add the test results of a patient.
AddTestResult:
    printNewScreen("Add Test Result");
    string RegistrationNumber;
    int idx;
    bool isInputCorrect;
    cout << "Enter the registration number of the patient: ";
    cout << endl;
    cout << "Registration Number:       ";
    cin >> ws;
    getline(cin, RegistrationNumber);
    isInputCorrect = validateNumericInput(RegistrationNumber);
    if (isInputCorrect == false)
    {
        printInvalidInputScreen();
        goto AddTestResult;
    }
    idx = searchRecord(stoi(RegistrationNumber));
    if (userRoles[idx] == "Patient")
    {
        string TestResult;
        cout << endl;
        cout << "Record successfully found" << endl;
        cout << endl;
        if (orderedTests[idx] != "Null")
        {
            cout << "Ordered Test:   " << orderedTests[idx] << " Test" << endl;
            cout << endl;
            cout << "1.    Positive" << endl;
            cout << "2.    Negative" << endl;
        EnterTestResult:
            cout << endl;
            cout << "Enter the test result:     ";
            cin >> ws;
            getline(cin, TestResult);
            if (TestResult == "1")
            {
                testResults[idx] = "Positive";
            }
            else if (TestResult == "2")
            {
                testResults[idx] = "Negative";
            }
            else
            {
                printInvalidInputScreen();
                cout << endl;
                cout << endl;
                goto EnterTestResult;
            }
            cout << endl;
            cout << "Test result successfully uploaded" << endl;
            writeAllPatientRecordsInFile();
        }
        else if (orderedTests[idx] == "Null")
        {
            cout << "No test has been ordered for this patient" << endl;
        }
        cout << endl;
        cout << "Press any key to continue........" << endl;
        getch();
    }
    else
    {
        printRecordNotFoundScreen();
        goto AddTestResult;
    }
}

void scheduleAppointment()
{
    // Used by a doctor to enter the date of an appointment with a patient in the database.
ScheduleAppointment:
    printNewScreen("Schedule Appointment");
    string RegistrationNumber;
    int idx;
    bool isInputCorrect;
    cout << "Enter the registration number of the patient: ";
    cout << endl;
    cout << "Registration Number:       ";
    cin >> ws;
    getline(cin, RegistrationNumber);
    isInputCorrect = validateNumericInput(RegistrationNumber);
    if (isInputCorrect == false)
    {
        printInvalidInputScreen();
        goto ScheduleAppointment;
    }
    idx = searchRecord(stoi(RegistrationNumber));
    if (userRoles[idx] == "Patient")
    {
        string date, month, year;
        cout << endl;
        cout << "Record successfully found" << endl;
    EnterDate:
        cout << endl;
        cout << "Enter appointment date: ";
        cin >> ws;
        getline(cin, date);
        isInputCorrect = validateNumericInput(date);
        if (isInputCorrect == true)
        {
            isInputCorrect = validateDate(date);
        }
        if (isInputCorrect == false)
        {
            printInvalidInputScreen();
            cout << endl;
            cout << endl;
            goto EnterDate;
        }
    EnterMonth:
        cout << endl;
        cout << "Enter appointment month: ";
        cin >> ws;
        getline(cin, month);
        isInputCorrect = validateNumericInput(month);
        if (isInputCorrect == true)
        {
            isInputCorrect = validateMonth(month);
        }
        if (isInputCorrect == false)
        {
            printInvalidInputScreen();
            cout << endl;
            cout << endl;
            goto EnterMonth;
        }
    EnterYear:
        cout << endl;
        cout << "Enter appointment year: ";
        cin >> ws;
        getline(cin, year);
        isInputCorrect = validateNumericInput(year);
        if (isInputCorrect == true)
        {
            isInputCorrect = validateYear(year);
        }
        if (isInputCorrect == false)
        {
            printInvalidInputScreen();
            cout << endl;
            cout << endl;
            goto EnterYear;
        }
        cout << endl;
        appointmentDates[idx] = date + "/" + month + "/" + year;
        cout << "Appointment successfully scheduled" << endl;
        cout << endl;
        scheduledAppointmentDoctor[loggedInIndex] = "Yes";
        appointmentDoctorRegistrationNumbers[idx] = to_string(loggedInRegistrationNumber);
        cout << "Press any key to continue........" << endl;
        getch();
        writeAllPatientRecordsInFile();
        writeAllDoctorRecordsInFile();
    }
    else
    {
        printRecordNotFoundScreen();
        goto ScheduleAppointment;
    }
}

bool validateDate(string date)
{
    // Used to validate date input.
    bool isInputCorrect = false;
    if (stoi(date) >= 1 && stoi(date) <= 31)
    {
        isInputCorrect = true;
    }
    return isInputCorrect;
}

bool validateMonth(string month)
{
    // Used to validate month input.
    bool isInputCorrect = false;
    if (stoi(month) >= 1 && stoi(month) <= 12)
    {
        isInputCorrect = true;
    }
    return isInputCorrect;
}

bool validateYear(string year)
{
    // Used to validate year input.
    bool isInputCorrect = false;
    if (stoi(year) >= 23 && stoi(year) <= 30)
    {
        isInputCorrect = true;
    }
    return isInputCorrect;
}

void cancelAppointment()
{
    // Used by a doctor to delete his appointment details with a patient from the database.
CancelAppointment:
    printNewScreen("Cancel Appointment");
    string RegistrationNumber;
    int idx;
    bool isInputCorrect;
    cout << "Enter the registration number of the patient: ";
    cout << endl;
    cout << "Registration Number:       ";
    cin >> ws;
    getline(cin, RegistrationNumber);
    isInputCorrect = validateNumericInput(RegistrationNumber);
    if (isInputCorrect == false)
    {
        printInvalidInputScreen();
        goto CancelAppointment;
    }
    idx = searchRecord(stoi(RegistrationNumber));
    if (userRoles[idx] == "Patient")
    {
        cout << endl;
        cout << "Record successfully found" << endl;
        cout << endl;
        if (appointmentDoctorRegistrationNumbers[idx] != "-1")
        {
            cout << "Appointment date: " << appointmentDates[idx] << endl;
            cout << "Patient         : " << usernames[idx] << endl;
            cout << endl;
            cout << "Appointment successfully cancelled" << endl;
            cout << endl;
            appointmentDoctorRegistrationNumbers[idx] = "-1";
            appointmentDates[idx] = "Null";
            scheduledAppointmentDoctor[loggedInIndex] = doctorAppointmentPresent(loggedInRegistrationNumber);
            writeAllDoctorRecordsInFile();
            writeAllPatientRecordsInFile();
        }
        else if (appointmentDoctorRegistrationNumbers[idx] == "-1")
        {
            cout << "You have no appointment with " << usernames[idx] << endl;
            cout << endl;
        }
        cout << "Press any key to continue........" << endl;
        getch();
    }
    else
    {
        printRecordNotFoundScreen();
        goto CancelAppointment;
    }
}

string doctorAppointmentPresent(int registrationNumber)
{
    string doctorHasAppointment = "No";
    for (int idx = 0; idx < currentUsers; idx++)
    {
        if (registrationNumber == stoi(appointmentDoctorRegistrationNumbers[idx]))
        {
            doctorHasAppointment = "Yes";
        }
    }
    return doctorHasAppointment;
}

void editAppointment()
{
    // Used by a doctor to edit the date of his appointment with a patient.
EditAppointment:
    printNewScreen("Change Appointment Date");
    string RegistrationNumber;
    int idx;
    bool isInputCorrect;
    cout << "Enter the registration number of the doctor: ";
    cout << endl;
    cout << "Registration Number:       ";
    cin >> ws;
    getline(cin, RegistrationNumber);
    isInputCorrect = validateNumericInput(RegistrationNumber);
    if (isInputCorrect == false)
    {
        printInvalidInputScreen();
        goto EditAppointment;
    }
    idx = searchRecord(stoi(RegistrationNumber));
    if (userRoles[idx] == "Patient")
    {
        cout << endl;
        cout << "Record successfully found" << endl;
        cout << endl;
        if (appointmentDoctorRegistrationNumbers[idx] != "-1")
        {
            string date, month, year;
            cout << "Appointment date: " << appointmentDates[idx] << endl;
            cout << "Patient         : " << usernames[idx] << endl;
            cout << endl;
        EnterDate:
            cout << endl;
            cout << "Enter appointment date: ";
            cin >> ws;
            getline(cin, date);
            isInputCorrect = validateNumericInput(date);
            if (isInputCorrect == true)
            {
                isInputCorrect = validateDate(date);
            }
            if (isInputCorrect == false)
            {
                printInvalidInputScreen();
                cout << endl;
                cout << endl;
                goto EnterDate;
            }
        EnterMonth:
            cout << endl;
            cout << "Enter appointment month: ";
            cin >> ws;
            getline(cin, month);
            isInputCorrect = validateNumericInput(month);
            if (isInputCorrect == true)
            {
                isInputCorrect = validateMonth(month);
            }
            if (isInputCorrect == false)
            {
                printInvalidInputScreen();
                cout << endl;
                cout << endl;
                goto EnterMonth;
            }
        EnterYear:
            cout << endl;
            cout << "Enter appointment year: ";
            cin >> ws;
            getline(cin, year);
            isInputCorrect = validateNumericInput(year);
            if (isInputCorrect == true)
            {
                isInputCorrect = validateYear(year);
            }
            if (isInputCorrect == false)
            {
                printInvalidInputScreen();
                cout << endl;
                cout << endl;
                goto EnterYear;
            }
            appointmentDates[idx] = date + "/" + month + "/" + year;
            cout << endl;
            cout << "Appointment date successfully changed" << endl;
            cout << endl;
            writeAllPatientRecordsInFile();
        }
        else if (appointmentDoctorRegistrationNumbers[idx] == "-1")
        {
            cout << "You have no appointment with " << usernames[idx] << endl;
            cout << endl;
        }
        cout << "Press any key to continue........" << endl;
        getch();
    }

    else
    {
        printRecordNotFoundScreen();
        goto EditAppointment;
    }
}

string printPatientMenu()
{
    // Used to print the patient's menu and input the functionality required by the user.
PrintPatientMenu:
    bool isInputCorrect;
    string choice;
    printNewScreen("Patient Menu");
    cout << "1.           View my record" << endl;
    cout << "2.           Edit my personal details" << endl;
    cout << "3.           View my diagnosis" << endl;
    cout << "4.           View my prescriptions" << endl;
    cout << "5.           View my recommended tests" << endl;
    cout << "6.           View the details of my appointment" << endl;
    cout << "7.           View my bill" << endl;
    cout << "8.           Give a review on hospital services" << endl;
    cout << "9.           View test result" << endl;
    cout << "10.          Logout" << endl;
    cout << endl;
    cout << "Enter your choice:   ";
    cin >> ws;
    getline(cin, choice);
    isInputCorrect = validateNumericInput(choice);
    if (isInputCorrect == true)
    {
        isInputCorrect = validatePatientMenuInput(choice);
    }
    if (isInputCorrect == false)
    {
        printInvalidInputScreen();
        goto PrintPatientMenu;
    }
    return choice;
}

bool validatePatientMenuInput(string choice)
{
    // Used to validate input from patient menu screen.
    bool isInputCorrect = false;
    if (stoi(choice) >= 1 && stoi(choice) <= 10)
    {
        isInputCorrect = true;
    }
    return isInputCorrect;
}

string choosePatientFunctionality(string menuChoice)
{
    // Used to choose which patient function to execute next.
    string nextStep, logoutChoice;
    if (menuChoice == "1")
    {
        viewOwnRecord();
        nextStep = "menuScreen";
    }
    else if (menuChoice == "2")
    {
        editPersonalDetails();
        nextStep = "menuScreen";
    }
    else if (menuChoice == "3")
    {
        viewPatientDiagnosis();
        nextStep = "menuScreen";
    }
    else if (menuChoice == "4")
    {
        viewPatientPrescription();
        nextStep = "menuScreen";
    }
    else if (menuChoice == "5")
    {
        viewPatientTest();
        nextStep = "menuScreen";
    }
    else if (menuChoice == "6")
    {
        viewPatientAppointment();
        nextStep = "menuScreen";
    }
    else if (menuChoice == "7")
    {
        viewPatientBill();
        nextStep = "menuScreen";
    }
    else if (menuChoice == "8")
    {
        giveReview();
        nextStep = "menuScreen";
    }
    else if (menuChoice == "9")
    {
        viewPatientTestResult();
        nextStep = "menuScreen";
    }
    else if (menuChoice == "10")
    {
        logoutChoice = inputLogoutChoice();
        printNewScreen("Logout");
        nextStep = printSessionEndScreen(logoutChoice);
    }
    return nextStep;
}

void viewOwnRecord()
{
    // Used by a patient to view his own record.
ViewPatientsOwnRecord:
    printNewScreen("View my Record");
    displayRecord(loggedInIndex);
    cout << endl;
    cout << "Press any key to continue....." << endl;
    getch();
}

void editPersonalDetails()
{
    // Used by a patient to edit his own personal details.
EditPersonalDetails:
    string editChoice;
    printNewScreen("Edit my Personal Details");
    cout << "What would you like to edit?" << endl;
    cout << endl;
    cout << "1.           Username" << endl;
    cout << "2.           Password" << endl;
    cout << endl;
    cout << "Enter your choice:    ";
    cin >> ws;
    getline(cin, editChoice);
    cout << endl;
    if (editChoice == "1")
    {
        editUsername();
    }
    else if (editChoice == "2")
    {
        editPassword();
    }
    else
    {
        printInvalidInputScreen();
        goto EditPersonalDetails;
    }
}

void editUsername()
{
    // Used to edit the username of the logged in user.
EditUsername:
    bool isInputCorrect;
    string Username;
    printNewScreen("Edit Username");
    cout << "Enter your new username: " << endl;
    cin >> ws;
    getline(cin, Username);
    isInputCorrect = validateUsername(Username);
    if (isInputCorrect == false)
    {
        printInvalidInputScreen();
        goto EditUsername;
    }
    usernames[loggedInIndex] = Username;
    cout << endl;
    cout << "Your username has been successfully updated to " << usernames[loggedInIndex] << endl;
    cout << endl;
    cout << "Press any key to continue.....";
    getch();
    writeAllPatientRecordsInFile();
    writeAllDoctorRecordsInFile();
    writeAdminRecordInFile();
}

void editPassword()
{
    // Used to edit the password of the logged in user.
EditUsername:
    bool isInputCorrect;
    string Password;
    printNewScreen("Edit Password");
    cout << "Enter your old password: " << endl;
    cin >> ws;
    getline(cin, Password);
    cout << endl;
    if (Password == loggedInPassword)
    {
        cout << "Correct Password" << endl;
        cout << endl;
    }
    else
    {
        useRedColour();
        cout << "Wrong Password" << endl;
        cout << endl;
        cout << "Please try again." << endl;
        useWhiteColour();
        cout << endl;
        cout << "Press any key to continue.....";
        getch();
        goto EditUsername;
    }
    cout << "Enter your new password: ";
    cin >> ws;
    getline(cin, Password);
    isInputCorrect = isPasswordUnique(Password);
    if (isInputCorrect == false)
    {
        printPasswordInUseScreen();
        goto EditUsername;
    }
    if (isInputCorrect == true)
    {
        passwords[loggedInIndex] = Password;
        cout << endl;
        cout << "Your password has been successfully updated to " << passwords[loggedInIndex] << endl;
        cout << endl;
        cout << "Press any key to continue.....";
        getch();
        writeAllPatientRecordsInFile();
        writeAllDoctorRecordsInFile();
        writeAdminRecordInFile();
    }
}

void viewPatientDiagnosis()
{
    // Used by a patient to view his own diagnosis.
    printNewScreen("View my Diagnosis");
    cout << "Your Diagnosis: " << diseases[loggedInIndex] << endl;
    cout << endl;
    cout << "Press any key to continue.....";
    getch();
}

void viewPatientPrescription()
{
    // Used by a patient to view his own medicine prescription.
    printNewScreen("View my Prescription");
    cout << "Medicine Prescribed:  " << prescribedMedicines[loggedInIndex];
    if (prescribedMedicines[loggedInIndex] != "No Prescription Yet")
    {
        cout << "    x" << prescribedMedicineAmounts[loggedInIndex] << endl;
    }
    cout << endl;
    cout << "Press any key to continue.....";
    getch();
}

void viewPatientTest()
{
    // Used by a patient to view the test recommended for him by his doctor.
    printNewScreen("View my Recommended Test");
    cout << "Your Recommended Test: " << orderedTests[loggedInIndex] << " Test" << endl;
    cout << endl;
    cout << "Press any key to continue.....";
    getch();
}

void viewPatientAppointment()
{
    // Used by a patient to view the details of his upcoming appointment.
    printNewScreen("View the Details of my Appointment");
    int idx;
    if (appointmentDoctorRegistrationNumbers[loggedInIndex] != "-1")
    {
        idx = searchRecord(stoi(appointmentDoctorRegistrationNumbers[loggedInIndex]));
        cout << endl;
        cout << "Appointment Date : " << appointmentDates[loggedInIndex] << endl;
        cout << "Doctor's Name    : Dr. " << usernames[idx] << endl;
        cout << endl;
    }
    if (appointmentDoctorRegistrationNumbers[loggedInIndex] == "-1")
    {
        cout << "No Appointment Scheduled Yet" << endl;
        cout << endl;
    }
    cout << "Press any key to continue.....";
    getch();
}

void viewPatientBill()
{
    // Used by a patient to view his bill.
    printNewScreen("View my Bill");
    if (stoi(patientBills[loggedInIndex]) >= 0)
    {
        cout << "Your Bill: Rs. " << patientBills[loggedInIndex] << endl;
        cout << endl;
        cout << "Press any key to continue.....";
        getch();
    }
    else
    {
        cout << "Your Bill: Not Added Yet" << endl;
        cout << endl;
        cout << "Press any key to continue.....";
        getch();
    }
}

void viewPatientTestResult()
{
    // Used by a patient to view his test result.
    printNewScreen("View my Test Result");
    if (testResults[loggedInIndex] != "Null")
    {
        cout << "Your Test Result: " << orderedTests[loggedInIndex] << " (" << testResults[loggedInIndex] << ")" << endl;
        cout << endl;
        cout << "Press any key to continue.....";
        getch();
    }
    else if (testResults[loggedInIndex] == "Null")
    {
        cout << "Your Test Result: Not Uploaded Yet" << endl;
        cout << endl;
        cout << "Press any key to continue.....";
        getch();
    }
}

void giveReview()
{
    // Used by doctors and patient to give a review on hospital services.
GiveReview:
    string choice;
    printNewScreen("Give Review on Hospital Services");
    if (stoi(hosptialReviewStars[loggedInIndex]) >= 1)
    {
        cout << "Review already given" << endl;
        cout << endl;
        cout << "Would you like to overwrite the given review?" << endl;
        cout << endl;
        cout << "1.     Yes" << endl;
        cout << "2.     No" << endl;
        cout << endl;
        cout << "Enter your choice:     ";
        cin >> ws;
        getline(cin, choice);
        cout << endl;
        if (choice == "1")
        {
            inputReview();
        }
        else if (choice == "2")
        {
            cout << "Press any key to continue.....";
            getch();
        }
        else
        {
            printInvalidInputScreen();
            goto GiveReview;
        }
    }
    else if (stoi(hosptialReviewStars[loggedInIndex]) <= 0)
    {
        inputReview();
    }
}

void inputReview()
{
    // Used to input a Hospital Service Review from the user.
InputReview:
    bool isInputValid;
    string reviewStars;
    printNewScreen("Give Review on Hospital Services");
    cout << "From 1 to 5, how many stars would you give to our service?" << endl;
    cin >> ws;
    getline(cin, reviewStars);
    isInputValid = validateNumericInput(reviewStars);
    if (isInputValid == true)
    {
        isInputValid = validateReviewInput(reviewStars);
    }
    if (isInputValid == false)
    {
        printInvalidInputScreen();
        goto InputReview;
    }
    hosptialReviewStars[loggedInIndex] = reviewStars;
    cout << endl;
    cout << "How would you describe your experience in words?" << endl;
    cin >> ws;
    getline(cin, hospitalReviewStatements[loggedInIndex]);
    cout << endl;
    writeAllDoctorRecordsInFile();
    writeAllPatientRecordsInFile();
    cout << "Review successfully submitted" << endl;
    cout << endl;
    cout << "Press any key to continue.....";
    getch();
}

bool validateReviewInput(string input)
{
    bool isInputValid = false;
    if (stoi(input) >= 1 && stoi(input) <= 5)
    {
        isInputValid = true;
    }
    return isInputValid;
}

string inputLogoutChoice()
{
    // Inputs from the user whether they want to logout or completely terminate the application.
InputLogoutChoice:
    printNewScreen("Logout");
    bool isInputCorrect;
    string logoutChoice;
    cout << "Would you like to login again or terminate the application?" << endl;
    cout << endl;
    cout << "1.           Login again" << endl;
    cout << "2.           Terminate the application" << endl;
    cout << endl;
    cout << "Enter your choice:    ";
    cin >> ws;
    getline(cin, logoutChoice);
    isInputCorrect = validateNumericInput(logoutChoice);
    if (isInputCorrect == true)
    {
        isInputCorrect = validateLogoutChoice(logoutChoice);
    }
    if (isInputCorrect == false)
    {
        printInvalidInputScreen();
        goto InputLogoutChoice;
    }
    return logoutChoice;
}

bool validateLogoutChoice(string logoutChoice)
{
    // Used to validate the input from the logout screen.
    bool isInputCorrect = false;
    if (logoutChoice == "1" || logoutChoice == "2")
    {
        isInputCorrect = true;
    }
    return isInputCorrect;
}

bool isPasswordUnique(string Password)
{
    // Used to make sure that a given password not already in use.
    bool isInputCorrect = true;
    for (int idx = 0; idx < currentUsers; idx++)
    {
        if (passwords[idx] == Password)
        {
            isInputCorrect = false;
        }
    }
    return isInputCorrect;
}

bool validateUsername(string Username)
{
    // Used to make sure that a given username does not contain numbers and special characters.
    bool isInputCorrect = true;
    for (int idx = 0; idx < Username.length(); idx++)
    {
        if (!((int(Username[idx]) >= 65 && int(Username[idx]) <= 90) || (int(Username[idx]) >= 97 && int(Username[idx]) <= 122) || (int(Username[idx]) == 32)))
        {
            isInputCorrect = false;
            break;
        }
    }
    return isInputCorrect;
}

bool validateNumericInput(string input)
{
    // Used to make sure that the given input consists of numbers only.
    bool validInput = true;
    for (int idx = 0; idx < input.length(); idx++)
    {
        if (!(int(input[idx]) >= 48 && int(input[idx]) <= 57))
        {
            validInput = false;
            break;
        }
    }
    return validInput;
}

int assignRegistrationNumber()
{
    // Used to assign a registration number to a new user by clculating the greatest registration number already in use.
    int greatest = -1;
    for (int idx = 0; idx < currentUsers; idx++)
    {
        if (registrationNumbers[idx] > greatest)
        {
            greatest = registrationNumbers[idx];
        }
    }
    return greatest + 1;
}

int searchRecord(int RegistrationNumber)
{
    // Used to search the index of a given registration number.
    int index = -1;
    for (int idx = 0; idx < currentUsers; idx++)
    {
        if ((RegistrationNumber == registrationNumbers[idx]))
        {
            index = idx;
            break;
        }
    }
    return index;
}

void displayRecord(int idx)
{
    // Used to display the record of given index.
    if (userRoles[idx] == "Admin")
    {
        cout << endl;
        cout << "Username            :  " << usernames[idx] << endl;
        cout << "User Role           :  " << userRoles[idx] << endl;
        cout << "Registration Number :  " << registrationNumbers[idx] << endl;
        cout << endl;
    }
    if (userRoles[idx] == "Doctor")
    {
        cout << endl;
        cout << "Username            :  " << usernames[idx] << endl;
        cout << "User Role           :  " << userRoles[idx] << endl;
        cout << "Salary              :  Rs. " << doctorSalaries[idx] << endl;
        cout << "Registration Number :  " << registrationNumbers[idx] << endl;
        cout << endl;
    }
    if (userRoles[idx] == "Patient")
    {
        cout << endl;
        cout << "Username            :  " << usernames[idx] << endl;
        cout << "User Role           :  " << userRoles[idx] << endl;
        cout << "Registration Number :  " << registrationNumbers[idx] << endl;
        if (stoi(patientBills[idx]) > 0)
        {
            cout << "Total Bill          :  Rs. " << patientBills[idx] << endl;
        }
        else
        {
            cout << "Total Bill          :  Not Added Yet" << endl;
        }

        cout << "Test Ordered        :  " << orderedTests[idx] << endl;

        if (testResults[idx] != "Null")
        {
            cout << "Test Result         :  " << testResults[idx] << endl;
        }
        else
        {
            cout << "Test Result         :  Not Uploaded Yet" << endl;
        }

        cout << "Disease             :  " << diseases[idx] << endl;

        cout << "Medicine Prescribed :  " << prescribedMedicines[idx];
        if (prescribedMedicines[idx] != "No Prescription Yet")
        {
            cout << "    x" << prescribedMedicineAmounts[idx] << endl;
        }

        cout << endl;
    }
}

void printRecordNotFoundScreen()
{
    // Use to show on screen that the required record could not be found.
    useRedColour();
    cout << "Record not Found" << endl;
    cout << endl;
    cout << "Please try again" << endl;
    useWhiteColour();
    cout << endl;
    cout << "Press any key to continue.....";
    getch();
}

void printNoRecordFoundScreen()
{
    // Used to print on the screen that no matching record was found.
    useRedColour();
    cout << endl;
    cout << "No Record Found" << endl;
    cout << endl;
    useWhiteColour();
}

void printInvalidInputScreen()
{
    // Used to show on the screen that the given input is invalid.
    useRedColour();
    cout << endl;
    cout << "Invalid Input" << endl;
    cout << endl;
    cout << "Please try again." << endl;
    useWhiteColour();
    cout << endl;
    cout << "Press any key to continue";
    getch();
}

void printInvalidUsernameScreen()
{
    // Used to print on the screen that the given username is invalid.
    useRedColour();
    cout << endl;
    cout << "Invalid Input" << endl;
    cout << endl;
    cout << "Please try again." << endl;
    useWhiteColour();
    cout << endl;
    cout << "Press any key to continue";
    getch();
}

void useRedColour()
{
    // Used to set the console text colour to red.
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 12);
}

void useWhiteColour()
{
    // Used to set the console text colour to white.
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 15);
}