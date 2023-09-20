#include <stdio.h>
#include <stdarg.h>
#include "utility.h"
#include "mem_manage.h"

int DebugLevel = 0;
int SyncSignal = 44;
FILE *dreplog;

UINT32 in_monitoring = 0;

ADDR32 reg_spill_addr;
ADDR32 fpsave_addr;

UINT32 iMapHist = 0;
UINT32 *aMmapHistory;

ARRAY *t_array;

void Abort_Location (const char *file_name, int  line_number ) {
    fprintf (Error_File, "%s:%-4d ", file_name, line_number);
}

void EmitMessage (const char *fmt, ... ) {
    va_list vp;
    va_start (vp, fmt);
    vfprintf (Error_File, fmt, vp );
    fflush (Error_File);
    va_end (vp);
}

void SetColor (char *color) {
    if(Error_File==stderr)
        fprintf (stderr, "\033[%sm", color);
}

void UnsetColor () {
    if(Error_File==stderr)
        fprintf (stderr, "\033[m");
}

ARRAY *ArrayNew() {
    ARRAY *a = (ARRAY *)MmAllocShMem(sizeof(ARRAY));
    
    a->ArrayBase = (ELEM_TYPE *)MmAllocShMem(ARRAY_INIT_SIZE*sizeof(ELEM_TYPE));
    a->Capcity = ARRAY_INIT_SIZE;
    a->NumOfElem = 0;

    return a;
}

void ArrayAdd(ARRAY *a, ELEM_TYPE element) {
    int i;
    ELEM_TYPE *t_base;
    if(a->NumOfElem == a->Capcity) {
        t_base = (ELEM_TYPE *)MmAllocShMem(a->Capcity*2*sizeof(ELEM_TYPE));
        for(i=0; i<a->Capcity; i++)
            t_base[i] = a->ArrayBase[i];
        a->Capcity = a->Capcity * 2;
        if(a->ArrayBase)
            MmFreeShMem((ADDR)a->ArrayBase);
        a->ArrayBase = t_base;
    }

    a->ArrayBase[a->NumOfElem++] = element;
}

void ArrayDel(ARRAY *a, ELEM_TYPE element) {
    int i, j;
    for(i=0; i<a->NumOfElem; i++)
        if(a->ArrayBase[i] == element) {
            for(j=i; j<a->NumOfElem-1; j++)
                a->ArrayBase[j] = a->ArrayBase[j+1];

            a->NumOfElem --;
        }
}

INDEX ArrayElemIndex(ARRAY *a, ELEM_TYPE element) {
    int i;
    for(i=0; i<a->NumOfElem; i++) {
        if(element == a->ArrayBase[i])
            return i;
    }
    return -1;
}

void ArraySort(ARRAY *a) {
    int i,j;
	BOOL change = TRUE;
	ELEM_TYPE t_elem;
	for(i=a->NumOfElem-1; i>0&&change; --i)	{
		change = FALSE;
		for(j=0; j<i; ++j) {
			if(a->ArrayBase[j] > a->ArrayBase[j+1])	{
				t_elem = a->ArrayBase[j];
				a->ArrayBase[j] = a->ArrayBase[j+1];
				a->ArrayBase[j+1] = t_elem;
				change = TRUE;
			}
		}
	}
}

BOOL ArrayExist(ARRAY *a, ELEM_TYPE element) {
    int i;
    for(i=0; i<a->NumOfElem; i++) {
        if(element == a->ArrayBase[i])
            return TRUE;
    }
    return FALSE;
}

BOOL ArraySExist(ARRAY *a, ELEM_TYPE element) {
    int low =0, high = a->NumOfElem - 1;
	int mid;
	
	while(low <= high) {
		mid = (low + high) / 2;
		if(element == a->ArrayBase[mid])
			return TRUE;
		else if(element < a->ArrayBase[mid])
			high = mid - 1;
		else
			low = mid + 1;
	}
	return FALSE;
}

void ArraySetAdd(ARRAY *a, ELEM_TYPE element) {
    int i;
    ELEM_TYPE *t_base;
    if(!ArrayExist(a, element)) {
        if(a->NumOfElem == a->Capcity){
            t_base = (ELEM_TYPE *)MmAllocShMem(a->Capcity*2*sizeof(ELEM_TYPE));
            for(i=0; i<a->Capcity; i++)
                t_base[i] = a->ArrayBase[i];
            a->Capcity = a->Capcity * 2;
            if(a->ArrayBase)
                MmFreeShMem((ADDR)a->ArrayBase);
            a->ArrayBase = t_base;
        }
        a->ArrayBase[a->NumOfElem++] = element;
    }
}

void ArrayAppend(ARRAY *a, ARRAY *b) {
    INT32 new_cap, i;
    ELEM_TYPE *t_base;
    
    if (a->Capcity > b->Capcity)
        new_cap = a->Capcity;
    else
        new_cap = b->Capcity;

    if (a->NumOfElem + b->NumOfElem > new_cap)
        new_cap *= 2;
    
    if(new_cap > a->Capcity) {
        t_base = (ELEM_TYPE *)MmAllocShMem(new_cap*sizeof(ELEM_TYPE));
        for(i=0; i<a->NumOfElem; i++)
            t_base[i] = a->ArrayBase[i];
        if(a->ArrayBase)
            MmFreeShMem((ADDR)a->ArrayBase);
        a->Capcity = new_cap;
        a->ArrayBase = t_base;
    }

    for (i=0; i<b->NumOfElem; ++i)
        a->ArrayBase[a->NumOfElem++] = b->ArrayBase[i];

    MmFreeShMem((ADDR)b->ArrayBase);
    MmFreeShMem((ADDR)b);
}

void ArrayFree (ARRAY *a) {
    if (a==NULL)
        return;
    MmFreeShMem ((ADDR)a->ArrayBase);
    MmFreeShMem ((ADDR)a);
}



QUEUE *QueueNew() {
    QUEUE *q = (QUEUE *)MmAllocShMem(sizeof(QUEUE));
    
    q->QueueBase = (ELEM_TYPE *)MmAllocShMem(QUEUE_INIT_SIZE*sizeof(ELEM_TYPE));
    q->Capcity = ARRAY_INIT_SIZE;
    q->NumOfElem = 0;
    q->BelowIndex = 0;
    q->FrontIndex = 0;

    q->Deleted = (ARRAY *)MmAllocShMem(sizeof(ARRAY));
    q->Deleted->ArrayBase = (ELEM_TYPE *)MmAllocShMem(ARRAY_INIT_SIZE*sizeof(ELEM_TYPE));
    q->Deleted->Capcity = ARRAY_INIT_SIZE;
    q->Deleted->NumOfElem = 0;
    
    return q;
}

BOOL QueueExist (QUEUE *q, ELEM_TYPE elem) {
    int i;
	for (i=0; i<q->NumOfElem; i++)
		if (q->QueueBase[(q->FrontIndex+i)%q->Capcity] == elem)
			return TRUE;
	return FALSE;
}

BOOL QueueExisted (QUEUE *q, ELEM_TYPE elem) {
    int i;
	for (i=0; i<q->NumOfElem; i++)
		if (q->QueueBase[(q->FrontIndex+i)%q->Capcity] == elem)
			return TRUE;

    for(i=0; i<q->Deleted->NumOfElem; i++)
        if(q->Deleted->ArrayBase[i] == elem)
            return TRUE;
	return FALSE;
}


void QueuePushFast (QUEUE *q, ELEM_TYPE elem) {
    int i, j;
    ELEM_TYPE *t_base;
    if(q->NumOfElem == q->Capcity) {
        t_base = (ELEM_TYPE *)MmAllocShMem(q->Capcity*2*sizeof(ELEM_TYPE));
        for (i=0, j=q->FrontIndex; i<q->NumOfElem; i++) {
    		if (j == q->Capcity) 
    			j = 0;
    		t_base[i] = q->QueueBase[j++]; 
    	}
    	q->Capcity = q->Capcity*2;
    	q->FrontIndex = 0;
    	q->BelowIndex = q->NumOfElem;
    	if(q->QueueBase)
    		MmFreeShMem((ADDR)q->QueueBase);
    	q->QueueBase = t_base; 
    }

	if (q->BelowIndex == q->Capcity) 
		q->BelowIndex = 0;
	q->QueueBase[q->BelowIndex++] = elem;
	q->NumOfElem++; 
}

void QueuePush (QUEUE *q, ELEM_TYPE elem) {
    int i, j;
    ELEM_TYPE *t_base;
    if(!QueueExisted(q, elem)) {
        if(q->NumOfElem == q->Capcity) {
            t_base = (ELEM_TYPE *)MmAllocShMem(q->Capcity*2*sizeof(ELEM_TYPE));
            for (i=0, j=q->FrontIndex; i<q->NumOfElem; i++) {
        		if (j == q->Capcity) 
        			j = 0;
        		t_base[i] = q->QueueBase[j++]; 
        	}
        	q->Capcity = q->Capcity*2;
        	q->FrontIndex = 0;
        	q->BelowIndex = q->NumOfElem;
        	if(q->QueueBase)
        		MmFreeShMem((ADDR)q->QueueBase);
        	q->QueueBase = t_base; 
        }

    	if (q->BelowIndex == q->Capcity) 
    		q->BelowIndex = 0;
    	q->QueueBase[q->BelowIndex++] = elem;
    	q->NumOfElem++; 
    }
}

ELEM_TYPE QueuePopFast (QUEUE *q) {
    ELEM_TYPE ret_v = q->QueueBase[q->FrontIndex];
	q->FrontIndex ++;
	if (q->FrontIndex == q->Capcity)
		q->FrontIndex = 0;
	q->NumOfElem --; 
	return ret_v;
}

ELEM_TYPE QueuePop (QUEUE *q) {
    ELEM_TYPE ret_v = q->QueueBase[q->FrontIndex];
	ArraySetAdd(q->Deleted, ret_v);
	q->FrontIndex ++;
	if (q->FrontIndex == q->Capcity)
		q->FrontIndex = 0;
	q->NumOfElem --; 
	return ret_v;
}

void QueueSort (QUEUE *q) {
    int i,j,ki,kj;
    ELEM_TYPE t_elem;
    for(i=q->FrontIndex,ki=0;ki<q->NumOfElem-1;ki++) {
        j = (i+1)==q->Capcity? 0 : i+1;
        for(kj = 0; kj < q->NumOfElem - ki - 1; kj++ ) {
            if(q->QueueBase[j] < q->QueueBase[i])
            {
                t_elem = q->QueueBase[i];
                q->QueueBase[i] = q->QueueBase[j];
                q->QueueBase[j] = t_elem;
            }
            j = (j+1)==q->Capcity ? 0 : j+1;
        }
        i = (i+1)==q->Capcity ? 0 : i+1;
    }
}

void QueueFree (QUEUE *q) {
    if (q==NULL)
        return;
    MmFreeShMem ((ADDR)q->QueueBase);
    MmFreeShMem((ADDR)q->Deleted->ArrayBase);
    MmFreeShMem((ADDR)q->Deleted);
    MmFreeShMem ((ADDR)q);
}

STACK *StackNew () {
    STACK *s = (STACK *)MmAllocShMem(sizeof(STACK));
    
    s->StackBase = (ELEM_TYPE *)MmAllocShMem(ARRAY_INIT_SIZE*sizeof(ELEM_TYPE));
    s->Capcity = STACK_INIT_SIZE;
    s->NumOfElem = 0;

    return s;
}

BOOL StackExist (STACK *s, ELEM_TYPE elem) {
    int i;
	for (i = 0; i < s->NumOfElem; i++)
		if (s->StackBase[i] == elem)
			return TRUE;
	return FALSE;
}

void StackPush (STACK *s, ELEM_TYPE elem) {
    ELEM_TYPE *t_base;
    int i;
	if (s->NumOfElem == s->Capcity) {
        t_base = (ELEM_TYPE *)MmAllocShMem(s->Capcity*2*sizeof(ELEM_TYPE));
        for(i=0; i<s->Capcity; i++)
            t_base[i] = s->StackBase[i];
        s->Capcity = s->Capcity * 2;
        if(s->StackBase)
            MmFreeShMem((ADDR)s->StackBase);
        s->StackBase = t_base;
    }

	s->StackBase[s->NumOfElem++] = elem;
}

ELEM_TYPE StackPop (STACK *s) {
    s->NumOfElem --;
    ASSERT(s->NumOfElem>=0, ("The stack is empty.\n"));
    return s->StackBase[s->NumOfElem];
}

ELEM_TYPE StackTop (STACK *s) {
    return s->StackBase[s->NumOfElem-1];
}

void StackFree (STACK *s) {
    if (s==NULL)
        return;
    MmFreeShMem ((ADDR)s->StackBase);
    MmFreeShMem ((ADDR)s);
}


