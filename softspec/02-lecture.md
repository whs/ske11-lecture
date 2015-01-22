# SoftSpec Lecture 2 - 22 Jan 2015

## POS System

- POS task is to record sales
- Handle payment (work with 3rd party to process credit cards)
- Normally includes barcode scanner

Our goal

- Cross platform (can be web, desktop, anything that runs Java)

## Inception

Inception is a phase to make mutual understanding from everyone of what we're going to do. We take a look at most important requirements in this phase.

In POS, the most important flow is checkout.

We look at critical functional and non-function requirements. Functional requirement is when something doing something. For example, cashier scan something into the system and it is displayed on the display. Non-functional requirement is static. For example, legal requirement.

The questions to ask in inception are:

- The vision of this project
- Is it cheaper to buy it instead of build it?
- Cost range?
- Do it?

### Analogy

If you're an oil company and know an area that may contains oil. You might want to perform exploratory drilling.

In this inception step you have to evaluated from the data you have to decide that you want to drill it or not.

### Categories of requirements

FURPS+ is developed by HP and is widely used.

- Functional - things that happen, things that the system can do
- Usability - eg. can read text from 2 meters
- Reliability
- Performance - eg. can response in 0.1s
- Supportability - how can it be supported, localized, etc.

### Artifacts in inception

(Go read [01-summary](01-summary.md))

### Prototyping

- Paper prototyping
- Powerpoint

### Use case

Use case is simple for non technical people. It is good for scaling up and down (brief, casual, formal, ...).

Users might think in terms of UI but we want to specify on the intend of the user instead. For example, don't say that user enter data in a text box (that could be changed to combo box later on)

Don't use too much words in the use case and don't specify the lower level stuff.

#### Use case example

- POS
  - A customer arrive at checkout with items to purchase
  - The cashier use POS to record each purchased item
  - The system presents a running total and line item detials
  - The customer enters payment information
  - The system validate and record
  - The system update inventory
  - The customer receive a recipt and return with the items

##### Casual example

Main Scenario [Success]:

- A customer arrives at checkout
- The cashier record the item succesfully.

Alternate Scenario [Rejected]:

- A customer arrive at checkout
- If customer paid by credit but it is rejected the customer pay by cash

Alternate Scenario [Item id not found]:

- A customer arrive at checkout
- If item identifier is not found, notify the cashier and suggest manual entry

##### Fully dressed example

Read the book page 68-72

- **Scope**: SKE POS
- **Level**: user goal
- **Primary Actor**: Cashier
- **Stakeholder and Interests**
  - Cashier: wants fast, accurate, no payment errors
  - Salesperson: wants sales commision updated
  - Customer: want to purchase with minimal effort, want item price and name displayed on screen, want to be able to return
  - Company: accurate record, satisfied customers
  - Manager: wants to be quickly perform override operations
  - Goverment: wants to collect sale tax
  - Payment Authorization Service: wants to received digital authorization requests in the correct format and protocol. wants accurate account information
- **Precondition:** Cashier is identified and authenticated *(things that happen before this use case)*
- **Postcondition:** Sale is saved. Tax is calculated *(things that must happen if this use case success)*
- **Main Success Scenario:**
  1. Customer arrives at POS
  2. blah blah blah
- **Alternative flows:**
  - **\*A** At any time, manager requests override (\*a = flow that can branch any time from the main branch)
    1. ....
    2. ....
  - **\*B** System fails
    1. ....
    2. ....
- **Special Requirements**
  - Touch screen UI on a large flat panel monitor
  - Text must be visible from 1 meter away
  - Multilanguage
  - Pluggable business rules at steps 3-7
- **Technology and Data varation list**
  - Manager can override by swiping card or enter code by keyboard
- **Frequency of occurence:** Could be nearly continuous
- **Open issues:**
  - What are the tax law variations?
  - Can customer use the card reader directly?

#### Best use case

No requirement is perfect. As long as everyone understand it it is OK.

#### Actor

Actor is something that can act

- Primary actor: goal are fulfilled in the use case
- Supporting actor: provide service in use case but doesn't get any benefit
- Offstage actor: related but doesn't appear in the use case. eg. the program might use a tax calculation program but it is not in the requirement directly.

### Vision

Read the book!

## Observer pattern

```java
public class Listener implements Observer {
	private void heardSomething(String name) {
		System.out.println("I heard " + name + " said something.");
	}

	@Override
	public void update(Observable o, Object arg){
		heardSomething((String) arg);
	}
}
public class Speaker extends Observable {

	private String name;

	public Speaker(String name){
		this.name = name;
	}

	public void speak(){
		System.out.println("Say something");
		setChanged();
		notifyObservers(name);
	}
}
public class Main {
	public static void main(String[] args){
		Speaker speaker = new Speaker("Jim");
		Listener listener = new Listener();
		speaker.addObserver(listener);
		speaker.speak();
	}
}
```

Output:

```
Say something
I heard Jim said something.
```

This is good because `Speaker` and `Listener` doesn't know each other directly yet know of others' action.