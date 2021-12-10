#pragma once

#include <utility>


class Calculator {
    public:
        static double calculateDistance(double lat1, double long1, double lat2, double long2);
        static std::pair<int, int> coordToPixel(double longitude, double latitude);
};