import java.io.*;
import java.util.*;

public class Grafo {

    private Map<String, Map<String, Integer>> grafo;
    //lista que facilita o acesso ao index de cada vertice
    private List<String> indexes;
    private int size;


    /**
     * Retorna a lista com os vértices
     * @return lista
     */
    public List<String> getIndexes() {
        return indexes;
    }


    /**
     * Insere vértice e aresta no grafo com seus respectivos pesos
     * @param ini O vértice de origem
     * @param dest O vértice de destino
     * @param peso O peso da aresta
     */
    public void insert(String ini, String dest, int peso){
        Map<String, Integer> adj = new HashMap<>();
        if(grafo.isEmpty()){
            //Caso grafo esteja vazio
            adj.put(dest, peso);
            grafo.put(ini,adj);
        }else{
            //Caso o nó já esteja no grafo
            if(grafo.containsKey(ini)){
                grafo.get(ini).put(dest, peso);
            }else{
                //Novo nó
                adj.put(dest, peso);
                grafo.put(ini, adj);
            }
        }
        size = grafo.size();
    }

    /**
     * Acessa o tamanho atual do grafo
     * @return o tamanho do grafo
     */
    public int getSize() {
        return size;
    }

    /**
     * Lê um arquivo de texto e insere os vértices do grafo de acordo com tabeamento do arquivo
     * @param filePath O caminho para o arquivo de texto
     * @throws IOException Exceção de leitura do arquivo
     */
    public Grafo(String filePath) throws IOException {
        grafo = new HashMap<>();
        BufferedReader sc = null;
        try {
            sc = new BufferedReader(new FileReader(filePath));
        }catch (FileNotFoundException e){
            throw new FileNotFoundException("Arquivo não encontrado");
        }
        //Leitura é feita linha por linha
        String node = sc.readLine();

        while (node!=null){
            String adj = sc.readLine();
            //Linhas abaixo com tab são consideradas nós adjacentes
            while(adj!=null && adj.charAt(0)=='\t'){
                String[] temp = adj.split(" ");
                temp[0] = temp[0].substring(1);
                insert(node, temp[0], Integer.parseInt(temp[1]));
                adj = sc.readLine();
            }
            node = adj;
        }
        //Lista com os nomes dos nós é feita para facilitar acesso ao index
        indexes = new ArrayList<>(grafo.keySet());

    }

    /**
     * Procura nó com menor distância entre o vetor de distâncias do grafo
     * @param dists O vetor com as distâncias entre o nó inicial e os restantes
     * @param lista A Lista temporária com os nós
     * @return Par contendo o nome do vértice e o valor da distância
     */
    public Par<String, Integer> menorDist(int[] dists, List lista){
        int menor = dists[0];
        int index=0;
        for(int i=1; i<dists.length; i++){
            if(dists[i]<menor && lista.contains(indexes.get(i))){
                menor=dists[i];
                index=i;
            }
        }
        return new Par<>(indexes.get(index), menor);
    }

    /**
     * Algorítimo de Dijkstra utilizado para encontrar o menor caminho entre um nó dado e os restantes
     * @param startNode O nó inicial
     */
    public void dijkstra(String startNode){
        //Vetor com as distâncias inicializado com valor máximo
        int distancias[] = new int[grafo.size()];
        for(int i=0; i<distancias.length; i++)
            distancias[i] = Integer.MAX_VALUE;
        //Distância do vértice inicial = 0
        distancias[indexes.indexOf(startNode)] = 0;

        Map<String, String> caminho = new HashMap<>();
        //Lista de vértices temporária
        List<String> listaV = new ArrayList<>();

        for(String vertice: grafo.keySet()){
            //Inicializa o map dos caminhos
            caminho.put(vertice, null);
            listaV.add(vertice);
        }

        while (!listaV.isEmpty()){
            //Nó de menor distância é recuperado da lista
            Par<String, Integer> noU = menorDist(distancias, listaV);
            listaV.remove(noU.getObj1());
            //Mapa contendo os vértices adjacentes ao vértice recém retirado
            Map<String, Integer> vizinhos = grafo.get(noU.getObj1());
            for(String v: vizinhos.keySet()){
                int distSum = distancias[indexes.indexOf(noU.getObj1())] + vizinhos.get(v);
                if(distSum < distancias[indexes.indexOf(v)]){
                    //Caso o caminho entre 2 nós seja melhor que o caminho direto, o valor da distância é atualizado
                    distancias[indexes.indexOf(v)] = distSum;
                    caminho.put(v, noU.getObj1());
                }
            }
        }
        //Mapa de caminho possue início e fim de vários caminhos
        //Para imprimir o caminho correto, basta empilhar os nós começando pelo fim do caminho até encontrar o nó inicial
        for(String s: caminho.keySet()){
            Stack<String> path= new Stack<>();
            if(!s.equals(startNode)){
                path.push(s);
                String next = caminho.get(s);
                path.push(next);
                while (!next.equals(startNode)){
                    next = caminho.get(next);
                    path.push(next);
                }

            }
            System.out.println("Caminho saindo de "+startNode+" até "+s);
            while(!path.isEmpty()){
                System.out.println(path.pop());
            }
            System.out.println();
        }
    }


}
