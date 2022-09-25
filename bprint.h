#ifndef BPRINT_H
#define BPRINT_H

#define BPRINTERS_SIZE    128

/* TODO handle this */
#ifdef BPRINT_EXTRA

#define reset       "\x1b[0m"
#define bold        "\x1b[1m"
#define under       "\x1b[4m"
#define blink       "\x1b[5m"
#define reverse     "\x1b[7m"

#endif /* BPRINT_EXTRA */

typedef long unsigned int size_t;
typedef void (*bprinter_cb)(void *);

typedef struct {
    char *name;
    bprinter_cb printer_cb;
} bprinter;

void        bprint_register_impl(char *string, bprinter_cb printer_cb);
#define     bprint_register(name, printer_cb) bprint_register_impl(name, (void (*)(void *))printer_cb)
void        bprint(const char *format, ...);
void        bprintln(const char *format, ...);

#endif /* BPRINT_H */
