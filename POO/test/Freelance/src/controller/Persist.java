
package controller;

import java.util.ArrayList;
import java.util.List;

/**
 * Classe de Persistencia de dados.
 * Dados são guardados estaticamente para serem utilizados em outras telas e classes
 * @author daniel
 */
public abstract class Persist {
    private static Usuario user;
    private static Perfil pm;
    private static List<Usuario> listUsuarios = new ArrayList<>();
    private static List<Perfil> listClientes = new ArrayList<>();
    private static List<EmpresaController> listEmpresas = new ArrayList<>();
    private static List<NotificacaoController> listNotificacao = new ArrayList<>();

    /**
     * Getter da lista de notificações
     * @return lista de notificações guardadas
     */
    public static List<NotificacaoController> getListNotificacao() {
        return listNotificacao;
    }

    /**
     * Setter das listas de notificações
     * @param listNotificacao lista de notificações a ser guardada
     */
    public static void setListNotificacao(List<NotificacaoController> listNotificacao) {
        Persist.listNotificacao = listNotificacao;
    }

    /**
     * Getter do perfil logado
     * @return perfil logado
     */
    public static Perfil getPerfilModel() {
        return pm;
    }

    /**
     * Setter do perfil logado
     * @param pm  perfil logado a ser guardado
     */
    public static void setPerfilModel(Perfil pm) {
        Persist.pm = pm;
    }
    
    /**
     * Getter do Usuario logado
     * @return usuario logado
     */
    public static Usuario getUser() {
        return user;
    }

    /**
     * Setter do usuario logado
     * @param user usuario logado a ser guardado
     */
    public static void setUser(Usuario user) {
        Persist.user = user;
    }

    /**
     * Getter da lista de usuários
     * @return lista de usuários guardada
     */
    public static List<Usuario> getListUsuarios() {
        return listUsuarios;
    }
    
    /**
     * Getter da lista de clientes
     * @return lista de clientes guardada
     */
    public static List<Perfil> getListClientes() {
        return listClientes;
    }
    
    /**
     * Getter da lista de empresas
     * @return lista de empresas guardadas
     */
    public static List<EmpresaController> getListEmpresas() {
        return listEmpresas;
    }
}
