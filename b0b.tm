* C- compiler version C-F21
* Built: Dec 3, 2021
* Author: Nathaniel Osterberg
* File compiled:  b0b.tm
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
* EXPRESSION
* CALL outputb
 40:     ST  1,-2(1)	Store fp in ghost frame for outputb
* TOFF dec: -3
* TOFF dec: -4
* Param
* EXPRESSION
* OpK
* EXPRESSION
 41:    LDC  3,0(6)	Load boolean const 
 42:     ST  3,-4(1)	Save left side 
* EXPRESSION
 43:    LDC  3,0(6)	Load boolean const 
 44:     LD  4,-4(1)	Load left into ac1 
 45:     OR  3,4,3	Op or 
 46:     ST  3,-4(1)	Push parameter 
* Param end
 47:    LDA  1,-2(1)	Ghost frame becomes new active frame 
 48:    LDA  3,1(7)	 Return address in ac 
 49:    JMP  7,-33(7)	CALL outputb
 50:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outputb
 51:     ST  1,-2(1)	Store fp in ghost frame for outputb
* TOFF dec: -3
* TOFF dec: -4
* Param
* EXPRESSION
* OpK
* EXPRESSION
 52:    LDC  3,0(6)	Load boolean const 
 53:     ST  3,-4(1)	Save left side 
* EXPRESSION
 54:    LDC  3,1(6)	Load boolean const 
 55:     LD  4,-4(1)	Load left into ac1 
 56:     OR  3,4,3	Op or 
 57:     ST  3,-4(1)	Push parameter 
* Param end
 58:    LDA  1,-2(1)	Ghost frame becomes new active frame 
 59:    LDA  3,1(7)	 Return address in ac 
 60:    JMP  7,-44(7)	CALL outputb
 61:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outputb
 62:     ST  1,-2(1)	Store fp in ghost frame for outputb
* TOFF dec: -3
* TOFF dec: -4
* Param
* EXPRESSION
* OpK
* EXPRESSION
 63:    LDC  3,1(6)	Load boolean const 
 64:     ST  3,-4(1)	Save left side 
* EXPRESSION
 65:    LDC  3,0(6)	Load boolean const 
 66:     LD  4,-4(1)	Load left into ac1 
 67:     OR  3,4,3	Op or 
 68:     ST  3,-4(1)	Push parameter 
* Param end
 69:    LDA  1,-2(1)	Ghost frame becomes new active frame 
 70:    LDA  3,1(7)	 Return address in ac 
 71:    JMP  7,-55(7)	CALL outputb
 72:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outputb
 73:     ST  1,-2(1)	Store fp in ghost frame for outputb
* TOFF dec: -3
* TOFF dec: -4
* Param
* EXPRESSION
* OpK
* EXPRESSION
 74:    LDC  3,1(6)	Load boolean const 
 75:     ST  3,-4(1)	Save left side 
* EXPRESSION
 76:    LDC  3,1(6)	Load boolean const 
 77:     LD  4,-4(1)	Load left into ac1 
 78:     OR  3,4,3	Op or 
 79:     ST  3,-4(1)	Push parameter 
* Param end
 80:    LDA  1,-2(1)	Ghost frame becomes new active frame 
 81:    LDA  3,1(7)	 Return address in ac 
 82:    JMP  7,-66(7)	CALL outputb
 83:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outnl
 84:     ST  1,-2(1)	Store fp in ghost frame for outnl
* Param end
 85:    LDA  1,-2(1)	Ghost frame becomes new active frame 
 86:    LDA  3,1(7)	 Return address in ac 
 87:    JMP  7,-54(7)	CALL outnl
 88:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* EXPRESSION
* CALL outputb
 89:     ST  1,-2(1)	Store fp in ghost frame for outputb
* TOFF dec: -3
* TOFF dec: -4
* Param
* EXPRESSION
* OpK
* EXPRESSION
 90:    LDC  3,0(6)	Load boolean const 
 91:     ST  3,-4(1)	Save left side 
* EXPRESSION
 92:    LDC  3,0(6)	Load boolean const 
 93:     LD  4,-4(1)	Load left into ac1 
 94:    AND  3,4,3	Op and 
 95:     ST  3,-4(1)	Push parameter 
* Param end
 96:    LDA  1,-2(1)	Ghost frame becomes new active frame 
 97:    LDA  3,1(7)	 Return address in ac 
 98:    JMP  7,-82(7)	CALL outputb
 99:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outputb
100:     ST  1,-2(1)	Store fp in ghost frame for outputb
* TOFF dec: -3
* TOFF dec: -4
* Param
* EXPRESSION
* OpK
* EXPRESSION
101:    LDC  3,0(6)	Load boolean const 
102:     ST  3,-4(1)	Save left side 
* EXPRESSION
103:    LDC  3,1(6)	Load boolean const 
104:     LD  4,-4(1)	Load left into ac1 
105:    AND  3,4,3	Op and 
106:     ST  3,-4(1)	Push parameter 
* Param end
107:    LDA  1,-2(1)	Ghost frame becomes new active frame 
108:    LDA  3,1(7)	 Return address in ac 
109:    JMP  7,-93(7)	CALL outputb
110:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outputb
111:     ST  1,-2(1)	Store fp in ghost frame for outputb
* TOFF dec: -3
* TOFF dec: -4
* Param
* EXPRESSION
* OpK
* EXPRESSION
112:    LDC  3,1(6)	Load boolean const 
113:     ST  3,-4(1)	Save left side 
* EXPRESSION
114:    LDC  3,0(6)	Load boolean const 
115:     LD  4,-4(1)	Load left into ac1 
116:    AND  3,4,3	Op and 
117:     ST  3,-4(1)	Push parameter 
* Param end
118:    LDA  1,-2(1)	Ghost frame becomes new active frame 
119:    LDA  3,1(7)	 Return address in ac 
120:    JMP  7,-104(7)	CALL outputb
121:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outputb
122:     ST  1,-2(1)	Store fp in ghost frame for outputb
* TOFF dec: -3
* TOFF dec: -4
* Param
* EXPRESSION
* OpK
* EXPRESSION
123:    LDC  3,1(6)	Load boolean const 
124:     ST  3,-4(1)	Save left side 
* EXPRESSION
125:    LDC  3,1(6)	Load boolean const 
126:     LD  4,-4(1)	Load left into ac1 
127:    AND  3,4,3	Op and 
128:     ST  3,-4(1)	Push parameter 
* Param end
129:    LDA  1,-2(1)	Ghost frame becomes new active frame 
130:    LDA  3,1(7)	 Return address in ac 
131:    JMP  7,-115(7)	CALL outputb
132:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outnl
133:     ST  1,-2(1)	Store fp in ghost frame for outnl
* Param end
134:    LDA  1,-2(1)	Ghost frame becomes new active frame 
135:    LDA  3,1(7)	 Return address in ac 
136:    JMP  7,-103(7)	CALL outnl
137:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* EXPRESSION
* CALL outputb
138:     ST  1,-2(1)	Store fp in ghost frame for outputb
* TOFF dec: -3
* TOFF dec: -4
* Param
* EXPRESSION
* EXPRESSION
139:    LDC  3,0(6)	Load boolean const 
140:    LDC  4,1(6)	Load 1 
141:    XOR  3,3,4	Op NOT 
142:     ST  3,-4(1)	Push parameter 
* Param end
143:    LDA  1,-2(1)	Ghost frame becomes new active frame 
144:    LDA  3,1(7)	 Return address in ac 
145:    JMP  7,-129(7)	CALL outputb
146:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outputb
147:     ST  1,-2(1)	Store fp in ghost frame for outputb
* TOFF dec: -3
* TOFF dec: -4
* Param
* EXPRESSION
* EXPRESSION
148:    LDC  3,1(6)	Load boolean const 
149:    LDC  4,1(6)	Load 1 
150:    XOR  3,3,4	Op NOT 
151:     ST  3,-4(1)	Push parameter 
* Param end
152:    LDA  1,-2(1)	Ghost frame becomes new active frame 
153:    LDA  3,1(7)	 Return address in ac 
154:    JMP  7,-138(7)	CALL outputb
155:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outnl
156:     ST  1,-2(1)	Store fp in ghost frame for outnl
* Param end
157:    LDA  1,-2(1)	Ghost frame becomes new active frame 
158:    LDA  3,1(7)	 Return address in ac 
159:    JMP  7,-126(7)	CALL outnl
160:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -2
* END COMPOUND
* Add standard closing in case there is no return statement
161:    LDC  2,0(6)	Set return value to 0 
162:     LD  3,-1(1)	Load return address 
163:     LD  1,0(1)	Adjust fp 
164:    JMP  7,0(3)	Return 
* END FUNCTION main
  0:    JMP  7,164(7)	Jump to init [backpatch] 
* INIT
165:    LDA  1,0(0)	Set first frame at end of globals 
166:     ST  1,0(1)	Store old fp (point to self) 
* INIT GLOBALS AND STATICS
* END INIT GLOBALS AND STATICS
167:    LDA  3,1(7)	Return address in ac 
168:    JMP  7,-130(7)	Jump to main 
169:   HALT  0,0,0	Done! 
* END INIT
