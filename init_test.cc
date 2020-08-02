#include "spdk/env.h"
#include "spdk/nvme.h"
#include "spdk/stdinc.h"
#include "spdk/vmd.h"

#include <stdint.h>
#include <stdio.h>

static bool fun1(void* cb_ctx, const struct spdk_nvme_transport_id* trid,
    struct spdk_nvme_ctrlr_opts* opts)
{
    printf("function1()!\n");
}

static void fun2(void* cb_ctx, const struct spdk_nvme_transport_id* trid,
    struct spdk_nvme_ctrlr* ctrlr, const struct spdk_nvme_ctrlr_opts* opts)
{
    printf("function2()!\n");
}

int main(int argc, char** argv)
{
    int res;
    struct spdk_env_opts opts;

    printf("Hello World!\n");

    spdk_env_opts_init(&opts);

    res = spdk_env_init(&opts);
    printf("spdk_env_init() = %d\n", res);

    res = spdk_vmd_init();
    printf("spdk_vmd_init() = %d\n", res);

    res = spdk_nvme_probe(NULL, NULL, fun1, fun2, NULL);
    printf("spdk_nvme_probe() = %d\n", res);
    return 0;
}