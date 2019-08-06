/*
 * UNG's Not GNU
 *
 * Copyright (c) 2011-2019, Jakob Kaivo <jkk@ung.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#define _POSIX_C_SOURCE 2
#include <locale.h>
#include <stdio.h>
#include <sys/utsname.h>
#include <unistd.h>

enum {
	MACHINE = 1<<0,
	NODENAME = 1<<1,
	RELEASE = 1<<2,
	SYSNAME = 1<<3,
	VERSION = 1<<4
};

unsigned int print(unsigned int flags, unsigned int field, const char *name)
{
	if (flags & field) {
		printf("%s", name);
		flags = flags & ~field;
		if (flags) {
			putchar(' ');
		}
	}
	return flags;
}

int main(int argc, char *argv[])
{
	setlocale(LC_ALL, "");

	unsigned int show = 0;

	int c;
	while ((c = getopt(argc, argv, "amnrsv")) != -1) {
		switch (c) {
		case 'a':
			show = MACHINE | NODENAME | RELEASE | SYSNAME | VERSION;
			break;

		case 'm':
			show |= MACHINE;
			break;

		case 'n':
			show |= NODENAME;
			break;

		case 'r':
			show |= RELEASE;
			break;

		case 's':
			show |= SYSNAME;
			break;

		case 'v':
			show |= VERSION;
			break;

		default:
			return 1;
		}
	}

	if (optind < argc) {
		fprintf(stderr, "uname: invalid operand %s\n", argv[optind]);
		return 1;
	}

	if (show == 0) {
		show = SYSNAME;
	}

	struct utsname uts;
	uname(&uts);

	show = print(show, SYSNAME, uts.sysname);
	show = print(show, NODENAME, uts.nodename);
	show = print(show, RELEASE, uts.release);
	show = print(show, VERSION, uts.version);
	show = print(show, MACHINE, uts.machine);

	putchar('\n');

	return 0;
}
