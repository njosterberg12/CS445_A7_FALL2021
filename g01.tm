* C- compiler version C-F21
* Built: Dec 3, 2021
* Author: Nathaniel Osterberg
* File compiled:  g01.tm
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
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION cat
* TOFF set: -2
 39:     ST  3,-1(1)	Store return address 
* COMPOUND
* TOFF set: -3
* EXPRESSION
* CALL output
 40:     ST  1,-3(1)	Store fp in ghost frame for output
* TOFF dec: -4
* TOFF dec: -5
* Param 1
* EXPRESSION
 41:     LD  3,-2(1)	Load variable z
 42:     ST  3,-5(1)	Push parameter 
* Param end
 43:    LDA  1,-3(1)	Ghost frame becomes new active frame 
 44:    LDA  3,1(7)	  Return address in ac 
 45:    JMP  7,-40(7)	CALL output
 46:    LDA  3,0(2)	  Save the result in ac 
* Call end output
* EXPRESSION
* Assign
* EXPRESSION
 47:    LDC  3,122(6)	Load integer const 
* EXPRESSION
* EXPRESSION
* CALL output
 48:     ST  1,-3(1)	Store fp in ghost frame for output
* TOFF dec: -4
* TOFF dec: -5
* Param 1
* EXPRESSION
 49:     LD  3,-2(1)	Load variable z
 50:     ST  3,-5(1)	Push parameter 
* Param end
 51:    LDA  1,-3(1)	Ghost frame becomes new active frame 
 52:    LDA  3,1(7)	  Return address in ac 
 53:    JMP  7,-48(7)	CALL output
 54:    LDA  3,0(2)	  Save the result in ac 
* Call end output
* Compound Body
* TOFF set: -3
* END COMPOUND
* Add standard closing in case there is no return statement
 55:    LDC  2,0(6)	Set return value to 0 
 56:     LD  3,-1(1)	Load return address 
 57:     LD  1,0(1)	Adjust fp 
 58:    JMP  7,0(3)	Return 
* END FUNCTION cat
* ** ** ** ** ** ** ** ** ** ** ** **
* FUNCTION main
* TOFF set: -2
 59:     ST  3,-1(1)	Store return address 
* COMPOUND
* TOFF set: -2
* TOFF dec: -3
* EXPRESSION
* Assign
* EXPRESSION
 60:    LDC  3,637(6)	Load integer const 
* EXPRESSION
 61:     ST  3,-2(1)	Store variable z
* EXPRESSION
* CALL cat
 62:     ST  1,-3(1)	Store fp in ghost frame for cat
* TOFF dec: -4
* TOFF dec: -5
* Param 1
* EXPRESSION
 63:     LD  3,-2(1)	Load variable z
 64:     ST  3,-5(1)	Push parameter 
* Param end
 65:    LDA  1,-3(1)	Ghost frame becomes new active frame 
 66:    LDA  3,1(7)	  Return address in ac 
 67:    JMP  7,-29(7)	CALL cat
 68:    LDA  3,0(2)	  Save the result in ac 
* Call end cat
* EXPRESSION
* CALL output
 69:     ST  1,-3(1)	Store fp in ghost frame for output
* TOFF dec: -4
* TOFF dec: -5
* Param 1
* EXPRESSION
 70:     LD  3,-2(1)	Load variable z
 71:     ST  3,-5(1)	Push parameter 
* Param end
 72:    LDA  1,-3(1)	Ghost frame becomes new active frame 
 73:    LDA  3,1(7)	  Return address in ac 
 74:    JMP  7,-69(7)	CALL output
 75:    LDA  3,0(2)	  Save the result in ac 
* Call end output
* Compound Body
* TOFF set: -2
* END COMPOUND
* Add standard closing in case there is no return statement
 76:    LDC  2,0(6)	Set return value to 0 
 77:     LD  3,-1(1)	Load return address 
 78:     LD  1,0(1)	Adjust fp 
 79:    JMP  7,0(3)	Return 
* END FUNCTION main
  0:    JMP  7,79(7)	Jump to init [backpatch] 
* INIT
 80:    LDA  1,0(0)	Set first frame at end of globals 
 81:     ST  1,0(1)	Store old fp (point to self) 
* INIT GLOBALS AND STATICS
* END INIT GLOBALS AND STATICS
 82:    LDA  3,1(7)	Return address in ac 
 83:    JMP  7,-25(7)	Jump to main 
 84:   HALT  0,0,0	Done! 
* END INIT
