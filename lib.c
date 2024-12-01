#include "lib.h"

char *aoc_input = NULL;

static size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata) {
    size_t total_size = size * nmemb;
    FILE *file = (FILE *)userdata;
    return fwrite(ptr, size, nmemb, file);
}

void load_aoc_input(int day) {
    char output_path[64];
    struct stat st;

    if (stat("../data", &st) == -1) {
        mkdir("../data", 0700);
    }
    
    snprintf(output_path, sizeof(output_path), "./data/%d.txt", day);

    if (stat(output_path, &st) == 0) {
        // File already exists, no need to download
        FILE *output_file = fopen(output_path, "r");
        if (!output_file) {
            perror("Failed to open output file");
            exit(EXIT_FAILURE);
        }

        fseek(output_file, 0, SEEK_END);
        long filesize = ftell(output_file);
        rewind(output_file);

        aoc_input = malloc(filesize + 1);
        if (!aoc_input) {
            perror("Failed to allocate memory for input data");
            fclose(output_file);
            exit(EXIT_FAILURE);
        }

        fread(aoc_input, 1, filesize, output_file);
        aoc_input[filesize] = '\0';

        fclose(output_file);
        return;
    }
    

    // Read the session cookie from sesson.txt
    FILE *session_file = fopen("./session.txt", "r");
    if (!session_file) {
        perror("Failed to open session.txt");
        exit(EXIT_FAILURE);
    }

    char session[128];
    if (!fgets(session, sizeof(session), session_file)) {
        perror("Failed to read session cookie");
        fclose(session_file);
        exit(EXIT_FAILURE);
    }
    fclose(session_file);

    // Remove trailing newline if present
    size_t len = strlen(session);
    if (session[len - 1] == '\n') {
        session[len - 1] = '\0';
    }

    // Construct the URL
    char url[256];
    snprintf(url, sizeof(url), "https://adventofcode.com/%d/day/%d/input", YEAR, day);

    // Open the output file

    FILE *output_file = fopen(output_path, "w");
    if (!output_file) {
        perror("Failed to open output file");
        exit(EXIT_FAILURE);
    }

    // Set up libcurl
    CURL *curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Failed to initialize libcurl\n");
        fclose(output_file);
        exit(EXIT_FAILURE);
    }

    struct curl_slist *headers = NULL;
    char cookie_header[256];
    snprintf(cookie_header, sizeof(cookie_header), "Cookie: session=%s", session);
    headers = curl_slist_append(headers, cookie_header);

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, output_file);

    // Perform the request
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
        fclose(output_file);
        exit(EXIT_FAILURE);
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    fclose(output_file);

    // Load the content into the global variable
    output_file = fopen(output_path, "r");
    if (!output_file) {
        perror("Failed to reopen output file");
        exit(EXIT_FAILURE);
    }

    fseek(output_file, 0, SEEK_END);
    long filesize = ftell(output_file);
    rewind(output_file);

    aoc_input = malloc(filesize + 1);
    if (!aoc_input) {
        perror("Failed to allocate memory for input data");
        fclose(output_file);
        exit(EXIT_FAILURE);
    }

    fread(aoc_input, 1, filesize, output_file);
    aoc_input[filesize] = '\0';

    fclose(output_file);
}

