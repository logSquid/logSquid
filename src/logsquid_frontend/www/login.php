<?php 
    require_once ("functions/autoload.php"); 
    if(!file_exists(WWW_FE."logsquid_frontend.conf")){
        header("Location: ".BASEURL."wizard.php");
        exit();
    }
?>
<html>
    <head>
        <title>logSquid</title>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/> 
        <meta http-equiv="cache-control" content="no-cache" />
        <meta http-equiv="pragma" content="no-cache" />
        <meta http-equiv="expires" content = "-1" />

        <link href="<?php echo BASEURL.CSS ?>bootstrap.css" rel="stylesheet" type="text/css"/>
        <link href="<?php echo BASEURL.CSS ?>login.css" rel="stylesheet" type="text/css"/>
        <link href="<?php echo BASEURL.CSS ?>msgbox.css" rel="stylesheet" type="text/css"/>
        <link href="<?php echo BASEURL.CSS ?>fontawesome.css" rel="stylesheet">
        <script type="text/javascript" src="<?php echo BASEURL.JS ?>jquery.js"></script>
        <script type="text/javascript" src="<?php echo BASEURL.JS ?>bootstrap.js"></script>
        <script type="text/javascript" src="<?php echo BASEURL.JS ?>msgbox.js"></script>
        <script type="text/javascript" src="<?php echo BASEURL.JS ?>login.js"></script>
        <script type="text/javascript" src="<?php echo BASEURL.JS ?>easter.js"></script>
    </head>
    <body>  
        <div class="areaMsg" id="area-msg"></div>
        <div class="container container-login">
            <div class="card card-container">
                <div class="area-logo-login">
                    <img id="logo-login" class="logo-login" src="<?php echo BASEURL.IMG; ?>logo-login.png" />
                </div>
                <p id="profile-name" class="profile-name-card"></p>
                <form class="form-signin" id="login">
                    <span id="reauth-login" class="reauth-login"></span>
                    <input type="text" id="username" class="form-control" placeholder="Usu&aacute;rio" autocomplete="off" />
                    <input type="password" id="password" class="form-control" placeholder="Senha" />
                    <button class="btn btn-lg btn-primary btn-block btn-signin" type="submit">Logar</button>
                </form><!-- /form -->
                <div class="area-forgot-password">
                    <!--data-target=".modal-forgotpassword"-->
                    <a href="#" class="forgot-password" id="forgot-password" data-toggle="modal">
                        Esqueceu a senha?
                    </a>
                </div>
            </div>
        </div>
        <div class="modal fade modal-forgotpassword" tabindex="-1" role="dialog" aria-labelledby="myLargeModalLabel">
            <div class="modal-dialog modal-lg">
                <div class="modal-content">
                    <div class="modal-header">
                      <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">×</span></button>
                      <h4 class="modal-title text-primary" id="myLargeModalLabel">Perdeu a senha?</h4>
                    </div>
                    <div class="modal-body" style="padding: 15px;">
                        Problema SEU
                    </div>
                </div>
            </div>
        </div>
    </body>
</html>