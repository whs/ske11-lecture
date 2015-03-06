# Database lecture 4 - 27 February 2015

## Anomaly

If we don't use join but store duplicated data, we'll get many problems.

### Insertion anomaly

First problem is that we might lost data when we delete it.

For example if we store branch information together with loans. If we delete all loans of a branch, that branch's information is lost. If we use `NULL` to store the loan it would be hard to manage.

### Updating anomaly

Second problem is that when we update data, we have to update every instances of the data otherwise it would be inconsistent.

## Constraints

### Domain constraints

If we want to add a constraints on data (eg. age must be 20-60) the DBMS can do that for you by using validation rules. Or you can add a validation code to your application.

### Key constraint

The DBMS can check whether the key is unique and not null.

### Referential integrity constraint

The DBMS can check whether the referenced id exists in the referenced table or not.

## Atomic value

A value that cannot be divided to smaller unit. For example, a person name is non-atomic as it can be seperated to first name, middle name and last name.

## Building a database

You need to know

- Business rule
- Business process
- Data relationship
- Normal form definitions
  - Schematics of each attributes

### Normal form

- More normalization create more normal form
  - Less anomalies
  - More tables
- The first normal form all the domain are atomic
  - eg. seperate employee's skills into separate rows
- Second normal form seperate the attributes and key
  - eg. split course name and enrollments
- Third normal form is like 2nd normal form but without transitive dependencies
  - eg. product ID and type can determine its price. This is called transitive dependencies