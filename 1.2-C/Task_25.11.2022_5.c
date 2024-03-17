#include <stdio.h>

int main() {
    int d, m, date;
    printf("Enter the Date to know your zodiac sign\nEnter the day and month\n");
    scanf("%d.%d", &d, &m);
    if (m == 1) {
        if (d >= 20) {
            printf("Aquarius");
        } else printf("Capricorn");
    } else if (m == 2) {
        if (d >= 19) {
            printf("Pisces");
        } else printf("Aquarius");
    } else if (m == 3) {
        if (d >= 21) {
            printf("Aquarius");
        } else printf("Aries");
    } else if (m == 4) {
        if (d >= 20) {
            printf("Taurus");
        } else printf("Aries");
    } else if (m == 5) {
        if (d >= 21) {
            printf("Gemini");
        } else printf("Aries");
    } else if (m == 6) {
        if (d >= 22) {
            printf("Cancer");
        } else printf("Gemini");
    } else if (m == 7) {
        if (d >= 23) {
            printf("Leo");
        } else printf("Cancer");
    } else if (m == 8) {
        if (d >= 23) {
            printf("Virgo");
        } else printf("Leo");
    } else if (m == 9) {
        if (d >= 23) {
            printf("Libra");
        } else printf("Virgo");
    } else if (m == 10) {
        if (d >= 23) {
            printf("Scorpio");
        } else printf("Sagittarius");
    } else if (m == 11) {
        if (d >= 23) {
            printf("Sagittarius");
        } else printf("Scorpio");
    } else if (m == 12) {
        if (d >= 22) {
            printf("Capricorn");
        } else printf("Sagittarius");
    }
    return 0;
}