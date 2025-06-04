public class Employee {

private String id;
private String[] availability;
public String schedule;

/*
 * Constructor takes a String for emplyoee name (id)
 * and a string of availability - Availability should take the form 
 * "(int startOfAvailability)-(int endOfAvaiability,0(for none), ..." 
 * for each day. every day in the month must be included as a range or a 0
 */
public Employee(String id, String availability){
this.id = id;
this.availability = toarray(availability);
this.schedule = "";
}

  /*
   * splits the availability string from constructor into an array
   * In: String of parameter described above
   * Out: String[] containing the range(or 0) of each day in the month
   */
  private String[] toarray(String str){
    String[] arr = new String[31];
    arr = str.split(",");
    return arr;
  }

  /*
   * Gets range(or 0) from a particular date. It is in array form
   * so it starts at index 0 instead of 1(it is intended for internal use only)
   */
  public String getDay(int date){
    return this.availability[date];
  }
  
  public String[] getAvailability() {
      return availability;
  }
  /*
   * returns the Id associated with the employee
   */
  public String getId(){
    return this.id;
  }

  @Override
  public String toString() {
    String str = this.id.toString();
    str = str + "\n";
    for(int i = 0; i < this.availability.length - 1; i++){
      str = str + this.availability[i] + ", ";
    }
    str = str + this.availability[this.availability.length - 1];
    return str;
  }
}
