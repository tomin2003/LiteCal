// menu.h - menükezelő függvényeinek deklarációi - SAXHSH

#include "date.h"
#include "time.h"
#include "event.h"
#include "calendar.h"

#ifndef MENU_H
#define MENU_H

/// @brief Menüállapotokra egy felsorolt lista.
enum class MenuState {
    MAIN_MENU,
    MANAGE_MENU,
    CAL_OPS_MENU,
    MONTHLY,
    YEARLY,
    FILTER_MENU,
    EXIT
};

/// @brief Szűrés feltételeire egy felsorolt lista.
enum class FilterOpts {
    BYDATE,
    BYYEARANDMONTH,
    BYMONTHANDDAY,
    BYYEAR,
    BYMONTH,
    BYDAY
};

/// @brief Naptárműveletekre egy felsorolt lista.
enum class CalOpOpts {
    WHATDAY,
    NUMBETWEEN,
    NUMTILL,
    DAYINX
};

/// @brief A főmenü menüelemeit és a címképernyőt kiíró függvény.
void showMainMenu();

/// @brief Az eseménykezelő menüelemeit kiíró függvény.
void showManageMenu();

/// @brief A naptárműveletek menüjének menüelemeit kiíró függvény.
void showCalOpsMenu();

/// @brief A szűrés opcióit megjelenítő függvény.
void showFilterMenu();

/// @brief Havi naptárat megjelenítő függvény inputokkal.
/// @param mainStore fő eseménytároló
void showMonthly(const EventStore& mainStore);

/// @brief Éves naptárat megjelennítő függvény inputokkal.
/// @param mainStore fő eseménytároló
void showYearly(const EventStore& es);

/// @brief Esemény hozzáadásának felületet adó és azt lekezelő függvény.
/// @param mainStore fő eseménytároló
void handleAddEvent(EventStore& mainStore);

/// @brief Esemény törlésének felületet adó és azt lekezelő függvény.
/// @param mainStore fő eseménytároló
void handleDelEvent(EventStore& mainStore);

/// @brief Keresésnek felületet adó és azt lekezelő függvény.
/// @param mainStore fő eseménytároló
void handleSearch(const EventStore& mainStore);

/// @brief A naptárműveleteknek felületet adó és azokat lekezelő függvény. 
/// @param mainStore fő eseménytároló
/// @param option a kiválasztott naptárművelet
void handleCalOps(EventStore& mainStore, CalOpOpts option);

/// @brief A szűrésnek felületet adó és azt lekezelő függvény.
/// @param mainStore fő eseménytároló
/// @param option a szűrés kiválasztott módja
void handleFilter(EventStore& mainStore, FilterOpts option);

#endif