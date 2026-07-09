#include <iostream>
#include <iomanip>
#include <conio.h>
using namespace std;

void input(int &numOfStudents);
int sizeOfString(char* str);
double bestScore(double** scores, int* attemps, int i);
double averageOfScores(double** scores, int* attemps, int i);
void calculateAndDisplayResults(char** names, double** scores, int* attemps, int numOfStudents);
bool appendScores(int choice, int numOfStudents, int* attemps, double** scores);

int main() {
    cout << "\nSTUDENT SCORE MANAGEMENT SYSTEM\n";
    cout << "--------------------------------------------\n";

    int numOfStudents = 0;
    input(numOfStudents);

    char** names   = new char*  [numOfStudents];
    double** scores  = new double*[numOfStudents];
    int* attemps = new int[numOfStudents];

    for (int i = 0; i < numOfStudents; i++) {
        char tempname[1000];

        cout << "\nStudent " << i + 1 << " of " << numOfStudents << "\n";
        cout << "Name: ";
        cin.getline(tempname, 1000);
        bool validName = false;
        for (int k = 0; k < sizeOfString(tempname); k++) {
            if (*(tempname + k) != ' ') { 
                validName = true; break; 
            }
        }
        while (!validName) {
            cout << "Invalid. Name: ";
            cin.getline(tempname, 1000);
            validName = false;
            for (int k = 0; k < sizeOfString(tempname); k++) {
                if (*(tempname + k) != ' ') { 
                    validName = true; 
                    break; 
                }
            }
        }

        *(names + i) = new char[sizeOfString(tempname) + 1];
        for (int j = 0; j < sizeOfString(tempname); j++)
            *(*(names + i) + j) = *(tempname + j);
        *(*(names + i) + sizeOfString(tempname)) = '\0';

        cout << "Attempts: ";
        while (!(cin >> *(attemps + i)) || *(attemps + i) <= 0) {
            cin.clear();
            while (cin.get() != '\n');
            cout << "Invalid. Attempts: ";
        }
        while (cin.get() != '\n');

        *(scores + i) = new double[*(attemps + i)];
        for (int j = 0; j < *(attemps + i); j++) {
            cout << "Score " << j + 1 << ": ";
            while (!(cin >> *(*(scores + i) + j)) || *(*(scores + i) + j) < 0 || *(*(scores + i) + j) > 100) {
                cin.clear();
                while (cin.get() != '\n');
                cout << "Invalid (0-100). Score " << j + 1 << ": ";
            }
            while (cin.get() != '\n');
        }
    }

    calculateAndDisplayResults(names, scores, attemps, numOfStudents);

    int choice = -1;
    do {
        cout << "Append a score? (1-Yes, 0-No): ";
        while (!(cin >> choice)) {
            cin.clear();
            while (cin.get() != '\n');
            cout << "Invalid. Enter 1 or 0: ";
        }
        while (cin.get() != '\n');

        switch (choice) {
            case 1:
                if (appendScores(choice, numOfStudents, attemps, scores))
                    calculateAndDisplayResults(names, scores, attemps, numOfStudents);
                break;
            case 0:
                break;
            default:
                cout << "Invalid. Enter 1 or 0.\n";
                break;
        }
    } while (choice != 0);

    for (int i = 0; i < numOfStudents; i++) {
        delete[] *(names + i);
        delete[] *(scores + i);
    }
    delete[] names;
    delete[] scores;
    delete[] attemps;
    names = nullptr; scores = nullptr; attemps = nullptr;

    cout << "\nPress any key to exit...";
    getch();
    return 0;
}

void input(int &numOfStudents) {
    while (numOfStudents <= 0) {
        cout << "Number of students: ";
        if (!(cin >> numOfStudents)) cin.clear();
        while (cin.get() != '\n');
        if (numOfStudents <= 0) cout << "Invalid. Try again.\n";
    }
}

int sizeOfString(char* str) {
    int i = 0;
    while (*(str + i) != '\0') i++;
    return i;
}

double bestScore(double** scores, int* attemps, int i) {
    double best = 0;
    for (int j = 0; j < *(attemps + i); j++)
        if (*(*(scores + i) + j) > best) best = *(*(scores + i) + j);
    return best;
}

double averageOfScores(double** scores, int* attemps, int i) {
    double sum = 0;
    for (int j = 0; j < *(attemps + i); j++)
        sum += *(*(scores + i) + j);
    return sum / (double)*(attemps + i);
}

void calculateAndDisplayResults(char** names, double** scores, int* attemps, int numOfStudents) {
    cout << "\n--------------------------------------------\n";
    cout << left << setw(20) << "Name" << setw(15) << "Average" << setw(15) << "Best" << "\n";
    cout << "--------------------------------------------\n";

    for (int i = 0; i < numOfStudents; i++) {
        double avg  = averageOfScores(scores, attemps, i);
        double best = bestScore(scores, attemps, i);

        cout << left  << setw(20) << *(names + i) << fixed << setprecision(2) << setw(15) << avg << setw(15) << best << "\n";
    }

    cout << "--------------------------------------------\n\n";
}

bool appendScores(int choice, int numOfStudents, int* attemps, double** scores) {
    if (choice != 1) return false;

    int studentIndex = -1;
    double newScore = 0;

    cout << "Student index (0 to " << numOfStudents - 1 << "): ";
    while (!(cin >> studentIndex) || studentIndex < 0 || studentIndex >= numOfStudents) {
        cin.clear();
        while (cin.get() != '\n');
        cout << "Invalid. Index (0 to " << numOfStudents - 1 << "): ";
    }
    while (cin.get() != '\n');

    cout << "New score (0-100): ";
    while (!(cin >> newScore) || newScore < 0 || newScore > 100) {
        cin.clear();
        while (cin.get() != '\n');
        cout << "Invalid. Score (0-100): ";
    }
    while (cin.get() != '\n');

    double* newArray = new double[*(attemps + studentIndex) + 1];
    for (int j = 0; j < *(attemps + studentIndex); j++)
        *(newArray + j) = *(*(scores + studentIndex) + j);
    *(newArray + *(attemps + studentIndex)) = newScore;

    delete[] *(scores + studentIndex);
    *(scores + studentIndex) = newArray;
    (*(attemps + studentIndex))++;

    return true;
}