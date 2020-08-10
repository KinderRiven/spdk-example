#include "spdk/env.h"
#include "spdk/nvme.h"
#include "spdk/stdinc.h"
#include "spdk/vmd.h"

#include <stdint.h>
#include <stdio.h>

void write_callback(void* arg, const struct spdk_nvme_cpl* completion)
{
    printf("write finished!\n");
}

void do_write(struct spdk_nvme_ctrlr* ctrlr, struct spdk_nvme_ns* ns)
{
    struct spdk_nvme_qpair* qpair = spdk_nvme_ctrlr_alloc_io_qpair(ctrlr, NULL, 0);
    char* buf = (char *)spdk_nvme_ctrlr_alloc_cmb_io_buffer(ctrlr, 0x1000); // 4KB
    strcpy(buf, "hello world, hello world, hello world.\n");
    int rc = spdk_nvme_ns_cmd_write(ns, qpair, buf, 0, 1, write_callback, nullptr, 0);
    printf("%d\n", rc);
}

void do_read(struct spdk_nvme_ctrlr* ctrlr, struct spdk_nvme_ns* ns)
{
}

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
    printf("[%d-%d][%s-%s-%s]\n", cdata->vid, cdata->ssvid, cdata->sn, cdata->mn, cdata->fr);

    uint32_t num_ns = spdk_nvme_ctrlr_get_num_ns(ctrlr);
    printf("num namespace:%d\n", num_ns);

    for (int i = 1; i <= num_ns; i++) {
        struct spdk_nvme_ns* ns = spdk_nvme_ctrlr_get_ns(ctrlr, i);
        uint64_t sz = spdk_nvme_ns_get_size(ns);
        printf("[%d][Size:%lluGB]\n", i, sz / 1000000000);
        do_write(ctrlr, ns);
    }
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