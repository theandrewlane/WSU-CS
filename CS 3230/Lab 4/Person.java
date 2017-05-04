/*
* Andrew Lane
* Lab 4
* 10/21/15
*/


public class Person implements Comparable<Person>
{
    private int 	id;
    private String	name;
    private String	street;
    private String	city;
    private String 	state;
    private String 	phoneNumber;

    public Person(int num, String n, String s, String c, String st, String p)
    {
        id = num;
        name = n;
        street = s;
        city = c;
        state = st;
        phoneNumber = p;
    }

    public Person(String n)
    {
        id = 0;
        name = n;
        street = null;
        city = null;
        state = null;
        phoneNumber = null;
    }

    public Person(int n)
    {
        id = n;
        name = null;
        street = null;
        city = null;
        state = null;
        phoneNumber = null;
    }

    @Override
    //Concats all Person instance variables
    public String toString() { return id + " " + name + " " + street + " " + city + " " + state + " " + phoneNumber; }
    public int getId()
    {
        return id;
    }

    @Override
    //Should return an int... not a string like 1.d.iii. says.
    public int compareTo(Person person)
    {
        return name.compareTo(person.name);
    }

}