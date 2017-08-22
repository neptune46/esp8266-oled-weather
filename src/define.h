#define DAY_NUM 3
#define MAX_STR 4

typedef struct _WeatherData {
  int code;
  int min;
  int max;
  int month;
  int day;
} WeatherData;

typedef struct _WeatherString {
  char strCode[MAX_STR];
  char strMin[MAX_STR];
  char strMax[MAX_STR];
  char strMonth[MAX_STR];
  char strDay[MAX_STR];
} WeatherString;

