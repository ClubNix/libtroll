#include "options.h"

// Needed because RTLD_NEXT is not in the standard
#define _GNU_SOURCE

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

// Used to get to the original function
#include <dlfcn.h>

// A macro that makes a getter to the original function.
//
// Example:
//
//   If I want to "override" the `int puts(const char* string)` and I want to
//   use the original `puts` function, I cannot call it directly in the body of
//   the function, else it will just be a recursive call.
//
//   Instead, I have to somehow get the original function, which is exactly
//   what this macro does.
//
//   So, instead of writing this;
//
//   int puts(const char* string) {
//       puts("shit lol");
//       puts(string);
//   }
//
//   What you can do is:
//
//   MAKE_ORIG_GETTER(puts, int, (const char*))
//
//   int puts(const char* string) {
//       orig_puts_f_type orig_puts = get_orig_puts();
//
//       orig_puts("shit, lol");
//       orig_puts(string);
//   }
//
// The first argument of the macro is the name of the function, the second is
// the return type of the function, and the third are the argument of the
// function, wrapped in parentheses.
//
// It will define a function type: orig_{function name}_f_type
// And a getter: get_orig_{function} that takes no arguments
#define MAKE_ORIG_GETTER(name, ret_type, arguments) \
	typedef ret_type (*orig_##name##_f_type)arguments; \
	\
	orig_##name##_f_type get_orig_##name () { \
		 orig_##name##_f_type orig_##name##_f = (orig_##name##_f_type)dlsym(RTLD_NEXT, #name);\
		return orig_##name##_f;\
	}

MAKE_ORIG_GETTER(printf, int, (const char*, ...))
// TODO: there is technically no need to get the original vprintf function
// since we don't "override" it, but we might do in the future..
MAKE_ORIG_GETTER(vprintf, int, (const char*, va_list))
MAKE_ORIG_GETTER(puts, int, (const char*))

// TODO: it would be better to use the terminfo database, since there might be
// some terminals with different escape codes, but for this usecase, it's fine
// for now.
#define TTY_RESET "\e[0m"
#define TTY_BOLD "\e[1m"
#define TTY_PINK "\e[95m"

// It might break some stuff, but it's still cosmetic?
#ifdef COSMETIC_LEVEL

int printf(const char* format, ...) {
	orig_printf_f_type orig_printf = get_orig_printf();

	orig_printf(TTY_BOLD TTY_PINK);

	// forward printf arguments to vprintf since vprintf uses va_list style
	// variadic arguments
	va_list args;
	va_start(args, format);
	int ret = get_orig_vprintf()(format, args);
	va_end(args);

	// Reset because we're nice
	orig_printf(TTY_RESET);

	return ret;
}

// Sometime when the printf is called with a simple string, the compiler
// replaces printf with puts (GCC does, but not Clang)
int puts(const char* string) {
	orig_printf_f_type orig_printf = get_orig_printf();

	orig_printf(TTY_BOLD TTY_PINK);

	int ret = get_orig_puts()(string);

	// Reset because we're nice
	orig_printf(TTY_RESET);

	return ret;
}

#endif
