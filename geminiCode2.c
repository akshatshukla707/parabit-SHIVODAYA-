#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _TIMESPEC_DEFINED
#include <pthread.h>

// --- Original Thresholds ---
#define XRAY_THRESHOLD   2.0e-2
#define PROTON_THRESHOLD 80.0
#define WIND_THRESHOLD   800.0
#define RADIO_THRESHOLD  2000.0

// This struct is used to pass data to and from the threads
typedef struct {
    char cme_type[20];
    char full_line_data[512]; // Stores the original line for the final output
    int is_xray_dangerous;
    int is_proton_dangerous;
    int is_wind_dangerous;
    int is_radio_dangerous;
} ThreadData;

// --- Thread Functions (No changes needed here) ---

void* check_xray(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    FILE* fp = fopen("xrayflux.txt", "r");
    if (!fp) return NULL;

    char cme_typeX[20], time[30];
    double value;
    while (fscanf(fp, "%s %s %lf", cme_typeX, time, &value) == 3) {
        if (strcmp(data->cme_type, cme_typeX) == 0 && value > XRAY_THRESHOLD) {
            data->is_xray_dangerous = 1;
            break;
        }
    }
    fclose(fp);
    return NULL;
}

void* check_proton(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    FILE* fp = fopen("proton_flux_series.txt", "r");
    if (!fp) return NULL;

    char cme_typeX[20], time[30];
    double value;
    while (fscanf(fp, "%s %s %lf", cme_typeX, time, &value) == 3) {
        if (strcmp(data->cme_type, cme_typeX) == 0 && value > PROTON_THRESHOLD) {
            data->is_proton_dangerous = 1;
            break;
        }
    }
    fclose(fp);
    return NULL;
}

void* check_wind(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    FILE* fp = fopen("solar_wind_series.txt", "r");
    if (!fp) return NULL;

    char cme_typeX[20], time[30];
    double value;
    while (fscanf(fp, "%s %s %lf", cme_typeX, time, &value) == 3) {
        if (strcmp(data->cme_type, cme_typeX) == 0 && value > WIND_THRESHOLD) {
            data->is_wind_dangerous = 1;
            break;
        }
    }
    fclose(fp);
    return NULL;
}

void* check_radio(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    FILE* fp = fopen("radio_bursts_series.txt", "r");
    if (!fp) return NULL;

    char cme_typeX[20], time[30];
    double value;
    while (fscanf(fp, "%s %s %lf", cme_typeX, time, &value) == 3) {
        if (strcmp(data->cme_type, cme_typeX) == 0 && value > RADIO_THRESHOLD) {
            data->is_radio_dangerous = 1;
            break;
        }
    }
    fclose(fp);
    return NULL;
}


int main() {
    // --- Step 1: Filter initial dangerous events ---
    FILE* cme_events_in = fopen("cme_events.txt", "r");
    FILE* cme_dangerous_temp = fopen("cme_dangerous.txt", "w+");
    if (!cme_events_in || !cme_dangerous_temp) {
        perror("Error opening initial files");
        return 1;
    }

    char line_buffer[512];
    while (fgets(line_buffer, sizeof(line_buffer), cme_events_in)) {
        char cme_type[20], time[30], result[10];
        double angle, width, velocity, acc, ke;
        sscanf(line_buffer, "%s %s %lf %lf %lf %lf %lf %s", cme_type, time, &angle, &width, &velocity, &acc, &ke, result);

        if ((width > 180.0) && (velocity > 800.0) && (acc < -10.0) && (ke > (1e25))) {
            fputs(line_buffer, cme_dangerous_temp);
        }
    }
    fclose(cme_events_in);
    rewind(cme_dangerous_temp);
    printf("Step 1: Initial filtering complete.\n");

    // --- Step 2 & 3: Concurrent checking and final output ---
    FILE* final_output = fopen("final_dangerous_events.txt", "w");
    if (!final_output) {
        perror("Error opening final output file");
        return 1;
    }

    pthread_t threads[4];

    while (fgets(line_buffer, sizeof(line_buffer), cme_dangerous_temp)) {
        ThreadData data = {0}; // Initialize all fields to 0/NULL
        sscanf(line_buffer, "%s", data.cme_type);
        strcpy(data.full_line_data, line_buffer);

        printf("-> Checking CME: %s\n", data.cme_type);

        // Launch all 4 threads to check files concurrently
        pthread_create(&threads[0], NULL, check_xray, &data);
        pthread_create(&threads[1], NULL, check_proton, &data) ;
        pthread_create(&threads[2], NULL, check_wind, &data);
        pthread_create(&threads[3], NULL, check_radio, &data);

        // Wait for all 4 threads to finish
        for (int i = 0; i < 4; i++) 
        {
            pthread_join(threads[i], NULL);
        }
        
        // ** THE ONLY CHANGE IS HERE: using || (OR) instead of && (AND) **
        if (data.is_xray_dangerous || data.is_proton_dangerous || data.is_wind_dangerous || data.is_radio_dangerous)
         {
            printf("   >>> DANGEROUS EVENT FOUND: %s\n", data.cme_type);
            fputs(data.full_line_data, final_output);
        }
    }

    fclose(cme_dangerous_temp);
    fclose(final_output);
    printf("\nStep 2 & 3: Concurrent analysis complete. Results are in final_dangerous_events.txt\n");

    return 0;
}