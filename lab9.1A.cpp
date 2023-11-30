#include <iostream>
#include <string>

using namespace std;

struct Student {
    string surname;
    int course;
    string specialty;
    int physicsGrade;
    int mathGrade;
    int informaticsGrade;
};

void displayTableHeader() {
    cout << "| No. | Surname   | Course | Specialty | Physics | Math | Informatics |\n";
}

void displayStudent(const Student& student, int number) {
    cout << "| " << number << "   | " << student.surname << " | " << student.course << "      | "
              << student.specialty << " | " << student.physicsGrade << "       | " << student.mathGrade
              << "   | " << student.informaticsGrade << "          |\n";
}

void countPhysicsGrades(const Student students[], int size) {
    int grade5 = 0, grade4 = 0, grade3 = 0;

    for (int i = 0; i < size; ++i) {
        if (students[i].physicsGrade == 5) {
            grade5++;
        } else if (students[i].physicsGrade == 4) {
            grade4++;
        } else if (students[i].physicsGrade == 3) {
            grade3++;
        }
    }

    cout << "Physics Grades:\n";
    cout << "Grade 5: " << grade5 << "\n";
    cout << "Grade 4: " << grade4 << "\n";
    cout << "Grade 3: " << grade3 << "\n";
}

void countPhysicsAndMathGrades(const Student students[], int size) {
    int count = 0;

    for (int i = 0; i < size; ++i) {
        if ((students[i].physicsGrade >= 4) && (students[i].mathGrade >= 4)) {
            count++;
        }
    }

    cout << "Students with Physics and Math grades 4 or 5: " << count << "\n";
}

int main() {
    int numberOfStudents;
    cout << "Enter the number of students: ";
    cin >> numberOfStudents;

    Student* students = new Student[numberOfStudents];

    for (int i = 0; i < numberOfStudents; ++i) {
        cout << "Enter details for student " << i + 1 << ":\n";
        cout << "Surname: ";
        cin >> students[i].surname;
        cout << "Course: ";
        cin >> students[i].course;
        cout << "Specialty: ";
        cin >> students[i].specialty;
        cout << "Physics grade: ";
        cin >> students[i].physicsGrade;
        cout << "Math grade: ";
        cin >> students[i].mathGrade;
        cout << "Informatics grade: ";
        cin >> students[i].informaticsGrade;
    }


    displayTableHeader();

   
    for (int i = 0; i < numberOfStudents; ++i) {
        displayStudent(students[i], i + 1);
    }

    countPhysicsGrades(students, numberOfStudents);

    countPhysicsAndMathGrades(students, numberOfStudents);

    delete[] students;

    return 0;
}
