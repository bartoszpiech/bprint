#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include "bstring.h"
#include "bprint.h"

typedef struct {
	char *name;
	bprinter_cb printer_cb;
} bprinter;

/* standard printers */
void print_int(va_list args) {
	int p = va_arg(args, int);
	printf("%d", p);
}

void print_unsigned_int(va_list args) {
	unsigned int p = va_arg(args, unsigned int);
	printf("%u", p);
}

void print_double(va_list args) {
	double p = va_arg(args, double);
	printf("%lf", p);
}

void print_float(va_list args) {
	float p = (float)va_arg(args, double);
	printf("%f", p);
}

void print_char(va_list args) {
	char p = (char)va_arg(args, int);
	printf("%c", p);
}

void print_cstr(va_list args) {
	char *p = va_arg(args, char*);
	printf("%s", p);
}

void print_bstr(va_list args) {
	bstr p = va_arg(args, bstr);
	printf(bstr_fmt, bstr_arg(p));
}

#define BPRINTERS_SIZE	7
static_assert(BPRINTERS_SIZE < BPRINTERS_MAX_SIZE, "Initial bprinters size has been maxed out, please update BPRINTERS_MAX_SIZE macro");
bprinter bprinters[BPRINTERS_MAX_SIZE] = { 
	{ "int",    print_int },
	{ "uint",   print_unsigned_int },
	{ "double", print_double },
	{ "float",  print_float },
	{ "char",   print_char },
	{ "cstr",   print_cstr },
	{ "bstr",   print_bstr },
};

size_t bprinters_size = BPRINTERS_SIZE;
void bprint_register(char *string, bprinter_cb printer_cb) {
	assert(bprinters_size < BPRINTERS_MAX_SIZE);
	bprinters[bprinters_size++] = (bprinter){ string, printer_cb };
}

/* TODO make escape sequences */
void vbprint(const char *format, va_list args) {
	bstr format_str = bstr_cstr(format);
	size_t fields = bstr_count_fields(format_str, bstr_cstr(BPRINT_OPENING), bstr_cstr(BPRINT_CLOSING));
	for (size_t i = 0; i < fields; i++) {
		bstr prefix = bstr_chop(&format_str, BPRINT_OPENING);
		bstr_print(prefix);
		int index = bstr_index(format_str, bstr_cstr(BPRINT_CLOSING));
		bstr field_name = bstr_substr(format_str, 0, index - 1);
		int field_ind = -1;
		for (size_t hm_ind = 0; hm_ind < bprinters_size; hm_ind++) {
			if (bstr_eq(bstr_cstr(bprinters[hm_ind].name), field_name)) {
				field_ind = hm_ind;
				break;
			}
		}
		if (field_ind == -1) {
			fprintf(stderr, "Error, could not find field "bstr_fmt" in bprint()\n", bstr_arg(field_name));
			return;
		}
		bprinters[field_ind].printer_cb(args);
		format_str = bstr_sub_left(format_str, index + bstr_strlen(bstr_cstr(BPRINT_CLOSING)));
	}
	printf(bstr_fmt, bstr_arg(format_str));
}

void bprint(const char *format, ...) {
	va_list args;
	va_start(args, format);
	vbprint(format, args);
	va_end(args);
}

void bprintln(const char *format, ...) {
	va_list args;
	va_start(args, format);
	vbprint(format, args);
	printf("\n");
	va_end(args);
}
