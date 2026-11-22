
#include <stdio.h>
#include <unistd.h>

int main()
{
    unsigned long user, nice, system, idle;
    unsigned long prev_total, curr_total;
    unsigned long prev_idle, curr_idle;

    FILE *fp;

    // First CPU reading
    fp = fopen("/proc/stat", "r");

    if (fp == NULL)
    {
        printf("File opening failed\n");
        return 1;
    }

    fscanf(fp, "cpu %lu %lu %lu %lu",
           &user, &nice, &system, &idle);

    prev_total = user + nice + system + idle;
    prev_idle = idle;

    fclose(fp);

    while (1)
    {
        sleep(1);

        // Second CPU reading
        fp = fopen("/proc/stat", "r");

        if (fp == NULL)
        {
            printf("File opening failed\n");
            return 1;
        }

        fscanf(fp, "cpu %lu %lu %lu %lu",
               &user, &nice, &system, &idle);

        curr_total = user + nice + system + idle;
        curr_idle = idle;

        fclose(fp);

        // Calculate CPU usage
        unsigned long total_diff = curr_total - prev_total;
        unsigned long idle_diff = curr_idle - prev_idle;

        if (total_diff != 0)
        {
            float cpu_usage =
                (float)(total_diff - idle_diff) / total_diff * 100;

            printf("CPU Usage: %.2f%%\n", cpu_usage);
        }

        // Update previous values
        prev_total = curr_total;
        prev_idle = curr_idle;
    }

    return 0;
}
