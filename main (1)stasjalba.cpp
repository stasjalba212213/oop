#include <iostream>
#include <vector>

class Carte {
public:
    std::string titlu;
    std::string autor;
    std::string isbn;

    Carte(std::string t, std::string a, std::string i) : titlu(t), autor(a), isbn(i) {}
};

class Biblioteca {
public:
    std::vector<Carte> carti;

    void adaugaCarte(const Carte& carte) {
        carti.push_back(carte);
    }

    void eliminaCarte(const Carte& carte) {
        carti.erase(std::remove(carti.begin(), carti.end(), carte), carti.end());
    }

    void afiseazaCarti() {
        for (const auto& carte : carti) {
            std::cout << "Titlu: " << carte.titlu << ", Autor: " << carte.autor << ", ISBN: " << carte.isbn << std::endl;
        }
    }
};

int main() {
    Carte carte1("Marele Gatsby", "F. Scott Fitzgerald", "978-3-16-148410-0");
    Carte carte2("Să ucizi o pasăre cântătoare", "Harper Lee", "978-0-06-112008-4");

    Biblioteca biblioteca;

    biblioteca.adaugaCarte(carte1);
    biblioteca.adaugaCarte(carte2);

    biblioteca.afiseazaCarti();

    biblioteca.eliminaCarte(carte1);

    biblioteca.afiseazaCarti();

    return 0;
}
