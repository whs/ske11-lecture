# Softspec lecture 7 - 26 March 2015

(note: the previous lectures are reiterative of past topics or hands on)

## Polymorphism

Polymorphism is when a class be in multiple types

A game has player, each player has 1 weapon. A weapon can be used to attack a monster. There can be many kind of weapons.

```java
public class Weapon {
	public static final int SWORD = 1;
	public static final int GUN = 2;

	private int type;

	public Weapon(int type){
		this.type = type;
	}

	public void attack(Monster monster){
		showAttackAnimation();
		monster.scream();
	}

	public void showAttackAnimation(){
		if(type == SWORD){
			System.out.println("Sword swings");
		}else if(type == GUN){
			System.out.println("Gun shoots");
		}
	}
}

public class Monster {
	public static final int SLIME = 1;
	public static final int BEAST = 2;

	private int type;

	public Monster(int type){
		this.type = type;
	}

	public void scream(){
		if(type == SLIME){
			System.out.println("Slime scream");
		}else if(type == BEAST){
			System.out.println("Beast scream");
		}
	}
}

public class Player {
	private Weapon weapon;

	public void attack(Monster monster){
		weapon.attack(monster);
	}

	public void setActiveWeapon(Weapon weapon){
		this.weapon = weapon;
	}
}

public class Main{
	public static void main(String[] args){
		Player p = new Player();
		Monster slime = new Monster(Monster.SLIME);
		p.setActiveWeapon(new Weapon(Weapon.SWORD));
		p.attack(slime);
	}
}
```

## Monopoly

## Indirection

## Pure Fabriction

## Protected Variation