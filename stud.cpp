#include "Stud.h"

void duomenuived(Studentas &Lok){
    while (true) {
        cout << "Iveskite Varda: ";
        std::getline(cin, Lok.vardas);
        if (Lok.vardas.empty()) {
            cout << "Vardas negali buti tuscias. Bandykite dar karta." << endl;
        } else {
            break;
        }
    }
    while (true) {
        cout << "Iveskite Pavarde: ";
        std::getline(cin, Lok.pavarde);
        if (Lok.pavarde.empty()) {
            cout << "Pavarde negali buti tuscia. Bandykite dar karta." << endl;
        } else {
            break;
        }
    }
    while (true) {
        cout << "Ar norite, kad pazymiai butu generuojami automatiskai? Jeigu Taip iveskite T, jeigu Ne - N: ";
        string ats;
        cin >> ats;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (ats == "T" || ats == "t") {
            atsitiktiniuBaluGeneravimas(Lok);
            break;
        } else if (ats == "N" || ats == "n") {
            int Egz;
            cout << "Iveskite egzamino rezultata (0 - 10): ";
            while (!(cin >> Egz) || Egz < 0 || Egz > 10) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Neteisingai ivedete, bandykite dar karta: ";
            }
            Lok.egz = Egz;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Iveskite Namu Darbu pazymius 1 - 10 (noredami uzbaigti ivedima iveskite 0): \n";
            int x;
            bool ivestasPazymys = false;
            while (true) {
                cout << "Pazymys: ";
                while (!(cin >> x)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Neteisingai ivedete, bandykite dar karta: ";
                }
                if (x < 0 || x > 10) {
                    cout << "Neteisingai";
                    continue;
                }
                if (x == 0) {
                    if (!ivestasPazymys) {
                        cout << "Turite ivesti bent viena pazymi. \n";
                        continue;
                    }
                    break;
                }
                Lok.NamuDarbai.push_back(x);
                ivestasPazymys = true;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        } else {
            cout << "Neteisingai ivedete. Prasome iveskite T arba N." << endl;
        }
    }
};

void spausdinimas(const vector<Studentas> &stud){
    cout << std::setw(15) << std::left << "Pavarde"
         << std::setw(15) << std::left << "Vardas"
         << std::setw(20) << std::left << "Galutinis (Vid.)"
         << std::setw(20) << std::left << "Galutinis (Med.)" << endl;

    cout << string(70, '-') << endl;

    for (const auto& Lok : stud){
        cout<< std::setw(15) << std::left << Lok.pavarde
        << std::setw(15) << std::left << Lok.vardas
        << std::setw(20) << std::left << std::fixed << std::setprecision(2) << skaicGalutiniBalaVidur(Lok)
        << std::setw(20) << std::left << std::fixed << std::setprecision(2) << skaicGalutiniBalaMed(Lok) << endl;
    }

};

void valymas(Studentas &Lok){
    Lok.vardas.clear();
    Lok.pavarde.clear();
    Lok.NamuDarbai.clear();
};
double vidurkioSkaic(const vector<int> &pazymiai){
    int suma = 0;
    for(int pazymys : pazymiai){
        suma += pazymys;
    };
    return suma/static_cast<double>(pazymiai.size());
};
double medianosSkaic(vector<int> pazymiai){
    sort(pazymiai.begin(), pazymiai.end());
    int kiekis = pazymiai.size();
    if (kiekis % 2 == 0){
        return (pazymiai[kiekis / 2 - 1] + pazymiai[kiekis / 2]) / 2.0;
    } else {
        return pazymiai[kiekis /2];
    }
};
double skaicGalutiniBalaVidur(const Studentas &studentas){
    double vidutinisND = vidurkioSkaic(studentas.NamuDarbai);
    return (vidutinisND * 0.4) + (studentas.egz * 0.6);
};
double skaicGalutiniBalaMed(const Studentas &studentas){
    double medianaND = medianosSkaic(studentas.NamuDarbai);
    return (medianaND * 0.4) + (studentas.egz * 0.6);
};
void atsitiktiniuBaluGeneravimas(Studentas &Lok){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 10);

    int NDskaicius = 5;
    for (int i=0; i < NDskaicius; i++){
        Lok.NamuDarbai.push_back(dist(mt));
    }
    Lok.egz = dist(mt);
};
void skaitytiFaila(vector<Studentas> &studentai, const string & failoPavadinimas){
    std::ifstream failas(failoPavadinimas);
    if (!failas) {
        cout<< "Nepavyko nuskaityti failo"<<endl;
        return;
    }
    string failoEilute;
    std::getline(failas, failoEilute);
    while(std::getline(failas, failoEilute)){
        std::istringstream iss(failoEilute);
        Studentas stud;

        iss >> stud.vardas >>stud.pavarde;

        if (iss.fail()){
            cout << "Nepavyko teisingai nuskaityti studento vardo ir pavardes." << endl;
            continue;
        }

        int pazymys;
        while(iss >> pazymys){
            if (pazymys < 0 || pazymys > 10) {
                cout << "Faile neteisingas pazymys studentui: " << stud.vardas << " " << stud.pavarde <<endl;
                continue;
            }
            stud.NamuDarbai.push_back(pazymys);
        }
        if (!stud.NamuDarbai.empty()) {
            stud.egz = stud.NamuDarbai.back();
            stud.NamuDarbai.pop_back();
        } else {
            cout << "Nera pazymiu studentui: " << stud.vardas << " " << stud.pavarde << endl;
            continue;
        }
        studentai.push_back(stud);
    }
    if (studentai.empty()){
        cout << "Ivyko klaida: Nebuvo galima nuskaityti jokiu studentu is failo" << endl;
    }
};
void generuotiStudentus (int studentuSkaicius, const string &failoPav){
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 10);

    auto start = std::chrono::high_resolution_clock::now();

    std::ofstream failas(failoPav);
    if (!failas){
        std::cerr << "Nepavyko atidaryti failo " << failoPav << endl;
        return;
    }
    failas << std::setw(20) << std::left << "Pavarde"
           << std::setw(20) << std::left << "Vardas";
    for (int i = 1; i <= 5; ++i) {
        failas << std::setw(10) << std::left << "ND" + std::to_string(i);
    }
    failas << std::setw(10) << std::left << "Egz." << std::endl;

    for (int i = 0; i < studentuSkaicius; i++) {
        string pavarde = "Pavarde" + std::to_string(i);
        string vardas = "Vardas" + std::to_string(i);

        failas << std::setw(20) << std::left << pavarde
               << std::setw(20) << std::left << vardas;
        for (int j=0; j<5; j++){
            failas << std::setw(10) << std::left << dist(mt);
        }
        failas << std::setw(10) << std::left << dist(mt) << endl;
    }
    failas.close();
    auto end = std::chrono::high_resolution_clock::now();
    duration<double> laikas = end - start;
    cout << "Sukurtas failas: " << failoPav << " su " << studentuSkaicius << " studentais. "
        << "Uztruko: " << laikas.count() << " sekundes." << endl;
}
bool rusiavimasPavarde(const Studentas &Lok, const Studentas &stud){
    return Lok.pavarde < stud.pavarde;
};
void studentuSkirstymas(const vector<Studentas> &studentai, vector<Studentas> &vargsiukai, vector<Studentas> &galvociai){
    for (const auto& stud : studentai){
        if (skaicGalutiniBalaVidur(stud) < 5.0){
            vargsiukai.push_back(stud);
        } else {
            galvociai.push_back(stud);
        }
    }
}
void rasytiIFaila(const vector<Studentas>& stud, const string& failoPav) {
    std::ofstream failas(failoPav);
    if (!failas) {
        std::cerr << "Nepavyko atidaryti failo " << failoPav << endl;
        return;
    }

    failas << std::setw(17) << std::left << "Pavarde"
           << std::setw(15) << std::left << "Vardas"
           << std::setw(20) << std::left << "Galutinis (Vid.)"
           << std::setw(20) << std::left << "Galutinis (Med.)" << endl;

    failas << std::string(70, '-') << endl;

    for (const auto& s : stud) {
        failas << std::setw(17) << std::left << s.pavarde
               << std::setw(15) << std::left << s.vardas
               << std::setw(20) << std::left << fixed << std::setprecision(2) << skaicGalutiniBalaVidur(s)
               << std::setw(20) << std::left << fixed << std::setprecision(2) << skaicGalutiniBalaMed(s) << std::endl;
    }
    failas.close();
}
void isrusiuotuFailuKurimas (vector<Studentas> &stud, const string& failoPav, int rusiavimoPasirinkimas){

    skaitytiFaila(stud, failoPav);

    if (rusiavimoPasirinkimas == 1){
        sort(stud.begin(), stud.end(), rusiavimasPavarde);
    } else if (rusiavimoPasirinkimas == 2) {
        sort(stud.begin(), stud.end(), [](const Studentas& a, const Studentas& b) {
                return skaicGalutiniBalaVidur(a) > skaicGalutiniBalaVidur(b);
            });
    } else {
        sort(stud.begin(), stud.end(), [](const Studentas& a, const Studentas& b) {
                return skaicGalutiniBalaVidur(a) < skaicGalutiniBalaVidur(b);
            });
    }

    vector<Studentas> vargsiukai, galvociai;
    studentuSkirstymas(stud, vargsiukai, galvociai);

    string vargsiukuFailas = failoPav + "_vargsiukai.txt";
    string galvociuFailas = failoPav + "_galvociai.txt";

    rasytiIFaila(vargsiukai, vargsiukuFailas);
    rasytiIFaila(galvociai, galvociuFailas);

    cout << "Failai " << vargsiukuFailas << " ir " << galvociuFailas << " buvo sukurti." << endl;
}
void failuTestavimas(string failoPav, vector<Studentas>& stud, int rusiavimoPasirinkimas) {
    stud.clear();
    auto start = high_resolution_clock::now();
    skaitytiFaila(stud, failoPav);
    auto end = high_resolution_clock::now();
    auto failoSkaitymas = duration_cast<milliseconds>(end - start).count();
    cout << "Failo is " << stud.size() << " irasu nuskaitymo laikas: " << fixed << setprecision(6) << failoSkaitymas / 1000.0 << " s" << endl;

    start = high_resolution_clock::now();
    if (rusiavimoPasirinkimas == 1){
        sort(stud.begin(), stud.end(), rusiavimasPavarde);
    } else if (rusiavimoPasirinkimas == 2) {
        sort(stud.begin(), stud.end(), [](const Studentas& a, const Studentas& b) {
                return skaicGalutiniBalaVidur(a) > skaicGalutiniBalaVidur(b);
            });
    } else {
        sort(stud.begin(), stud.end(), [](const Studentas& a, const Studentas& b) {
                return skaicGalutiniBalaVidur(a) < skaicGalutiniBalaVidur(b);
            });
    }

    end = high_resolution_clock::now();
    auto rusiavimoLaikas = duration_cast<milliseconds>(end - start).count();
    cout << "Rusiavimo laikas: " << fixed << setprecision(6) << rusiavimoLaikas / 1000.0 << " s" << endl;

    vector<Studentas> vargsiukai, galvociai;
    start = high_resolution_clock::now();
    studentuSkirstymas(stud, vargsiukai, galvociai);
    end = high_resolution_clock::now();
    auto skirstymoLaikas = duration_cast<milliseconds>(end - start).count();
    cout << "Dalijimo i dvi grupes laikas: " << fixed << setprecision(6) << skirstymoLaikas / 1000.0 << " s" << endl;

    string vargsiukaiFailas = failoPav + "_vargsiukai.txt";
    string galvociaiFailas = failoPav + "_galvociai.txt";

    start = high_resolution_clock::now();
    rasytiIFaila(vargsiukai, vargsiukaiFailas);
    end = high_resolution_clock::now();
    auto vfailoIsvedimoLaikas = duration_cast<milliseconds>(end - start).count();
    cout << "Irasymo i " << vargsiukaiFailas << " faila laikas: " << fixed << setprecision(6) << vfailoIsvedimoLaikas / 1000.0 << " s" << endl;

    start = high_resolution_clock::now();
    rasytiIFaila(galvociai, galvociaiFailas);
    end = high_resolution_clock::now();
    auto gfailoIsvedimoLaikas = duration_cast<milliseconds>(end - start).count();
    cout << "Irasymo i " << galvociaiFailas << " faila laikas: " << fixed << setprecision(6) << gfailoIsvedimoLaikas / 1000.0 << " s" << endl;

    auto visasLaikas = failoSkaitymas + rusiavimoLaikas + skirstymoLaikas + vfailoIsvedimoLaikas + gfailoIsvedimoLaikas;
    cout << stud.size() << " irasu testo laikas: " << fixed << setprecision(6) << visasLaikas / 1000.0 << " s" << endl << endl;
}
