# OOP Inheritance for dummy

เวลาเราเขียนโปรแกรม บางครั้งจะมีโค้ดที่ซ้ำๆ กันหลายครั้ง เช่น...

~~~~java
class Car{
	private int speed=0;
	private boolean isStarted=false;
	public void start(){
		this.isStarted=true;
	}
	public void drive(){
		this.speed = 40;
	}
}
class SuperCar{
	private int speed=0;
	private boolean isStarted=false;
	public void start(){
		this.isStarted=true;
	}
	public void drive(){
		this.speed = 40;
	}
	public void nitrous(){
		this.speed = 200;
	}
}
~~~~

จะเห็นว่าทั้งสองคลาสมี `speed`, `isStarted`, `start`, `drive` ซ้ำกัน ตัวภาษาเลยมีระบบ inheritance (สืบทอด) มาช่วยให้เราไม่ต้องเขียนโค้ดก๊อปแปะ

~~~~java
class Car{
	private int speed=0;
	private boolean isStarted=false;
	public void start(){
		this.isStarted=true;
	}
	public void drive(){
		this.speed = 40;
	}
	public void setSpeed(int speed){
		this.speed = speed;
	}
}
class SuperCar extends Car{
	public void nitrous(){
		this.setSpeed(200);
	}
}
~~~~

จะเห็นว่าคลาส `SuperCar` ไม่มีอะไรตัดแปะมาอีกแล้ว แต่กลายเป็น `extends Car`

ในกรณีนี้คลาสแม่คือ `Car` เรียกว่า **superclass** ส่วนคลาสลูกคือ `SuperCar` เรียกว่า **subclass**

## Visibility

เมื่อกี้จะเห็นว่า `nitrous` ใช้ `setSpeed` ไม่ใช่ `this.speed` เพราะมันใช้ไม่ได้เนื่องจาก attribute `speed` เป็น `private`

กลับไปที่เรื่องนี้อีกทีนึง

- **public**: คลาสไหนๆ ก็สามารถใช้ `this.speed` ได้
- **protected**: เฉพาะ `Car` และคลาสที่ extends ต่อจากมัน (กรณีนี้คือ `SuperCar`) สามารถใช้ `this.speed` ได้เท่านั้น
- **private**: เฉพาะ `Car` เท่านั้นที่ใช้ `this.speed` ได้ แม้แต่ `SuperCar` ก็ใช้ไม่ได้

สำหรับตัวแปรที่ไม่ใช่ `public` แล้วถ้าอยากได้ค่าก็ต้องเรียกจาก `get...`​ หรือกำหนดค่าด้วย `set...` ถ้าเป็นโค้ดคนอื่นแล้วไม่มีให้ เค้าอาจจะจงใจให้เราใช้วิธีอื่นๆ เข้ามา หรือเป็นข้อมูลลับที่ไม่ต้องการให้เข้ามายุ่ง

## Overrides

สมมุติว่า `SuperCar` เนี่ยต้องการแก้ให้ตอนขับมันเริ่มที่ 80

~~~~java
class SuperCar extends Car{
	public void drive(){
		this.setSpeed(80);
	}
	public void nitrous(){ .... } // ขี้เกียจก๊อปมา
}
~~~~

จะพบว่า `SuperCar` มีเมธอด `drive` เหมือนกับของ `Car` ซึ่งเวลาเรียกมันจะมาเรียก `drive` เฉพาะที่ `SuperCar` ตัว `drive` เดิมที่มีเป็นอันหายไป เว้นแต่จะไปสร้างคลาส `Car` มาใช้

## super vs. this

กลับไปที่ `this` อีกที คราวนี้เรามีญาติของมันมาแนะนำให้รู้จักคือ `super`

- `this` มองหาตัวแปรตัวนี้ใน class **นี้** ถ้าไม่เจอก็ไปหาของ superclass (คลาสแม่) ไล่ขึ้นไปเรื่อยๆ
- `super` มองหาตัวแปรตัวนี้ใน class **แม่** ถ้าไม่เจอก็ไปหาของ class แม่ของแม่ ไล่ขึ้นไปเรื่อยๆ
- ถ้าไม่ใส่เลย จะมองหาตัวแปรใน **local variable** ถ้าไม่มีจะดูใน class **นี้** และไล่ขึ้นไปเรื่อยๆ

ประโยชน์คือเวลาเราจะ override method (เขียนเมธอดชื่อเดิมซ้ำในคลาสลูก) แต่ยังต้องการให้เมธอดตัวหลักทำงานอยู่ควบคู่กันไป เช่น ถ้า `SuperCar` สตาร์ทปุ๊บมันออก 20 เลย

~~~~~java
class SuperCar extends Car{
	public void start(){
		super.start(); // เมธอดนี้เซต this.isStarted=true
		this.setSpeed(20);
	}
	// ก๊อปโค้ดเก่ามาเองนะ
}
~~~~~

พูดง่ายๆ ว่าแทนที่จะต้องก๊อปโค้ดเมธอดตัวนี้ของ class แม่ ก็ใช้คำสั่ง `super.methodName();` แทน​ (อย่าลืมใส่ argument เหมือนไปเรียกเมธอดนั้นๆ ของคลาสแม่ตามปกติ มันไม่ได้ก๊อปใส่วงเล็บให้เราอัตโนมัติ)

## Generics

ประโยชน์ข้อต่อมาคือ เวลาส่ง argument เข้าไป เราสามารถส่งคลาสลูกเข้าไปได้ถ้า data type เป็นคลาสแม่ เช่น

~~~~~java
class CarPark{
	private Car[] storage;
	public CarPark(){
		this.storage = new Car[50];
	}
	public void park(Car car){
		// จริงๆ ต้องเขียนให้มันจอดเรียงกันไป เอาเป็นว่าไปทำเอาเองนะ :P
		this.storage[0] = car;
	}
}
~~~~~

กรณีนี้ไม่ว่าเราจะขับ `Car` หรือ `SuperCar` เราสามารถเข้าจอดได้หมด

~~~~~
public static void main(String[] args){
	CarPark centralLadphrao = new CarPark();

	SuperCar myCar = new SuperCar();
	centralLadphrao.park(myCar);

	Car myFriendCar = new Car();
	centralLadphrao.park(myFriendCar);
}
~~~~~

สังเกตว่า `myCar` และ `myFriendCar` เป็นคนละชนิดกัน แต่ทั้งหมดเป็นญาติกับ `Car` ก็เข้าจอดได้หมด

แต่ถ้าเราเปลี่ยนคลาสเป็น

~~~~~java
class SuperCarPark{
	private SuperCar[] storage;
	// ก๊อปที่เหลือมาเองนะ
}
~~~~~

กรณีนี้ `SuperCar` **เท่านั้น** ถึงจะเข้าจอดได้ `Car` เฉยๆ จอดไม่ได้ (พูดง่ายๆ คือคลาสลูกจอดได้ คลาสแม่จอดไม่ได้)

การใช้ลักษณะนี้ ถ้าใช้วิธี copy paste code มาโดยไม่ใช้ inheritance ไม่สามารถทำได้

## instanceof

วิธีนึงที่ใช้เช็คว่าตัวแปรตัวนั้นๆ เป็น class ที่ต้องการหรือไม่ คือใช้ `instanceof` operator

วิธีการใช้ `instanceof` เหมือนเครื่องหมาย `==`

~~~~~~java
if(myCar instanceof Car){}
~~~~~~

กรณีนี้คำตอบก็เป็น `true` แม้ `SuperCar` จะไม่ใช่ `Car` ตรงๆ แต่สืบทอดมา

## Multi level

Inheritance สามารถทำต่อกันเป็นทอดๆ ได้ด้วย แต่ไม่สามารถ extends จากหลายๆ คลาสพร้อมกันได้

~~~~~java
class Car{
	public void start(){}
	public void drive(){}
}
class SuperCar extends Car{
	public void drive(){}
	public void nitrous(){}
}
class FerariCar extends SuperCar{
}
class GameCar extends Car{
	public void start(){}
}
class MarioCart extends GameCar{
	public void drive(){}
}
class BurnoutCar extends GameCar{
}
~~~~~

![Class diagram](https://gist.github.com/whs/9cc9ec1dd6b6b6631dc9/raw/diagram1.png)

ในกรณีนี้ ถ้าเอา `BurnoutCar` ไปเข้าจอดใน `CarPark` ก็สามารถจอดได้ เพราะเป็นญาติห่างๆ กันอยู่ดี ส่วน `FerariCar` ก็สามารถเข้าจอด `SuperCarPark` ได้ แต่ `MarioCart` เอาไปเข้าจอดใน `SuperCarPark` ไม่ได้

## ตัวอย่างการเอาไปใช้

ตัวอย่างเช่นใน Dota2 คลาสอาจจะเป็นแบบนี้:

- Skill
  - **Attributes**
    - int manaCost
    - boolean canBeSilenced
  - **Subclass**
    - DamageSkill
      - SingleTargetDamageSkill
      - AoeDamageSkill
    - StunSkill
      - SingleTargetStunSkill
      - AoeStunSkill
    - PassiveSkill
- Item
  - **Attribute**
    - int cost
    - Item[] composedOf : ไอเทมนี้ประกอบจาก / สังเกตว่าสามารถอ้างอิงตัวเองได้
    - Skill activeSkill
  - **Subclass**
    - RecipeItem
    - ConsumableItem
- Hero
  - **Attribute**
    - Skill[4] skills
    - Item[6] items
    - int stat_int
    - int stat_str
    - int stat_agi
    - String teamName
  - **Method**
    - getHP()
    - getMana()
  - **Subclass**
  	- AntiMage
  	- Alchemist
  	- Rubick
  	- Invoker

ในดอทเอจะเห็นว่าสกิลมีเยอะมาก ถ้าใช้วิธี CPE (Copy paste engineering) โค้ดจะยาวมาก และหากจะแก้ให้ cooldown \* 2 ทุกสกิลจะเสียเวลาแก้ทีละอันมาก (หรือถ้าไปแก้ตอนเรียกใช้ ก็อาจจะลืมแก้บางจุด) ถ้าใช้วิธี inheritance แล้วเราแก้แค่ `getCooldown` ของคลาส `Skill` ให้คืนค่า \* 2 เพียงจุดเดียวก็จะสมบูรณ์โดยมีโอกาสบั๊กน้อยมาก