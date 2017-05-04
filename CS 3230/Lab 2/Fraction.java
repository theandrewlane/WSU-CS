/**
 * Created by Andrew Lane on 9/13/15.
 * Lab 2
 * WSU - CS3230
 */

public class Fraction {
    private int numerator, denominator;

    //If there's no denominator, set it to 1.
    public Fraction(int numerator) {
        this.numerator = numerator;
        this.denominator = 1;
    }

    public Fraction(int numerator, int denominator) {
        //This isn't required, but what if the user creates a fraction -5/-2? it should be 5/2.
        if(numerator < 0 && denominator < 0){
            numerator*=-1;
            denominator*=-1;
        }
        this.numerator = numerator;
        this.denominator = denominator;
        reduceFrac(numerator, denominator);
    }

    private static int gcd(int u, int v) {
        u = Math.abs(u);
        v = Math.abs(v);
        while (u > 0) {
            if (u < v) {
                int t = u; // swap u and v
                u = v;
                v = t;
            }
            u -= v;
        }
       return v;
    }
    private void reduceFrac(int num, int den){
        int v = gcd(num, den);
        this.numerator /= v;
        this.denominator /= v;
    }

    //Given a fraction, add the numerators if the denominator is the same
    // If not, calculate the least common denominator, multiply throughout, then add.
    public Fraction add(Fraction f) {
        if (this.denominator == f.denominator)
           return new Fraction(this.numerator + f.numerator, denominator);
        else{
            int lcd = lcd(this.denominator, f.denominator);
            return new Fraction((this.numerator*(lcd/this.denominator) + f.numerator*(lcd/f.denominator)), lcd);
        }
    }

    //Given a fraction, subtract the numerators if the denominator is the same
    // If not, calculate the least common denominator, multiply throughout, then add.
    public Fraction sub(Fraction f) {
        if (this.denominator == f.denominator)
            return new Fraction(this.numerator - f.numerator, denominator);
        else{
            int lcd = lcd(this.denominator, f.denominator);
            return new Fraction((this.numerator*(lcd/this.denominator) - f.numerator*(lcd/f.denominator)), lcd);
        }
    }

    public Fraction div(Fraction f) {
            return new Fraction(this.numerator * f.denominator, this.denominator * f.numerator);
    }

    public Fraction mult(Fraction f) {
        return new Fraction(this.numerator * f.numerator, this.denominator * f.denominator);
    }

    private int lcd(int denom1, int denom2)
    {
        int factor = denom1;
        while ((denom1 % denom2) != 0)
            denom1 += factor;
        return denom1;
    }

    public String toString() {
        return numerator + "/" + denominator;
    }

    public Boolean equals(Fraction f) {
        return (this.numerator == f.numerator && this.denominator == f.denominator);
    }


    public static void main(String args[]) {
        Fraction a = new Fraction(-1,30);
        Fraction b = new Fraction(-2,60);
        System.out.println( b.add(a).toString());

    }
}
