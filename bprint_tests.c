#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define BPRINT_VT100
#include "bprint.h"

/* dog */
typedef struct {
	char *name;
	char *race;
} dog;

void print_dog_old(void *d_ptr) {
	dog *d = d_ptr;
	printf("This is dog %s, he's %s.", d->name, d->race);
}

void print_dog(dog *d) {
	printf("This is dog %s, he's %s.", d->name, d->race);
}

/* cat */
typedef struct {
	char *name;
	int years;
} cat;

void print_cat(void *c_ptr) {
	cat *c = c_ptr;
	printf("This is %s, he's %d years old", c->name, c->years);
}

/* point */
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
	};
	cat c = {
		"Andrew",
		5,
	};
	cat c2 = {
		"Baltazar",
		23,
	};

	bprintln("{dog} My dog is cute.", &d);
	bprintln("These are my animals and my points: "bprint_bold bprint_under"{cat}, "bprint_reset"{cat}, {dog}, {point}", &c, &c2, &d, &(point) { 3.14, 2 });
	bprintln(bprint_red_fg bprint_green_bg"Hello, "bprint_reset "World");
	return 0;
}
