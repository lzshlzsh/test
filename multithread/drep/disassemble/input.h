/* ----------------------------------------------------------------------------- input.h Copyright 
   (c) 2006, Vivek Mohan <vivek@sig9.com> All rights reserved. See LICENSE
   ----------------------------------------------------------------------------- */
#ifndef BT_INPUT_H
#define BT_INPUT_H

/* inp_cur() - Returns the current input byte. */
#define inp_curr(u) *((UINT8*)(u->pc))

/* inp_back() - Resets the current pointer to its position before the current instruction
   disassembly was started. */
#define inp_back(u) u->pc--

/* ----------------------------------------------------------------------------- inp_next_r() -
   Loads and returns the next byte from input. */
#define inp_next_r(u) *((UINT8*)(++(u->pc)))

/* ----------------------------------------------------------------------------- inp_next() - pc
   location next */
#define inp_next(u) u->pc++

/* ----------------------------------------------------------------------------- inp_uintx() - next 
   pc locations 's x bits,notice that the pc stop at the last byte of the unit returned */
#define inp_uint8(u) *((UINT8*)(++(u->pc)))

#define inp_uint16(u) \
	*((UINT16*)(++(u->pc)));\
	u->pc++

#define inp_uint32(u) \
	*((UINT32*)(++(u->pc)));\
	u->pc+=3;

#define inp_uint64(u) \
	*((UINT64*)(++(u->pc)));\
	u->pc+=7;

#define inp_int8(u) (*((INT8*)(++(u->pc))))

#define inp_int16(u) \
	(*((INT16*)(++(u->pc))));\
	u->pc++

#define inp_int32(u) \
	(*((INT32*)(++(u->pc))));\
	u->pc+=3;

#define inp_int64(u) \
	(*((INT64*)(++(u->pc))));\
	u->pc+=7;

#define inp_peek(u)  *((UINT8*)(u->pc+1))

#endif
