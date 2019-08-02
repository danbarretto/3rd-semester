/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controller;

/**
 * Guarda todas informações do perfil de um usuário
 * @author daniel
 */
public class Perfil {
    private String nome, cpf_cnpj, universidade, descricaoProf, dataNasc, escolaridade, cidade, cep,experiencia, motivacoes, especializacao, areaAtuacao, estado;
    private int anoFormacao;
    
    /**
     * Getter do campo cpf_cnpj
     * @return cpf_cnpj guardado
     */
    public String getCpf_cnpj() {
        return cpf_cnpj;
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
     * Setter do cpf_cnpj
     * @param cpf_cnpj cpf_cnpj a ser guardado
     */
    public void setCpf_cnpj(String cpf_cnpj) {
        this.cpf_cnpj = cpf_cnpj;
    }

    /**
     * Getter do nome
     * @return o nome guardado
     */
    public String getNome() {
        return nome;
    }

    /**
     * Setter do nome
     * @param nome o nome a ser guardado
     */
    public void setNome(String nome) {
        this.nome = nome;
    }

    /**
     * Getter da universidade
     * @return a universidade guardada
     */
    public String getUniversidade() {
        return universidade;
    }

    /**
     * Setter da universidade
     * @param universidade a universidade guardada
     */
    public void setUniversidade(String universidade) {
        this.universidade = universidade;
    }

    /**
     * Getter da descrição profissional
     * @return a descrição profissional guardada
     */
    public String getDescricaoProf() {
        return descricaoProf;
    }

    /**
     * Setter da descrição profissional
     * @param descricaoProf a descrição profissional a ser guardada
     */
    public void setDescricaoProf(String descricaoProf) {
        this.descricaoProf = descricaoProf;
    }

    /**
     * Getter da data de nascimento
     * @return data de nascimento guardada
     */
    public String getDataNasc() {
        return dataNasc;
    }

    /**
     * Setter da data de nascimento
     * @param dataNasc data de nascimento a ser guardada
     */
    public void setDataNasc(String dataNasc) {
        this.dataNasc = dataNasc;
    }

    /**
     * Getter da escolaridade
     * @return escolaridade guardada
     */
    public String getEscolaridade() {
        return escolaridade;
    }

    /**
     * Setter da escolaridade
     * @param escolaridade escolaridade guardada
     */
    public void setEscolaridade(String escolaridade) {
        this.escolaridade = escolaridade;
    }

    /**
     * Getter da cidade
     * @return cidade guardada
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
     * Getter do cep
     * @return cep guardado
     */
    public String getCep() {
        return cep;
    }

    /**
     * Setter o cep
     * @param cep cep a ser guardado
     */
    public void setCep(String cep) {
        this.cep = cep;
    }

    /**
     * Getter da experiência
     * @return experiência guardada
     */
    public String getExperiencia() {
        return experiencia;
    }

    /**
     * Setter da experiência
     * @param experiencia a ser guardada
     */
    public void setExperiencia(String experiencia) {
        this.experiencia = experiencia;
    }

    /**
     * Getter das Motivações
     * @return motivações guardadas
     */
    public String getMotivacoes() {
        return motivacoes;
    }

    /**
     * Setter das motivações
     * @param motivacoes motivações a serem guardadas
     */
    public void setMotivacoes(String motivacoes) {
        this.motivacoes = motivacoes;
    }

    /**
     * Getter da especialização
     * @return especialização guardada
     */
    public String getEspecializacao() {
        return especializacao;
    }

    /**
     * Setter da especialização
     * @param especializacao especialização a ser guardada
     */
    public void setEspecializacao(String especializacao) {
        this.especializacao = especializacao;
    }

    /**
     * Getter da area de atuação
     * @return area de atuação guardada
     */
    public String getAreaAtuacao() {
        return areaAtuacao;
    }

    /**
     * Setter da area de atuação
     * @param areaAtuacao área de atuação a ser guardada
     */
    public void setAreaAtuacao(String areaAtuacao) {
        this.areaAtuacao = areaAtuacao;
    }

    /**
     * Getter do ano de formação
     * @return o ano de formação guardado
     */
    public int getAnoFormacao() {
        return anoFormacao;
    }

    /**
     * Setter do ano de formação
     * @param anoFormacao ano formação a ser guardado
     */
    public void setAnoFormacao(int anoFormacao) {
        this.anoFormacao = anoFormacao;
    }

    /**
     * Construtor
     * @param nome
     * @param cpf_cnpj
     * @param universidade
     * @param descricaoProf
     * @param dataNasc
     * @param escolaridade
     * @param cidade
     * @param cep
     * @param experiencia
     * @param motivacoes
     * @param especializacao
     * @param areaAtuacao
     * @param anoFormacao
     * @param estado
     */
    public Perfil(String nome, String cpf_cnpj, String universidade, String descricaoProf, String dataNasc, String escolaridade, String cidade, String cep, String experiencia, String motivacoes, String especializacao, String areaAtuacao, int anoFormacao, String estado) {
        this.nome = nome;
        this.cpf_cnpj = cpf_cnpj;
        this.universidade = universidade;
        this.descricaoProf = descricaoProf;
        this.dataNasc = dataNasc;
        this.escolaridade = escolaridade;
        this.cidade = cidade;
        this.cep = cep;
        this.experiencia = experiencia;
        this.motivacoes = motivacoes;
        this.especializacao = especializacao;
        this.areaAtuacao = areaAtuacao;
        this.anoFormacao = anoFormacao;
        this.estado = estado;
    }

    /**
     * Construtor
     * @param nome
     * @param cpf_cnpj
     * @param universidade
     * @param descricaoProf
     * @param dataNasc
     */
    public Perfil(String nome, String cpf_cnpj, String universidade, String descricaoProf, String dataNasc) {
        this.nome = nome;
        this.cpf_cnpj = cpf_cnpj;
        this.universidade = universidade;
        this.descricaoProf = descricaoProf;
        this.dataNasc = dataNasc;
    }
    
    /**
     * Contrutor
     * @param nome
     * @param cpf_cnpj
     * @param cidade
     * @param cep
     * @param motivacoes
     * @param especializacao
     * @param areaAtuacao
     * @param estado
     */
    public Perfil(String nome, String cpf_cnpj, String cidade, String cep, String motivacoes, String especializacao, String areaAtuacao, String estado) {
        this.nome = nome;
        this.cpf_cnpj = cpf_cnpj;
        this.cidade = cidade;
        this.cep = cep;
        this.motivacoes = motivacoes;
        this.especializacao = especializacao;
        this.areaAtuacao = areaAtuacao;
        this.estado = estado;
    }
}
