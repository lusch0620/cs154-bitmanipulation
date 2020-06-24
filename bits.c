/* CS:APP Data Lab 
 *
 * Name: Lucius Gao
 * CNET: luciusgao2001
 * 
 * bits.c - Source file with your solutions to the project.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
* it's not good practice to ignore compiler warnings, but in this
* case it's OK.  
*/

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the project by
editing the collection of functions in this source file.

CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
  
  int Funct(arg1, arg2, ...) {
  	  /* brief description of how your implementation works */
	  int var1 = Expr1;
	  ...
	  int varM = ExprM;
	  
	  varJ = ExprJ;
	  ...
      varN = ExprN;
	  return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
  not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
  cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
  than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
	 /* exploit ability of shifts to compute powers of 2 */
	 return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
	 /* exploit ability of shifts to compute powers of 2 */
	 int result = (1 << x);
	 result += 4;
	 return result;
  }


NOTES:
1. Use the dlc (data lab checker) compiler (described in the handout) to 
		check the legality of your solutions.
2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
		that you are allowed to use for your implementation of the function. 
		The max operator count is checked by dlc. Note that '=' is not 
		counted; you may use as many of these as you want without penalty.
		3. Use the btest test harness to check your functions for correctness.
		4. The maximum number of ops for each function is given in the
		header comment for each function.

		/*
		 * STEP 2: Modify the following functions according to the coding rules.
		 * 
		 *   IMPORTANT. TO AVOID GRADING SURPRISES:
		 *   1. Use the dlc compiler to check that your solutions conform
		 *      to the coding rules.
		 *   2. Use the btest checker to verify that your solutions produce
		 *      the correct answers.
		 */


#endif

#define check(x) printf("%d:0x%x\n", __LINE__, (x))



/************************************************ 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) 
{
	/* My first step was to mask x with either all 1's for negative numbers and 
	 * 0's for positive numbers. Then I added the masked number to the binary
	 * number which gave me a number that was the opposite of what I actually
	 * wanted. Finally, I used XOR to change everything to what I wanted
	 */
	int mask = x >> 31;
	int ans = (x + mask) ^ mask;
	return ans;
}

/************************************************ 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) 
{
	/* When it comes to addition/subtraction and overflow, it's important to 
	 * realize that there are 3 cases--(1) overflow with + + results in a 
	 * negative number, (2) overflow with - - results in a positive number, 
	 * and (3) if x and why have opposite signs then there will be no 
	 * overflow. So the most critical element of this puzzle is to find the
	 * signs of x, y, and the sum's signs. The way to see if the signs are 
	 * different is done by the same_sign_precaution variable. The final step
	 * is just OR-ing the two signs and then binarizing the answer.
	 */

	int sum = x + y;
	int x_sign = x >> 31;
	int y_sign = y >> 31;
	int xy_sign = x_sign ^ y_sign;
	int sum_sign = sum >> 31;
	int same_sign_precaution = y_sign ^ sum_sign;
	int ans = xy_sign | ~same_sign_precaution;
	return !!ans;
}

/************************************************ 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) 
{
	/* The most important thing in this puzzle was to find and create the right
	 * mask. I did that in two steps--creating the first half and then shifting
	 * and creating the second half. To account for one of the edge cases, I 
	 * had to XOR the value as well as AND it with the mask. The second to last
	 * result if x were 0x55555555 would be 0 so I !0 which yielded 1. 
	 * Every other value would have yielded 1 at first so !1 would yield 0.
	 */
	int half_mask = (0x55 << 8) + 0x55;
	int full_mask = (half_mask << 16) + half_mask;
	int precaution = x & full_mask;
	int apply_mask = precaution ^ full_mask;
	int ans = !apply_mask;
	return ans;
}

/************************************************
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x)
{
	/* I think the most important thing to realize here is that the negative
	 * two's complement's version of 0 is the same but for any other number
	 * it's not. So, when I OR x with its negative version, the most 
	 * significant byte will always be 1. When I shift everything right by
	 * 31, all 32 bits will be the same as the MSB. If all 32 bytes are 1, the
	 * value is -1, add 1 to it and it's 0! In the case where x is 0, we do the
	 * same thing which still yields 0 and then add 1, which is 1 which is what
	 * we want. 
	 */

	int negative_x = (~x) + 1;
	int all_ones_or_zeros = (x | negative_x) >> 31; 
	// >> needed for the edge case 0x80000001 !!!
	int ans = all_ones_or_zeros + 1;
	return ans;
}

/************************************************
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) 
{
	/* Unfortunately I couldn't figure out how to do less operators. Essentially,
	 * the most important part here is to have a marker for each important
	 * nibble. Then shift x the right in increments of one and apply the 
	 * mask so that it can keep track of the ones. Add those all together. 
	 * The final answer is derived by shifting the original sum to the 
	 * right in increments of 4.
	 */
	int mask = (1 << 28) + (1 << 24) + (1 << 20) + (1 << 16) + (1 << 12) + (1 << 8) + (1 << 4) + 1;
	int app_mask1 = x & mask;
	int app_mask2 = mask & (x >> 1);
	int app_mask3 = mask & (x >> 2);
	int app_mask4 = mask & (x >> 3);
	int sum = app_mask1 + app_mask2 + app_mask3 + app_mask4;
	int total1 = sum & 0xF;
	int total2 = (sum >> 4) & 0xF;
	int total3 = (sum >> 8) & 0xF;
	int total4 = (sum >> 12) & 0xF;
	int total5 = (sum >> 16) & 0xF;
	int total6 = (sum >> 20) & 0xF;
	int total7 = (sum >> 24) & 0xF;
	int total8 = (sum >> 28) & 0xF;
	int ans = total1 + total2 + total3 + total4 + total5 + total6 + total7 +total8;
	return ans;
}

/************************************************
 * bitNor - ~(x|y) using only ~ and & 
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitNor(int x, int y)
{
	/* bitNor is really just the complete opposite of or. So all that needs 
	 * to be done is to NOT all the values and AND them together. Logically
	 * that also makes sense. 
	 */
	int not_x = ~x;
	int not_y = ~y;
	int ans = not_x & not_y;;

	return ans;
}

/************************************************
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) 
{
	/* The trick to this problem was essentially just splitting the relevant
	 * bytes apart and then creating the proper mask. Another important step is
	 * to mask all the relevant bytes to 0 and then "add" back in the other
	 * relevant bytes. This effectively simulates "swapping" bytes. 
	 */
	int nth_byte = (x >> ((n << 3) & 0xFF)) & 0xFF;
	int mth_byte = (x >> ((m << 3) & 0xFF)) & 0xFF;

	int nth_byte_one_mask = 0xFF << ((n << 3) & 0xFF);
	int mth_byte_one_mask = 0xFF << ((m << 3) & 0xFF);
	
	int mask = nth_byte_one_mask | mth_byte_one_mask;
	int apply_mask = x & ~mask;
	
	int m_to_n = mth_byte << ((n << 3) & 0xFF);
	int n_to_m = nth_byte << ((m << 3) & 0xFF);
	int add_to_x = m_to_n | n_to_m;
	
	int ans = apply_mask | add_to_x;
	return ans;
}

/************************************************ 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) 
{
	/* This one was actually sorta difficult. The first important realization
	 * is that everything has to do with the x value and that binarizing it
	 * made all the difference. The second important thing is finding a way
	 * to make either y or z zero and keeping the other its original value. This
	 * was done by creating mask variables that would always either be 1111 or 
	 * 0000 but change based on x. Then all we needed to do was AND both 
	 * values with the mask and add them together since the result of one of 
	 * them will be the original value and the other will be all zeros
	 */
	int binarize = !x;
	int mask1 = (~ binarize) + 1;
	int mask2 = ~mask1;
	int z_apply_mask1 = z & mask1;
	int y_apply_mask2 = y & mask2;
	int ans = z_apply_mask1 + y_apply_mask2;
	return ans;
}

/************************************************
 * ezThreeFourths - multiplies by 3/4 rounding toward 0,
 *   Should exactly duplicate effect of C expression (x*3/4),
 *   including overflow behavior.
 *   Examples: ezThreeFourths(11) = 8
 *             ezThreeFourths(-9) = -6
 *             ezThreeFourths(1073741824) = -268435456 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int ezThreeFourths(int x) 
{
	/* This problem would've been easy had we not had to take into account
	 * overflow. Clearly, we need to add x 3 times to simulate multiplying
	 * by the numerator. This may cause the overflow, so we need to get the
	 * sign of product. If the sign is negative (all 1's), we must mask it by
	 * 3, this is no coincidence because we multiplied by 3! After we mask
	 * the value by three, we need to add it back to the original product so 
	 * we get the actual product and then shift it right by 2 effectively 
	 * simulating dividng by 4. 
	 */
	int xxx = x + x + x;
	int xxx_sign = xxx >> 31;
	int mask_with_3 = xxx_sign & 0x3;
	int xxx_add = xxx + mask_with_3;
	int ans = xxx_add >> 2;
	return ans;
}

/************************************************ 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) 
{
	/* The most important property to note here is that when x is shifted 
	 * left and then right by 32 + (~n + 1) amounts. By shifting it that way 
	 * twice, we effectively simulate truncation. If the x can fit in n bits,
	 * then after shifting left and right, it should return the same number. 
	 * Else, it returns a different number. Once this is established we can 
	 * just use the isEqual function to compare.
	 */
	int shift_by = 32 + (~n + 1);
	int get_sign = x << shift_by;
	int revert = get_sign >> shift_by;
	int is_equal = !(revert ^ x);
	return is_equal;
}

/************************************************
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) 
{
	/* First, I calculated the amount I need to shift by. If n is 0 we would
	 * shift 0, 1 shift 8, 2 shift 16, and 3 shift 24. This shifts it just 
	 * enough to where the desired byte becomes the least significant byte, or
	 * sits at the 0th position. Once it's at that position, mask it with
	 * 0b11111111 will allow us to gives us the proper answer taking sign
	 * int account.
	 */
	int shift_num = (n << 3);
	int nth_byte = x >> shift_num;
	int ans = nth_byte & 0xff;
	return ans;
}

/************************************************ 
 * greatestBitPos - return a mask that marks the position of the
 *               most significant 1 bit. If x == 0, return 0
 *   Example: greatestBitPos(96) = 0x40
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70
 *   Rating: 4 
 */
int greatestBitPos(int x) 
{
	int msb, result;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	msb = 0x1 << 31;
	result = x & ((~x >> 1) + msb)
	return result;
}

/************************************************
 * implication - return x -> y in propositional logic - 0 for false, 1
 * for true
 *   Example: implication(1,1) = 1
 *            implication(1,0) = 0
 *   Legal ops: ! ~ ^ |
 *   Max ops: 5
 *   Rating: 2
 */
int implication(int x, int y) 
{
	/* Implication is a bit odd...but it essentially is completely dependent
	 * on either x or y. The only time an implication is false is when
	 * x is 1 and y is 0. The formula that makes this true is BANG x and OR it
	 * with y. This allows us to get 1 75% of the time. The time when it's false
	 * is when x=1, !x = 0, 0 | 0 = 0!
	 */

	int not_x = !x;
	int or_both = not_x | y;
	return or_both;
}

/************************************************ 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) 
{
	/* Need to get the first and second bytes. The second byte is easy since
	 * it always needs to be a 3. The least significant byte is a bit more
	 * challenging because it needs to be between 0 and 9. What I found to be
	 * useful was deciding whether or not the 4 bit of the least significant
	 * byte was a 1 and then seeing if the 2's and 4's spot was also ones. If
	 * the 8's spot was one and the 2's and 4's spot were also ones, then the
	 * value would be invalid. 
	 */
	int second_byte = (x ^ 0x30) >> 4;
	int first_byte_mask = x & 0xF;
	int is_eight = (first_byte_mask >> 3) & 1;
	int twos_fours_exist = !((x >> 1) & 0x3);
	int twos_fours_valid =!(is_eight & !(twos_fours_exist));
	int ans = (!second_byte) & twos_fours_valid;
	return ans;
}

/************************************************ 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) 
{
	/* XOR has a property where if x and y are the same, the answer will be
	 * all 0's. When x and y are different, it will be anything but 0. So,
	 * taking this into account, when they are equal !0 yields 1 and !0 yields
	 * 0, which is what we want.
	 */

	int step1 = x ^ y;
	int ans = !step1;
	return ans;
}

/************************************************
 * isLess - if x < y  then return 1, else return 0 
 *   Example: isLess(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLess(int x, int y) 
{
	/* Perhaps the most important part of this function is realizing that there
  	 * are two scenerios where x is less than y. That is why there are 2 masks 
	 * to get the signs under the different criteria. Once this is done, it's
	 * just a simple matter of OR-ing the two and the binarizing the answer.
	 */
	int diff = x + (~y + 1);
	int mask1 = (x & (~y)) >> 31;
	int mask2 = ((~(x ^ y)) & diff) >> 31;
	int ans = !!(mask1 | mask2); 
	return ans;
}

/************************************************
 * isNonNegative - return 1 if x >= 0, return 0 otherwise 
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int isNonNegative(int x)
{
	/* Shifting everything to the right by 31 will give us either all 0's or
	 * all 1's. When we NOR the rightshift value with all 1's, it will give 2
	 * different results: (1) if right_shift = all 1's, nor_both will be all
	 * 0's and (2) all 1's for the other case. To take into account the edge
	 * cases and to binarize the answer a !! is used. 
	 */

	int right_shift = x >> 31;
	int nor_both = (~ right_shift) & (~0);
	int ans = !!nor_both;
	return ans;
}

/************************************************
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) 
{
	/* There are 3 things to take into consideration here: (1) x cannot be
	 * zero, (2) x cannot be negative, and (3) x then needs to be a power of
	 * 2. The non-negative check is done by the 2nd and 3rd lines. If x is a
	 * power of 2 there will only be one 1 in all 32 bits. Adding x to ~0 
	 * will effectively make it all zeros after the 1 in x and all zeros before
	 * the 1. If we and that result with original x then we should get 0 if
	 * it's a power of 2 and anything else if not. Then we just need to 
	 * binarize the answer. The final answer will just be cominbing the sign
	 * check and and whether or not it's a power of 2.
	 */
	int all_ones = ~0;
	int non_zero_check = !!x;
	int positive_check = !(x >> 31);
	int is_nonneg = non_zero_check & positive_check;
	int highest_bit_one = x + all_ones;
	int is_same_as_before = !(x & highest_bit_one);
	int ans = is_same_as_before & is_nonneg;
	
	return ans;
}

/************************************************
 * isTmin - returns 1 if x is the minimum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmin(int x) 
{
	/* Tmin has the special property where ~Tmin + 1 is itself. No other
	 * binary number does this. The most difficult part, however, was the case
	 * where x was 0x00000000. A fix that I found was using ! and adding that 
	 * to x. From there on, I just used the isEqual function to test if x
	 * is equal to the new x that I calculated. 
	 */

	int not_x = ~x;
	int add_1 = not_x + 1;
	int zero_case = x + !x;
	int ans = !(add_1 ^ zero_case);
	return ans;
}

/************************************************
 * minusOne - return a value of -1 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void)
{
	/* This one is actually quite simple. -1 is just all one's (1111....1111),
	 * which can also be written as the opposite of all 0's -- ~0;
	 */
	int ans = ~0;
	return ans;
}

/************************************************
 * rotateLeft - Rotate x to the left by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateLeft(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateLeft(int x, int n) 
{
	/* rotateLeft has a lot of similar characteristics as byteSwap in that
	 * we need to locate the last n bytes that we want to shift to the front.
	 * Then we need to mask the last n bytes to zero. Shift x over by n so that
	 * the least significant n bytes are 0 and then OR-ing the changes in so
	 * it appears like the bytes have been rotated left. 
	 */
	int move_by = 32 + (~n + 1);
	int left_n = (x >> move_by );
	int mask_p1 = ~((~0) << n);
	int n_mask = mask_p1 & left_n;
	int change_x = x << n;
	int ans = change_x | n_mask;
	return ans;
}

/************************************************
 * satMul2 - multiplies by 2, saturating to Tmin or Tmax if overflow
 *   Examples: satMul2(0x30000000) = 0x60000000
 *             satMul2(0x40000000) = 0x7FFFFFFF (saturate to TMax)
 *             satMul2(0x60000000) = 0x80000000 (saturate to TMin)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int satMul2(int x) 
{
	/* The most important aspect of this problem is understanding that the 
	 * sign changes when overflow occurs. It also helps to know that left 
	 * shifting by one is the equivalent of multiplying by 2. However, the 
	 * most challenging part is writing a line that takes into account what
	 * happens when multiplying by 2 changes the sign (overflow) or keeps the
	 * same sign (normal). That is derived by XOR-ing the original x with xx
	 * and then getting its sign by shifting over by 31. Saturating is very
	 * similar to truncating so that's done by getting the final sign, and
	 * AND-ing it with the ~ of the last sign AND xx. 
	 */
	int tmin = 1 << 31;
	int xx = x << 1;
	int x_sign = (x >> 31);
	int sign_status = (x ^ xx) >> 31;
	int saturate = sign_status & (x_sign ^ ~tmin);
	int ans = saturate | (~sign_status & xx);
	return ans;
}

