#include <stdio.h>
#include "scheduler.h"
#include "input.h"

static int check_timeline(const Timeline *t, const int *pids, const int *starts,
                          const int *ends, size_t n)
{
    if (t->count != n) return 0;
    for (size_t i = 0; i < n; ++i) {
        if (t->segments[i].pid != pids[i] ||
            t->segments[i].start != starts[i] ||
            t->segments[i].end != ends[i]) return 0;
    }
    return 1;
}

static int test_fcfs_all_arrive_zero(void)
{
    Process p[3];
    process_init(&p[0], 1, 0, 8, 0);
    process_init(&p[1], 2, 0, 4, 0);
    process_init(&p[2], 3, 0, 2, 0);
    Timeline t; timeline_init(&t);
    int ids[] = {1,2,3}, s[] = {0,8,12}, e[] = {8,12,14};
    return fcfs_schedule(p, 3, &t) && check_timeline(&t, ids, s, e, 3);
}

static int test_fcfs_different_arrivals(void)
{
    Process p[3];
    process_init(&p[0], 1, 0, 5, 0);
    process_init(&p[1], 2, 1, 3, 0);
    process_init(&p[2], 3, 2, 2, 0);
    Timeline t; timeline_init(&t);
    int ids[] = {1,2,3}, s[] = {0,5,8}, e[] = {5,8,10};
    return fcfs_schedule(p, 3, &t) && check_timeline(&t, ids, s, e, 3);
}

static int test_fcfs_initial_idle(void)
{
    Process p[2];
    process_init(&p[0], 1, 5, 3, 0);
    process_init(&p[1], 2, 6, 2, 0);
    Timeline t; timeline_init(&t);
    int ids[] = {-1,1,2}, s[] = {0,5,8}, e[] = {5,8,10};
    return fcfs_schedule(p, 2, &t) && check_timeline(&t, ids, s, e, 3);
}

static int test_fcfs_idle_between(void)
{
    Process p[2];
    process_init(&p[0], 1, 0, 2, 0);
    process_init(&p[1], 2, 7, 3, 0);
    Timeline t; timeline_init(&t);
    int ids[] = {1,-1,2}, s[] = {0,2,7}, e[] = {2,7,10};
    return fcfs_schedule(p, 2, &t) && check_timeline(&t, ids, s, e, 3);
}

static int test_srtf_preemption(void)
{
    Process p[4];
    process_init(&p[0],1,0,8,0);
    process_init(&p[1],2,1,4,0);
    process_init(&p[2],3,2,2,0);
    process_init(&p[3],4,3,1,0);
    Timeline t; timeline_init(&t);
    int ids[] = {1,2,3,4,2,1};
    int s[] = {0,1,2,4,5,8};
    int e[] = {1,2,4,5,8,15};
    return srtf_schedule(p,4,&t) && check_timeline(&t,ids,s,e,6);
}

static int test_srtf_tie(void)
{
    Process p[3];
    process_init(&p[0],2,0,3,0);
    process_init(&p[1],1,0,3,0);
    process_init(&p[2],3,0,1,0);
    Timeline t; timeline_init(&t);
    int ids[] = {3,1,2}, s[] = {0,1,4}, e[] = {1,4,7};
    return srtf_schedule(p,3,&t) && check_timeline(&t,ids,s,e,3);
}

static int test_srtf_initial_idle(void)
{
    Process p[2];
    process_init(&p[0],1,5,3,0);
    process_init(&p[1],2,6,2,0);
    Timeline t; timeline_init(&t);
    int ids[] = {-1,1,2}, s[] = {0,5,8}, e[] = {5,8,10};
    return srtf_schedule(p,2,&t) && check_timeline(&t,ids,s,e,3);
}

static int test_srtf_idle_between(void)
{
    Process p[2];
    process_init(&p[0],1,0,2,0);
    process_init(&p[1],2,7,3,0);
    Timeline t; timeline_init(&t);
    int ids[] = {1,-1,2}, s[] = {0,2,7}, e[] = {2,7,10};
    return srtf_schedule(p,2,&t) && check_timeline(&t,ids,s,e,3);
}

static int test_single_process(void)
{
    Process p;
    process_init(&p,1,3,4,0);
    Timeline t; timeline_init(&t);
    int ids[] = {-1,1}, s[] = {0,3}, e[] = {3,7};
    return srtf_schedule(&p,1,&t) && check_timeline(&t,ids,s,e,2);
}

static int test_process_validation(void)
{
    Process good, bad_at, bad_bt, bad_pid, a[2];
    process_init(&good,1,0,1,0);
    process_init(&bad_at,2,-1,1,0);
    process_init(&bad_bt,3,0,0,0);
    process_init(&bad_pid,-1,0,1,0);
    process_init(&a[0],1,0,1,0);
    process_init(&a[1],1,2,1,0);
    return process_validate(&good) && !process_validate(&bad_at) &&
           !process_validate(&bad_bt) && !process_validate(&bad_pid) &&
           !processes_have_unique_pids(a,2);
}

static int test_original_data_is_preserved(void)
{
    Process p[2];
    process_init(&p[0],1,0,8,0);
    process_init(&p[1],2,1,2,0);
    Timeline t; timeline_init(&t);

    if (!srtf_schedule(p,2,&t)) return 0;
    return p[0].burst_time == 8 && p[0].remaining_time == 8 &&
           p[0].completed == 0 && p[1].burst_time == 2 &&
           p[1].remaining_time == 2 && p[1].completed == 0;
}

int main(void)
{
    int pass = 0, total = 10;
    pass += test_fcfs_all_arrive_zero();
    pass += test_fcfs_different_arrivals();
    pass += test_fcfs_initial_idle();
    pass += test_fcfs_idle_between();
    pass += test_srtf_preemption();
    pass += test_srtf_tie();
    pass += test_srtf_initial_idle();
    pass += test_srtf_idle_between();
    pass += test_single_process();
    pass += test_process_validation() && test_original_data_is_preserved();

    printf("Task 1 & 2 tests: %d/%d PASS\n", pass, total);
    return pass == total ? 0 : 1;
}
