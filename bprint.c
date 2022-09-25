#include <stdio.h>
#include <stdarg.h>
#include "bstring.h"
#include "bprint.h"

typedef struct {
    char *name;
    bprinter_cb printer_cb;
} bprinter;

bprinter bprinters[BPRINTERS_SIZE] = { 0 };
size_t bprinters_size = 0;

void bprint_register_impl(char *string, bprinter_cb printer_cb) {
    bprinters[bprinters_size++] = (bprinter){ string, printer_cb };
}

void bprint(const char *format, ...) {
    bstr format_str = bstr_cstr(format);
    size_t fields = bstr_count_fields(format_str, '{', '}');
    va_list args;
    void *va_ptr;
    va_start(args, format);
    for (size_t i = 0; i < fields; i++) {
        bstr prefix = bstr_chop(&format_str, "{");
        printf(bstr_fmt, bstr_arg(prefix));
        int index = bstr_index(format_str, bstr_cstr("}"));
        bstr field_name = bstr_substr(format_str, 0, index - 1);
        int field_ind = -1;
        for (size_t hm_ind = 0; hm_ind < bprinters_size; hm_ind++) {
            if (bstr_eq(bstr_cstr(bprinters[hm_ind].name), field_name)) {
                field_ind = hm_ind;
                break;
            }
        }
        if (field_ind == -1) {
            fprintf(stderr, "Error, could not find field "bstr_fmt" in blog\n", bstr_arg(field_name));
            return;
        }
        va_ptr = va_arg(args, void *);
        bprinters[field_ind].printer_cb(va_ptr);
        format_str = bstr_sub_left(format_str, index + 1);
    }
    printf(bstr_fmt, bstr_arg(format_str));
    va_end(args);
}

void bprintln(const char *format, ...) {
    bstr format_str = bstr_cstr(format);
    size_t fields = bstr_count_fields(format_str, '{', '}');
    va_list args;
    void *va_ptr;
    va_start(args, format);
    for (size_t i = 0; i < fields; i++) {
        bstr prefix = bstr_chop(&format_str, "{");
        printf(bstr_fmt, bstr_arg(prefix));
        int index = bstr_index(format_str, bstr_cstr("}"));
        bstr field_name = bstr_substr(format_str, 0, index - 1);
        int field_ind = -1;
        for (size_t hm_ind = 0; hm_ind < bprinters_size; hm_ind++) {
            if (bstr_eq(bstr_cstr(bprinters[hm_ind].name), field_name)) {
                field_ind = hm_ind;
                break;
            }
        }
        if (field_ind == -1) {
            fprintf(stderr, "Error, could not find field "bstr_fmt" in blog\n", bstr_arg(field_name));
            return;
        }
        va_ptr = va_arg(args, void *);
        bprinters[field_ind].printer_cb(va_ptr);
        format_str = bstr_sub_left(format_str, index + 1);
    }
    bstr_print(format_str);
    va_end(args);
}
