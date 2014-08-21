# Serializable

ใน Java มีระบบการเก็บ object ลงไฟล์และคืนรูปจากไฟล์อยู่แล้ว เรียกว่า Serializable

วิธีใช้ก็ง่ายๆ โง่ๆ เพียงแค่ implements `Serializable` ในคลาสที่เก็บข้อมูล และใส่โค้ดนี้ลงไป

~~~~java
private static final long serialVersionUID = 1L;
~~~~

ตัว 1L ก็คือเลข 1 ในชนิด `long` นี่ล่ะ ที่ต้องใส่เพื่อบอกว่าขณะนี้ object ตัวนี้เป็นโปรแกรม version 1 อยู่ เมื่อเรามีการเปลี่ยนแปลงข้อมูลซะจนคิดว่าข้อมูลเดิมไม่น่าโหลดขึ้นแล้ว ก็ควรจะเปลี่ยนเลข 1 เป็นเลขอื่นๆ เพื่อบังคับไม่ให้ serializable โหลดข้อมูลเดิมออกมา (ไม่ต้องเป็นเลขเรียงกันก็ได้นะ)

ตัวอย่างเช่น

~~~~java
package object;

import java.io.Serializable;

public class Product implements Serializable {
	private static final long serialVersionUID = 1L;
	private String name;
	private double price;
	
	public Product(String name, double price){
		this.name = name;
		this.price = price;
	}
	
	public String getName(){
		return this.name;
	}
	
	public double getPrice(){
		return this.price;
	}
	
	public void setName(String name){
		this.name = name;
	}
	
	public void setPrice(double price){
		this.price = price;
	}
		
}
~~~~

## Save

วิธีการเซฟไม่ยาก

~~~~java
import java.io.File;
import java.io.FileOutputStream;
import java.io.ObjectOutputStream;
// ...
File file = new File("file.txt");
ObjectOutputStream writer = new ObjectOutputStream(new FileOutputStream(file));
writer.writeObject(data);
writer.close();
~~~~

โดย `data` ก็คือตัวแปรที่เก็บ object ตัวนั้นๆ ไว้

## Load

วิธีการโหลดก็ไม่ยาก

~~~~java
import java.io.File;
import java.io.FileInputStream;
import java.io.ObjectInputStream;
// ...
File file = new File("file.txt");
ObjectInputStream reader = new ObjectInputStream(new FileInputStream(file));
data = reader.readObject();
~~~~

อย่าลืมแปลงกลับเป็น data type เดิม เช่น

~~~~java
Customer data = (Customer) reader.readObject();
~~~~

ก็จะได้ object ที่มีค่าเหมือนตอนเซฟกลับคืนมาทุกประการ

## Array

นอกจากนี้แล้ว primitive array (`int[]` และคณะที่ใช้ `[]` สร้าง) หรือ `ArrayList` ก็สามารถโยนเข้าไปใน `writeObject` ได้เช่นเดียวกัน

## Extending

กรณีคลาสที่ extend ต่อๆ กันมาอยู่ เช่น `Stuff` ควรทำ implements `Serializable` ในทุกคลาสที่เกี่ยวข้อง คือ `Product`, `ProductExt` และ `Stuff`