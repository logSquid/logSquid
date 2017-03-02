# logSquid beta
É um gerenciador de logs do Squid em Banco de Dados, e distribuído sob a Licença GPLv3. 

## Novidades
Nesta versão o logSquid possui três aplicações: o agente, o servidor e a interface gráfica, essas aplicações se relacionam a fim de centralizar os log's do Squid em banco de dados e melhorar a experiencia da visualizalção dos relatórios de navegação do proxy.

A função do agente é enviar os log's do Squid para o servidor, que recebe os log's e armazena-os no banco de dados. O servidor pode receber log's de mais de um agente. 

A interface gráfica interage diretamente com o banco de dados proporcionando uma visualização amigavel dos log's, possibilitando acompanhar os ultimos log's recebidos por agente, utilizar filtros específicos, além de gerar relatórios diários e mensais com gráficos.

Acesse http://doc.logsquid.com para mais informações.
