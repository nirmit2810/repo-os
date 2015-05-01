#include "fs_func.h"
#include "fs_helper.h"
#include "fs.h"
#include "thread.h"
#include "output.h"
#include "helper.h"
#include "fs_debug.h"

bool system_initialized = FALSE;

#define system_init_check() do{if(!system_initialized){rd_reset();}}while(0)


void rd_reset(){

	prints("File system restting....");
	// Setting up Super block
	// -1 to account for the root node
	file_system.sb.sb.num_free_blocks = ALLOCATED_NUM_BLOCKS;
	file_system.sb.sb.num_free_innodes = NUM_INDEX_NODE - 1;
	
	//Clearing Bit Map
	for(int i = 0; i < NUM_BYTE_FOR_BITMAP; i++) {
		file_system.bmap.byte_maps[i] = 0;
	}

	// Setting up root node
	int error = 0;
	uint16_t dummy;
	index_node * root_node = get_and_use_next_unused_node(&dummy);
	error |= init_index_node_reg(root_node, DIRECTORY);
	if(error)
		println("Error setting up root node");

	println("Done");
	system_initialized = TRUE;

}

int go_to_target_directory(char * pathname, index_node ** target, char* buffer) {
	int position = 0;
	int flag = -3;

	index_node * directory_node = &(file_system.ins[ROOT_IN_INDEX]);

	// PARSING PATH
	flag = next_path_in_str(pathname, &position, buffer);
	while(flag != FLAG_ERROR && flag != FLAG_DONE) {
		int next_entry_index = 0;
		entry_dir * next_level = NULL;
		entry_dir * curr_entry = NULL;
		while(curr_entry = walk_along_directory_entry(directory_node, &next_entry_index)){
			if(strmatch(buffer, curr_entry->filename)){
				if(strmatch((get_index_node_at_index(curr_entry->index_node_number)->type),FILE_TYPE_DIR) == TRUE) {
					next_level = curr_entry;
					directory_node = get_index_node_at_index(next_level->index_node_number);
					break;
				}
			}
		}
		if(!next_level){
			println("Error: Incorrect Path");
			return FLAG_ERROR;
		}
		flag = next_path_in_str(pathname, &position, buffer);
	}
	*target = directory_node;
	return FLAG_SUCCESS;
}

int rd_creat(char * pathname){
	system_init_check();
	if(file_system.sb.sb.num_free_blocks == 0 || file_system.sb.sb.num_free_innodes == 0){
		println("Can't create new file. Full");
		return FLAG_ERROR;
	}
	//Going to directory
	index_node * directory_node = NULL;
	char buffer[TEMP_BUFFER_SIZE];
	int flag = go_to_target_directory(pathname, & directory_node, buffer);
	if(flag == FLAG_ERROR)
		return flag;

	if(1 && filename_in_directory(buffer, directory_node)){
		println("Error: File already exists");
		return FLAG_ERROR;
	} else {
		uint16_t new_node_index = -1;
		index_node * new_index_node = get_and_use_next_unused_node(&new_node_index);
		strcpy_b(new_index_node->type, FILE_TYPE_REG, 4);
		new_index_node->size = 0;

		entry_dir * new_entry = create_new_entry(directory_node);
		strcpy_b(new_entry->filename, buffer, DIR_FILENAME_SIZE);
		new_entry->filename[DIR_FILENAME_SIZE - 1] = '\0';
		new_entry->index_node_number = new_node_index;
	}
}

int rd_mkdir(char *pathname){
	system_init_check();
	if(file_system.sb.sb.num_free_blocks == 0 || file_system.sb.sb.num_free_innodes == 0){
		println("Can't create new file. Full");
		return FLAG_ERROR;
	}
	//Going to directory
	index_node * directory_node;
	char buffer[TEMP_BUFFER_SIZE];
	int flag = go_to_target_directory(pathname, & directory_node, buffer);
	if(flag == FLAG_ERROR)
		return flag;

	if(1 && filename_in_directory(buffer, directory_node)){
		println("Error: Directory already exists");
		return FLAG_ERROR;
	} else {
		uint16_t new_node_index = -1;
		index_node * new_index_node = get_and_use_next_unused_node(&new_node_index);
		strcpy_b(new_index_node->type, FILE_TYPE_DIR, 4);
		new_index_node->size = 0;

		entry_dir * new_entry = create_new_entry(directory_node);
		strcpy_b(new_entry->filename, buffer, DIR_FILENAME_SIZE);
		new_entry->filename[DIR_FILENAME_SIZE - 1] = '\0';
		new_entry->index_node_number = new_node_index;
	}
}

int rd_open(char *pathname){
	system_init_check();

}

int rd_close(int fd){
	system_init_check();

}

int rd_read(int fd, char * address, int num_bytes){
	system_init_check();

}

int rd_write(int fd, char * address, int num_bytes){
	system_init_check();

}

int rd_lseek(int fd, int offset){
	system_init_check();

}

int rd_unlink(char * pathname){
	system_init_check();

}

int rd_readdir(int fd, char * address){
	system_init_check();

}
