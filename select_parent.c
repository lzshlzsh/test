#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "linux_list.h"

struct directory {
	struct list_head d_subdirs;
	struct list_head d_child;
	struct directory *d_parent;
	int d_magic;
};

#define MAX_DIRECTORIES 10

struct directory root = {
	LIST_HEAD_INIT(root.d_subdirs),
	LIST_HEAD_INIT(root.d_child),
	NULL,
	0,
};

static struct directory *new_direct(int magic)
{
	struct directory *d;

	d = malloc(sizeof(struct directory));
	assert(d);	

	INIT_LIST_HEAD(&d->d_subdirs);
	INIT_LIST_HEAD(&d->d_child);
	d->d_magic = magic;
	d->d_parent = NULL;

	return d;
}

static void construct_directories()
{
	int i, j;
	int max = MAX_DIRECTORIES;
	int nb = 0;
	struct directory *direct, *cur;

	cur = direct = &root;
	for (i = 0; i < max; i++){
		for (j = 0; j <  i / 2; j++){
			direct = new_direct(++nb);	
			list_add(&direct->d_child, &cur->d_subdirs);
			direct->d_parent = cur;
		}
		cur = direct;
	}
}

static void dump_direct()
{
	struct directory *dir, *parent;
	struct list_head *cur;

	parent = &root;
	printf("%d\n", root.d_magic);
	cur = parent->d_subdirs.next;
repeat:
	while (cur != &parent->d_subdirs){
		dir = list_entry(cur, struct directory, d_child);
		printf("%d\n", dir->d_magic);
		
		if (!list_empty(&dir->d_subdirs)){
			parent = dir;
			cur = dir->d_subdirs.next;
			printf("desending to next level %d\n", parent->d_magic);
		}else{
			cur = cur->next;
		}
	}

	if (&root != parent){
		cur = parent->d_child.next;
		parent = parent->d_parent;
		printf("asending to above level %d\n", parent->d_magic);
		goto repeat;
	}
	
}

int main()
{
	construct_directories();
	dump_direct();

	return 0;
}
