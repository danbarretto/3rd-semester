/**
 * @class ListaCircular: lista circular estática implementada com array
 * @param <T> Generic com o tipo T a ser inserido
 */
public class ListaCircular<T> {
    private Object[] objs;
    private int ini, fim, nObjs, maxSize;

    /**
     * Construtor inicializa indíces com valores padrão e inicializa array com o valor dado
     * @param maxSize tamanho máximo da array
     */
    public ListaCircular( int maxSize){
        objs = new Object[maxSize];
        ini = -1;
        fim =0;
        nObjs = 0;
        this.maxSize = maxSize;
    }

    /**
     * Checa se a lista esta cheia de acordo com os índices
     * @return true para lista cheia e false para lista não cheia
     */
    public boolean estaCheia(){
        return ((ini==0 && fim == maxSize-1) || (ini == fim+1));
    }

    /**
     * Insere objeto no ínicio da lista circular
     * @param obj objeto a ser inserido
     * @throws Exception exceção jogada caso lista esteja cheia
     */
    public void addIni(T obj) throws Exception {
        if(estaCheia()){
            throw new Exception("Lista chiea");
        }
        //caso a lista não esteja inicializada
        if(ini == -1){
            ini=0;
            fim=0;

        }else if(ini == 0){
            //marca indíce de início no final da array para adicionar objetos de trás para frente
            ini = maxSize - 1;
        }else{
            ini--;
        }
        objs[ini] = obj;
        nObjs++;

    }

    /**
     * Retorna array dos objetos
     * @return array de objetos
     */
    public Object[] getObjs() {
        return objs;
    }

    /**
     * Insere objeto no fim da lista circular
     * @param obj Objeto a ser inserido
     * @throws Exception exceção jogada caso lista esteja cheia
     */
    public void addFim(T obj) throws Exception {
        if(estaCheia()){
            throw new Exception("Lista cheia");
        }
        if(ini == -1){
            //caso lista não esteja inicilizada
            ini = 0;
            fim = 0;
        }else if(fim == maxSize-1){
            //caso o indicador de fim esteja na ultima posição, fim é setado para 0 para
            //inserir objetos de frente para trás
            fim = 0;
        }else{
            fim++;
        }
        nObjs++;
        objs[fim] = obj;
    }

    /**
     * Remove objeto no início da lista
     * @return Objeto retirado
     */
    public Object removeIni() {
        if(nObjs==0){
            System.out.println("Lista vazia");
            return null;
        }

        Object aux = objs[ini];
        objs[ini] = null;
        if(ini==fim){
            //Caso lista tenha apenas 1 objeto
            fim = -1;
            ini = -1;
        }else{
            //caso objeto esteja na ultima posição
            if(ini == maxSize-1)
                ini = 0;
            else
                ini++;
        }
        nObjs--;
        return  aux;
    }

    /**
     * Retira objeto do final da lista
     * @return Objeto retirado
     */
    public Object removeFim(){
        if(nObjs==0){
            System.out.println("Lista vazia");
            return null;
        }
        Object aux = objs[fim];
        objs[fim] = null;

        if(fim==ini){
            //Caso lista tenha apenas 1 objeto

            ini = -1;
            fim = -1;
        }else if(fim==0){
            //caso seja o ultimo objeto da lista
            fim = maxSize-1;
        }else{
            fim--;
        }
        nObjs--;
        return  aux;
    }


}
