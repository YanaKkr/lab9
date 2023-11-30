#include <iostream>
#include <string>
#include <algorithm>

enum class Specialty { ComputerScience, Physics, Mathematics };

struct Student {
    std::string surname;
    int course;
    Specialty specialty;
    double physicsGrade;
    double mathGrade;
    double computerScienceGrade;
};


void inputStudentsData(Student* students, int count) {
    for (int i = 0; i < count; ++i) {
        std::cout << "Enter data for student " << i + 1 << ":\n";
        std::cout << "Surname: ";
        std::cin >> students[i].surname;

        while (true) {
            std::cout << "Course: ";
            if (std::cin >> students[i].course && students[i].course > 0) {
                break;
            } else {
                std::cout << "Invalid input. Course must be a positive integer.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        while (true) {
            std::cout << "Specialty (1 - Computer Science, 2 - Physics, 3 - Mathematics): ";
            int specialtyChoice;
            if (std::cin >> specialtyChoice && specialtyChoice >= 1 && specialtyChoice <= 3) {
                students[i].specialty = static_cast<Specialty>(specialtyChoice - 1);
                break;
            } else {
                std::cout << "Invalid input. Please enter a valid specialty.\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }

        switch (students[i].specialty) {
            case Specialty::ComputerScience:
                std::cout << "Computer Science Grade: ";
                std::cin >> students[i].computerScienceGrade;
                break;
            case Specialty::Physics:
                std::cout << "Physics Grade: ";
                std::cin >> students[i].physicsGrade;
                break;
            case Specialty::Mathematics:
                std::cout << "Math Grade: ";
                std::cin >> students[i].mathGrade;
                break;
        }

        std::cout << "\n";
    }
}


void displayStudentsTable(const Student* students, int count) {
    
    std::cout << "-------------------------------------------------------------------\n";
    std::cout << "| No. | Surname   | Course | Specialty     | Physics | Math | CS   |\n";
    std::cout << "-------------------------------------------------------------------\n";

    
    for (int i = 0; i < count; ++i) {
        std::cout << "| " << i + 1 << "   | ";
        std::cout.width(10);
        std::cout << students[i].surname << " | ";
        std::cout.width(6);
        std::cout << students[i].course << " | ";
        std::cout.width(14);

        switch (students[i].specialty) {
            case Specialty::ComputerScience:
                std::cout << "Computer Science | ";
                std::cout.width(7);
                std::cout << students[i].physicsGrade << " | N/A  | ";
                std::cout.width(4);
                std::cout << students[i].computerScienceGrade << " | ";
                break;
            case Specialty::Physics:
                std::cout << "Physics          | ";
                std::cout.width(7);
                std::cout << students[i].physicsGrade << " | N/A  | N/A  | ";
                break;
            case Specialty::Mathematics:
                std::cout << "Mathematics      | N/A  | ";
                std::cout.width(5);
                std::cout << students[i].mathGrade << " | N/A  | ";
                break;
        }

        std::cout << "\n";
    }

    
    std::cout << "-------------------------------------------------------------------\n";
}


void sortStudentsByPhysicsGrade(Student* students, int count) {
    std::sort(students, students + count, [](const Student& a, const Student& b) {
        return a.physicsGrade > b.physicsGrade;
    });
}


void buildIndexArray(const Student* students, int* indexArray, int count) {
    for (int i = 0; i < count; ++i) {
        indexArray[i] = i;
    }

    std::sort(indexArray, indexArray + count, [&students](int a, int b) {
        if (students[a].physicsGrade != students[b].physicsGrade) {
            return students[a].physicsGrade > students[b].physicsGrade;
        } else if (students[a].course != students[b].course) {
            return students[a].course > students[b].course;
        } else {
            return students[a].surname > students[b].surname;
        }
    });
}


bool binarySearch(const Student* students, int count, const std::string& surname, int course, double physicsGrade) {
    int left = 0;
    int right = count - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (students[mid].surname == surname && students[mid].course == course && students[mid].physicsGrade == physicsGrade) {
            return true;  
        } else if (students[mid].surname > surname || (students[mid].surname == surname && students[mid].course > course) ||
                   (students[mid].surname == surname && students[mid].course == course && students[mid].physicsGrade > physicsGrade)) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    return false;  
}

int main() {
    int numberOfStudents;

    while (true) {
        std::cout << "Enter the number of students: ";
        if (std::cin >> numberOfStudents && numberOfStudents > 0) {
            break;
        } else {
            std::cout << "Invalid input. Number of students must be a positive integer.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    
    Student* students = new Student[numberOfStudents];

    
    inputStudentsData(students, numberOfStudents);

    
    sortStudentsByPhysicsGrade(students, numberOfStudents);

    
    displayStudentsTable(students, numberOfStudents);

    
    int* indexArray = new int[numberOfStudents];
    buildIndexArray(students, indexArray, numberOfStudents);

    
    std::cout << "\nIndex Array: ";
    for (int i = 0; i < numberOfStudents; ++i) {
        std::cout << indexArray[i] << " ";
    }
    std::cout << "\n";

    
    std::string searchSurname;
    int searchCourse;
    double searchPhysicsGrade;

    std::cout << "\nEnter student details for binary search:\n";
    std::cout << "Surname: ";
    std::cin >> searchSurname;
    std::cout << "Course: ";
    std::cin >> searchCourse;
    std::cout << "Physics Grade: ";
    std::cin >> searchPhysicsGrade;

    bool found = binarySearch(students, numberOfStudents, searchSurname, searchCourse, searchPhysicsGrade);
    if (found) {
        std::cout << "Student found!\n";
    } else {
        std::cout << "Student not found.\n";
    }

   
    delete[] students;
    delete[] indexArray;

    return 0;
}
