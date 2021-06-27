#include <stdio.h>
#include <stdlib.h>
#include <error.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <sys/stat.h>

#include <linux/limits.h>

// Convenience macro for fprintf(stderr, ...)
#define ERROR(fmt, ...) fprintf(stderr, fmt __VA_OPT__(,) __VA_ARGS__)

// Size of the read buffer
#define BUF_SIZE (sizeof(struct inotify_event) + NAME_MAX + 1)

// Forward declerations
void printbits(uint32_t data, int numbits);
void dumpevent(struct inotify_event *event);

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

    
    /*
    printf("IN_ACCES:         "); printbits(IN_ACCESS,        32); printf("\n");
    printf("IN_ATTRIB:        "); printbits(IN_ATTRIB,        32); printf("\n");
    printf("IN_CLOSE_WRITE:   "); printbits(IN_CLOSE_WRITE,   32); printf("\n");
    printf("IN_CLOSE_NOWRITE: "); printbits(IN_CLOSE_NOWRITE, 32); printf("\n");
    printf("IN_CREATE:        "); printbits(IN_CREATE,        32); printf("\n");
    printf("IN_DELETE:        "); printbits(IN_DELETE,        32); printf("\n");
    printf("IN_DELETE_SELF:   "); printbits(IN_DELETE_SELF,   32); printf("\n");
    printf("IN_MODIFY:        "); printbits(IN_MODIFY,        32); printf("\n");
    printf("IN_MOVE_SELF:     "); printbits(IN_MOVE_SELF,     32); printf("\n");
    printf("IN_MOVED_FROM:    "); printbits(IN_MOVED_FROM,    32); printf("\n");
    printf("IN_MOVED_TO:      "); printbits(IN_MOVED_TO,      32); printf("\n");
    printf("IN_OPEN:          "); printbits(IN_OPEN,          32); printf("\n");

    printf("\n");

    printf("IN_IGNORED:       "); printbits(IN_IGNORED,       32); printf("\n");
    printf("IN_ISDIR:         "); printbits(IN_ISDIR,         32); printf("\n");
    printf("IN_Q_OVERFLOW:    "); printbits(IN_Q_OVERFLOW,    32); printf("\n");
    printf("IN_UNMOUNT:       "); printbits(IN_UNMOUNT,       32); printf("\n");
    

    printf("\n");
    */

    while(1) {
        // Read events from the inotify instance or block
        // until one occurs
        read(inotify_fd, buffer, BUF_SIZE);
        dumpevent((struct inotify_event *) buffer);
        printf("\n");

        // printf("\"%s\"\n", node_event.name);
    }

    close(inotify_fd);

    return 0;
}

// Recursive component of printbits
// Only exists so that "0b isn't printed repeatedly
void printbits_rec(uint32_t data, int numbits) {
    if(numbits == 0) {
        return; 
    } 

    printbits_rec(data >> 1, numbits - 1);
    printf("%d", data & 0x1);
}

// Print the bits of an unsigned int
void printbits(uint32_t data, int numbits) {
    if(numbits == 0) {
        return; 
    }

    printf("0b");
    printbits_rec(data, numbits);
}

// Print the flags in the mask of an inotify_event
void dumpmask(uint32_t mask) {
    if(mask & IN_ACCESS) {
        printf("IN_ACCESS"); 
        mask ^= IN_ACCESS;
        if(mask) {
            // There are move flags in the event mask so print
            // a seperator (same goes for all other if statements)
            printf(" | "); 
        }
    }
    if(mask & IN_ATTRIB) {
        printf("IN_ATTRIB"); 
        mask ^= IN_ATTRIB;
        if(mask) {
            printf(" | "); 
        }
    }
    if(mask & IN_CLOSE_WRITE) {
        printf("IN_CLOSE_WRITE"); 
        mask ^= IN_CLOSE_WRITE;
        if(mask) {
            printf(" | "); 
        }
    }
    if(mask & IN_CLOSE_NOWRITE) {
        printf("IN_CLOSE_NOWRITE"); 
        mask ^= IN_CLOSE_NOWRITE;
        if(mask) {
            printf(" | "); 
        }
    }
    if(mask & IN_CREATE) {
        printf("IN_CREATE"); 
        mask ^= IN_CREATE;
        if(mask) {
            printf(" | "); 
        }
    }
    if(mask & IN_DELETE) {
        printf("IN_DELETE"); 
        mask ^= IN_DELETE;
        if(mask) {
            printf(" | "); 
        }
    }
    if(mask & IN_DELETE_SELF) {
        printf("IN_DELETE_SELF"); 
        mask ^= IN_DELETE_SELF;
        if(mask) {
            printf(" | "); 
        }
    }
    if(mask & IN_MODIFY) {
        printf("IN_MODIFY"); 
        mask ^= IN_MODIFY;
        if(mask) {
            printf(" | "); 
        }
    }
    if(mask & IN_MOVE_SELF) {
        printf("IN_MOVE_SELF"); 
        mask ^= IN_MOVE_SELF;
        if(mask) {
            printf(" | "); 
        }
    }
    if(mask & IN_MOVED_FROM) {
        printf("IN_MOVED_FROM"); 
        mask ^= IN_MOVED_FROM;
        if(mask) {
            printf(" | "); 
        }
    }
    if(mask & IN_MOVED_TO) {
        printf("IN_MOVED_TO"); 
        mask ^= IN_MOVED_TO;
        if(mask) {
            printf(" | "); 
        }
    }
    if(mask & IN_OPEN) {
        printf("IN_OPEN"); 
        mask ^= IN_OPEN;
        if(mask) {
            printf(" | "); 
        }
    }

    if(mask & IN_IGNORED) {
        printf("IN_IGNORED"); 
        mask ^= IN_IGNORED;
        if(mask) {
            printf(" | "); 
        }
    }
    if(mask & IN_ISDIR) {
        printf("IN_ISDIR"); 
        mask ^= IN_ISDIR;
        if(mask) {
            printf(" | "); 
        }
    }
    if(mask & IN_Q_OVERFLOW) {
        printf("IN_Q_OVERFLOW"); 
        mask ^= IN_Q_OVERFLOW;
        if(mask) {
            printf(" | "); 
        }
    }
    if(mask & IN_UNMOUNT) {
        printf("IN_UNMOUNT"); 
        mask ^= IN_UNMOUNT;
        if(mask) {
            printf(" | "); 
        }
    }
}

// Dump the contents of an event
void dumpevent(struct inotify_event *event) {
    printf("Event:\n");
    printf("    wd = %d\n", event->wd);
    printf("    mask = "); dumpmask(event->mask); printf("\n");
    printf("    cookie = %d\n", event->cookie);
    printf("    len = %u\n", event->cookie);
    printf("    name = \"%s\"\n", event->name);
}
