#include <stdio.h>
#include "mem_manage.h"
#include "utility.h"
#include "optimization.h"

OUTER_LOOP  *aOutLoop;
INNER_LOOP  *aInnLoop;
REGION      *aRegion;
REM         *aRem;
REM_INS     *aRemIns;

OUTLPINDEX  nOutLp;
INNLPINDEX  nInnLp;
REGIONINDEX nRegion;
REMINDEX    nRem;
RMINSINDEX  nRemIns;

int rem_weight[REM_TYPE_NUM] = {
    0,  //REM_NONE
    0, 1,   //TRAN_DEST, TRAN_SRC
    24, 22, 20, //TRAN_SRC_D02, TRAN_SRC_D01, TRAN_SRC_D0
    16, 12, 8, 5, //TRAN_SRC_D1, TRAN_SRC_D2, TRAN_SRC_D3, TRAN_SRC_D4
    3,  //TRAN_SRC_D5
    0, 1,   //TRAN_DEST, TRAN_SRC
    24, 22, 20, //TRAN_SRC_D02, TRAN_SRC_D01, TRAN_SRC_D0
    16, 12, 8, 5, //TRAN_SRC_D1, TRAN_SRC_D2, TRAN_SRC_D3, TRAN_SRC_D4
    3,  //TRAN_SRC_D5
    0, 5,  //LOAR_DEST, LOAR_SRC,
    24, 22, 18, 14, 10,    //LOAR_SRC_D0, LOAR_SRC_D1, LOAR_SRC_D2, LOAR_SRC_D3, LOAR_SRC_D4,
    6,  //LOAR_SRC_D5
    0, 5,  //XMM_DEST, XMM_SRC,
    24, 22, 18, 14, 10, //XMM_SRC_D0, XMM_SRC_D1, XMM_SRC_D2, XMM_SRC_D3, XMM_SRC_D4
    6,  //XMM_SRC_D5
    0, 0,   //MMX_OPER, FR_OPER,
    0  //REM_MAX
};

void LoopRemInit() {
    aOutLoop = (OUTER_LOOP *)MmAllocShMem(MAXNOUTLP*sizeof(OUTER_LOOP));
    aInnLoop = (INNER_LOOP *)MmAllocShMem(MAXNINNLP*sizeof(INNER_LOOP));
    aRegion = (REGION *)MmAllocShMem(MAXNREGION*sizeof(REGION));
    aRem = (REM *)MmAllocShMem(MAXNREM*sizeof(REM));
    aRemIns = (REM_INS *)MmAllocShMem(MAXNREMINS*sizeof(REM_INS));

    nOutLp = INVALID + 1;
    nInnLp = INVALID + 1;
    nRegion = INVALID + 1;
    nRem = INVALID + 1;
    nRemIns = INVALID + 1;
}

void LoopRemFree() {
    int i;
    for(i=1; i<nRem; i++)
        ArrayFree(aRem[i]._rem_instr);
    for(i=1; i<nInnLp; i++) {
        ArrayFree(aInnLoop[i]._exit);
        ArrayFree(aInnLoop[i]._member);
    }
    for(i=1; i<nOutLp; i++) {
        ArrayFree(aOutLoop[i]._exit);
        ArrayFree(aOutLoop[i]._member);
    }
    
    MmFreeShMem((ADDR)aRemIns);
    MmFreeShMem((ADDR)aRem);
    MmFreeShMem((ADDR)aRegion);
    MmFreeShMem((ADDR)aInnLoop);
    MmFreeShMem((ADDR)aOutLoop);
}

RMINSINDEX RemInsNew() {
    ASSERT(nRemIns<MAXNREMINS, ("Rem Instr array is overflow.\n"));
    aRemIns[nRemIns]._iins = INVALID;
    aRemIns[nRemIns]._rem_type = REM_NONE;
    aRemIns[nRemIns]._weight = 0;
    aRemIns[nRemIns]._operand_no = 0;
    
    return (nRemIns++);
}

REMINDEX RemNew() {
    ASSERT(nRem<MAXNREM, ("Rem array is overflow.\n"));
    aRem[nRem]._offset = 0;
    aRem[nRem]._rem_instr = ArrayNew();
    aRem[nRem]._allotted_reg = EX_NONE;
    aRem[nRem]._xmm_order = 0;
    aRem[nRem]._rem_size = 0;
    aRem[nRem]._gpr_num = 0;
    aRem[nRem]._xmm_num = 0;
    aRem[nRem]._trans_num = 0;
    aRem[nRem]._trans_xmm_num = 0;
    aRem[nRem]._fr_num = 0;
    aRem[nRem]._weight = 0;
    aRem[nRem]._need_sync = 0;

    aRem[nRem]._next = INVALID;

    return (nRem++);
}

void RemCalWeight(REMINDEX irem) {
    RMINSINDEX irem_ins;
    int i;
    
    ASSERT(REM_MAX<REM_TYPE_NUM, ("The num of rem type is overflow.\n"));
    for(i=0; i<aRem[irem]._rem_instr->NumOfElem; i++) {
        irem_ins = aRem[irem]._rem_instr->ArrayBase[i];
      #ifndef _ANOTHER_SELECT
        if(aRemIns[irem_ins]._rem_type==TRAN_DEST || aRemIns[irem_ins]._rem_type==TRAN_XMM_DEST || \
            aRemIns[irem_ins]._rem_type==LOAR_DEST || aRemIns[irem_ins]._rem_type==XMM_DEST) {
            aRem[irem]._weight += 1;
            aRem[irem]._need_sync = 1;
        }
        else
            aRem[irem]._weight += rem_weight[aRemIns[irem_ins]._rem_type] * aRemIns[irem_ins]._weight;
      #else
        if(aRemIns[irem_ins]._rem_type==TRAN_DEST || aRemIns[irem_ins]._rem_type==TRAN_XMM_DEST || \
            aRemIns[irem_ins]._rem_type==LOAR_DEST || aRemIns[irem_ins]._rem_type==XMM_DEST) {
            aRem[irem]._weight += aRemIns[irem_ins]._weight;
            aRem[irem]._need_sync = 1;
        }
        else
            aRem[irem]._weight += 5*aRemIns[irem_ins]._weight;
      #endif

        if(aRemIns[irem_ins]._rem_type>=LOAR_DEST && aRemIns[irem_ins]._rem_type<=LOAR_SRC_D5)
            aRem[irem]._gpr_num ++;
        else if(aRemIns[irem_ins]._rem_type>=XMM_DEST && aRemIns[irem_ins]._rem_type<=XMM_SRC_D5)
            aRem[irem]._xmm_num ++;
        else if(aRemIns[irem_ins]._rem_type>=TRAN_DEST && aRemIns[irem_ins]._rem_type<=TRAN_SRC_D5)
            aRem[irem]._trans_num ++;
        else if(aRemIns[irem_ins]._rem_type>=TRAN_XMM_DEST && aRemIns[irem_ins]._rem_type<=TRAN_XMM_SRC_D5)
            aRem[irem]._trans_xmm_num ++;
        else if(aRemIns[irem_ins]._rem_type==MMX_OPER || aRemIns[irem_ins]._rem_type==FR_OPER) {
            aRem[irem]._fr_num ++;
            aRem[irem]._weight = 0;
            break;
        }
    }
}

REMINDEX RemSearch(REMINDEX irem, int offset) {
    while(irem) {
        if(aRem[irem]._offset == offset)
            break;
        else
            irem = aRem[irem]._next;
    }

    return irem;
}

void RemListSort(OUTLPINDEX iloop) {
    REMINDEX ipre1, ipre2, imax, ip1, ip2, itemp;

    if(aOutLoop[iloop]._rem_list == INVALID)
        return;

    for(ip1=aOutLoop[iloop]._rem_list; ip1!=INVALID; ip1=aRem[ip1]._next)
        RemCalWeight(ip1);

    for(ip1=aOutLoop[iloop]._rem_list; aRem[ip1]._next!=INVALID; ipre1=imax,ip1=aRem[imax]._next) /*pre_p1 maxmum*/ 
    { 
        imax = ip1; 
        for(ip2=ip1; ip2!=INVALID; ipre2=ip2,ip2=aRem[ip2]._next) { 
            if(aRem[ip2]._weight > aRem[imax]._weight) 
               imax = ip2;  /*record the maxmum node and the pre*/ 
            else 
               continue; 
  
            /*swap*/
            if(ip1==aOutLoop[iloop]._rem_list) 
                aOutLoop[iloop]._rem_list = imax;
            else 
                aRem[ipre1]._next = imax;

            itemp = aRem[imax]._next;

            if(aRem[ip1]._next == imax) { 
                aRem[imax]._next = ip1; 
                aRem[ip1]._next = itemp; 
            } 
            else { 
                aRem[imax]._next = aRem[ip1]._next; 
                aRem[ipre2]._next = ip1; 
                aRem[ip1]._next = itemp; 
            }

            ip1 = imax;
        } 
    }
}

void RemListSortRegion(OUTLPINDEX iloop) {
    REGIONINDEX iregion;
    REMINDEX ipre1, ipre2, imax, ip1, ip2, itemp;

    iregion = aOutLoop[iloop]._region;
    while(iregion) {
        if(aRegion[iregion]._rem_list == INVALID) {
            iregion = aRegion[iregion]._next;
            continue;
        }

        for(ip1=aRegion[iregion]._rem_list; ip1!=INVALID; ip1=aRem[ip1]._next)
            RemCalWeight(ip1);

        for(ip1=aRegion[iregion]._rem_list; aRem[ip1]._next!=INVALID; ipre1=imax,ip1=aRem[imax]._next) /*pre_p1 maxmum*/ 
        { 
            imax = ip1; 
            for(ip2=ip1; ip2!=INVALID; ipre2=ip2,ip2=aRem[ip2]._next) { 
                if(aRem[ip2]._weight > aRem[imax]._weight) 
                   imax = ip2;  /*record the maxmum node and the pre*/ 
                else 
                   continue; 
      
                /*swap*/
                if(ip1==aRegion[iregion]._rem_list) 
                    aRegion[iregion]._rem_list = imax;
                else 
                    aRem[ipre1]._next = imax;

                itemp = aRem[imax]._next;

                if(aRem[ip1]._next == imax) { 
                    aRem[imax]._next = ip1; 
                    aRem[ip1]._next = itemp; 
                } 
                else { 
                    aRem[imax]._next = aRem[ip1]._next; 
                    aRem[ipre2]._next = ip1; 
                    aRem[ip1]._next = itemp; 
                }

                ip1 = imax;
            } 
        }
        iregion = aRegion[iregion]._next;
    }
}

REGIONINDEX RegionNew() {
    ASSERT(nRegion<MAXNREGION, ("Region array is overflow.\n"));
    aRegion[nRegion]._ibb = INVALID;
    aRegion[nRegion]._rem_list = INVALID;
    aRegion[nRegion]._rem_num = 0;
    aRegion[nRegion]._next = INVALID;

    return (nRegion++);
}

INNLPINDEX InnLoopNew() {
    ASSERT(nInnLp<MAXNINNLP, ("Inner loop array is overflow.\n"));
    aInnLoop[nInnLp]._entry = INVALID;
    aInnLoop[nInnLp]._flag = 0;
    aInnLoop[nInnLp]._member = ArrayNew();
    aInnLoop[nInnLp]._exit = ArrayNew();
    aInnLoop[nInnLp]._instr_num = 0;
    aInnLoop[nInnLp]._call_num = 0;
    aInnLoop[nInnLp]._samples = 0;
    aInnLoop[nInnLp]._inner = INVALID;
    aInnLoop[nInnLp]._next = INVALID;

    return (nInnLp++);
}

OUTLPINDEX OutLoopNew() {
    ASSERT(nOutLp<MAXNOUTLP, ("Outer loop array is overflow.\n"));
    aOutLoop[nOutLp]._entry = INVALID;
    aOutLoop[nOutLp]._flag = 0;
    aOutLoop[nOutLp]._member = ArrayNew();
    aOutLoop[nOutLp]._exit = ArrayNew();
    aOutLoop[nOutLp]._rem_list = INVALID;
    aOutLoop[nOutLp]._rem_num = 0;
    aOutLoop[nOutLp]._instr_num = 0;
    aOutLoop[nOutLp]._call_num = 0;
    aOutLoop[nOutLp]._samples = 0;
    aOutLoop[nOutLp]._inner = INVALID;
    aOutLoop[nOutLp]._region = INVALID;

    return (nOutLp++);
}

#ifdef _DEBUG
void PrintLoopMember(ARRAY *t_array) {
    int i,j;
	BOOL change = TRUE;
	ELEM_TYPE t_elem;
	for(i=t_array->NumOfElem-1; i>0&&change; --i)	{
		change = FALSE;
		for(j=0; j<i; ++j) {
			if(aBb[t_array->ArrayBase[j]]._entry_addr > aBb[t_array->ArrayBase[j+1]]._entry_addr)	{
				t_elem = t_array->ArrayBase[j];
				t_array->ArrayBase[j] = t_array->ArrayBase[j+1];
				t_array->ArrayBase[j+1] = t_elem;
				change = TRUE;
			}
		}
	}
    
    for(i=0; i<t_array->NumOfElem; i++) {
        fprintf(stderr, "0x%lx  ", aBb[t_array->ArrayBase[i]]._entry_addr);
        if((i+1)%5==0)
            fprintf(stderr, "\n");
    }
}
#endif

