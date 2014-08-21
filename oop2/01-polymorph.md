# OOP2 - Polymorphism and Interface

## Assignment

การกำหนดตัวแปร สามารถกำหนดชนิดตัวแปรได้เป็น

1. คลาสตามที่จะเก็บข้อมูล
2. Superclass ของมัน (กี่ชั้นก็ได้)
3. Interface ของมัน

````java
public interface Storable{
	public boolean deposit(int x);
}
public class BankAccount implements Storable{
	@Override
	public boolean deposit(int x){
		// ...
		return true;
	}
	public boolean withdraw(int x){
		// ...
		return true;
	}
}
public class SavingAccount extends BankAccount{
	// SavingAccount ก็ implements Storable
}
public class RecurringSavingAccount extends SavingAccount{
	private int month;
	@Override
	public boolean withdraw(int x){
		return false;
	}
	public int getMonths(){
		return month;
	}
}
public class Chest implements Storable{
	public boolean deposit(int x){
		return true;
	}
}

// 1. คลาสตามที่เก็บข้อมูล
RecurringSavingAccount a = new RecurringSavingAccount();
// 2. Superclass
SavingAccount b = new RecurringSavingAccount();
BankAccount c = new RecurringSavingAccount();
// 3. Interface
Storable d = new RecurringSavingAccount();
````

## Apparent Type

ปัญหาคือ `a`, `b`, `c`, `d` แตกต่างกันอย่างไร

- `a` สามารถใช้เมธอด `getMonths` ของ `RecurringSavingAccount` ได้
- `b`, `c`, `d` ไม่สามารถใช้เมธอด `getMonths` ได้
- `a`, `b`, `c` สามารถใช้เมธอด `deposit`, `withdraw` ได้
- `d` ใช้ได้เฉพาะเมธอด `deposit` เท่านั้น เมธอดอื่นๆ ของ `Object` ใช้ไม่ได้ (เช่น `toString()`)

ในตัวอย่างนี้เราจะเห็นว่าตัวแปร `d` นั้น

- **Actual Type:** `RecurringSavingAccount` (ตัวแปรที่เอามาใส่)
- **Apparent Type:** `Storable` (ชนิดตัวแปรนั้น)

จะเห็นว่าเราจะใช้เมธอดได้เฉพาะที่มีอยู่ใน Apparent Type เท่านั้น

## Polymorphism

กรณีที่เราทราบว่า `d` จริงๆ แล้วเป็นคลาสไหน สามารถสร้างตัวแปรใหม่แล้วกำหนดค่าได้ทั้ง 3 ข้อข้างบนเลย

````java
SavingAccount e = (SavingAccount) d;
````

ข้อควรระวังคือ compiler ไม่สามารถรู้ล่วงหน้าได้ว่า `d` นั้นมี Actual Type เป็นอะไร ฉะนั้นแล้วโค้ดจะสามารถคอมไพล์ผ่านได้ แต่รันแล้วอาจจะเกิด `ClassCastException` ได้ error ชนิดนี้เรียกว่า Runtime Exception คือเกิดขึ้นขณะรัน อีกแบบคือ Compile-time Exception คือเกิดขณะคอมไพล์

ทางที่ดีที่สุดแล้วเราควรให้ error เราเป็น Compile-time exception จะดีกว่า เพราะเราสามารถรู้และแก้ไขล่วงหน้าได้ แต่ Runtime Exception นั้นบางครั้งใช้ๆ ไปแล้วอาจจะไม่เคยเจอเอง แต่ให้ผู้ใช้งานใช้แล้วเจอก็ได้ เพราะอาจจะเกิดในกรณีแปลกๆ

ทางแก้ไขตัวแปร `e` ให้มีความปลอดภัยคือใช้ `instanceof` เช็คก่อนแปลงเสมอ

````java
if(d instanceof SavingAccount){
	SavingAccount e = (SavingAccount) d;
}
// ตรงนี้ e ไม่ถูกประกาศ เพราะอยู่นอก if
````

## Overriding

ข้อควรรู้อย่างหนึ่งคือ ตัวแปร `c` ที่มีชนิดเป็น `BankAccount` นั้น ถ้าเราเรียก `withdraw` ก็จะ return `false` ตามโค้ดใน `RecurringSavingAccount` อยู่ดี เพราะการเรียกเมธอดจะเรียกตาม Actual Type

## Usage

ประโยชน์ของการใช้ Polymorphism น่าจะเคยเห็นแล้วใน OOP1 นั่นคือการที่ `ArrayList` สามารถเก็บข้อมูลหลายๆ ชนิดรวมกันได้

ประโยชน์ของการใช้ Interface คือลดการจับคู่กันของโค้ด (decoupling) ตัวอย่างเช่น ในแอพ KUSmartBus จะมีคลาส [StopSelectedInterface](https://github.com/whs/kubus-android/blob/master/src/th/in/whs/ku/bus/StopSelectedInterface.java) ซึ่งมีเมธอด `void stopSelected(JSONObject item)` อยู่ อินเทอร์เฟสนี้ถูก implements โดยสองหน้า

- [หน้าหลักของโปรแกรม](https://github.com/whs/kubus-android/blob/master/src/th/in/whs/ku/bus/BusStopFragment.java#L49) เมื่อเลือกป้ายรถแล้วให้แสดงข้อมูลป้ายรถออกมา
- [หน้าเลือกป้ายรถ](https://github.com/whs/kubus-android/blob/master/src/th/in/whs/ku/bus/BusStopListActivity.java#L66) (ใช้ในหน้าค้นหาเส้นทาง) เมื่อเลือกป้ายรถแล้วให้คืนข้อมูลป้ายไปยังหน้าที่เปิดหน้านี้มา

ในกรณีนี้จะสังเกตว่า[ส่วนแสดงป้ายรถ](https://github.com/whs/kubus-android/blob/master/src/th/in/whs/ku/bus/BusStopListFragment.java#L188)นั้นไม่จำเป็นจะต้องรู้จักกับหน้าไหนเป็นพิเศษในโปรแกรมเลย เพียงแค่หาหน้าที่เปิดตัวมันเองออกมา แล้วเรียกเมธอดผ่าน `StopSelectedInterface` ก็สามารถส่งข้อมูลให้กันได้แล้ว

การเขียนโค้ดในลักษณะนี้มีข้อดีคือโค้ดสามารถนำไปใช้ใหม่ได้เรื่อยๆ ตอนเขียนโค้ดนี้ครั้งแรกใช้เฉพาะในหน้าแรกของโปรแกรม ต่อมาเมื่อเพิ่มหน้าค้นหาเส้นทางก็สามารถทำให้เลือกป้ายรถได้โดยไม่ต้องแก้โค้ดในส่วนแสดงผลมากนัก