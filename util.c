#include "util.h"

#include <stdio.h>

void dump_flags(bool print_binary) {
    if(print_binary) {
        // Dump flags in binary
        printf("IN_ACCES:         "); print_bits(IN_ACCESS,        32); printf("\n");
        printf("IN_ATTRIB:        "); print_bits(IN_ATTRIB,        32); printf("\n");
        printf("IN_CLOSE_WRITE:   "); print_bits(IN_CLOSE_WRITE,   32); printf("\n");
        printf("IN_CLOSE_NOWRITE: "); print_bits(IN_CLOSE_NOWRITE, 32); printf("\n");
        printf("IN_CREATE:        "); print_bits(IN_CREATE,        32); printf("\n");
        printf("IN_DELETE:        "); print_bits(IN_DELETE,        32); printf("\n");
        printf("IN_DELETE_SELF:   "); print_bits(IN_DELETE_SELF,   32); printf("\n");
        printf("IN_MODIFY:        "); print_bits(IN_MODIFY,        32); printf("\n");
        printf("IN_MOVE_SELF:     "); print_bits(IN_MOVE_SELF,     32); printf("\n");
        printf("IN_MOVED_FROM:    "); print_bits(IN_MOVED_FROM,    32); printf("\n");
        printf("IN_MOVED_TO:      "); print_bits(IN_MOVED_TO,      32); printf("\n");
        printf("IN_OPEN:          "); print_bits(IN_OPEN,          32); printf("\n");

        printf("\n");

        printf("IN_IGNORED:       "); print_bits(IN_IGNORED,       32); printf("\n");
        printf("IN_ISDIR:         "); print_bits(IN_ISDIR,         32); printf("\n");
        printf("IN_Q_OVERFLOW:    "); print_bits(IN_Q_OVERFLOW,    32); printf("\n");
        printf("IN_UNMOUNT:       "); print_bits(IN_UNMOUNT,       32); printf("\n");
    }
    else {
        // Dump flags in hex 
        printf("IN_ACCES:         0x%08X\n", IN_ACCESS);
        printf("IN_ATTRIB:        0x%08X\n", IN_ATTRIB);
        printf("IN_CLOSE_WRITE:   0x%08X\n", IN_CLOSE_WRITE);
        printf("IN_CLOSE_NOWRITE: 0x%08X\n", IN_CLOSE_NOWRITE);
        printf("IN_CREATE:        0x%08X\n", IN_CREATE);
        printf("IN_DELETE:        0x%08X\n", IN_DELETE);
        printf("IN_DELETE_SELF:   0x%08X\n", IN_DELETE_SELF);
        printf("IN_MODIFY:        0x%08X\n", IN_MODIFY);
        printf("IN_MOVE_SELF:     0x%08X\n", IN_MOVE_SELF);
        printf("IN_MOVED_FROM:    0x%08X\n", IN_MOVED_FROM);
        printf("IN_MOVED_TO:      0x%08X\n", IN_MOVED_TO);
        printf("IN_OPEN:          0x%08X\n", IN_OPEN);

        printf("\n");

        printf("IN_IGNORED:       0x%08X\n", IN_IGNORED);
        printf("IN_ISDIR:         0x%08X\n", IN_ISDIR);
        printf("IN_Q_OVERFLOW:    0x%08X\n", IN_Q_OVERFLOW);
        printf("IN_UNMOUNT:       0x%08X\n", IN_UNMOUNT);
    }
}

// Recursive component of print_bits
// Only exists so that "0b isn't printed repeatedly
void print_bits_rec(uint32_t data, int num_bits) {
    if(num_bits == 0) {
        return; 
    } 

    print_bits_rec(data >> 1, num_bits - 1);
    printf("%d", data & 0x1);
}

// Print the bits of an unsigned int
void print_bits(uint32_t data, int num_bits) {
    if(num_bits == 0) {
        return; 
    }

    printf("0b");
    print_bits_rec(data, num_bits);
}

// Print the flags in the mask of an inotify_event
void dump_mask(uint32_t mask) {
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
void dump_event(struct inotify_event *event) {
    printf("Event:\n");
    printf("    wd = %d\n", event->wd);
    printf("    mask = "); dump_mask(event->mask); printf("\n");
    printf("    cookie = %d\n", event->cookie);
    printf("    len = %u\n", event->cookie);
    printf("    name = \"%s\"\n", event->name);
}
