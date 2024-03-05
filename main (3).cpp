#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <ctime>
#include <filesystem>

namespace fs = std::filesystem;

struct FileInfo {
    std::string filename;
    std::string extension;
    std::time_t createdTime;
    std::time_t updatedTime;
};

class FileManager {
private:
    std::string folderPath;
    std::time_t snapshotTime;
    std::vector<FileInfo> files;

public:
    FileManager(const std::string& path) : folderPath(path), snapshotTime(0) {
        updateFilesList();
    }

    void commit() {
        snapshotTime = std::time(nullptr);
        std::cout << "Snapshot actualizat la " << std::put_time(std::localtime(&snapshotTime), "%c") << std::endl;
    }

    void info(const std::string& filename) {
        auto it = std::find_if(files.begin(), files.end(), [&filename](const FileInfo& fileInfo) {
            return fileInfo.filename == filename;
        });

        if (it != files.end()) {
            const FileInfo& fileInfo = *it;

            std::cout << "Informații despre fișierul \"" << fileInfo.filename << "\":" << std::endl;
            std::cout << "Extensie: " << fileInfo.extension << std::endl;
            std::cout << "Creat la: " << std::put_time(std::localtime(&fileInfo.createdTime), "%c") << std::endl;
            std::cout << "Ultima actualizare la: " << std::put_time(std::localtime(&fileInfo.updatedTime), "%c") << std::endl;

            // Adăugați informații specifice fiecărui tip de fișier aici
        } else {
            std::cout << "Fișierul \"" << filename << "\" nu a fost găsit." << std::endl;
        }
    }

    void status() {
        std::cout << "Status la " << std::put_time(std::localtime(&snapshotTime), "%c") << ":" << std::endl;

        for (const auto& fileInfo : files) {
            std::cout << "Fișier: " << fileInfo.filename;

            if (fileInfo.updatedTime > snapshotTime) {
                std::cout << " - Modificat" << std::endl;
            } else {
                std::cout << " - Neschimbat" << std::endl;
            }
        }
    }

private:
    void updateFilesList() {
        files.clear();

        for (const auto& entry : fs::directory_iterator(folderPath)) {
            if (entry.is_regular_file()) {
                FileInfo fileInfo;
                fileInfo.filename = entry.path().filename().string();
                fileInfo.extension = entry.path().extension().string();
                fileInfo.createdTime = fs::last_write_time(entry);
                fileInfo.updatedTime = fileInfo.createdTime;

                files.push_back(fileInfo);
            }
        }
    }
};

int main() {
    std::string folderPath = "C:\\Cale\\Catre\\Folder";

    FileManager fileManager(folderPath);

    while (true) {
        std::cout << "\nAcțiuni disponibile:\n";
        std::cout << "1. commit - Actualizează snapshot-ul\n";
        std::cout << "2. info <nume_fișier> - Afișează informații despre un fișier\n";
        std::cout << "3. status - Afișează starea fișierelor\n";
        std::cout << "0. Ieșire\n";

        std::string userInput;
        std::getline(std::cin, userInput);

        if (userInput == "1") {
            fileManager.commit();
        } else if (userInput.find("info") == 0) {
            std::string filename = userInput.substr(5);
            fileManager.info(filename);
        } else if (userInput == "3") {
            fileManager.status();
        } else if (userInput == "0") {
            break;
        } else {
            std::cout << "Comandă invalidă. Încercați din nou.\n";
        }
    }

    return 0;
}
