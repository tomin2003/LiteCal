// menu.cpp - menüvezérelt program implementációja - SAXHSH

#include "date.h"
#include "time.h"
#include "event.h"
#include "calendar.h"
#include "string.h"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <limits>

enum class MenuState {
    MAIN_MENU,
    MANAGE_MENU,
    MONTHLY,
    YEARLY,
    FILTER_MENU,
    EXIT
};

void showMainMenu() {
    system("clear");
    std::cout << "\n--- FŐMENÜ ---\n"
    << "1. Események kezelése\n"
    << "2. Havi naptár kiírása\n"
    << "3. Éves naptár kiírása\n"
    << "4. Kilépés\n"
    << "Válassz opciót (1-4): ";
}

void showManageMenu() {
    system("clear");
    std::cout << "\n--- ESEMÉNYEK ---\n"
    << "1. Listázás\n"
    << "2. Új felvétele\n"
    << "3. Törlés\n"
    << "4. Keresés\n"
    << "5. Szűrés...\n"
    << "6. Vissza\n"
    << "Válassz opciót (1-6): ";
}

void showFilterMenu() {
    system("clear");
    std::cout << "\n--- SZŰRÉS ---\n"
    << "1. Dátum szerint\n"
    << "2. Év szerint\n"
    << "3. Hónap szerint\n"
    << "4. Nap szerint\n"
    << "5. Vissza\n"
    << "Válassz opciót (1-5): ";
}

void showMonthly(const EventStore& es) {
    system("clear");
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
    system("clear");
    try {
        MonthlyCalendar(es, year, month).printCalendar();
    } catch(const invalid_date &e) {
        system("clear");
        std::cout << e.what() << "\nAdj meg egy új dátumot.\n";
    }
}

void showYearly(const EventStore& es) {
    system("clear");
    std::cout << "\n--- Éves naptár ---\n"
    << "\nMelyik év? ";
    int year;
    std::cin >> year;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    system("clear");
    try {
        YearlyCalendar(es, year).printCalendar();
    } catch(const invalid_date &e) {
        system("clear");
        std::cout << e.what() << "\nAdj meg egy új dátumot.\n";
    }
}

void handleAddEvent(EventStore& mainStore) {
    system("clear");
    bool correct = false;
    while (!correct) {
        try {
            Event ev;
            std::cout << "Add meg az eseményt (ÉÉÉÉ.HH.NN. ÓÓ:PP - LEÍRÁS):\n";
            std::cin >> ev;
            if (!std::cin) {
                std::cout << '\n';
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            char c;
            std::cout << "Ez helyes? (i/n) " << ev << "\n";
            std::cin >> c;
            if (c == 'i') {
                correct = true;
                mainStore + ev;
                mainStore.sort();   
                system("clear");
                std::cout << "Esemény hozzáadva.\n";
            } else if (c == 'n') {
                correct = false;
                system("clear");
            }
        } catch (const invalid_date &e) {
            system("clear");
            std::cout << e.what() << std::endl;
        } catch (const invalid_time &e) {
            system("clear");
            std::cout << e.what() << std::endl;
        } catch (const evclash &e) {
            system("clear");
            std::cout << e.what() << std::endl;
        }
    }
}

void handleDelEvent(EventStore& mainStore) {
    system("clear");
    try {
        Event ev;
        std::cout << "Add meg az eseményt (ÉÉÉÉ.HH.NN. ÓÓ:PP - LEÍRÁS):\n";
        std::cin >> ev;
        if (!std::cin) {
            std::cout << '\n';
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        char c;
        std::cout << "Biztos szeretnéd törölni? (i/n) " << ev << "\n";
        std::cin >> c;
        if (c == 'i') {
            mainStore - ev; // A túlterhelt "-" operátor tud nofind kivételt dobni
            mainStore.sort(); // A törlés után egy újrarendezés
            system("clear");
            std::cout << "Esemény törölve.\n";
        } else if (c == 'n') {
            system("clear");
            std::cout << "Törlés megszakítva.\n";
            return;
        }
    } catch (const invalid_date &e) {
        system("clear");
        std::cout << e.what() << std::endl;
    } catch (const invalid_time &e) {
        system("clear");
        std::cout << e.what() << std::endl;
    } catch (const nofind &e) {
        system("clear");
        std::cout << e.what() << std::endl;
    }
}

void handleSearch() {

}


int main() {
    MenuState currentState = MenuState::MAIN_MENU;
    bool running = true;
    EventStore mainStore;
    mainStore+Event(2025,01,01,00,00,"Haho")+Event(2025,01,11,00,00,"GA");

    while (running) {
        switch (currentState) {
            case MenuState::MAIN_MENU: {
                showMainMenu();
                int choice;
                std::cin >> choice;

                switch (choice) {
                    case 1:
                        currentState = MenuState::MANAGE_MENU;
                        break;
                    case 2:
                        currentState = MenuState::MONTHLY;
                        break;
                    case 3:
                        currentState = MenuState::YEARLY;
                        break;
                    case 4:
                        currentState = MenuState::EXIT;
                        break;
                    default:
                        break;
                }
                break;
            }

            case MenuState::MANAGE_MENU: {
                showManageMenu();
                int choice;
                std::cin >> choice;

                switch (choice) {
                    case 1: {
                        system("clear");
                        std::cout << "Az összes eltárolt esemény: \n" << mainStore << std::endl;
                        std::cout << "Nyomj meg bármilyen gombot a visszatéréshez...";
                        std::cin.ignore(); // dummy input 
                        std::cin.get();
                        currentState = MenuState::MAIN_MENU;
                        break;
                    }
                    case 2: {
                        handleAddEvent(mainStore);
                        std::cout << "Nyomj meg bármilyen gombot a visszatéréshez...";
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cin.get();
                        currentState = MenuState::MANAGE_MENU;
                        break;
                    }
                    case 3: {
                        std::cout << "Felvett események:\n" << mainStore << std::endl;
                        handleDelEvent(mainStore);
                        std::cout << "Nyomj meg bármilyen gombot a visszatéréshez...";
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cin.get();
                        currentState = MenuState::MANAGE_MENU;
                        break;
                    }
                    case 4: {
                        
                    }
                    case 5: {
                        currentState = MenuState::FILTER_MENU;
                        break;
                    }
                    case 6: {
                        currentState = MenuState::MAIN_MENU;
                        break;
                    }
                }
                break;
            }

            case MenuState::FILTER_MENU: {
                showFilterMenu();
                int choice;
                std::cin >> choice;
                switch (choice) {
                    case 1:
                        currentState = MenuState::MANAGE_MENU;
                        break;
                    case 2:
                        currentState = MenuState::MONTHLY;
                        break;
                    case 3:
                        currentState = MenuState::YEARLY;
                        break;
                    case 4:
                        currentState = MenuState::EXIT;
                        break;
                    default:
                        break;
                }
                break;
            }

            case MenuState::MONTHLY: {
                showMonthly(mainStore);
                std::cout << "Nyomj meg bármilyen gombot a visszatéréshez...";
                std::cin.ignore(); // dummy input 
                std::cin.get();
                currentState = MenuState::MAIN_MENU;
                system("clear");
                break;
            }

            case MenuState::YEARLY: {
                showYearly(mainStore);
                std::cout << "Nyomj meg bármilyen gombot a visszatéréshez...";
                std::cin.ignore(); // dummy input 
                std::cin.get();
                currentState = MenuState::MAIN_MENU;
                system("clear");
                break;
            }

            case MenuState::EXIT: {
                running = false;
                std::cout << "Kilépés...\n";
                break;
            }
        }
    }

    return 0;
}
