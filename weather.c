#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./lib/curl_url.h"
#include "./lib/jsmn.h"
#include "./lib/termux_output.h"
#include "./lib/get_key.h"

char url[255];

static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
  if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
      strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
    return 0;
  }
  return -1;
}

int main(void)
{
    char *apikey = get_key("OWM_APIKEY");
    snprintf(url, 254, "https://api.openweathermap.org/data/2.5/weather?lat=1.342487&lon=103.693262&mode=default&units=metric&appid=%s", apikey);

    // CURL
    char *json_out = api_call(url);

    // Parse JSON
    jsmn_parser p;
    jsmntok_t t[128]; // We expect no more than 128 JSON tokens

    jsmn_init(&p);

    int r = jsmn_parse(&p, json_out, strlen(json_out), t, sizeof(t) / sizeof(t[0]));

    if (r < 0) {
        fprintf(stderr, "Failed to parse JSON: %d\n", r);
        return EXIT_FAILURE;
    }

    char weather_desc[50];
    char temp[50];
    char feels_like[50];
    char pressure[50];
    char humidity[50];
    char wind_speed[50];
    char wind_deg[50];
    char wind_gust[50];
    char sunrise[50];
    char sunset[50];

    for (int i = 0; i < r; i++) {
        if (jsoneq(json_out, &t[i], "description") == 0) {
            snprintf(weather_desc, 50, "%.*s", t[i + 1].end - t[i + 1].start, json_out + t[i + 1].start);
        }
        else if (jsoneq(json_out, &t[i], "temp") == 0) {
            snprintf(temp, 50, "%.*s", t[i + 1].end - t[i + 1].start, json_out + t[i + 1].start);
        }
        else if (jsoneq(json_out, &t[i], "feels_like") == 0) {
            snprintf(feels_like, 50, "%.*s", t[i + 1].end - t[i + 1].start, json_out + t[i + 1].start);
        }
        else if (jsoneq(json_out, &t[i], "pressure") == 0) {
            snprintf(pressure, 50, "%.*s", t[i + 1].end - t[i + 1].start, json_out + t[i + 1].start);
        }
        else if (jsoneq(json_out, &t[i], "humidity") == 0) {
            snprintf(humidity, 50, "%.*s", t[i + 1].end - t[i + 1].start, json_out + t[i + 1].start);
        }
        else if (jsoneq(json_out, &t[i], "speed") == 0) {
            snprintf(wind_speed, 50, "%.*s", t[i + 1].end - t[i + 1].start, json_out + t[i + 1].start);
        }
        else if (jsoneq(json_out, &t[i], "wind_deg") == 0) {
            snprintf(wind_deg, 50, "%.*s", t[i + 1].end - t[i + 1].start, json_out + t[i + 1].start);
        }
        else if (jsoneq(json_out, &t[i], "wind_gust") == 0) {
            snprintf(wind_gust, 50, "%.*s", t[i + 1].end - t[i + 1].start, json_out + t[i + 1].start);
        }
        else if (jsoneq(json_out, &t[i], "sunrise") == 0) {
            snprintf(sunrise, 50, "%.*s", t[i + 1].end - t[i + 1].start, json_out + t[i + 1].start);
        }
        else if (jsoneq(json_out, &t[i], "sunset") == 0) {
            snprintf(sunset, 50, "%.*s", t[i + 1].end - t[i + 1].start, json_out + t[i + 1].start);
        }
    }

    char output[500];
    snprintf(
        output, 
        499, 
        "Weather description: %s\n"
        "Temperature: %s C\n"
        "Feels like: %s C\n"
        "Pressure: %s hPa\n"
        "Humidity: %s%%\n"
        "Wind speed: %s m/s\n", 
        weather_desc, temp, feels_like, pressure, humidity, wind_speed
    );

    notif_print(output, "Current weather");

    return EXIT_SUCCESS;
}