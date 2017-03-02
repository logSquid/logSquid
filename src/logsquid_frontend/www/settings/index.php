<?php
$PATHS = array('class','css','js','img','functions','settings','realtime','filters','report','daemon','webgui','lang','graph','tmp','user');
$WWW = str_replace($PATHS, "", dirname(__FILE__));
require_once("{$WWW}functions/autoload.php");
?>
<html>
    <?php require_once ("../".WEB."header.php");?>
    <script type="text/javascript" src="<?php echo BASEURL.JS ?>bootstrap-tab.js"></script>
    <script type="text/javascript" src="settings.js"></script>
    <script type="text/javascript">
        $(document).ready(function(){
            $("#config").attr("class","active");
            $("#logSquid_database").submit(function(def){
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
                $.post("<?php echo BASEURL.FUNC; ?>conectclass.php",{action: "setdatabase",hostname: hostname, username: username, password: password, database: database, timezone: timezone},
                function(content){
                    $(".areaScript").html(content);
                });
                dataBaseCheck();
                def.preventDefault();
            });
            $("#confTheme").submit(function(def){
                var theme = $("#select_theme").val();
                $.post("<?php echo BASEURL.USER;?>conectuser.php", {action: "settheme", theme: theme},
                function(content){
                    $(".areaMsg").html(content);
                });
                def.preventDefault();
            });
            function getTheme(){
                $.post("<?php echo BASEURL.USER;?>conectuser.php", {action: "gettheme"},
                function(content){
                    $(".areaScript").html(content);
                });
            }
            function loadDataBase(){
                $.post("<?php echo BASEURL.FUNC; ?>conectclass.php",{action: "getdatabase"},
                function(retorno){
                    ret = retorno.split(";");
                    $("#hostname").val(ret[0]);
                    $("#username").val(ret[1]);
                    $("#password").val(ret[2]);
                    $("#database_name").val(ret[3]);
		    setTimeout(function(){
			$("#timezone").val(ret[4]);
		    }, 1000);
                });
            }
            function dataBaseCheck(){
                $.post("<?php echo BASEURL.FUNC; ?>conectclass.php",{action: "checkDB"},
                function(logSquid){
                    if(logSquid == 1){
                        $("#createDlogSquid").removeClass("btn-danger");
                        $("#createDlogSquid").addClass("btn-success");
                        $("#createDlogSquid").html("Ok");
                        $("#defaultlogsquid").text("Banco de Dados logSquid");
                    }
                    else{
                        $("#createDlogSquid").removeClass("btn-success");
                        $("#createDlogSquid").addClass("btn-danger");
                        $("#createDlogSquid").html("Erro");
                        $("#defaultlogsquid").text("Banco de Dados logSquid");
                    }
                });
            }
	    function getListTimezone(){
            	$("#timezone").append("<option value=''>Escolha</option>");
               	$.post("<?php echo BASEURL.FUNC; ?>conectclass.php", {action: "getListTimezone"},
               	function(list){
        	        $("#timezone").append(list);
	        });
            }
	    getListTimezone();
            loadDataBase();
            dataBaseCheck();
            getTheme();
        });
    </script>
    <div class="container container-config">
        </pre>
        <div class="container" style="padding: 5px;">
        <ul id="myTab" class="nav nav-tabs">
            <li class="active"><a href="#database" data-toggle="tab">Banco de Dados</a></li>
            <li><a href="#user" data-toggle="tab">Usu&aacute;rio</a></li>
        </ul>
        <div id="myTabContent" class="tab-content">
            <div class="tab-pane panel fade in active" id="database">
                <h3 class="text-primary">Configura&ccedil;&atilde;o Banco de Dados</h3>
                <form id="logSquid_database" class="form-horizontal">
                    <fieldset class="scheduler-border"><h4 class="text-info">Banco de Dados MySQL</h4>
                        <div class="form-group" id="HostName">
                            <label for="hostname" class="col-sm-3 control-label text-muted">Servidor (IP)</label>
                            <div class="col-sm-6"><input type="text" class="form-control" id="hostname" placeholder="" /></div>
                        </div>
                        <div class="form-group" id="UserName">
                            <label for="username" class="col-sm-3 control-label text-muted">Usu&aacute;rio</label>
                            <div class="col-sm-6"><input type="text" class="form-control" id="username" placeholder="" /></div>
                        </div>
                        <div class="form-group" id="Password">
                            <label for="password" class="col-sm-3 control-label text-muted">Senha</label>
                            <div class="col-sm-6"><input type="password" class="form-control" id="password" placeholder="" /></div>
                        </div>
                        <div class="form-group" id="Database">
                            <label for="database" class="col-sm-3 control-label text-muted">Nome Banco de Dados</label>
                            <div class="col-sm-6"><input type="text" class="form-control" id="database_name" placeholder="" /></div>
                        </div>
			<div class="form-group" id="Timezone">
                            <label for="timezone" class="col-sm-3 control-label text-muted">Timezone</label>
	                    <div class="col-sm-6"><select class="form-control" id="timezone"></select></div>
                        </div>
                    </fieldset>
                    <input type="submit" class="btn btn-primary" value="Salvar" />
                </form>
                <fieldset class="scheduler-border"><h4 class="text-info">Conex&atilde;o com o Banco de Dados</h4>
                    <div class="form-group" id="DefaullogSquid">
                        <div class="col-sm-3"><button id="createDlogSquid" class="btn btn-dbase">Carregando...</button></div>
                        <label for="defaultlogsquid" id="defaultlogsquid" class="col-sm-6 control-label text-muted"></label>
                    </div>
                </fieldset>
            </div>
            
            <div class="tab-pane panel fade" id="user">
                <h3 class="text-primary">Usu&aacute;rio</h3>
                <form name="confUsername" id="confUsername" class="form-horizontal">
                    <fieldset class="scheduler-border"><h4 class="text-info">Informa&ccedil;&otilde;es</h4>
                        <div class="form-group">
                            <label for="field-username" class="col-sm-2 control-label text-muted">Nome</label>
                            <div class="col-sm-4">
                                <input type="text" class="form-control" id="field-username" />
                            </div>
                        </div>
                    </fieldset>
                    <input type="submit" class="btn btn-primary" value="Atualizar" />
                </form>
                <form name="confPassword" id="confPassword" class="form-horizontal">
                    
                    <fieldset class="scheduler-border"><h4 class="text-info">Alterar senha</h4>
                        <div class="form-group">
                            <label for="password-current" class="col-sm-2 control-label text-muted">Senha Atual</label>
                            <div class="col-sm-3">
                                <input type="password" class="form-control" id="password-current" />
                            </div>
                        </div>
                        <div class="form-group">
                            <label for="password-new" class="col-sm-2 control-label text-muted">Nova Senha</label>
                            <div class="col-sm-3">
                                <input type="password" class="form-control" id="password-new" />
                            </div>
                        </div>
                        <div class="form-group">
                            <label for="password-confirm" class="col-sm-2 control-label text-muted">Confirmar Senha</label>
                            <div class="col-sm-3">
                                <input type="password" class="form-control" id="password-confirm" />
                            </div>
                        </div>
                    </fieldset>
                    <input type="submit" class="btn btn-primary" value="Alterar Senha" />
                </form>
                <form name="confTheme" id="confTheme" class="form-horizontal">
                    <fieldset class="scheduler-border"><h4 class="text-primary">Tema</h4>
                        <div class="form-group">
                            <label for="password-confirm" class="col-sm-2 control-label text-muted">&nbsp;</label>
                            <div class="col-sm-3">
                                <select class="form-control" name="select_theme" id="select_theme">
                                    <option>Light</option>
                                    <option>Dark</option>
                                </select>
                            </div>
                        </div>
                    </fieldset>
                    <input type="submit" class="btn btn-primary" value="Alterar" />
                </form>
            </div>
        </div>
        </div>
    </div>
    </body>
</html>
