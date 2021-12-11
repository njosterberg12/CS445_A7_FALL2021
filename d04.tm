* C- compiler version C-F21
* Built: Dec 3, 2021
* Author: Nathaniel Osterberg
* File compiled:  d04.tm
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
* TOFF dec: -5
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
* Assign
* EXPRESSION
 44:    LDC  3,1(6)	Load boolean const 
* EXPRESSION
 45:     ST  3,-4(1)	Store variable z
* EXPRESSION
* CALL outputb
 46:     ST  1,-5(1)	Store fp in ghost frame for outputb
* TOFF dec: -6
* TOFF dec: -7
* Param
* EXPRESSION
* OpK
* EXPRESSION
 47:     LD  3,-2(1)	Load variable x
 48:     ST  3,-7(1)	Push left side 
* EXPRESSION
* OpK
* EXPRESSION
 49:     LD  3,-3(1)	Load variable y
 50:     ST  3,-7(1)	Push left side 
* EXPRESSION
 51:     LD  3,-4(1)	Load variable z
 52:     LD  4,-7(1)	Load left into ac1 
 53:    AND  3,4,3	Op and 
 54:     LD  4,-7(1)	Load left into ac1 
 55:     OR  3,4,3	Op or 
 56:     ST  3,-7(1)	Push parameter 
* Param end
 57:    LDA  1,-5(1)	Ghost frame becomes new active frame 
 58:    LDA  3,1(7)	  Return address in ac 
 59:    JMP  7,-43(7)	CALL outputb
 60:    LDA  3,0(2)	  Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outputb
 61:     ST  1,-5(1)	Store fp in ghost frame for outputb
* TOFF dec: -6
* TOFF dec: -7
* Param
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
 62:     LD  3,-2(1)	Load variable x
 63:     ST  3,-7(1)	Push left side 
* EXPRESSION
 64:     LD  3,-3(1)	Load variable y
 65:     LD  4,-7(1)	Load left into ac1 
 66:    AND  3,4,3	Op and 
 67:     ST  3,-7(1)	Push left side 
* EXPRESSION
 68:     LD  3,-4(1)	Load variable z
 69:     LD  4,-7(1)	Load left into ac1 
 70:     OR  3,4,3	Op or 
 71:     ST  3,-7(1)	Push parameter 
* Param end
 72:    LDA  1,-5(1)	Ghost frame becomes new active frame 
 73:    LDA  3,1(7)	  Return address in ac 
 74:    JMP  7,-58(7)	CALL outputb
 75:    LDA  3,0(2)	  Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outputb
 76:     ST  1,-5(1)	Store fp in ghost frame for outputb
* TOFF dec: -6
* TOFF dec: -7
* Param
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
 77:     LD  3,-2(1)	Load variable x
 78:     ST  3,-7(1)	Push left side 
* EXPRESSION
 79:     LD  3,-3(1)	Load variable y
 80:     LD  4,-7(1)	Load left into ac1 
 81:    AND  3,4,3	Op and 
 82:     ST  3,-7(1)	Push left side 
* EXPRESSION
* OpK
* EXPRESSION
 83:     LD  3,-4(1)	Load variable z
 84:     ST  3,-7(1)	Push left side 
* EXPRESSION
 85:     LD  3,-4(1)	Load variable z
 86:     LD  4,-7(1)	Load left into ac1 
 87:    AND  3,4,3	Op and 
 88:     LD  4,-7(1)	Load left into ac1 
 89:     OR  3,4,3	Op or 
 90:     ST  3,-7(1)	Push parameter 
* Param end
 91:    LDA  1,-5(1)	Ghost frame becomes new active frame 
 92:    LDA  3,1(7)	  Return address in ac 
 93:    JMP  7,-77(7)	CALL outputb
 94:    LDA  3,0(2)	  Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outputb
 95:     ST  1,-5(1)	Store fp in ghost frame for outputb
* TOFF dec: -6
* TOFF dec: -7
* Param
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
 96:     LD  3,-2(1)	Load variable x
* EXPRESSION
 97:     LD  3,-2(1)	Load variable x
 98:    LDC  4,1(6)	Load 1 
 99:    XOR  3,3,4	Op NOT 
100:     ST  3,-7(1)	Push left side 
* EXPRESSION
* OpK
* EXPRESSION
101:     LD  3,-3(1)	Load variable y
102:     ST  3,-7(1)	Push left side 
* EXPRESSION
103:     LD  3,-4(1)	Load variable z
104:     LD  4,-7(1)	Load left into ac1 
105:    AND  3,4,3	Op and 
106:     LD  4,-7(1)	Load left into ac1 
107:     OR  3,4,3	Op or 
108:     ST  3,-7(1)	Push parameter 
* Param end
109:    LDA  1,-5(1)	Ghost frame becomes new active frame 
110:    LDA  3,1(7)	  Return address in ac 
111:    JMP  7,-95(7)	CALL outputb
112:    LDA  3,0(2)	  Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outputb
113:     ST  1,-5(1)	Store fp in ghost frame for outputb
* TOFF dec: -6
* TOFF dec: -7
* Param
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
114:     LD  3,-2(1)	Load variable x
* EXPRESSION
115:     LD  3,-2(1)	Load variable x
116:    LDC  4,1(6)	Load 1 
117:    XOR  3,3,4	Op NOT 
118:     ST  3,-7(1)	Push left side 
* EXPRESSION
119:     LD  3,-3(1)	Load variable y
120:     LD  4,-7(1)	Load left into ac1 
121:    AND  3,4,3	Op and 
122:     ST  3,-7(1)	Push left side 
* EXPRESSION
123:     LD  3,-4(1)	Load variable z
124:     LD  4,-7(1)	Load left into ac1 
125:     OR  3,4,3	Op or 
126:     ST  3,-7(1)	Push parameter 
* Param end
127:    LDA  1,-5(1)	Ghost frame becomes new active frame 
128:    LDA  3,1(7)	  Return address in ac 
129:    JMP  7,-113(7)	CALL outputb
130:    LDA  3,0(2)	  Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outnl
131:     ST  1,-5(1)	Store fp in ghost frame for outnl
* TOFF dec: -6
* TOFF dec: -7
* Param end
132:    LDA  1,-5(1)	Ghost frame becomes new active frame 
133:    LDA  3,1(7)	  Return address in ac 
134:    JMP  7,-101(7)	CALL outnl
135:    LDA  3,0(2)	  Save the result in ac 
* Call end outnl
* EXPRESSION
* Assign
* EXPRESSION
136:    LDC  3,1(6)	Load boolean const 
* EXPRESSION
137:     ST  3,-2(1)	Store variable x
* EXPRESSION
* Assign
* EXPRESSION
138:    LDC  3,1(6)	Load boolean const 
* EXPRESSION
139:     ST  3,-3(1)	Store variable y
* EXPRESSION
* Assign
* EXPRESSION
140:    LDC  3,0(6)	Load boolean const 
* EXPRESSION
141:     ST  3,-4(1)	Store variable z
* EXPRESSION
* CALL outputb
142:     ST  1,-5(1)	Store fp in ghost frame for outputb
* TOFF dec: -6
* TOFF dec: -7
* Param
* EXPRESSION
* OpK
* EXPRESSION
143:     LD  3,-2(1)	Load variable x
144:     ST  3,-7(1)	Push left side 
* EXPRESSION
* OpK
* EXPRESSION
145:     LD  3,-3(1)	Load variable y
146:     ST  3,-7(1)	Push left side 
* EXPRESSION
147:     LD  3,-4(1)	Load variable z
148:     LD  4,-7(1)	Load left into ac1 
149:    AND  3,4,3	Op and 
150:     LD  4,-7(1)	Load left into ac1 
151:     OR  3,4,3	Op or 
152:     ST  3,-7(1)	Push parameter 
* Param end
153:    LDA  1,-5(1)	Ghost frame becomes new active frame 
154:    LDA  3,1(7)	  Return address in ac 
155:    JMP  7,-139(7)	CALL outputb
156:    LDA  3,0(2)	  Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outputb
157:     ST  1,-5(1)	Store fp in ghost frame for outputb
* TOFF dec: -6
* TOFF dec: -7
* Param
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
158:     LD  3,-2(1)	Load variable x
159:     ST  3,-7(1)	Push left side 
* EXPRESSION
160:     LD  3,-3(1)	Load variable y
161:     LD  4,-7(1)	Load left into ac1 
162:    AND  3,4,3	Op and 
163:     ST  3,-7(1)	Push left side 
* EXPRESSION
164:     LD  3,-4(1)	Load variable z
165:     LD  4,-7(1)	Load left into ac1 
166:     OR  3,4,3	Op or 
167:     ST  3,-7(1)	Push parameter 
* Param end
168:    LDA  1,-5(1)	Ghost frame becomes new active frame 
169:    LDA  3,1(7)	  Return address in ac 
170:    JMP  7,-154(7)	CALL outputb
171:    LDA  3,0(2)	  Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outputb
172:     ST  1,-5(1)	Store fp in ghost frame for outputb
* TOFF dec: -6
* TOFF dec: -7
* Param
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
173:     LD  3,-2(1)	Load variable x
174:     ST  3,-7(1)	Push left side 
* EXPRESSION
175:     LD  3,-3(1)	Load variable y
176:     LD  4,-7(1)	Load left into ac1 
177:    AND  3,4,3	Op and 
178:     ST  3,-7(1)	Push left side 
* EXPRESSION
* OpK
* EXPRESSION
179:     LD  3,-4(1)	Load variable z
180:     ST  3,-7(1)	Push left side 
* EXPRESSION
181:     LD  3,-4(1)	Load variable z
182:     LD  4,-7(1)	Load left into ac1 
183:    AND  3,4,3	Op and 
184:     LD  4,-7(1)	Load left into ac1 
185:     OR  3,4,3	Op or 
186:     ST  3,-7(1)	Push parameter 
* Param end
187:    LDA  1,-5(1)	Ghost frame becomes new active frame 
188:    LDA  3,1(7)	  Return address in ac 
189:    JMP  7,-173(7)	CALL outputb
190:    LDA  3,0(2)	  Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outputb
191:     ST  1,-5(1)	Store fp in ghost frame for outputb
* TOFF dec: -6
* TOFF dec: -7
* Param
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
192:     LD  3,-2(1)	Load variable x
* EXPRESSION
193:     LD  3,-2(1)	Load variable x
194:    LDC  4,1(6)	Load 1 
195:    XOR  3,3,4	Op NOT 
196:     ST  3,-7(1)	Push left side 
* EXPRESSION
* OpK
* EXPRESSION
197:     LD  3,-3(1)	Load variable y
198:     ST  3,-7(1)	Push left side 
* EXPRESSION
199:     LD  3,-4(1)	Load variable z
200:     LD  4,-7(1)	Load left into ac1 
201:    AND  3,4,3	Op and 
202:     LD  4,-7(1)	Load left into ac1 
203:     OR  3,4,3	Op or 
204:     ST  3,-7(1)	Push parameter 
* Param end
205:    LDA  1,-5(1)	Ghost frame becomes new active frame 
206:    LDA  3,1(7)	  Return address in ac 
207:    JMP  7,-191(7)	CALL outputb
208:    LDA  3,0(2)	  Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outputb
209:     ST  1,-5(1)	Store fp in ghost frame for outputb
* TOFF dec: -6
* TOFF dec: -7
* Param
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
210:     LD  3,-2(1)	Load variable x
* EXPRESSION
211:     LD  3,-2(1)	Load variable x
212:    LDC  4,1(6)	Load 1 
213:    XOR  3,3,4	Op NOT 
214:     ST  3,-7(1)	Push left side 
* EXPRESSION
215:     LD  3,-3(1)	Load variable y
216:     LD  4,-7(1)	Load left into ac1 
217:    AND  3,4,3	Op and 
218:     ST  3,-7(1)	Push left side 
* EXPRESSION
219:     LD  3,-4(1)	Load variable z
220:     LD  4,-7(1)	Load left into ac1 
221:     OR  3,4,3	Op or 
222:     ST  3,-7(1)	Push parameter 
* Param end
223:    LDA  1,-5(1)	Ghost frame becomes new active frame 
224:    LDA  3,1(7)	  Return address in ac 
225:    JMP  7,-209(7)	CALL outputb
226:    LDA  3,0(2)	  Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outnl
227:     ST  1,-5(1)	Store fp in ghost frame for outnl
* TOFF dec: -6
* TOFF dec: -7
* Param end
228:    LDA  1,-5(1)	Ghost frame becomes new active frame 
229:    LDA  3,1(7)	  Return address in ac 
230:    JMP  7,-197(7)	CALL outnl
231:    LDA  3,0(2)	  Save the result in ac 
* Call end outnl
* Compound Body
* TOFF set: -2
* END COMPOUND
* Add standard closing in case there is no return statement
232:    LDC  2,0(6)	Set return value to 0 
233:     LD  3,-1(1)	Load return address 
234:     LD  1,0(1)	Adjust fp 
235:    JMP  7,0(3)	Return 
* END FUNCTION main
  0:    JMP  7,235(7)	Jump to init [backpatch] 
* INIT
236:    LDA  1,0(0)	Set first frame at end of globals 
237:     ST  1,0(1)	Store old fp (point to self) 
* INIT GLOBALS AND STATICS
* END INIT GLOBALS AND STATICS
238:    LDA  3,1(7)	Return address in ac 
239:    JMP  7,-201(7)	Jump to main 
240:   HALT  0,0,0	Done! 
* END INIT
