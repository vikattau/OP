#include "Mylib.h"
#include "Stud.h"

int main()
{
    vector<Studentas> Vec1;
    Studentas A;
    cout<< "Noresite generuoti studentu failus, duomenis apie studentus nuskaityti is failo ar ivesti duomenis ranka? \n" <<
        "3 - jei norite atlikti programos veikimo greicio analize, \n" <<
        "2 - jei norite generuoti failus su studentu duomenimis, \n" <<
        "1 - jei norite nuskaityti nuo failo, \n" <<
        "0 - jei duomenis ivesite ranka: \n"<< endl;
    int ats;
    while(!(cin >> ats) || (ats != 1 && ats != 0 && ats != 2 && ats != 3)){
        cout << "Netinkama ivestis. Bandykite dar karta: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    try{
    if(ats == 1){
        cout<< "Kuri faila norite nuskaityti? (Pasirinkite skaiciu): \n"<<
            "1 - kursiokai.txt \n"<<
            "2 - studentai10000.txt \n"<<
            "3 - studentai100000.txt \n"<<
            "4 - studentai1000000.txt \n"<<endl;
        int failas;
        cin>>failas;
        if (failas == 1){
            skaitytiFaila(Vec1, "kursiokai.txt");
        }else if (failas == 2){
            skaitytiFaila(Vec1, "studentai10000.txt");
        }else if (failas == 3){
            skaitytiFaila(Vec1,"studentai100000.txt");
        }else if (failas == 4) {
            skaitytiFaila(Vec1, "studentai1000000.txt");
        }else{
            cout << "Tokio failo nera" << endl;
        }
        sort(Vec1.begin(), Vec1.end(), rusiavimasPavarde);
        spausdinimas(Vec1);
    }else if (ats == 0){
        cout<<"Kiek studentu ivesite?: ";
        int skaicius;
        while (!(cin >> skaicius) || skaicius <= 0){
            cout << "Netinkama ivesti, bandykite dar karta: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore();
        for(int i=0; i<skaicius; i++){
            cout<<"Iveskite informacija: "<<endl;
            duomenuived(A);
            Vec1.push_back(A);
            valymas(A);
        }
        sort(Vec1.begin(), Vec1.end(), rusiavimasPavarde);
        spausdinimas(Vec1);
    }else if (ats == 2){
        cout << "Kiek studentu norite sugeneruoti? (iveskite atitinkama skaiciu): \n" <<
            "1 - 1000 studentu \n" <<
            "2 - 10000 studentu \n" <<
            "3 - 100000 studentu \n" <<
            "4 - 1000000 studentu \n" <<
            "5 - 10000000 studentu \n" << endl;
        int skaicius;
        while(!(cin >> skaicius) || (skaicius != 1 && skaicius != 2 && skaicius != 3 && skaicius != 4 && skaicius != 5)){
            cout << "Netinkama ivestis. Bandykite dar karta: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        string failoPav;
        if (skaicius == 1){
            failoPav = "studentai_1000.txt";
            generuotiStudentus(1000, failoPav);
        }else if (skaicius == 2){
            failoPav = "studentai_10000.txt";
            generuotiStudentus(10000, failoPav);
        }else if (skaicius == 3){
            failoPav = "studentai_100000.txt";
            generuotiStudentus(100000, "studentai_100000.txt");
        }else if (skaicius == 4) {
            failoPav = "studentai_1000000.txt";
            generuotiStudentus(1000000, failoPav);
        }else if (skaicius == 5) {
            failoPav = "studentai_10000000.txt";
            generuotiStudentus(10000000, failoPav);
        }else{
            cout << "Klaida" << endl;
        }
    }else if (ats == 3){
        cout << "Kaip norite rusiuoti studentus?: \n"
            << "1 - pagal pavardes \n"
            << "2 - pagal galutini bala mazejancia tvarka \n"
            << "3 - pagal galutini bala didejancia tvarka \n" << endl;
        int rusiavimoPasirinkimas;
        cin >> rusiavimoPasirinkimas;

        vector<string> testuojamiFailai = {
        "studentai_1000.txt",
        "studentai_10000.txt",
        "studentai_100000.txt",
        "studentai_1000000.txt",
        "studentai_10000000.txt"
        };
        for (const auto& failoPav : testuojamiFailai) {
            cout << "Testuojamas failas: " << failoPav << endl;
            failuTestavimas(failoPav, Vec1, rusiavimoPasirinkimas);
        }
    }
    } catch (const std::runtime_error &e){
        cout << "Klaida: " << e.what() << endl;
    } catch (...){
        cout << "Ivyko nezinoma klaida." << endl;
    }
    system("pause");
    return 0;
};

