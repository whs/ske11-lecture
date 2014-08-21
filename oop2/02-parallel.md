# Parallel with Java

## ทำไมต้อง Parallel

สมมุติว่าได้รายงานมาหนึ่งหัวข้อมี 4 บทกับกลุ่ม 4 คน

แน่นอนการมีสี่คนแล้วให้คนเดียวทำเป็นอะไรที่ส้นตีนมาก

เช่นเดียวกัน การใช้คอมมี 4 Core แต่โปรแกรมมันรันทีละคอร์ก็ส้นตีนมาก

ใน Java เวลาเขียนโปรแกรมแล้วโปรแกรมจะรันคำสั่งจากต้นไปจนจบตามลำดับกัน ซึ่งมันรันโดยการที่ใช้แค่คอร์เดียวเท่านั้น อีก 3 core ปล่อยว่าง บางทีแล้วเราอาจจะสามารถแบ่งงานให้ 3 core ที่เหลือได้แล้วงานจะเร็วขึ้น คำสำคัญตอนนี้คือ **แบ่งงาน** ถ้างานแบ่งไม่ได้ ก็แตกคอร์ไม่ได้

งานยังไงบ้างล่ะที่จะแบ่งได้? สำคัญคือต้องสามารถทำงานแยกกันได้โดยอิสระ

- งานคำนวณบางอย่าง เช่น มีข้อมูลในฐานข้อมูล 1,000,000 ข้อมูล ต้องการหาผลรวมของช่องคะแนน (แบ่งได้หลายวิธี เช่น แบ่งตามหมายเลขข้อมูล 1-100,000, 100,001-200,000, ...) บางอย่างก็แบ่งไม่ได้ เช่น​ Factorial เพราะผลมันเกิดจากคำตอบก่อนหน้า
- งานที่มันแยกกันสนิทแต่ใช้รวมกัน เช่น ในใน BioShock ภาคแรกแบ่งระบบต่างๆ แยกออกจากกันได้แก่ ระบบจำลองเกม, ระบบ GUI, ระบบแสดงผล, ระบบเล่นเสียง, ระบบเอฟเฟกท์เสียง, ระบบโหลดภาพพื้นผิว, ระบบโหลดไฟล์, ระบบจำลองฟิสิกส์
- งานที่เป็น I/O Bound (Input/Output) เช่นการโหลดข้อมูลจากเน็ต ถ้าไม่แตก Threads ออกไปโปรแกรมจะค้างขณะโหลด
- การเขียน GUI นั้นทุกอย่างที่ไม่ได้ยุ่งกับ GUI (เช่น การเซฟไฟล์) ควรแตกไปทำข้างหลังเพื่อไม่ให้ GUI ค้าง

## Threads

Threads (เธรด) เป็นความสามารถของระบบปฏิบัติการที่ทำให้โปรแกรมสามารถแยกตัวเองเป็นหลายๆ ส่วนเพื่อประมวลผลพร้อมๆ กันได้

Java นั้นมีคลาส `Thread` สำหรับใช้สร้างเธรด

~~~~~java
class ThreadByThread extends Thread{
	@Override
	public void run(){
		// สิ่งที่ต้องการประมวลผล
	}
}
class ThreadByRunnable implements Runnable{
	@Override
	public void run(){
		// สิ่งที่ต้องการประมวลผล
	}
}
class Main{
	public static void main(String[] args){
		ThreadByThread t1 = new ThreadByThread();
		t1.start(); // เรียก start ไม่ใช่ run
		Thread t2 = new Thread(new ThreadByRunnable());
		t2.start();
	}
}
~~~~~

สังเกตว่าเราสามารถใช้ได้ทั้งสองแบบ โดยแบบที่ใช้ `implements Runnable` จะเป็นประโยชน์ในกรณีที่ต้องการ extends class ที่มีอยู่แล้ว และทำให้เป็นเธรด

เมื่อสั่ง `start` (ไม่ใช่ `run`) แล้ว Java จะแตกเธรดออกไปและรันโค้ดใน `run` โดยไม่รอให้ `run` ทำงานเสร็จก่อน การ start นี้เรียกว่า "fork"

## Race condition

เมื่อมีโค้ดทำงานพร้อมๆ กัน บางครั้งจึงเกิดกรณีที่เรียกว่า race condition หรือการที่ 2 threads แย่งกันใช้ตัวแปร

~~~~~java
class BankAccount{
	private int balance;
	public boolean withdraw(int amount){
		if(balance-amount <= 0){
			return false;
		}
		// หยุดตรงนี้
		balance -= amount;
		return true;
	}
}
~~~~~

ตัวอย่างเช่นในกรณีนี้ ถ้ามี 2 เธรดทำงานพร้อมกันอยู่แล้วเรียกใช้ `withdraw` พร้อมกัน ตัวหนึ่งอาจจะทำงานถึง comment แล้วและพักการทำงานให้อีกเธรดทำงาน อีกเธรดนั้นรันคำสั่ง withdraw จนจบแล้วเธรดแรกจึงทำที่เหลือของ withdraw ต่อ

สิ่งที่เกิดขึ้นคือสามารถถอนเงินเกินบัญชีได้ เพราะเธรดแรกผ่านการเช็คแล้ว และ `balance` เกิดเปลี่ยนแปลง

![Flow chart of execution](https://gist.github.com/whs/e5809911efb7e39ba50d/raw/7cd9afd6bebaf62a72502fa7327fdec01a7fee93/concurrent1.png)

วิธีการแก้ปัญหานี้คือการใช้ `synchronized`

~~~~java
class Synchronized{
	int x = 0;
	public synchronized void syncMethod(){
		x += 1;
	}
	public void syncBlock(){
		synchronized(this){
			x += 1;
		}
	}
}
~~~~

สองเมธอดนี้โค้ดเหมือนกัน อันหนึ่งใช้ `synchronized` ในหัวเมธอด อีกอันใช้ใน body เรียกว่า synchronized block

เมื่อโค้ดมาถึงจุดที่มีการใส่ `synchronized` คร่อมไว้จะต้องเข้าคิวกันทำงาน เมื่อคนหนึ่งเข้าไปแล้วจะต้องรอให้เสร็จก่อนจึงจะเรียกคิวต่อไป

ตัวอย่างเช่นถ้าเอา `BankAccount` มาเติม ``synchronized`

~~~~~java
class BankAccount{
	private int balance;
	public synchronized boolean withdraw(int amount){
		if(balance-amount <= 0){
			return false;
		}
		// หยุดตรงนี้
		balance -= amount;
		return true;
	}
}
~~~~~

![Flowchart](https://gist.github.com/whs/e5809911efb7e39ba50d/raw/8ed8a944633630fffbcbe698428af5b6b282c895/concurrent2.png)

กรณีนี้แล้วจะไม่มีการรัน `withdraw` ครึ่งๆ กลางๆ จะต้องรันให้จบก่อนคนอื่นจึงจะสามารถเข้า `withdraw` ต่อได้

สิ่งที่อยู่ใน `synchronized(..)` นั้นคือชื่อของคิว นั่นหมายความว่าถ้าคิวคนละชื่อกันถึงจะมีโค้ดรันอยู่ใน `synchronized(a)` อยู่ก็สามารถเข้า `synchronized(b)` ได้ ไม่เกี่ยวข้องกัน

## แบ่งงาน

อ้างอิงจาก [Lois S. and Rajkuma B. Parallel Programming Models and Paradigms.](http://www.buyya.com/cluster/v2chap1.pdf)

### Master-Slave

การแบ่งงานแบบ Master-Slave คือมีตัว master เป็นหัวหน้ากลุ่ม และมีลูกน้อง (slave) ภายในกลุ่ม

1. master สร้าง slave มาจำนวนหนึ่ง (อาจจะตาม cores ของ CPU)
2. slave ของานจาก master
3. master แบ่งงานมาหนึ่งชิ้นแล้วให้ slave
4. slave ทำงานเสร็จแล้วส่งคำตอบให้ master
5. วนซ้ำข้อ 2 จนกว่าจะไม่ได้งานจาก master
5. master รวบรวมคำตอบและสรุปผล

ข้อดีของวิธีนี้คือกรณีสถานการณ์มีการเปลี่ยนแปลง เช่น งานเพิ่มขึ้นขณะที่กำลังทำงานอยู่ หรือต้องการสร้าง slave เพิ่มเติมอีกก็สามารถทำได้ ข้อเสียคือการขอข้อมูลจาก master มันช้า ทำบ่อยๆ ยิ่งช้า

### Divide and Conquer

วิธีนี้เหมือน Phantom Lancer คือตัดปัญหาเป็นชิ้นย่อยๆ ที่ทำงานแยกจากกันแล้ว slave แบ่งไปทำ

![Divide 1](https://gist.github.com/whs/e5809911efb7e39ba50d/raw/c6b998ef04ae22ee1eff37716d6e4ec3d7acd974/dac1.png)

![Juxtapose](https://gist.github.com/whs/e5809911efb7e39ba50d/raw/5f31d831eca6abab4a30dad9a5616933a36d4ae9/split.png)

*ฟาร์ม*

บางกรณีเราอาจจะทำให้ slave อาจจะมองเห็นงานที่แบ่งแล้วว่ายังใหญ่อยู่ และแบ่งต่อเข้าไปอีกเรื่อยๆ

![Divide Recurse](https://gist.github.com/whs/e5809911efb7e39ba50d/raw/4698292eb030f08fa24030b6d5f5cc47eb01fd36/dac2.png)

![Phantom Edge](https://gist.github.com/whs/e5809911efb7e39ba50d/raw/c921d6ed7cfd639018665f5dcda966281f0a0aad/split2.png)

*ฟาร์มรัวๆ*

### Single-Program Multiple-Data (SPMD)

**วิธีนี้และหลังจากนี้ไม่มีสอนในที่เรียน ข้ามไปก็ได้**

1. master สร้าง slave มาจำนวนหนึ่ง
2. master แบ่งงานและส่งให้ slave ทั้งหมด
3. slave ประมวลผล และอาจจะมีการสื่อสารหรือดึงข้อมูลระหว่างกัน
4. master รวบรวมคำตอบและสรุปผล

![SPMD](https://gist.github.com/whs/e5809911efb7e39ba50d/raw/a45830ff1e9cfab5e31c0b058252595deec5529b/spmd.png)

วิธีนี้มีข้อสังเกตคือมีการแบ่งงานก่อนแล้วค่อยทำ และมีการสื่อสารกันระหว่าง slave (เหมือนการทำงานกลุ่ม) ซึ่งอาจจะจำเป็นในการแก้ปัญหาบางประเภท

ข้อเสียของวิธีนี้คือหาก slave บางตัวเกิดตาย (เช่นเกิด exception) อาจทำให้ระบบเกิด deadlock คือ slave ตัวอื่นอาจจะต้องการสื่อสารกับ slave ที่ตายแล้ว และจะหยุดรอไปเรื่อยๆ ไม่ทำงาน

### Data Pipelining

![Pipeline](https://gist.github.com/whs/e5809911efb7e39ba50d/raw/f664374ddbe4aa4a90c70137b139e9287aeb9e15/pipeline.png)

วิธีนี้ใช้สำหรับปัญหาที่แตกเป็นข้อย่อยๆ ที่แก้แยกจากกันเป็นอิสระได้แล้วเอาคำตอบมารวมกัน การทำงานคือ

1. แตกงานเป็นข้อๆ
2. เอาข้อแรกส่งให้เธรดที่ 1
3. เธรดที่ 1 หาคำตอบและส่งต่อให้เธรดที่ 2 ที่จะทำขั้นต่อไป
4. เธรดที่ 1 รับข้อใหม่มาทำไปเรื่อยๆ จนกว่าจะหมด
5. เช่นเดียวกัน เธรดที่ 2 เสร็จงานแล้วก็ส่งต่อให้เธรดที่ 3 ไปเรื่อยๆ

วิธีนี้อาจจะเหมือนการส่งถังน้ำ แทนที่จะให้แต่ละคนยกน้ำไปก็ยืนเฉยๆ แล้วส่งถังให้เพื่อนคนถัดไปแทน

## Fork Join

สังเกตว่าการแบ่งงานหลักๆ แล้วคือ

1. สร้างลูก
2. ให้ลูกทำงาน
3. สรุปผล

ขั้นตอนที่ 1 นี้เรียกว่า fork ที่แปลว่าส้อม เหมือนส้อมที่ด้ามเป็นเส้นตรงแล้วแยกออกเป็นกิ่งๆ

![Yamaha](https://upload.wikimedia.org/wikipedia/en/thumb/2/20/YamahaCorp.svg/457px-YamahaCorp.svg.png)

*โลโก้ Yamaha เป็นส้อมเสียง 3 อันซ้อนกัน*

และขั้นตอนที่ 3 เรียกว่า join คือการรวมกิ่งที่แยกออกไปให้กลับเข้ามาเป็นกิ่งเดียว

การ Fork ใน Java ทำได้ด้วยการใช้เธรดตามหัวข้อด้านบน ส่วนการ Join สามารถทำได้ดังนี้

~~~~java
class Main{
	public static void main(String[] args){
		ThreadByThread t1 = new ThreadByThread();
		t1.start(); // fork
		System.out.println("thread started");
		
		try{
			t1.join();
		}catch(InterruptedException e){
		}
		System.out.println(t1.getResult()); // เมธอดนี้ไปเขียนเอง
	}
}
~~~~

คำสั่ง join จะหยุดการทำงานของเธรดปัจจุบันจนกว่าเธรดที่สั่ง join จะหลุดออกจาก `run` แล้วจึงจะทำงานต่อ

## Technical

หัวข้อนี้เป็นข้อมูลเพิ่มเติม งงก็งงต่อไป

- กรณีที่คอมพิวเตอร์ใช้คอร์เดียว หรือคอร์จองทำงานเต็ม ระบบปฏิบัติการจะมี[กระบวนการ Time sharing](https://en.wikipedia.org/wiki/Preemptive_multitasking) คือแบ่งเวลาให้โปรแกรมต่างๆ ตามความเหมาะสมและลำดับความสำคัญ เมื่อหมดเวลาแล้วระบบปฏิบัติการจะพักการทำงานของโปรแกรมไว้แล้วให้โปรแกรมอื่นผลัดกันทำงาน