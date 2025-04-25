// test.cpp tesztprogram, a gtest_lite segítségével teszteli az osztályok helyes viselkedését - SAXHSH
#include "gtest_lite.h"

#include "date.h"
#include "time.h"
#include "event.h"
#include "calendar.h"
#include "string.h"

#include <iostream>
#include <sstream>
#include <algorithm>

int main() {
    // JPORTA működéséhez
    GTINIT(std::cin);

    /*String osztályra vonatkozó tesztek*/

    TEST(String, CTOR) {
        // default ctor, char ctor, c-str ctor, copy ctor
        String s, s1('A'), s2("TesztTeszt"), s3(s2);
        EXPECT_EQ(0,  static_cast<int>(s.getLen())); // Az alapértelmezett sztringhossz 0?
        EXPECT_STREQ("A", s1.c_str()); // s1 tartalma tényleg "A"?
        EXPECT_EQ(static_cast<int>(strlen("TesztTeszt")), static_cast<int>(s2.getLen())); // s2 hossza annyi, mint az inputként adott c-sztringnek?
        EXPECT_STREQ("TesztTeszt", s2.c_str()); // s2 tartalma megegyezik a paraméterként adott c-sztringével?
        // jól működött a copy ctor?
        EXPECT_EQ(static_cast<int>(s3.getLen()), static_cast<int>(s2.getLen())); // A hossz egyezzen
        EXPECT_NE(s2.c_str(), s3.c_str()); // A pointer nem egyezhet
        EXPECT_STREQ(s2.c_str(), s3.c_str()); // De a tartalom igen
    } END

    TEST(String, ASSIGN) {
        String s1('A'), s2('B');
        s1 = s2;
        EXPECT_EQ(s1, s2); // megegyezik?
    } END

    TEST(String, APPEND) {
        String s1('A'), s2('B');
        String s3 = s1 + s2; // karakter hozzáfűzés
        std::cout << '\t' << s1 << " + " << s2 << " = " << s3 << std::endl;
        EXPECT_STREQ("AB", s3.c_str()); // Az összefűzés után az új sztring tartalma AB?
        s2 += s3; // sztring értékadó hozzáfűzés
        std::cout << '\t' << "B" << " += " << s3 << " = " << s2 << std::endl;
        EXPECT_STREQ("BAB", s2.c_str()); // Az értékadó összefűzés után az új sztring tartalma ABA?
    } END

    TEST(String, IDX) {
        String s1("Indexelt"); // próbasztring
        EXPECT_NO_THROW(s1[4]); // ez helyes
        EXPECT_THROW(s1[-1], std::out_of_range&); // itt kivételt várunk
        EXPECT_THROW(s1[10], std::out_of_range&); // és itt is
    } END

    TEST(String, LOGICAL) {
        String s1('A'), s2('B'), s3('B');
        EXPECT_LT(s1, s2);
        EXPECT_GT(s2, s1);
        EXPECT_EQ(s2, s3);
    } END

    TEST(String, STREAM) {
        String sout1("StreamTeszt");
        std::stringstream ss;
        ss << sout1; // streamre kiír
        EXPECT_STREQ("StreamTeszt", ss.str().c_str()); // streamen a sztring tartalma van?
        String sin1;
        ss >> sin1; // streamről beolvas
        EXPECT_STREQ("StreamTeszt", sin1.c_str()); // új sztringen a stream tartalma van?
    } END

    /*Dátum osztályra vonatkozó tesztek*/

    TEST(Date, CTOR/VALID/LEAP) {
        // default ctor, param ctor (helyes dátummal)
        Date d1, d2(2025, 04, 25);
        EXPECT_EQ(1970, d1.getYear());
        EXPECT_EQ(1, d1.getMonth());
        EXPECT_EQ(1, d1.getDay());
        EXPECT_EQ(2025, d2.getYear());
        EXPECT_EQ(4, d2.getMonth());
        EXPECT_EQ(25, d2.getDay());
        // Peremesetek ellenőrzése (legkisebb és legnagyobb dátumok)
        EXPECT_NO_THROW(Date(1970, 01, 01));
        EXPECT_NO_THROW(Date(2100, 12, 31));
        // Pár érvénytelen dátum letesztelése
        EXPECT_THROW(Date(-1200, 01, 01), invalid_date&); // érvénytelen év
        EXPECT_THROW(Date(2000, 13, 01), invalid_date&); // érvénytelen hónap
        EXPECT_THROW(Date(2000, 01, 32), invalid_date&); // érvénytelen nap
        // Szökőév teszt
        EXPECT_THROW(Date(2001, 02, 29), invalid_date&); // érvénytelen szökőév
        EXPECT_NO_THROW(Date(2000, 02, 29)); // érvényes szökőév
    } END

    TEST(Date, DAYSINMONTH) {
        Date d(2020, 01, 01); // Az év miatt kell a dátum
        EXPECT_EQ(31, d.daysInMonth(1));
        EXPECT_EQ(29, d.daysInMonth(2)); // Szökőévben 29 napos a február
        d.setYear(2021);
        EXPECT_EQ(28, d.daysInMonth(2)); // Nem szökőévben 28 napos
    } END

    TEST(Date, WEEKDAY) {
        Date d(2025, 04, 25); // péntek van/volt
        EXPECT_STREQ("Pentek", d.getWeekDay()); // péntek
        EXPECT_STRNE("Szombat", d.getWeekDay()); // nem szombat
    } END
    
    TEST(Date, DATEINDAYS) {
        Date d;
        EXPECT_EQ(0, d.dateInDays()); // Ez a kiindulópont
        Date d1(1970, 01, 10);
        EXPECT_EQ(9, d1.dateInDays());
        Date d2(1970, 12, 31);
        EXPECT_EQ(364, d2.dateInDays());
        Date d3(1971, 01, 10);
        EXPECT_EQ(374, d3.dateInDays()); // Túlcsordul?

        Date d4(2025,04,25); // egy keresés után kiderült: 20203 napot várunk
        EXPECT_EQ(20203, d4.dateInDays()); // tényleg ennyi nap?
    } END

    TEST(Date, LOGICAL) {
        Date d1(2025, 04, 20), d2(2025, 04, 25), d3(2025, 04, 25);
        // Dátum frisebb, régebbi, egyenlő-e
        EXPECT_LT(d1, d2);
        EXPECT_LE(d1, d2);
        EXPECT_LE(d2, d3);
        EXPECT_GT(d2, d1);
        EXPECT_GE(d2, d1);
        EXPECT_GE(d2, d3);
        EXPECT_EQ(d2, d3);
    } END

    TEST(Date, ADDDAY) {
        Date d1(2025, 04, 01);
        EXPECT_EQ(Date(2025,04,20), d1+19); // plusz 19 nappal 20.-a lesz
        EXPECT_EQ(Date(2025,05,11), d1+40); // plusz 40 nappal átfordul május 11-re
        EXPECT_EQ(Date(2026,01,26), d1+300); // plusz 40 nappal átfordul 2026. január 26-ra
    } END

    TEST(Date, STREAM) {
        Date dout1(2025,04,25); 
        std::stringstream ss;
        ss << dout1; // streamre kiír
        EXPECT_STREQ("2025. 04. 25.", ss.str().c_str());
        Date din1;
        ss >> din1; // streamről beolvas egy objektumba
        EXPECT_EQ(din1, dout1); // meg kell, hogy egyezzen az eredetivel
    } END

    /*Idő osztályra vonatkozó tesztek*/

    TEST(Time, CTOR/VALID) {
        // default ctor, param ctor (helyes időponttal)
        Time t1, t2(12,30);
        EXPECT_EQ(0, t1.getHour());
        EXPECT_EQ(0, t1.getMinute());
        EXPECT_EQ(12, t2.getHour());
        EXPECT_EQ(30, t2.getMinute());
        // Peremesetek ellenőrzése (legkisebb és legnagyobb időpontok)
        EXPECT_NO_THROW(Time(00,00));
        EXPECT_NO_THROW(Time(23,59));
        // Pár érvénytelen időpont letesztelése
        EXPECT_THROW(Time(-1,00), invalid_time&); // érvénytelen óra
        EXPECT_THROW(Time(24,00), invalid_time&); // érvénytelen óra
        EXPECT_THROW(Time(00,60), invalid_time&); // érvénytelen perc
        EXPECT_THROW(Time(23,-1), invalid_time&); // érvénytelen perc
    } END

    TEST(Time, LOGICAL) {
        Time t1(12,00), t2(18,30), t3(18,30);
        // Időpont frisebb, régebbi, egyenlő-e
        EXPECT_LT(t1, t2);
        EXPECT_LE(t1, t2);
        EXPECT_LE(t2, t3);
        EXPECT_GT(t2, t1);
        EXPECT_GE(t2, t1);
        EXPECT_GE(t2, t3);
        EXPECT_EQ(t2, t3);
    } END

    TEST(Time, STREAM) {
        Time tout1(16,49); 
        std::stringstream ss;
        ss << tout1; // streamre kiír
        EXPECT_STREQ("16:49", ss.str().c_str());
        Time tin1;
        ss >> tin1; // streamről beolvas egy objektumba
        EXPECT_EQ(tin1, tout1); // meg kell, hogy egyezzen az eredetivel
    } END

    /* Esemény osztályra vonatkozó tesztek */ 

    TEST(Event, CTOR) {
        // default ctor, param ctorok (helyes eseményekkel)
        Event e, e1(Date(2025,04,05), Time(12,00), String("Mai nap")), e2(2025, 04, 05, 12, 00, "Mai nap");
        // Default konstruktor
        EXPECT_EQ(1970, e.getEvDate().getYear());
        EXPECT_EQ(1, e.getEvDate().getMonth());
        EXPECT_EQ(1, e.getEvDate().getDay());
        EXPECT_EQ(0, e.getEvTime().getHour());
        EXPECT_EQ(0, e.getEvTime().getMinute());
        EXPECT_STREQ("", e.getEvDesc().c_str());
        // Paraméteres konstruktor
        EXPECT_EQ(2025, e1.getEvDate().getYear());
        EXPECT_EQ(4, e1.getEvDate().getMonth());
        EXPECT_EQ(5, e1.getEvDate().getDay());
        EXPECT_EQ(12, e1.getEvTime().getHour());
        EXPECT_EQ(0, e1.getEvTime().getMinute());
        EXPECT_STREQ("Mai nap", e1.getEvDesc().c_str());
        // Ugyanaz a tartalma a kétféle paraméteres konstruktornak?
        EXPECT_EQ(e1.getEvDate(), e2.getEvDate());
        EXPECT_EQ(e1.getEvTime(), e2.getEvTime());
        EXPECT_EQ(e1.getEvDesc(), e2.getEvDesc());
    } END

    TEST(Event, ASSIGN) {
        Event e, e1(2000,01,01,12,00, "Másik dátum");
        e = e1;
        // Minden adattagja egyezik?
        EXPECT_EQ(e.getEvDate(), e1.getEvDate());
        EXPECT_EQ(e.getEvTime(), e1.getEvTime());
        EXPECT_EQ(e.getEvDesc(), e1.getEvDesc());
    } END

    TEST(Event, LOGICAL) {
        Event e1(2025, 04, 25, 10, 00, "Mai nap délelőtt"), e2(2025, 04, 25, 14, 00, "Mai nap délután"), 
                e3(2025, 04, 24, 12, 00, "Tegnapi nap dél"), e4(2025, 04, 24, 12, 00, "Tegnapi nap dél");
        // Időpont frisebb, régebbi, egyenlő-e
        EXPECT_LT(e1, e2);
        EXPECT_GT(e1, e3);
        EXPECT_EQ(e3, e4);
    } END

    TEST(Event, STREAM) {
        Event eout1(2025,04,25,13,00, "Mai nap délután");
        std::stringstream ss;
        ss << eout1; // streamre kiírás
        EXPECT_STREQ("2025. 04. 25. 13:00 - Mai nap délután", ss.str().c_str());
        Event ein1;
        ss >> ein1; // streamről beolvasás
        EXPECT_EQ(ein1, eout1); // Meg kell, hogy egyezzen az eredetivel
    } END

    /*Eseménytárolóra vonatkozó tesztek*/

    TEST(EventStore, CTOR) {
        // teszt esemény
        Event e1(2025,04,25,12,00, "Mai nap dél");
        // default ctor, param ctor (esemény), copy ctor
        EventStore es, es1(e1), es2(es1);
        EXPECT_EQ(0, static_cast<int>(es.getNEvents())); // a default ctorral létrehozott tároló 0 elemet tartalmaz?
        EXPECT_EQ(e1, es1.getEvents()[0]); // A 0. helyre bekerült az inicializáló esemény?
        // Működött a copy ctor?
        EXPECT_EQ(static_cast<int>(es2.getNEvents()), static_cast<int>(es1.getNEvents())); 
        EXPECT_NE(es2.getEvents(), es1.getEvents()); // A pointer nem egyezhet
        EXPECT_EQ(es2.getEvents()[0], es1.getEvents()[0]); // De a tartalom igen
    } END

    TEST(EventStore, APPEND/CLASH) {
        EventStore es;
        Event e1(2000, 10, 20, 12, 00, "Esemény1");
        es + e1;
        EXPECT_EQ(1, static_cast<int>(es.getNEvents())); // Bekerült +1 esemény?
        EXPECT_EQ(e1, es.getEvents()[0]); // A 0. helyre bekerült az elsőként hozzáadott esemény?

        Event e2(2001, 10, 20, 12, 00, "Esemény2");
        es + e2;
        EXPECT_EQ(2, static_cast<int>(es.getNEvents())); // Bekerült +1 esemény?
        EXPECT_EQ(e2, es.getEvents()[1]); // Az 1. helyre bekerült az másodikként hozzáadott esemény?

        Event e3(2002, 10, 20, 12, 00, "Esemény3"), e4(2003, 10, 20, 12, 00, "Esemény4");
        es + e3 + e4; // Láncolható?
        EXPECT_EQ(4, static_cast<int>(es.getNEvents())); // Bekerült +2 esemény?
        EXPECT_EQ(e3, es.getEvents()[2]); // A 2. helyre bekerült az harmadikként hozzáadott esemény?
        EXPECT_EQ(e4, es.getEvents()[3]); // A 3. helyre bekerült az negyedikként hozzáadott esemény?

        // Ha ütköző eseményt adunk hozzá, kivételt dob
        EXPECT_THROW(es+Event(2003,10,20,12,00,"Esemény5"), evclash&);
    } END

    TEST(EventStore, FIND) {
        // teszt események
        Event e1(2025,01,22,10,00, "Esemény1");
        Event e2(2025,03,02,19,20, "Esemény2");
        Event e3(2025,02,26,01,00, "Esemény3");
        EventStore es;
        es+e1+e2+e3;
        // Ezek megtalálhatóak, ezért nem kell, hogy kivételt dobjon
        EXPECT_NO_THROW(es.find(e2));
        EXPECT_NO_THROW(es.find(Event(2025,02,26,01,00, "Esemény3")));
        // Ez nincs benne ilyen formában a tároióban, kivételt dob
        EXPECT_THROW(es.find(Event(2025,03,02,10,00, "Esemény2")), nofind&);
    } END

    TEST(EventStore, DELETE/NOFIND) {
        // Random teszt események
        Event e1(2025,01,22,10,00, "Esemény1");
        Event e2(2025,03,02,19,20, "Esemény2");
        Event e3(2025,02,26,01,00, "Esemény3");
        Event e4(2025,02,26,10,00, "Esemény4");
        EventStore es;
        es+e1+e2+e3+e4;
        size_t sizeBeforeDelete = es.getNEvents();
        es-e2;
        EXPECT_LT(static_cast<int>(es.getNEvents()), static_cast<int>(sizeBeforeDelete)); // kevesebb elem lett?
        EXPECT_THROW(es.find(e2), nofind&); // Azt várjuk, hogy nem található benne meg
        sizeBeforeDelete = es.getNEvents();

        // Láncolható?
        es-e3-e4;
        EXPECT_EQ(2, static_cast<int>(sizeBeforeDelete)-static_cast<int>(es.getNEvents())); // Kettővel kevesebb elem lett?
        // Azt várjuk, hogy nem található benne meg sem e3, sem e4
        EXPECT_THROW(es.find(e3), nofind&); 
        EXPECT_THROW(es.find(e4), nofind&); 

        // Ha nem létező eseményt törölnénk, kivételt dob
        EXPECT_THROW(es-Event(2003,10,20,12,00,"Esemény4"), nofind&);
    } END

    TEST(EventStore, SORT) {
        // Random teszt események
        Event e1(2025,01,22,10,00, "Esemény1");
        Event e2(2025,03,02,19,20, "Esemény2");
        Event e3(2025,02,26,01,00, "Esemény3");
        Event e4(2025,02,26,10,00, "Esemény4");
        Event e5(2025,06,04,9,00, "Esemény5");
        Event e6(2025,12,26,8,00, "Esemény6");
        EventStore es;
        es+e1+e2+e3+e4+e5+e6;
        EXPECT_FALSE(std::is_sorted(es.begin(), es.end()));
        es.sort();
        EXPECT_TRUE(std::is_sorted(es.begin(), es.end()));
    } END

    TEST(EventStore, STREAM) {
        EventStore es;
        Event e1(2025,01,22,10,00, "Esemény1");
        Event e2(2025,03,02,19,20, "Esemény2");
        es+e1+e2;
        std::stringstream ss;
        ss << es;
        // Kiírja helyesen a két eseményt egymás alá?
        EXPECT_STREQ("2025. 01. 22. 10:00 - Esemény1\n2025. 03. 02. 19:20 - Esemény2\n", ss.str().c_str());
    } END

    // JPORTA működéséhez
    GTEND(std::cerr);
    return 0;
}