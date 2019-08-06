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
#include <stdio.h>
#include <sys/utsname.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	enum { MACHINE = 1<<0, NODENAME = 1<<1, RELEASE = 1<<2, SYSNAME = 1<<3,
		VERSION = 1<<4 } show = 0;

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

	int space = 0;
	if (show & SYSNAME) {
		space = printf("%s", uts.sysname);
	}

	if (show & NODENAME) {
		space = printf("%s%s", space ? " " : "", uts.nodename);
	}

	if (show & RELEASE) {
		space = printf("%s%s", space ? " " : "", uts.release);
	}

	if (show & VERSION) {
		space = printf("%s%s", space ? " " : "", uts.version);
	}

	if (show & MACHINE) {
		space = printf("%s%s", space ? " " : "", uts.machine);
	}

	putchar('\n');

	return 0;
}
