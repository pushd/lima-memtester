/*
 * r8p1 mali kernel module ioctl interface.
 * Namespaced with "_r8p1" to coexist with the old r3p2 header in the same TU.
 *
 * Derived from Allwinner A33's mali_utgard kernel driver headers.
 */

#ifndef MALI_IOCTL_R8P1_H
#define MALI_IOCTL_R8P1_H 1

#include <stdint.h>

/* Caller must have included <sys/ioctl.h> and <asm/ioctl.h> for _IOWR etc. */

#ifndef u32
#define u32 uint32_t
#endif

typedef uint64_t u64_r8p1;
typedef int32_t  s32_r8p1;

/* _mali_uk_functions enum (r8p1) */
enum {
    /* Core */
    R8P1_MALI_UK_OPEN                    = 0,
    R8P1_MALI_UK_CLOSE                   = 1,
    R8P1_MALI_UK_WAIT_FOR_NOTIFICATION   = 2,
    R8P1_MALI_UK_GET_API_VERSION         = 3,
    R8P1_MALI_UK_POST_NOTIFICATION       = 4,
    R8P1_MALI_UK_GET_USER_SETTING        = 5,
    R8P1_MALI_UK_GET_USER_SETTINGS       = 6,
    R8P1_MALI_UK_REQUEST_HIGH_PRIORITY   = 7,
    R8P1_MALI_UK_TIMELINE_GET_LATEST_POINT = 8,
    R8P1_MALI_UK_TIMELINE_WAIT           = 9,
    R8P1_MALI_UK_TIMELINE_CREATE_SYNC_FENCE = 10,
    R8P1_MALI_UK_SOFT_JOB_START          = 11,
    R8P1_MALI_UK_SOFT_JOB_SIGNAL         = 12,
    R8P1_MALI_UK_PENDING_SUBMIT          = 13,

    /* Memory */
    R8P1_MALI_UK_ALLOC_MEM               = 0,
    R8P1_MALI_UK_FREE_MEM                = 1,
    R8P1_MALI_UK_BIND_MEM                = 2,
    R8P1_MALI_UK_UNBIND_MEM              = 3,
    R8P1_MALI_UK_COW_MEM                 = 4,
    R8P1_MALI_UK_COW_MODIFY_RANGE        = 5,
    R8P1_MALI_UK_RESIZE_MEM              = 6,
    R8P1_MALI_UK_QUERY_MMU_PAGE_TABLE_DUMP_SIZE = 7,
    R8P1_MALI_UK_DUMP_MMU_PAGE_TABLE     = 8,
    R8P1_MALI_UK_DMA_BUF_GET_SIZE        = 9,
    R8P1_MALI_UK_MEM_WRITE_SAFE          = 10,

    /* PP/GP */
    R8P1_MALI_UK_START_JOB               = 0,
    R8P1_MALI_UK_GET_NUMBER_OF_CORES     = 1,
    R8P1_MALI_UK_GET_CORE_VERSION        = 2,
    R8P1_MALI_UK_PP_DISABLE_WB           = 3,
    R8P1_MALI_UK_PP_AND_GP_START_JOB     = 4,
    R8P1_MALI_UK_GP_SUSPEND_RESPONSE     = 3,
};

/* Subsystem numbers (same as old) */
#define R8P1_MALI_IOC_BASE           0x82
#define R8P1_MALI_IOC_CORE_BASE      (0 + R8P1_MALI_IOC_BASE)   /* 0x82 */
#define R8P1_MALI_IOC_MEMORY_BASE    (1 + R8P1_MALI_IOC_BASE)   /* 0x83 */
#define R8P1_MALI_IOC_PP_BASE        (2 + R8P1_MALI_IOC_BASE)   /* 0x84 */
#define R8P1_MALI_IOC_GP_BASE        (3 + R8P1_MALI_IOC_BASE)   /* 0x85 */

#define MALI_UK_TIMELINE_MAX 3

typedef struct {
    u32 points[MALI_UK_TIMELINE_MAX];
    s32_r8p1 sync_fd;
} _mali_uk_fence_t_r8p1;

/* Notification types (same encoding as old for PP/GP FINISHED) */
typedef enum {
    R8P1_MALI_NOTIFICATION_CORE_SHUTDOWN_IN_PROGRESS = (0 << 16) | 0x20,
    R8P1_MALI_NOTIFICATION_APPLICATION_QUIT          = (0 << 16) | 0x40,
    R8P1_MALI_NOTIFICATION_SETTINGS_CHANGED          = (0 << 16) | 0x80,
    R8P1_MALI_NOTIFICATION_SOFT_ACTIVATED            = (0 << 16) | 0x100,
    R8P1_MALI_NOTIFICATION_PP_FINISHED               = (2 << 16) | 0x10,
    R8P1_MALI_NOTIFICATION_PP_NUM_CORE_CHANGE        = (2 << 16) | 0x20,
    R8P1_MALI_NOTIFICATION_GP_FINISHED               = (3 << 16) | 0x10,
    R8P1_MALI_NOTIFICATION_GP_STALLED                = (3 << 16) | 0x20,
} _mali_uk_notification_type_r8p1;

typedef enum {
    R8P1_MALI_UK_JOB_STATUS_END_SUCCESS         = 1 << (16 + 0),
    R8P1_MALI_UK_JOB_STATUS_END_OOM             = 1 << (16 + 1),
    R8P1_MALI_UK_JOB_STATUS_END_ABORT           = 1 << (16 + 2),
    R8P1_MALI_UK_JOB_STATUS_END_TIMEOUT_SW      = 1 << (16 + 3),
    R8P1_MALI_UK_JOB_STATUS_END_HANG            = 1 << (16 + 4),
    R8P1_MALI_UK_JOB_STATUS_END_SEG_FAULT       = 1 << (16 + 5),
    R8P1_MALI_UK_JOB_STATUS_END_ILLEGAL_JOB     = 1 << (16 + 6),
    R8P1_MALI_UK_JOB_STATUS_END_UNKNOWN_ERR     = 1 << (16 + 7),
    R8P1_MALI_UK_JOB_STATUS_END_SHUTDOWN        = 1 << (16 + 8),
    R8P1_MALI_UK_JOB_STATUS_END_SYSTEM_UNUSABLE = 1 << (16 + 9),
} _mali_uk_job_status_r8p1;

/* ===== Core ===== */

/* GET_API_VERSION v1: just a u32 */
/* GET_API_VERSION_V2: struct */
typedef struct {
    u64_r8p1 ctx;
    u32 version;
    int compatible;
} _mali_uk_get_api_version_v2_s_r8p1;

/* Wait for notification */
#define R8P1_MALIGP2_NUM_REGS_FRAME 6
#define R8P1_MALI_PP_MAX_SUB_JOBS 8
#define R8P1_MALI_PP_MAX_FRAME_REGISTERS ((0x058/4)+1)
#define R8P1_MALI_PP_MAX_WB_REGISTERS ((0x02C/4)+1)
#define R8P1_MALI_DLBU_MAX_REGISTERS 4

typedef struct {
    u64_r8p1 user_job_ptr;                   /* [out] */
    _mali_uk_job_status_r8p1 status;
    u32 heap_current_addr;
    u32 perf_counter0;
    u32 perf_counter1;
    u32 pending_big_job_num;
} _mali_uk_gp_job_finished_s_r8p1;

typedef struct {
    u64_r8p1 user_job_ptr;
    _mali_uk_job_status_r8p1 status;
    u32 perf_counter0[R8P1_MALI_PP_MAX_SUB_JOBS];
    u32 perf_counter1[R8P1_MALI_PP_MAX_SUB_JOBS];
    u32 perf_counter_src0;
    u32 perf_counter_src1;
} _mali_uk_pp_job_finished_s_r8p1;

typedef struct {
    u64_r8p1 user_job_ptr;
    u32 cookie;
} _mali_uk_gp_job_suspended_s_r8p1;

typedef struct {
    u32 number_of_enabled_cores;
} _mali_uk_pp_num_cores_changed_s_r8p1;

typedef struct {
    /* Simplified: we only really use type and user_job_ptr. We match the
     * actual r8p1 layout byte-for-byte so copy_to_user from the kernel
     * lands in the right place. */
    u64_r8p1 ctx;
    _mali_uk_notification_type_r8p1 type;
    union {
        _mali_uk_gp_job_suspended_s_r8p1 gp_job_suspended;
        _mali_uk_gp_job_finished_s_r8p1  gp_job_finished;
        _mali_uk_pp_job_finished_s_r8p1  pp_job_finished;
        struct { /* settings_changed */
            int setting;
            u32 value;
        } setting_changed;
        struct { /* soft_job_activated */
            u64_r8p1 user_job;
        } soft_job_activated;
        struct { /* profiling_mem_counter */
            u32 counter_id;
            u32 key;
            int enable;
        } profiling_mem_counter;
        struct {
            u32 sampling_rate;
            int enable;
        } profiling_enable;
    } data;
} _mali_uk_wait_for_notification_s_r8p1;

/* ===== Memory ===== */

typedef struct {
    u64_r8p1 ctx;
    u32 gpu_vaddr;
    u32 vsize;
    u32 psize;
    u32 flags;
    u64_r8p1 backend_handle;
    s32_r8p1 secure_shared_fd;
} _mali_uk_alloc_mem_s_r8p1;

typedef struct {
    u64_r8p1 ctx;
    u32 gpu_vaddr;
    u32 free_pages_nr;
} _mali_uk_free_mem_s_r8p1;

#define R8P1_MALI_MEMORY_BIND_BACKEND_UMP             (1<<8)
#define R8P1_MALI_MEMORY_BIND_BACKEND_DMA_BUF         (1<<9)
#define R8P1_MALI_MEMORY_BIND_BACKEND_MALI_MEMORY     (1<<10)
#define R8P1_MALI_MEMORY_BIND_BACKEND_EXTERNAL_MEMORY (1<<11)
#define R8P1_MALI_MEMORY_BIND_BACKEND_EXT_COW         (1<<12)
#define R8P1_MALI_MEMORY_BIND_BACKEND_HAVE_ALLOCATION (1<<13)

typedef struct {
    u64_r8p1 ctx;
    u32 vaddr;
    u32 size;
    u32 flags;
    u32 padding;
    union {
        struct { u32 secure_id; u32 rights; u32 flags; } bind_ump;
        struct { u32 mem_fd; u32 rights; u32 flags; } bind_dma_buf;
        struct { u32 phys_addr; u32 rights; u32 flags; } bind_ext_memory;
    } mem_union;
} _mali_uk_bind_mem_s_r8p1;

typedef struct {
    u64_r8p1 ctx;
    u32 flags;
    u32 vaddr;
} _mali_uk_unbind_mem_s_r8p1;

/* ===== PP/GP ===== */

typedef struct {
    u64_r8p1 ctx;
    u32 number_of_total_cores;
    u32 number_of_enabled_cores;
} _mali_uk_get_pp_number_of_cores_s_r8p1;

typedef struct {
    u64_r8p1 ctx;
    u32 version;
    u32 padding;
} _mali_uk_get_pp_core_version_s_r8p1;

typedef struct {
    u64_r8p1 ctx;
    u32 number_of_cores;
} _mali_uk_get_gp_number_of_cores_s_r8p1;

typedef struct {
    u64_r8p1 ctx;
    u32 version;
} _mali_uk_get_gp_core_version_s_r8p1;

typedef struct {
    u64_r8p1 ctx;
    u64_r8p1 user_job_ptr;
    u32 priority;
    u32 frame_registers[R8P1_MALIGP2_NUM_REGS_FRAME];
    u32 perf_counter_flag;
    u32 perf_counter_src0;
    u32 perf_counter_src1;
    u32 frame_builder_id;
    u32 flush_id;
    _mali_uk_fence_t_r8p1 fence;
    u64_r8p1 timeline_point_ptr;
    u32 varying_memsize;
    u32 deferred_mem_num;
    u64_r8p1 deferred_mem_list;
} _mali_uk_gp_start_job_s_r8p1;

#define R8P1_MALI_PP_JOB_FLAG_NO_NOTIFICATION (1<<0)
#define R8P1_MALI_PP_JOB_FLAG_IS_WINDOW_SURFACE (1<<1)
#define R8P1_MALI_PP_JOB_FLAG_PROTECTED (1<<2)

typedef struct {
    u64_r8p1 ctx;
    u64_r8p1 user_job_ptr;
    u32 priority;
    u32 frame_registers[R8P1_MALI_PP_MAX_FRAME_REGISTERS];
    u32 frame_registers_addr_frame[R8P1_MALI_PP_MAX_SUB_JOBS - 1];
    u32 frame_registers_addr_stack[R8P1_MALI_PP_MAX_SUB_JOBS - 1];
    u32 wb0_registers[R8P1_MALI_PP_MAX_WB_REGISTERS];
    u32 wb1_registers[R8P1_MALI_PP_MAX_WB_REGISTERS];
    u32 wb2_registers[R8P1_MALI_PP_MAX_WB_REGISTERS];
    u32 dlbu_registers[R8P1_MALI_DLBU_MAX_REGISTERS];
    u32 num_cores;
    u32 perf_counter_flag;
    u32 perf_counter_src0;
    u32 perf_counter_src1;
    u32 frame_builder_id;
    u32 flush_id;
    u32 flags;
    u32 tilesx;
    u32 tilesy;
    u32 heatmap_mem;
    u32 num_memory_cookies;
    u64_r8p1 memory_cookies;
    _mali_uk_fence_t_r8p1 fence;
    u64_r8p1 timeline_point_ptr;
} _mali_uk_pp_start_job_s_r8p1;

/* ===== IOCTL numbers (r8p1) ===== */

#define MALI_IOC_WAIT_FOR_NOTIFICATION_R8P1 \
    _IOWR(R8P1_MALI_IOC_CORE_BASE, R8P1_MALI_UK_WAIT_FOR_NOTIFICATION, \
          _mali_uk_wait_for_notification_s_r8p1)
#define MALI_IOC_GET_API_VERSION_R8P1 \
    _IOWR(R8P1_MALI_IOC_CORE_BASE, R8P1_MALI_UK_GET_API_VERSION, u32)
#define MALI_IOC_GET_API_VERSION_V2_R8P1 \
    _IOWR(R8P1_MALI_IOC_CORE_BASE, R8P1_MALI_UK_GET_API_VERSION, \
          _mali_uk_get_api_version_v2_s_r8p1)

#define MALI_IOC_MEM_ALLOC_R8P1 \
    _IOWR(R8P1_MALI_IOC_MEMORY_BASE, R8P1_MALI_UK_ALLOC_MEM, \
          _mali_uk_alloc_mem_s_r8p1)
#define MALI_IOC_MEM_FREE_R8P1 \
    _IOWR(R8P1_MALI_IOC_MEMORY_BASE, R8P1_MALI_UK_FREE_MEM, \
          _mali_uk_free_mem_s_r8p1)
#define MALI_IOC_MEM_BIND_R8P1 \
    _IOWR(R8P1_MALI_IOC_MEMORY_BASE, R8P1_MALI_UK_BIND_MEM, \
          _mali_uk_bind_mem_s_r8p1)
#define MALI_IOC_MEM_UNBIND_R8P1 \
    _IOWR(R8P1_MALI_IOC_MEMORY_BASE, R8P1_MALI_UK_UNBIND_MEM, \
          _mali_uk_unbind_mem_s_r8p1)

#define MALI_IOC_PP_START_JOB_R8P1 \
    _IOWR(R8P1_MALI_IOC_PP_BASE, R8P1_MALI_UK_START_JOB, \
          _mali_uk_pp_start_job_s_r8p1)
#define MALI_IOC_PP_NUMBER_OF_CORES_GET_R8P1 \
    _IOR (R8P1_MALI_IOC_PP_BASE, R8P1_MALI_UK_GET_NUMBER_OF_CORES, \
          _mali_uk_get_pp_number_of_cores_s_r8p1)
#define MALI_IOC_PP_CORE_VERSION_GET_R8P1 \
    _IOR (R8P1_MALI_IOC_PP_BASE, R8P1_MALI_UK_GET_CORE_VERSION, \
          _mali_uk_get_pp_core_version_s_r8p1)

#define MALI_IOC_GP_START_JOB_R8P1 \
    _IOWR(R8P1_MALI_IOC_GP_BASE, R8P1_MALI_UK_START_JOB, \
          _mali_uk_gp_start_job_s_r8p1)
#define MALI_IOC_GP_NUMBER_OF_CORES_GET_R8P1 \
    _IOR (R8P1_MALI_IOC_GP_BASE, R8P1_MALI_UK_GET_NUMBER_OF_CORES, \
          _mali_uk_get_gp_number_of_cores_s_r8p1)
#define MALI_IOC_GP_CORE_VERSION_GET_R8P1 \
    _IOR (R8P1_MALI_IOC_GP_BASE, R8P1_MALI_UK_GET_CORE_VERSION, \
          _mali_uk_get_gp_core_version_s_r8p1)

#endif /* MALI_IOCTL_R8P1_H */
