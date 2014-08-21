# OOP: Typed LinkedList (Generics), Polymorphism

## Typed LinkedList

จะเห็นว่าสัปดาห์นี้เราใช้โค้ดนี้

~~~~java
ArrayList<BankAccount> bank = new ArrayList<BankAccount>();
~~~~

มันคืออะไร?

สมมุติว่าเรามีคลาสนี้

~~~~java
class Operation {
	public static int add(int a, int b){
		return a + b;
	}
}
~~~~

ใน Java เราสามารถประกาศ class ที่มีเมธอดแบบไม่ระบุ data type ตายตัวได้โดยใช้ Generics แบบนี้

~~~~java
class Operation<T> {
	public static T add(T a, T b){
		return a + b;
	}
}
~~~~

สังเกต่วาเรารับ <T> เข้าไปแล้วแท่นที่ int ด้วย T หมด ฉะนั้น เวลาเรา new อะไร T จะแทนที่ด้วยตัวนั้น เช่น

~~~~java
Operation<Integer> addInt = new Operation<Integer>();
System.out.println(addInt(5, 3));
~~~~

ถ้าเราอยากเปลี่ยนเป็น double หรือชนิดอื่นๆ เพียงแค่เปลี่ยนตอน new ไม่ต้องแก้เข้าไปในคลาส และใช้คลาสเดียวแต่ new หลายๆ รอบ หลายๆ แบบ ทำเป็นหลาย data type ได้ ไม่ต้องก๊อปวาง

ใน ArrayList ก็มีสมบัตินี้อยู่ คือ ถ้าเปิด [Javadoc](http://docs.oracle.com/javase/7/docs/api/java/util/ArrayList.html) จะเห็นว่ามันใช้ `public class ArrayList<E>` ฉะนั้นแล้วเราจึงสามารถส่งผ่าน data type เข้าไปได้แทนตัว `E`

~~~~~java
ArrayList<BankAccount> bank = new ArrayList<BankAccount>();
~~~~~

ทีนี้ถามว่าใส่แล้วเกิดอะไรล่ะ? เราก็เลื่อนไปดูเมธอดของมันก็จะพบว่า

    boolean	add(E e) : Appends the specified element to the end of this list.

แสดงว่า เมื่อเราใส่อะไรเข้าไปแล้ว มันจะบังคับว่าต้อง add เป็นชนิดนั้นเท่านั้น (จากเดิมที่เป็นชนิดอะไรก็ได้) และ

    E	get(int index) : Returns the element at the specified position in this list.

แสดงว่า เวลาเรา get มันก็จะ return ออกมาเป็นชนิดที่เราส่งเข้าไป ดังนั้นจากที่ปกติจะต้องใส่ (BankAccount) x.get(0) ก็ไม่ต้องแล้ว เพราะเราบังคับแล้วว่า ArrayList นี้นั้นเก็บได้เฉพาะ BankAccount และจะคืนเป็น BankAccount เสมอ

(เข้าใจว่าเรื่องนี้อยู่ใน OOP2 นะ)

## Polymorphism

ทีนี้กลับไปใช้ ArrayList กันแบบปกติกัน

~~~~java
ArrayList x = new ArrayList();
x.add(new SavingAccount(3000, 1));
((SavingAccount) x.get(0)).deposit(5000);
~~~~

จะเห็นว่าเราต้อง `(SavingAccount) x.get(0)` เพื่ออะไร?

คำตอบคือ ArrayList ที่ไม่ใส่ `<..>` นั้นจะเก็บข้อมูลเป็นชนิด Object (ซึ่งถ้าสังเกตใน Eclipse ตอนสร้าง class จะเห็นว่าทุกอย่าง inherit มาจาก Object) ดังนั้นมันจึง return ออกมาเป็น  type Object

ทีนี้พอได้ Object มา เราสามารถใช้เมธอดอะไรก็ได้ที่มีอยู่ใน Object เช่น `toString()` เป็นต้น แต่ `deposit` ไม่ใช่ ฉะนั้นเราจึงต้องแปลงกลับก่อน ก็คือ

~~~~java
(SavingAccount) x.get(0);
~~~~

(อาจจะคุ้นๆ ตอนที่มันเคยเป็นรูป `int x = (int) 5.35;` หรือเรียกว่า casting)

ก็จะทำให้ได้ผลเป็น SavingAccount ก่อนจะทำอย่างอื่นต่อไปได้

ทีนี้ มันมีข้อพิเศษอยู่ว่า **ไม่จำเป็นต้องแปลงกลับเป็นตัวคลาสของมันเอง แต่สามารถเป็นตัวแม่ของมันก็ได้** (แต่เป็นตัวลูกของมันไม่ได้นะ) หรือแม้แต่ Interface ที่ `implements` ไว้ก็ได้ด้วย ฉะนั้นโค้ดเราจึงใช้วิธีนี้

~~~~~java
BankAccount account = (BankAccount) x.get(0);
x.deposit(5000);
~~~~~

สังเกตว่า ไม่ต้องสนใจว่ามันเป็น `Saving` หรือ `Checking` เพราะทั้ง inherit มาจาก `BankAccount` และ `BankAccount` มีเมธอด `deposit` เป็นอันใช้ได้

เรื่องนี้ไม่จำเป็นแค่เป็นการ cast ตัวแปร แต่ใช้เก็บค่าก็ได้ เช่น

~~~~java
BankAccount account = new SavingAccount(5000, 1);
~~~~

ก็ไม่ผิดแต่อย่างใด ฉะนั้นใน StoreGUI เราจึงใช้วิธีนี้ในการเปิดหน้าต่าง...

~~~~java
private class OpenDialogHandler implements ActionListener{

	private Runnable run;

	public OpenDialogHandler(Runnable run){
		this.run = run;
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		this.run.run();
	}

}
~~~~

~~~~java
JButton button = new JButton("Take order");
button.addActionListener(new OpenDialogHandler(this.takeOrderMenu));
~~~~

(เพราะ `TakeOrderMenu` implements `Runnable`)