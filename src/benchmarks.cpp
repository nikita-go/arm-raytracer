#include "benchmarks.h"
#include <sys/resource.h>

// Memory
long get_memory_usage() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss; // In kilobytes on Linux, bytes on macOS
}