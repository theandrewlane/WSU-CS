/*
* Andrew Lane
* Lab 4
* 10/21/15
*/

import java.util.Comparator;


public class CompareInt implements Comparator<Person>
{
    @Override
    //Compare 2 person objects by Id
    public int compare(Person p1, Person p2)
    {
        Integer firstId = p1.getId();
        Integer secondId = p2.getId();

        return firstId.compareTo(secondId);
    }
}