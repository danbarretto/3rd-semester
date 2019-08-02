
package controller;

/**
 *
 * @author daniel
 */
public class Usuario {
    private int permissao;
    private String email;
    private String senha;
    private String cpf_cnpj;
    private Perfil perfil;
    private EmpresaController empresa;

    /**
     * Construtor
     * @param permissao
     * @param cpfCnpj
     * @param email
     * @param senha
     */
    public Usuario(int permissao, String cpfCnpj, String email, String senha) {
        this.permissao = permissao;
        this.cpf_cnpj = cpfCnpj;
        this.email = email;
        this.senha = senha;
    }

    /**
     * Getter da permissao
     * @return permissao guardada
     */
    public int getPermissao() {
        return permissao;
    }

    /**
     * Setter da permissao
     * @param permissao permissao a ser guardada
     */
    public void setPermissao(int permissao) {
        this.permissao = permissao;
    }
    
    /**
     * Getter do cpf_cnpj
     * @return cpg_cnpj guardado
     */
    public String getCpf_cnpj() {
        return cpf_cnpj;
    }

    /**
     * Getter do email
     * @return email guardado
     */
    public String getEmail() {
        return email;
    }

    /**
     * Setter do email
     * @param email email a ser guardado
     */
    public void setEmail(String email) {
        this.email = email;
    }

    /**
     * Getter da senha
     * @return senha guardada
     */
    public String getSenha() {
        return senha;
    }

    /**
     * Setter da senha
     * @param senha Senha a ser guardada
     */
    public void setSenha(String senha) {
        this.senha = senha;
    }
       
    /**
     * Getter do perfil
     * @return perfil guardado
     */
    public Perfil getPerfil() {
        return perfil;
    }
    
    /**
     * Setter do perfil
     * @param perfil perfil a ser guardado
     */
    public void setPerfil(Perfil perfil) {
        this.perfil = perfil;
    }
    
    public EmpresaController getEmpresa() {
        return empresa;
    }
    
    public void setEmpresa(EmpresaController empresa) {
        this.empresa = empresa;
    }
}