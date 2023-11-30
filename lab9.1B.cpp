// lab 9.1B
#include <iostream>
#include <string>

enum class Specialty { ComputerScience, Informatics, MathEconomics, PhysicsInformatics, LaborTraining };

union ThirdGrade {
    int programming;
    int numericalMethods;
    int pedagogy;
};

struct Student {
    std::string lastName;
    int course;
    Specialty specialty;
    int physicsGrade;
    int mathGrade;
    ThirdGrade thirdGrade;
};

void inputStudentData(Student& student) {
    std::cout << "Enter last name: ";
    std::cin >> student.lastName;

    std::cout << "Enter course: ";
    std::cin >> student.course;

    std::cout << "Enter specialty (0 - Computer Science, 1 - Informatics, 2 - Math Economics, 3 - Physics Informatics, 4 - Labor Training): ";
    int specialtyChoice;
    std::cin >> specialtyChoice;
    student.specialty = static_cast<Specialty>(specialtyChoice);

    std::cout << "Enter physics grade: ";
    std::cin >> student.physicsGrade;

    std::cout << "Enter math grade: ";
    std::cin >> student.mathGrade;

    switch (student.specialty) {
        case Specialty::ComputerScience:
            std::cout << "Enter programming grade: ";
            std::cin >> student.thirdGrade.programming;
            break;
        case Specialty::Informatics:
            std::cout << "Enter numerical methods grade: ";
            std::cin >> student.thirdGrade.numericalMethods;
            break;
        case Specialty::MathEconomics:
            std::cout << "Enter pedagogy grade: ";
            std::cin >> student.thirdGrade.pedagogy;
            break;
        default:
            break;
    }
}

void displayStudentsTable(const Student* students, int size) {
    std::cout << "-----------------------------------------------------------------------------\n";
    std::cout << "| No. | Last Name | Course | Specialty           | Physics | Math | Third Grade |\n";
    std::cout << "-----------------------------------------------------------------------------\n";

    for (int i = 0; i < size; ++i) {
        std::cout << "| " << i + 1 << "   | ";
        std::cout.width(10);
        std::cout << students[i].lastName << " | ";
        std::cout.width(6);
        std::cout << students[i].course << " | ";
        std::cout.width(20);

        switch (students[i].specialty) {
            case Specialty::ComputerScience:
                std::cout << "Computer Science     | ";
                std::cout.width(7);
                std::cout << students[i].physicsGrade << " | ";
                std::cout.width(5);
                std::cout << students[i].mathGrade << " | ";
                std::cout.width(11);
                std::cout << students[i].thirdGrade.programming << " |";
                break;
            case Specialty::Informatics:
                std::cout << "Informatics          | ";
                std::cout.width(7);
                std::cout << students[i].physicsGrade << " | ";
                std::cout.width(5);
                std::cout << students[i].mathGrade << " | ";
                std::cout.width(11);
                std::cout << students[i].thirdGrade.numericalMethods << " |";
                break;
            case Specialty::MathEconomics:
                std::cout << "Math Economics       | ";
                std::cout.width(7);
                std::cout << students[i].physicsGrade << " | ";
                std::cout.width(5);
                std::cout << students[i].mathGrade << " | ";
                std::cout.width(11);
                std::cout << students[i].thirdGrade.pedagogy << " |";
                break;
            case Specialty::PhysicsInformatics:
                std::cout << "Physics Informatics  | ";
                std::cout.width(7);
                std::cout << students[i].physicsGrade << " | ";
                std::cout.width(5);
                std::cout << students[i].mathGrade << " | N/A         |";
                break;
            case Specialty::LaborTraining:
                std::cout << "Labor Training       | ";
                std::cout.width(7);
                std::cout << students[i].physicsGrade << " | ";
                std::cout.width(5);
                std::cout << students[i].mathGrade << " | N/A         |";
                break;
        }

        std::cout << "\n";
    }

    std::cout << "-----------------------------------------------------------------------------\n";
}

void countPhysicsGrades(const Student* students, int size, int& grade5, int& grade4, int& grade3) {
    grade5 = grade4 = grade3 = 0;

    for (int i = 0; i < size; ++i) {
        if (students[i].physicsGrade == 5) {
            grade5++;
        } else if (students[i].physicsGrade == 4) {
            grade4++;
        } else if (students[i].physicsGrade == 3) {
            grade3++;
        }
    }
}

void countStudentsWithMathPhysicsGrades(const Student* students, int size, int& count) {
    count = 0;

    for (int i = 0; i < size; ++i) {
        if ((students[i].mathGrade == 4 || students[i].mathGrade == 5) &&
            (students[i].physicsGrade == 4 || students[i].physicsGrade == 5)) {
            count++;
        }
    }
}

int main() {
    int numberOfStudents;
    std::cout << "Enter the number of students: ";
    std::cin >> numberOfStudents;

    if (numberOfStudents <= 0) {
        std::cout << "Invalid input. The number of students must be a positive integer.\n";
        return 1;
    }

    Student* students = new Student[numberOfStudents];

    for (int i = 0; i < numberOfStudents; ++i) {
        std::cout << "\nEnter data for student " << i + 1 << ":\n";
        inputStudentData(students[i]);
    }

    displayStudentsTable(students, numberOfStudents);

    int grade5, grade4, grade3;
    countPhysicsGrades(students, numberOfStudents, grade5, grade4, grade3);
    std::cout << "\nPhysics Grades Distribution:\n";
    std::cout << "Grade 5: " << grade5 << " students\n";
    std::cout << "Grade 4: " << grade4 << " students\n";
    std::cout << "Grade 3: " << grade3 << " students\n";

   
    int countStudentsWithMathPhysicsGradesResult;
    countStudentsWithMathPhysicsGrades(students, numberOfStudents, countStudentsWithMathPhysicsGradesResult);
    std::cout << "\nNumber of students with grades 4 or 5 in both Physics and Math: "
              << countStudentsWithMathPhysicsGradesResult << "\n";

    delete[] students;

    return 0;
}

