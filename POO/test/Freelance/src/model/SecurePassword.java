
package model;

import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

/**
 * Classe realiza operação de hash utilizando o algorítimo de SHA-512 para gerar uma
 * senha criptografada
 * @author daniel
 */
public class SecurePassword {
   
    /**
     * Gera uma senha criptografada para ser guardada no banco de dados
     * @param passwordToHash Senha a ser criptografada
     * @return generatedPassword Senha gerada pelo algorítimo
     */
    public static String securePassword(String passwordToHash){
            String generatedPassword = null;
            try {
                 MessageDigest md = MessageDigest.getInstance("SHA-512");
                 byte[] bytes = md.digest(passwordToHash.getBytes(StandardCharsets.UTF_8));
                 StringBuilder sb = new StringBuilder();
                 for(int i=0; i< bytes.length ;i++){
                    sb.append(Integer.toString((bytes[i] & 0xff) + 0x100, 16).substring(1));
                 }
                 generatedPassword = sb.toString();
                } 
               catch (NoSuchAlgorithmException e){
                   System.out.println(e);
               }
            return generatedPassword;
        }
    
}
