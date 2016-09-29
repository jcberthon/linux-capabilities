# linux-capabilities
Getting info about Linux capabilities of a process

Simply compile the .c file:

    $ gcc get-cap.c -o get-cap -lcap

_Note: you might have to install the libcap development package (`libcap-dev` or `libcap-devel` depending on your distribution)._

The executable require a process ID (aka PID) for parameter:
    $ ./get-cap 15833
    caps_to_text() returned "= cap_setgid,cap_setuid,cap_net_bind_service,cap_sys_chroot,cap_sys_time+ep"
