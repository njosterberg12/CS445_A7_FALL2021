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
* EXPRESSION
* Assign
* EXPRESSION
 40:    LDC  3,755(6)	Load integer const 
* EXPRESSION
 41:     ST  3,-2(1)	Store variable x
* EXPRESSION
* Assign
* EXPRESSION
 42:    LDC  3,88(6)	Load integer const 
* EXPRESSION
 43:     ST  3,-3(1)	Store variable y
* EXPRESSION
* Assign
* EXPRESSION
 44:    LDC  3,3(6)	Load integer const 
* EXPRESSION
 45:     ST  3,-4(1)	Store variable z
* EXPRESSION
* CALL output
 46:     ST  1,-5(1)	Store fp in ghost frame for output
* TOFF dec: -6
* TOFF dec: -7
* Param
* EXPRESSION
* OpK
* EXPRESSION
 47:    LDC  3,755(6)	Load integer const 
 48:     ST  3,-7(1)	Push left side 
* EXPRESSION
* OpK
* EXPRESSION
 49:    LDC  3,88(6)	Load integer const 
 50:     ST  3,-7(1)	Push left side 
* EXPRESSION
 51:    LDC  3,3(6)	Load integer const 
 52:     LD  4,-7(1)	Pop left into ac1 
 53:    MUL  3,4,3	Op * 
 54:     LD  4,-7(1)	Pop left into ac1 
 55:    ADD  3,4,3	Op + 
 56:     ST  3,-7(1)	Push parameter 
* Param end
 57:    LDA  1,-5(1)	Ghost frame becomes new active frame 
 58:    LDA  3,1(7)	 Return address in ac 
 59:    JMP  7,-54(7)	CALL output
 60:    LDA  3,0(2)	Save the result in ac 
* Call end output
* EXPRESSION
* CALL output
 61:     ST  1,-5(1)	Store fp in ghost frame for output
* TOFF dec: -6
* TOFF dec: -7
* Param
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
 62:    LDC  3,755(6)	Load integer const 
 63:     ST  3,-7(1)	Push left side 
* EXPRESSION
 64:    LDC  3,88(6)	Load integer const 
 65:     LD  4,-7(1)	Pop left into ac1 
 66:    MUL  3,4,3	Op * 
 67:     ST  3,-7(1)	Push left side 
* EXPRESSION
 68:    LDC  3,3(6)	Load integer const 
 69:     LD  4,-7(1)	Pop left into ac1 
 70:    ADD  3,4,3	Op + 
 71:     ST  3,-7(1)	Push parameter 
* Param end
 72:    LDA  1,-5(1)	Ghost frame becomes new active frame 
 73:    LDA  3,1(7)	 Return address in ac 
 74:    JMP  7,-69(7)	CALL output
 75:    LDA  3,0(2)	Save the result in ac 
* Call end output
* EXPRESSION
* CALL output
 76:     ST  1,-5(1)	Store fp in ghost frame for output
* TOFF dec: -6
* TOFF dec: -7
* Param
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
 77:    LDC  3,755(6)	Load integer const 
 78:     ST  3,-7(1)	Push left side 
* EXPRESSION
 79:    LDC  3,88(6)	Load integer const 
 80:     LD  4,-7(1)	Load left into ac1 
 81:    SUB  3,4,3	Op - 
 82:     ST  3,-7(1)	Push left side 
* EXPRESSION
 83:    LDC  3,3(6)	Load integer const 
 84:     LD  4,-7(1)	Load left into ac1 
 85:    SUB  3,4,3	Op - 
 86:     ST  3,-7(1)	Push parameter 
* Param end
 87:    LDA  1,-5(1)	Ghost frame becomes new active frame 
 88:    LDA  3,1(7)	 Return address in ac 
 89:    JMP  7,-84(7)	CALL output
 90:    LDA  3,0(2)	Save the result in ac 
* Call end output
* EXPRESSION
* CALL output
 91:     ST  1,-5(1)	Store fp in ghost frame for output
* TOFF dec: -6
* TOFF dec: -7
* Param
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
 92:    LDC  3,755(6)	Load integer const 
 93:     ST  3,-7(1)	Push left side 
* EXPRESSION
 94:    LDC  3,88(6)	Load integer const 
 95:     LD  4,-7(1)	Load left into ac1 
 96:    DIV  3,4,3	Op / 
 97:     ST  3,-7(1)	Push left side 
* EXPRESSION
 98:    LDC  3,3(6)	Load integer const 
 99:     LD  4,-7(1)	Load left into ac1 
100:    DIV  3,4,3	Op / 
101:     ST  3,-7(1)	Push parameter 
* Param end
102:    LDA  1,-5(1)	Ghost frame becomes new active frame 
103:    LDA  3,1(7)	 Return address in ac 
104:    JMP  7,-99(7)	CALL output
105:    LDA  3,0(2)	Save the result in ac 
* Call end output
* EXPRESSION
* CALL output
106:     ST  1,-5(1)	Store fp in ghost frame for output
* TOFF dec: -6
* TOFF dec: -7
* Param
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
107:    LDC  3,755(6)	Load integer const 
108:     ST  3,-7(1)	Push left side 
* EXPRESSION
109:    LDC  3,88(6)	Load integer const 
110:     LD  4,-7(1)	Pop left into ac1 
111:    MUL  3,4,3	Op * 
112:     ST  3,-7(1)	Push left side 
* EXPRESSION
* OpK
* EXPRESSION
113:    LDC  3,3(6)	Load integer const 
114:     ST  3,-7(1)	Push left side 
* EXPRESSION
115:    LDC  3,3(6)	Load integer const 
116:     LD  4,-7(1)	Pop left into ac1 
117:    MUL  3,4,3	Op * 
118:     LD  4,-7(1)	Pop left into ac1 
119:    ADD  3,4,3	Op + 
120:     ST  3,-7(1)	Push parameter 
* Param end
121:    LDA  1,-5(1)	Ghost frame becomes new active frame 
122:    LDA  3,1(7)	 Return address in ac 
123:    JMP  7,-118(7)	CALL output
124:    LDA  3,0(2)	Save the result in ac 
* Call end output
* EXPRESSION
* CALL output
125:     ST  1,-5(1)	Store fp in ghost frame for output
* TOFF dec: -6
* TOFF dec: -7
* Param
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
126:    LDC  3,755(6)	Load integer const 
127:     ST  3,-7(1)	Push left side 
* EXPRESSION
128:    LDC  3,88(6)	Load integer const 
129:     LD  4,-7(1)	Load left into ac1 
130:    DIV  5,4,3	Op % 
131:    MUL  5,5,3	 
132:    SUB  3,4,5	 
133:     ST  3,-7(1)	Push left side 
* EXPRESSION
134:    LDC  3,3(6)	Load integer const 
135:     LD  4,-7(1)	Load left into ac1 
136:    DIV  5,4,3	Op % 
137:    MUL  5,5,3	 
138:    SUB  3,4,5	 
139:     ST  3,-7(1)	Push parameter 
* Param end
140:    LDA  1,-5(1)	Ghost frame becomes new active frame 
141:    LDA  3,1(7)	 Return address in ac 
142:    JMP  7,-137(7)	CALL output
143:    LDA  3,0(2)	Save the result in ac 
* Call end output
* EXPRESSION
* CALL output
144:     ST  1,-5(1)	Store fp in ghost frame for output
* TOFF dec: -6
* TOFF dec: -7
* Param
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
145:    LDC  3,755(6)	Load integer const 
* EXPRESSION
146:    LDC  3,755(6)	Load integer const 
147:    NEG  3,3,3	Op Unary - 
148:     ST  3,-7(1)	Push left side 
* EXPRESSION
* OpK
* EXPRESSION
149:    LDC  3,88(6)	Load integer const 
150:     ST  3,-7(1)	Push left side 
* EXPRESSION
151:    LDC  3,3(6)	Load integer const 
152:     LD  4,-7(1)	Pop left into ac1 
153:    MUL  3,4,3	Op * 
154:     LD  4,-7(1)	Pop left into ac1 
155:    ADD  3,4,3	Op + 
156:     ST  3,-7(1)	Push parameter 
* Param end
157:    LDA  1,-5(1)	Ghost frame becomes new active frame 
158:    LDA  3,1(7)	 Return address in ac 
159:    JMP  7,-154(7)	CALL output
160:    LDA  3,0(2)	Save the result in ac 
* Call end output
* EXPRESSION
* CALL outnl
161:     ST  1,-5(1)	Store fp in ghost frame for outnl
* Param end
162:    LDA  1,-5(1)	Ghost frame becomes new active frame 
163:    LDA  3,1(7)	 Return address in ac 
164:    JMP  7,-131(7)	CALL outnl
165:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* Compound Body
* TOFF set: -2
* END COMPOUND
* Add standard closing in case there is no return statement
166:    LDC  2,0(6)	Set return value to 0 
167:     LD  3,-1(1)	Load return address 
168:     LD  1,0(1)	Adjust fp 
169:    JMP  7,0(3)	Return 
* END FUNCTION main
  0:    JMP  7,169(7)	Jump to init [backpatch] 
* INIT
170:    LDA  1,0(0)	Set first frame at end of globals 
171:     ST  1,0(1)	Store old fp (point to self) 
* INIT GLOBALS AND STATICS
* END INIT GLOBALS AND STATICS
172:    LDA  3,1(7)	Return address in ac 
173:    JMP  7,-135(7)	Jump to main 
174:   HALT  0,0,0	Done! 
* END INIT
