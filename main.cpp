// menu.cpp - menüvezérelt program implementációja - SAXHSH

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
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                switch (choice) {
                    case 1:
                        currentState = MenuState::MANAGE_MENU;
                        break;
                    case 2:
                        currentState = MenuState::CAL_OPS_MENU;
                        break;
                    case 3:
                        currentState = MenuState::MONTHLY;
                        break;
                    case 4:
                        currentState = MenuState::YEARLY;
                        break;
                    case 5:
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
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                switch (choice) {
                    case 1:
                        system("clear");
                        std::cout << "A foglalt események: \n" << mainStore << std::endl;
                        std::cout << "Nyomj meg bármilyen gombot a visszatéréshez...";
                        std::cin.get();
                        currentState = MenuState::MANAGE_MENU;
                        break;
                    case 2:
                        handleAddEvent(mainStore);
                        std::cout << "Nyomj meg bármilyen gombot a visszatéréshez...";
                        std::cin.get();
                        currentState = MenuState::MANAGE_MENU;
                        break;
                    case 3:
                        handleDelEvent(mainStore);
                        std::cout << "Nyomj meg bármilyen gombot a visszatéréshez...";
                        std::cin.get();
                        currentState = MenuState::MANAGE_MENU;
                        break;
                    case 4:
                        handleSearch(mainStore);
                        std::cout << "Nyomj meg bármilyen gombot a visszatéréshez...";
                        std::cin.get();
                        currentState = MenuState::MANAGE_MENU;
                        break;
                    case 5:
                        currentState = MenuState::FILTER_MENU;
                        break;
                    case 6:
                        currentState = MenuState::MAIN_MENU;
                        break;
                    default:
                        break;
                }
                break;
            }

            case MenuState::CAL_OPS_MENU: {
                showCalOpsMenu();
                CalOpOpts selOpt;
                int choice;

                std::cin >> choice;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                bool validOpt = true;

                switch (choice) {
                    case 1:
                        selOpt = CalOpOpts::WHATDAY;
                        break;
                    case 2:
                        selOpt = CalOpOpts::NUMBETWEEN;
                        break;
                    case 3:
                        selOpt = CalOpOpts::NUMTILL;
                        break;
                    case 4:
                        selOpt = CalOpOpts::DAYINX;
                        break;
                    case 5:
                        currentState = MenuState::MAIN_MENU;
                        validOpt = false;
                        break;
                    default:
                        validOpt = false;
                        break;
                }

                if (validOpt) {
                    handleCalOps(mainStore, selOpt);
                    std::cout << "Nyomj meg bármilyen gombot a visszatéréshez...";
                    std::cin.get();
                    currentState = MenuState::CAL_OPS_MENU;
                }

                system("clear");
                break;
            }

            case MenuState::FILTER_MENU: {
                showFilterMenu();
                FilterOpts selOpt;
                int choice;

                std::cin >> choice;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                bool validOpt = true;

                switch (choice) {
                    case 1:
                        selOpt = FilterOpts::BYDATE;
                        break;
                    case 2:
                        selOpt = FilterOpts::BYYEARANDMONTH;
                        break;
                    case 3:
                        selOpt = FilterOpts::BYMONTHANDDAY;
                        break;
                    case 4:
                        selOpt = FilterOpts::BYYEAR;
                        break;
                    case 5:
                        selOpt = FilterOpts::BYMONTH;
                        break;
                    case 6:
                        selOpt = FilterOpts::BYDAY;
                        break;
                    case 7:
                        currentState = MenuState::MANAGE_MENU;
                        validOpt = false;
                        break;
                    default:
                        validOpt = false;
                        break;
                }

                if (validOpt) {
                    handleFilter(mainStore, selOpt);
                    std::cout << "Nyomj meg bármilyen gombot a visszatéréshez...";
                    std::cin.get();
                    currentState = MenuState::FILTER_MENU;
                }

                system("clear");
                break;
            }

            case MenuState::MONTHLY:
                showMonthly(mainStore);
                std::cout << "Nyomj meg bármilyen gombot a visszatéréshez...";
                std::cin.get();
                currentState = MenuState::MAIN_MENU;
                system("clear");
                break;

            case MenuState::YEARLY:
                showYearly(mainStore);
                std::cout << "Nyomj meg bármilyen gombot a visszatéréshez...";
                std::cin.get();
                currentState = MenuState::MAIN_MENU;
                system("clear");
                break;

            case MenuState::EXIT:
                running = false;
                std::cout << "Kilépés...\n";
                break;
        }
    }

    return 0;
}
