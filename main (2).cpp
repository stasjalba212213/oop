#include <iostream>
#include <vector>

enum class StudyField {
    COMPUTER_SCIENCE,
    ELECTRICAL_ENGINEERING,
    MECHANICAL_ENGINEERING,
    CIVIL_ENGINEERING,
    BIOLOGY,
    CHEMISTRY,
    PHYSICS,
    MATHEMATICS,
    LITERATURE,
    HISTORY
};

class Student {
public:
    std::string firstName;
    std::string lastName;
    std::string email;
    std::string enrollmentDate;
    std::string dateOfBirth;

    Student(std::string fName, std::string lName, std::string mail, std::string enrollDate, std::string dob)
        : firstName(fName), lastName(lName), email(mail), enrollmentDate(enrollDate), dateOfBirth(dob) {}
};

class Faculty {
public:
    std::string name;
    std::string abbreviation;
    std::vector<Student> students;
    StudyField studyField;

    Faculty(std::string n, std::string abbr, StudyField field) : name(n), abbreviation(abbr), studyField(field) {}

    void addStudent(const Student& student) {
        students.push_back(student);
    }

    void displayStudents() {
        std::cout << "Students in " << name << " (" << abbreviation << ") - Study Field: ";
        switch (studyField) {
            case StudyField::COMPUTER_SCIENCE:
                std::cout << "Computer Science";
                break;
            case StudyField::ELECTRICAL_ENGINEERING:
                std::cout << "Electrical Engineering";
                break;
            default:
                std::cout << "Unknown";
                break;
        }
        std::cout << ":" << std::endl;

        for (const auto& student : students) {
            std::cout << "Name: " << student.firstName << " " << student.lastName
                      << ", Email: " << student.email
                      << ", Enrollment Date: " << student.enrollmentDate
                      << ", Date of Birth: " << student.dateOfBirth << std::endl;
        }
    }
};

int main() {
    Student student1("John", "Doe", "john.doe@example.com", "2022-02-15", "1998-05-20");
    Student student2("Jane", "Smith", "jane.smith@example.com", "2022-02-20", "1999-03-10");

    Faculty computerScienceFaculty("Computer Science Faculty", "CSF", StudyField::COMPUTER_SCIENCE);
    computerScienceFaculty.addStudent(student1);
    computerScienceFaculty.addStudent(student2);

    computerScienceFaculty.displayStudents();

    return 0;
}
