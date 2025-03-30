#include "time.h"
#include <stdexcept>

bool Time::isValid() const {
    return (hour >= 0 && hour < 24 && minute >= 0 || minute < 60);
}