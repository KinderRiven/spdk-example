# SPDK_LINK_FLAGS= -Wl,--whole-archive -Llib/dpdk -ldpdk  \
	-Llib/spdk \
	-lspdk_app_rpc -lspdk_blobfs_bdev -lspdk_jsonrpc \
	-lspdk_bdev -lspdk_conf -lspdk_log \
	-lspdk_bdev_aio -lspdk_copy -lspdk_log_rpc \
	-lspdk_bdev_delay -lspdk_copy_ioat -lspdk_lvol \
	-lspdk_bdev_error -lspdk_env_dpdk -lspdk_nbd  \
	-lspdk_bdev_ftl -lspdk_env_dpdk_rpc -lspdk_net  \
	-lspdk_bdev_gpt -lspdk_event -lspdk_notify \
	-lspdk_bdev_lvol -lspdk_event_bdev -lspdk_nvme \
	-lspdk_bdev_malloc -lspdk_event_copy -lspdk_nvmf \
	-lspdk_bdev_null -lspdk_event_iscsi -lspdk_rpc \
	-lspdk_bdev_nvme -lspdk_event_nbd -lspdk_scsi \
	-lspdk_bdev_passthru -lspdk_event_net -lspdk_sock \
	-lspdk_bdev_raid -lspdk_event_nvmf -lspdk_sock_posix \
	-lspdk_bdev_rpc -lspdk_event_scsi -lspdk_thread \
	-lspdk_bdev_split -lspdk_event_vhost -lspdk_trace \
	-lspdk_bdev_virtio  -lspdk_event_vmd -lspdk_util \
	-lspdk_bdev_zone_block  -lspdk_ftl -lspdk_ut_mock \
	-lspdk_blob -lspdk_ioat -lspdk_vhost \
	-lspdk_blob_bdev -lspdk_iscsi -lspdk_virtio \
	-lspdk_blobfs -lspdk_json -lspdk_vmd \
    -Wl,--no-whole-archive  -lpthread -lrt -lnuma -ldl -luuid -lm

SPDK_LINK_FLAGS= -Wl,--whole-archive  -Llib/dpdk -lspdk_env_dpdk  -lspdk_env_dpdk_rpc \
    -Llib/spdk -ldpdk  \
    -lspdk_json -lspdk_jsonrpc -lspdk_log_rpc  -lspdk_app_rpc  -lspdk_rpc \
    -lspdk_bdev_rpc -lspdk_bdev_null -lspdk_bdev_malloc \
    -lspdk_bdev_nvme -lspdk_bdev_zone_block \
    -lspdk_bdev \
    -lspdk_event_bdev -lspdk_event_copy -lspdk_event_net -lspdk_event_vmd -lspdk_event \
    -lspdk_thread -lspdk_sock_posix -lspdk_sock -lspdk_notify \
    -lspdk_net \
    -lspdk_nvme \
    -lspdk_ftl \
    -lspdk_log -lspdk_trace -lspdk_util -lspdk_copy -lspdk_conf \
    -lspdk_vmd \
    -Wl,--no-whole-archive  -lpthread -lrt -lnuma -ldl -luuid -lm

all:
	g++ init_test.cc -o init_test -Iinclude $(SPDK_LINK_FLAGS)