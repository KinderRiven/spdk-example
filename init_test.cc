#include "spdk/env.h"
#include "spdk/nvme.h"
#include "spdk/stdinc.h"
#include "spdk/vmd.h"

#include <stdint.h>
#include <stdio.h>

static bool fun1(void* cb_ctx, const struct spdk_nvme_transport_id* trid,
    struct spdk_nvme_ctrlr_opts* opts)
{
    printf("function1(%s)!\n", trid->traddr);
}

static void fun2(void* cb_ctx, const struct spdk_nvme_transport_id* trid,
    struct spdk_nvme_ctrlr* ctrlr, const struct spdk_nvme_ctrlr_opts* opts)
{
    printf("function2(%s)!\n", trid->traddr);
    const struct spdk_nvme_ctrlr_data* cdata = spdk_nvme_ctrlr_get_data(ctrlr);
    printf("%d-%d-%s-%s-%s\n", cdata->vid, cdata->ssvid, data->sn, data->mn, data->fr);
    uint32_t num_ns = spdk_nvme_ctrlr_get_num_ns(ctrlr);
    printf("num namespace:%d\n", num_ns);
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