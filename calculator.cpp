#include "calculator.h"
#include <utility>
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

std::pair<int, int> Calculator::coordToPixel(double longitude, double latitude)
{ 
    double horizontal_delta = 32.933333, vertical_delta = 41.40, longitude_start = 64.433, longitude_end = 125.7388, latitude_start = 17.72947, latitude_end = 50.700;
    int x_pixel = (double)(longitude_end - longitude) * horizontal_delta;
    int y_pixel = (double)(latitude_end - latitude) * vertical_delta;
    std::pair<int, int> temp(x_pixel, y_pixel);
    return temp;
}


