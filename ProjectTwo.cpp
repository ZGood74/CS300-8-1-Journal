//============================================================================
// Name        : Project 2
// Author      : Zack Good 
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Structure to hold course information
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Function prototypes
void loadCourses(const string& filename, unordered_map<string, Course>& courses);
void printCourseList(const unordered_map<string, Course>& courses);
void printCourse(const unordered_map<string, Course>& courses, const string& courseNumber);
void displayMenu();

int main() {
    unordered_map<string, Course> courses;
    int choice;
    string filename = "courses.csv"; // Path to the file
    string courseNumber;

    cout << "Welcome to the course planner." << endl;

    while (true) {
        displayMenu();
        cout << "What would you like to do? ";
        cin >> choice;

        switch (choice) {
        case 1:
            loadCourses(filename, courses);
            break;
        case 2:
            printCourseList(courses);
            break;
        case 3:
            cout << "What course do you want to know about? ";
            cin >> courseNumber;
            printCourse(courses, courseNumber);
            break;
        case 9:
            cout << "Thank you for using the course planner!" << endl;
            return 0;
        default:
            cout << choice << " is not a valid option." << endl;
        }
    }
}

void displayMenu() {
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;
}

void loadCourses(const string& filename, unordered_map<string, Course>& courses) {
    ifstream file(filename);
    string line;

    if (!file.is_open()) {
        cout << "Error: Cannot open file " << filename << endl;
        return;
    }

    cout << "Reading file: " << filename << endl;

    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        Course course;

        // Read the course number
        getline(ss, course.courseNumber, ',');

        // Read the course title
        getline(ss, course.courseTitle, ',');

        cout << "Loaded course: " << course.courseNumber << " - " << course.courseTitle << endl;

        // Read the prerequisites
        while (getline(ss, token, ',')) {
            course.prerequisites.push_back(token);
        }

        // Add the course to the map
        courses[course.courseNumber] = course;
    }

    file.close();
    cout << "Courses loaded successfully." << endl;
}

void printCourseList(const unordered_map<string, Course>& courses) {
    vector<string> courseNumbers;

    for (const auto& pair : courses) {
        courseNumbers.push_back(pair.first);
    }

    sort(courseNumbers.begin(), courseNumbers.end());

    cout << "Here is a sample schedule:" << endl;
    for (const string& courseNumber : courseNumbers) {
        cout << courseNumber << ", " << courses.at(courseNumber).courseTitle << endl;
    }
}

void printCourse(const unordered_map<string, Course>& courses, const string& courseNumber) {
    if (courses.find(courseNumber) == courses.end()) {
        cout << "Course not found." << endl;
        return;
    }

    const Course& course = courses.at(courseNumber);
    cout << course.courseNumber << ", " << course.courseTitle << endl;
    if (!course.prerequisites.empty()) {
        cout << "Prerequisites: ";
        for (size_t i = 0; i < course.prerequisites.size(); ++i) {
            cout << course.prerequisites[i];
            if (i < course.prerequisites.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
    else {
        cout << "No prerequisites." << endl;
    }
}
