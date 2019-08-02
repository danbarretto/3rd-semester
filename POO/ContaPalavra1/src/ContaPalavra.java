import java.io.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

public class ContaPalavra {

    private String nomeArquivo;
    private File fp;
    private HashMap<String, Integer> hm;
    private Scanner sc;
    public ContaPalavra(String nomeArquivo) throws FileNotFoundException {
        this.nomeArquivo = nomeArquivo;
        hm = new HashMap<>();
        fp = new File(nomeArquivo);
        sc = new Scanner(fp);
    }

    public void criaMapa() throws IOException, ClassNotFoundException {

        while (sc.hasNext()){
            String s = sc.next().toLowerCase();
            if(hm.containsKey(s)){
                hm.replace(s, hm.get(s)+1);
            }else{
                hm.put(s,1);
            }
        }
        sc.close();

    }

    public void mostraMapa(){
        ArrayList<String> ar = new ArrayList<>(hm.keySet());
        ar.sort(String::compareTo);
        for(String s: ar){
            System.out.println(s+" "+hm.get(s));
        }
    }

    public static void main(String[] args) throws IOException, ClassNotFoundException {
        ContaPalavra cp = new ContaPalavra("/home/daniel/Desktop/3o semestre/POO/ContaPalavra1/src/teste.txt");
        cp.criaMapa();
        cp.mostraMapa();

    }
}
