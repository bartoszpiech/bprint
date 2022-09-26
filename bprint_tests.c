#include <stdio.h>
#include <unistd.h>
#include <time.h>

//#define BPRINT_VT100
#include "bprint.h"
#include "bstring.h"

/* cat */
typedef struct {
    char *name;
    int years;
} cat;

/* TODO */
// create the printflike fcn that returns bstring for those purposes
void print_cat(void *c_ptr) {
    cat *c = c_ptr;
    printf("This is %s, he's %d years old.", c->name, c->years);
}

int main() {
    bprint_register("cat", print_cat);

    /*
    cat kot_andrzej = {
        "Andrew",
        5,
    };
    */

    int i = -1234;
    unsigned int ui = 123456;
    double d = 12.3456789;
    float f = 0.699;
    char c = 'X';
    char *cstr = "Ala ma kota";
    bstr b = bstr_cstr("Bartek ma psa");
    bprintln("this is an int: {int}", &i);
    bprintln("this is an unsigned int: {uint}", &ui);
    bprintln("this is a double: {double}", &d);
    bprintln("this is a float: {float}", &f);
    bprintln("this is a character: {char}", &c);
    bprintln("this is a cstr: {cstr}", &cstr);
    /* cannot return local variable from a fcn */
    //bprintln("this is a bstr: {bstr}", &(bstr)bstr_cstr("bartek ma pieska"));
    bprintln("this is a bstr: {bstr}", &b);
    bstr_print(bstr_cstr("this is a bstr using bstr_print: bartek ma pieska"));
    return 0;
}
