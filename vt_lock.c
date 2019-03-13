#include <stdarg.h>     // variable arguments number
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>     // getopt_long()
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>   // mlock()

#include <sys/ioctl.h>
#include <sys/types.h>
#include <fcntl.h>
#include <linux/vt.h>

static void
die(const char *errstr, ...) {
    va_list ap;
    va_start(ap, errstr);
    fprintf(stderr, "%s: ", PROGNAME);
    vfprintf(stderr, errstr, ap);
    va_end(ap);
    exit(EXIT_FAILURE);
}

void vt_lock() {
    /* disable tty switching */
    int term;
    if ((term = open("/dev/console", O_RDWR)) == -1) {
        fprintf(stderr, "error opening console\n");
    }

    int ioterm = ioctl(term, VT_LOCKSWITCH);
    if (ioterm == -1) {
        fprintf(stderr, "error locking console\n");
    }
}

void vt_unlock() {
    /* enable tty switching */
    int term;
    if ((term = open("/dev/console", O_RDWR)) == -1) {
        fprintf(stderr, "error opening console\n");
    }

    int ioterm = ioctl(term, VT_UNLOCKSWITCH);
    if (ioterm == -1) {
        fprintf(stderr, "error locking console\n");
    }
}


void parse_options(int argc, char** argv)
{
    static struct option opts[] = {
        { "help",           no_argument,       0, 'h' },
        { "lock",           no_argument,       0, 'u' },
        { "unlock",         no_argument,       0, 'l' },
        { "version",        no_argument,       0, 'v' },
        { 0, 0, 0, 0 },
    };

    for (;;) {
        int opt = getopt_long(argc, argv, "huvl", opts, NULL);
        if (opt == -1)
            break;

        switch (opt) {
            case 'h':
                die("usage: "PROGNAME" [-lu]\n"
                    "   -l: lock vt switching\n"
                    "   -u: unlock vt switching\n"
                );
                break;
            case 'u':
		vt_unlock();
                return;
            case 'l':
		vt_lock();
                return;
            case 'v':
                die(PROGNAME"-"VERSION", © 2019 Lomonosow\n");
                break;
            default:
                return;
        }
    }

}


int main(int argc, char** argv) {
	parse_options(argc, argv);
}
