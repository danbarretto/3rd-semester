
package controller;

/**
 * Classe guarda informações sobre Notificações
 * @author daniel
 */
public class NotificacaoController {
    private String emailRemetente;
    private ServicoController servicoController;

    /**
     * Getter do Controller do Serviço
     * @return objeto serviçoController
     */
    public ServicoController getServicoController() {
        return servicoController;
    }

    /**
     * Setter do ServicoController guardado
     * @param servicoController ServicoController a ser guardado
     */
    public void setServicoController(ServicoController servicoController) {
        this.servicoController = servicoController;
    }

    /**
     * Getter do email do remetente
     * @return o email guardado
     */
    public String getEmailRemetente() {
        return emailRemetente;
    }

    /**
     * Setter do email do remetente
     * @param emailRemetente email a ser guardado
     */
    public void setEmailRemetente(String emailRemetente) {
        this.emailRemetente = emailRemetente;
    }
    
    
    
    
    
    
}
