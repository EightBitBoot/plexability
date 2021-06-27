#include <stdio.h>
#include <stdlib.h>
#include <error.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <sys/stat.h>

#include <linux/limits.h>

#include "util.h"

// Convenience macro for fprintf(stderr, ...)
#define ERROR(fmt, ...) fprintf(stderr, fmt __VA_OPT__(,) __VA_ARGS__)

// Size of the read buffer
#define BUF_SIZE (sizeof(struct inotify_event) + NAME_MAX + 1)

int main(int argc, char **argv) {
    char *ingest_path = NULL;
    int inotify_fd = -1;
    int watch_fd = -1;
    struct stat ingest_path_stat = {0};
    uint8_t *buffer = NULL;

    if(argc < 2) {
        ERROR("Usage: plexingest <ingest-dir>\n"); 
        return 1;
    }

    ingest_path = argv[1];

    // Initalize the inoitfy instance
    inotify_fd = inotify_init(); 
    if(inotify_fd == -1) {
        perror("inotify_init"); 
        return 1;
    }
    
    printf("ingest_path: %s\n", ingest_path);

    if(stat(ingest_path, &ingest_path_stat) != 0) {
        // Stat error usually menas the supplied path doesn't exist
        perror("stat");
        close(inotify_fd);
        return 1;
    }

    if((ingest_path_stat.st_mode & S_IFMT) != S_IFDIR) {
        ERROR("Path \"%s\" is not a directory!\n", ingest_path);
        close(inotify_fd);
        return 1;
    }

    // Add a watch to the inotify instance whcih watches ingest_path
    watch_fd = inotify_add_watch(inotify_fd, ingest_path, IN_ALL_EVENTS);
    if(watch_fd == -1) {
        perror("inotify_add_watch");
        close(inotify_fd);
        return 1;
    }

    buffer = (uint8_t *) malloc(BUF_SIZE);
    if(buffer == 0) {
        perror("malloc buffer");
        close(inotify_fd);
        return 1;
    }
    
    // printf("watch_fd: %d\n", watch_fd);

    printf("\n");

    while(1) {
        // Read events from the inotify instance or block
        // until one occurs
        read(inotify_fd, buffer, BUF_SIZE);
        dump_event((struct inotify_event *) buffer);
        printf("\n");

        // printf("\"%s\"\n", node_event.name);
    }

    close(inotify_fd);

    return 0;
}

