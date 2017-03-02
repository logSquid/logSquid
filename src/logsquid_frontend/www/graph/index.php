<?php
$PATHS = array('class','css','js','img','functions','settings','realtime','filters','report','daemon','webgui','lang','graph','tmp','user');
$WWW = str_replace($PATHS, "", dirname(__FILE__));
require_once("{$WWW}functions/autoload.php");

$Data = array(
    array(499817, '192.168.20.195', "3506560651"),
    array(283623, '192.168.20.156', "2206565507"),
    array(92400, '192.168.20.166', "12985540068"),
    array(72867, '192.168.20.24', "1545005012"),
    array(11387, '192.168.20.154', "888006322"),
    array(630, '192.168.20.181', "995905315")
);

foreach ($Data as $k => $v){
    $total[$k] = array($v[1], $v[0]);
    $band[$k] = array($v[1], $v[2]);
}

$access = new Graph();
$access->data = $total;
$access->report = "IP";
$access->GraphAccess();

/*
$bandwidth = new Graph();
$bandwidth->data = $band;
$bandwidth->report = "IP";
$bandwidth->GraphBandWidth();
*/
