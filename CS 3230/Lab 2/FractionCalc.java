import java.util.ArrayList;
import java.util.Scanner;
import java.util.StringTokenizer;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * Created by Andrew Lane on 9/13/15.
 * Lab 2
 * WSU - CS3230
 */
public class FractionCalc {
    public static volatile boolean done = false; //This is used specifically for threading. It tells the threads when to start execution

    //Read user input with scanner and do not loop if isFraction is false
    public static String getUserInput() {
        System.out.println("Please enter a two fraction mathematical expression");
        Scanner s = new Scanner(System.in);
        if (s.hasNext()) {
            String input = s.nextLine().trim();
            if (isFraction(input)) return input;
        }
        System.out.println("You did not enter a valid expression\nEx. 1/2 * -3/4\nProgram will now exit!");
        System.exit(0);
        return null;
    }

    /*
    * Parse the expression into a token stream.
    *
    * These threads and lambda expressions will provide faster execution over other non-threaded approaches.
    * It's worth noting that due to this program's simplicity, threading won't really make a difference :)
     */
    public static void parseAndExecute(String input) {
        String token, token2, token3;
        ArrayList<String> tokens = new ArrayList<String>();
        input = input.replaceAll("--", " - -"); //This is just in case the user enters something like 1/2--3/4, the tokenizer needs to separate everything
        StringTokenizer st = new StringTokenizer(input, "/ () + *"); //Strip the input of "/"
        if (input.chars().filter(e -> e == '/').count() == 3) new Thread(() -> division(tokens)).start();
        if (input.chars().filter(e -> e == '+').count() == 1) new Thread(() -> addition(tokens)).start();
        if (input.chars().filter(e -> e == '*').count() == 1) new Thread(() -> multiplication(tokens)).start();
        while (st.hasMoreTokens()) {
            token = st.nextToken();
            if (token.endsWith("-") || token.matches("-(\\d+)-(\\d+)") || token.matches("(\\d+)-(\\d+)")) new Thread(() -> subtraction(tokens)).start();
            if (token.matches("(\\d+)-(\\d+)") || token.matches("-(\\d+)-(\\d+)")) {
                Pattern pattern = Pattern.compile("(\\d+)");
                Pattern pattern2 = Pattern.compile("^-(\\d+)");
                Matcher matcher2 = pattern2.matcher(token);
                Matcher matcher = pattern.matcher(token);
                while (matcher.find()) {
                    tokens.add(matcher.group(0));
                }
                while (matcher2.find()) {
                    tokens.add(matcher2.group(0));
                }
            }
            if (!token.matches("(\\d+)-(\\d+)") && !token.contains("*") && !token.endsWith("+") && !token.endsWith("+") && !token.endsWith("-"))
                tokens.add(token);
            done = tokens.size() == 4 ? true : false;
        }
    }

    //Assemble the tokens into fractions, use the this.mult() function from the Fraction class
    public static void multiplication(ArrayList<String> tokens) {
        while (!done);

        boxOutput(new Fraction(Integer.parseInt(tokens.get(0)), Integer.parseInt(tokens.get(1))).mult(new Fraction(Integer.parseInt(tokens.get(2)), Integer.parseInt(tokens.get(3)))).toString());
    }

    //Assemble the tokens into fractions, use the this.add() function from the Fraction class
    public static void addition(ArrayList<String> tokens) {
        while (!done);
        boxOutput(new Fraction(Integer.parseInt(tokens.get(0)), Integer.parseInt(tokens.get(1))).add(new Fraction(Integer.parseInt(tokens.get(2)), Integer.parseInt(tokens.get(3)))).toString());
    }

    //Assemble the tokens into fractions, use the this.sub() function from the Fraction class
    public static void subtraction(ArrayList<String> tokens) {
        while (!done);
        boxOutput(new Fraction(Integer.parseInt(tokens.get(0)), Integer.parseInt(tokens.get(1))).sub(new Fraction(Integer.parseInt(tokens.get(2)), Integer.parseInt(tokens.get(3)))).toString());
    }

    //Assemble the tokens into fractions, use the this.div() function from the Fraction class
    public static void division(ArrayList<String> tokens) {
        while (!done);
        boxOutput(new Fraction(Integer.parseInt(tokens.get(0)), Integer.parseInt(tokens.get(1))).div(new Fraction(Integer.parseInt(tokens.get(2)), Integer.parseInt(tokens.get(3)))).toString());
    }

    //Validate user's input and make sure it's a fraction expression
    //This is based on the provided RegExDemo.java file
    public static boolean isFraction(String input) {
        return input.matches("-?[0-9]+[ \\t]*/[ \\t]*-?[0-9]+[ \\t]*[+-/\\\\*][ \\t]*-?[0-9]+[ \\t]*/[ \\t]*-?[0-9]+");
    }

    //Make the expression's result pretty
    //Print 0 if the numerator is 0
    //Print numerator if denominator is 1
    public static void boxOutput(String input) {
        if (input.startsWith("0")) input = "0";
        if (input.endsWith("1") && (input.indexOf("/")+1 == input.lastIndexOf("1"))) {
            Pattern pattern = Pattern.compile("^.+(?=/)");
            Matcher matcher = pattern.matcher(input);
            while (matcher.find()) {
                input = (matcher.group());
            }
        }
            input = "Evaluated Expression Result: " + input;
        System.out.print("+");
        for (int i = 0; i < input.length() + 2; i++)
            System.out.print("-");
        System.out.println("+");
        System.out.println("| " + input + " |");
        System.out.print("+");
        for (int i = 0; i < input.length() + 2; i++)
            System.out.print("-");
        System.out.println("+");
    }

    //Run this beast!
    public static void main(String[] args) {
        parseAndExecute(getUserInput());
    }
}
