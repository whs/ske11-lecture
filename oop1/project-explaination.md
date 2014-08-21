# GUIProject

## Object storage

เวลาเก็บข้อมูลใน static fields คลาสอื่นจะสามารถเข้ามาเรียกได้ ดังนี้

~~~~java
class Store{
	public static String data = "hello world";
}

class Main{
	public static void main(String[] args){
		System.out.println(Store.data);
	}
}
~~~~

จะสังเกตว่า ไม่ต้อง `new Store()` ก่อนก็สามารถเรียกข้อมูลใน `data` ได้เพราะเป็น static

โปรแกรมนี้ใช้สมบัตินี้ในการเก็บข้อมูล คือ

~~~~java
public class Store{
	private static Store instance = new Store();
	public static Store getInstance(){
		return instance;
	}
}
~~~~

เมธอด `getInstance` ชื่ออาจจะฟังดูยาก แต่จริงๆ ก็คือ getter ธรรมดา

เมื่อคลาสอื่นๆ อยากได้ Store ก็  `Store.getInstance()` ก็จะได้ store เดียวกันตลอด ไม่ว่า class ไหนจะเรียก ถ้าใช้ new ก็จะได้ store คนละอัน ส่งผลให้การข้อมูลแต่ละหน้าไม่ตรงกัน

วิธีเก็บข้อมูลแบบนี้มีชื่อเรียกว่า Singleton pattern (ชื่อไม่สำคัญ จำวิธีทำงานก็พอ) มาจากที่ว่า instance นั้นโปรแกรมนึงมีแค่อันเดียว (single) คือที่ return จาก `getInstance()` ไม่ว่าคลาสไหนเรียกก็จะได้ instance ตัวเดียวกันเสมอ

Shopping Cart ก็ใช้วิธีนี้เช่นกันในการเก็บข้อมูล ส่วน Bills นั้นใช้ `ArrayList` ที่เป็น static field (ตัวแปร `Bill.bills` เป็น `ArrayList`)

## Serializable

ทีนี้เวลาเซฟข้อมูล กลุ่มอื่นๆ จะใช้วิธีเอาข้อมูลแต่ละแถวโยนลงไฟล์ คั่นด้วย space แล้วใช้ Scanner อ่าน แต่เพื่อความรวดเร็วในการพัฒนาเราเลยใช้ระบบ Serializable ซึ่งมีอยู่ใน Java บันทึกแทน

ระบบนี้จะทำให้คลาสอะไรก็ได้ที่ implements `Serializable` สามารถบันทึกลงไฟล์ได้ โค้ดไปดูในอ่านเพิ่มเติมเอา

ทีนี้เวลาโหลดข้อมูลกลับมา ก็จะได้ object ตัวเดิมกลับมาเลย เสมือนไม่มีการปิดโปรแกรมเกิดขึ้น ตรงนี้ทำให้เราไม่ต้องเสียเวลาใช้ scanner อ่านข้อมูลแล้วแปลงเป็น object เอง

ในโปรแกรมนี้ `Store`, `Stuff`, `Customer` ต่างเก็บข้อมูลใน `Serializable` หมด และเนื่องจาก array และ `ArrayList` ก็เป็น `Serializable` ก็เลยเอา `Bill.bills` โยนลงไฟล์ได้ด้วย

เพิ่มเติม: http://pagist.info/6f66495127be09d45180

## HashMap

ทีนี้มีไฟล์ๆ เดียว จะเก็บข้อมูลยังไงตั้งสี่ห้าอย่าง (store, stuff, customer, bills, cloud key) วิธีการก็คือเก็บข้อมูลเป็นตาราง ซึ่ง java มีระบบตาราง 2 column ให้ชื่อว่า HashMap ซึ่งจะเหมือน dict ใน Python

สมบัติของ HashMap คือ มี key กับ value ถ้ารู้ key สามารถหา value เดิมได้เสมอ

~~~~~java
HashMap<String, String> hm = new HashMap<String, String>(); // ระบุว่า key เป็น String, value เป็น String
hm.add("key", "value");
System.out.println(hm.get("key")); // แสดงคำว่า value
~~~~~

โปรแกรมนี้ใช้วิธีโยนข้อมูลทั้งหมดไปใส่ใน hashmap ตัวเดียว แล้วเอา hashmap นั้นเขียนลงไฟล์ผ่านระบบ serializable ทั้งหมดนี้คือการทำงานของคลาส `storage.FileStorage` แต่คลาสนี้นั้นตัว instance กลับไปเก็บที่คลาส `object.File` *(เหตุผลที่แยกกันเก็บคือจะล้อการทำงานของระบบ cloud)*

เพิ่มเติมในสไลด์

## Facade

ต่อมาเราพบว่า เวลาจะเซฟข้อมูลเนี่ย ระบบที่เก็บข้อมูลใน HashMap มันมีตั้งหลายอย่าง จะเขียนแบบนี้หรอ?

~~~~java
Store.save();
Customer.save();
Bills.save();
~~~~

แล้วจุดที่เซฟได้มีเยอะมาก ทั้งหน้า take order, restock, clear profit ถ้าต่อไปเพิ่มการเก็บข้อมูลอีกคลาสนึงแล้วลืมใส่ให้ครบทุกหน้าก็ซวยล่ะสิ

วิธีการคือทำคลาสๆ นึง ซึ่งมีเมธอดที่เรียกเมธอดพวกนี้อีกที

~~~~~java
public class Persistent{
	public static void save(){
		Customer.save();
		Bill.save();
		Store.save();
		File.getInstance().save();
	}
}
~~~~~

(ในโค้ดคือ `storage.Persistent`)

เวลาจะเซฟก็แทนที่จะต้องก๊อปแปะการเซฟ เราก็แค่เรียก `Persistent.save();` (ไม่ต้อง new เพราะเป็น static)

วิธีนี้มีชื่อเรียกว่า Facade pattern มาจาก Facade ที่แปลว่าผนังด้านหน้า คือทำให้เมธอดที่เราเรียกมันดูเรียบร้อยน่ารักมาก โดยไม่ต้องสนใจการทำงานด้านหลัง

## Adapter

ทีนี้ในหน้าที่เราทำจะเห็นว่ามันใช้ `JTable` ซึ่งตัว `JTable` การใช้มันซับซ้อนนิดนึง คือมันไม่ทราบว่าตารางที่เราอยากได้มีกี่แถวมีกี่ช่อง ในช่องมีข้อมูลอะไรบ้าง มันก็เลยใช้ระบบ adapter มาแปลงโดยกำหนดให้ extend จาก class  `AbstractTableModel` ของ Java

ใน class ของเราจะมีเมธอด `getColumnCount` `getRowCount` `getColumnName` มีหน้าที่ก็ตามชื่อเลย และเมธอด `getValueAt(int row, int col)` ก็คือให้แถวนี้คอลัมน์นี้มา แล้ว return ไปว่าต้องการแสดงค่าอะไรในช่องนั้นๆ

ในโค้ดอยู่ที่ไฟล์ `view.BillUI` และ `object.ShoppingCart`

และเนื่องจากว่า class นี้สามารถใช้ดึงข้อมูลทั้งหมดในตารางออกมาได้อยู่แล้ว เราเลยเอาสมบัตินี้ไปใช้ในการทำระบบ search ด้วย ก็คือเวลา search

1. for ไปทีละแถวจาก `getRowCount`
2. for ไปทีละคอลัมน์จาก `getColumnCount`
3.  เรียกค่าในช่องนั้นจาก `getValueAt`
4. เช็คว่าค่านั้นมีส่วนใดส่วนหนึ่งตรงตามคำค้นที่ผู้ใช้กรอกมาหรือไม่
5. ถ้าใช่ก็ให้เน้นแถวนั้น

(โค้ดอยู่ใน `actionPerformed` ของปุ่ม Search ใน `view.BillUI`)

วิธีนี้มีชื่อเรียกว่า Adapter pattern คือ ทำให้คลาสหนึ่งมีเมธอดตรงตาม interface ได้ โดยเขียนอีกคลาสหนึ่งมาครอบไว้อีกที (ชื่อ pattern ไม่ต้องจำก็ได้ จำการทำงานของมันก็พอว่าคลาสไหนทำงานยังไง)

## Reflection

**ความเห็นส่วนตัวถ้าว่ามันเยอะจำไม่ได้ reflection ในโค้ดนี้ใช้อยู่สองบรรทัด ข้ามไปเลยไม่ต้องจำก็ได้**

อันนี้ต้องขอโทษด้วยว่า design โปรแกรมในส่วนของเราก็รีบจนมันห่วย คือ `view.BillUI` มันถูก extend ไปยังหลายๆ หน้า แล้วเราต้องการเพิ่มปุ่ม export เฉพาะหน้า Bill ซึ่งวิธีที่ดีที่สุดคือเขียนคลาสที่หน้า Bill จะ extend มา แต่เรากลัวจะไม่ทันเลยใช้วิธีนี้แทน

ถ้าดูในเมธอด `initComponents` หรือ `tableDblClick` จะเห็น `this.getClass().getName() == BillUI.class.getName()` มันคืออะไร

มันคือการเช็คว่าคลาสนี้คือ `BillUI` หรือไม่นั่นแหละ แต่มันใช้ `instanceof` เช็คไม่ได้ เพราะคลาสลูกเช็คด้วย `instanceof` ก็ถือว่าเป็นคลาสแม่ด้วย เลยต้องใช้วิธีนี้ (อาจจะมีวิธีดีกว่า นึกไม่ทัน)

เมธอด `.getClass().getName()` จะ return ชื่อคลาสเต็มๆ ออกมาเช่น `view.BillUI` แล้วเราก็ไปเทียบกับ BillUI ของจริงว่ามีชื่อว่าอะไร ถ้าตรงกันก็โอเคใช่

## CSV Export

ขึ้นส่วนที่เข้าใจง่ายดีกว่า ในส่วนนี้คือปุ่ม CSV Export ที่อาจจะตะลึงว่าทำไมมันเปิดกับ Excel ได้ฟะ

ถ้าศึกษาฟอร์แมต CSV จะพบว่า excel เปิดไฟล์นามสกุล .csv ได้ โดยรูปแบบของไฟล์เป็นดังนี้

~~~~
col1,col2,col3
val1,val2,val3
val1,val2,val3
~~~~

พูดง่ายๆ คือตารางที่เอาคอมม่าคั่นนั่นแหละ (csv = comma-seperated values) ฉะนั้นแล้วเราก็เลยใช้ `FileWriter` (ในเล็คเชอร์บทเดียวกับ ArrayList กลุ่มอื่นๆ ก็ใช้คลาสนี้เซฟข้อมูล)

(โค้ดอยู่ที่ `view.BillUI` คลาส `CSVExportHandler` อาจจะดูหรู จริงๆ ก็คือ `ActionListener` ของปุ่ม export นั่นแหละ)

ถ้าเปิดไฟล์ `export.csv` ดูก็จะเห็นรูปแบบประมาณนี้

~~~~
No,Date,Customer Name, Customer Type,Customer Email,Discount %,#MacBook Air 11",Price/Unit,Total Price,#MacBook Air 13",Price/Unit,Total Price,#MacBook Pro 13",Price/Unit,Total Price,#MacBook Pro Retina 13",Price/Unit,Total Price,#MacBook Pro Retina 15",Price/Unit,Total Price,#Mac Mini,Price/Unit,Total Price,#iMac 21.5",Price/Unit,Total Price,#Mac Pro,Price/Unit,Total Price,#Apple TV,Price/Unit,Total Price,#iPad 2,Price/Unit,Total Price,#iPad Air,Price/Unit,Total Price,#iPhone 4s,Price/Unit,Total Price,#iPhone 5c,Price/Unit,Total Price,#iPhone 5s,Price/Unit,Total Price,#iPod Classic,Price/Unit,Total Price,#iPod Shuffle,Price/Unit,Total Price,#iPod Nano,Price/Unit,Total Price,#iPod Touch,Price/Unit,Total Price,Discount,Bill total
1,Sun Dec 01 23:36:58 ICT 2013,user,1,user@example.com,10.00,0,31900.00,0.00,0,34900.00,0.00,0,37900.00,0.00,0,43000.00,0.00,1,66900.00,1.00,0,19900.00,0.00,0,44900.00,0.00,0,99000.00,0.00,0,3800.00,0.00,0,13500.00,0.00,0,16900.00,0.00,0,14900.00,0.00,0,19900.00,0.00,0,23900.00,0.00,0,8900.00,0.00,0,2200.00,0.00,0,5500.00,0.00,0,9900.00,0.00,6690.0,66900.0
~~~~

ลองนั่งนับคอมม่าแถวหนึ่งกับแถวสองดูก็น่าจะพอเดาได้ว่าเลขเยอะๆ แต่ละตัวคืออะไรบ้าง หรือถ้างงก็เอา Excel เปิดเถอะ

สุดท้ายเพื่อความอลังนิดหน่อย เลยให้ Java เปิด excel ให้ด้วย โค้ดก็ไม่ยาก

~~~~java
Desktop.getDesktop().open(file);
~~~~

มันก็จะเปิดไฟล์ที่เขียนเสร็จแล้วใน Excel

เราคิดว่าถ้าบอกกลุ่มอื่นว่า excel มันอ่านแบบนี้ได้นี่ใครๆ ก็เขียนได้เลยนะ มันอยู่ในเรื่องที่สอนแล้ว 100% ที่เค้างงกันก็เพราะไม่รู้จักไฟล์ csv เท่านั้นเอง

## Print

โค้ด print มีอยู่สองส่วน คือในส่วน GUI

~~~~java
Bill bill = Bill.bills.get(row);
PrinterJob job = PrinterJob.getPrinterJob();
job.setPrintable(bill.print());
if(job.printDialog()){
	try{
		job.print();
	}catch(PrinterException e){
	}
}
~~~~

(`view.BillUI` เมธอด `tableDblClick`)

ในส่วนนี้ก็คือสร้างคลาส `PrinterJob` มา (อยู่ใน Java) แล้วกำหนดหน้าที่จะพิมพ์ เสร็จแล้วก็ขึ้นหน้าต่างพิมพ์ปกติ ถ้าผู้ใช้ตกลงพิมพ์ก็สั่งพิมพ์ ไม่พิมพ์ก็เลิก

สำหรับไฟล์ที่เป็นเนื้อหาในงานพิมพ์ก็อยู่ที่คลาส `print.Bill` วิธีการคือสร้างคลาสมาที่ implements `Printable` (อันนี้ Java มีให้) แล้วมันจะมีเมธอดบังคับอันนึงมา ในเมธอดนี้จะให้ `Graphics` มา ที่เหลือก็สามารถใช้คำสั่งวาดใน `Graphics` ได้ เหมือนกับการบ้าน Histogram ฉะนั้นโค้ดอาจจะดูยาวและอลังหน่อยๆ ก็ไม่ต้องตกใจเพราะการบ้าน Histogram ก็น่าจะเป็นแบบนั้นกัน