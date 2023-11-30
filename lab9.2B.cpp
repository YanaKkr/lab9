#include <iostream>
#include <string>
#include <algorithm>
#include <numeric>

using namespace std;

enum class Specialty {
    ComputerScience,
    Informatics,
    MathEconomics,
    PhysicsInformatics,
    LaborTraining
};

union ThirdGrade {
    int programming;
    int numericalMethods;
    int pedagogy;
};

struct Student {
    string lastName;
    int course;
    Specialty specialty;
    int physicsGrade;
    int mathGrade;
    ThirdGrade thirdGrade;
};

void inputStudentData(Student& student) {
    cout << "Enter last name: ";
    cin >> student.lastName;

    cout << "Enter course: ";
    cin >> student.course;

    cout << "Enter specialty (0 - Computer Science, 1 - Informatics, 2 - Math Economics, 3 - Physics Informatics, 4 - Labor Training): ";
    int specialtyChoice;
    cin >> specialtyChoice;
    student.specialty = static_cast<Specialty>(specialtyChoice);

    cout << "Enter physics grade: ";
    cin >> student.physicsGrade;

    cout << "Enter math grade: ";
    cin >> student.mathGrade;

    switch (student.specialty) {
    case Specialty::ComputerScience:
        cout << "Enter programming grade: ";
        cin >> student.thirdGrade.programming;
        break;
    case Specialty::Informatics:
        cout << "Enter numerical methods grade: ";
        cin >> student.thirdGrade.numericalMethods;
        break;
    case Specialty::MathEconomics:
        cout << "Enter pedagogy grade: ";
        cin >> student.thirdGrade.pedagogy;
        break;
    default:
        break;
    }
}

void displayStudentsTable(const Student* students, size_t numberOfStudents) {
    cout << "-----------------------------------------------------------------------------------------------------------------\n";
    cout << "| No. | Last Name | Course | Specialty           | Physics | Math | Third Grade | Programming | Numerical Methods | Pedagogy |\n";
    cout << "-----------------------------------------------------------------------------------------------------------------\n";

    for (size_t i = 0; i < numberOfStudents; ++i) {
        cout << "| " << i + 1 << "   | ";
        cout.width(10);
        cout << students[i].lastName << " | ";
        cout.width(6);
        cout << students[i].course << " | ";
        cout.width(20);

        switch (students[i].specialty) {
        case Specialty::ComputerScience:
            cout << "Computer Science     | ";
            cout.width(7);
            cout << students[i].physicsGrade << " | ";
            cout.width(5);
            cout << students[i].mathGrade << " | ";
            cout.width(11);
            cout << students[i].thirdGrade.programming << " |";
            break;
        case Specialty::Informatics:
            cout << "Informatics          | ";
            cout.width(7);
            cout << students[i].physicsGrade << " | ";
            cout.width(5);
            cout << students[i].mathGrade << " | ";
            cout.width(11);
            cout << students[i].thirdGrade.numericalMethods << " |";
            break;
        case Specialty::MathEconomics:
            cout << "Math Economics       | ";
            cout.width(7);
            cout << students[i].physicsGrade << " | ";
            cout.width(5);
            cout << students[i].mathGrade << " | ";
            cout.width(11);
            cout << students[i].thirdGrade.pedagogy << " |";
            break;
        case Specialty::PhysicsInformatics:
            cout << "Physics Informatics  | ";
            cout.width(7);
            cout << students[i].physicsGrade << " | ";
            cout.width(5);
            cout << students[i].mathGrade << " | N/A         | N/A             | N/A      |";
            break;
        case Specialty::LaborTraining:
            cout << "Labor Training       | ";
            cout.width(7);
            cout << students[i].physicsGrade << " | ";
            cout.width(5);
            cout << students[i].mathGrade << " | N/A         | N/A             | N/A      |";
            break;
        }

        cout << "\n";
    }

    cout << "-----------------------------------------------------------------------------------------------------------------\n";
}

void sortByPhysics(Student* students, size_t numberOfStudents) {
    sort(students, students + numberOfStudents,
        [](const Student& a, const Student& b) {
            return a.physicsGrade > b.physicsGrade;
        });
}

void buildIndexArray(const Student* students, size_t numberOfStudents, size_t* indexArray) {
    iota(indexArray, indexArray + numberOfStudents, 0);

    sort(indexArray, indexArray + numberOfStudents,
        [&students](size_t a, size_t b) {
            const Student& studentA = students[a];
            const Student& studentB = students[b];

            if (studentA.physicsGrade != studentB.physicsGrade) {
                return studentA.physicsGrade > studentB.physicsGrade;
            }
            else if (studentA.course != studentB.course) {
                return studentA.course < studentB.course;
            }
            else {
                return studentA.lastName > studentB.lastName;
            }
        });
}

bool binarySearchStudent(const Student* students, size_t numberOfStudents, const size_t* indexArray,
    const string& lastName, int course, int physicsGrade, size_t& foundIndex) {
    auto iter = lower_bound(indexArray, indexArray + numberOfStudents, 0,
        [&students, &lastName, course, physicsGrade](size_t a, size_t b) {
            const Student& student = students[a];
            if (student.lastName != lastName) {
                return student.lastName < lastName;
            }
            else if (student.course != course) {
                return student.course < course;
            }
            else {
                return student.physicsGrade < physicsGrade;
            }
        });

    if (iter != indexArray + numberOfStudents) {
        size_t index = *iter;
        const Student& foundStudent = students[index];

        if (foundStudent.lastName == lastName && foundStudent.course == course && foundStudent.physicsGrade == physicsGrade) {
            foundIndex = index;
            return true;
        }
    }

    return false;
}

int main() {
    size_t numberOfStudents;
    cout << "Enter the number of students: ";
    cin >> numberOfStudents;

    Student* students = new Student[numberOfStudents];
    size_t* indexArray = new size_t[numberOfStudents];

    for (size_t i = 0; i < numberOfStudents; ++i) {
        cout << "\nEnter data for student #" << i + 1 << ":\n";
        inputStudentData(students[i]);
    }

    cout << "\nTable of Students:\n";
    displayStudentsTable(students, numberOfStudents);

    sortByPhysics(students, numberOfStudents);
    cout << "\nTable of Students (Sorted by Physics Grade):\n";
    displayStudentsTable(students, numberOfStudents);

    buildIndexArray(students, numberOfStudents, indexArray);
    cout << "\nIndex Array (Sorted by Physics Grade, Course, and Last Name):\n";
    for (size_t i = 0; i < numberOfStudents; ++i) {
        cout << indexArray[i] + 1 << " ";
    }
    cout << "\n";

    string searchLastName;
    int searchCourse, searchPhysicsGrade;
    cout << "\nEnter student information for binary search:\n";
    cout << "Last Name: ";
    cin >> searchLastName;
    cout << "Course: ";
    cin >> searchCourse;
    cout << "Physics Grade: ";
    cin >> searchPhysicsGrade;

    size_t foundIndex;
    if (binarySearchStudent(students, numberOfStudents, indexArray, searchLastName, searchCourse, searchPhysicsGrade, foundIndex)) {
        cout << "\nStudent found at position " << foundIndex + 1 << " in the sorted array.\n";
    }
    else {
        cout << "\nStudent not found.\n";
    }

    delete[] students;
    delete[] indexArray;

    return 0;
}
