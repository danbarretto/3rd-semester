
package controller;

/**
 * Classe guarda informações sobre serviços
 * @author daniel
 */
public class ServicoController {
    private String descricao, servico, dataAnuncio, cidade, estado, emailEmpresa, entrega, categorias, empresa;
    private float valor;
    private boolean presenca, transporte;
    private int id;
    
    /**
     * Construtor
     * @param descricao
     * @param servico
     * @param dataAnuncio
     * @param cidade
     * @param estado
     * @param emailEmpresa
     * @param entrega
     * @param categorias
     * @param valor
     * @param presenca
     * @param transporte
     * @param id
     * @param empresa
     */
    public ServicoController(String descricao, String servico, String dataAnuncio, String cidade, String estado, String emailEmpresa, String entrega, String categorias, float valor, boolean presenca, boolean transporte, int id, String empresa) {
        this.descricao = descricao;
        this.servico = servico;
        this.dataAnuncio = dataAnuncio;
        this.cidade = cidade;
        this.estado = estado;
        this.emailEmpresa = emailEmpresa;
        this.entrega = entrega;
        this.categorias = categorias;
        this.valor = valor;
        this.presenca = presenca;
        this.transporte = transporte;
        this.id = id;
        this.empresa = empresa;
    }

    /**
     * Construtor
     * @param descricao
     * @param servico
     * @param dataAnuncio
     * @param cidade
     * @param estado
     * @param emailEmpresa
     * @param entrega
     * @param categorias
     * @param empresa
     * @param valor
     * @param presenca
     * @param transporte
     */
    public ServicoController(String descricao, String servico, String dataAnuncio, String cidade, String estado, String emailEmpresa, String entrega, String categorias, String empresa, float valor, boolean presenca, boolean transporte) {
        this.descricao = descricao;
        this.servico = servico;
        this.dataAnuncio = dataAnuncio;
        this.cidade = cidade;
        this.estado = estado;
        this.emailEmpresa = emailEmpresa;
        this.entrega = entrega;
        this.categorias = categorias;
        this.empresa = empresa;
        this.valor = valor;
        this.presenca = presenca;
        this.transporte = transporte;
    }

    /**
     * Getter das categorias
     * @return categorias guardadas
     */
    public String getCategorias() {
        return categorias;
    }

    /**
     * Setter das categorias
     * @param categorias categorias a serem guardadas
     */
    public void setCategorias(String categorias) {
        this.categorias = categorias;
    }
    
    /**
     * Getter da descrição
     * @return descrição guardada
     */
    public String getDescricao() {
        return descricao;
    }

    /**
     * Setter da descrição
     * @param descricao descrição a ser guardada
     */
    public void setDescricao(String descricao) {
        this.descricao = descricao;
    }

    /**
     * Getter do título do serviço
     * @return título do serviço guardado
     */
    public String getServico() {
        return servico;
    }

    /**
     * Setter do título do serviço
     * @param servico título a ser guardado
     */
    public void setServico(String servico) {
        this.servico = servico;
    }

    /**
     * Getter da data do anúncio
     * @return data do anúncio guardada
     */
    public String getDataAnuncio() {
        return dataAnuncio;
    }

    /**
     * Setter da data do anúncio
     * @param dataAnuncio data a ser guardada
     */
    public void setDataAnuncio(String dataAnuncio) {
        this.dataAnuncio = dataAnuncio;
    }

    /**
     * Getter da cidade
     * @return a cidade guardada
     */
    public String getCidade() {
        return cidade;
    }

    /**
     * Setter da cidade
     * @param cidade cidade a ser guardada
     */
    public void setCidade(String cidade) {
        this.cidade = cidade;
    }

    /**
     * Getter do estado
     * @return estado guardado
     */
    public String getEstado() {
        return estado;
    }

    /**
     * Setter do estado
     * @param estado estado a ser guardado
     */
    public void setEstado(String estado) {
        this.estado = estado;
    }

    /**
     * Getter do email da empresa
     * @return o email guardado
     */
    public String getEmailEmpresa() {
        return emailEmpresa;
    }

    /**
     * Setter do email da empresa
     * @param emailEmpresa email a ser guardado
     */
    public void setEmailEmpresa(String emailEmpresa) {
        this.emailEmpresa = emailEmpresa;
    }

    /**
     * Getter do nome da empresa
     * @return nome guardado
     */
    public String getEmpresa() {
        return empresa;
    }

    /**
     * Setter do nome da empresa
     * @param empresa nome a ser guardado
     */
    public void setEmpresa(String empresa) {
        this.empresa = empresa;
    }

    /**
     * Getter da data de entrega
     * @return data guardada
     */
    public String getEntrega() {
        return entrega;
    }

    /**
     * Setter da data de entrega
     * @param entrega data a ser guardada
     */
    public void setEntrega(String entrega) {
        this.entrega = entrega;
    }

    /**
     * Getter do valor
     * @return o valor guardado
     */
    public float getValor() {
        return valor;
    }

    /**
     * Setter do valor
     * @param valor valor a ser guardado
     */
    public void setValor(float valor) {
        this.valor = valor;
    }

    /**
     * Getter da presença
     * @return presença guardada
     */
    public boolean isPresenca() {
        return presenca;
    }

    /**
     * Setter da presença
     * @param presenca presença a ser guardada
     */
    public void setPresenca(boolean presenca) {
        this.presenca = presenca;
    }

    /**
     * Getter do transporte
     * @return transporte guardado
     */
    public boolean isTransporte() {
        return transporte;
    }

    /**
     * Setter do tranporte 
     * @param transporte transporte a ser guardado
     */
    public void setTransporte(boolean transporte) {
        this.transporte = transporte;
    }

    /**
     * Getter do id
     * @return id guardado
     */
    public int getId() {
        return id;
    }

    /**
     * Setter do id
     * @param id a ser guardado
     */
    public void setId(int id) {
        this.id = id;
    }
    
    
}
