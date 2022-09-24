#include "bstring.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

size_t bstr_count_fields(bstr string) {
    size_t result = 0;
    char ob = '{', cb = '}';
    typedef enum {
        BEFORE_OB,
        AT_OB,
        BEFORE_CB,
        AT_CB,
    } state;

    state s = BEFORE_CB;
    for (size_t i = 0; i < string.size; i++) {
        if (s == BEFORE_OB) {
            if (string.data[i] == ob) {
                s = AT_OB;
            }
        }
        if (s == AT_OB) {
            s = BEFORE_CB;
        }
        if (s == BEFORE_CB) {
            if (string.data[i] == cb) {
                s = AT_CB;
            }
        }
        if (s == AT_CB) {
            s = BEFORE_OB;
            result++;
        }
    }
    return result;
}

alloc gnu_alloc = {
    .malloc = malloc,
    .realloc = realloc,
    .free = free
};

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

void print_point(void *ptr) {
    point *p = ptr;
    printf("(%f, %f)", p->x, p->y);
}

/* logger */
typedef void (*printer_cb)(void *);

typedef struct {
    char *name;
    printer_cb printer;
} blogger;

#define BLOGGER_SIZE 16

blogger blog_hm[BLOGGER_SIZE] = { 0 };
size_t blog_hm_size = 0;

void blog_register_printer(const char *string, printer_cb printer) {
    blog_hm[blog_hm_size++] = (blogger){ (char *)string, printer };
}

void blog(const char *format, ...) {
//void blog(const char *format, void *ptr_d, void *ptr_c) {
    bstr format_str = bstr_cstr(format);
    size_t fields = bstr_count_fields(format_str);

    va_list args;
    void *va_ptr;
    va_start(args, format);

    for (size_t i = 0; i < fields; i++) {
        bstr prefix = bstr_chop(&format_str, "{");
        printf(bstr_fmt, bstr_arg(prefix));
        int index = bstr_index(format_str, bstr_cstr("}"));
        bstr field_name = bstr_substr(format_str, 0, index - 1);
        int field_ind = -1;
        for (size_t hm_ind = 0; hm_ind < blog_hm_size; hm_ind++) {
            if (bstr_eq(bstr_cstr(blog_hm[hm_ind].name), field_name)) {
                field_ind = hm_ind;
                break;
            }
        }
        if (field_ind == -1) {
            fprintf(stderr, "Error, could not find field "bstr_fmt" in blog\n", bstr_arg(field_name));
            return;
        }
        va_ptr = va_arg(args, void *);
        blog_hm[field_ind].printer(va_ptr);
        format_str = bstr_sub_left(format_str, index + 1);
    }
    bstr_print(format_str);
    va_end(args);
}


int main() {
    blog_register_printer("cat", print_cat);
    blog_register_printer("dog", print_dog);
    blog_register_printer("point", print_point);

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
    blog("Point: {point}", &(point) { 3.14, 2 });
    return 0;
}
