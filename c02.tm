* C- compiler version C-F21
* Built: Dec 3, 2021
* Author: Nathaniel Osterberg
* File compiled:  c02.tm
* 
* FUNCTION input
  1:     ST  3,-1(1)	Store return address 
  2:     IN  2,2,2	Grab int input 
  3:     LD  3,-1(1)	Load return address 
  4:     LD  1,0(1)	Adjust fp 
  5:    JMP  7,0(3)	Return 
* End FUNCTION input
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION output
  6:     ST  3,-1(1)	Store return address 
  7:     LD  3,-2(1)	Load return address 
  8:    OUT  3,3,3	Output integer 
  9:     LD  3,-1(1)	Load return address 
 10:     LD  1,0(1)	Adjust fp 
 11:    JMP  7,0(3)	Return 
* End FUNCTION output
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION inputb
 12:     ST  3,-1(1)	Store return address 
 13:    INB  2,2,2	Grab bool input 
 14:     LD  3,-1(1)	Load return address 
 15:     LD  1,0(1)	Adjust fp 
 16:    JMP  7,0(3)	Return 
* End FUNCTION inputb
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION outputb
 17:     ST  3,-1(1)	Store return address 
 18:     LD  3,-2(1)	Load return address 
 19:   OUTB  3,3,3	Output integer 
 20:     LD  3,-1(1)	Load return address 
 21:     LD  1,0(1)	Adjust fp 
 22:    JMP  7,0(3)	Return 
* End FUNCTION outputb
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION inputc
 23:     ST  3,-1(1)	Store return address 
 24:    INC  2,2,2	Grab bool input 
 25:     LD  3,-1(1)	Load return address 
 26:     LD  1,0(1)	Adjust fp 
 27:    JMP  7,0(3)	Return 
* End FUNCTION inputc
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION outputc
 28:     ST  3,-1(1)	Store return address 
 29:     LD  3,-2(1)	Load return address 
 30:   OUTC  3,3,3	Output integer 
 31:     LD  3,-1(1)	Load return address 
 32:     LD  1,0(1)	Adjust fp 
 33:    JMP  7,0(3)	Return 
* End FUNCTION outputc
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION outnl
 34:     ST  3,-1(1)	Store return address 
 35:  OUTNL  3,3,3	Output a newline 
 36:     LD  3,-1(1)	Load return address 
 37:     LD  1,0(1)	Adjust fp 
 38:    JMP  7,0(3)	Return 
* End FUNCTION outnl
* 
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION main
* TOFF set: -2
 39:     ST  3,-1(1)	Store return address 
* COMPOUND
* TOFF set: -2
* Compound Body
* TOFF dec: -3
* TOFF dec: -4
* EXPRESSION
* Assign
* EXPRESSION
 40:    LDC  3,1(6)	Load boolean const 
* EXPRESSION
 41:     ST  3,-2(1)	Store variable x
* EXPRESSION
* Assign
* EXPRESSION
 42:    LDC  3,0(6)	Load boolean const 
* EXPRESSION
 43:     ST  3,-3(1)	Store variable y
* EXPRESSION
* CALL outputb
 44:     ST  1,-4(1)	Store fp in ghost frame for outputb
* TOFF dec: -5
* TOFF dec: -6
* Param
* EXPRESSION
* OpK
* EXPRESSION
 45:     LD  3,-2(1)	Load variable x
 46:     ST  3,-6(1)	Save left side 
* EXPRESSION
 47:     LD  3,-3(1)	Load variable y
 48:     LD  4,-6(1)	Load left into ac1 
 49:    AND  3,4,3	Op and 
 50:     ST  3,-6(1)	Push parameter 
* Param end
 51:    LDA  1,-4(1)	Ghost frame becomes new active frame 
 52:    LDA  3,1(7)	 Return address in ac 
 53:    JMP  7,-37(7)	CALL outputb
 54:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outnl
 55:     ST  1,-4(1)	Store fp in ghost frame for outnl
* Param end
 56:    LDA  1,-4(1)	Ghost frame becomes new active frame 
 57:    LDA  3,1(7)	 Return address in ac 
 58:    JMP  7,-25(7)	CALL outnl
 59:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -2
* END COMPOUND
* Add standard closing in case there is no return statement
 60:    LDC  2,0(6)	Set return value to 0 
 61:     LD  3,-1(1)	Load return address 
 62:     LD  1,0(1)	Adjust fp 
 63:    JMP  7,0(3)	Return 
* END FUNCTION main
  0:    JMP  7,63(7)	Jump to init [backpatch] 
* INIT
 64:    LDA  1,0(0)	Set first frame at end of globals 
 65:     ST  1,0(1)	Store old fp (point to self) 
* INIT GLOBALS AND STATICS
* END INIT GLOBALS AND STATICS
 66:    LDA  3,1(7)	Return address in ac 
 67:    JMP  7,-29(7)	Jump to main 
 68:   HALT  0,0,0	Done! 
* END INIT
