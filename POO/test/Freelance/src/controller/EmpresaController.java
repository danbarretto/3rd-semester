
package controller;

import java.util.ArrayList;
import java.util.List;

/**
 * EmpresaController: guarda informações de usuário e Lista de todos seus servicos
 * @author daniel
 */
public class EmpresaController {
    private Usuario usuario;
    private static List<ServicoController> listServicos = new ArrayList<>();

    /**
     * Construtor
     * @param usuario
     */
    public EmpresaController(Usuario usuario) {
        this.usuario = usuario;
    }
    
    /**
     * Getter do atributo usuario
     * @return usuario
     */
    public Usuario getUsuario() {
        return usuario;
    }
   
    /**
     * Getter da lista de serviços
     * @return Lista de serviços
     */
    public static List<ServicoController> getListServicos() {
        return listServicos;
    }
}
