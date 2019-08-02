DROP DATABASE freelance;
CREATE DATABASE freelance;
USE freelance;
CREATE TABLE perfil(
    name varchar(50) not null,
    birthday varchar(10),
    cpf_cnpj varchar(20) not null,
    cep varchar(9),
    cidade varchar(50),
    escolaridade varchar(30),
    anoFormacao int,
    especializacao varchar(50),
    areaAtuacao varchar(50),
    experiencias varchar(1000),
    motivacao varchar(1000),
    primary key (cpf_cnpj),
    university varchar(50),
    professionalDesc varchar(1000),
    estado varchar(2)
);
CREATE TABLE usuario(
     permission smallint unsigned not null,
     email varchar(50) not null,
     password varchar(200) not null,
     cpf_cnpj varchar(20) not null,
     FOREIGN KEY (cpf_cnpj) REFERENCES perfil(cpf_cnpj),
     primary key (email)
     
);

CREATE TABLE servico(
    descricao varchar(300) not null,
    servico varchar(100) not null,
    dataAnuncio varchar(10) not null,
    cidade varchar(20) not null,
    estado char(2) not null,
    emailEmpresa varchar(50) not null,
    valor float not null,
    nomeEmpresa varchar(50) not null,
    entrega varchar(10) not null,
    id int auto_increment not null,
    presenca boolean,
    transporte boolean,
    categorias varchar(1000),
    primary key (id),
    FOREIGN KEY (emailEmpresa) REFERENCES usuario(email)
);

CREATE TABLE proposta(
    id int not null auto_increment,
    fk_idServico int,
    FOREIGN KEY (fk_idServico) REFERENCES servico(id),
    emailDest varchar(50) not null,
    FOREIGN KEY (emailDest) REFERENCES usuario(email),
    primary key(id),
    emailEnvio varchar(50) not null,
    FOREIGN KEY (emailEnvio) REFERENCES usuario(email),
    visualizado boolean
);

CREATE TABLE mensagem(
    idServico int,
    FOREIGN KEY (idServico) REFERENCES servico(id),
    emailUsuario varchar(50) not null,
    FOREIGN KEY (emailUsuario) REFERENCES usuario(email),
    mensagem varchar(500) not null,
    filePath varchar(128) not null 
);

CREATE TABLE areaDeAtuacao(
    id smallint auto_increment not null,
    nome varchar(200),
    primary key (id)
);

INSERT INTO perfil (name, birthday, cpf_cnpj, university, professionalDesc) VALUES ('Daniel', '04/11/1998', '37855424881','USP' ,'student');
INSERT INTO usuario(permission, email, password, cpf_cnpj) VALUES (1, 'aaa', 'aaa', '37855424881');

INSERT INTO servico(descricao,valor,nomeEmpresa, servico, dataAnuncio, cidade, estado, emailEmpresa, entrega, presenca, transporte, categorias)
VALUES ('test1',5000.00,'da inc', 'test s', '2019-02-02', 'são carlos', 'SP', 'aaa', '07/07/2019', 1, 1, 'tudo');
INSERT INTO servico(descricao,valor,nomeEmpresa, servico, dataAnuncio, cidade, estado, emailEmpresa, entrega, presenca, transporte, categorias)
VALUES ('Servico de verdade',10000.00,'AAA', 'testAAAAAA', '2019-02-02', 'são carlos', 'SP', 'aaa', '07/07/2019', 1, 1, 'tudo');

INSERT INTO proposta(fk_idServico, emailDest,visualizado, emailEnvio) VALUES (1, 'da',0, 'aaa');
INSERT INTO proposta(fk_idServico, emailDest,visualizado, emailEnvio) VALUES (2, 'da',0, 'aaa');

use freelance;
SELECT * from servico;
SELECT * FROM servico LEFT JOIN proposta ON servico.id=proposta.fk_idServico AND proposta.emailDest='da' AND proposta.visualizado=0;
update proposta set visualizado=0;
SELECT * FROM servico LEFT JOIN proposta on servico.id=proposta.fk_idServico AND emailDest='da';
UNION
SELECT emailEnvio from proposta RIGHT JOIN servico on proposta.fk_idServico=servico.id and emailDest='da';
SELECT * FROM usuario;

/*
DELETE FROM mysql.user WHERE User = 'freelanceAdm';
CREATE USER 'freelanceAdm'@'localhost' IDENTIFIED BY 'Freelance!123'; 
GRANT ALL PRIVILEGES ON * . * TO 'freelanceAdm'@'localhost';
use freelance;
SELECT DATE_FORMAT(birthday, '%d/%m/%Y') FROM perfil;
SELECT * from usuario;
*/