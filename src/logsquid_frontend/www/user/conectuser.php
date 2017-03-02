<?php
$PATHS = array('class','css','js','img','functions','settings','realtime','filters','report','daemon','webgui','lang','graph','tmp','user');
$WWW = str_replace($PATHS, "", dirname(__FILE__));
require_once("{$WWW}functions/autoload.php");

$Session = new Session();
switch ($_REQUEST['action']) {
    case "login":
        login();
        break;
    case "logout":
        logout();
        break;
    case "status":
        status();
        break;
    case "alterPass":
        alterPass();
        break;
    case "gettheme":
        getTheme();
        break;
    case "settheme":
        setTheme();
        break;
    case "updateUser":
        updateUsername();
        break;
}

function login(){
    $user = new user();
    $user->setUserPass($_REQUEST['username'], $_REQUEST['password']);
    $user->checkUser();
    $user->validateLogin();
    if($user->checkStatus() == TRUE){
        echo BASEURL;
    }
}

function logout(){
    $user = new user();
    $user->logout();
}

function status(){
    echo call_user_func(["user", "checkStatus"]);
}

function alterPass(){
    $user = new user();
    $user->password = sha1($_REQUEST['pwdcurrent']);
    $user->passwordnew = sha1($_REQUEST['pwdnew']);
    $user->alterPassword();
}

function setTheme(){
    global $Session;
    $theme = new user();
    $theme->theme = $_REQUEST['theme'];
    if($theme->alterTheme() == TRUE){
        $Session->setField('theme', $_REQUEST['theme']);
        echo "<script>MsgSuccess('Tema alterado com sucesso');</script>";
        echo "<script>location.reload();</script>";
    }
    else{
        echo "<script>MsgInfo('Falha ao alterar o Tema');</script>";
    }
    
}

function getTheme(){
    $theme = new user();
    echo "<script>$('#select_theme').val('{$theme->getTheme()}');</script>";
    echo "Oi";
}

function updateUsername(){
    global $Session;
    $username = new user();
    $username->nickname = $_REQUEST['name'];
    if($username->updateUsername() == TRUE){
        $Session->setField('nickname', $_REQUEST['name']);
        echo "";
    }
    else{
        echo "N&atilde;o foi poss&iacute;vel atualizar o nome do usu&aacute;rio";
    }
    
}