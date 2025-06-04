

/*
 * KVPair class inspired by polymorphic implementation I recall vaguely from Samuel Rebelsky
 */
public class KVpair {
  
  private String key;
  private int value;
  private int value_2;

  public KVpair(String key, int value){
    this.key = key;
    this.value = value;
    this.value_2 = 0;
  }

  public void set_v2(int val){
    this.value_2 = val;
  }

  public void set_v1(int val){
    this.value = val;
  }

  public void plus_v1(){
    this.value++;
  }
  public void minus_v1(){
    this.value--;
  }

  public void plus_v2(){
    this.value_2++;
  }
  public void minus_v2(){
    this.value_2--;
  }


  public String getkey(){ 
    return this.key;
  }

  public int getvalue(){ 
    return this.value;
  }

  public int getvalue_2(){ 
    return this.value_2;
  }


}
