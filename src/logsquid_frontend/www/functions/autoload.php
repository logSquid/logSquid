<?php
$PATHS = array('class','css','js','img','functions','settings','realtime','filters','report','daemon','webgui','lang','graph','tmp','user', 'services');
DEFINE("WWW", str_replace($PATHS, "", dirname(__FILE__)));
DEFINE("WWW_FE", "/usr/share/logSquid/frontend/");

function __autoload($class){
    $mod = "";
    switch ($class){
        case "logsquid":
            $mod = WWW.CLASSES;
            break;
        case "logsquidcsv":
            $mod = WWW.FILTERS;
            break;
        case "logsquidhtml":
            $mod = WWW.FILTERS;
            break;
        case "logsquidpdf":
            $mod = WWW.FILTERS;
            break;
        case "conectdb":
            $mod = WWW.CLASSES;
            break;
        case "config":
            $mod = WWW.SET;
            break;
        case "logSquidconf":
            $mod = WWW.SET;
            break;
        case "logdaemon":
            $mod = WWW.DAEMON;
            break;
        case "webgui":
            $mod = WWW.WEB;
            break;
        case "realtime":
            $mod = WWW.REALTIME;
            break;
        case "PHPlot":
            $mod = WWW.GRAPH;
            break;
        case "Graph":
            $mod = WWW.GRAPH;
            break;
        case "Functions":
            $mod = WWW.CLASSES;
            break;
        case "filters":
            $mod = WWW.FILTERS;
            break;
        case "user":
            $mod = WWW.USER;
            break;
        case "Session":
            $mod = WWW.USER;
            break;
        case "Services":
            $mod = WWW.SERVICES;
            break;
    }
    require_once "{$mod}{$class}.inc";
}

if(isset($_SERVER['SERVER_NAME'])){$host = $_SERVER['SERVER_NAME'];}
else{$host = "";}
if(isset($_SERVER['SERVER_PORT'])){$port = $_SERVER['SERVER_PORT'];}
else{$port = "";}

define("BASE", dirname(__FILE__)."/");
define("URL", "http://{$host}:{$port}");
define("BASEURL", URL."/logsquid/");

define("CLASSES", "class/");
define("CSS", "css/");
define("JS", "js/");
define("IMG", "img/");
define("FUNC", "functions/");
define("SET", "settings/");
define("REALTIME", "realtime/");
define("FILTERS", "filters/");
define("REPORT", "report/");
define("DAEMON", "daemon/");
define("WEB", "webgui/");
define("LANG", "lang/");
define("GRAPH", "graph/");
define("TMP", "tmp/");
define("USER", "user/");
define("SERVICES", 'services/');