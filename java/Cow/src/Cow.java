class Animal
{
	void saySomething()
	{
		System.out.println("Gurrr!");
	}
}

class Cow extends Animal 
{
	protected void saySomething()
	{
		System.out.println("Moo!");
	}
	public static void main(String[] args)
	{
		System.out.println("MooYa!");
		Animal [] animals = {new Animal(), new Cow()};
		for (Animal a : animals){
			a.saySomething();
		}
	}
}
