#include <stdio.h>

#include "radix-tree.h"

#define DUMP_BEGIN printf("********************************\n")
#define DUMP_END printf("\n\n\n")

static struct radix_tree_root s_root = RADIX_TREE_INIT(0);

static void radix_tree_dump(struct radix_tree_root *root)
{
    void **slot;
    struct radix_tree_iter iter;

    DUMP_BEGIN;
    printf("root: height %d, gfp_mask %#x, rnode %p\n", 
        root->height, root->gfp_mask, root->rnode);

    radix_tree_for_each_slot(slot, &s_root, &iter, 0) {
        printf("0x%08x\n", *(int *)slot);
    }

    DUMP_END;
}
    
int main()
{
    int i;
    
    radix_tree_init();

    for (i = 0; i < 65; i++) {
        radix_tree_dump(&s_root);
        radix_tree_insert(&s_root, i, (void *)(unsigned long)((i + 1) << 1));
    }
    radix_tree_dump(&s_root);
    
    return 0;
}

