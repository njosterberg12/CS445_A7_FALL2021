* C- compiler version C-F21
* Built: Dec 3, 2021
* Author: Nathaniel Osterberg
* File compiled:  c06.tm
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
 40:    LDC  3,3(6)	  load size of array x
 41:     ST  3,-2(1)	save size of array x
 42:    LDC  3,4(6)	  load size of array y
 43:     ST  3,-6(1)	save size of array y
* EXPRESSION
* Assign
* EXPRESSION
 44:    LDC  3,2(6)	Load integer const 
* EXPRESSION
* EXPRESSION
 45:    LDC  3,73(6)	Load integer const 
 46:     LD  4,-11(1)	Pop index 
 47:    LDA  5,-3(1)	Load address of base of array x
 48:    SUB  5,5,4	Compute offset of value 
 49:     ST  3,0(5)	Store variable x
* EXPRESSION
* Assign
* EXPRESSION
 50:    LDC  3,1(6)	Load integer const 
* EXPRESSION
* EXPRESSION
 51:    LDC  3,211(6)	Load integer const 
 52:     LD  4,-11(1)	Pop index 
 53:    LDA  5,-7(1)	Load address of base of array y
 54:    SUB  5,5,4	Compute offset of value 
 55:     ST  3,0(5)	Store variable y
* EXPRESSION
* CALL output
 56:     ST  1,-11(1)	Store fp in ghost frame for output
* TOFF dec: -12
* TOFF dec: -13
* Param
* EXPRESSION
* OpK
* EXPRESSION
* OpK
 57:    LDA  3,-3(1)	Load address of base of array 
 58:     ST  3,-13(1)	Push left side 
* TOFF dec: -14
* EXPRESSION
 59:    LDC  3,2(6)	Load integer const 
* TOFF inc: -13
 60:     LD  4,-13(1)	Pop left into ac1 
 61:    SUB  3,4,3	Compute location from index 
 62:     LD  3,0(3)	Load array element 
 63:     ST  3,-13(1)	Save left side 
* TOFF dec: -14
* EXPRESSION
* OpK
 64:    LDA  3,-7(1)	Load address of base of array 
 65:     ST  3,-14(1)	Push left side 
* TOFF dec: -15
* EXPRESSION
 66:    LDC  3,1(6)	Load integer const 
* TOFF inc: -14
 67:     LD  4,-14(1)	Pop left into ac1 
 68:    SUB  3,4,3	Compute location from index 
 69:     LD  3,0(3)	Load array element 
* TOFF inc: -13
 70:     LD  4,-13(1)	Pop left into ac1 
 71:    ADD  3,4,3	Op + 
 72:     ST  3,-13(1)	Push parameter 
* Param end
 73:    LDA  1,-11(1)	Ghost frame becomes new active frame 
 74:    LDA  3,1(7)	 Return address in ac 
 75:    JMP  7,-70(7)	CALL output
 76:    LDA  3,0(2)	Save the result in ac 
* Call end output
* EXPRESSION
* CALL outnl
 77:     ST  1,-11(1)	Store fp in ghost frame for outnl
* Param end
 78:    LDA  1,-11(1)	Ghost frame becomes new active frame 
 79:    LDA  3,1(7)	 Return address in ac 
 80:    JMP  7,-47(7)	CALL outnl
 81:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -2
* END COMPOUND
* Add standard closing in case there is no return statement
 82:    LDC  2,0(6)	Set return value to 0 
 83:     LD  3,-1(1)	Load return address 
 84:     LD  1,0(1)	Adjust fp 
 85:    JMP  7,0(3)	Return 
* END FUNCTION main
  0:    JMP  7,85(7)	Jump to init [backpatch] 
* INIT
 86:    LDA  1,0(0)	Set first frame at end of globals 
 87:     ST  1,0(1)	Store old fp (point to self) 
* INIT GLOBALS AND STATICS
* END INIT GLOBALS AND STATICS
 88:    LDA  3,1(7)	Return address in ac 
 89:    JMP  7,-51(7)	Jump to main 
 90:   HALT  0,0,0	Done! 
* END INIT
