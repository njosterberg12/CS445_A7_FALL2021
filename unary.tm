* C- compiler version C-F21
* Built: Dec 3, 2021
* Author: Nathaniel Osterberg
* File compiled:  unary.tm
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
* FUNCTION main
* TOFF set: -2
 39:     ST  3,-1(1)	Store return address 
* COMPOUND
* TOFF set: -2
* TOFF dec: -3
* TOFF dec: -4
 40:    LDC  3,7(6)	  load size of array a
 41:     ST  3,-4(1)	save size of array a
 42:    LDC  3,5(6)	  load size of array b
 43:     ST  3,-12(1)	save size of array b
* EXPRESSION
* Assign
* EXPRESSION
 44:    LDC  3,88(6)	Load integer const 
* EXPRESSION
 45:     ST  3,-2(1)	Store variable x
* EXPRESSION
* Assign
* EXPRESSION
* OpK
* EXPRESSION
 46:     LD  3,-2(1)	Load variable x
 47:     ST  3,-18(1)	Push left side 
* TOFF dec:///// -19
* EXPRESSION
 48:    LDC  3,9(6)	Load integer const 
* TOFF inc:///// -18
 49:     LD  4,-18(1)	Load left into ac1 
 50:    SUB  3,4,3	Op - 
* EXPRESSION
 51:     ST  3,-3(1)	Store variable y
* EXPRESSION
* Assign
* EXPRESSION
* EXPRESSION
 52:     LD  3,-2(1)	Load variable x
* EXPRESSION
 53:     LD  3,-2(1)	Load variable x
 54:    NEG  3,3,3	Op Unary - 
* EXPRESSION
 55:     ST  3,-3(1)	Store variable y
* EXPRESSION
* CALL output
 56:     ST  1,-18(1)	Store fp in ghost frame for output
* TOFF dec: -19
* TOFF dec: -20
* Param 1
* EXPRESSION
* EXPRESSION
 57:     LD  3,-2(1)	Load variable x
* EXPRESSION
 58:     LD  3,-2(1)	Load variable x
 59:    NEG  3,3,3	Op Unary - 
 60:     ST  3,-20(1)	Push parameter 
* Param end
 61:    LDA  1,-18(1)	Ghost frame becomes new active frame 
 62:    LDA  3,1(7)	  Return address in ac 
 63:    JMP  7,-58(7)	CALL output
 64:    LDA  3,0(2)	  Save the result in ac 
* Call end output
* EXPRESSION
* CALL output
 65:     ST  1,-18(1)	Store fp in ghost frame for output
* TOFF dec: -19
* TOFF dec: -20
* Param 1
* EXPRESSION
 66:     LD  3,-3(1)	Load variable y
 67:     ST  3,-20(1)	Push parameter 
* Param end
 68:    LDA  1,-18(1)	Ghost frame becomes new active frame 
 69:    LDA  3,1(7)	  Return address in ac 
 70:    JMP  7,-65(7)	CALL output
 71:    LDA  3,0(2)	  Save the result in ac 
* Call end output
* EXPRESSION
* CALL outnl
 72:     ST  1,-18(1)	Store fp in ghost frame for outnl
* Param end
 73:    LDA  1,-18(1)	Ghost frame becomes new active frame 
 74:    LDA  3,1(7)	  Return address in ac 
 75:    JMP  7,-42(7)	CALL outnl
 76:    LDA  3,0(2)	  Save the result in ac 
* Call end outnl
* EXPRESSION
* CALL output
 77:     ST  1,-18(1)	Store fp in ghost frame for output
* TOFF dec: -19
* TOFF dec: -20
* Param 1
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
* EXPRESSION
 78:    LDC  3,3(6)	Load integer const 
* EXPRESSION
 79:    LDC  3,3(6)	Load integer const 
 80:    NEG  3,3,3	Op Unary - 
* EXPRESSION
* EXPRESSION
 81:    LDC  3,3(6)	Load integer const 
* EXPRESSION
 82:    LDC  3,3(6)	Load integer const 
 83:    NEG  3,3,3	Op Unary - 
 84:    NEG  3,3,3	Op Unary - 
 85:     ST  3,-20(1)	Push left side 
* TOFF dec://// -21
* EXPRESSION
* EXPRESSION
 86:    LDC  3,5(6)	Load integer const 
* EXPRESSION
 87:    LDC  3,5(6)	Load integer const 
 88:    NEG  3,3,3	Op Unary - 
* TOFF inc:///// -20
 89:     LD  4,-20(1)	Pop left into ac1 
 90:    MUL  3,4,3	Op * 
 91:     ST  3,-20(1)	Push parameter 
* Param end
 92:    LDA  1,-18(1)	Ghost frame becomes new active frame 
 93:    LDA  3,1(7)	  Return address in ac 
 94:    JMP  7,-89(7)	CALL output
 95:    LDA  3,0(2)	  Save the result in ac 
* Call end output
* EXPRESSION
* CALL output
 96:     ST  1,-18(1)	Store fp in ghost frame for output
* TOFF dec: -19
* TOFF dec: -20
* Param 1
* EXPRESSION
* EXPRESSION
* EXPRESSION
 97:    LDC  3,3(6)	Load integer const 
* EXPRESSION
 98:    LDC  3,3(6)	Load integer const 
 99:    NEG  3,3,3	Op Unary - 
* EXPRESSION
* EXPRESSION
100:    LDC  3,3(6)	Load integer const 
* EXPRESSION
101:    LDC  3,3(6)	Load integer const 
102:    NEG  3,3,3	Op Unary - 
103:    NEG  3,3,3	Op Unary - 
104:     ST  3,-20(1)	Push parameter 
* Param end
105:    LDA  1,-18(1)	Ghost frame becomes new active frame 
106:    LDA  3,1(7)	  Return address in ac 
107:    JMP  7,-102(7)	CALL output
108:    LDA  3,0(2)	  Save the result in ac 
* Call end output
* EXPRESSION
* CALL outnl
109:     ST  1,-18(1)	Store fp in ghost frame for outnl
* Param end
110:    LDA  1,-18(1)	Ghost frame becomes new active frame 
111:    LDA  3,1(7)	  Return address in ac 
112:    JMP  7,-79(7)	CALL outnl
113:    LDA  3,0(2)	  Save the result in ac 
* Call end outnl
* COMPOUND
* TOFF set: -18
* TOFF dec: -19
* TOFF dec: -20
* EXPRESSION
* Assign
* EXPRESSION
114:    LDC  3,1(6)	Load boolean const 
* EXPRESSION
115:     ST  3,-18(1)	Store variable x
* EXPRESSION
* Assign
* EXPRESSION
* EXPRESSION
116:     LD  3,-18(1)	Load variable x
* EXPRESSION
117:     LD  3,-18(1)	Load variable x
118:    LDC  4,1(6)	Load 1 
119:    XOR  3,3,4	Op NOT 
* EXPRESSION
120:     ST  3,-19(1)	Store variable y
* EXPRESSION
* CALL outputb
121:     ST  1,-20(1)	Store fp in ghost frame for outputb
* TOFF dec: -21
* TOFF dec: -22
* Param 1
* EXPRESSION
* EXPRESSION
122:     LD  3,-18(1)	Load variable x
* EXPRESSION
123:     LD  3,-18(1)	Load variable x
124:    LDC  4,1(6)	Load 1 
125:    XOR  3,3,4	Op NOT 
126:     ST  3,-22(1)	Push parameter 
* Param end
127:    LDA  1,-20(1)	Ghost frame becomes new active frame 
128:    LDA  3,1(7)	  Return address in ac 
129:    JMP  7,-113(7)	CALL outputb
130:    LDA  3,0(2)	  Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outputb
131:     ST  1,-20(1)	Store fp in ghost frame for outputb
* TOFF dec: -21
* TOFF dec: -22
* Param 1
* EXPRESSION
132:     LD  3,-19(1)	Load variable y
133:     ST  3,-22(1)	Push parameter 
* Param end
134:    LDA  1,-20(1)	Ghost frame becomes new active frame 
135:    LDA  3,1(7)	  Return address in ac 
136:    JMP  7,-120(7)	CALL outputb
137:    LDA  3,0(2)	  Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outputb
138:     ST  1,-20(1)	Store fp in ghost frame for outputb
* TOFF dec: -21
* TOFF dec: -22
* Param 1
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
* EXPRESSION
139:     LD  3,-18(1)	Load variable x
* EXPRESSION
140:     LD  3,-18(1)	Load variable x
141:    LDC  4,1(6)	Load 1 
142:    XOR  3,3,4	Op NOT 
* EXPRESSION
* EXPRESSION
143:     LD  3,-18(1)	Load variable x
* EXPRESSION
144:     LD  3,-18(1)	Load variable x
145:    LDC  4,1(6)	Load 1 
146:    XOR  3,3,4	Op NOT 
147:    LDC  4,1(6)	Load 1 
148:    XOR  3,3,4	Op NOT 
149:     ST  3,-22(1)	Push left side 
* TOFF dec:///// -23
* EXPRESSION
* EXPRESSION
150:     LD  3,-19(1)	Load variable y
* EXPRESSION
151:     LD  3,-19(1)	Load variable y
152:    LDC  4,1(6)	Load 1 
153:    XOR  3,3,4	Op NOT 
* TOFF inc:///// -22
154:     LD  4,-22(1)	Load left into ac1 
155:    AND  3,4,3	Op and 
156:     ST  3,-22(1)	Push parameter 
* Param end
157:    LDA  1,-20(1)	Ghost frame becomes new active frame 
158:    LDA  3,1(7)	  Return address in ac 
159:    JMP  7,-143(7)	CALL outputb
160:    LDA  3,0(2)	  Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outputb
161:     ST  1,-20(1)	Store fp in ghost frame for outputb
* TOFF dec: -21
* TOFF dec: -22
* Param 1
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
* EXPRESSION
162:     LD  3,-18(1)	Load variable x
* EXPRESSION
163:     LD  3,-18(1)	Load variable x
164:    LDC  4,1(6)	Load 1 
165:    XOR  3,3,4	Op NOT 
* EXPRESSION
* EXPRESSION
166:     LD  3,-18(1)	Load variable x
* EXPRESSION
167:     LD  3,-18(1)	Load variable x
168:    LDC  4,1(6)	Load 1 
169:    XOR  3,3,4	Op NOT 
170:    LDC  4,1(6)	Load 1 
171:    XOR  3,3,4	Op NOT 
172:     ST  3,-22(1)	Push left side 
* TOFF dec:///// -23
* EXPRESSION
* EXPRESSION
173:     LD  3,-19(1)	Load variable y
* EXPRESSION
174:     LD  3,-19(1)	Load variable y
175:    LDC  4,1(6)	Load 1 
176:    XOR  3,3,4	Op NOT 
* TOFF inc:///// -22
177:     LD  4,-22(1)	Load left into ac1 
178:     OR  3,4,3	Op or 
179:     ST  3,-22(1)	Push parameter 
* Param end
180:    LDA  1,-20(1)	Ghost frame becomes new active frame 
181:    LDA  3,1(7)	  Return address in ac 
182:    JMP  7,-166(7)	CALL outputb
183:    LDA  3,0(2)	  Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outputb
184:     ST  1,-20(1)	Store fp in ghost frame for outputb
* TOFF dec: -21
* TOFF dec: -22
* Param 1
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
* EXPRESSION
185:     LD  3,-19(1)	Load variable y
* EXPRESSION
186:     LD  3,-19(1)	Load variable y
187:    LDC  4,1(6)	Load 1 
188:    XOR  3,3,4	Op NOT 
* EXPRESSION
* EXPRESSION
189:     LD  3,-19(1)	Load variable y
* EXPRESSION
190:     LD  3,-19(1)	Load variable y
191:    LDC  4,1(6)	Load 1 
192:    XOR  3,3,4	Op NOT 
193:    LDC  4,1(6)	Load 1 
194:    XOR  3,3,4	Op NOT 
195:     ST  3,-22(1)	Push left side 
* TOFF dec:///// -23
* EXPRESSION
* EXPRESSION
196:     LD  3,-18(1)	Load variable x
* EXPRESSION
197:     LD  3,-18(1)	Load variable x
198:    LDC  4,1(6)	Load 1 
199:    XOR  3,3,4	Op NOT 
* TOFF inc:///// -22
200:     LD  4,-22(1)	Load left into ac1 
201:     OR  3,4,3	Op or 
202:     ST  3,-22(1)	Push parameter 
* Param end
203:    LDA  1,-20(1)	Ghost frame becomes new active frame 
204:    LDA  3,1(7)	  Return address in ac 
205:    JMP  7,-189(7)	CALL outputb
206:    LDA  3,0(2)	  Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outputb
207:     ST  1,-20(1)	Store fp in ghost frame for outputb
* TOFF dec: -21
* TOFF dec: -22
* Param 1
* EXPRESSION
* EXPRESSION
* EXPRESSION
208:     LD  3,-18(1)	Load variable x
* EXPRESSION
209:     LD  3,-18(1)	Load variable x
210:    LDC  4,1(6)	Load 1 
211:    XOR  3,3,4	Op NOT 
* EXPRESSION
* EXPRESSION
212:     LD  3,-18(1)	Load variable x
* EXPRESSION
213:     LD  3,-18(1)	Load variable x
214:    LDC  4,1(6)	Load 1 
215:    XOR  3,3,4	Op NOT 
216:    LDC  4,1(6)	Load 1 
217:    XOR  3,3,4	Op NOT 
218:     ST  3,-22(1)	Push parameter 
* Param end
219:    LDA  1,-20(1)	Ghost frame becomes new active frame 
220:    LDA  3,1(7)	  Return address in ac 
221:    JMP  7,-205(7)	CALL outputb
222:    LDA  3,0(2)	  Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outnl
223:     ST  1,-20(1)	Store fp in ghost frame for outnl
* Param end
224:    LDA  1,-20(1)	Ghost frame becomes new active frame 
225:    LDA  3,1(7)	  Return address in ac 
226:    JMP  7,-193(7)	CALL outnl
227:    LDA  3,0(2)	  Save the result in ac 
* Call end outnl
* Compound Body
* TOFF set: -18
* END COMPOUND
* EXPRESSION
* CALL output
228:     ST  1,-18(1)	Store fp in ghost frame for output
* TOFF dec: -19
* TOFF dec: -20
* Param 1
* EXPRESSION
* EXPRESSION
229:    LDA  3,0(1)	Load address of base of array *
230:     LD  3,1(3)	Load array size 
231:     ST  3,-20(1)	Push parameter 
* Param end
232:    LDA  1,-18(1)	Ghost frame becomes new active frame 
233:    LDA  3,1(7)	  Return address in ac 
234:    JMP  7,-229(7)	CALL output
235:    LDA  3,0(2)	  Save the result in ac 
* Call end output
* EXPRESSION
* CALL output
236:     ST  1,-18(1)	Store fp in ghost frame for output
* TOFF dec: -19
* TOFF dec: -20
* Param 1
* EXPRESSION
* EXPRESSION
237:    LDA  3,0(1)	Load address of base of array *
238:     LD  3,1(3)	Load array size 
239:     ST  3,-20(1)	Push parameter 
* Param end
240:    LDA  1,-18(1)	Ghost frame becomes new active frame 
241:    LDA  3,1(7)	  Return address in ac 
242:    JMP  7,-237(7)	CALL output
243:    LDA  3,0(2)	  Save the result in ac 
* Call end output
* Compound Body
* TOFF set: -2
* END COMPOUND
* Add standard closing in case there is no return statement
244:    LDC  2,0(6)	Set return value to 0 
245:     LD  3,-1(1)	Load return address 
246:     LD  1,0(1)	Adjust fp 
247:    JMP  7,0(3)	Return 
* END FUNCTION main
  0:    JMP  7,247(7)	Jump to init [backpatch] 
* INIT
248:    LDA  1,0(0)	Set first frame at end of globals 
249:     ST  1,0(1)	Store old fp (point to self) 
* INIT GLOBALS AND STATICS
* END INIT GLOBALS AND STATICS
250:    LDA  3,1(7)	Return address in ac 
251:    JMP  7,-213(7)	Jump to main 
252:   HALT  0,0,0	Done! 
* END INIT
