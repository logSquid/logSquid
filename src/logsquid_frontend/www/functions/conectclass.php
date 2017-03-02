<?php
$PATHS = array('class','css','js','img','functions','settings','realtime','filters','report','daemon','webgui','lang','graph','tmp','user');
$WWW = str_replace($PATHS, "", dirname(__FILE__));
require_once("{$WWW}functions/autoload.php");

$action = $_POST['action'];
switch ($action){
    case "setdatabase";
        setDataBase();
        break;
    case "setdatabasewizard";
        setDataBaseWizard();
        break;
    case "getdatabase":
        getDataBase();
        break;
    case "checkDB":
        checkDB();
        break;
    case "checkDatabaseWizard":
        checkDatabase();
        break;
    case "getRealTime":
        getRealTime();
        break;
    case "searchpg":
        searchpg();
        break;
    case "filter";
        searchfilter();
        break;
    case "getnumpg":
        getnumpg();
        break;
    case "countlines":
        countlines();
        break;
    case "writelogs":
        writelogs();
        break;
    case "generatepdf":
        generatePDF();
        break;
    case "generatecsv":
        generateCSV();
        break;
    case "generatehtml":
        generateHTML();
        break;
    case "report":
        report();
        break;
    case "getListTimezone":
	getListTimezone();
	break;
}

function setDataBase(){
    $hostname = $_POST['hostname'];
    $username = $_POST['username'];
    $password = $_POST['password'];
    $database = $_POST['database'];
    $timezone = $_POST['timezone'];
    
    $conf = new logSquidconf();
    $conf->writeDataBase($hostname, $username, $password, $database, $timezone);
}
function setDataBaseWizard(){
    $hostname = $_POST['hostname'];
    $username = $_POST['username'];
    $password = $_POST['password'];
    $database = $_POST['database'];
    $timezone = $_POST['timezone'];
    
    $conf = new logSquidconf();
    $conf->writeDataBase($hostname, $username, $password, $database, $timezone);
    if($conf->status == true){
    ?><script>
        $(document).ready(function(){
            $(".wizard-logs").append("<div><span class=\"glyphicon glyphicon-ok check\" aria-hidden=\"true\"></span>Criação do arquivo logsquid_frontend.conf</div>");
            status++;
        });
    </script><?php
    }
    else{
    ?><script>
        $(document).ready(function(){
            $(".wizard-logs").append("<div><span class=\"glyphicon glyphicon-remove check\" aria-hidden=\"true\"></span>Criação do arquivo logsquid_frontend.conf</div>");
        });
    </script><?php
    }
}

function getListTimezone(){
	$conf = new logSquidconf();
	$list = array();
	$list = $conf->get_list_timezone();
	foreach($list as $l){
		echo "<option value='{$l}'>{$l}</option>";
	}
}

function getDataBase(){
    $logsquid = new logsquid();
    $conf = new logSquidconf();
    $conf->readDataBase();
    echo "{$conf->hostname};{$conf->username};{$conf->password};{$conf->database};{$conf->timezone}";
}

function checkDB(){
    $database = new logsquid();
    $database->checkDB($database->database, "check");
    echo $database->result;
}

function checkDatabase(){
    $database = new logsquid(1);
    if($database->Con == TRUE){
    ?><script>
        $(document).ready(function(){
            $(".wizard-logs").append("<div><span class=\"glyphicon glyphicon-ok check\" aria-hidden=\"true\"></span>Testando conexão com o Banco de Dados");
            status++;
        });
    </script><?php   
    }
    else{
    ?><script>
        $(document).ready(function(){
            $(".wizard-logs").append("<div><span class=\"glyphicon glyphicon-remove check\" aria-hidden=\"true\"></span>Testando conexão com o Banco de Dados");
        });
    </script><?php   
    }
}

function getRealTime(){
    $logSquid = new logsquid();
    $realtime = new realtime();
    $search = $_REQUEST['search'];
    $showlines = $_REQUEST['showlines'];
    $fields = $_REQUEST['fields'];
    $agent = NULL;
    if(isset($_POST['agent'])){
	$agent = $_POST['agent'];
    }

    $realtime->nRealTimelogSquid($search, $showlines, $fields, $agent);
}

function searchpg(){
    $showpg = $_POST['showpg'];
    $goto = $_POST['goto'];
    $logSquid = new logsquid();
    $logSquid->numlimit = $showpg;
    $logSquid->goto = $goto;
    if($logSquid->typelog == "access"){
        $logSquid->readAccessLog();
    }
    else if($logSquid->typelog == "logSquid"){
        $logSquid->readlogSquid();
    }
}
function searchfilter(){
    $search = explode(",", $_POST['search']);
    $datestart = ($_POST['datestart']);
    $dateend = ($_POST['dateend']);
    $timestart = $_POST['timestart'];
    $timeend = $_POST['timeend'];
    $datetimestart = "{$datestart} {$timestart}";
    $datetimeend = "{$dateend} {$timeend}";
    $showpg = $_POST['showpg'];
    $goto = $_POST['goto'];
    $logsquid = new logsquid();
    if($_POST['typefilter'] == ""){
        $logsquid->where = "WHERE `datetime` BETWEEN '{$datetimestart}' and '{$datetimeend}'"; 
    }else{ 
        $typefilter = explode(",", $_POST['typefilter']);
        for($i = 0; $i < count($typefilter); $i++){
            $filter[] = "{$typefilter[$i]} LIKE '%".trim($search[$i])."%'";
        }
        $search_filter = implode(" AND ", $filter);
        $logsquid->where = "WHERE {$search_filter} AND `datetime` BETWEEN '{$datetimestart}' and '{$datetimeend}'"; 
    }
    $logsquid->numlimit = $showpg;
    $logsquid->goto = $goto;
    
    if($logsquid->typelog == "access"){
        $logsquid->readAccessLog();
    }
    else if($logsquid->typelog == "logSquid"){
        $logsquid->readlogSquid();
    }
}
function getnumpg(){
    $search = explode(",", $_POST['search']);
    $datestart = $_POST['datestart'];
    $dateend = $_POST['dateend'];
    $timestart = $_POST['timestart'];
    $timeend = $_POST['timeend'];
    $datetimestart = "{$datestart} {$timestart}";
    $datetimeend = "{$dateend} {$timeend}";
    $showpg = $_POST['showpg'];
    $goto = $_POST['goto'];
    $logsquid = new logsquid();
    if($_POST['typefilter'] == ""){
        $logsquid->where = "WHERE `datetime` BETWEEN '{$datetimestart}' and '{$datetimeend}'"; 
    }else{ 
        $typefilter = explode(",", $_POST['typefilter']);
        for($i = 0; $i < count($typefilter); $i++){
            $filter[] = "{$typefilter[$i]} LIKE '%".trim($search[$i])."%'";
        }
        $search_filter = implode(" AND ", $filter);
        $logsquid->where = "WHERE {$search_filter} AND `datetime` BETWEEN '{$datetimestart}' and '{$datetimeend}'"; 
    }
    $logsquid->numlimit = $_POST['showpg'];
    $logsquid->goto = $_POST['goto'];
    $logsquid->nPage();
    
    echo "{$logsquid->totalreg},{$logsquid->totalpg},{$logsquid->numlimit},{$logsquid->goto}";
}

function generatePDF(){
    ini_set('memory_limit', '512M');
    include '../pdf/mpdf.php';
    $search = explode(",", $_POST['search']);
    $datetimestart = "{$_POST['datestart']} {$_POST['timestart']}";
    $datetimeend = "{$_POST['dateend']} {$_POST['timeend']}";
    if($_POST['typefilter'] == ""){
        $where = "WHERE `datetime` BETWEEN '{$datetimestart}' and '{$datetimeend}'"; 
    }else{ 
        $typefilter = explode(",", $_POST['typefilter']);
        for($i = 0; $i < count($typefilter); $i++){
            $filter[] = "{$typefilter[$i]} LIKE '%".trim($search[$i])."%'";
        }
        $search_filter = implode(" AND ", $filter);
        $where = "WHERE {$search_filter} AND `datetime` BETWEEN '{$datetimestart}' and '{$datetimeend}'"; 
    }
    $pdf = new logsquidpdf($where, $_POST);
    ob_start();
    $pdf->createStructure();
    $html = ob_get_clean();
    $html = utf8_encode($html);
    
    $gpdf = new mPDF("utf-8", "{$_POST['format']}{$_POST['orientation']}", "", "", 1, 1, 1, 4, 1, 1, "{$_POST['orientation']}");
    $gpdf->allow_charset_conversion = true;
    $gpdf->charset_in = "UTF-8";
    $gpdf->SetFooter('logSquid - Squid filter           pg {PAGENO}');
    $gpdf->WriteHTML($html);
    $gpdf->Output("../".FILTERS."export/{$_POST['pdfname']}.pdf","F");
}
function generateCSV(){
    $search = explode(",", $_POST['search']);
    $datetimestart = "{$_POST['datestart']} {$_POST['timestart']}";
    $datetimeend = "{$_POST['dateend']} {$_POST['timeend']}";
    if($_POST['typefilter'] == ""){
        $where = "WHERE `datetime` BETWEEN '{$datetimestart}' and '{$datetimeend}'"; 
    }else{ 
        $typefilter = explode(",", $_POST['typefilter']);
        for($i = 0; $i < count($typefilter); $i++){
            $filter[] = "{$typefilter[$i]} LIKE '%".trim($search[$i])."%'";
        }
        $search_filter = implode(" AND ", $filter);
        $where = "WHERE {$search_filter} AND `datetime` BETWEEN '{$datetimestart}' and '{$datetimeend}'"; 
    }
    $csv = new logsquidcsv($where, $_POST);
    ob_start();
    $csv->createStructure();
    $gcsv = ob_get_clean();
    $gcsv = utf8_encode($gcsv);
    
    $file = fopen("../".FILTERS."export/{$_POST['csvname']}.csv", 'a');
    $write = fwrite($file, $gcsv);
    fclose($file);
    if($file){
        echo 1;
    }
    else{
        echo 0;
    }
}
function generateHTML(){
    $search = explode(",", $_POST['search']);
    $datetimestart = "{$_POST['datestart']} {$_POST['timestart']}";
    $datetimeend = "{$_POST['dateend']} {$_POST['timeend']}";
    if($_POST['typefilter'] == ""){
        $where = "WHERE `datetime` BETWEEN '{$datetimestart}' and '{$datetimeend}'"; 
    }else{ 
        $typefilter = explode(",", $_POST['typefilter']);
        for($i = 0; $i < count($typefilter); $i++){
            $filter[] = "{$typefilter[$i]} LIKE '%".trim($search[$i])."%'";
        }
        $search_filter = implode(" AND ", $filter);
        $where = "WHERE {$search_filter} AND `datetime` BETWEEN '{$datetimestart}' and '{$datetimeend}'"; 
    }
    $html = new logsquidhtml($where, $_POST);
    ob_start();
    $html->createStructure();
    $ghtml = ob_get_clean();
    $ghtml = utf8_encode($ghtml);
    
    $file = fopen("../".FILTERS."export/{$_POST['htmlname']}.html", "a");
    $write = fwrite($file, $ghtml);
    fclose($file);
    if($file){
        echo 1;
    }
    else{
        echo 0;
    }
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
    $logsquid = new logsquid();
    $logsquid->where = $where;
    #$logsquid->reportlogSquidData();
}
