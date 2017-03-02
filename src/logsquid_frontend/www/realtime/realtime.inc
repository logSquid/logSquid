<?php
$PATHS = array('class','css','js','img','functions','settings','realtime','filters','report','daemon','webgui','lang','graph','tmp','user');
$WWW = str_replace($PATHS, "", dirname(__FILE__));
require_once("{$WWW}functions/autoload.php");

class realtime extends logsquid{
    
    public function __construct(){
        parent::__construct();
    }
    
    public function nRealTimeSquid($search = NULL, $showlines = NULL){
        $logsquid = new logsquid();
        ($showlines == NULL)? $lines = 20 : $lines = $showlines;
        ($search == NULL)? $grep = "": $grep = "| /usr/bin/grep {$search}";
    }
    public function nRealTimelogSquid($search = NULL, $showlines = NULL, $fields = NULL, $agent = NULL){
        $search_agent = ($agent == "")? "": "`agent`='{$agent}' AND";
        $logsquid = new logsquid();
        ($showlines == NULL)? $lines = "LIMIT 0,20" : $lines = "LIMIT 0,{$showlines}";
        if($search == NULL && $search_agent != ""){
            $where = "WHERE `agent`='{$agent}'";
        }
        elseif(ereg("!", $search)){
            $search = str_replace("!", "", $search);
            $where = "
                WHERE {$search_agent} ipuser NOT LIKE '%{$search}%' OR destination NOT LIKE '%{$search}%' OR url NOT LIKE '%{$search}%' OR
                    ipdest NOT LIKE '%{$search}%' OR mime NOT LIKE '%{$search}%' OR size NOT LIKE '%{$search}%' OR status NOT LIKE '%{$search}%'
            ";
        }
        else{
            ($search == NULL)? $where = "": $where = "
                WHERE {$search_agent} ipuser LIKE '%{$search}%' OR destination LIKE '%{$search}%' OR url LIKE '%{$search}%' OR
                    ipdest LIKE '%{$search}%' OR mime LIKE '%{$search}%' OR size LIKE '%{$search}%' OR status LIKE '%{$search}%'
            ";
        }
        if($fields == NULL || $fields == "") $fields = "datetime, ipuser, macaddress, username, destination, url, ipdest, mime, size, status";
        $efields = explode(", ", $fields);
        
        mysql_query("SET character_set_results = 'utf8', character_set_client = 'utf8', character_set_connection = 'utf8', character_set_database = 'utf8', character_set_server = 'utf8'");
        $this->select = "SELECT {$fields} FROM logSquid {$where} ORDER BY datetime DESC {$lines}";
        $this->result = mysql_query($this->select);
        $i = 1;
        while($log = @mysql_fetch_assoc($this->result)){
            $errorcode = explode("/", $log['status']);
            echo "<tr id=\"realtime-{$i}\">";
            if(in_array("datetime", $efields)) echo "<td class=\"nowrap\">".date('d/m/Y H:i:s',strtotime($log['datetime']))."</td>";
            if(in_array("ipuser", $efields)) echo "<td>{$log['ipuser']}</td>";
            if(in_array("macaddress", $efields)) echo "<td style=\"text-transform: uppercase\">{$log['macaddress']}</td>";
            if(in_array("username", $efields)) echo "<td>{$log['username']}</td>";
            if(in_array("destination", $efields)) echo "<td><a href=\"http://{$log['destination']}\" target=\"_blank\">{$log['destination']}</a></td>";
            if(in_array("url", $efields)) echo "<td class=\"break\"><a href=\"{$log['url']}\" target=\"_blank\">{$log['url']}</a></td>";
            if(in_array("ipdest", $efields)) echo "<td>{$log['ipdest']}</td>";
            if(in_array("mime", $efields)) echo "<td>{$log['mime']}</td>";
            if(in_array("size", $efields)) echo "<td style='color: ".  call_user_func(["Functions", "getColorTamFile"], call_user_func(["Functions", 'convertSize'], $log['size']))."'>".call_user_func(["Functions", 'convertSize'], $log['size'])."</td>";
            if(in_array("status", $efields)) echo "<td id=\"statuscod\" data-toggle=\"tooltip\" data-placement=\"left\" title=\"".$this->statusReturn($log['status'])."\">{$log['status']}</td>";
            echo "</tr>";
            $i++;
        }
    }
}

