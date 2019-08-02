import java.util.Comparator;

/**
 * @class Par: estrutura abriga 2 objetos de tipos diferentes
 * @param <Tipo1> Tipo do primeiro objeto
 * @param <Tipo2> Tipo do segundo objeto
 */
public class Par<Tipo1, Tipo2>{
    private Tipo1 obj1;
    private Tipo2 obj2;

    /**
     * Construtor
     * @param o1 primeiro objeto
     * @param o2 segundo objeto
     */
    public Par(Tipo1 o1, Tipo2 o2){
        obj1 = o1;
        obj2 = o2;
    }

    /**
     *
     * @return primeiro objeto
     */
    Tipo1 getObj1(){
        return obj1;
    }

    /**
     *
     * @return segundo objeto
     */
    Tipo2 getObj2(){
        return obj2;
    }



}