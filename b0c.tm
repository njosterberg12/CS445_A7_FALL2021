* C- compiler version C-F21
* Built: Dec 3, 2021
* Author: Nathaniel Osterberg
* File compiled:  b0c.tm
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
* EXPRESSION
 41:    LDC  3,1(6)	Load integer const 
 42:    RND  3,3,6	Op ? 
 43:     ST  3,-4(1)	Save left side 
* EXPRESSION
 44:    LDC  3,0(6)	Load integer const 
 45:     LD  4,-4(1)	Load left into ac1 
 46:    TEQ  3,4,3	Op = 
 47:     ST  3,-4(1)	Push parameter 
* Param end
 48:    LDA  1,-2(1)	Ghost frame becomes new active frame 
 49:    LDA  3,1(7)	 Return address in ac 
 50:    JMP  7,-34(7)	CALL outputb
 51:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outnl
 52:     ST  1,-2(1)	Store fp in ghost frame for outnl
* Param end
 53:    LDA  1,-2(1)	Ghost frame becomes new active frame 
 54:    LDA  3,1(7)	 Return address in ac 
 55:    JMP  7,-22(7)	CALL outnl
 56:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* EXPRESSION
* CALL outputb
 57:     ST  1,-2(1)	Store fp in ghost frame for outputb
* TOFF dec: -3
* TOFF dec: -4
* Param
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
 58:    LDC  3,100000(6)	Load integer const 
 59:    RND  3,3,6	Op ? 
 60:     ST  3,-4(1)	Save left side 
* EXPRESSION
 61:    LDC  3,0(6)	Load integer const 
 62:     LD  4,-4(1)	Load left into ac1 
 63:    TGT  3,4,3	Op > 
 64:     ST  3,-4(1)	Push parameter 
* Param end
 65:    LDA  1,-2(1)	Ghost frame becomes new active frame 
 66:    LDA  3,1(7)	 Return address in ac 
 67:    JMP  7,-51(7)	CALL outputb
 68:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outputb
 69:     ST  1,-2(1)	Store fp in ghost frame for outputb
* TOFF dec: -3
* TOFF dec: -4
* Param
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
 70:    LDC  3,3(6)	Load integer const 
 71:    RND  3,3,6	Op ? 
 72:     ST  3,-4(1)	Save left side 
* EXPRESSION
 73:    LDC  3,0(6)	Load integer const 
 74:     LD  4,-4(1)	Load left into ac1 
 75:    TGT  3,4,3	Op > 
 76:     ST  3,-4(1)	Save left side 
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
 77:    LDC  3,3(6)	Load integer const 
 78:    RND  3,3,6	Op ? 
 79:     ST  3,-4(1)	Save left side 
* EXPRESSION
 80:    LDC  3,0(6)	Load integer const 
 81:     LD  4,-4(1)	Load left into ac1 
 82:    TGT  3,4,3	Op > 
 83:     LD  4,-4(1)	Load left into ac1 
 84:    AND  3,4,3	Op and 
 85:     ST  3,-4(1)	Save left side 
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
 86:    LDC  3,3(6)	Load integer const 
 87:    RND  3,3,6	Op ? 
 88:     ST  3,-4(1)	Save left side 
* EXPRESSION
 89:    LDC  3,0(6)	Load integer const 
 90:     LD  4,-4(1)	Load left into ac1 
 91:    TGT  3,4,3	Op > 
 92:     LD  4,-4(1)	Load left into ac1 
 93:    AND  3,4,3	Op and 
 94:     ST  3,-4(1)	Save left side 
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
 95:    LDC  3,3(6)	Load integer const 
 96:    RND  3,3,6	Op ? 
 97:     ST  3,-4(1)	Save left side 
* EXPRESSION
 98:    LDC  3,0(6)	Load integer const 
 99:     LD  4,-4(1)	Load left into ac1 
100:    TGT  3,4,3	Op > 
101:     LD  4,-4(1)	Load left into ac1 
102:    AND  3,4,3	Op and 
103:     ST  3,-4(1)	Save left side 
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
104:    LDC  3,3(6)	Load integer const 
105:    RND  3,3,6	Op ? 
106:     ST  3,-4(1)	Save left side 
* EXPRESSION
107:    LDC  3,0(6)	Load integer const 
108:     LD  4,-4(1)	Load left into ac1 
109:    TGT  3,4,3	Op > 
110:     LD  4,-4(1)	Load left into ac1 
111:    AND  3,4,3	Op and 
112:     ST  3,-4(1)	Save left side 
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
113:    LDC  3,3(6)	Load integer const 
114:    RND  3,3,6	Op ? 
115:     ST  3,-4(1)	Save left side 
* EXPRESSION
116:    LDC  3,0(6)	Load integer const 
117:     LD  4,-4(1)	Load left into ac1 
118:    TGT  3,4,3	Op > 
119:     LD  4,-4(1)	Load left into ac1 
120:    AND  3,4,3	Op and 
121:     ST  3,-4(1)	Save left side 
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
122:    LDC  3,3(6)	Load integer const 
123:    RND  3,3,6	Op ? 
124:     ST  3,-4(1)	Save left side 
* EXPRESSION
125:    LDC  3,0(6)	Load integer const 
126:     LD  4,-4(1)	Load left into ac1 
127:    TGT  3,4,3	Op > 
128:     LD  4,-4(1)	Load left into ac1 
129:    AND  3,4,3	Op and 
130:     ST  3,-4(1)	Save left side 
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
131:    LDC  3,3(6)	Load integer const 
132:    RND  3,3,6	Op ? 
133:     ST  3,-4(1)	Save left side 
* EXPRESSION
134:    LDC  3,0(6)	Load integer const 
135:     LD  4,-4(1)	Load left into ac1 
136:    TGT  3,4,3	Op > 
137:     LD  4,-4(1)	Load left into ac1 
138:    AND  3,4,3	Op and 
139:     ST  3,-4(1)	Save left side 
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
140:    LDC  3,3(6)	Load integer const 
141:    RND  3,3,6	Op ? 
142:     ST  3,-4(1)	Save left side 
* EXPRESSION
143:    LDC  3,0(6)	Load integer const 
144:     LD  4,-4(1)	Load left into ac1 
145:    TGT  3,4,3	Op > 
146:     LD  4,-4(1)	Load left into ac1 
147:    AND  3,4,3	Op and 
148:     ST  3,-4(1)	Save left side 
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
149:    LDC  3,3(6)	Load integer const 
150:    RND  3,3,6	Op ? 
151:     ST  3,-4(1)	Save left side 
* EXPRESSION
152:    LDC  3,0(6)	Load integer const 
153:     LD  4,-4(1)	Load left into ac1 
154:    TGT  3,4,3	Op > 
155:     LD  4,-4(1)	Load left into ac1 
156:    AND  3,4,3	Op and 
157:     ST  3,-4(1)	Save left side 
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
158:    LDC  3,3(6)	Load integer const 
159:    RND  3,3,6	Op ? 
160:     ST  3,-4(1)	Save left side 
* EXPRESSION
161:    LDC  3,0(6)	Load integer const 
162:     LD  4,-4(1)	Load left into ac1 
163:    TGT  3,4,3	Op > 
164:     LD  4,-4(1)	Load left into ac1 
165:    AND  3,4,3	Op and 
166:     ST  3,-4(1)	Save left side 
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
167:    LDC  3,3(6)	Load integer const 
168:    RND  3,3,6	Op ? 
169:     ST  3,-4(1)	Save left side 
* EXPRESSION
170:    LDC  3,0(6)	Load integer const 
171:     LD  4,-4(1)	Load left into ac1 
172:    TGT  3,4,3	Op > 
173:     LD  4,-4(1)	Load left into ac1 
174:    AND  3,4,3	Op and 
175:     ST  3,-4(1)	Save left side 
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
176:    LDC  3,3(6)	Load integer const 
177:    RND  3,3,6	Op ? 
178:     ST  3,-4(1)	Save left side 
* EXPRESSION
179:    LDC  3,0(6)	Load integer const 
180:     LD  4,-4(1)	Load left into ac1 
181:    TGT  3,4,3	Op > 
182:     LD  4,-4(1)	Load left into ac1 
183:    AND  3,4,3	Op and 
184:     ST  3,-4(1)	Push parameter 
* Param end
185:    LDA  1,-2(1)	Ghost frame becomes new active frame 
186:    LDA  3,1(7)	 Return address in ac 
187:    JMP  7,-171(7)	CALL outputb
188:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outputb
189:     ST  1,-2(1)	Store fp in ghost frame for outputb
* TOFF dec: -3
* TOFF dec: -4
* Param
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
190:    LDC  3,3(6)	Load integer const 
191:    RND  3,3,6	Op ? 
192:     ST  3,-4(1)	Save left side 
* EXPRESSION
193:    LDC  3,0(6)	Load integer const 
194:     LD  4,-4(1)	Load left into ac1 
195:    TGT  3,4,3	Op > 
196:     ST  3,-4(1)	Save left side 
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
197:    LDC  3,3(6)	Load integer const 
198:    RND  3,3,6	Op ? 
199:     ST  3,-4(1)	Save left side 
* EXPRESSION
200:    LDC  3,0(6)	Load integer const 
201:     LD  4,-4(1)	Load left into ac1 
202:    TGT  3,4,3	Op > 
203:     LD  4,-4(1)	Load left into ac1 
204:     OR  3,4,3	Op or 
205:     ST  3,-4(1)	Save left side 
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
206:    LDC  3,3(6)	Load integer const 
207:    RND  3,3,6	Op ? 
208:     ST  3,-4(1)	Save left side 
* EXPRESSION
209:    LDC  3,0(6)	Load integer const 
210:     LD  4,-4(1)	Load left into ac1 
211:    TGT  3,4,3	Op > 
212:     LD  4,-4(1)	Load left into ac1 
213:     OR  3,4,3	Op or 
214:     ST  3,-4(1)	Save left side 
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
215:    LDC  3,3(6)	Load integer const 
216:    RND  3,3,6	Op ? 
217:     ST  3,-4(1)	Save left side 
* EXPRESSION
218:    LDC  3,0(6)	Load integer const 
219:     LD  4,-4(1)	Load left into ac1 
220:    TGT  3,4,3	Op > 
221:     LD  4,-4(1)	Load left into ac1 
222:     OR  3,4,3	Op or 
223:     ST  3,-4(1)	Save left side 
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
224:    LDC  3,3(6)	Load integer const 
225:    RND  3,3,6	Op ? 
226:     ST  3,-4(1)	Save left side 
* EXPRESSION
227:    LDC  3,0(6)	Load integer const 
228:     LD  4,-4(1)	Load left into ac1 
229:    TGT  3,4,3	Op > 
230:     LD  4,-4(1)	Load left into ac1 
231:     OR  3,4,3	Op or 
232:     ST  3,-4(1)	Save left side 
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
233:    LDC  3,3(6)	Load integer const 
234:    RND  3,3,6	Op ? 
235:     ST  3,-4(1)	Save left side 
* EXPRESSION
236:    LDC  3,0(6)	Load integer const 
237:     LD  4,-4(1)	Load left into ac1 
238:    TGT  3,4,3	Op > 
239:     LD  4,-4(1)	Load left into ac1 
240:     OR  3,4,3	Op or 
241:     ST  3,-4(1)	Save left side 
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
242:    LDC  3,3(6)	Load integer const 
243:    RND  3,3,6	Op ? 
244:     ST  3,-4(1)	Save left side 
* EXPRESSION
245:    LDC  3,0(6)	Load integer const 
246:     LD  4,-4(1)	Load left into ac1 
247:    TGT  3,4,3	Op > 
248:     LD  4,-4(1)	Load left into ac1 
249:     OR  3,4,3	Op or 
250:     ST  3,-4(1)	Save left side 
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
251:    LDC  3,3(6)	Load integer const 
252:    RND  3,3,6	Op ? 
253:     ST  3,-4(1)	Save left side 
* EXPRESSION
254:    LDC  3,0(6)	Load integer const 
255:     LD  4,-4(1)	Load left into ac1 
256:    TGT  3,4,3	Op > 
257:     LD  4,-4(1)	Load left into ac1 
258:     OR  3,4,3	Op or 
259:     ST  3,-4(1)	Save left side 
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
260:    LDC  3,3(6)	Load integer const 
261:    RND  3,3,6	Op ? 
262:     ST  3,-4(1)	Save left side 
* EXPRESSION
263:    LDC  3,0(6)	Load integer const 
264:     LD  4,-4(1)	Load left into ac1 
265:    TGT  3,4,3	Op > 
266:     LD  4,-4(1)	Load left into ac1 
267:     OR  3,4,3	Op or 
268:     ST  3,-4(1)	Save left side 
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
269:    LDC  3,3(6)	Load integer const 
270:    RND  3,3,6	Op ? 
271:     ST  3,-4(1)	Save left side 
* EXPRESSION
272:    LDC  3,0(6)	Load integer const 
273:     LD  4,-4(1)	Load left into ac1 
274:    TGT  3,4,3	Op > 
275:     LD  4,-4(1)	Load left into ac1 
276:     OR  3,4,3	Op or 
277:     ST  3,-4(1)	Save left side 
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
278:    LDC  3,3(6)	Load integer const 
279:    RND  3,3,6	Op ? 
280:     ST  3,-4(1)	Save left side 
* EXPRESSION
281:    LDC  3,0(6)	Load integer const 
282:     LD  4,-4(1)	Load left into ac1 
283:    TGT  3,4,3	Op > 
284:     LD  4,-4(1)	Load left into ac1 
285:     OR  3,4,3	Op or 
286:     ST  3,-4(1)	Save left side 
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
287:    LDC  3,3(6)	Load integer const 
288:    RND  3,3,6	Op ? 
289:     ST  3,-4(1)	Save left side 
* EXPRESSION
290:    LDC  3,0(6)	Load integer const 
291:     LD  4,-4(1)	Load left into ac1 
292:    TGT  3,4,3	Op > 
293:     LD  4,-4(1)	Load left into ac1 
294:     OR  3,4,3	Op or 
295:     ST  3,-4(1)	Save left side 
* EXPRESSION
* OpK
* EXPRESSION
* EXPRESSION
296:    LDC  3,3(6)	Load integer const 
297:    RND  3,3,6	Op ? 
298:     ST  3,-4(1)	Save left side 
* EXPRESSION
299:    LDC  3,0(6)	Load integer const 
300:     LD  4,-4(1)	Load left into ac1 
301:    TGT  3,4,3	Op > 
302:     LD  4,-4(1)	Load left into ac1 
303:     OR  3,4,3	Op or 
304:     ST  3,-4(1)	Push parameter 
* Param end
305:    LDA  1,-2(1)	Ghost frame becomes new active frame 
306:    LDA  3,1(7)	 Return address in ac 
307:    JMP  7,-291(7)	CALL outputb
308:    LDA  3,0(2)	Save the result in ac 
* Call end outputb
* EXPRESSION
* CALL outnl
309:     ST  1,-2(1)	Store fp in ghost frame for outnl
* Param end
310:    LDA  1,-2(1)	Ghost frame becomes new active frame 
311:    LDA  3,1(7)	 Return address in ac 
312:    JMP  7,-279(7)	CALL outnl
313:    LDA  3,0(2)	Save the result in ac 
* Call end outnl
* TOFF set: -2
* END COMPOUND
* Add standard closing in case there is no return statement
314:    LDC  2,0(6)	Set return value to 0 
315:     LD  3,-1(1)	Load return address 
316:     LD  1,0(1)	Adjust fp 
317:    JMP  7,0(3)	Return 
* END FUNCTION main
  0:    JMP  7,317(7)	Jump to init [backpatch] 
* INIT
318:    LDA  1,0(0)	Set first frame at end of globals 
319:     ST  1,0(1)	Store old fp (point to self) 
* INIT GLOBALS AND STATICS
* END INIT GLOBALS AND STATICS
320:    LDA  3,1(7)	Return address in ac 
321:    JMP  7,-283(7)	Jump to main 
322:   HALT  0,0,0	Done! 
* END INIT
