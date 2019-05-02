import jdk.swing.interop.SwingInterOpUtils;
import org.junit.Test;

import static org.junit.Assert.*;
public class ListaCircularTest {

    private ListaCircular lc;
    private Par extra = new Par(32,(double)0.88);
    @org.junit.Before
    public void setUp() throws Exception {
        lc = new ListaCircular(10);

        double d = 0.5;
        for(int i=0; i<10; i++){
            Par p = new Par(i, i+d);
            lc.addIni(p);
            System.out.println(p.getObj1());
            System.out.println(p.getObj2());
        }
    }

    @org.junit.After
    public void tearDown() throws Exception {
        lc = null;
    }

    @Test
    public void getObjs(){
        Object[] a = lc.getObjs();
    }

    @org.junit.Test (expected = Exception.class)
    public void addIni() throws Exception {
        double d = 93123.321312;
        Par p = new Par(54, d);
        lc.addIni(p);
        assertNotNull(lc.getObjs());
    }

    @org.junit.Test
    public void addFim() throws Exception {
        lc = new ListaCircular(10);
        lc.addFim(extra);
    }
    @org.junit.Test (expected = Exception.class)
    public void addFim2() throws Exception {
        lc = new ListaCircular(10);
        double d = 0.5;
        for(int i=0; i<=10; i++){
            Par p1 = new Par(i, i+d);
            lc.addFim(p1);
        }

    }

    @org.junit.Test
    public void addFim3() throws Exception {
        lc = new ListaCircular(10);
        for(int i=0; i<10; i++){
            lc.addFim(extra);
        }
        lc.removeIni();
        lc.addFim(extra);
    }



    @org.junit.Test
    public void removeIni() {
        lc = new ListaCircular(10);
        Object o = lc.removeIni();
        assertNull(o);
    }
    @org.junit.Test
    public void removeIni2() throws Exception {
        Object o = lc.removeIni();
        assertNotNull(o);
    }
    @org.junit.Test
    public void removeIni3() throws Exception {
        for(int i=0; i<10; i++)
            lc.removeIni();

    }


    @org.junit.Test
    public void removeFim() {
        lc = new ListaCircular(10);
        Object o = lc.removeFim();
        assertNull(o);
    }

    @org.junit.Test
    public void removeFim2() throws Exception {
        Object o = lc.removeFim();
        assertNotNull(o);
    }

    @org.junit.Test
    public void removeFim3() throws Exception {
        Object o;
        for(int i=0; i<10; i++){
            o = lc.removeFim();
        }
    }



}