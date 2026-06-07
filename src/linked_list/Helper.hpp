#ifndef Helper_HPP
#define Helper_HPP

#include <string>
using namespace std;


enum Field {
    RESIDENT_ID,
    AGE,
    MODE_OF_TRANSPORT,
    DAILY_DISTANCE,
    CARBON_EMISSION_FACTOR,
    AVG_DAYS_PER_MONTH
};

enum ValueType {
    INT,
    DOUBLE,
    STRING
};

struct Value {
    ValueType type;

    int iVal;
    double dVal;
    string sVal;
};

int menu();

#endif
