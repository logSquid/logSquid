<?php
$PATHS = array('class','css','js','img','functions','settings','realtime','filters','report','daemon','webgui','lang','graph','tmp','user');
$WWW = str_replace($PATHS, "", dirname(__FILE__));
require_once("{$WWW}functions/autoload.php");

$Data = array(
    array(499817, '192.168.20.195', "3.04GB"),
    array(183623, '192.168.20.156', "12.04GB"),
    array(92400, '192.168.20.166', "12.98GB"),
    array(72867, '192.168.20.24', "1.42GB"),
    array(11387, '192.168.20.154', "248.55MB"),
    array(630, '192.168.20.181', "475.49MB")
);
$data = array();

foreach ($Data as $k => $v){
    $total[$k] = array($v[1], $v[0]);
    $band[$k] = array($v[1], $v[2]);
}

$graphic = new PHPlot(800, 600);

$graphic->SetDefaultTTFont("ubuntu.ttf");
$graphic->SetTextColor('DimGrey');
$graphic->SetFontTTF('title', null, 12);
$graphic->SetFontTTF('y_label', NULL, 9);
$graphic->SetFontTTF('x_label', NULL, 9);

$graphic->SetShading('5');
$graphic->SetImageBorderType("none");
$graphic->SetPlotType("bars");
#$graphic->SetDataType("text-data");
$graphic->SetDataValues($total);

$graphic->SetTitle("ACESSOS POR IP");

$graphic->SetXTickPos("none");
$graphic->SetYTickPos("none");

$graphic->SetPlotAreaWorld(NULL, 0);

$graphic->SetYDataLabelPos("plotin");

#$graphic->SetCallback("draw_all", 'annotate_graph', $graphic);

$graphic->SetDrawYGrid(TRUE);
$graphic->SetDrawXGrid(TRUE);
$graphic->SetPlotBorderType("none");

$graphic->DrawGraph();

function annotate_graph($img, $graph){
    global $band;
    
    $color = imagecolorresolve($img, 99, 99, 99);
    $font = '2';
    foreach ($band as $x => $point){
        list($best_x, $best_y) = $graph->GetDeviceXY(($x + 0.3), $point[$x]);
        imagestring($img, $font, ($best_x -2), ($best_y -10), $band[$x][1], $color);
    }
}

