import org.junit.Before;
import org.junit.Test;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Random;


public class GrafoTest {

    private Grafo g;
    private Par<String, String> p = new Par("teste", "teste");
    @org.junit.After
    public void tearDown() throws Exception {
        g = null;
        p = null;
    }

    @Before
    public void setUp(){
        System.out.println(p.getObj2());
    }

    @Test (expected = FileNotFoundException.class)
    public void nullFile() throws IOException {
        g = new Grafo("euNaoExisto.txt");
    }

    @org.junit.Test
    public void dijkstra() throws IOException {
        g=new Grafo("src/cidades.txt");
        Random r = new Random();
        int cityIndex = r.nextInt(g.getSize());
        System.out.println(cityIndex);
        String randCity = g.getIndexes().get(cityIndex);
        System.out.println(randCity);
        g.dijkstra(randCity);
    }
}