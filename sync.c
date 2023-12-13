#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/inotify.h>

void synchronize_files(const char *source_dir, const char *destination_dir) {
    int inotify_fd = inotify_init();
    if (inotify_fd == -1) {
        perror("inotify_init");
        exit(EXIT_FAILURE);
    }

    int watch_descriptor = inotify_add_watch(inotify_fd, source_dir, IN_CLOSE_WRITE | IN_MOVED_TO);
    if (watch_descriptor == -1) {
        perror("inotify_add_watch");
        exit(EXIT_FAILURE);
    }

    printf("File synchronization started. Press Ctrl+C to exit.\n");

    while (1) {
        char buffer[1024];
        ssize_t len = read(inotify_fd, buffer, sizeof(buffer));
        if (len == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        struct inotify_event *event;
        for (char *ptr = buffer; ptr < buffer + len; ptr += sizeof(struct inotify_event) + event->len) {
            event = (struct inotify_event *)ptr;

            if (event->mask & (IN_CLOSE_WRITE | IN_MOVED_TO)) {
                // Handle file changes
                printf("File changed. Performing synchronization...\n");

                // Perform file copy (you may use system calls like fork, exec, open, read, write, etc.)
                char command[1024];
                snprintf(command, sizeof(command), "cp -r %s/* %s", source_dir, destination_dir);
                system(command);

                printf("Synchronization complete.\n");
            }
        }
    }

    // Clean up
    close(inotify_fd);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_directory> <destination_directory>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    synchronize_files(argv[1], argv[2]);

    return 0;
}
