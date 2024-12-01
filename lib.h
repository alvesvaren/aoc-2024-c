#pragma once

#define YEAR 2024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <curl/curl.h> // Assuming you use libcurl for HTTP requests

// Global variable to hold the input data
extern char *aoc_input;

// Function to load input for the current day
void load_aoc_input(int day);
