#include "someprogram.h"
#include <iostream>
#include <string>
#include "parsing.h"

using ::parsing;

int main() {
   parsing * myParse = new parsing();
   myParse->fillVector("data/CS225 final project data.csv");
   return 0;
}

