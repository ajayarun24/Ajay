#include "calculator.h"

#include <cmath>

double Calculator::calculateDistance(double lat1, double long1, double lat2, double long2) {
    double radius = 6371; 
    double radLat1 = lat1 * M_PI / 180;
    double radLat2 = lat2 * M_PI / 180;
    double diffLat = (lat2 - lat1) * M_PI / 180;
    double diffLong = (long2 - long1) * M_PI / 180;

    double a = sin(diffLat / 2) * sin(diffLat / 2) + cos(radLat1) * cos(radLat2) * sin(diffLong / 2) * sin(diffLong / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    return (radius * c);
}


