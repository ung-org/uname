/*
 * UNG's Not GNU
 * 
 * Copyright (c) 2011, Jakob Kaivo <jakob@kaivo.net>
 * 
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
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
