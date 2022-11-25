#ifndef BPRINT_H
#define BPRINT_H

/* TODO make escape sequences */

#include <stdarg.h>

/* opening and closing braces */
#define BPRINT_OPENING "{"
#define BPRINT_CLOSING "}"

#define BPRINTERS_MAX_SIZE	128

#ifdef BPRINT_VT100
/* 
 * VT-100 settings that can be used alongside bprint command, for example:
 * bprintln(bprint_bold"Hello, "bprint_reset bprint_blink"World"bprint_reset);
 */
/* standard attributes */
#define bprint_reset        "\x1b[0m"
#define bprint_bold         "\x1b[1m"
#define bprint_dim          "\x1b[2m"
#define bprint_under        "\x1b[4m"
#define bprint_blink        "\x1b[5m"
#define bprint_reverse      "\x1b[7m"
#define bprint_hidden       "\x1b[8m"
/* foreground colors */
#define bprint_black_fg     "\x1b[30m"
#define bprint_red_fg       "\x1b[31m"
#define bprint_green_fg     "\x1b[32m"
#define bprint_yellow_fg    "\x1b[33m"
#define bprint_blue_fg      "\x1b[34m"
#define bprint_magenta_fg   "\x1b[35m"
#define bprint_cyan_fg      "\x1b[36m"
#define bprint_white_fg     "\x1b[37m"
/* background colors */
#define bprint_black_bg     "\x1b[40m"
#define bprint_red_bg       "\x1b[41m"
#define bprint_green_bg     "\x1b[42m"
#define bprint_yellow_bg    "\x1b[43m"
#define bprint_blue_bg      "\x1b[44m"
#define bprint_magenta_bg   "\x1b[45m"
#define bprint_cyan_bg      "\x1b[46m"
#define bprint_white_bg     "\x1b[47m"
#endif /* BPRINT_VT100 */

#ifndef BPRINT_VT100
/* standard attributes */
#define bprint_reset        ""
#define bprint_bold         ""
#define bprint_dim          ""
#define bprint_under        ""
#define bprint_blink        ""
#define bprint_reverse      ""
#define bprint_hidden       ""
/* foreground colors */
#define bprint_black_fg     ""
#define bprint_red_fg       ""
#define bprint_green_fg     ""
#define bprint_yellow_fg    ""
#define bprint_blue_fg      ""
#define bprint_magenta_fg   ""
#define bprint_cyan_fg      ""
#define bprint_white_fg     ""
/* background colors */
#define bprint_black_bg     ""
#define bprint_red_bg       ""
#define bprint_green_bg     ""
#define bprint_yellow_bg    ""
#define bprint_blue_bg      ""
#define bprint_magenta_bg   ""
#define bprint_cyan_bg      ""
#define bprint_white_bg     ""
#endif /* BPRINT_VT100 */

typedef long unsigned int size_t;
typedef void (*bprinter_cb)(va_list args);

void        bprint_register(char *string, bprinter_cb printer_cb);
void        bprint(const char *format, ...);
void        bprintln(const char *format, ...);

#endif /* BPRINT_H */
