<?php

$PATHS = array('class','css','js','img','functions','settings','realtime','filters','report','daemon','webgui','lang','graph','tmp','user', 'services');
$WWW = str_replace($PATHS, "", dirname(__FILE__));
require_once("{$WWW}functions/autoload.php");

switch ($_REQUEST['action']){
    case "setNameAgent":
        setNameAgent();
        break;
    case "setNameServer":
        setNameServer();
        break;
}

function setNameAgent(){
    $Services = new Services();
    echo $Services->setNameAgents($_REQUEST['id'], $_REQUEST['name']);
}
function setNameServer(){
    $Services = new Services();
    echo $Services->setNameServers($_REQUEST['id'], $_REQUEST['name']);
}