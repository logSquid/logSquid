<?php
$PATHS = array('class','css','js','img','functions','settings','realtime','filters','report','daemon','webgui','lang','graph','tmp','user');
$WWW = str_replace($PATHS, "", dirname(__FILE__));

require_once("{$WWW}functions/autoload.php");
class logsquid extends conectdb{
    protected $Session;
    public $squid;
    public $logSquid;
    public $logSquid_0;
    public $squid_conf;
    public $read_logSquid_0;
    public $access_log;
    public $logsquidd = "daemon.log";
    public $flogsquidd;
    public $configXml;
    
    public $typelog;
    public $filelog;
    public $pathlog;
    public $filerotate;
    public $read_filerotate;
    public $read_filelog;
    
    public $linestart;
    public $linemax;

    protected $insert;
    protected $select;
    protected $update;
    protected $delete;
    protected $LinesAffected;
    public $result;
    public $realtime;
    protected $truncate;
    public $numrows;
    public $goto;
    public $showpg;
    public $numstart;
    public $numlimit;
    public $totalreg;
    public $totalpg;
    public $where;
    public $orderby;
    public $fields;
    public $database;

    public $readLogStart;

    public function __construct($check = NULL) {
        $logSquidconf = new logSquidconf();
        $logSquidconf->readDataBase();
        $this->typelog = $logSquidconf->typelog;
        $this->pathlog = $logSquidconf->pathlog;
        $this->filelog = "{$logSquidconf->pathlog}{$this->typelog}.log";
        $this->filerotate = "{$logSquidconf->pathlog}{$this->typelog}.log.0";
        $this->squid = "{$logSquidconf->binsquid}";
        $this->squid_conf = "{$logSquidconf->pathsquid}etc/squid/squid.conf";
        $this->database = trim($logSquidconf->database);
        parent::setData(trim($logSquidconf->hostname), trim($logSquidconf->username), trim($logSquidconf->password), trim($logSquidconf->database));
        parent::Conect();
        if($check == NULL)
            $this->checkHash();
    }
    
    protected function checkHash(){
        $this->Session = new Session();
        $check_hash_select = "SELECT `hashCode` FROM users WHERE `username`='{$this->Session->getField('username')}' and `hashCode`='{$this->Session->getField('hash')}'";
        $check_hash_query = mysql_query($check_hash_select);
        $check_hash_rows = mysql_num_rows($check_hash_query);
        
        if($check_hash_rows != 1){
            exit("Voce não tem permissão");
        }
    }
    
    public function makeTypeLog(){
        exec("/bin/mv {$this->filelog} {$this->filerotate};sudo {$this->squid} -k reconfigure");
    }
    public function readTypeLog(){
        //$this->read_filerotate = file($this->filerotate);
        exec("cat {$this->filerotate}", $this->read_filerotate);
        $this->flogsquidd = fopen(WWW.$this->logsquidd, "a+");
        $i = 1;
        if(isset($this->readLogStart)){
            if($this->typelog == "access"){
                foreach ($this->read_filerotate as $line){
                    if($i <= $this->readLogStart){$i++;}
                    else{
                        $Line = trim(preg_replace("/ +/", ' ', $line));
                        $Linha = explode(" ", $Line);
                        if(strpos($Linha[6], "logsquid/functions/conectclass.php") == FALSE){
                            if($Linha[0] == "" and $Linha[1] == "" and $Linha[2] == "" and $Linha[3] == "" and $Linha[4] == "" and $Linha[5] == "" and $Linha[6] == "" and $Linha[7] == "" and $Linha[8] == "" and $Linha[9] == ""){}
                            else{
                                $datetime = date("Y/m/d H:i:s",$Linha[0]);
                                $campos = "`datetime`, `ipuser`, `username`, `url`, `ipdest`, `mime`, `size`, `status`, `macaddress`, `destination`";
                                $valores = "'{$datetime}', '{$Linha[2]}', '{$Linha[7]}', '{$Linha[6]}', '{$Linha[8]}', '{$Linha[9]}', '{$Linha[4]}', '{$Linha[3]}', '-', '-'";
                                logsquid::insertLog($campos, $valores);
                                fwrite($this->flogsquidd, $i++.PHP_EOL);
                            }
                        }
                    }
                }
            }
            else if($this->typelog == "logSquid"){
                foreach ($this->read_filerotate as $line){
                    if($i <= $this->readLogStart){$i++;}
                    else{
                        $Linha = explode(" ", $line);
                        if(strpos($Linha[5], "logsquid/functions/conectclass.php") == FALSE){
                            if($Linha[0] == "" and $Linha[1] == "" and $Linha[2] == "" and $Linha[3] == "" and $Linha[4] == "" and $Linha[5] == "" and $Linha[6] == "" and $Linha[7] == "" and $Linha[8] == "" and $Linha[9] == ""){}
                            else{
                                $datetime = $Linha[0]; #date("Y/m/d H:i:s",$Linha[0]);
                                $campos = "`datetime`, `ipuser`, `macaddress`, `username`, `destination`, `url`, `ipdest`, `mime`, `size`, `status`";
                                $valores = "'{$datetime}','{$Linha[1]}','{$Linha[2]}','{$Linha[3]}','{$Linha[4]}','{$Linha[5]}','{$Linha[6]}','{$Linha[7]}','{$Linha[8]}','{$Linha[9]}'";
                                logsquid::insertLog($campos, $valores);
                                fwrite($this->flogsquidd, $i++.PHP_EOL);
                            }
                        }
                    }
                }
            }
        }
        else{
            if($this->typelog == "access"){
                foreach ($this->read_filerotate as $line){
                    $Line = trim(preg_replace("/ +/", ' ', $line));
                    $Linha = explode(" ", $Line);
                    if(strpos($Linha[6], "logsquid/functions/conectclass.php") == FALSE){
                        if($Linha[0] == "" and $Linha[1] == "" and $Linha[2] == "" and $Linha[3] == "" and $Linha[4] == "" and $Linha[5] == "" and $Linha[6] == "" and $Linha[7] == "" and $Linha[8] == "" and $Linha[9] == ""){}
                        else{
                            $datetime = date("Y/m/d H:i:s",$Linha[0]);
                            $campos = "`datetime`, `ipuser`, `username`, `url`, `ipdest`, `mime`, `size`, `status`, `macaddress`, `destination`";
                            $valores = "'{$datetime}', '{$Linha[2]}', '{$Linha[7]}', '{$Linha[6]}', '{$Linha[8]}', '{$Linha[9]}', '{$Linha[4]}', '{$Linha[3]}', '-', '-'";
                            logsquid::insertLog($campos, $valores);
                            fwrite($this->flogsquidd, $i++.PHP_EOL);
                        }
                    }
                }
            }
            else if($this->typelog == "logSquid"){
                foreach ($this->read_filerotate as $line){
                    $Linha = explode(" ", $line);
                    if(strpos($Linha[5], "logsquid/functions/conectclass.php") == FALSE){
                        if($Linha[0] == "" and $Linha[1] == "" and $Linha[2] == "" and $Linha[3] == "" and $Linha[4] == "" and $Linha[5] == "" and $Linha[6] == "" and $Linha[7] == "" and $Linha[8] == "" and $Linha[9] == ""){}
                        else{
                            $datetime = date("Y/m/d H:i:s",$Linha[0]);
                            $campos = "`datetime`, `ipuser`, `macaddress`, `username`, `destination`, `url`, `ipdest`, `mime`, `size`, `status`";
                            $valores = "'{$datetime}','{$Linha[1]}','{$Linha[2]}','{$Linha[3]}','{$Linha[4]}','{$Linha[5]}','{$Linha[6]}','{$Linha[7]}','{$Linha[8]}','{$Linha[9]}'";
                            logsquid::insertLog($campos, $valores);
                            fwrite($this->flogsquidd, $i++.PHP_EOL);
                        }
                    }
                }
            }
        }
    }
    public function insertLog($campos, $valores){
        mysql_query("SET character_set_results = 'utf8', character_set_client = 'utf8', character_set_connection = 'utf8', character_set_database = 'utf8', character_set_server = 'utf8'");
        $this->insert = "INSERT INTO `logSquid`({$campos}) VALUES ({$valores})";
        mysql_query($this->insert);
        $this->LinesAffected = mysql_affected_rows();
        if($this->LinesAffected == -1){
            return "Nenhuma alteraçao feita";
        }
        else if($this->LinesAffected == 0){
            return "Falha na operacao";
        }
        else if($this->LinesAffected > 0){
            return "Dados inseridos com sucesso";
        }
    }
    /* Start NumPage */
    public function nPage(){
        if($this->typelog == "access"){$table = "squid";}
        else if($this->typelog == "logSquid"){$table = "logSquid";}
        if($this->where == NULL){
            $datetimestart = date("Y-m-d 00:00:01");
            $datetimeend = date("Y-m-d 23:59:59");
            $where = "WHERE `datetime` BETWEEN '{$datetimestart}' and '{$datetimeend}'";
        }
        else{$where = $this->where;}
        /*$select = "SELECT id FROM {$table} {$where}";
        $this->numrows = mysql_num_rows(mysql_query($select));
         */
        $select = mysql_query("SELECT COUNT(*) as count FROM {$table} {$where}");
        $this->numrows = mysql_fetch_assoc($select);
        $this->totalreg = ($this->numrows['count']);
        ($this->goto == NULL)? $this->goto = 1 : $goto = $this->goto;
        ($this->numstart == NULL)? $this->numstart = 1: "";
        ($this->numlimit == NULL)? $this->numlimit = 100: "";
        $this->totalpg = floor(($this->totalreg / $this->numlimit));
    }
    public function shownPage(){
        ?>
        <div class="numpage" id="area-numpage">
            <span class="group-text group-text-border">
                <span class="text-info"><b><input type="hidden" value="<?=$this->totalreg?>" id="totalreg" /><span id="sTotalreg"><?=$this->totalreg?></span>&nbsp;</b></span>
                <span class="text-info">registros</span>
            </span>
            <span class="group-text group-text-border">
                <span class="text-info">exibir&nbsp;</span>
                <span class="text-info"><input type="number" step="10" min="10" value="<?=$this->numlimit?>" name="showpg" id="showpg" class="form-control input-showpg" /></span>
            </span>
            <span class="group-text">
                <span class="text-info">ir p/&nbsp;</span>
                <span class="text-info"><input type="number" value="<?=$this->goto?>" min="1" max="<?=$this->totalpg?>" name="goto" id="goto" class="form-control input-showpg" /></span>
                <span class="text-info">de</span>
                <span class="text-info"><b><input type="hidden" value="<?=$this->totalpg?>" id="totalpg"/><span id="sTotalpg"><?=$this->totalpg?></span></b></span>
            </span>
        </div>
    <?php
    }
    public function shownPagef(){
    ?>
        <div class="numpage">
            <span class="group-text group-text-border">
                <span class="text-info"><b><input type="hidden" value="<?=$this->totalreg?>" id="totalregf" /><span id="sTotalregf"><?=$this->totalreg?></span>&nbsp;</b></span>
                <span class="text-info">registros</span>
            </span>
            <span class="group-text group-text-border">
                <span class="text-info">exibir&nbsp;</span>
                <span class="text-info"><input type="number" step="10" min="10" value="<?=$this->numlimit?>" name="showpgf" id="showpgf" class="form-control input-showpg" /></span>
            </span>
            <span class="group-text">
                <span class="text-info">ir p/&nbsp;</span>
                <span class="text-info"><input type="number" value="<?=$this->goto?>" min="1" max="<?=$this->totalpg?>" name="gotof" id="gotof" class="form-control input-showpg" /></span>
                <span class="text-info">de</span>
                <span class="text-info"><b><input type="hidden" value="<?=$this->totalpg?>" id="totalpgf"/><span id="sTotalpgf"><?=$this->totalpg?></span></b></span>
            </span>
        </div>
    <?php
    }
    protected function numPage(){
        if($this->typelog == "access"){$table = "squid";}
        else if($this->typelog == "logSquid"){$table = "logSquid";}
        if($this->where == NULL){ $where = ""; }else{$where = $this->where;}
        $select = "SELECT * FROM {$table} {$where}";
        $this->numrows = mysql_num_rows(mysql_query($select));
        $totalreg = ($this->numrows);
        $showpg = 100;
        $totalpg = floor(($totalreg / $showpg));
        ($this->goto == NULL)? $goto = 1 : $goto = $this->goto;
        ($this->numstart == NULL)? $numstart = 1: $numstart = $this->numstart;
        ($this->numlimit == NULL)? $numlimit = 100: $numlimit = $this->numlimit;
    ?>
        <div class="numpage">
            <span class="group-text group-text-border">
                <span class="text-info"><b><input type="hidden" value="<?=$totalreg?>" id="totalreg" /><span id="sTotalreg"><?=$totalreg?></span>&nbsp;</b></span>
                <span class="text-info">registros</span>
            </span>
            <span class="group-text group-text-border">
                <span class="text-info">mostrar&nbsp;</span>
                <span class="text-info"><input type="number" step="10" min="10" value="100" name="showpg" id="showpg" class="form-control input-showpg" /></span>
            </span>
            <span class="group-text">
                <span class="text-info">ir p/ p&aacute;g&nbsp;</span>
                <span class="text-info"><input type="number" value="<?=$goto?>" min="1" max="<?=$totalpg?>" name="goto" id="goto" class="form-control input-showpg" /></span>
                <span class="text-info">de</span>
                <span class="text-info"><b><input type="hidden" value="<?=$totalpg?>" id="totalpg"/><span id="sTotalpg"><?=$totalpg?></span></b></span>
            </span>
        </div>
    <?php
    }
    protected function numPagefooter(){
        if($this->typelog == "access"){$table = "squid";}
        else if($this->typelog == "logSquid"){$table = "logSquid";}
        $select = "SELECT * FROM {$table}";
        $this->numrows = mysql_num_rows(mysql_query($select));
        $totalreg = ($this->numrows);
        $showpg = 100;
        $totalpg = floor(($totalreg / $showpg));
        $goto = 1;
        ($this->goto == NULL)? $goto = 1 : $goto = $this->goto;
        ($this->numstart == NULL)? $numstart = 1: $numstart = $this->numstart;
        ($this->numlimit == NULL)? $numlimit = 100: $numlimit = $this->numlimit;
    ?>
        <div class="numpage">
            <span class="group-text group-text-border">
                <span class="text-info"><b><input type="hidden" value="<?=$totalreg?>" id="totalregf" /><span id="sTotalregf"><?=$totalreg?></span>&nbsp;</b></span>
                <span class="text-info">registros</span>
            </span>
            <span class="group-text group-text-border">
                <span class="text-info">mostrar&nbsp;</span>
                <span class="text-info"><input type="number" step="10" min="10" value="100" name="showpgf" id="showpgf" class="form-control input-showpg" /></span>
            </span>
            <span class="group-text">
                <span class="text-info">ir p/ p&aacute;g&nbsp;</span>
                <span class="text-info"><input type="number" value="<?=$goto?>" min="1" max="<?=$totalpg?>" name="gotof" id="gotof" class="form-control input-showpg" /></span>
                <span class="text-info">de</span>
                <span class="text-info"><b><input type="hidden" value="<?=$totalpg?>" id="totalpgf"/><span id="sTotalpgf"><?=$totalpg?></span></b></span>
            </span>
        </div>
    <?php
    }
    /* End NumPage */
    /* Start Filter */
    public function readLog(){
        if($this->typelog == "access"){
            logsquid::headerReadSquid();
        }
        else if($this->typelog == "logSquid"){
            logsquid::headerReadlogSquid();
        }
    }
    public function readAccessLog(){
        if ($this->numlimit == NULL) {
            $limit = "LIMIT 1,100";
        } else {
            ($this->goto == 1)? $this->numstart = 1 :$this->numstart =  $this->goto * $this->numlimit;
            $limit = "LIMIT {$this->numstart},{$this->numlimit}";
        }
        if($this->where == NULL){
            $datetimestart = date("Y-m-d 00:00:01");
            $datetimeend = date("Y-m-d 23:59:59");
            $where = "WHERE `datetime` BETWEEN '{$datetimestart}' and '{$datetimeend}'";
        }
        else{
            $where = $this->where;
        }
        mysql_query("SET character_set_results = 'utf8', character_set_client = 'utf8', character_set_connection = 'utf8', character_set_database = 'utf8', character_set_server = 'utf8'");
        $this->select = "SELECT * FROM squid {$where} ORDER BY id DESC {$limit}";
        $this->result = mysql_query($this->select);
        while ($log = @mysql_fetch_assoc($this->result)){
                echo "
                    <tr id=\"{$log['id']}\">
                        <td class=\"nowrap\">".date('d/m/Y H:i:s',strtotime($log['datetime']))."</td>
                        <td>{$log['timeresp']}</td>
                        <td>{$log['client']}</td>
                        <td>".call_user_func(["Functions", 'convertSize'], $log['size'])."</td>
                        <td>{$log['method']}</td>
                        <td class=\"break\"><a href=\"{$log['url']}\" target=\"_blank\">{$log['url']}</a></td>
                        <td>{$log['user']}</td>
                        <td>{$log['request']}</td>
                        <td>{$log['mime']}</td>
                        <td>{$this->statusReturn($log['action'])}</td>
                    </tr>
                ";
        }
    }
    public function readlogSquid(){
        if ($this->numlimit == NULL) {
            $limit = "LIMIT 1,100";
        } else {
            ($this->goto == 1)? $this->numstart = 1 :$this->numstart =  $this->goto * $this->numlimit;
            $limit = "LIMIT {$this->numstart},{$this->numlimit}";
        }
        if($this->where == NULL){
            $datetimestart = date("Y-m-d 00:00:01");
            $datetimeend = date("Y-m-d 23:59:59");
            $where = "WHERE `datetime` BETWEEN '{$datetimestart}' and '{$datetimeend}'";
        }
        else{
            $where = $this->where;
        }
        mysql_query("SET character_set_results = 'utf8', character_set_client = 'utf8', character_set_connection = 'utf8', character_set_database = 'utf8', character_set_server = 'utf8'");
        $this->select = "SELECT * FROM logSquid {$where} ORDER BY id DESC {$limit}";
        $this->result = mysql_query($this->select);
        while ($log = @mysql_fetch_assoc($this->result)){
            $errorcode = explode("/", $log['status']);
            echo "
                <tr id=\"url-{$log['id']}\">
                    <td class=\"nowrap\">".date('d/m/Y H:i:s',strtotime($log['datetime']))."</td>
                    <td>{$log['ipuser']}</td>
                    <td style=\"text-transform: uppercase\">{$log['macaddress']}</td>
                    <td>{$log['username']}</td>
                    <td><a href=\"http://{$log['destination']}\" target=\"_blank\">{$log['destination']}</a></td>
                    <td class=\"break\"><a href=\"{$log['url']}\" target=\"_blank\">{$log['url']}</a></td>
                    <td>{$log['ipdest']}</td>
                    <td>{$log['mime']}</td>
                    <td style='color: ".  call_user_func(["Functions", "getColorTamFile"], call_user_func(["Functions", 'convertSize'], $log['size']))."'>".  call_user_func(["Functions", 'convertSize'], $log['size'])."</td>
                    <td id=\"statuscod\" data-toggle=\"tooltip\" data-placement=\"left\" title=\"".$this->statusReturn($log['status'])."\">{$log['status']}</td>
                </tr>
            ";
        }
    }
    protected function headerReadlogSquid(){?>
        <div class="area-search">
            <div class="search">
                <input type="text" class="input-search form-control" alt="table" placeholder="Procurar por qualquer item na p&atilde;gina" />
            </div>
            <?php logsquid::shownPage(); ?>
        </div>
        <table id="listAccess" class="table table-hover">
                <thead>
                    <tr class="">
                        <th>Data/Hora</th>
                        <th>IP</th>
                        <th>MAC Address</th>
                        <th>Usu&aacute;rio</th>
                        <th>Destino</th>
                        <th>URL</th>
                        <th nowrap>IP destino</th>
                        <th>Tipo</th>
                        <th>Tamanho</th>
                        <th>Status</th>
                    </tr>
                </thead>
                <tbody>
                    <?php logsquid::readlogSquid(); ?>
                </tbody>
        </table>
        <div class="area-search" style="border-top: solid 1px #ddd;height: 40px;">
            <div class="search">&nbsp;</div>
            <?php logsquid::shownPagef(); ?>
        </div>
        <?php
    }
    protected function headerReadSquid(){?>
        <div class="area-search">
            <div class="search">
                <input type="text" class="input-search form-control" alt="table" placeholder="Procurar por qualquer item na p&aacute;gina" />
            </div>
            <?php logsquid::shownPage(); ?>
        </div>
        <table id="listAccess" class="table table-hover">
            <thead>
                <tr>
                    <th>Data/Hora</th>
                    <th>TimeResp</th>
                    <th>Cliente</th>
                    <th>Tamanho</th>
                    <th>M&eacute;todo</th>
                    <th>URL</th>
                    <th>Usu&aacute;rio</th>
                    <th>Requisi&ccedil;&atilde;o</th>
                    <th>Tipo</th>
                    <th width="8%">A&ccedil;&atatilde;o</th>
                </tr>
            </thead>
            <tbody>
                <?php logsquid::readAccessLog(); ?>
            </tbody>
        </table>
        <div class="area-search" style="border-top: solid 1px #ddd;height: 40px;">
            <div class="search">&nbsp;</div>
            <?php logsquid::shownPagef(); ?>
        </div>
        <?php
    }
    /* End Filter */
    /* Start Filters Module - Export */
    public function PDFselectLog($settings){
        $View = explode(",", $settings['view']);
        $TypeFilter = explode(",", $settings['typefilter']);
        $Search = explode(",", $settings['search']);
        if ($this->numlimit == NULL) {
            $limit = "LIMIT 1,100";
        } else {
            ($this->goto == 1)? $this->numstart = 1 :$this->numstart =  $this->goto * $this->numlimit;
            $limit = "LIMIT {$this->numstart},{$this->numlimit}";
        }
        if($this->where == NULL){
            $datetimestart = date("Y-m-d 00:00:01");
            $datetimeend = date("Y-m-d 23:59:59");
            $where = "WHERE `datetime` BETWEEN '{$datetimestart}' and '{$datetimeend}'";
        }
        else{
            $where = $this->where;
        }
        mysql_query("SET character_set_results = 'utf8', character_set_client = 'utf8', character_set_connection = 'utf8', character_set_database = 'utf8', character_set_server = 'utf8'");
        $this->select = "SELECT * FROM logSquid {$where} ORDER BY id DESC {$limit}";
        $this->result = mysql_query($this->select);
            echo "
                    <table class=\"table table-pdf\">
                        <thead>
                            <tr>
                ";
                for($th = 0; $th < count($View);$th++){
                    echo "
                        <th>{$View[$th]}</th>
                        ";
                }
                echo "
                            </tr>
                        </thead>
                        <tbody>
                    ";
                while ($logs = mysql_fetch_assoc($this->result)){
                    echo "<tr>";
                    for($td = 0; $td < count($View);$td++){
                        if($View[$td] == "datetime"){
                            echo "<td class=\"nowrap\">{$logs[$View[$td]]}</td>";
                        }
                        else if($View[$td] == "url"){
                            echo "<td class=\"break\">".wordwrap($logs['url'], 50,"</br>",true)."</td>";
                        }
                        else{
                            echo "<td>{$logs[$View[$td]]}</td>";
                        }
                    }
                echo "</tr>";
                }
                echo "
                        </tbody>
                    </table>
                    ";
    }
    public function CSVselectLog($settings){
        $View = explode(",", $settings['view']);
        mysql_query("SET character_set_results = 'utf8', character_set_client = 'utf8', character_set_connection = 'utf8', character_set_database = 'utf8', character_set_server = 'utf8'");
        $this->select = "SELECT * FROM logSquid {$this->where} ORDER BY id DESC";
        $this->result = mysql_query($this->select);
        while ($result = mysql_fetch_assoc($this->result)){
            for($c = 0; $c < count($View); $c++){
                echo "{$result[$View[$c]]}";
                if($c != (count($View)-1)){
                    echo ",";
                }
            }
            echo "\n";
        }
    }
    public function HTMLselectLog($settings){
        $View = explode(",", $settings['view']);
        mysql_query("SET character_set_results = 'utf8', character_set_client = 'utf8', character_set_connection = 'utf8', character_set_database = 'utf8', character_set_server = 'utf8'");
        $this->select = "SELECT * FROM logSquid {$this->where} ORDER BY id DESC";
        $this->result = mysql_query($this->select);
            echo "
                    <table class=\"table table-html\">
                        <thead>
                            <tr>
                ";
                for($th = 0; $th < count($View);$th++){
                    echo "
                        <th>{$View[$th]}</th>
                        ";
                }
                echo "
                            </tr>
                        </thead>
                        <tbody>
                    ";
                while ($logs = mysql_fetch_assoc($this->result)){
                    echo "<tr>";
                    for($td = 0; $td < count($View);$td++){
                        if($View[$td] == "datetime"){
                            echo "<td class=\"nowrap\">{$logs[$View[$td]]}</td>";
                        }
                        else if($View[$td] == "url"){
                            echo "<td class=\"break\">".($logs['url'])."</td>";
                        }
                        else{
                            if($View[$td] == "datetime"){
                                echo "<td class=\"nowrap\">{$logs[$View['datetime']]}</td>";
                            }
                            else if($View[$td] == "url"){
                                echo "<td class=\"break\">".($logs['url'])."</td>";
                            }
                            else if($View[$td] == "size"){
                                echo "<td>".call_user_func(["Functions", 'convertSize'], $logs['size'])."</td>";
                            }
                            else{
                                echo "<td>{$logs[$View[$td]]}</td>";
                            }
                        }
                    }
                echo "</tr>";
                }
                echo "
                        </tbody>
                    </table>
                    ";
    }
    protected function generatePDF(){
    ?>
        <div class="modal fade bs-export-pdf" tabindex="-1" role="dialog" aria-labelledby="myLargeModalLabel">
            <div class="modal-dialog modal-lg">
                <div class="modal-content">
                    <form id="export-to-pdf" class="form-horizontal">
                        <div class="modal-header">
                          <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">×</span></button>
                          <h4 class="modal-title text-primary" id="myLargeModalLabel">Exportar este filtro para PDF</h4>
                        </div>
                        <div class="modal-body" style="padding: 15px;">
                            <fieldset class="scheduler-border"><h4 class="text-info">O que voc&ecirc; deseja filtrar  </h4>
                                <table class="table" id="showFilter">
                                    <thead><tr></tr></thead>
                                    <tbody><tr></tr></tbody>
                                </table>
                            </fieldset>
                            <fieldset class="scheduler-border" id="fieldview"><h4 class="text-info">O que você deseja visualizar no PDF?</h4>
                                <div class="form-group" style="padding-left: 20px;">
                                    <div class="col-sm-2">
                                        <label class="control-label text-muted"><input type="checkbox" value="datetime" name="cdatetime" id="cdatetime" checked/>&nbsp;Data/Hora</label>
                                    </div>
                                    <div class="col-sm-2">
                                        <label class="control-label text-muted"><input type="checkbox" value="ipuser" name="cipuser" id="cipuser" checked/>&nbsp;IP</label>
                                    </div>
                                    <div class="col-sm-2">
                                        <label class="control-label text-muted"><input type="checkbox" value="macaddress" name="cmacaddress" id="cmacaddress"/>&nbsp;MAC Address</label>
                                    </div>
                                    <div class="col-sm-2">
                                        <label class="control-label text-muted"><input type="checkbox" value="username" name="username" id="cusername"/>&nbsp;Usu&aacute;rio</label>
                                    </div>
                                    <div class="col-sm-2">
                                        <label class="control-label text-muted"><input type="checkbox" value="destination" name="destination" id="cdestination" checked/>&nbsp;Destino</label>
                                    </div>
                                    <div class="col-sm-2">
                                        <label class="control-label text-muted"><input type="checkbox" value="url" name="curl" id="curl" checked/>&nbsp;URL</label>
                                    </div>
                                    <div class="col-sm-2">
                                        <label class="control-label text-muted"><input type="checkbox" value="ipdest" name="cipdest" id="cipdest"/>&nbsp;IP Destino</label>
                                    </div>
                                    <div class="col-sm-2">
                                        <label class="control-label text-muted"><input type="checkbox" value="mime" name="cmime" id="cmime" checked/>&nbsp;Tipo de Arquivo</label>
                                    </div>
                                    <div class="col-sm-2">
                                        <label class="control-label text-muted"><input type="checkbox" value="size" name="csize" id="csize" checked/>&nbsp;Tamanho</label>
                                    </div>
                                    <div class="col-sm-2">
                                        <label class="control-label text-muted"><input type="checkbox" value="status" name="cstatus" id="cstatus" checked/>&nbsp;Status</label>
                                    </div>
                                </div>
                            </fieldset>
                            <fieldset class="scheduler-border"><h4 class="text-info">Configurar PDF</h4>
                                <div style="padding-left: 20px;">
                                    <div class="form-group col-sm-5">
                                        <div class="input-group">
                                            <span class="input-group-addon">Formato</span>
                                            <select name="format" id="format" class="form-control">
                                                <option value="4A0">4A0</option>
                                                <option value="">2A0</option>
                                                <option value="2A0">A0</option>
                                                <option value="A1">A1</option>
                                                <option value="A2">A2</option>
                                                <option value="A3">A3</option>
                                                <option value="A4" selected>A4</option>
                                                <option value="A5">A5</option>
                                                <option value="A6">A6</option>
                                                <option value="A7">A7</option>
                                                <option value="A8">A8</option>
                                                <option value="A9">A9</option>
                                                <option value="A10">A10</option>
                                                <option value="B0">B0</option>
                                                <option value="B1">B1</option>
                                                <option value="B2">B2</option>
                                                <option value="B3">B3</option>
                                                <option value="B4">B4</option>
                                                <option value="B5">B5</option>
                                                <option value="B6">B6</option>
                                                <option value="B7">B7</option>
                                                <option value="B8">B8</option>
                                                <option value="B9">B9</option>
                                                <option value="B10">B10</option>
                                                <option value="C0">C0</option>
                                                <option value="C1">C1</option>
                                                <option value="C2">C2</option>
                                                <option value="C3">C3</option>
                                                <option value="C4">C4</option>
                                                <option value="C5">C5</option>
                                                <option value="C6">C6</option>
                                                <option value="C7">C7</option>
                                                <option value="C8">C8</option>
                                                <option value="C9">C9</option>
                                                <option value="C10">C10</option>
                                                <option value="RA0">RA0</option>
                                                <option value="RA1">RA1</option>
                                                <option value="RA2">RA2</option>
                                                <option value="RA3">RA3</option>
                                                <option value="RA4">RA4</option>
                                                <option value="SRA0">SRA0</option>
                                                <option value="SRA1">SRA1</option>
                                                <option value="SRA2">SRA2</option>
                                                <option value="SRA3">SRA3</option>
                                                <option value="SRA4">SRA4</option>
                                                <option value="LETTER">LETTER</option>
                                                <option value="LEGAL">LEGAL</option>
                                                <option value="EXECUTIVE">EXECUTIVE</option>
                                                <option value="FOLIO">FOLIO</option>
                                                <option value="DEMY">DEMY</option>
                                                <option value="ROYAL">ROYAL</option>
                                            </select>
                                        </div>
                                    </div>
                                    <div class="form-group col-sm-5">
                                        <div class="input-group" style="padding-left: 20px;">
                                            <span class="input-group-addon">Orientation</span>
                                            <span class="input-group-addon">
                                                <label style="padding-left: 20px;padding-top: 5px">
                                                    <input type="radio" value="-L" name="portrait" id="portrait" checked />
                                                    &nbsp;Paisagem
                                                </label>
                                                <label style="padding-left: 10px;padding-top: 5px">
                                                    <input type="radio" value="" name="portrait" id="portrait" />
                                                    &nbsp;Retrato
                                                </label>
                                            </span>
                                        </div>
                                    </div>
                                    <div class="form-group col-sm-5">
                                        <div class="input-group">
                                            <span class="input-group-addon" id="basic-addon1">Nome</span>
                                            <input type="text" class="form-control" name="pdfname" id="pdfname" />
                                            <span class="input-group-addon">.pdf</span>
                                        </div>
                                    </div>
                                    <div class="form-group col-sm-7">
                                        <span class="text-danger" style="padding-left: 20px;">*n&atilde;o use espa&ccedil;o, caracteres especiais ou n&uacute;meros no nome do arquivo</span>
                                    </div>
                                </div>
                            </fieldset>
                        </div>
                        <div class="modal-footer">
                            <button class="btn btn-primary" name="generate-pdf" id="generate-pdf"><span class="glyphicon glyphicon-ok"></span>&nbsp;Gerar PDF</button>
                            <span id="area-download" class="area-download">
                                <a href="" id="btn-download" class="btn btn-default" target="_blank">Download</a>
                                <button class="btn btn-default" data-file="teste" id="deleteFile">Remover</button>
                            </span>
                        </div>
                    </form>
                </div>
            </div>
        </div>
    <?php
    }
    protected function generateCSV(){
    ?>
        <div class="modal fade bs-export-csv" tabindex="-1" role="dialog" aria-labelledby="myLargeModalLabel">
            <div class="modal-dialog modal-lg">
                <div class="modal-content">
                    <form id="export-to-csv" class="form-horizontal">
                        <div class="modal-header">
                            <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">×</span></button>
                            <h4 class="modal-title text-primary" id="myLargeModalLabel">Exportar este filtro para CSV</h4>
                        </div>
                        <div class="modal-body" style="padding: 15px;">
                            <fieldset class="scheduler-border"><h4 class="text-info">O que voc&ecirc; deseja filtrar  </h4>
                                <table class="table" id="showFilterCSV">
                                    <thead><tr></tr></thead>
                                    <tbody><tr></tr></tbody>
                                </table>
                            </fieldset>
                            <fieldset class="scheduler-border" id="fieldviewCSV"><h4 class="text-info">O que você deseja visualizar no CSV?</h4>
                                <div class="form-group" style="padding-left: 20px;">
                                    <div class="col-sm-2">
                                        <label class="control-label text-muted"><input type="checkbox" value="datetime" name="csvdatetime" id="csvdatetime" checked/>&nbsp;Data/Hora</label>
                                    </div>
                                    <div class="col-sm-2">
                                        <label class="control-label text-muted"><input type="checkbox" value="ipuser" name="csvipuser" id="csvipuser" checked/>&nbsp;IP</label>
                                    </div>
                                    <div class="col-sm-2">
                                        <label class="control-label text-muted"><input type="checkbox" value="macaddress" name="csvcmacaddress" id="csvmacaddress"/>&nbsp;MAC Address</label>
                                    </div>
                                    <div class="col-sm-2">
                                        <label class="control-label text-muted"><input type="checkbox" value="username" name="csvusername" id="csvusername"/>&nbsp;Usu&&aacute;rio</label>
                                    </div>
                                    <div class="col-sm-2">
                                        <label class="control-label text-muted"><input type="checkbox" value="destination" name="csvdestination" id="csvdestination" checked/>&nbsp;Destino</label>
                                    </div>
                                    <div class="col-sm-2">
                                        <label class="control-label text-muted"><input type="checkbox" value="url" name="csvurl" id="csvurl" checked/>&nbsp;URL</label>
                                    </div>
                                    <div class="col-sm-2">
                                        <label class="control-label text-muted"><input type="checkbox" value="ipdest" name="csvipdest" id="csvipdest"/>&nbsp;IP Destino</label>
                                    </div>
                                    <div class="col-sm-2">
                                        <label class="control-label text-muted"><input type="checkbox" value="mime" name="csvmime" id="csvmime" checked/>&nbsp;Tipo de arquivo</label>
                                    </div>
                                    <div class="col-sm-2">
                                        <label class="control-label text-muted"><input type="checkbox" value="size" name="csvsize" id="csvsize" checked/>&nbsp;Tamanho</label>
                                    </div>
                                    <div class="col-sm-2">
                                        <label class="control-label text-muted"><input type="checkbox" value="status" name="csvstatus" id="csvstatus" checked/>&nbsp;Status</label>
                                    </div>
                                </div>
                            </fieldset>
                            <fieldset class="scheduler-border"><h4 class="text-info">Configurar CSV</h4>
                                <div style="padding-left: 20px;">
                                    <div class="form-group col-sm-5">
                                        <div class="input-group">
                                            <span class="input-group-addon" id="basic-addon1">Name</span>
                                            <input type="text" class="form-control" name="csvname" id="csvname" />
                                            <span class="input-group-addon">.csv</span>
                                        </div>
                                    </div>
                                    <div class="form-group col-sm-7">
                                        <span class="text-danger" style="padding-left: 20px;">*n&atilde;o use espa&ccedil;o, caracteres especiais ou n&uacute;meros no nome do arquivo</span>
                                    </div>
                                </div>
                            </fieldset>
                        </div>
                        <div class="modal-footer">
                            <button class="btn btn-primary" name="generate-csv" id="generate-csv"><span class="glyphicon glyphicon-ok"></span>&nbsp;Gerar CSV</button>
                            <span id="area-downloadCSV" class="area-download">
                                <a href="" id="btn-downloadCSV" class="btn btn-default" target="_blank">Download</a>
                                <button class="btn btn-default" data-file="teste" id="deleteFileCSV">Remover</button>
                            </span>
                        </div>
                    </form>
                </div>
            </div>
        </div>
    <?php
    }
    protected function generateHTML(){
    ?>
        <div class="modal fade bs-export-html" tabindex="-1" role="dialog" aria-labelledby="myLargeModalLabel">
            <div class="modal-dialog modal-lg">
                <div class="modal-content">
                    <form id="export-to-html" class="form-horizontal">
                    <div class="modal-header">
                        <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">×</span></button>
                        <h4 class="modal-title text-primary" id="myLargeModalLabel">Exportar este filtro para HTML</h4>
                    </div>
                        <div class="modal-body" style="padding: 15px">
                            <fieldset class="scheduler-border"><h4 class="text-info">O que voc&ecirc; deseja filtrar  </h4>
                                <table class="table" id="showFilterHTML">
                                    <thead><tr></tr></thead>
                                    <tbody><tr></tr></tbody>
                                </table>
                            </fieldset>
                            <fieldset class="scheduler-border" id="fieldviewHTML"><h4 class="text-info">O que você deseja visualizar no HTML?</h4>
                                <div class="form-group" style="padding-left: 20px;">
                                    <div class="col-sm-2">
                                        <label class="control-label text-muted"><input type="checkbox" value="datetime" name="htmldatetime" id="htmldatetime" checked/>&nbsp;Data/Hora</label>
                                    </div>
                                    <div class="col-sm-2">
                                        <label class="control-label text-muted"><input type="checkbox" value="ipuser" name="htmlipuser" id="htmlipuser" checked/>&nbsp;IP</label>
                                    </div>
                                    <div class="col-sm-2">
                                        <label class="control-label text-muted"><input type="checkbox" value="macaddress" name="htmlmacaddress" id="htmlmacaddress"/>&nbsp;MAC Address</label>
                                    </div>
                                    <div class="col-sm-2">
                                        <label class="control-label text-muted"><input type="checkbox" value="username" name="htmlusername" id="htmlusername"/>&nbsp;Usu&aacute;rio</label>
                                    </div>
                                    <div class="col-sm-2">
                                        <label class="control-label text-muted"><input type="checkbox" value="destination" name="htmldestination" id="htmldestination" checked/>&nbsp;Destino</label>
                                    </div>
                                    <div class="col-sm-2">
                                        <label class="control-label text-muted"><input type="checkbox" value="url" name="htmlurl" id="htmlurl" checked/>&nbsp;URL</label>
                                    </div>
                                    <div class="col-sm-2">
                                        <label class="control-label text-muted"><input type="checkbox" value="ipdest" name="htmlipdest" id="htmlipdest"/>&nbsp;IP Destino</label>
                                    </div>
                                    <div class="col-sm-2">
                                        <label class="control-label text-muted"><input type="checkbox" value="mime" name="htmlmime" id="htmlmime" checked/>&nbsp;Tipo de arquivo</label>
                                    </div>
                                    <div class="col-sm-2">
                                        <label class="control-label text-muted"><input type="checkbox" value="size" name="htmlsize" id="htmlsize" checked/>&nbsp;Tamanho</label>
                                    </div>
                                    <div class="col-sm-2">
                                        <label class="control-label text-muted"><input type="checkbox" value="status" name="htmlstatus" id="htmlstatus" checked/>&nbsp;Status</label>
                                    </div>
                                </div>
                            </fieldset>
                            <fieldset class="scheduler-border"><h4 class="text-info">Configurar HTML</h4>
                                <div style="padding-left: 20px;">
                                    <div class="form-group col-sm-5">
                                        <div class="input-group">
                                            <span class="input-group-addon" id="basic-addon1">Nome</span>
                                            <input type="text" class="form-control" name="htmlname" id="htmlname" />
                                            <span class="input-group-addon">.html</span>
                                        </div>
                                    </div>
                                    <div class="form-group col-sm-7">
                                        <span class="text-danger" style="padding-left: 20px;">*n&atilde;o use espa&ccedil;o, caracteres especiais ou n&uacute;meros no nome do arquivo</span>
                                    </div>
                                </div>
                            </fieldset>
                        </div>
                        <div class="modal-footer">
                            <button class="btn btn-primary" name="generate-html" id="generate-html"><span class="glyphicon glyphicon-ok"></span>&nbsp;Gerar HTML</button>
                            <span id="area-downloadHTML" class="area-download">
                                <a href="" id="btn-downloadHTML" class="btn btn-default" target="_blank">Download</a>
                                <button class="btn btn-default" data-file="teste" id="deleteFileHTML">Remover</button>
                            </span>
                        </div>
                    </form>
                </div>
            </div>
        </div>
    <?php
    }
    public function exportsMod(){
        logsquid::generatePDF();
        logsquid::generateCSV();
        logsquid::generateHTML();
    }
    /* End Filters Module - Export */

    /* Start Functions Extras */
    public function statusReturn($cod){
        $Cod = explode("/", $cod);
        //if($Cod[0] == "TCP_MISS" or $Cod[0] == "TCP_MEM_HIT" or $Cod[0] == "TCP_DENIED" or $Cod[0] == "TCP_REFRESH_MODIFIED" or $Cod[0] == "TCP_REFRESH_UNMODIFIED" or $Cod[0] == "TCP_REFRESH_UNMODIFIED"){
            if($Cod[1] == 200){$return = "permitido";}
            else if($Cod[1] == 201){$return = "permitido";}
            else if($Cod[1] == 202){$return = "permitido";}
            else if($Cod[1] == 203){$return = "informa&ccedil;&otilde;es n&atilde;o autorizadas";}
            else if($Cod[1] == 204){$return = "sem conte&uacute;do";}
            else if($Cod[1] == 205){$return = "conte&uacute;do removido";}
            else if($Cod[1] == 206){$return = "conte&uacute;do parcial";}
            else if($Cod[1] == 302){$return = "permitido";}
            else if($Cod[1] == 304){$return = "permitido";}
            else if($Cod[1] == 401){$return = "n&atilde;o autorizado";}
            else if($Cod[1] == 403){$return = "negado";}
            else if($Cod[1] == 404){$return = "n&atilde;o encontrado";}
            else if($Cod[1] == 407){$return = "sem autentica&ccedil;&atilde;o";}
            else if($Cod[1] == 407){$return = "tempo esgotado";}
            else if($Cod[1] == 500){$return = "erro do servidor interno";}
            else if($Cod[1] == 502){$return = "gateway incorreto";}
            else if($Cod[1] == 503){$return = "servi&ccedil;o indispon&iacute;vel";}
            else if($Cod[1] == 504){$return = "tempo esgotado do gateway";}
            else if($Cod[1] == 505){$return = "Vers&atilde;o HTTP n&atilde;o suportada";}
            else if($Cod[1] == 600){$return = "resposta errada do cabe&ccedil;alho ";}
            else{$return = $Cod[1];}
        //}
        /*else if($Cod[0] == "TCP_MISS_ABORTED"){
            $return = "Abortado";
        }*/
        //else{$return = "{$cod}";}
        return $return;
        //return "{$status[$Cod[0]]}";
    }
    public function checkDB($db, $action){
        $dbs = mysql_list_dbs();
        while($dbLists = mysql_fetch_object($dbs)){
            $DBs[] = $dbLists->Database;
        }
        if(in_array($db, $DBs)){
            return $this->result = 1;
        }
        else{
            return $this->result = 0;
        }
    }
    public function tamFile($bytes) {
        if ($bytes >= 1073741824){
            $bytes = number_format($bytes / 1073741824, 2) . 'GB';
        }
        elseif ($bytes >= 1048576){
            $bytes = number_format($bytes / 1048576, 2) . 'MB';
        }
        elseif ($bytes >= 1024){
            $bytes = number_format($bytes / 1024, 2) . 'KB';
        }
        elseif ($bytes > 1){
            $bytes = $bytes . 'b';
        }
        elseif ($bytes == 1){
            $bytes = $bytes . 'b';
        }
        else{
            $bytes = '0b';
        }
        return $bytes;
    }
    /* End Functions Extras */
    public function __destruct() {
        parent::Desconect();
    }
}
