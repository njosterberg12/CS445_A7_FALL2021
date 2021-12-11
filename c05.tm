* C- compiler version C-F21
* Built: Dec 3, 2021
* Author: Nathaniel Osterberg
* File compiled:  c05.tm
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
 39:    LDC  3,3(6)	  load size of array x
 40:     ST  3,0(1)	save size of array x
 41:    LDC  3,4(6)	  load size of array y
 42:     ST  3,-4(1)	save size of array y
* FUNCTION main
* TOFF set: -2
 43:     ST  3,-1(1)	Store return address 
* COMPOUND
* TOFF set: -2
* EXPRESSION
* Assign
* EXPRESSION
 44:    LDC  3,2(6)	Load integer const 
 45:     ST  3,-2(1)	Push index 
* TOFF dec: -3
* EXPRESSION
 46:    LDC  3,73(6)	Load integer const 
* TOFF inc: -2
 47:     LD  4,-2(1)	Pop index 
 48:    LDA  5,-1(0)	Load address of base of array x
 49:    SUB  5,5,4	Compute offset of value x
 50:     ST  3,0(5)	Store variable x
* EXPRESSION
* Assign
* EXPRESSION
 51:    LDC  3,1(6)	Load integer const 
 52:     ST  3,-2(1)	Push index 
* TOFF dec: -3
* EXPRESSION
 53:    LDC  3,211(6)	Load integer const 
* TOFF inc: -2
 54:     LD  4,-2(1)	Pop index 
 55:    LDA  5,-5(0)	Load address of base of array y
 56:    SUB  5,5,4	Compute offset of value y
 57:     ST  3,0(5)	Store variable y
* EXPRESSION
* CALL output
 58:     ST  1,-2(1)	Store fp in ghost frame for output
* TOFF dec: -3
* TOFF dec: -4
* Param
* EXPRESSION
* OpK
* EXPRESSION
* OpK
 59:    LDA  3,-1(0)	Load address of base of array 
 60:     ST  3,-4(1)	Push left side 
* TOFF dec: -5
* EXPRESSION
 61:    LDC  3,2(6)	Load integer const 
* TOFF inc: -4
 62:     LD  4,-4(1)	Pop left into ac1 
 63:    SUB  3,4,3	Compute location from index 
 64:     LD  3,0(3)	Load array element 
 65:     ST  3,-4(1)	Save left side 
* TOFF dec: -5
* EXPRESSION
* OpK
 66:    LDA  3,-5(0)	Load address of base of array 
 67:     ST  3,-5(1)	Push left side 
* TOFF dec: -6
* EXPRESSION
 68:    LDC  3,1(6)	Load integer const 
* TOFF inc: -5
 69:     LD  4,-5(1)	Pop left into ac1 
 70:    SUB  3,4,3	Compute location from index 
 71:     LD  3,0(3)	Load array element 
* TOFF inc: -4
 72:     LD  4,-4(1)	Pop left into ac1 
 73:    ADD  3,4,3	Op + 
 74:     ST  3,-4(1)	Push parameter 
* Param end
 75:    LDA  1,-2(1)	Ghost frame becomes new active frame 
 76:    LDA  3,1(7)	 Return address in ac 
 77:    JMP  7,-72(7)	CALL output
 78:    LDA  3,0(2)	Save the result in ac 
* Call end output
* EXPRESSION
* CALL outnl
 79:     ST  1,-2(1)	Store fp in ghost frame for outnl
* Param end
 80:    LDA  1,-2(1)	Ghost frame becomes new active frame 
 81:    LDA  3,1(7)	 Return address in ac 
 82:    JMP  7,-49(7)	CALL outnl
 83:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* Compound Body
* TOFF set: -2
* END COMPOUND
* Add standard closing in case there is no return statement
 84:    LDC  2,0(6)	Set return value to 0 
 85:     LD  3,-1(1)	Load return address 
 86:     LD  1,0(1)	Adjust fp 
 87:    JMP  7,0(3)	Return 
* END FUNCTION main
  0:    JMP  7,87(7)	Jump to init [backpatch] 
* INIT
 88:    LDA  1,-9(0)	Set first frame at end of globals 
 89:     ST  1,0(1)	Store old fp (point to self) 
* INIT GLOBALS AND STATICS
 90:    LDC  3,3(6)	load saved size of array x
 91:     ST  3,0(0)	save size of array x
 92:    LDC  3,4(6)	load saved size of array y
 93:     ST  3,-4(0)	save size of array y
* END INIT GLOBALS AND STATICS
 94:    LDA  3,1(7)	Return address in ac 
 95:    JMP  7,-53(7)	Jump to main 
 96:   HALT  0,0,0	Done! 
* END INIT
