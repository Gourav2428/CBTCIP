#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class StudentManager {
public:
    void displayMenu();
    void addStudent();
    void viewStudents();
    void searchStudent();
    void modifyStudent();
    void removeStudent();

private:
    struct Student {
        int studentId;
        std::string studentName;
        int studentAge;
        std::string studentDepartment;
    };

    void saveToFile(const Student& student);
    std::vector<Student> loadFromFile();
    void saveAllToFile(const std::vector<Student>& students);
};

void StudentManager::displayMenu() {
    int option;
    do {
        std::cout << "\n--- Student Management System ---\n";
        std::cout << "1. Add Student\n";
        std::cout << "2. View All Students\n";
        std::cout << "3. Search Student\n";
        std::cout << "4. Modify Student\n";
        std::cout << "5. Remove Student\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> option;

        switch (option) {
            case 1:
                addStudent();
                break;
            case 2:
                viewStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                modifyStudent();
                break;
            case 5:
                removeStudent();
                break;
            case 6:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (option != 6);
}

void StudentManager::addStudent() {
    Student newStudent;
    std::cout << "Enter Student ID: ";
    std::cin >> newStudent.studentId;
    std::cin.ignore(); // To ignore the newline character left by std::cin
    std::cout << "Enter Student Name: ";
    std::getline(std::cin, newStudent.studentName);
    std::cout << "Enter Student Age: ";
    std::cin >> newStudent.studentAge;
    std::cin.ignore();
    std::cout << "Enter Student Department: ";
    std::getline(std::cin, newStudent.studentDepartment);

    saveToFile(newStudent);
    std::cout << "Student added successfully.\n";
}

void StudentManager::viewStudents() {
    std::vector<Student> students = loadFromFile();
    std::cout << "\n--- Student List ---\n";
    for (const auto& student : students) {
        std::cout << "ID: " << student.studentId << "\n";
        std::cout << "Name: " << student.studentName << "\n";
        std::cout << "Age: " << student.studentAge << "\n";
        std::cout << "Department: " << student.studentDepartment << "\n";
        std::cout << "---------------------\n";
    }
}

void StudentManager::searchStudent() {
    int searchId;
    std::cout << "Enter Student ID to search: ";
    std::cin >> searchId;

    std::vector<Student> students = loadFromFile();
    for (const auto& student : students) {
        if (student.studentId == searchId) {
            std::cout << "\n--- Student Found ---\n";
            std::cout << "ID: " << student.studentId << "\n";
            std::cout << "Name: " << student.studentName << "\n";
            std::cout << "Age: " << student.studentAge << "\n";
            std::cout << "Department: " << student.studentDepartment << "\n";
            return;
        }
    }
    std::cout << "Student not found.\n";
}

void StudentManager::modifyStudent() {
    int modifyId;
    std::cout << "Enter Student ID to modify: ";
    std::cin >> modifyId;

    std::vector<Student> students = loadFromFile();
    for (auto& student : students) {
        if (student.studentId == modifyId) {
            std::cout << "Enter new Student Name: ";
            std::cin.ignore();
            std::getline(std::cin, student.studentName);
            std::cout << "Enter new Student Age: ";
            std::cin >> student.studentAge;
            std::cin.ignore();
            std::cout << "Enter new Student Department: ";
            std::getline(std::cin, student.studentDepartment);

            saveAllToFile(students);
            std::cout << "Student modified successfully.\n";
            return;
        }
    }
    std::cout << "Student not found.\n";
}

void StudentManager::removeStudent() {
    int deleteId;
    std::cout << "Enter Student ID to remove: ";
    std::cin >> deleteId;

    std::vector<Student> students = loadFromFile();
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->studentId == deleteId) {
            students.erase(it);
            saveAllToFile(students);
            std::cout << "Student removed successfully.\n";
            return;
        }
    }
    std::cout << "Student not found.\n";
}

void StudentManager::saveToFile(const Student& student) {
    std::ofstream file("students.dat", std::ios::binary | std::ios::app);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(&student), sizeof(Student));
        file.close();
    } else {
        std::cerr << "Unable to open file for writing.\n";
    }
}

std::vector<StudentManager::Student> StudentManager::loadFromFile() {
    std::vector<Student> students;
    std::ifstream file("students.dat", std::ios::binary);
    if (file.is_open()) {
        Student student;
        while (file.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
            students.push_back(student);
        }
        file.close();
    } else {
        std::cerr << "Unable to open file for reading.\n";
    }
    return students;
}

void StudentManager::saveAllToFile(const std::vector<Student>& students) {
    std::ofstream file("students.dat", std::ios::binary | std::ios::trunc);
    if (file.is_open()) {
        for (const auto& student : students) {
            file.write(reinterpret_cast<const char*>(&student), sizeof(Student));
        }
        file.close();
    } else {
        std::cerr << "Unable to open file for writing.\n";
    }
}

int main() {
    StudentManager manager;
    manager.displayMenu();
    return 0;
}
