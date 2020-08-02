all:
	g++ init_test.cc -o init_test -Iinclude -lspdk_log -lspdk_nvme -lspdk_thread -lspdk_vmd