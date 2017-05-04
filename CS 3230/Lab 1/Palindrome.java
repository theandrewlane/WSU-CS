import java.util.Arrays;
import java.util.Scanner;

/**
 * Created by Andrew Lane on 9/3/15 for CS3230.
 */
public class Palindrome {
    //Defining messages for user
    private static final String greetingMessage = "Please enter a potential palindrome string:";
    private static final String noPdromeMessage = "\"is NOT a palindrome!";
    private static final String pDromeMessage = "\" IS a palindrome!";
    private static final String tryAgainMessage = "Are you going to actually enter a string here or what?\nTry again.\n";


    public static void main(String[] args) {
        String pdrome = (args.length > 1 && args != null && args.toString() != "") ? Arrays.toString(args).replace(",", "").replace("[", "").replace("]", "").trim() : getUserInput();
        System.out.println("Checking if " + "\"" + pdrome + "\" is a palindrome...");
        if (isPalindrome(pdrome)) {
            boxOutput("\"" + pdrome + pDromeMessage);
            System.exit(0);
        }
        boxOutput("\"" + pdrome + noPdromeMessage);
    }

    //if the user hasn't passed in any args via command line
    public static String getUserInput() {
        System.out.println(greetingMessage);
        Scanner s = new Scanner(System.in);
        String input = s.nextLine();
        if (input.trim().length() < 1) {
            System.out.println(tryAgainMessage);
            return getUserInput();
        }
        return input;
    }

    /*
    * Make the final output pretty
    * Code revised from Namebox.java
    */
    public static void boxOutput(String input) {
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


    //Here's the actual palendrome check
    public static boolean isPalindrome(String s) {
        s = s.replaceAll("\\W", "").toLowerCase();
        return s.equals(new StringBuilder(s).reverse().toString().replaceAll("\\W", "").toLowerCase());
    }
}
