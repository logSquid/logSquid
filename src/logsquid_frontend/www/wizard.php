<?php 
    require_once("functions/autoload.php"); 
    if(file_exists(WWW_FE."logsquid_frontend.conf")){
        header("Location: ".BASEURL."login.php");
        exit();
    }
?>
<html>
    <head>
        <title>logSquid - Assistente de Configura&ccedil;&atilde;o</title>
        <meta http-equiv="cache-control" content="no-cache" />
        <meta http-equiv="pragma" content="no-cache" />
        <meta http-equiv="expires" content = "-1" />
        
        <link href="<?php echo BASEURL.CSS ?>bootstrap.css" rel="stylesheet" type="text/css"/>
        <link href="<?php echo BASEURL.CSS ?>logSquid.css" rel="stylesheet" type="text/css"/>
        <link href="<?php echo BASEURL.CSS ?>wizard.css" rel="stylesheet" type="text/css"/>
        <link href="<?php echo BASEURL.CSS ?>msgbox.css" rel="stylesheet" type="text/css"/>
        <link href="<?php echo BASEURL.CSS ?>fontawesome.css" rel="stylesheet">
        <script type="text/javascript" src="<?php echo BASEURL.JS ?>jquery.js"></script>
        <script type="text/javascript" src="<?php echo BASEURL.JS ?>bootstrap.js"></script>
        <script type="text/javascript" src="<?php echo BASEURL.JS ?>msgbox.js"></script>
        <script type="text/javascript">
            $(document).ready(function(){
                $("#logSquid_database").submit(function(def){
                    status = 0;
                    $(".wizard-logs").html("<div id=\"loading-area\"><span class=\"loading-area\"><img src=\"<?php echo BASEURL.IMG ?>loading-wizard.gif\"></span>aguarde...</div>");
                    var hostname = $("#hostname").val();
                    var username = $("#username").val();
                    var password = $("#password").val();
                    var database = $("#database_name").val();
		    var timezone = $("#timezone").val();
		    if(timezone == ""){
			MsgWarning("Escolha o Timezone");
			$("#timezone").focus();
			return false;
		    }
                    $.post("<?php echo BASEURL.FUNC; ?>conectclass.php", {action: "setdatabasewizard", hostname: hostname, username: username, password: password, database: database, timezone: timezone},
                    function(content){
                        $(".areaScript").html(content);
                        dataBaseCheck();
                    });
                    def.preventDefault();
                });
                function dataBaseCheck(){
                    $.post("<?php echo BASEURL.FUNC; ?>conectclass.php", {action: "checkDatabaseWizard"},
                    function(content){
                        $(".areaScript").html(content);
                        setTimeout(redirectLogin(), 1000);
                        setTimeout($("#loading-area").remove(), 1000);
                    });
                }
                function redirectLogin(){
                    if(status == 2){
                        $(".wizard-logs").append("<div><span class=\"glyphicon glyphicon-repeat check\" aria-hidden=\"true\"></span>Redirecionando para a tela de Login");
                        setTimeout(($(location).attr('href', "<?php echo BASEURL; ?>login.php")), 2000);
                    }
                }
		function getListTimezone(){
			$("#timezone").append("<option value=''>Escolha</option>");
			$.post("<?php echo BASEURL.FUNC; ?>conectclass.php", {action: "getListTimezone"},
			function(list){
				$("#timezone").append(list);
			});
		}
		getListTimezone();
            });
        </script>
    </head>
    <body>
        <div class="areaMsg" id="area-msg"></div>
        <div class="areaScript" id="area-script"></div>
        <div class="container container-wizard">
            <div class="area-logo-wizard">
                <img src="<?php echo BASEURL.IMG; ?>logsquid-wizard.png" />
            </div>
            <div class="card card-container cont-wizard">
                <div class="content-title">
                    <h4 class="title-welcome">Bem-Vindo</h4>
                    <h5 class="text-welcome">Assistente de Configura&ccedil;&atilde;o</h5>
                </div>
                <div class="content-wizard">
                    <div id="database">
                        <h3 class="text-primary">Banco de Dados</h3>
                        <form id="logSquid_database" class="form-horizontal">
                            <fieldset class="scheduler-border"><br/>
                                <div class="form-group" id="HostName">
                                    <label for="hostname" class="col-sm-3 control-label text-muted">Servidor (IP)</label>
                                    <div class="col-sm-9"><input type="text" class="form-control" id="hostname" placeholder="" /></div>
                                </div>
                                <div class="form-group" id="Database">
                                    <label for="database" class="col-sm-3 control-label text-muted">Nome Banco de Dados</label>
                                    <div class="col-sm-9"><input type="text" class="form-control" id="database_name" placeholder="" /></div>
                                </div>
                                <div class="form-group" id="UserName">
                                    <label for="username" class="col-sm-3 control-label text-muted">Usu&aacute;rio</label>
                                    <div class="col-sm-9"><input type="text" class="form-control" id="username" placeholder="" /></div>
                                </div>
                                <div class="form-group" id="Password">
                                    <label for="password" class="col-sm-3 control-label text-muted">Senha</label>
                                    <div class="col-sm-9"><input type="password" class="form-control" id="password" placeholder="" /></div>
                                </div>
				<div class="form-group" id="Timezone">
                                    <label for="timezone" class="col-sm-3 control-label text-muted">Timezone</label>
                                    <div class="col-sm-9"><select class="form-control" id="timezone"></select></div>
                                </div>
                            </fieldset>
                            <input type="submit" class="btn btn-primary" value="Configurar" />
                        </form>
                    </div>
                </div>
                <div class="wizard-logs"></div>
            </div>
        </div>
    </body>
</html>
