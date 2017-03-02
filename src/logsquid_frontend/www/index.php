<?php require_once ("functions/autoload.php"); ?>
<html>
        <?php require_once ("webgui/header.php");?>
    <script type="text/javascript" src="<?php echo BASEURL.SERVICES ?>Services.js"></script>
    <script type="text/javascript">
    </script>
        <div class="container container-home">
            <div class="container" style="padding: 5px">
                <h4 class="title-welcome">Bem-vindo</h4>
                <div style="margin: 20px 0px">
                    <div class="content-title">
                        <h5 class="text-welcome">Dashboard</h5>
                    </div>
                    <div class="content-box-lg">
                        <h4 class="text-primary bold">Servers</h4>
                        <h5 class="text-muted text-box">
                            <?php
                                $Servers = new Services();
                                $Servers->getServicesServer();
                                $Servers->modalEditServer();
                            ?>
                        </h5>
                    </div>
                    <div class="content-box-lg">
                        <h4 class="text-primary bold">Agents</h4>
                        <h5 class="text-muted text-box">
                            <div id="table-agents">
                            <?php
                                $Agents = new Services();
                                $Agents->getServicesAgents();
                                $Agents->modalEditAgent();
                            ?>
                            </div>
                        </h5>
                    </div>
                </div>
                <div style="margin: 20px 0px">
                    <div class="content-title">
                        <h5 class="text-welcome">Sobre</h5>
                    </div>
                    <div class="content-box">
                        <h4 class="text-primary bold">O que &eacute;?</h4>
                        <h5 class="text-muted text-box">logSquid é um projeto OpenSource para gerenciamento de logs do Squid em Banco de Dados</h5>
                    </div>
                    <div class="content-box">
                        <h4 class="text-primary bold">Documenta&ccedil;&atilde;o</h4>
                        <h5 class="text-muted text-box">Documenta&ccedil;&atilde;o completa para instala&ccedil;&atilde;o, configura&ccedil;&atilde;o, filtros e relat&oacute;rios em: <a href="http://doc.logsquid.com" target="_blank">doc.logsquid.com</a></h5>
                    </div>
                    <div class="content-box">
                        <h4 class="text-primary bold">Desenvolvimento</h4>
                        <h5 class="text-muted text-box">O logSquid &eacute; desenvolvido por <a href="http://vantagebrazil.com/" target="_blank">VANTAGE BRAZIL</a></h5>
                    </div>
                    <div class="content-box">
                        <h4 class="text-primary bold">Vers&atilde;o</h4>
                        <h5 class="text-muted text-box">
                            <?php
                                require_once ("class/Functions.inc");
                                $version = new Functions();
                                echo $version->getVersion();
                            ?>
                        </h5>
                    </div>
                </div>
            </div>
        </div>
    </body> 
</html>
