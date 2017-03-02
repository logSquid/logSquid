<?php
/**
 * @author Mauro Marssola
 */
$PATHS = array('class','css','js','img','functions','settings','realtime','filters','report','daemon','webgui','lang','graph','tmp','user', 'services');
$WWW = str_replace($PATHS, "", dirname(__FILE__));
require_once("{$WWW}functions/autoload.php");

class filters extends logsquid{

    public function __construct() {
        parent::__construct();
    }
    
    public function numberRec(){
        if($this->typelog == "access"){$table = "squid";}
        else if($this->typelog == "logSquid"){$table = "logSquid";}
        if($this->where == NULL){
            $datetimestart = date("Y-m-d 00:00:00");
            $datetimeend = date("Y-m-d 23:59:59");
            $this->where = "WHERE `datetime` BETWEEN '{$datetimestart}' and '{$datetimeend}'";
        }
        $records = mysql_query("SELECT COUNT(*) as count FROM logSquid {$this->where}");
        $this->numrows = mysql_fetch_assoc($records);
        $this->totalreg = ($this->numrows['count']);
        
        ($this->goto == NULL)? $this->goto = 1: "";
        ($this->numstart == NULL)? $this->numstart = 0: "";
        ($this->showpg == NULL)? $this->numlimit = 100: "";
        $this->totalpg = ceil($this->totalreg / $this->showpg);
    }
    
    public function SelectLogSquid(){
        if($this->showpg == NULL){
            $this->numlimit = "LIMIT 0,100";
        }
        else{
            ($this->goto == 1)? $this->numstart = 0: $this->numstart = ($this->goto * $this->showpg) - ($this->showpg);
            $this->numlimit = "LIMIT {$this->numstart}, {$this->showpg}";
        }
        if($this->where == NULL){
            $datetimestart = date("Y-m-d 00:00:00");
            $datetimeend = date("Y-m-d 23:59:59");
            $this->where = "WHERE `datetime` BETWEEN '{$datetimestart}' and '{$datetimeend}'";
        }
        if($this->orderby == NULL){
            $this->orderby = "ORDER BY datetime DESC";
        }
        else{
            $this->orderby = "ORDER BY {$this->orderby}";
        }
        if($this->fields == NULL){
            $this->fields = "*";
        }
        
        mysql_query("SET character_set_results = 'utf8', character_set_client = 'utf8', character_set_connection = 'utf8', character_set_database = 'utf8', character_set_server = 'utf8'");
        $this->select = "SELECT {$this->fields} FROM logSquid {$this->where} {$this->orderby} {$this->numlimit}";
        $this->result = mysql_query($this->select);
        $i = 1;
        $fields = explode(", ", $this->fields);
        echo "";
        echo "<form class='filter-form'>";
        while ($log = @mysql_fetch_assoc($this->result)){
            $errorcode = explode("/", $log['status']);
            #<td style='color: ".  call_user_func(["Functions", "getColorTamFile"], call_user_func(["Functions", 'convertSize'], $log['size']))."'>".  call_user_func(["Functions", 'convertSize'], $log['size'])."</td>
            echo "<tr id=\"filter-{$i}\">";
            echo "<td id=\"check\"><input type=\"checkbox\" value=\"{$i}\" name=\"cline\" id=\"\" /><span></span></td>";
            if(in_array("datetime", $fields)) echo "<td class=\"nowrap\">".date('d/m/Y H:i:s',strtotime($log['datetime']))."</td>";
            if(in_array("ipuser", $fields)) echo "<td>{$log['ipuser']}</td>";
            if(in_array("macaddress", $fields)) echo "<td style=\"text-transform: uppercase\">{$log['macaddress']}</td>";
            if(in_array("username", $fields)) echo "<td>{$log['username']}</td>";
            if(in_array("destination", $fields)) echo "<td><a href=\"http://{$log['destination']}\" target=\"_blank\">{$log['destination']}</a></td>";
            if(in_array("url", $fields)) echo "<td class=\"break\"><a href=\"{$log['url']}\" target=\"_blank\">{$log['url']}</a></td>";
            if(in_array("ipdest", $fields)) echo "<td>{$log['ipdest']}</td>";
            if(in_array("mime", $fields)) echo "<td>{$log['mime']}</td>";
            if(in_array("size", $fields)) echo "<td style='color: ".  call_user_func(["Functions", "getColorTamFile"], call_user_func(["Functions", 'convertSize'], $log['size']))."'>".call_user_func(["Functions", 'convertSize'], $log['size'])."</td>";
            if(in_array("status", $fields)) echo "<td id=\"statuscod\" data-toggle=\"tooltip\" data-placement=\"left\" title=\"".$this->statusReturn($log['status'])."\">{$log['status']}</td>";
            echo "</tr>";
            $i++;
        }
        echo "</form>";
        mysql_num_rows($this->result) or die("<tr><td colspan=\"11\" class=\"wfilter\"><input type=\"hidden\" value=\"null\" name=\"searchnull\"/>Nenhum resultado encontrado, ou seu filtro est&aacute; incorreto.</td></tr>");
    }
    
    
}
