#ifndef    _MACH_MACH_TIME_H_
#define    _MACH_MACH_TIME_H_

#include <mach/mach_types.h>

#include <sys/cdefs.h>

struct mach_timebase_info {
    uint32_t    numer;
    uint32_t    denom;
};

typedef struct mach_timebase_info    *mach_timebase_info_t;
typedef struct mach_timebase_info    mach_timebase_info_data_t;

__BEGIN_DECLS
#ifndef    KERNEL

kern_return_t        mach_timebase_info(
                                        mach_timebase_info_t    info);

kern_return_t        mach_wait_until(
                                     uint64_t        deadline);

#endif    /* KERNEL */

uint64_t            mach_absolute_time(void);
__END_DECLS

#endif /* _MACH_MACH_TIME_H_ */
