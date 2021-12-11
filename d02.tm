* C- compiler version C-F21
* Built: Dec 3, 2021
* Author: Nathaniel Osterberg
* File compiled:  d02.tm
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
* TOFF dec: -3
* TOFF dec: -4
* TOFF dec: -5
 40:    LDC  3,755(6)	  Load integer constant 
 41:     ST  3,-2(1)	Store variable x
 42:    LDC  3,88(6)	  Load integer constant 
 43:     ST  3,-3(1)	Store variable y
 44:    LDC  3,3(6)	  Load integer constant 
 45:     ST  3,-4(1)	Store variable z
* CALL output
* TOFF dec: -6
* TOFF dec: -7
* Param 1
* OpK
 46:    LDC  3,755(6)	  Load integer constant 
 47:     ST  3,-7(1)	Save left side 
* OpK
 48:    LDC  3,88(6)	  Load integer constant 
 49:     ST  3,-7(1)	Save left side 
 50:    LDC  3,3(6)	  Load integer constant 
 51:     LD  4,-7(1)	Pop left into ac1 
 52:    MUL  3,4,3	Op * 
 53:     LD  4,-7(1)	Pop left into ac1 
 54:    ADD  3,4,3	Op + 
 55:     ST  3,-7(1)	Push parameter 
* Param end
 56:    LDA  1,-5(1)	Ghost frame becomes new active frame 
 57:    LDA  3,1(7)	 Return address in ac 
 58:    JMP  7,-53(7)	CALL output
 59:    LDA  3,0(2)	Save the result in ac 
* Call end output
* CALL output
* TOFF dec: -6
* TOFF dec: -7
* Param 1
* OpK
* OpK
 60:    LDC  3,755(6)	  Load integer constant 
 61:     ST  3,-7(1)	Save left side 
 62:    LDC  3,88(6)	  Load integer constant 
 63:     LD  4,-7(1)	Pop left into ac1 
 64:    MUL  3,4,3	Op * 
 65:     ST  3,-7(1)	Save left side 
 66:    LDC  3,3(6)	  Load integer constant 
 67:     LD  4,-7(1)	Pop left into ac1 
 68:    ADD  3,4,3	Op + 
 69:     ST  3,-7(1)	Push parameter 
* Param end
 70:    LDA  1,-5(1)	Ghost frame becomes new active frame 
 71:    LDA  3,1(7)	 Return address in ac 
 72:    JMP  7,-67(7)	CALL output
 73:    LDA  3,0(2)	Save the result in ac 
* Call end output
* CALL output
* TOFF dec: -6
* TOFF dec: -7
* Param 1
* OpK
* OpK
 74:    LDC  3,755(6)	  Load integer constant 
 75:     ST  3,-7(1)	Save left side 
 76:    LDC  3,88(6)	  Load integer constant 
 77:     LD  4,-7(1)	Load left into ac1 
 78:    SUB  3,4,3	Op - 
 79:     ST  3,-7(1)	Save left side 
 80:    LDC  3,3(6)	  Load integer constant 
 81:     LD  4,-7(1)	Load left into ac1 
 82:    SUB  3,4,3	Op - 
 83:     ST  3,-7(1)	Push parameter 
* Param end
 84:    LDA  1,-5(1)	Ghost frame becomes new active frame 
 85:    LDA  3,1(7)	 Return address in ac 
 86:    JMP  7,-81(7)	CALL output
 87:    LDA  3,0(2)	Save the result in ac 
* Call end output
* CALL output
* TOFF dec: -6
* TOFF dec: -7
* Param 1
* OpK
* OpK
 88:    LDC  3,755(6)	  Load integer constant 
 89:     ST  3,-7(1)	Save left side 
 90:    LDC  3,88(6)	  Load integer constant 
 91:     LD  4,-7(1)	Load left into ac1 
 92:    DIV  3,4,3	Op / 
 93:     ST  3,-7(1)	Save left side 
 94:    LDC  3,3(6)	  Load integer constant 
 95:     LD  4,-7(1)	Load left into ac1 
 96:    DIV  3,4,3	Op / 
 97:     ST  3,-7(1)	Push parameter 
* Param end
 98:    LDA  1,-5(1)	Ghost frame becomes new active frame 
 99:    LDA  3,1(7)	 Return address in ac 
100:    JMP  7,-95(7)	CALL output
101:    LDA  3,0(2)	Save the result in ac 
* Call end output
* CALL output
* TOFF dec: -6
* TOFF dec: -7
* Param 1
* OpK
* OpK
102:    LDC  3,755(6)	  Load integer constant 
103:     ST  3,-7(1)	Save left side 
104:    LDC  3,88(6)	  Load integer constant 
105:     LD  4,-7(1)	Pop left into ac1 
106:    MUL  3,4,3	Op * 
107:     ST  3,-7(1)	Save left side 
* OpK
108:    LDC  3,3(6)	  Load integer constant 
109:     ST  3,-7(1)	Save left side 
110:    LDC  3,3(6)	  Load integer constant 
111:     LD  4,-7(1)	Pop left into ac1 
112:    MUL  3,4,3	Op * 
113:     LD  4,-7(1)	Pop left into ac1 
114:    ADD  3,4,3	Op + 
115:     ST  3,-7(1)	Push parameter 
* Param end
116:    LDA  1,-5(1)	Ghost frame becomes new active frame 
117:    LDA  3,1(7)	 Return address in ac 
118:    JMP  7,-113(7)	CALL output
119:    LDA  3,0(2)	Save the result in ac 
* Call end output
* CALL output
* TOFF dec: -6
* TOFF dec: -7
* Param 1
* OpK
* OpK
120:    LDC  3,755(6)	  Load integer constant 
121:     ST  3,-7(1)	Save left side 
122:    LDC  3,88(6)	  Load integer constant 
123:     LD  4,-7(1)	Load left into ac1 
124:    DIV  5,4,3	Op % 
125:    MUL  5,5,3	 
126:    SUB  3,4,5	 
127:     ST  3,-7(1)	Save left side 
128:    LDC  3,3(6)	  Load integer constant 
129:     LD  4,-7(1)	Load left into ac1 
130:    DIV  5,4,3	Op % 
131:    MUL  5,5,3	 
132:    SUB  3,4,5	 
133:     ST  3,-7(1)	Push parameter 
* Param end
134:    LDA  1,-5(1)	Ghost frame becomes new active frame 
135:    LDA  3,1(7)	 Return address in ac 
136:    JMP  7,-131(7)	CALL output
137:    LDA  3,0(2)	Save the result in ac 
* Call end output
* CALL output
* TOFF dec: -6
* TOFF dec: -7
* Param 1
* OpK
138:    LDC  3,755(6)	  Load integer constant 
139:    LDC  3,755(6)	  Load integer constant 
140:    NEG  3,3,3	Op Unary - 
141:     ST  3,-7(1)	Save left side 
* OpK
142:    LDC  3,88(6)	  Load integer constant 
143:     ST  3,-7(1)	Save left side 
144:    LDC  3,3(6)	  Load integer constant 
145:     LD  4,-7(1)	Pop left into ac1 
146:    MUL  3,4,3	Op * 
147:     LD  4,-7(1)	Pop left into ac1 
148:    ADD  3,4,3	Op + 
149:     ST  3,-7(1)	Push parameter 
* Param end
150:    LDA  1,-5(1)	Ghost frame becomes new active frame 
151:    LDA  3,1(7)	 Return address in ac 
152:    JMP  7,-147(7)	CALL output
153:    LDA  3,0(2)	Save the result in ac 
* Call end output
* CALL outnl
* Param end
154:    LDA  1,-5(1)	Ghost frame becomes new active frame 
155:    LDA  3,1(7)	 Return address in ac 
156:    JMP  7,-123(7)	CALL outnl
157:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* Compound Body
* TOFF set: -2
* END COMPOUND
* Add standard closing in case there is no return statement
158:    LDC  2,0(6)	Set return value to 0 
159:     LD  3,-1(1)	Load return address 
160:     LD  1,0(1)	Adjust fp 
161:    JMP  7,0(3)	Return 
* END FUNCTION main
  0:    JMP  7,161(7)	Jump to init [backpatch] 
* INIT
162:    LDA  1,0(0)	Set first frame at end of globals 
163:     ST  1,0(1)	Store old fp (point to self) 
* INIT GLOBALS AND STATICS
* END INIT GLOBALS AND STATICS
164:    LDA  3,1(7)	Return address in ac 
165:    JMP  7,-127(7)	Jump to main 
166:   HALT  0,0,0	Done! 
* END INIT
