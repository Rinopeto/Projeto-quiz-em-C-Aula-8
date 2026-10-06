Gerenciador de Perguntas - Quiz de TI

Programa em C, executado no terminal, para gerenciar o banco de perguntas de um futuro quiz de orientação sobre os cursos de CC (Ciência da Computação), ES (Engenharia de Software) e ADS (Análise e Desenvolvimento de Sistemas). Nesta etapa não há aplicação do quiz, apenas o cadastro e a organização das perguntas.


Integrantes:
Bruno Seiti Ota
Eduardo Elioterio de Oliveira
Enrico Monteiro de Andrade 
Gabriel Tavares Moura Dias 
Matheus Alves da Silva
Turma: Manha
Grupo: 10
Link do video:
https://youtu.be/02niI4DCXBk?si=s6LALKnYblWPg1wb

Funcionalidades
1- Cadastrar pergunta
2- Listar todas as perguntas
3- Consultar por categoria
4- Consultar por curso
5- Atualizar pergunta
6- Excluir pergunta
Como funciona
Cada pergunta é uma struct Pergunta (id, texto, categoria, curso, resposta).
Os dados ficam em perguntas.csv, no formato id;texto;categoria;curso;resposta.
A leitura usa fgets() e strtok(); o cadastro grava com fprintf() em modo "a".
O ID é gerado automaticamente (maior ID + 1).
Atualização e exclusão usam um arquivo temporário, que depois substitui o original.
Validações
Opção de menu e código numéricos.
Texto e categoria não vazios.
Curso: somente CC, ES ou ADS.
Resposta: somente SIM ou NAO.
Erros de abertura de arquivo e buscas sem resultado tratados.
Compilar e executar
bash
gcc Aula8.c -o gerenciador
./gerenciador

Execute na mesma pasta do perguntas.csv.
