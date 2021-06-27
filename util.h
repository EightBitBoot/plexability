#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdint.h>
#include <stdbool.h>

#include <sys/inotify.h>

extern void dump_flags(bool print_binary);
extern void print_bits(uint32_t data, int num_bits);
extern void dump_event(struct inotify_event *event);

#endif
