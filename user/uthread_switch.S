	.text

	/*
         * save the old thread's registers,
         * restore the new thread's registers.
         */

	.globl thread_switch
thread_switch:
	/* YOUR CODE HERE */
	    sd ra, 0(a0)
        sd sp, 8(a0)
        sd s0, 16(a0)
        sd s1, 24(a0)
        sd s2, 32(a0)
        sd s3, 40(a0)
        sd s4, 48(a0)
        sd s5, 56(a0)
        sd s6, 64(a0)
        sd s7, 72(a0)
        sd s8, 80(a0)
        sd s9, 88(a0)
        sd s10, 96(a0)
        sd s11, 104(a0)

# 	/*switch stack*/ 
# 		xor s0,s0,s0
# 		xor s1,s1,s1
#         xor s2,s2,s2
#         xor s3,s3,s3
#         xor s4,s4,s4
# 		addi s0,s0,512
# save_stack1:
#         addi s1,s1,8
#         add s2,sp,s1
#         add s3,a0,s1
#         ld s4,0(s2)
#         sd s4,0(s3)
#         addi s0,s0,-1
#         bne s0,x0,save_stack1


# 		xor s0,s0,s0 //512....0 indicator loop 
# 		xor s1,s1,s1 //8 16 24 32 indicate sp offset
#         xor s2,s2,s2 //sp sp+8 sp+16 ...
#         xor s3,s3,s3 //struct offset
#         xor s4,s4,s4 // stack content
# 		addi s0,s0,512
# load_stack1:
#         addi s1,s1,8
#         ld s2,8(a1)
#         add s2,s2,s1
#         add s3,a2,s1
#         ld s4,0(s3)
#         sd s4,0(s2)
#         addi s0,s0,-1
#         bne s0,x0,load_stack1

        ld ra, 0(a1)
        ld sp, 8(a1)
        ld s0, 16(a1)
        ld s1, 24(a1)
        ld s2, 32(a1)
        ld s3, 40(a1)
        ld s4, 48(a1)
        ld s5, 56(a1)
        ld s6, 64(a1)
        ld s7, 72(a1)
        ld s8, 80(a1)
        ld s9, 88(a1)
        ld s10, 96(a1)
        ld s11, 104(a1)
	ret    /* return to ra */
