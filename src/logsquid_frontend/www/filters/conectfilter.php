<?php
ini_set("memory_limit", "512M");
$PATHS = array('class','css','js','img','functions','settings','realtime','filters','report','daemon','webgui','lang','graph','tmp','user');
$WWW = str_replace($PATHS, "", dirname(__FILE__));
require_once("{$WWW}functions/autoload.php");
require_once("../pdf/mpdf.php");

switch ($_REQUEST['action']){
    case "filter":
        searchFilter();
        break;
    case "getnumpg":
        getNumPG();
        break;
    case "generate-pdf":
        generatePDF();
        break;
    case "generate-html":
        generateHTML();
        break;
    case "generate-csv":
        generateCSV();
        break;
}

function searchFilter(){
    $search = explode(",", $_POST['search']);
    $datetimestart = $_POST['datetimestart'];
    $datetimeend = $_POST['datetimeend'];
    $showpg = $_POST['showpg'];
    $goto = $_POST['goto'];
    $agent = $_POST['agent'];
    $search_agent = ($agent == "")? "": "`agent`='{$agent}' AND";
    
    $filter = new filters();
    
    if($_POST['typefilter'] == ""){
        $filter->where = "WHERE {$search_agent} `datetime` BETWEEN '{$datetimestart}' and '{$datetimeend}'";
    }else{
        $typefilter = explode(",", $_REQUEST['typefilter']);
        for($i = 0; $i < count($typefilter); $i++){
            $filt[] = WhereFilter($search[$i], $typefilter[$i]);
        }
        $search_filter = implode(" AND ", $filt);
        $filter->where = "WHERE {$search_agent} {$search_filter} AND `datetime` BETWEEN '{$datetimestart}' AND '{$datetimeend}'";
    }
    $filter->goto = $_REQUEST['goto'];
    $filter->showpg = $_REQUEST['showpg'];
    $filter->orderby = $_REQUEST['orderby'];
    $filter->fields = implode(", ", $_REQUEST['fields']);

    $filter->SelectLogSquid();
    $result_select = str_replace("\'", "&#039;","SELECT {$filter->fields} FROM logSquid {$filter->where} {$filter->orderby}");
    echo "<input type='hidden' value=\"{$result_select}\" id='get_sql' />";
}
function WhereFilter($str, $type){
    $estr = explode("\\", $str);
    if($type == "size"){
        foreach ($estr as $rs){
            $r = strtoupper($rs);
            if(ereg(">", $r) && !ereg("!", $r)){
                $rstr[] = "`size` > ".call_user_func(["Functions", "convertSize"], trim(str_replace(">", "", $r)), TRUE);
            }
            elseif(ereg(">", $r) && ereg("!", $r)){
                $rstr[] = "NOT `size` > ".call_user_func(["Functions", "convertSize"], trim(str_replace(">", "", trim(str_replace("!", "", $r)))), TRUE);
            }
            elseif(ereg("<", $r) && ! ereg("!", $r)){
                $rstr[] = "`size` < ".call_user_func(["Functions", "convertSize"], trim(str_replace("<", "", $r)), TRUE);
            }
            elseif(ereg("<", $r) && ereg("!", $r)){
                $rstr[] = "NOT `size` < ".call_user_func(["Functions", "convertSize"], trim(str_replace("<", "", trim(str_replace("!", "", $r)))), TRUE);
            }
            elseif(ereg("!", $r)){
                $rstr[] = "`size` LIKE ".call_user_func(["Functions", "convertSize"], trim(str_replace("<", "", trim(str_replace("!", "", $r)))), TRUE);
            }
            else{
                $rstr[] = "`size` LIKE ".call_user_func(["Functions", "convertSize"], trim(str_replace("<", "", $r)), TRUE);
            }
        }
        $nstr = implode(" AND ", $rstr);
    }
    elseif($type == "ipuser" || $type == "username" || $type == "destination" || $type == "url" || $type == "ipdest" || $type == "mime"){
        if(count($estr) > 1){
            foreach ($estr as $r){
                $rs[] = "'".trim($r)."'";
            }
            if(ereg("!", $str)){
                $rstr[] = "`{$type}` NOT IN (".implode(", ", str_replace("!", "", $rs)).")";
                $nstr = implode(" AND ", $rstr);
            }
            else{
                $rstr[] = "`{$type}` IN (".implode(", ", $rs).")";
                $nstr = implode(" AND ", $rstr);
            }
        }
        else{
            if(ereg("!", $str)){
                $rstr[] = "`{$type}` NOT LIKE '".trim(str_replace("!", "", $str))."'";
                $nstr = implode(" AND ", $rstr);
            }
            else{
                $rstr[] = "`{$type}` LIKE '".trim($str)."'";
                $nstr = implode(" AND ", $rstr);
            }
        }
    }
    else{
        $rstr[] = "`{$type}` LIKE '".trim($str)."'";
        $nstr = implode(" AND ", $rstr);
    }
    return $nstr;
}
function getNumPG(){
    $search = explode(",", $_POST['search']);
    $datetimestart = $_POST['datetimestart'];
    $datetimeend = $_POST['datetimeend'];
    $showpg = $_POST['showpg'];
    $goto = $_POST['goto'];
    $agent = $_POST['agent'];
    $search_agent = ($agent == "")? "": "`agent`='{$agent}' AND";
    
    $filter = new filters();
    if($_POST['typefilter'] == ""){
        $filter->where = "WHERE {$search_agent} `datetime` BETWEEN '{$datetimestart}' and '{$datetimeend}'";
    }else{
        $typefilter = explode(",", $_REQUEST['typefilter']);
        for($i = 0; $i < count($typefilter); $i++){
            $filt[] = WhereFilter($search[$i], $typefilter[$i]);
        }
        $search_filter = implode(" AND ", $filt);
        $filter->where = "WHERE {$search_filter} AND {$search_agent} `datetime` BETWEEN '{$datetimestart}' and '{$datetimeend}'";
    }
    $filter->showpg = $_POST['showpg'];
    $filter->goto = $_POST['goto'];
    $filter->numberRec();
    
    echo "{$filter->totalreg},{$filter->totalpg},{$filter->showpg},{$filter->goto}";
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
function generateCSV(){
    $name = call_user_func(["Functions","getNameFile"]);
    $file = "../".TMP.$name.".csv";
    $csv = fopen($file, "w+");
    $content = implode("\n", $_REQUEST['Table']);
    fwrite($csv, $content);
    fclose($csv);
    if(file_exists($file)){
        echo BASEURL.TMP."\\".$name;
    }
    else{
        echo "erro";
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
        <table class='table'>".implode("\n", $_REQUEST['Table'])."</table>
    </body>
</html>
";
return $html;
}
