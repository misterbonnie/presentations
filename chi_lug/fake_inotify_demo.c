// http://lwn.net/Articles/604686/
// From Michael Kerrisk

int
main(int argc, char *argv[])
{
    struct inotify_event *event
    ...

    inotifyFd = inotify_init();         /* Create inotify instance */

    for (j = 1; j < argc; j++) {
        wd = inotify_add_watch(inotifyFd, argv[j], IN_ALL_EVENTS);

        printf("Watching %s using wd %d\n", argv[j], wd);
    }

    for (;;) {                          /* Read events forever */
        numRead = read(inotifyFd, buf, BUF_LEN);
        ...

        /* Process all of the events in buffer returned by read() */

        for (p = buf; p < buf + numRead; ) {
            event = (struct inotify_event *) p;
            displayInotifyEvent(event);

            p += sizeof(struct inotify_event) + event->len;
        }
    }
}
