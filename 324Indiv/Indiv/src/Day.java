
import java.lang.String ;
import java.util.ArrayList;



public class Day {
private int date;
public Hour[] hours;
private int maxOverlap;
private Employee[] availableWorkers;
private int Start;
private int End;
public ArrayList<KVpair> EmpHours;

/*
 * Constructor takes the date(int), max number of employees who can work at once(int)
 * an array of the employees who can work that day, store open, and store
 * close hours(int)
 * It then places all emplyees into the hours they are available
 */

public Day(int date,int maxOverlap, Employee[] availableWorkers, int Start, int Ennd){
  this.Start = Start;
  this.End = Ennd + 1;
  this.date = date;
  this.availableWorkers = availableWorkers;
  this.hours = init_hours(Start, End);
  this.maxOverlap = maxOverlap;
  this.EmpHours = initEmpHours();
  this.The_Algorithm();
}
/*
 * Places all employees into the hours they are available
 * In: store open and close hours(int)
 * Out: array of Hours with employees inserted
 */
  private Hour[] init_hours(int Start, int End){
    Hour[] hours = new Hour[End - Start];
    hours = init_hours_helper(hours);
    String[] strtend = new String[2];
    int shiftstart;
    int shiftend;

    for(Employee emp : availableWorkers){
      if(! emp.getDay(this.date).equals("0")){
        
      strtend = emp.getDay(this.date).split("-");
      shiftstart = Math.max((Integer.parseInt(strtend[0]) - Start), 0);
      shiftend = Math.min((Integer.parseInt(strtend[1]) - Start), End - Start);
        
        for(int i = shiftstart; i < shiftend; i++){
          hours[i].add(emp.getId());
        }
    }
  }
    return hours;
  }

  /*
   * Helper for init_hours, initializes all Hours as empty ArrayLists
   */
  private Hour[] init_hours_helper(Hour[] hours){
    for(int i = 0; i<hours.length; i++){
      hours[i] = new Hour();
    }
    return hours;
  }
  
  /*
   * This is a function that sets up a list of all employees on a particular day and
   * pairs it with the number of hours they are scheduled, for algorithm purposes
   * In: none
   * Out: List of KVpairs: (Employee Name, # of Hours Scheduled)
   */

  public ArrayList<KVpair> initEmpHours(){
    ArrayList<KVpair> EmpHours = new ArrayList<KVpair>();
    String Emp = "";
    for(int i = 0; i < this.hours.length; i++){
      for(int j = 0; j < this.hours[i].getsize(); j++){
        Hour currHour = this.hours[i];
        Emp = currHour.getName(j);
        boolean found = false;
        for(KVpair pair : EmpHours){
          if(Emp.equals(pair.getkey())){
            pair.plus_v1();
            found = true;
          }
        }//for each pair already in the list
        if(!found){
          EmpHours.add(new KVpair(Emp, 1));
        }// if not yet in list
      }//for each name in an hour
    }//for each hour
    return EmpHours;
  }

/*
 * gets hours that the employee is currently scheduled for that day
 * IN: String emp :ID of employee
 * OUT: int :number of hours scheduled
 */
public int getEmpHours(String emp){
  for(KVpair pair : EmpHours){
    if(pair.getkey().equals(emp)){
      return pair.getvalue();
    }
  }
  return 0;
}

/*
 * gets index of the employee in the EmpHours ArrayList
 * IN: String emp :ID of employee
 * OUT: int :Index in arrayList Emphours
 */
private int getEmpIndex(String emp){
  int index = 0;
  for(KVpair pair : EmpHours){
    if(pair.getkey().equals(emp)){
      return index;
    }
    index++;
  }
  return 0;
}

/*
 * gets secondary value of a chosen employee
 */
private int getChosenHours(String emp){
  for(KVpair pair : EmpHours){
    if(pair.getkey().equals(emp)){
      return pair.getvalue_2();
    }
  }
  return 0;
}

private void plusEmpHours(String emp){
  for(KVpair pair : EmpHours){
    if(pair.getkey().equals(emp)){
      pair.plus_v1();
    }
  }
}

private void plusChosenHours(String emp){
  for(KVpair pair : EmpHours){
    if(pair.getkey().equals(emp)){
      pair.plus_v2();
    }
  }
}

public void minusEmpHours(String emp){
  for(KVpair pair : EmpHours){
    if(pair.getkey().equals(emp)){
      pair.minus_v1();
    }
  }
}

/*
 * cull removes any employee with two or less hours from the day
 */
private void cull(){
ArrayList<String> culls = new ArrayList<String>(); 
for(int i = 0; i < this.hours.length;i++){
  for(String emp : this.hours[i].list){
    if(getEmpHours(emp) < 3) culls.add(emp);
  }
}
for(int i = 0; i < this.hours.length;i++){
  for(String emp : culls){
    if(this.hours[i].list.contains(emp))this.hours[i].list.remove(emp);
    this.EmpHours.get(getEmpIndex(emp)).set_v1(0);
  }
}
}//cull

/*
 * returns the first employee that occurs in a day
 */
private String getFirst(){
for(int i = Start; i< End; i++){
  if(hours[i].getsize() != 0){
    return hours[i].getName(0);
  }
  }
return "";
}

private ArrayList<String> pickBest(ArrayList<String> list, String Incumbent, int hour){
ArrayList<String> newList = new ArrayList<String>();
int numChosen = 1;
//System.out.println("Incumbent is " + Incumbent + " at hour " + hour);

//Pick the Employee(s) to keep



if(list.contains(Incumbent) && getChosenHours(Incumbent) < 8) {
  //System.out.println("Incumbent chosen");
  newList.add(Incumbent);
  plusChosenHours(Incumbent);
}else {
    if(list.size() > 0 && !list.get(0).equals(Incumbent)) {newList.add(list.get(0));
  }else if(list.size() > 1){
    newList.add(list.get(1));
  }else{
    newList.add("");
  }//else 2
}//else 1

while(numChosen < maxOverlap && numChosen < list.size()){
  newList.add(list.get(numChosen));
  plusChosenHours(list.get(numChosen));
  numChosen++;
}//while

//Confirm that those who were not kept are not working
for(String allEmp : list){
  boolean contains = false;
  for (String  keptEmp: newList) {
    if(keptEmp.equals(allEmp)){
      contains = true;
    }//if the Emp is kept set to true
  }// for each kept employee
  if(!contains){
    minusEmpHours(allEmp);
  }
}// for each emp in the hour
return newList;
}//pickBest


public void The_Algorithm(){
String Incumbent = getFirst();

//if(Incumbent.equals("")) return; //if Day is empty
for(int i = Start - Start; i < End - Start; i++){
  cull();

  if(!(this.hours[i].list.contains(Incumbent))){
  if(this.hours[i].list.size() > 0){
      Incumbent = this.hours[i].list.get(0);
    }else{
      Incumbent = "";
    }
  }//if
  this.hours[i].list = pickBest(this.hours[i].list, Incumbent, i);
  if(!(this.hours[i].list.contains(Incumbent))){
    if(this.hours[i].list.size() > 0){
      Incumbent = this.hours[i].list.get(0);
    }else{
      Incumbent = "";
    }//if hour is empty
  }// if the new hour doeds not have the incumbent
}//for every hour
}//The_Algorithm


public boolean isDone(){
for(int i = 0; i < this.hours.length; i++){
  if(this.hours[i].list.size() > maxOverlap) return false;
}
return true;
}

public void updateHcounts(){
ArrayList<KVpair> countList = new ArrayList<KVpair>();
String temp;
boolean cont = false;
int iters = 0;
int index = 0;
for(int i = 0; i < this.hours.length; i++){
  for(int j = 0; j< this.hours[i].list.size();j++){
    temp = this.hours[i].list.get(j);
    iters = 0;
    for(KVpair pair : countList){
      if(pair.getkey().equals(temp)){
        cont = true;  
        index = iters;
      }
      iters++;
    }//for
    if(!cont){
      countList.add(new KVpair(temp, 1));
    }else countList.get(index).plus_v1();
  }
}//construct a list of hour counts

for(KVpair countpair : countList){
  for(KVpair empPair : EmpHours){
    System.out.println("Cp: " + countpair.getkey() + "\nEp: " + empPair.getkey());
    if(countpair.getkey().equals(empPair.getkey())){
      System.out.println("Changing Count for " + empPair.getkey() + " from " + empPair.getvalue() + " to " + countpair.getvalue());
      empPair.set_v1(countpair.getvalue());
      System.out.println("Count for " + empPair.getkey() + " is now " + empPair.getvalue());
    }
  }
}
}//updateHcounts

public void mitigate(String emp1, String emp2, int hour){
String first = "";
KVpair fhrs = new KVpair(first, 0);
String last = "";
KVpair lhrs = new KVpair(last, 0);
int switch1 = 0;//has 1 been init
int switch2 = 0;//has 2 been init
int switch3 = 0;//which emp is first

for(int i = 0; i < this.hours.length; i++){
  if(this.hours[i].list.contains(emp1) && switch1 == 0){
    System.out.println("Initializing" + emp1 + ", starts at " + i);
    if(switch2 == 0){
      first = emp1;
      fhrs = new KVpair(first, i); 
    }else{
      last = emp1;
      lhrs = new KVpair(last, i);
    }
    switch1 = 1;
    
  }//if emp 1 is in hour and not initialized

  if(this.hours[i].list.contains(emp2) && switch2 == 0){
    System.out.println("Initializing" + emp2 + ", starts at " + i);
    if(switch1 == 0){
      first = emp2;
      fhrs = new KVpair(first, i); 
      switch3 = 1;
    }else{
      last = emp2;
      lhrs = new KVpair(last, i);
    }
    switch2 = 1;
  }// if emp 2 is in hour and not initialized
}//for loop for first

switch1 = 0;
switch2 = 0;

for(int i = this.hours.length - 1; i >= 0; i--){
  if(this.hours[i].list.contains(emp1) && switch1 == 0){
    System.out.println("Finalizing" + emp1 + ", end at " + i);
    if(switch3 == 0){
      fhrs.set_v2(i);
    }else{
      lhrs.set_v2(i);
    }
    switch1 = 1;
    
  }//if emp 1 is in hour and not initialized
  
  if(this.hours[i].list.contains(emp2) && switch2 == 0){
    System.out.println("Finalizing" + emp2 + ", end at " + i);
    if(switch2 == 0){ 
    if(switch3 == 1){
      fhrs.set_v2(i);
    }else{
      lhrs.set_v2(i);
    }
    switch2 = 1;
    }
  }// if emp 2 is in hour and not initialized
}//for loop for first

String cut;

if((lhrs.getvalue() - hour) > (hour - fhrs.getvalue_2())){
  cut = first;
  for(int j = fhrs.getvalue_2(); j > hour - 1; j--){
    this.hours[j].list.remove(cut);
  }//for
}else{
  cut = last;
  for(int j = lhrs.getvalue(); j < hour + 1; j++){ 
    this.hours[j].list.remove(cut);
  }//for
}
}//mitigate

public void The_Algorithm_2(){
int maxHour = 0;

while(!isDone()){
  cull();
//find max overlap
  System.out.println(this.hours.length);
  for(int i = 0; i < this.hours.length; i++){
    if(this.hours[i].list.size() > maxHour){
      maxHour = i;
    }
  }
  maxHour--;
  if(this.hours[maxHour].list.size() <= maxOverlap)break;
    mitigate(this.hours[maxHour].list.get(0), this.hours[maxHour].list.get(1), maxHour);
    updateHcounts();
}//while not done
}//The_Algorithm_2


  

@Override
public String toString() {
String str = "\"Day: "+ (this.date + 1) + "\n";
  for(int i = this.Start; i < this.End; i++){
    if(this.hours[i - this.Start].getsize() > 0){
str = str  + i + ":00 ; " + this.hours[i - this.Start].toString() + "\n";
    }// if not empty
  }// for every hour
str = str + "\"";
return str;
}//toString
}
