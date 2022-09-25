#include <stdio.h>
#include <unistd.h>
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

void print_cat(void *c_ptr) {
    cat *c = c_ptr;
    /* TODO */
    // create the printflike fcn that returns bstring for those purposes
    printf("This is %s, he's %d years old. He has %d fur", c->name, c->years, c->color);
}

typedef struct {
    double x, y;
} point;

void print_point(point *ptr) {
    //point *p = ptr;
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
    //print_dog(&d);
    //print_cat(&c);
    //blog("Dog: {dog} And a cat: {cat}, other cat: {dog} aaa", &d, &c, &c2);
    bprintln("Point(("bprint_bold bprint_under"{cat}"bprint_reset")({cat}),({dog})): {point}SIEMANO", &c, &c2, &d, &(point) { 3.14, 2 });
    bprintln(bprint_red_fg bprint_green_bg"Hello, "bprint_reset "World");
    return 0;
}
