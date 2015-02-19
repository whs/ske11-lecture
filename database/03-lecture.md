# Database lecture 3 - 13 February 2015

## Relational Data Model

Relational data model is simple to the programmer but the internal operation is not well obvious.

A relational database is a collection of tables. The schema of data are also stored in tables as well. The relationship between data is expressed as primary keys.

In a table we have name and column names. A row in a table is a entity and must have the same structure. A data in relational database cannot be duplicated. We can append data to table indefinitely.

Table is stored physically as a file that store rows consecutively. As the schema is stored in another table, the schema is stored in another file.

E-R model can be compared to relational model:

E-R model            | Relational model
---------------------|------------------
Entity type          |table
Entity instance      |row
Relationship         |reference using key
Attribute            |column
Primary key required | Some table may not have primary key
                     | Foreign key

Some terminologies:

Table-oriented | Set-oriented                     | Record-oriented
---------------|----------------------------------|-----------------
Table          | Relation                         | Record-type, File
Row            | Tuple (eg. ('John', 'CPE', 3.1)) | Record
Column         | Attribute                        | Field

In each table there is a column with unique value. It is called primary key.

## Relationship

In E-R we have one to one, one to many, many to many relationship but in relational model the many to many relationship is not supported

To store one to many relationship we add an extra column that store the primary key of another table we want to link to. When we want to get the data we've linked, we have to use that key to lookup in the linked table. So, this column in the linked table should have a unique value. The one to one relationship can also be stored this way or just store it in one table.

The primary key from another table that are stored in a table to link them together is called a **foreign key**.

To store many to many relationship we use two one to many relationship to a special table called **associative table**.

![Diagram 1](img/03-diagram-01.txt)

Some definitions:

- **Superkey**: column(s) with unique values
- **Candidate key**: superkey with only really important column (that are still unique)
- **Primary key**: a selected candidate key that contains no null value to be the representitive of an entity
- **Foreign key**: column(s) whose values must match the values in a candidate key of another table
- **NULL value**: empty/unknown value (eg. customer with no phone number has NULL as their stored phone number)
- **Entity integrity**: Each table must have a primary key that is unique and not null
- **Referential integrity**: Foreign key must match candidate key of source table (cannot refer to a non-existing primary key). In some case foreign key could be null.
- **Self-reference relationship**: When foreign key references to same table. Eg. a boss supervise a manager, a manager supervise employees. They're all stored in employee table.

Example for superkey:

A | B  | C   | D
--|----|-----|---
1 | 41 | 500 | m
1 | 42 | 600 | n
2 | 42 | 600 | o
3 | 43 | 750 | p

We can see that A, B, C alone can't be a superkey but if we combine A with B or A and C it can be a superkey. B and C together cannot be a superkey because they still contains duplicated value.

Sometimes we want to modify an entity that has foreign keys references to it. They're called **referenced row**. If we want to delete a row that has reference rows we must preserve referential integrity by changing their foreign key to other entity or delete them.

(eg. If we're going to delete a course, the course offerings should be deleted too or changed to NULL)

The actions to preserve referential integrity has their name:

- **Restrict**: prevent action if we have referenced rows (ie. cannot delete course)
- **Cascade**: perform action on referenced rows
  - **Nullify**: set foreign key of them to NULL (ie. course offerings are now referenced to NULL)
  - **Default**: set foreign key of them to the default value

## Algrebra operations

Tables can has algrebra operators performed on them to create a new table.

- Subset operator
  - Restrict: output a subset of rows that satisfied given logical condition (eg. `major = "Computer"`) similar to `if` in programming languages. The database will loop into each rows and check whether it satisfy the condition so you cannot compare a row to another row.
  - Project: output a subset of columns that are selected from the table. The database might eliminate duplicated rows for us.
  - They're often used together
- Extended cross product
  - Often used
  - We don't store duplicated data and we have many tables which are related. When we want to get data which are from multiple tables we have to combine them using this operator.
- Join operator
  - Similar to cross product, but only join data that are satisfying a condition
  - Most popular condition: primary key = foreign key
  - If the foreign key and primary key has the same column name the database can create the join condition automatically. This is called **natural join**.
- Outer join
  - Join but rows that does not satisfy the condition are not eliminated
  - eg. List of students and enrolled course. If some students are not enrolled to any course they will be omitted from outer join.
  - Variations:
    - Full outer join
    - One-sided join
      - Left outer join
      - Right outer join

Join example

**Table A**

ID | Name
---|------
A  | xx
B  | yy

**Table B**

ID | Text
---|------
A  | 11
A  | 22
-  | 33

**Cross product**

ID| Name | ID | Text
--|------|----|------
A | xx   | A  | 11
A | xx   | A  | 22
A | xx   | -  | 33
B | xx   | A  | 11
B | xx   | A  | 22
B | xx   | -  | 33

**Join**

ID| Name | Text
--|------|------
A | xx   | 11
A | xx   | 22

**Left outer join**

ID| Name | Text
--|------|------
A | xx   | 11
A | xx   | 22
B | yy   | - (unmatched)

**Right outer join**

ID| Name | Text
--|------|------
A | xx   | 11
A | xx   | 22
- | - (unmatched)    | 33

**Full outer join**

ID| Name | Text
--|------|------
A | xx   | 11
A | xx   | 22
B | yy   | - (unmatched left)
- | - (unmatched right)    | 33

- Set operators
  - Union
    - Input tables must have the same number of columns that are compatible (ie. same data type)
    - If they don't have the same column numbers we can convert data types, rename columns and remove some columns before applying union
  - Intersect
  - Minus
- Summarize operator
  - Compress group of rows to a calculated value
  - Use aggregate function to summarize rows (eg. average)
  - eg. monthly sale data from daily sale data, student and their GPA
- Divide operator
  - Some DBMS may not provides this operator
  - May use other operators together to mimics behavior
  - Match subset of data
    - eg. Suppliers who supply all parts

## SQL

- SQL is Structured Query Language
- Can be used standalone or in application writing
- 4 type of statements:
  - Definition (manipulate schema)
  - Manipulation (select, update, delete rows)
  - Control (grant permission)
  - Other

### `SELECT` statement

```sql
SELECT <column,..> FROM <tables>
WHERE <expression>
GROUP BY <columns> HAVING <expressions>
ORDER BY <sorting>
```

`SELECT ... FROM ...` is required but parts of the rest could be omitted.

Example:

```sql
SELECT * FROM Faculty
```

```sql
SELECT * FROM Faculty WHERE FacSSN = '543210987'
```

```sql
SELECT * FROM Faculty WHERE FacSalary > 65000 AND FacRank = 'PROF'
```

```sql
SELECT FacFirstName, FacLastName, FacCity, FacSalary*1.1, FacHireDate AS IncreasedSalary FROM Faculty WHERE year(FacHireDate) > 1991
```

```sql
SELECT * FROM Offering WHERE FacSSN IS NULL
```

(* is used in the column name place that indicates that all columns are selected)

The select command is similar to project of relational algebra.

The result of `SELECT` is a table which can be stored temporary or permanently to perform additional processing.

If the column name is ambiguous (joined table also contain column with the same name) you need to specify the table name in front of the column name followed by dot.

#### In exact matching

```sql
SELECT * FROM Offering WHERE CourseNo LIKE '204*'
```

(Access use *, but Oracle use % to indicate that any character may follows)

#### Date

Date are not standard feature of SQL.

```sql
SELECT * FROM Faculty WHERE FacHireDate BETWEEN '1-Jan-1994' AND '31-Dec-1995'
```

(Oracle syntax)

#### Join

Specify join condition in `WHERE`

```sql
SELECT *
FROM Offering, Faculty
WHERE Faculty.FacSSN = Offering.FacSSN
```

(Access)

```sql
SELECT *
FROM Offering INNER JOIN Faculty
  ON Faculty.FacSSN = Offering.FacSSN
```

#### Summarize

```sql
SELECT branch_name, SUM(balance)
FROM account
GROUP BY branch_name
```

```sql
SELECT FacRank, AVG(FacSalary) AS AvgSalary
FROM Faculty
GROUP BY FacRank
```

```sql
SELECT StdMajor, AVG(StdGPA) AS AvgGpa
FROM Student
WHERE StdClass IN ('JR', 'SR')
GROUP BY StdMajor
HAVING AVG(StdGPA) > 3.1
```

The select must only contains columns that are used in group by.

The `HAVING` clause is for specifying group condition while the `WHERE` clause is for specifying select conditions.