#include <Finder7M.h>

#define ADDRESS 1
#define ATTEMPTS 1

Finder7M f7m;

void setup()
{
    Serial.begin(9600);
    delay(1000);

    f7m.init(38400);
    f7m.setTimeout(200);

    benchmark_single();
    benchmark_couple();
}

void loop()
{
}

void benchmark_single()
{
    int count = 50;
    int errors = 0;
    int treshold_ms = 50;
    int long_reads = 0; // reads that lasted more than treshold_ms

    uint32_t min_time = UINT32_MAX;
    uint32_t max_time = 0;

    uint32_t elapsed = 0;
    uint32_t valid_duration = 0;
    uint32_t error_duration = 0;

    uint32_t start = millis();
    for (int i = 0; i < count; i++)
    {
        uint32_t s = millis();
        Measure m = f7m.getMIDInActiveEnergy(ADDRESS, ATTEMPTS);

        uint32_t duration = millis() - s;
        min_time = min(min_time, duration);
        max_time = max(max_time, duration);
        elapsed += duration;

        if (duration > treshold_ms)
        {
            long_reads++;
        }

        if (m.isReadError())
        {
            errors++;
            error_duration += duration;
        }
        else
        {
            valid_duration += duration;
        }
    }
    int valid_reads = count - errors;

    Serial.print("benchmark for single devices at address ");
    Serial.print(ADDRESS);
    Serial.println(":");

    Serial.print("* valid reads: ");
    Serial.println(valid_reads);

    Serial.print("* errors: ");
    Serial.println(errors);

    Serial.print("* elpased time: ");
    Serial.print(elapsed);
    Serial.println("ms");

    Serial.print("* avg read time: ");
    Serial.print(elapsed / count);
    Serial.println("ms");

    Serial.print("* min read time: ");
    Serial.print(min_time);
    Serial.println("ms");

    Serial.print("* max read time: ");
    Serial.print(max_time);
    Serial.println("ms");

    Serial.print("* read time > ");
    Serial.print(treshold_ms);
    Serial.print("ms: ");
    Serial.println(long_reads);

    Serial.print("* avg valid read time: ");
    Serial.print(valid_reads > 0 ? valid_duration / valid_reads : 0);
    Serial.println("ms");

    Serial.print("* avg error read time: ");
    Serial.print(errors > 0 ? error_duration / errors : 0);
    Serial.println("ms");
}

void benchmark_couple()
{
    int count = 50;
    int errors = 0;
    int treshold_ms = 50;
    int long_reads = 0; // reads that lasted more than treshold_ms

    uint32_t min_time = UINT32_MAX;
    uint32_t max_time = 0;

    uint32_t elapsed = 0;
    uint32_t valid_duration = 0;
    uint32_t error_duration = 0;

    uint32_t start = millis();
    for (int i = 0; i < count; i++)
    {
        uint32_t s = millis();
        Measure m = f7m.getMIDInActiveEnergy(ADDRESS, ATTEMPTS);

        uint32_t duration = millis() - s;
        min_time = min(min_time, duration);
        max_time = max(max_time, duration);
        elapsed += duration;

        if (duration > treshold_ms)
        {
            long_reads++;
        }

        if (m.isReadError())
        {
            errors++;
            error_duration += duration;
        }
        else
        {
            valid_duration += duration;
        }

        s = millis();
        m = f7m.getMIDInActiveEnergy(ADDRESS + 1, ATTEMPTS);

        duration = millis() - s;
        min_time = min(min_time, duration);
        max_time = max(max_time, duration);
        elapsed += duration;

        if (duration > treshold_ms)
        {
            long_reads++;
        }

        if (m.isReadError())
        {
            errors++;
            error_duration += duration;
        }
        else
        {
            valid_duration += duration;
        }
    }
    int valid_reads = count * 2 - errors;

    Serial.print("benchmark for devices at address ");
    Serial.print(ADDRESS);
    Serial.print(" and ");
    Serial.print(ADDRESS + 1);
    Serial.println(":");

    Serial.print("* valid reads: ");
    Serial.println(valid_reads);

    Serial.print("* errors: ");
    Serial.println(errors);

    Serial.print("* elpased time: ");
    Serial.print(elapsed);
    Serial.println("ms");

    Serial.print("* avg read time: ");
    Serial.print(elapsed / (count * 2));
    Serial.println("ms");

    Serial.print("* min read time: ");
    Serial.print(min_time);
    Serial.println("ms");

    Serial.print("* max read time: ");
    Serial.print(max_time);
    Serial.println("ms");

    Serial.print("* read time > ");
    Serial.print(treshold_ms);
    Serial.print("ms: ");
    Serial.println(long_reads);

    Serial.print("* avg valid read time: ");
    Serial.print(valid_reads > 0 ? valid_duration / valid_reads : 0);
    Serial.println("ms");

    Serial.print("* avg error read time: ");
    Serial.print(errors > 0 ? error_duration / errors : 0);
    Serial.println("ms");
}
