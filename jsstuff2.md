# JavaScript class

JavaScript ไม่มี OOP ในลักษณะเดียวกับภาษา Java แต่จะใช้ลักษณะ [Prototype-based](https://en.wikipedia.org/wiki/Prototype-based_programming)

~~~~js
// Constructor
var MyObject = function(x){
	this.x = x;
};
// Method
MyObject.prototype.getX = function(){
	return this.x;
};

// การใช้งาน
var instance = new MyObject("Hello, world");
console.log(instance.getX());
// ไม่มี visibility
console.log(instance.x);
~~~~

ข้อดีของระบบนี้คือสามารถที่จะต่อเติมคลาสได้ตลอดเวลา

~~~~js
MyObject.prototype.logX = function(){
	console.log(this.x);
};
instance.logX();
~~~~

เมื่อรันโค้ดนี้ต่อจากโค้ดที่แล้วจะเห็นว่า `MyObject` ทุกตัวจะมีเมธอด `logX` ขึ้นมาทันที การใช้งานอย่างหนึ่งของความสามารถนี้คือการเข้าไปแก้ไข object ของระบบให้มีความสามารถมากขึ้น ซึ่งใช้ในไลบรารีบางตัว เช่น [PrototypeJS](http://prototypejs.org/)

~~~~js
// https://github.com/sstephenson/prototype/blob/master/src/prototype/lang/array.js#L222
Array.prototype.first = function(){
	return this[0];
};

console.log(["a", "b", "c"].first());
~~~~

(ทั้งนี้มีข้อถกเถียงกันว่าการแก้ไข object ระบบดีหรือไม่ เพราะถ้าใช้หลายๆ ไลบรารีอาจจะเกิดการชนกันได้ง่าย)

## Other style of inheritance

บางทีอาจจะเห็นการเขียนคลาสในลักษณะนี้

~~~~js
var Person = function(name){
	this.name = name;
	this.sayName = function(){
		console.log(this.name);
	}
};
var instance = new Person("Madoka");
instance.sayName();
~~~~

ปัญหาของวิธีนี้คือเมธอด `sayName` จะถูกสร้างใหม่ทุกครั้งที่มีการสร้างคลาส `Person` ทำให้ช้ากว่าวิธีอื่นๆ

## Inheritance

เนื่องด้วยว่า JavaScript ไม่มีคลาสแท้ๆ จึงมีผู้คิดค้น Inheritance ใน JavaScript โดยอาศัยการ copy `prototype` ของ object นั้นๆ มาใส่ในออพเจ็กท์ใหม่

วิธีนี้โค้ดค่อนข้างยาวพอสมควร ศึกษาได้จากบล็อคของ [John Resig](http://ejohn.org/blog/simple-javascript-inheritance/) (ผู้พัฒนา jQuery)

~~~~js
var Being = Class.extend({});
Being.prototype.breath = function(){
};

var Human = Being.extend();
Human.prototype.eat = function(){
};
Human.prototype.breed = function(){
};
~~~~

เพื่อความสะดวก ไลบรารีนี้ยอมให้เราส่งเมธอดไปในรูปแบบของ hash ได้

# Hash

ใน JavaScript มีตัวแปรชนิดหนึ่งเรียกว่า Object แต่เพื่อไม่ให้งงขอเรียกว่า hash แล้วกัน

ทุกอย่างใน JavaScript เป็น object หมด รวมถึง primitive types ด้วย เช่นใช้ `2..toString()` ก็ได้ (สังเกตว่าการใช้เมธอดกับตัวเลขมี . สองครั้ง เพราะถ้ามีจุดเดียวมันจะนึกว่ากำลังจะระบุทศนิยม) แต่ในทีนี้เราจะมาพูดถึง object พื้นฐานกัน

Hash มีหน้าตาแบบนี้

````js
var x = {
    "key": "value",
    "key2": "value2"
};
````

โดย key เป็น string และ value เป็นอะไรก็ได้ รวมถึง hash ซ้อน

เมื่อเรามี hash แล้วและรู้ key สามารถหาค่าได้

````js
console.log(x.key);
console.log(x["key"]);
````

ทั้งสองแบบนี้ได้ผลลัพท์เหมือนกัน แบบแรกสั้นกว่า แบบหลังสามารถระบุ key ด้วยตัวแปรได้

## Inheritance (cont)

กลับมาที่ไลบรารีของเรา เราสามารถสร้างคลาสแบบเดียวกันได้ด้วยโค้ดนี้

````js
var Being = Class.extend({
	breath: function(){
	}
});
var Human = Being.extend({
	eat: function(){
	},
	breed: function(){
	}
});
````

นั่นคือ ใช้แฮชที่มีชื่อเป็นชื่อเมธอด และค่าเป็นฟังก์ชั่นนั่นเอง

ข้อสังเกตคือในแฮชจะต้องมีลูกน้ำคั่นระหว่างสมาชิกเสมอ ถ้าตกไปก็จะเกิด error ขึ้นได้ ข้อแนะนำคือเราสามารถทิ้งลูกน้ำเกินไว้ได้โดยไม่ถือเป็น error

````js
var Human = Being.extend({
	eat: function(){
	},
	breed: function(){
	}, // ใส่ลูกน้ำทิ้งไว้เลย
});
````

# JSHint

เนื่องจาก JavaScript นั้นไม่มีการตรวจสอบโค้ดทำให้อาจจะมีข้อผิดพลาดเกิดขึ้นได้ง่าย เราสามารถใช้โปรแกรม JSHint ช่วยตรวจได้

## Online

สามารถใช้ JSHint แบบออนไลน์ได้ที่ [jshint.com](http://jshint.com)

## Terminal

สามารถติดตั้ง JSHint ได้โดยติดตั้ง node.js ก่อน แล้วติดตั้งผ่าน npm

### การติดตั้ง Node.JS (Debian/Ubuntu)

````bash
sudo apt-get install nodejs
````

### การติดตั้ง Node.JS (Arch Linux)

````bash
sudo pacman -S nodejs
````

### การติดตั้ง Node.JS (Mac)

ให้ติดตั้งโปรแกรม [Homebrew](http://brew.sh) ก่อน ซึ่งจำเป็นจะต้องติดตั้ง XCode ก่อน แล้วรันคำสั่ง

````bash
brew install nodejs
````

### การติดตั้ง JSHint

````bash
sudo npm install -g jshint
````

สามารถรันได้ด้วยการสั่ง `jshint file.js`

## Sublime Text

ต้องติดตั้งให้ใช้งานใน Terminal ได้ก่อนจึงจะใช้วิธีนี้ได้

สามารถติดตั้งปลั๊กอินได้ที่ [Sublime-JSHint](https://github.com/victorporof/Sublime-JSHint) และเรียกใช้โดยการกดปุ่ม Ctrl/Cmd+Shift+J

## ความสามารถ

[JSHint สามารถเตือนเรื่องดังต่อไปนี้ได้](http://www.jshint.com/docs/options/) โดยสามารถเปิดปิดได้ตามต้องการ

- การตั้งชื่อตัวแปรต้องเป็น `variableName` หรือ `VARIABLE_NAME` เท่านั้น
- บังคับให้ใส่ปีกกาเสมอ (เช่น หลัง if หรือ while)
- ห้ามไม่ให้แก้ไข `prototype` ของ object ที่มีอยู่แล้วในระบบ
- ชื่อ Constructor ต้องขึ้นด้วยตัวใหญ่เสมอ
- ห้ามใช้ `new` โดยไม่บันทึกผลลงตัวแปร
- บังคับให้ใช้ single quotes หรือ double quotes อย่างใดอย่างหนึ่งเท่านั้น
- แจ้งเตือนเมื่อมีการใช้ตัวแปรที่ไม่มีการประกาศไว้ (ถ้ามาจากไลบรารีอื่นๆ ที่หัวไฟล์จะต้องประกาศ `/* globals A, B, C */` เพื่้อบอกว่าตัวแปร A, B, C มีการประกาศแล้วที่ไฟล์อื่น)
- แจ้งเตือนเมื่อมีการประกาศตัวแปรแล้วไม่ได้ใช้