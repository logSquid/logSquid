<?php
ini_set("memory_limit", "512M");
require_once("../functions/autoload.php");
require_once("../pdf/mpdf.php");

$functions = new Functions();

switch (($_REQUEST['action'])){
    case "gGraph":
        gGraph();
        break;
    case "generate-pdf":
        generatePDF();
        break;
}

function gGraph(){
    global $functions;
    
    $Data = array();
    $data = $_REQUEST['data'];
    $type = $_REQUEST['type'];
    $typegraph = $_REQUEST['typegraph'];
    
    $leg = explode("/", $_REQUEST['leg']);
    foreach ($data as $d){
        if(isset($d[2])){
            $Data[] = array(call_user_func(['Functions', 'sizeString'], $d[0]), $d[2], $d[1]);
        }
        else{
            $Data[] = array(call_user_func(['Functions', 'sizeString'], $d[0]), $d[1]);
        }
    }
    if($type == "accesssites" || $type == "deniedsites"){
        $graphic = new Graph($_REQUEST['measures'][0], $_REQUEST['measures'][1]);
        $graphic->TypeGraph = $typegraph;
        $graphic->data = $Data;
        $graphic->SetTitle = $leg[0];
        $graphic->report = "Sites";
        $graphic->GraphAccess();
    }
    if($type == "accessurl" || $type == "deniedurl"){
        $graphic = new Graph($_REQUEST['measures'][0], $_REQUEST['measures'][1]);
        $graphic->TypeGraph = $typegraph;
        $graphic->data = $Data;
        $graphic->SetTitle = $leg[0];
        $graphic->report = "URL's";
        $graphic->GraphAccess();
    }
    if($type == "adownloads" || $type == "ddownloads"){
        foreach ($Data as $k => $v){
            $total[$k] = array($v[0], $v[2]);
            $band[$k] = array($v[0], $functions->convertSize($v[1]));
        }
        $graphic = new Graph($_REQUEST['measures'][0], $_REQUEST['measures'][1]);
        $graphic->TypeGraph = $typegraph;
        $graphic->data = $total;
        $graphic->SetTitle = $leg[0];
        $graphic->report = "Downloads";
        $graphic->GraphAccess();
        sleep(1);
        $cband = new Graph($_REQUEST['measures'][0], $_REQUEST['measures'][1]);
        $cband->TypeGraph = $typegraph;
        $cband->data = $band;
        $cband->SetTitle = $leg[1];
        $cband->report = "Downloads";
        $cband->GraphBandWidth();
    }
    if($type == "aipuser" || $type == "dipuser"){
        foreach ($Data as $k => $v){
            $total[$k] = array($v[0], $v[2]);
            $band[$k] = array($v[0], $functions->convertSize($v[1]));
        }
        $graphic = new Graph($_REQUEST['measures'][0], $_REQUEST['measures'][1]);
        $graphic->TypeGraph = $typegraph;
        $graphic->data = $total;
        $graphic->SetTitle = $leg[0];
        $graphic->report = "IP";
        $graphic->GraphAccess();
        sleep(1);
        $cband = new Graph($_REQUEST['measures'][0], $_REQUEST['measures'][1]);
        $cband->TypeGraph = $typegraph;
        $cband->data = $band;
        $cband->SetTitle = $leg[1];
        $cband->report = "IP";
        $cband->GraphBandWidth();
    }
    if($type == "ausername" || $type == "dusername"){
        foreach ($Data as $k => $v){
            $total[$k] = array($v[0], $v[2]);
            $band[$k] = array($v[0], $functions->convertSize($v[1]));
        }
        $graphic = new Graph($_REQUEST['measures'][0], $_REQUEST['measures'][1]);
        $graphic->TypeGraph = $typegraph;
        $graphic->data = $total;
        $graphic->SetTitle = $leg[0];
        $graphic->report = "Usu&aacute;rio";
        $graphic->GraphAccess();
        sleep(1);
        $cband = new Graph($_REQUEST['measures'][0], $_REQUEST['measures'][1]);
        $cband->TypeGraph = $typegraph;
        $cband->data = $band;
        $cband->SetTitle = $leg[1];
        $cband->report = "Usu&aacute;rio";
        $cband->GraphBandWidth();
    }
    if($type == "mime"){
        foreach ($Data as $k => $v){
            $total[$k] = array($v[0], $v[2]);
            $band[$k] = array($v[0], $functions->convertSize($v[1]));
        }
        $graphic = new Graph($_REQUEST['measures'][0], $_REQUEST['measures'][1]);
        $graphic->TypeGraph = $typegraph;
        $graphic->data = $total;
        $graphic->SetTitle = $leg[0];
        $graphic->report = "Tipos de Arquivo";
        $graphic->GraphAccess();
        sleep(1);
        $cband = new Graph($_REQUEST['measures'][0], $_REQUEST['measures'][1]);
        $cband->TypeGraph = $typegraph;
        $cband->data = $band;
        $cband->SetTitle = $leg[1];
        $cband->report = "Tipos de Arquivo";
        $cband->GraphBandWidth();
    }
}

function generatePDF(){
    $name = call_user_func(["Functions","getNameFile"]);
    $pdf = new mPDF("utf-8", "{$_REQUEST['format']}{$_REQUEST['orientation']}", "", "", 1, 1, 1, 4, 1, 1, "{$_REQUEST['orientation']}");
    $pdf->allow_charset_conversion = TRUE;
    $pdf->charset_in = "UTF-8";
    $pdf->SetFooter("logSquid - Squid Report           pg {PAGENO}");
    $pdf->WriteHTML(getTable());
    $pdf->Output("../".TMP.$name.".pdf", "F");
    if(file_exists("../".TMP.$name.".pdf")){
        echo BASEURL.TMP."\\".$name;
    }
    else{
        echo 'erro';
    }
}

function getTable(){
file_get_contents("export.css");
$html = "
<html>
    <head>
        <title>logSquid Report</title>
        <meta charset=\"utf-8\" />
        <link href=\"./export.css\" rel=\"stylesheet\" type=\"text/css\"/>
    </head>
    <body>
        ".implode("\n", $_REQUEST['Table'])."
    ";
foreach ($_REQUEST['imgGraph'] as $img){
$html .= "
    <img src=\"{$img}\" />
    ";
}
$html .= "
    </body>
</html>
";
return $html;
}