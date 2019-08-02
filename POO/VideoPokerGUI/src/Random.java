import java.util.Calendar;
import java.lang.Math;

/**
*Essa classe permite gerar numeros aleatorios a partir
*de uma seed determinada ou aleatoria.
*@author daniel
*/

public class Random {
  private long p = 2147483648L;
  private long m = 843314861;
  private long a = 453816693;
  private long seed;

  public Random() {
    this.seed =  Calendar.getInstance().getTimeInMillis();
  }

  public Random(int k){
    this.seed = k;
  }

  public double getRand() {
   seed = (a + m * seed) % p;
   double d = seed; // promove p/ double
   return d / p;
  }

  public int getIntRand(){
    return getIntRand(Integer.MAX_VALUE);
  }

  public int getIntRand(int max){
    double d = getRand()*max;
    return (int) Math.abs(d);
  }

  public int getIntRand(int min, int max) throws IllegalArgumentException{
    if( max <= min )
     throw new IllegalArgumentException("Parametros invalidos");
    return min + getIntRand(max - min);
  }

  public void setSemente(int semente){
    this.seed = semente;
  }

}