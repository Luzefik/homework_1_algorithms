#include "mem_utils.h"
#if defined(__APPLE__)
#include <mach/mach.h>
#endif

using namespace std;

size_t getCurrentRSS() {
#if defined(__APPLE__)
    struct mach_task_basic_info info;
    mach_msg_type_number_t count = MACH_TASK_BASIC_INFO_COUNT;
    if (task_info(mach_task_self(), MACH_TASK_BASIC_INFO,
                  (task_info_t)&info, &count) != KERN_SUCCESS) {
        return 0;
    }
    return (size_t)info.resident_size;
#else
    // Запасний варіант: повертаємо 0 на платформах без реалізації
    return 0;
#endif
}
