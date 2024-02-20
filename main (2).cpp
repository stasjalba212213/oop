#include <iostream>
#include <vector>
#include <algorithm>

struct Student {
    std::string uniqueIdentifier; 
    std::string name;
    bool graduated;
};

struct Faculty {
    std::string name;
    std::string field;
    std::vector<Student> students;
};

std::vector<Faculty> universities;

void addStudentToFaculty(const std::string& facultyName, const Student& student) {
    auto faculty = std::find_if(universities.begin(), universities.end(),
        [&facultyName](const Faculty& f) { return f.name == facultyName; });

    if (faculty != universities.end()) {
        faculty->students.push_back(student);
        std::cout << "Studentul " << student.name << " a fost adaugat la facultatea " << faculty->name << std::endl;
    } else {
        std::cout << "Facultatea " << facultyName << " nu a fost gasita." << std::endl;
    }
}

void graduateStudent(const std::string& facultyName, const std::string& uniqueIdentifier) {
    auto faculty = std::find_if(universities.begin(), universities.end(),
        [&facultyName](const Faculty& f) { return f.name == facultyName; });

    if (faculty != universities.end()) {
        auto student = std::find_if(faculty->students.begin(), faculty->students.end(),
            [&uniqueIdentifier](const Student& s) { return s.uniqueIdentifier == uniqueIdentifier; });

        if (student != faculty->students.end()) {
            student->graduated = true;
            std::cout << "Studentul " << student->name << " a absolvit cu succes." << std::endl;
        } else {
            std::cout << "Studentul cu identificatorul " << uniqueIdentifier << " nu a fost gasit la facultatea " << facultyName << std::endl;
        }
    } else {
        std::cout << "Facultatea " << facultyName << " nu a fost gasita." << std::endl;
    }
}

void displayCurrentEnrolledStudents(const std::string& facultyName) {
    auto faculty = std::find_if(universities.begin(), universities.end(),
        [&facultyName](const Faculty& f) { return f.name == facultyName; });

    if (faculty != universities.end()) {
        std::cout << "Studentii actuali la facultatea " << faculty->name << " sunt:" << std::endl;
        for (const auto& student : faculty->students) {
            if (!student.graduated) {
                std::cout << student.name << std::endl;
            }
        }
    } else {
        std::cout << "Facultatea " << facultyName << " nu a fost gasita." << std::endl;
    }
}

void displayGraduates(const std::string& facultyName) {
    auto faculty = std::find_if(universities.begin(), universities.end(),
        [&facultyName](const Faculty& f) { return f.name == facultyName; });

    if (faculty != universities.end()) {
        std::cout << "Absolventii facultatii " << faculty->name << " sunt:" << std::endl;
        for (const auto& student : faculty->students) {
            if (student.graduated) {
                std::cout << student.name << std::endl;
            }
        }
    } else {
        std::cout << "Facultatea " << facultyName << " nu a fost gasita." << std::endl;
    }
}

bool isStudentInFaculty(const std::string& facultyName, const std::string& uniqueIdentifier) {
    auto faculty = std::find_if(universities.begin(), universities.end(),
        [&facultyName](const Faculty& f) { return f.name == facultyName; });

    if (faculty != universities.end()) {
        auto student = std::find_if(faculty->students.begin(), faculty->students.end(),
            [&uniqueIdentifier](const Student& s) { return s.uniqueIdentifier == uniqueIdentifier; });

        return student != faculty->students.end();
    } else {
        std::cout << "Facultatea " << facultyName << " nu a fost gasita." << std::endl;
        return false;
    }
}

void createNewFaculty(const std::string& facultyName, const std::string& field) {
    auto faculty = std::find_if(universities.begin(), universities.end(),
        [&facultyName](const Faculty& f) { return f.name == facultyName; });

    if (faculty == universities.end()) {
        Faculty newFaculty;
        newFaculty.name = facultyName;
        newFaculty.field = field;
        universities.push_back(newFaculty);
        std::cout << "Facultatea " << facultyName << " a fost creata cu succes in domeniul " << field << std::endl;
    } else {
        std::cout << "Facultatea " << facultyName << " deja exista." << std::endl;
    }
}

void searchFacultyByStudentIdentifier(const std::string& uniqueIdentifier) {
    for (const auto& faculty : universities) {
        auto student = std::find_if(faculty.students.begin(), faculty.students.end(),
            [&uniqueIdentifier](const Student& s) { return s.uniqueIdentifier == uniqueIdentifier; });

        if (student != faculty.students.end()) {
            std::cout << "Studentul " << student->name << " apartine facultatii " << faculty.name << std::endl;
            return;
        }
    }

    std::cout << "Studentul cu identificatorul " << uniqueIdentifier << " nu a fost gasit in nicio facultate." << std::endl;
}

void displayUniversityFaculties() {
    std::cout << "Facultatile universitatii sunt:" << std::endl;
    for (const auto& faculty : universities) {
        std::cout << faculty.name << " - Domeniu: " << faculty.field << std::endl;
    }
}

void displayFacultiesByField(const std::string&
