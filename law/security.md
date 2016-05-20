# Threats and Vulnerabilities

หัวข้อจาก http://www.professormesser.com/security-plus/sy0-401/sy0-401-course-index/

## Malware

Malware = โปรแกรมที่ไม่พึงประสงค์

1. **Virus** เป็นโปรแกรมที่ copy ตัวเองไปได้เรื่อยๆ อาจใช้ช่องโหว่ทำให้ทำงานเองได้โดยผู้ใช้ไม่ต้องทำะไรเลย
   - **Boot sector virus** ฝังตังเองไว้ในส่วน Boot sector ทำให้ถอดได้ยาก ปัจจุบันไม่มีแล้ว
   - **Program virus** ก็คือไวรัสทั่วๆ ไป เช่น ไวรัส Folder ปลอม
   - **Script virus** ไวรัสที่เขียนในภาษาสคริปต์ เช่น JavaScript หรือ .vbs ตัวอย่างเช่น Hacked by Godzilla (vbs)
   - **Macro virus** คือไวรัสที่ฝังมากับเอกสาร Microsoft Office เพราะเอกสารพวกนี้สามารถเขียนโปรแกรมพ่วงมาด้วยได้
   - **Worm** คือไวรัสที่ติดผ่านเครือข่ายได้ ถ้าเครื่องนึงติดเครื่องที่ต่อ LAN กันอยู่จะติดไปเองโดยอาศัยช่องโหว่ของโปรแกรม/OS ต่างกับไวรัสที่ต้องมีพาหะไป เช่น Flash drive สามารถป้องกัน worm ได้โดยติดตั้ง Antivirus และ Firewall ตัวอย่าง worm เช่น [Blaster](https://en.wikipedia.org/wiki/Blaster_(computer_worm)) (ที่มาของชื่อ [หยง บลัสเตอร์](http://th.uncyclopedia.info/wiki/%E0%B8%AB%E0%B8%A2%E0%B8%87%E0%B8%9A%E0%B8%A5%E0%B8%B1%E0%B8%AA%E0%B9%80%E0%B8%95%E0%B8%AD%E0%B8%A3%E0%B9%8C#.E0.B8.97.E0.B8.B5.E0.B9.88.E0.B8.A1.E0.B8.B2.E0.B8.82.E0.B8.AD.E0.B8.87.E0.B8.84.E0.B8.B3.E0.B8.99.E0.B8.B5.E0.B9.89))
   - ทั้งนี้ Virus ใช้เรียกตามลักษณะการแพร่กระจาย ไม่ได้กล่าวถึงพฤติกรรมเมื่อติดไวรัสแล้ว
2. **Adware/Spyware** คือโปรแกรมกวนใจที่จะแสดงข้อความโฆษณา เช่น Baidu PC Faster, Hao123 และอาจมีการดักข้อมูลผู้ใช้งานส่งกลับไปหาผู้ผลิตด้วย
3. **Trojan** คือโปรแกรมที่ดูเหมือนเป็นโปรแกรมดี เพื่อให้ user download มาใช้งาน แต่ฝังการทำงานประสงค์ร้ายไว้ เช่น Antivirus ปลอม
4. **Rookit** คือโปรแกรมที่จะเข้าไปฝังตัวเป็นส่วนหนึ่งของ OS เพื่อให้ตรวจจับได้ยากมาก (ไม่เห็นใน task manager) ตัวอย่างเช่น [Rootkit ใน CD เพลงของ Sony BMG](https://en.wikipedia.org/wiki/Sony_BMG_copy_protection_rootkit_scandal) เพื่อป้องกันการ copy CD ทำให้ Sony ถูกฟ้องร้อง
5. **Logic bomb** คือโค้ดที่ตั้งเวลาไว้ให้เกิดผลกระทบทีหลัง เช่นเกม [Spintires](https://www.reddit.com/r/pcgaming/comments/48juu7/spintires_publisher_installed_a_time_bomb_in_the/) ผู้พัฒนาตั้งเวลาไว้ให้เกมเด้งเพื่อป้องกันกรณีที่ publisher ไม่จ่ายเงินก็จะไม่ส่งโค้ดใหม่ให้
6. **Botnet** คือ malware ที่ทำให้เจ้าของ botnet ควบคุมคอมเราได้ เช่น ส่งไวรัส หรือยิง DDoS
7. **Ransomware** คือ malware ที่จะล็อคไม่ให้ใช้คอม หรือเข้ารหัสไฟล์ของเราไว้ และจะยกเลิกการทำงานเมื่อเราจ่ายเงินซื้อโค้ดปลดล็อคจากผู้สร้าง เช่น [TeslaCrypt](https://en.wikipedia.org/wiki/TeslaCrypt)
8. **Polymorphic malware** คือ malware ที่เปลี่ยนแปลงตัวเองไปเรื่อยๆ เพื่อป้องกันไม่ให้ antivirus ที่อาศัยการจับ checksum หรือพฤติกรรม (heuristic) จับได้
9. **Armored virus** คือไวรัสที่มีการเข้ารหัสไว้เพื่อป้องกันไม่ให้นักวิจัยวิเคราะห์การทำงานได้ เช่น [Stuxnet](https://www.wired.com/2011/07/how-digital-detectives-deciphered-stuxnet/)

## Attack

การ hack ทำได้หลายรูปแบบ ดังนี้

1. **Man in the Middle** *(MITM)* เรียกง่ายๆ ว่าดักฟัง มีทั้งแบบที่ดักฟังเฉยๆ และสามารถแอบแก้ไข (เพิ่ม/ลบ) ข้อมูลได้ด้วย โดยทั่วไปอาศัยเทคนิคที่ทำให้เปลี่ยนเส้นทางการเชื่อมต่อให้มาหาผู้โจมตี แล้วจากผู้โจมตีไปหาคู่สนทนา ![MITM](https://upload.wikimedia.org/wikipedia/commons/thumb/e/e7/Man_in_the_middle_attack.svg/260px-Man_in_the_middle_attack.svg.png)
2. **Denial of Service** *(DoS)* ก็คือการทำให้ล่ม อาจจะใช้ช่องโหว่ หรือยิงถล่มกันโต้งๆ ก็ได้ ถ้ายิงมาจากหลายที่พร้อมกันจะเรียกว่า Distributed Denial of Service (DDoS)
3. **Replay attack** คือการเอาข้อมูลที่ได้มาจากการดักฟังไปฉายซ้ำ เช่นโดนดักรหัสผ่านไป ถึงรหัสผ่านที่ส่งจะเข้ารหัสไว้ทำให้ไม่รู้รหัสจริง แต่ถ้าส่งข้อมูลนี้ซ้ำก็จะทำให้ login ได้เหมือนกัน ปกติแล้วจะใช้เทคนิค nonce (number used only once) แก้ปัญหา โดยเติมตัวเลขอะไรก็ได้เข้าไปในข้อมูลที่ส่ง แล้วตรวจจับเมื่อมีการใช้ตัวเลขเดิมซ้ำ
4. **Spoofing** คือการปลอมตัว อาจจะปลอมต้นทาง (เช่น ส่งอีเมลปลอม) หรือปลายทาง (Man in the Middle Attack)
5. **Spam**
6. **Phishing** คือการปลอมตัวลักษณะหนึ่ง โดยทำเว็บปลอมขึ้นมาแล้วส่งอีเมลไปหลอกให้เป้าหมายเข้ามาที่เว็บแล้วหลอกเอารหัสผ่าน ทั้งเว็บและอีเมลจะใช้รูปแบบคล้ายๆ ของจริงเพื่อให้เป้าหมายตายใจ ![Phishing](http://www.kasikornbank.com/TH/ServicesChannel/SearchServiceChannel/Internet/NewKCyberBanking/PublishingImages/for%20Security%20Tips/sample20phishing20K-Cyber-th.jpg)
7. **Vising** คือการทำ Phishing ทางโทรศัพท์ เช่น โทรมาหลอกให้โอนเงิน
8. **Christmas Tree Attack** เป็นการส่ง TCP packet ที่อยู่ในทุกสถานะพร้อมกัน (ผิดจาก TCP standard) ไปเพื่อสังเกตการทำงานของอุปกรณ์เป้าหมาย และอาจใช้เดา OS/รุ่นของ router เป้าหมายได้
9. **Privilege Escalation** คือการใช้ช่องโหว่เพื่อให้มีสิทธิ์มากกว่าโปรแกรมปกติได้ เช่นการ [Jailbreak iPhone](http://geohot.com/e7writeup.html)
10. **Insider Threats** ภาษาไทยเรียก สาวไส้ให้กากิน
11. **Transitive Attack** คือการที่โดนเจาะแล้วไปเจาะเครื่องอื่นต่อได้ เช่นถ้า firewall อนุญาตให้เข้าเครื่อง C ได้เครื่องเดียว ถ้า C โดนเจาะ เครื่อง A, B ก็อาจจะถูกเจาะโดยอาศัย C เป็นทางผ่าน
12. **Password attack**
   - **Brute force attack** คือการเดารหัสไปเรื่อยๆ ตำราภาษาไทยใช้คำว่า การตะลุย ป้องกันได้โดยจำกัดจำนวนครั้งที่ใส่รหัสผิดได้
   - **Dictionary attack** คือการลองรหัสจาก dictionary
   - **Hybrid attack** คือการใช้วิธีข้างบนผสมกัน เช่น เปลี่ยนตัวอักษรตัว a เป็น 4
   - **Birthday attack** ใช้ [Birthday problem](https://en.wikipedia.org/wiki/Birthday_problem) เป็นประโยชน์โดยการหา hash collision หรือข้อความที่ hash แล้วจะได้ hash เดียวกันกับรหัสผ่าน (อาจจะเป็นคนละข้อความกับรหัสผ่าน) แก้ไขได้โดยเลือกใช้ hash function ที่ป้องกัน hash collision ได้ดี เช่น MD5, SHA1 **ไม่**ควรใช้
   - **Rainbow table** คือการคำนวณ brute force เก็บใส่ไฟล์ไว้ล่วงหน้า เวลารหัสหลุดออกมาก็เปิดตารางตอบได้เลย
13. **URL Hijacking** คือการจดชื่อเว็บไซต์ดักคนพิมพ์ผิด เช่น gogle.com หรือเปลี่ยนนามสกุล เช่น ku.in.th
14. **Watering hole attack** คือการ hack เจาะจงเป้าหมาย โดยสังเกตพฤติกรรมเป้าหมายแล้วพยายาม hack สิ่งที่เป้าหมายใช้งานด้วย (เช่น เว็บไซต์) เพื่อให้เป้าหมายไม่สังเกต
