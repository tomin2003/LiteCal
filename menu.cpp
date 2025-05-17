// menu.h - menükezelő függvényeinek definíciói - SAXHSH

#include "menu.h"

#include "date.h"
#include "time.h"
#include "event.h"
#include "calendar.h"
#include "string.h"
#include "menu.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <limits>

void waitForReturn() {
    std::cout << "Nyomj meg bármilyen gombot a visszatéréshez...";
    std::cin.get();
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void showMainMenu() {
    clearScreen();
    // Egy kis ASCII rajz - credit: https://patorjk.com/
    std::cout
    <<" _     _ _       _____       _ \n"
    <<"| |   (_) |     /  __ \\     | |\n"
    <<"| |    _| |_ ___| /  \\/ __ _| |\n"
    <<"| |   | | __/ _ \\ |    / _` | |\n"
    <<"| |___| | ||  __/ \\__/\\ (_| | |\n"
    <<"\\_____/_|\\__\\___|\\____/\\__,_|_|\n";
    std::cout << "\n--- FŐMENÜ ---\n"
    << "1. Események kezelése\n"
    << "2. Naptárműveletek\n"
    << "3. Havi naptár kiírása\n"
    << "4. Éves naptár kiírása\n"
    << "5. Kilépés\n"
    << "Válassz opciót (1-5): ";
}

void showManageMenu() {
    clearScreen();
    std::cout << "\n--- ESEMÉNYEK ---\n"
    << "1. Foglalt napok listázása\n"
    << "2. Új esemény felvétele\n"
    << "3. Esemény törlése\n"
    << "4. Keresés\n"
    << "5. Szűrés...\n"
    << "6. Vissza\n"
    << "Válassz opciót (1-6): ";
}

void showCalOpsMenu() {
    clearScreen();
    std::cout << "\n--- NAPTÁRMŰVELETEK ---\n"
    << "1. A hét melyik napjára esik egy nap?\n"
    << "2. Hány nap van a két dátum között?\n"
    << "3. Hány nap van hátra egy adott dátumig?\n"
    << "4. Mi lesz a dátum X nap múlva?\n"
    << "5. Vissza\n"
    << "Válassz opciót (1-5): ";
}

void showFilterMenu() {
    clearScreen();
    std::cout << "\n--- SZŰRÉS ---\n"
    << "1. Dátum szerint\n"
    << "2. Év és hónap szerint\n"
    << "3. Hónap és nap szerint\n"
    << "4. Év szerint\n"
    << "5. Hónap szerint\n"
    << "6. Nap szerint\n"
    << "7. Vissza\n"
    << "Válassz opciót (1-7): ";
}

void showMonthly(const EventStore& mainStore) {
    clearScreen();
    std::cout << "\n--- Havi naptár ---\n"
    << "\nMelyik év? ";
    int year;
    std::cin >> year;
    std::cout << "\nMelyik hónap? ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    int month;
    std::cin >> month;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    clearScreen();
    try {
        MonthlyCalendar(mainStore, year, month).printCalendar();
    } catch(const invalid_date &e) {
        clearScreen();
        std::cout << e.what() << "\nAdj meg egy új dátumot.\n";
    }
}

void showYearly(const EventStore& mainStore) {
    clearScreen();
    std::cout << "\n--- Éves naptár ---\n"
    << "\nMelyik év? ";
    int year;
    std::cin >> year;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    clearScreen();
    try {
        YearlyCalendar(mainStore, year).printCalendar();
    } catch(const invalid_date &e) {
        clearScreen();
        std::cout << e.what() << "\nAdj meg egy új dátumot.\n";
    }
}

void handleAddEvent(EventStore& mainStore) {
    clearScreen();
    try {
        Event ev;
        std::cout << "Add meg az eseményt (ÉÉÉÉ. HH. NN. ÓÓ:PP - LEÍRÁS):\n";
        std::cin >> ev;
        if (!std::cin) {
            std::cout << '\n';
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        }
        char c;
        std::cout << "Ez helyes? (i/n) " << ev << "\n";
        std::cin >> c;
        if (c == 'i') {
            mainStore + ev;
            mainStore.sort();   
            clearScreen();
            std::cout << "Esemény hozzáadva.\n";
            std::cin.ignore();
        } else if (c == 'n') {
            clearScreen();
            std::cout << "Hozzáadás megszakítva." << std::endl;
            std::cin.ignore();
        }
    } catch (const invalid_date &e) {
        clearScreen();
        std::cout << e.what() << std::endl;
        std::cin.ignore();
    } catch (const invalid_time &e) {
        clearScreen();
        std::cout << e.what() << std::endl;
        std::cin.ignore();
    } catch (const evclash &e) {
        clearScreen();
        std::cout << e.what() << std::endl;
        std::cin.ignore();
    }
}

void handleDelEvent(EventStore& mainStore) {
    clearScreen();
        std::cout << mainStore << std::endl;
    try {
        Event ev;
        std::cout << "Add meg az eseményt (ÉÉÉÉ. HH. NN. ÓÓ:PP - LEÍRÁS):" << std::endl;
        std::cin >> ev;
        if (!std::cin) {
            std::cout << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            char c;
            std::cout << "Biztos szeretnéd törölni? (i/n) " << ev << std::endl;
            std::cin >> c;
            if (c == 'i') {
                mainStore - ev; // A túlterhelt "-" operátor tud nofind kivételt dobni
                mainStore.sort(); // A törlés után egy újrarendezés
                clearScreen();
                std::cout << "Esemény törölve." << std::endl;
                std::cin.ignore();
            } else if (c == 'n') {
                clearScreen();
                std::cout << "Törlés megszakítva." << std::endl;
                std::cin.ignore();
            }
        }
    } catch (const invalid_date &e) {
        clearScreen();
        std::cout << e.what() << std::endl;
    } catch (const invalid_time &e) {
        clearScreen();
        std::cout << e.what() << std::endl;
    } catch (const nofind &e) {
        clearScreen();
        std::cout << e.what() << std::endl;
    }
}

void handleSearch(const EventStore& mainStore) {
    clearScreen();
    try {
        Event ev;
        std::cout << "Add meg az eseményt (ÉÉÉÉ. HH. NN. ÓÓ:PP - LEÍRÁS):\n";
        std::cin >> ev;
        if (!std::cin) {
            std::cout << '\n';
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        mainStore.find(ev);
        std::cout << "A(z) '" << ev << "' esemény benne van a listában.\n";
    } catch (const invalid_date &e) {
        clearScreen();
        std::cout << e.what() << std::endl;
    } catch (const invalid_time &e) {
        clearScreen();
        std::cout << e.what() << std::endl;
    } catch (const nofind &e) {
        clearScreen();
        std::cout << e.what() << std::endl;
    }
}

void handleFilter(EventStore& mainStore, FilterOpts option) {
    clearScreen();
    try {
        int year = NOPARAM, month = NOPARAM, day = NOPARAM;
        bool inputOk = true;
        // Az érvénytelen napokat/hónapokat egy dummy dátummal hibakezelhetjük, 
        // legyen az év 1972, mert az szökőév, és 29-e is előfordulhat ha nem adunk meg külön évet
        Date dummy(1972,1,1);

        switch (option) {
            case FilterOpts::BYDATE: {
                Date d;
                std::cout << "Add meg a dátumot (ÉÉÉÉ. HH. NN.): ";
                std::cin >> d;
                if (!std::cin) inputOk = false;
                else {
                    year = d.getYear();
                    month = d.getMonth();
                    day = d.getDay();
                }
                break;
            }
            case FilterOpts::BYYEARANDMONTH: {
                std::cout << "Add meg az évet: ";
                std::cin >> year;
                std::cout << "Add meg a hónapot: ";
                std::cin >> month;
                dummy.setYear(year);
                dummy.setMonth(month);
                if (!std::cin) inputOk = false;
                break;
            }
            case FilterOpts::BYMONTHANDDAY: {
                std::cout << "Add meg a hónapot: ";
                std::cin >> month;
                std::cout << "Add meg a napot: ";
                std::cin >> day;
                dummy.setMonth(month);
                dummy.setDay(year);
                if (!std::cin) inputOk = false;
                break;
            }
            case FilterOpts::BYYEAR: {
                std::cout << "Add meg az évet: ";
                std::cin >> year;
                dummy.setYear(year);
                if (!std::cin) inputOk = false;
                break;
            }
            case FilterOpts::BYMONTH: {
                std::cout << "Add meg a hónapot: ";
                std::cin >> month;
                dummy.setMonth(month);
                if (!std::cin) inputOk = false;
                break;
            }
            case FilterOpts::BYDAY: {
                std::cout << "Add meg a napot: ";
                std::cin >> day;
                dummy.setDay(day);
                if (!std::cin) inputOk = false;
                break;
            }
        }

        if (!inputOk) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
        }

        EventStore temp = mainStore.filterBy(year, month, day);
        std::cout << temp << std::endl;

        if (temp.getNEvents() != 0) {
            std::cout << "Szeretnéd ezt a szűrést beállítani? (i/n)\n";
            char c;
            std::cin >> c;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (c == 'i') {
                mainStore = temp;
                clearScreen();
                std::cout << "A beállítás megtörtént." << std::endl;
            } else if (c == 'n') {
                clearScreen();
                std::cout << "Nem történt módosítás." << std::endl;
            }
        } else {
            clearScreen();
            std::cout << "A szűrés nem tért vissza bejegyzésekkel." << std::endl;
            std::cin.ignore();
        }
    } catch (const invalid_date &e) {
        clearScreen();
        std::cout << e.what() << std::endl;
        std::cin.ignore();
    }
}

void handleCalOps(EventStore& mainStore, CalOpOpts option) {
    clearScreen();
    try {
        bool inputOk = true;

        switch (option) {
            case CalOpOpts::WHATDAY: {
                Date d;
                std::cout << "Add meg a dátumot (ÉÉÉÉ. HH. NN.): ";
                std::cin >> d;
                if (!std::cin) inputOk = false;
                else {
                    clearScreen();
                    std::cout << "A dátum " << d.getWeekDay() << "-re/ra esik." << std::endl;
                    std::cin.get();
                    std::cin.clear();
                }
                break;
            }
            case CalOpOpts::NUMBETWEEN: {
                Date d1;
                std::cout << "Add meg a kezdődátumot (ÉÉÉÉ. HH. NN.): ";
                std::cin >> d1;
                Date d2;
                std::cout << "Add meg a végdátumot (ÉÉÉÉ. HH. NN.): ";
                std::cin >> d2;
                if (!std::cin) inputOk = false;
                else {
                    clearScreen();
                    std::cout << "A két dátum között " << d1-d2 << " nap van." << std::endl;
                    std::cin.get();
                    std::cin.clear();
                }
                break;
            }
            case CalOpOpts::NUMTILL: {
                Date d1;
                std::cout << "Add meg a mai dátumot (ÉÉÉÉ. HH. NN.): ";
                std::cin >> d1;
                Date d2;
                std::cout << "Add meg a végdátumot (ÉÉÉÉ. HH. NN.): ";
                std::cin >> d2;
                // Ha végdátum hamarabb van mint a "mai" nap, akkor direkt rontsuk el, hogy kivételt dobjon
                if (d2 <= d1) d2.setYear(9999); 
                if (!std::cin) inputOk = false;
                else {
                    clearScreen();
                    std::cout << d2 << "-ig " << d1-d2 << " nap van hátra." << std::endl;
                    std::cin.get();
                    std::cin.clear();
                }
                break;
            }
            case CalOpOpts::DAYINX: {
                Date d1;
                std::cout << "Add meg a kezdő dátumot (ÉÉÉÉ. HH. NN.): ";
                std::cin >> d1;
                int day;
                std::cout << "Add meg a napot: ";
                std::cin >> day;
                if (!std::cin) inputOk = false;
                else {
                    clearScreen();
                    std::cout << day << " nap múlva " << d1+day << " lesz." << std::endl;
                    std::cin.get();
                    std::cin.clear();
                }
                break;
            }
        }
    if (!inputOk) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    } catch (const invalid_date &e) {
        clearScreen();
        std::cout << e.what() << std::endl;
        std::cin.ignore();
    }
}