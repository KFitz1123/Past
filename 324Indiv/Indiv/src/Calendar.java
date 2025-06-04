
import com.opencsv.CSVReader;
import java.lang.String ;
import java.util.ArrayList;
import java.io.Reader;
import java.io.FileReader;
import java.io.PrintWriter;
import java.util.List;
import java.io.File;
public class Calendar {

private String month;
private Day[] days;
private int maxOverlap;
private ArrayList<Employee> workers;
private int startH;
private int endH;
//private Employee[] workerArray;

public Calendar(String file){
  this.maxOverlap = 0;
  this.startH = 0;
  this.endH = 0;
  this.days = null;
  this.workers = walkCSV(file);
}

/*
 * monthdays takes a month as a string amd returns the number of days in that month
 * IN: String month: string is case insensitive, must be one of 12 months
 * OUT: int : number of days in typcal month(not FEB leap year)
 * 
 */
public int monthDays(String month){
  int daynum = 0;
  switch(month.toUpperCase()){
    case "JANUARY": daynum = 31;
    break;
    case "FEBRUARY": daynum = 28;
    break;
    case "MARCH": daynum = 31;
    break;
    case "APRIL": daynum = 30;
    break;
    case "MAY": daynum = 31;
    break;
    case "JUNE": daynum = 30;
    break;
    case "JULY": daynum = 31;
    break;
    case "AUGUST": daynum = 31;
    break;
    case "SEPTEMBER": daynum = 30;
    break;
    case "OCTOBER": daynum = 31;
    break;
    case "NOVEMBER": daynum = 30;
    break;
    case "DECEMBER": daynum = 31;
    break;
    default: daynum = 0;
    break;
  }
return daynum;
}

public int getdaynum(){
  return this.days.length;
}

public String getmonth(){
  return this.month;
}

/*
 * fillArray takes an arraylist of Employees and turns it into an array of employees
 * 
 */
private Employee[] fillArray(ArrayList<Employee> list){
  Employee[] workers = new Employee[list.size()];
  for(int i=0; i < list.size(); i++){
    workers[i] = list.get(i);
  }
  return workers;
}

/* 
 * WalkCSV takes a filename of a CSV file and initializes a the fields of the calendar
 *IN: String file  :file path
 * OUT: ArrayList<Employee> :the list of all employees working that month
 */
private ArrayList<Employee> walkCSV(String file){
  ArrayList<Employee> arr = new ArrayList<Employee>();
  Reader eye = null;
  List<String[]> csv;
  try {
  eye = new FileReader(file);
  CSVReader read = new CSVReader(eye);
  csv = read.readAll();

  this.days = new Day[monthDays(csv.get(0)[0])];
  this.month = csv.get(0)[0].toUpperCase();
  this.maxOverlap = Integer.parseInt(csv.get(0)[1]);
  this.startH = Integer.parseInt(csv.get(0)[2]);
  this.endH = Integer.parseInt(csv.get(0)[3]);

  String[] next = new String[2]; 
  Employee Intern;
  int i = 1;
  while(i < csv.size()){
    next = csv.get(i);
    Intern = new Employee(next[0], next[1]);
    arr.add(Intern);
    i++;
  }
  read.close();
  } catch (Exception e) {
    System.err.println("CSV Failed to Load");
    System.exit(1);
  }
  for(int j = 0; j < days.length; j++){
  //System.out.println("day " + j);
    days[j] = new Day(j , this.maxOverlap, fillArray(arr), this.startH, this.endH);
  }
  return arr;
}

/*
 * WriteCSV takes a file path and writes the calendar to a CSV at that location
 * IN String filename: path to a file you want to hold the resulting calendar
 * 
 */
public void writeCSV(String filename){
  PrintWriter pen = null;
  try{
  File written = new File(filename);
  pen = new PrintWriter(written);
  pen.println(toString());
  pen.close();
    }
  catch(Exception e){
  return;
  }
}

@Override
public String toString() {
  String str = "\"month is " + this.getmonth() + ", max employees per hour:" + this.maxOverlap + ", Opens: " + this.startH + ", Closes: " + this.endH + "\"\n";
    for(int i = 0; i< this.getdaynum(); i++){
      str = str + days[i].toString() + ",\n";
    }
    //str = str + "Opens: " + this.startH + "\nCloses: " + this.endH + "\n";

  return str;
}
}
