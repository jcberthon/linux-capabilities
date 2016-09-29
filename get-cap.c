#include <stdlib.h>
#include <stdio.h>
#include <sys/capability.h>
#include <errno.h>
#include <limits.h>

int main(int argc, char *argv[]) {
    cap_t caps;
    char *txt_caps;
    unsigned long tmp_pid;
    pid_t pid;

    if (argc != 2) {
        fprintf(stderr, "%s <pid>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Interpret PID and make sure it is unsigned short.
    errno = 0;
    tmp_pid = strtoul(argv[1], NULL, 0);
    if ( (errno == ERANGE && tmp_pid == ULONG_MAX) ||
         (errno != 0 && tmp_pid == 0) ) {
        perror("strtoul: pid is not a number");
        exit(EXIT_FAILURE);
    }
    pid = tmp_pid % 65536;
    if (pid == 0) {
        perror("pid cannot be 0");
        exit(EXIT_FAILURE);
    }

    // Get the process capabilities
    caps = cap_get_pid(pid);
    if (caps == NULL) {
        perror("cap_get_pid: wrong pid?");
        exit(EXIT_FAILURE);
    }

    // Get the human readibale form for the capabilities
    txt_caps = cap_to_text(caps, NULL);
    if (txt_caps == NULL) {
        perror("cap_to_text: wrong value for caps");
        exit(EXIT_FAILURE);
    }

    printf("Capabilities: \"%s\"\n", txt_caps);

    if (cap_free(txt_caps) != 0 || cap_free(caps) != 0) {
        perror("cap_free failed");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
