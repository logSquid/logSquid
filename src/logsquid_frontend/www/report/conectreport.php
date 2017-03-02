<?php
ini_set("memory_limit", "512M");
require_once("../functions/autoload.php");
require_once("../pdf/mpdf.php");

switch ($_POST['action']){
    case "report":
        report();
        break;
    case "getReport":
        getReport();
        break;
    case "switchMonthCalendar":
        switchMonthCalendar();
        break;
    case "generateReport":
        generateReport();
        break;
    case "removeReport":
        removeReport();
        break;
    case "export-pdf":
        generatePDF();
        break;
    case "export-html":
        generateHTML();
        break;
}

function report(){
    $datetimestart = "{$_POST['datestart']} {$_POST['timestart']}";
    $datetimeend = "{$_POST['dateend']} {$_POST['timeend']}";
    if($_POST['freport'] == ""){
        $where = "WHERE `datetime` BETWEEN '{$datetimestart}' and '{$datetimeend}'";
    }
    else{
        $where = "WHERE `datetime` BETWEEN '{$datetimestart}' and '{$datetimeend}' and `{$_POST['freport']}` LIKE '%".trim($_POST['fieldreport'])."%'";
    }
    $report = new report();
    $report->where = $where;
    $report->reportlogSquidData();
}

function getReport(){
    $type = $_POST['showReport'];
    if(file_exists("details/{$type}.html")){
        include_once("details/{$type}.html");
    }
}

function switchMonthCalendar(){
    $report = new report();
    $report->calendar($_REQUEST['date']);
}

function generateReport(){
    $report = new report();
    $report->generateReport($_REQUEST);
}

function removeReport(){
    $report = new report();
    $report->removeReport($_REQUEST);
}

function generatePDF(){
    $name = call_user_func(["Functions","getNameFile"]);
    $pdf = new mPDF("utf-8", "{$_REQUEST['format']}{$_REQUEST['orientation']}", "", "", 1, 1, 1, 4, 1, 1, "{$_REQUEST['orientation']}");
    $pdf->allow_charset_conversion = TRUE;
    $pdf->charset_in = "UTF-8";
    $pdf->SetFooter("logSquid - Squid Filter           pg {PAGENO}");
    $pdf->WriteHTML(getTable());
    $pdf->Output("../".TMP.$name.".pdf", "F");
    if(file_exists("../".TMP.$name.".pdf")){
        echo BASEURL.TMP."\\".$name;
    }
    else{
        echo "erro";
    }
}

function generateHTML(){
    $name = call_user_func(["Functions","getNameFile"]);
    $file = "../".TMP.$name.".html";
    $html = fopen($file, "w+");
    fwrite($html, getTable());
    fclose($html);
    if(file_exists($file)){
        echo BASEURL.TMP."\\".$name;
    }
    else{
        echo "erro";
    }
}

function getTable(){
//file_get_contents("export.css");
$html = "
<html>
    <head>
        <title>logSquid Report</title>
        <meta charset=\"utf-8\" />
        <style type=\"text/css\">
            *, body, table{
                margin: 0px;
                padding: 0px;
                font-family: Ubuntu, sans-serif;
                font-size: 12pt;
                color: #444;
            }
            .nowrap{
                white-space: nowrap;
            }
            .break{
                word-break: break-all !important;
            }
            table, .table{
                width: 100%;
                border: 0px;
                border-collapse: collapse !important;
            }
            .table tr td{
                width: auto;
                height: auto;
                border-top: solid 1px #e0e0e0;
                border-bottom: solid 0px #e0e0e0;
                border-right: 0px;
                border-left: 0px;
                padding: 5px 8px;
                word-break: break-all;
            }
            .table tr th{
                padding: 5px 0px 2px 30px;
                text-align: left;
            }
            a {
                text-decoration: none;
                color: #333;
            }
            .alignblock{
                width: 48%;
                display: inline-table;
                margin-right: 5px;
                text-align: left;
            }
            .aligntd{
                text-align: right;
                cursor: pointer;
            }
        </style>
    </head>
    <body>
        <table class='table'>".implode("\n", $_REQUEST['contHtml'])."</table>
    </body>
</html>
";
return $html;
}
