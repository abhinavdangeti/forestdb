#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "filemgr.h"
#include "filemgr_ops_linux.h"
#include "btreeblock.h"
#include "btree.h"
#include "btree_kv.h"
#include "test.h"

void basic_test()
{
	TEST_INIT();
	
	int ksize = 8;
	int vsize = 8;
	int nodesize = (ksize + vsize)*4 + sizeof(struct bnode);
	int blocksize = nodesize * 2;
	struct filemgr *file;
	struct btreeblk_handle btree_handle;
	struct btree btree;
	struct filemgr_config config;
	int i;
	uint64_t k,v;

	config.blocksize = blocksize;
	config.ncacheblock = 1024;
	config.flags = 0x0;
	file = filemgr_open("./dummy", get_linux_filemgr_ops(), config);
	btreeblk_init(&btree_handle, file, nodesize);

	btree_init(&btree, (void*)&btree_handle, btreeblk_get_ops(), btree_kv_get_ku64_vu64(), nodesize, ksize, vsize, 0x0, NULL);

	for (i=0;i<6;++i) {
		k = i; v = i*10;
		btree_insert(&btree, &k, &v);
	}	
	
	btree_print_node(&btree);
	//btree_operation_end(&btree);

	for (i=6;i<12;++i) {
		k = i; v = i*10;
		btree_insert(&btree, &k, &v);
	}	

	btree_print_node(&btree);
	btreeblk_end(&btree_handle);
	//btree_operation_end(&btree);

	k = 4;
	v = 44;
	btree_insert(&btree, &k, &v);
	btree_print_node(&btree);
	//btree_operation_end(&btree);
	
	btreeblk_end(&btree_handle);
	filemgr_commit(file);
	
	k = 5;
	v = 55;
	btree_insert(&btree, &k, &v);
	btree_print_node(&btree);
	//btree_operation_end(&btree);

	btreeblk_end(&btree_handle);
	filemgr_commit(file);

	k = 5;
	v = 59;
	btree_insert(&btree, &k, &v);
	btree_print_node(&btree);
	//btree_operation_end(&btree);

	btreeblk_end(&btree_handle);
	filemgr_commit(file);


	struct btree btree2;
	
	DBG("re-read using root bid %"_F64"\n", btree.root_bid);
	btree_init_from_bid(&btree2, (void*)&btree_handle, btreeblk_get_ops(), btree_kv_get_ku64_vu64(), nodesize, btree.root_bid);
	btree_print_node(&btree2);
	/*
	DBG("re-read using root bid 13\n");
	btree_init_from_bid(&btree2, (void*)&btree_handle, btreeblk_get_ops(), btree_kv_get_ku64_vu64(), nodesize, 13);
	btree_print_node(&btree2);
	*/
	TEST_RESULT("basic test");
}

void two_btree_test()
{
	TEST_INIT();

	int i;
	int nodesize = sizeof(struct bnode) + 16*4;
	int blocksize = nodesize * 4;
	struct filemgr *file;
	struct btreeblk_handle btreeblk_handle;
	struct btree btree_a, btree_b;
	struct filemgr_config config;
	uint64_t k,v;

	config.blocksize = blocksize;
	config.ncacheblock = 1024;
	file = filemgr_open("./dummy", get_linux_filemgr_ops(), config);
	btreeblk_init(&btreeblk_handle, file, nodesize);

	btree_init(&btree_a, (void*)&btreeblk_handle, btreeblk_get_ops(), btree_kv_get_ku64_vu64(), nodesize, 8, 8, 0x0, NULL);
	btree_init(&btree_b, (void*)&btreeblk_handle, btreeblk_get_ops(), btree_kv_get_ku64_vu64(), nodesize, 8, 8, 0x0, NULL);

	for (i=0;i<12;++i){
		k = i*2; v = k * 10;
		btree_insert(&btree_a, &k, &v);

		k = i*2 + 1; v = k*10 + 5;
		btree_insert(&btree_b, &k, &v);
	}

	filemgr_commit(file);

	btree_print_node(&btree_a);
	btree_print_node(&btree_b);

	TEST_RESULT("two btree test");
}


int main()
{
	int r = system("rm -rf ./dummy");
	basic_test();
	//two_btree_test();

	return 0;
}