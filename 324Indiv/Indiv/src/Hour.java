import java.util.ArrayList;


public class Hour {
  public ArrayList<String> list;

  /*
   * Constructor initializes the arraylist of employees who are available during
   * that hour
   */
  public Hour(){
  this.list = new ArrayList<String>();
  }


  /*\
   * adds an employee by Id to the hour
   */
  public void add(String emp){
    this.list.add(emp);
  }

  /*
   * simple function for removing a specified name from the Arraylist
   * In: String of name you want removed
   */
  public void rm(String emp){
    for(int i = 0; i < this.list.size(); i++){
      if(emp.equals(list.get(i))){
        list.remove(i);
      }
    }
  }

  public String getName(int index){
    return this.list.get(index);
  }

  /*
   * Allows size of arraylist to be obtained in other classes
   * Out: size of ArrayList
   */
  public int getsize(){
    return this.list.size();
  }

  /*
   * Just using the ArrayList toString() for Hour
   */
 public String toString(){
  String str ="";
  for(int i = 0; i < this.list.size() - 1; i++){
    str = str + this.list.get(i) + ", ";
  }
  if(this.list.size() != 0) {
    str = str + this.list.get(this.list.size() - 1);
  }
  return str;

 };

}