# Database Lecture 1 - 16 Jan 2015

## Introduction to Database Management

- Database is used everywhere esp. in modern organizations. They store large amount of data for analysis. For example, customer purchasing data so they can know how to organize products on the show floor.
- Database is a major transformation in computing skills. In database there is a language that is very easy and increase programming productivity.
- Database is a self-describing collection of interrelated data
  - Database is self-describing
    - contains data dictionary (metadata) (eg. table wateruser has 6 column, the primary key is ID. the table electricuser has id column as number of length 3) this data is updated automatically by the system
    - contains indices (eg. id 101 is at position 1, 102 is at position 2)
    - contains application metadata (stored procedure/function - program codes, query, form, report) if we want to change the output format of function instead of editing the program we can change in the database
  - Database is a collection of interrelated data (a database tends to store data that are related to each other)
- Database can be accessed by database applications or use DBMS query tools but these applications will connect to the database through the DBMS (database management system) which manages query optimization (optimizing commands and transform into executable code)

**Vocabularies**

- **Data**: raw facts about things and events
  - eg. employee data: name, salary, address or images, video, maps are also data
- **Information**: data that has been transformed to create value for usage
  - summarized data, reports, student transcripts

Some textbooks use these terms interchangably.

## Data formats

Data in computer are stored in word processor, spreadsheet, file or database.

Text file is a simple form of data storage format which store unorganized string of characters seperated by end of line character and ends with end of file character.

Spreadsheet is another data storage format which organize data into column and rows. Spreadsheet softwares allows operations on data such as finding the average. The cons of spreadsheet software is that it has a limit on column and rows so it is not suitable for large amount of data.

File of record is a data storage format which is commonly used before the age of database (1960s). We write application that allows users to enter data into the file easily. To use this file you have define the data structure and then open the file. The cons is the file cannot be shared easily so data have to be duplicated and when we update data it has to be updated in every places otherwise we would get data inconsistency.

The limitation of file processing is that it requires a lot of programming in high level language. The file cannot be used in multiple programs as the file structure has to be loaded in the program. The cost of maintenance is high as data has multiple duplicates that needs to be updated. The security is low because the file system does not support multiuser access really well.

The database was developed in 1970s which has a few types: hierachical database, network database. Relational database was developed in 1980s which become popular because it is very simple and easy to use.

- File: bits > bytes > fields > records > files
- Database: bits > bytes > fields > records > files + metadata + indices + application metadata > database
  - Metadata is data about data. The DBMS (database management system) stores data structure in the metadata called data dictionary
  - Comparing to the real world: library (database) stores books (data) and index cards (metadata)

## Characteristics of database

- Persistent - data lasts a long time
- Inter-related - data are related. They can be stored seperately but linked with relationship.
- Shared - data are shared between applications and supports multiple simultaneously users with concurrency control (allow reads, but not simultaneously write)

## Database application development

1. Database design
   - Data modeling - how the data will be represented in the database
   - Use entity-relationship diagram which can use to model data in all database models
2. Create database
   - Use commands (SQL) or graphical tools to instruct DBMS to create the designed database
3. Develop application

## Three schema architecture

- External level
  - What user see. May have multiple view (eg. transcript view has student name and courses, salary view has professor name and salary)
- Conceptual level
  - What programmer use. Data is splitted to tables
- Internal Level
  - Index types
  - Storage types
  - Server location

In file storage if the structure is updated all applications have to be updated, but in database each level changes doesn't affect other layer

## DBMS

DBMS provides:

- Tools for creating data
- Languages for creating/manipulating data
  - Procedural language - languages that are run sequentially eg. Java/C++
  - Non-procedural language - languages that the system computes run order automatically (you tell what you want, not the way to get it) eg. SQL
- Tools for application development
  - Form: formatted document for entering data and displaying
  - Report: formatted document for displaying

## SQL

SQL stands for Structural Query Language. It can create tables, retrieve, insert, update, delete data and query data to answer a question. It is a descriptive language which means that the DBMS must parse it into procedural form.

Example of SQL:

```sql
SELECT * FROM people WHERE name = $name
```

Similar to this code:

```py
def find(name):
	db = open('people')
	out = []
	for person in db:
		if person == name:
			out.append(person)
	return out
```

Procedural language (Java, COBOL, etc.) can interact with SQL to allow for complex processing and performance improvements.

## DBMS

Inside the database management system there are multiple subsystems.

- User query & reporting
- Application development
- Data dictionary
- Security and Integrity
- Database access

It supports:

- Create database
- Writing applications
- Data accessing without writing program
- Security/integrity management

Kinds of DBMS:

- Desktop DBMS - single user eg. Access, FoxPro
- Enterprise DBMS - multiuser, multiple applications eg. SQL Server, Oracle
- Embedded DBMS - database in devices

### Transaction processing

- Group code into a unit that should be processed together
- If the system fails during transaction the DBMS will rollback the entire process

## Client-server architecture

To support several users, servers database can be distributed to several locations. Data could be stored seperately (each branch of bank has their own DBMS) or distributed stored (every branch of bank has same dataset or called mirror so that if disaster struck the data is not lose easily)

In web-based system they also use client-server architecture but it is called "thin client" as the DBMS is not running on the client. The "thick client" is used in banks as the performance is faster. The client in thick client must install DBMS on their computer.

## Database specialist

- Database administrator (DBA)
  - More technical
  - DBMS specific skills
- Data administrator
  - Less technical
  - Focus on quality of data in the database

## Summary

- Database is important to all organizations that have a lot of data
- Database technology supports daily operations to policy making
- One great feature of database is nonprocedural access because it helps increase programmers productivity