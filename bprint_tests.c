#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define BPRINT_VT100
#include "bprint.h"

typedef enum {
    WHITE,
    BROWN,
    BLACK,
    RED,
    OTHER
} color;

/* dog */
typedef struct {
    char *name;
    char *race;
    color color;
} dog;

void print_dog(void *d_ptr) {
    dog *d = d_ptr;
    printf("This is dog %s, he's %s. He has %d fur", d->name, d->race, d->color);
}

/* cat */
typedef struct {
    char *name;
    int years;
    color color;
} cat;

/* TODO */
// create the printflike fcn that returns bstring for those purposes
void print_cat(void *c_ptr) {
    cat *c = c_ptr;
    printf("This is %s, he's %d years old. He has %d fur", c->name, c->years, c->color);
}

typedef struct {
    double x, y;
} point;

void print_point(point *ptr) {
    printf("(%f, %f)", ptr->x, ptr->y);
}

int main() {
    bprint_register("cat", print_cat);
    bprint_register("point", print_point);
    bprint_register("dog", print_dog);

    dog d = {
        "Leon",
        "Pomeranian",
        WHITE
    };
    cat c = {
        "Andrew",
        5,
        BROWN
    };
    cat c2 = {
        "Baltazar",
        23,
        BLACK
    };

    const int iterations = 1000;
    clock_t start_bprint = clock();
    for (int i = 0; i < iterations; i++) {
        bprintln("Point:{point};Cat:{cat};Dog{dog}", &(point) { 123.45, 43.12 }, &c2, &d);
    }
    clock_t end_bprint = clock();
    float seconds_bprint = (float)(end_bprint - start_bprint) / CLOCKS_PER_SEC;

    clock_t start_printf = clock();
    for (int i = 0; i < iterations; i++) {
        printf("Point:");
        print_point(&(point) { 123.45, 43.12 });
        printf(";Cat:");
        print_cat(&c2);
        printf(";Dog:");
        print_dog(&d);
        printf("\n");
    }
    clock_t end_printf = clock();
    float seconds_printf = (float)(end_printf - start_printf) / CLOCKS_PER_SEC;
    bprintln("seconds for printf: "bprint_red_fg"{float}"bprint_reset", seconds for bprint: "bprint_green_fg"{float}"bprint_reset"", &seconds_printf, &seconds_bprint);
    printf("%f, %f\n", seconds_printf, seconds_bprint);

    //bprintln("Point(("bprint_bold bprint_under"{cat}"bprint_reset")({cat}),({dog})): {point}SIEMANO", &c, &c2, &d, &(point) { 3.14, 2 });
    //bprintln(bprint_red_fg bprint_green_bg"Hello, "bprint_reset "World");
    return 0;
}
