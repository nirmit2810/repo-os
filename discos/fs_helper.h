#ifndef __H_FILE_SYSTEM_HELPER__
#define __H_FILE_SYSTEM_HELPER__
#include "stdint.h"
#include "fs.h"
#include "global_t.h"

typedef enum {
	DIRECTORY,
	REGULAR
} file_type;
extern bool system_initialized;
void rd_reset();
int go_to_target_directory(char * pathname, index_node ** target, char* buffer) ;
// Paths
int next_path_in_str(const char * src, int * position, char * buffer);
index_node * get_next_index_node(index_node * curr_node, char * filename);

//Index node
index_node * get_index_node_at_index(uint16_t index);
void reset_index_node(index_node *innode);
index_node * get_and_use_next_unused_node(uint16_t * index);
int init_index_node_reg(index_node * innode, file_type ft);

//Bit mask
uint16_t get_next_available_bit();
int set_bit_map(uint16_t index);
int clear_bit_map(uint16_t index);

//Blocks
allocated_block_t * get_alloc_block_with_num(index_node * node, int num);
allocated_block_t ** get_alloc_block_ptr_with_num(index_node * node, int num);
allocated_block_t  * get_last_available_alloc_block(index_node * node);
allocated_block_t * alloc_new_block();
uint16_t index_of_allocated_block(allocated_block_t * blk);
void clear_block_content(allocated_block_t * blk);
void remove_block(allocated_block_t * blk);

//Directory
entry_dir * filename_in_directory(const char * filename, index_node * node);
entry_dir * walk_along_directory_entry(index_node * node, int * next_entry_index);
entry_dir * create_new_entry(index_node * node);
entry_dir * get_new_directory_entry(index_node * node);

void remove_entry_from_parent_directory(entry_dir * dir, index_node * node);

#define TEMP_BUFFER_SIZE 256

#endif
