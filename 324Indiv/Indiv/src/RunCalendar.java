
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;


public class RunCalendar {
public static void main(String[] args) throws Exception {
  PrintWriter pen = new PrintWriter(System.out, true);
  pen.println("input the filepath to the CSV for availbaility");
  Scanner eye = new Scanner(System.in);
  String filename = eye.next();
  eye.close();

    Calendar cal = new Calendar(filename);//"/home/fitzgera/csc324/Indiv/Indiv/src/Schedule.csv");
    cal.writeCSV("DoneSched.csv");
  }

}
