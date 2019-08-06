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
	int c;
	int machine = 0;
	int nodename = 0;
	int release = 0;
	int sysname = 0;
	int version = 0;
	struct utsname uts;
	int space = 0;

	while ((c = getopt(argc, argv, "amnrsv")) != -1) {
		switch (c) {
		case 'a':
			machine = 1;
			nodename = 1;
			release = 1;
			sysname = 1;
			version = 1;
			break;

		case 'm':
			machine = 1;
			break;

		case 'n':
			nodename = 1;
			break;

		case 'r':
			release = 1;
			break;

		case 's':
			sysname = 1;
			break;

		case 'v':
			version = 1;
			break;

		default:
			return 1;
		}
	}

	if (optind < argc) {
		return 1;
	}

	if (machine == 0 && nodename == 0 && release == 0 && version == 0)
		sysname = 1;

	uname(&uts);

	if (sysname) {
		space = printf("%s", uts.sysname);
	}

	if (nodename) {
		space = printf("%s%s", space ? " " : "", uts.nodename);
	}

	if (release) {
		space = printf("%s%s", space ? " " : "", uts.release);
	}

	if (version) {
		space = printf("%s%s", space ? " " : "", uts.version);
	}

	if (machine) {
		space = printf("%s%s", space ? " " : "", uts.machine);
	}

	printf("\n");

	return 0;
}
