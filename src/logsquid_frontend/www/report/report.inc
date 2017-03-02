<?php
ini_set("memory_limit", "512M");
require_once("../functions/autoload.php");
class report extends logsquid {
    var $select;
    var $result;
    var $where;
    var $con;
    var $mime = array();
    var $band = array();
    var $total = array();
    
    public function __construct() {
        parent::__construct();
        /*
        $logSquidconf = new logSquidconf();
        $logSquidconf->readDataBase();
        $typelog = $logSquidconf->typelog;
        $this->con = new conectdb();
        $this->con->setData(trim($logSquidconf->hostname), trim($logSquidconf->username), trim($logSquidconf->password), trim($logSquidconf->database));
        $this->con->Conect();
        */
    }

    public function reportlogSquidData(){
        $where = $this->where;
        mysql_query("SET character_set_results = 'utf8', character_set_client = 'utf8', character_set_connection = 'utf8', character_set_database = 'utf8', character_set_server = 'utf8'");
        $this->select = "SELECT * FROM logSquid {$where} ORDER BY id DESC";
        $this->result = mysql_query($this->select);
        /*
        echo mysql_num_rows($this->result)."<br/>";
        echo memory_get_usage()."<br/>";
        echo memory_get_peak_usage()."<br/>";
         */
        while ($result = mysql_fetch_object($this->result)){
            $mime = explode("/", $result->mime);
            $this->returnTypeFile($mime[0],$mime[1]);
        }
        echo "<pre>";
        print_r($this->mime);
        echo memory_get_usage() . "<br/>";
        mysql_free_result($this->result);
        echo memory_get_usage() . "<br/>";
    }
    public function modalReport(){
    ?>
        <div class="modal fade bs-reportoptions" tabindex="-1" role="dialog" aria-labelledby="title-report">
            <div class="modal-dialog modal-lg">
                <div class="modal-content">
                    <div class="modal-header">
                        <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">×</span></button>
                        <h4 class="modal-title text-primary" id="title-report">Op&ccedil;&oti&otilde;es de Relat&&oacute;rio</h4>
                    </div>
                    <div class="modal-body" style="padding: 15px;">
                        <fieldset class="scheduler-border">
                            <h4 class="text-info">Gerar relatório a partir das seguintes op&ccedil;&oti&otilde;es</h4>
                            <div class="field-options">
                                <div class='input-group date' id='datestart'>
                                    <span class="input-group-addon calendar">
                                        <span class="glyphicon glyphicon-calendar"></span>
                                        of
                                    </span>
                                    <input type='text' class="form-control" id='fDatestart' value="<?php echo date("Y-m-d"); ?>" />
                                </div>
                            </div>
                            <div class="field-options">
                                <div class='input-group'>
                                    <span class="input-group-addon calendar">
                                        <span class="glyphicon glyphicon-time"></span>
                                        between
                                    </span>
                                    <input type='text' class="form-control" id='timestart' value="00:00:01" />
                                </div>
                            </div>
                            <div class="field-options">
                                <div class='input-group'>
                                    <span class="input-group-addon calendar">
                                        <span class="glyphicon glyphicon-time"></span>
                                        and
                                    </span>
                                    <input type='text' class="form-control" value="23:59:59" id='timeend' />
                                </div>
                            </div>
                            <div class="field-options">
                                <div class='input-group date' id='dateend'>
                                    <span class="input-group-addon calendar">
                                        <span class="glyphicon glyphicon-calendar"></span>
                                        to
                                    </span>
                                    <input type='text' class="form-control" id='fDateend' value="<?php echo date("Y-m-d"); ?>" />
                                </div>
                            </div>
                            <div class="input-group">
                                <div class="input-group-btn">
                                    <button class="btn btn-primary" data-label-placement>Choose one or more filter</button>
                                    <button class="btn btn-primary" data-toggle="dropdown">&nbsp;<span class="caret"></span>&nbsp;</button>
                                    <ul class="dropdown-menu">
                                        <li>
                                            <input type="radio" id="sitespip" name="typefilter" value="sitespip">
                                            <label for="sitespip">Sites por IP</label>
                                        </li>
                                        <li>
                                            <input type="radio" id="sitespuser" name="typefilter" value="sitespuser">
                                            <label for="sitespuser">Sites por Usu&aacute;rio</label>
                                        </li>
                                        <li>
                                            <input type="radio" id="urlpip" name="typefilter" value="urlpip">
                                            <label for="urlpip">URL's por IP</label>
                                        </li>
                                        <li>
                                            <input type="radio" id="urlpusername" name="typefilter" value="urlpusername">
                                            <label for="urlpusername">URL's por Usu&aacute;rio</label>
                                        </li>
                                        <li>
                                            <input type="radio" id="accesspip" name="typefilter" value="accesspip">
                                            <label for="accesspip">Acessos por IP</label>
                                        </li>
                                        <li>
                                            <input type="radio" id="accesspusername" name="typefilter" value="accesspusername">
                                            <label for="accesspusername">Acessos por Usu&aacute;rio</label>
                                        </li>
                                        <li>
                                            <input type="radio" id="deniedpip" name="typefilter" value="deniedpip" >
                                            <label for="deniedpip">Acessos negado por IP</label>
                                        </li>
                                        <li>
                                            <input type="radio" id="deniedpusername" name="typefilter" value="deniedpusername" >
                                            <label for="deniedpusername">Acessos negados por Usu&aacute;rio</label>
                                        </li>
                                    </ul>
                                </div>
                                <input type="text" class="form-control " id='fieldreport' />
                                <span class="input-group-addon calendar" id='bt-report'>
                                    <span class="glyphicon glyphicon-search"></span>
                                </span>
                            </div>
                            <?php /*
                            <div class="input-group">
                                <div class="input-group-btn">
                                    <button class="btn btn-primary" data-toggle="dropdown">choose an option for the report&nbsp;<span class="caret"></span>&nbsp;</button>
                                    <ul class="dropdown-menu">
                                        <li>
                                            <input type="radio" id="ip" name="typereport" value="ipuser" />
                                            <label for="ip">IP User</label>
                                        </li>
                                        <li>
                                            <input type="radio" id="user" name="typereport" value="user" />
                                            <label for="user">Username</label>
                                        </li>
                                        <li>
                                            <input type="radio" id="url-sites" name="typereport" value="url" />
                                            <label for="url-sites">Sites</label>
                                        </li>
                                        <li>
                                            <input type="radio" id="type-files" name="typereport" value="mime" />
                                            <label for="type-files">Type Files</label>
                                        </li>
                                        <li>
                                            <input type="radio" id="action" name="typereport" value="action" />
                                            <label for="action">Status</label>
                                        </li>
                                        
                                        <li>
                                            <input type="radio" id="downloads" name="typereport" value="downloads" />
                                            <label for="downloads">Downloads</label>
                                        </li>
                                    </ul>
                                </div>
                                <input type="text" class="form-control " id='fieldfilter' />
                                <span class="input-group-addon calendar" id='bt-filter'>
                                    <span class="glyphicon glyphicon-search"></span>
                                </span>
                            </div>
                            <div class="input-group">
                                <div class="input-group-btn">
                                    <button class="btn btn-primary" data-label-placement>choose an option for the report</button>
                                    <button class="btn btn-primary" data-toggle="dropdown">&nbsp;<span class="caret"></span>&nbsp;</button>
                                    <ul class="dropdown-menu">
                                        <li>
                                            <input type="radio" id="ipuser" name="typereport" value="ipuser">
                                            <label for="ipuser">IP</label>
                                        </li>
                                        <li>
                                            <input type="radio" id="user" name="typereport" value="user">
                                            <label for="user">Username</label>
                                        </li>
                                        <li>
                                            <input type="radio" id="url" name="typereport" value="url">
                                            <label for="url">Sites</label>
                                        </li>
                                        <li>
                                            <input type="radio" id="action" name="typereport" value="action" >
                                            <label for="action">Status</label>
                                        </li>
                                        <li>
                                            <input type="radio" id="mime" name="typereport" value="mime" >
                                            <label for="mime">Mime</label>
                                        </li>
                                        <li>
                                            <input type="radio" id="downloads" name="typereport" value="downloads" >
                                            <label for="downloads">Downloads</label>
                                        </li>
                                    </ul>
                                </div>
                                <input type="text" class="form-control " id='fieldfilter' />
                                <span class="input-group-addon calendar" id='bt-filter'>
                                    <span class="glyphicon glyphicon-search"></span>
                                </span>
                            </div>*/?>
                            
                        </fieldset>
                            
                        
                    </div>
                    <div class="modal-footer">
                        <button type="button" class="btn btn-default" data-dismiss="modal">Close</button>
                    </div>
                </div>
            </div>
        </div>
    <?php
    }
    protected function returnTypeFile($type,$file){
        if(array_key_exists($type, $this->mime)){
            $this->mime[$type][$file] = $this->mime[$type][$file] + 1;
        }
        else{
            $this->mime[$type][$file] = 1;
        }
    }
    public function Dashboard($my){
        $date = explode("-", $my);
        $path = "details";
        $dir = dir($path);
        $count = count(glob("{$path}/*.{$my}"));
        
        if($count != 0){
            foreach(glob("{$path}/*.{$my}") as $file){
                echo $this->getDashboard($file);
            }
        }
        else{
            if(count($date) == 3){
                echo "
                    <div class=\"info-generate-report bg-warning\">
                        <h3 class=\"text-warning\" style=\"text-align: center;\">
                            <span class=\"glyphicon glyphicon-alert\" aria-hidden=\"true\"></span>&nbsp;
                            Nenhum relatório foi encontrado para este dia. Deseja gerar agora?
                        </h3>
                        <p style=\"text-align: center;\" id=\"area-bt-generate\">
                            <button type=\"button\" class=\"btn btn-primary\" id=\"generate-report-msg\">Gerar agora</button>
                        </p>
                        <br/>
                        <p class=\"text-muted\">
                            Nota: Se você já gerou relatório para este dia, não se esqueça de limpar o cache do seu navegador. ( CTRL / SHIFT + F5)
                        </p>
                    </div>
                ";
                return;
            }
            elseif(count($date) == 2){
                echo "
                    <div class=\"info-generate-report bg-warning\">
                        <h3 class=\"text-warning\" style=\"text-align: center;\">
                            <span class=\"glyphicon glyphicon-alert\" aria-hidden=\"true\"></span>&nbsp;
                            Nenhum relatório foi encontrado para este dia. Deseja gerar agora?
                        </h3>
                        <h4 class=\"text-danger\" style=\"text-align: center;\">
                            Para gerar o relatório mensal, certifique-se de que o Sistema Operacional não esteja com o consumo de memória e de processamento elevado.
                        </h4>
                        <p style=\"text-align: center;\" id=\"area-bt-generate\">
                            <button type=\"button\" class=\"btn btn-primary\" id=\"generate-report-msg\">Gerar agora</button>
                        </p>
                        <br/>
                        <p class=\"text-muted\">
                            Nota: Se você já gerou relatório para este dia, não se esqueça de limpar o cache do seu navegador. ( CTRL / SHIFT + F5)
                        </p>
                    </div>
                ";
                return;
            }
        }
    }
    
    public function getDashboard($file){
        $typereport = explode(".", explode("/", $file)[1]);
        $return = "";

        if($typereport[0] == "accesssites"){
            $return .= "<div class='box-dashboard'><table class='table table-striped' id='accesssites'>";
            $return .= "<tr><th>Sites acessados por IP e Usu&aacute;rio</th>";
            $return .= "<th class='area-bt-report' colspan='2'>
                        <div class='bt-dashboard'><a class='icon-graph' data-toggle='modal' data-info='Top sites acessados' data-target='.dashboard-graph' id='accesssites' href='#'></a></div>
                        <div class='bt-dashboard'><a class='glyphicon glyphicon-plus' href='?d={$typereport[1]}&detail=accesssites'></a></div>
                    </th></tr>";
            $gfile = file($file);
            unset($this->total);
            for ($i = 0; $i < count($gfile); $i++){
                $return .= $this->getLineDashboard($gfile[$i], $typereport[0], $i);
            }
            (isset($this->total))? $total = array_sum($this->total): $total = 0;
            $return .= "<tr><th colspan='2'>Total</th><th style='text-align: right'>{$total}</th></tr>";
            $return .= "</table></div>";
        }
        
        if($typereport[0] == "deniedsites"){
            $return .= "<div class='box-dashboard'><table class='table table-striped' id='deniedsites'>";
            $return .= "<tr><th>Sites negados por IP e Usu&aacute;rio</th><th class='area-bt-report' colspan='2'><div class='bt-dashboard'><a class='icon-graph' data-toggle='modal' data-info='Top sites negados' data-target='.dashboard-graph' id='deniedsites' href='#'></a></div><div class='bt-dashboard'><a class='glyphicon glyphicon-plus' href='?d={$typereport[1]}&detail=deniedsites'></a></div></th></tr>";
            $gfile = file($file);
            unset($this->total);
            for ($i = 0; $i < count($gfile); $i++){
                $return .= $this->getLineDashboard($gfile[$i], $typereport[0], $i);
            }
            (isset($this->total))?$total = array_sum($this->total):$total = "";
            $return .= "<tr><th colspan='2'>Total</th><th style='text-align: right'>{$total}</th></tr>";
            $return .= "</table></div>";
        }
        
        if($typereport[0] == "accessurl"){
            $return .= "<div class='box-dashboard'><table class='table table-striped' id='accessurl'>";
            $return .= "<tr><th>URL's acessados por IP e Usu&aacute;rio</th>
                        <th class='area-bt-report' colspan='2'>
                        <div class='bt-dashboard'><a class='icon-graph' data-toggle='modal' data-info=\"Top URL's acessados\" data-target='.dashboard-graph' id='accessurl' href='#'></a></div>
                        <div class='bt-dashboard'><a class='glyphicon glyphicon-plus' href='?d={$typereport[1]}&detail=accessurl'></a></div>
                    </th></tr>";
            $gfile = file($file);
            unset($this->total);
            for ($i = 0; $i < count($gfile); $i++){
                $return .= $this->getLineDashboard($gfile[$i], $typereport[0], $i);
            }
            (isset($this->total))? $total = array_sum($this->total): $total = 0;
            $return .= "<tr><th colspan='2'>Total</td><th style='text-align: right'>{$total}</th></tr>";
            $return .= "</table></div>";
        }
        
        if($typereport[0] == "deniedurl"){
            $return .= "<div class='box-dashboard'><table class='table table-striped' id='deniedurl'>";
            $return .= "<tr><th>URL's negados por IP e Usu&aacute;rio</th>
                        <th class='area-bt-report' colspan='2'>
                        <div class='bt-dashboard'><a class='icon-graph' data-toggle='modal' data-info=\"Top URL's negados\" data-target='.dashboard-graph' id='deniedurl' href='#'></a></div>
                        <div class='bt-dashboard'><a class='glyphicon glyphicon-plus' href='?d={$typereport[1]}&detail=deniedurl'></a></div>
                    </th></tr>";
            $gfile = file($file);
            unset($this->total);
            for ($i = 0; $i < count($gfile); $i++){
                $return .= $this->getLineDashboard($gfile[$i], $typereport[0], $i);
            }
            (isset($this->total))?$total = array_sum($this->total):$total = "";
            $return .= "<tr><th colspan='2'>Total</th><th style='text-align: right'>{$total}</th></tr>";
            $return .= "</table></div>";
        }
        if($typereport[0] == "adownloads"){
            $return .= "<div class='box-dashboard'><table class='table table-striped' id='adownloads'>";
            $return .= "<tr><th colspan='2'>Downloads por IP e Usu&aacute;rio</th><th class='area-bt-report' colspan='2'>
                        <div class='bt-dashboard'><a class='icon-graph' data-toggle='modal' data-info=\"Download IP ou Usu&aacute;rio\" data-target='.dashboard-graph' id='adownloads' href='#'></a></div>
                        <div class='bt-dashboard'><a class='glyphicon glyphicon-plus' href='?d={$typereport[1]}&detail=adownloads'></a></div>
                    </th></tr>";
            $gfile = file($file);
            unset($this->total);
            for ($i = 0; $i < count($gfile); $i++){
                $return .= $this->getLineDashboard($gfile[$i], $typereport[0], $i);
            }
            (isset($this->total['size']))? $size = array_sum($this->total['size']): $size = 0;
            (isset($this->total['total']))? $total = array_sum($this->total['total']): $total = 0;
            $return .= "<tr><th colspan='2'>Total</th><th style='text-align: right;'>{$total}</th><th style='text-align: right;color: ".call_user_func(['Functions', 'getColorTamFile'], call_user_func(['Functions', 'convertSize'], $size))."'>".call_user_func(['Functions', 'convertSize'], $size)."</th></tr>";
            $return .= "</table></div>";
        }
        if($typereport[0] == "ddownloads"){
            $return .= "<div class='box-dashboard'><table class='table table-striped' id='ddownloads'>";
            $return .= "<tr><th colspan='2'>Downloads Negado por IP e Usu&aacute;rio</th><th class='area-bt-report' colspan='2'>
                        <div class='bt-dashboard'><a class='icon-graph' data-toggle='modal' data-info=\"Download Negado por IP ou Usu&aacute;rio\" data-target='.dashboard-graph' id='ddownloads' href='#'></a></div>
                        <div class='bt-dashboard'><a class='glyphicon glyphicon-plus' href='?d={$typereport[1]}&detail=ddownloads'></a></div>
                    </th></tr>";
            $gfile = file($file);
            unset($this->total);
            for ($i = 0; $i < count($gfile); $i++){
                $return .= $this->getLineDashboard($gfile[$i], $typereport[0], $i);
            }
            (isset($this->total['size']))? $size = array_sum($this->total['size']): $size = 0;
            (isset($this->total['total']))? $total = array_sum($this->total['total']): $total = 0;
            $return .= "<tr><th colspan='2'>Total</th><th style='text-align: right;'>{$total}</th><th style='text-align: right;color: ".call_user_func(['Functions', 'getColorTamFile'], call_user_func(['Functions', 'convertSize'], $size))."'>".call_user_func(['Functions', 'convertSize'], $size)."</th></tr>";
            $return .= "</table></div>";
        }
        if($typereport[0] == "aipuser"){
            $return .= "<div class='box-dashboard'><table class='table table-striped' id='aipuser'>";
            $return .= "<tr><th colspan='2'>Acessos por IP</th><th class='area-bt-report' colspan='2'>
                        <div class='bt-dashboard'><a class='icon-graph' data-toggle='modal' data-info=\"Acessos por IP/Consumo por IP\" data-target='.dashboard-graph' id='aipuser' href='#'></a></div>
                        <div class='bt-dashboard'><a class='glyphicon glyphicon-plus' href='?d={$typereport[1]}&detail=aipuser'></a></div>
                    </th></tr>";
            $gfile = file($file);
            unset($this->total);
            for ($i = 0; $i < count($gfile); $i++){
                $return .= $this->getLineDashboard($gfile[$i], $typereport[0], $i);
            }
            (isset($this->total['size']))? $size = array_sum($this->total['size']): $size = 0;
            (isset($this->total))? $total = array_sum($this->total['total']): $total = 0;
            $return .= "<tr><th colspan='2'>Total</th><th style='text-align: right;'>{$total}</th><th style='text-align: right;color: ".call_user_func(['Functions', 'getColorTamFile'], call_user_func(['Functions', 'convertSize'], $size))."'>".call_user_func(['Functions', 'convertSize'], $size)."</th></tr>";
            $return .= "</table></div>";
        }
        if($typereport[0] == "dipuser"){
            $return .= "<div class='box-dashboard'><table class='table table-striped' id='dipuser'>";
            $return .= "<tr><th colspan='2'>Negados por IP</th><th class='area-bt-report' colspan='2'>
                        <div class='bt-dashboard'><a class='icon-graph' data-toggle='modal' data-info=\"Negados por IP\" data-target='.dashboard-graph' id='dipuser' href='#'></a></div>
                        <div class='bt-dashboard'><a class='glyphicon glyphicon-plus' href='?d={$typereport[1]}&detail=dipuser'></a></div>
                    </th></tr>";
            $gfile = file($file);
            for ($i = 0; $i < count($gfile); $i++){
                $return .= $this->getLineDashboard($gfile[$i], $typereport[0], $i);
            }
            (isset($this->total))? $total = array_sum($this->total): $total = 0;
            $return .= "<tr><th colspan='3'>Total</th><th style='text-align: right'>{$total}</th></tr>";
            $return .= "</table></div>";
        }
        if($typereport[0] == "ausername"){
            $return .= "<div class='box-dashboard'><table class='table table-striped' id='ausername'>";
            $return .= "<tr><th colspan='2'>Acessos por Usu&aacute;rio</th><th class='area-bt-report' colspan='2'>
                        <div class='bt-dashboard'><a class='icon-graph' data-toggle='modal' data-info=\"Acessos por Usu&aacute;rio/Consumo por Usu&aacute;rio\" data-target='.dashboard-graph' id='ausername' href='#'></a></div>
                        <div class='bt-dashboard'><a class='glyphicon glyphicon-plus' href='?d={$typereport[1]}&detail=ausername'></a></div>
                    </th></tr>";
            $gfile = file($file);
            unset($this->total);
            for ($i = 0; $i < count($gfile); $i++){
                $return .= $this->getLineDashboard($gfile[$i], $typereport[0], $i);
            }
            (isset($this->total['size']))? $size = array_sum($this->total['size']): $size = 0;
            (isset($this->total))? $total = array_sum($this->total['total']): $total = 0;
            $return .= "<tr><th colspan='2'>Total</th><th style='text-align: right;'>{$total}</th><th style='text-align: right;color: ".call_user_func(['Functions', 'getColorTamFile'], call_user_func(['Functions', 'convertSize'], $size))."'>".call_user_func(['Functions', 'convertSize'], $size)."</th></tr>";
            $return .= "</table></div>";
        }
        if($typereport[0] == "dusername"){
            $return .= "<div class='box-dashboard'><table class='table table-striped' id='dusername'>";
            $return .= "<tr><th colspan='2'>Negados por Usu&aacute;rio</th><th class='area-bt-report' colspan='2'>
                        <div class='bt-dashboard'><a class='icon-graph' data-toggle='modal' data-info=\"Negados por Usu&aacute;rio\" data-target='.dashboard-graph' id='dusername' href='#'></a></div>
                        <div class='bt-dashboard'><a class='glyphicon glyphicon-plus' href='?d={$typereport[1]}&detail=dusername'></a></div>
                    </th></tr>";
            $gfile = file($file);
            for ($i = 0; $i < count($gfile); $i++){
                $return .= $this->getLineDashboard($gfile[$i], $typereport[0], $i);
            }
            (isset($this->total))? $total = array_sum($this->total): $total = 0;
            $return .= "<tr><th colspan='3'>Total</th><th style='text-align: right'>{$total}</th></tr>";
            $return .= "</table></div>";
        }
        if($typereport[0] == "mime"){
            unset($this->total);
            $return .= "<div class='box-dashboard'><table class='table table-striped' id='mime'>";
            $return .= "<tr><th colspan='2'>Consumo de Banda</th><th class='area-bt-report' colspan='2'>
                        <div class='bt-dashboard'><a class='icon-graph' data-toggle='modal' data-info=\"Acessos por Tipo de Arquivo/Consumo de Banda\" data-target='.dashboard-graph' id='mime' href='#'></a></div>
                        <div class='bt-dashboard'><a class='glyphicon glyphicon-plus' href='?d={$typereport[1]}&detail=mime'></a></div>
                    </th></tr>";
            $gfile = file($file);
            (count($gfile) < 10? $mline = count($gfile) : $mline = 10);
            for ($i = 0; $i < count($gfile); $i++){
                $return .= $this->getLineDashboard($gfile[$i], $typereport[0], $i);
            }
            (isset($this->total['size']))? $size = array_sum($this->total['size']): $size = 0;
            (isset($this->total))? $total = array_sum($this->total['total']): $total = 0;
            $return .= "<tr><th colspan='2'>Consumo Total</th><th style='text-align: right;'>{$total}</th><th style='text-align: right;color: ".call_user_func(['Functions', 'getColorTamFile'], call_user_func(['Functions', 'convertSize'], $size))."'>".call_user_func(['Functions', 'convertSize'], $size)."</th></tr>";
            $return .= "</table></div>";
        }
        return $return;
    }

    protected function getLineDashboard($gline, $typereport, $li = null){
        $return = "";
        if($typereport == "accesssites" || $typereport == "deniedsites"){
            $line = explode(" | ", $gline);
            $this->total[] = $line[0];
            if($li < 10){
                $return .= "<tr><td colspan='2' class='break' style='color: #337ab7;'>{$line[1]}</td><td style='text-align: right'>{$line[0]}</td></tr>";
            }
        }
        if($typereport == "accessurl" || $typereport == "deniedurl"){
            $line = explode(" | ", $gline);
            $this->total[] = $line[0];
            if($li < 10){
                $return .= "<tr><td colspan='2' class='break' style='color: #337ab7;'>{$line[1]}</td><td style='text-align: right'>{$line[0]}</td></tr>";
            }
        }
        if($typereport == "adownloads" || $typereport == "ddownloads"){
            $line = explode(" | ", $gline);
            /*echo "<pre>";
            echo "{$line[2]} - {$line[1]} {$line[0]}<br/>";
            echo "</pre>";*/
            (isset($line[0]))? $totalsize = $line[0]: $totalsize = 0;
            (isset($line[0]))? $this->total['size'][] = $line[0]: $this->total['size'][] = "";
            (isset($line[1]))? $this->total['total'][] = $line[1]: $this->total['total'][] = "";
            if($li < 10){
                $return .= "<tr><td colspan='2' class='break' style='color: #337ab7;'>{$line[2]}</td>";
                $return .= "<td style='text-align: right'>{$line[1]}</td>";
                $return .= "<td style='text-align: right;color: ".call_user_func(['Functions', 'getColorTamFile'], call_user_func(['Functions', 'convertSize'], $totalsize))."'>";
                if($totalsize) $return .= call_user_func(['Functions', 'convertSize'], $totalsize);
                $return .= "</td></tr>";
            }
        }
        if($typereport == "aipuser" || $typereport == "dipuser"){
            $line = explode(" | ", $gline);
            $getTotalSize = explode(" ", $line[0]);
            (isset($getTotalSize[0]))? $this->total['size'][] = $getTotalSize[0]: $this->total['size'][] = "";
            (isset($getTotalSize[0]))? $totalsize = $getTotalSize[0]: $totalsize = 0;
            $this->total['total'][] = $getTotalSize[1];
            if($li < 10){
                $return .= "<tr><td colspan='2' class='break' style='color: #337ab7;'>{$line[1]}</td>";
                $return .= "<td style='text-align: right'>{$getTotalSize[1]}</td>";
                $return .= "<td style='text-align: right;color: ".call_user_func(['Functions', 'getColorTamFile'], call_user_func(['Functions', 'convertSize'], $totalsize))."'>";
                if($totalsize) $return .= call_user_func(['Functions', 'convertSize'], $totalsize);
                $return .= "</td></tr>";
            }
        }
        if($typereport == "ausername" || $typereport == "dusername"){
            $line = explode(" | ", $gline);
            $getTotalSize = explode(" ", $line[0]);
            (isset($getTotalSize[0]))? $this->total['size'][] = $getTotalSize[0]: $this->total['size'][] = "";
            (isset($getTotalSize[0]))? $totalsize = $getTotalSize[0]: $totalsize = 0;
            $this->total['total'][] = $getTotalSize[1];
            if($li < 10){
                $return .= "<tr><td colspan='2' class='break' style='color: #337ab7;'>{$line[1]}</td>";
                $return .= "<td style='text-align: right'>{$getTotalSize[1]}</td>";
                $return .= "<td style='text-align: right;color: ".call_user_func(['Functions', 'getColorTamFile'], call_user_func(['Functions', 'convertSize'], $totalsize))."'>";
                if($totalsize) $return .= call_user_func(['Functions', 'convertSize'], $totalsize);
                $return .= "</td></tr>";
            }
        }
        if($typereport == "mime"){
            $line = explode(" \/ ", $gline);
            $mime = $line[0];
            unset($line[0]);
            foreach($line as $l){
                $type = explode("\\", explode(" | ", $l)[0]);
                $total[] = $type[1];
                $tamfile[] = $type[2];
            }
            $total = array_sum($total);
            $tamfile = array_sum($tamfile);
            $this->total['size'][] = $tamfile;
            $this->total['total'][] = $total;
            if($li < 10){
                $return .= "<tr><td colspan='2' class='break' style='color: #337ab7'>{$mime}</td><td style='text-align: right'>{$total}</td><td style='text-align: right;color: ".call_user_func(['Functions', 'getColorTamFile'], call_user_func(['Functions', 'convertSize'], $tamfile))."'>".call_user_func(['Functions', 'convertSize'], $tamfile)."</td></tr>";
            }
        }
        
        return $return;
    }


    public function getReports(){
        $report = array();
        $path = "details";
        $dir = dir($path);
        while ($file = $dir->read()){
            if($file == '.' or $file == '..'){}
            else {
                $f = explode(".", $file);
                $date = explode("-", $f[1]);
                if(isset($date[2])){
                    $report[$date[1]][$date[0]][$date[2]] = TRUE;
                }
            }
        }
        return $report;
    }
    public function getMonthReports(){
        $report = array();
        $path = "details";
        $dir = dir($path);
        while ($file = $dir->read()){
            if($file == '.' xor $file == '..'){}
            else {
                $f = explode(".", $file);
                $date = explode("-", $f[1]);
                if(!isset($date[2])){
                    $report[$date[1]][$date[0]] = TRUE;
                }
            }
        }
        return $report;
    }

    public function listDashboard($MY = NULL){
        $My = explode("-", $MY);
        ?>
        <a href="" id="monthYear" class="dropdown-toggle" data-toggle="dropdown" role="button" aria-haspopup="true" aria-expanded="false">
            <?php echo "{$this->showMonth($My[0])} {$My[1]}"; ?>
            <span class="caret"></span>
        </a>
        <ul class="dropdown-menu" aria-labelledby="monthYear">
            <?php
            
            $path = "dashboard";
            $dir = dir($path);
            $iMonthYear = array();
            while ($file = $dir->read()){
                if($file == '.' or $file == '..'){}
                else {
                    $f = explode(".", trim($file));
                    $my = explode("-", $f[1]);
                    $iMonthYear[$my[1]][$my[0]] = "";
                }
            }
            foreach ($iMonthYear as $y => $m){?>
            <li class="divider"></li>
            <li class="dropdown-submenu" style="padding: 0px 10px;">
                    <?php echo $y; ?>
                </li>
                <?php foreach ($m as $month => $v){?>
                <li>
                    <a href="?my=<?php echo "{$month}-{$y}"; ?>"><?php echo $this->showMonth($month); ?></a>
                </li>
                <?php
                }
            }
        ?></ul><?php
    }
    
    public function listDetails($file){
        if(file_exists("details/{$file}")){
            $details = file("details/{$file}");
            echo '<table class="table table-hover">';
            
            foreach ($details as $line => $detail){
                echo $this->getDetail($line +1, $detail, $file);
            }
            echo '</table>';
            if(ereg("mime", $file)){
                echo "<div class='total-bandwith'>Consumo de Banda <span style='color: ".call_user_func(['Functions', 'getColorTamFile'], call_user_func(['Functions', 'convertSize'], array_sum($this->band)))."'>".call_user_func(['Functions', 'convertSize'], array_sum($this->band))."</span></div>";
            }
        }
        else{
            echo "Arquivo nao encontrado";
        }
    }
    
    protected function getDetail($line, $detail, $type){
        $typerep = explode(".", $type);
        $det = explode(" | ", $detail);
        $index = $det[0];
        $link = $det[1];
        $return = "";
        $user = "";
        if($typerep[0] == "accesssites" || $typerep[0] == "deniedsites"){
            $ips = explode(" ", str_replace("ips: ", "", $det[2]));
            unset($ips[count($ips) -1]);
            $users = explode(" ", str_replace("users: ", "", $det[3]));
            unset($users[count($users) -1]);
            ($typerep[0] == "accesssites"? $d = "aipuser" : $d = "dipuser");
            $return .= "<tr style='cursor: pointer;' data-id='det{$line}'><td id='check'><input type='checkbox' value='{$line}' name='cline'/></td><td id='index'>{$line}</td><td style='color: #337ab7;'>{$link}</td><td style='text-align: right;'>{$index}</td></tr>";
            $return .= "<tr id='det{$line}' class='hide-det'><td colspan='4' class='space-td'><div class='details-box-inline'>";
            $return .= "<table class='table table-bordered table-striped'>";
            $return .= "<tr><td colspan='2' class='table-table-details' class='table-table-details'>IP</td></tr>";
            foreach($ips as $ip){
                $nip = str_replace(".", "", $ip);
                $return .= "<tr><td colspan='2'><a href='?d={$typerep[1]}&detail=aipuser&show={$nip}' target='blank'>{$ip}</a></td></tr>";
            }
            $return .= "</table></div>";
            $return .= "<div class='details-box-inline'><table class='table table-bordered table-striped'>";
            $return .= "<tr><td colspan='2' class='table-table-details'>Usu&aacute;rio</td></tr>";
            foreach ($users as $user){
                $nuser = str_replace(".", "", $user);
                $return .= "<tr><td colspan='2'><a href='?d={$typerep[1]}&detail={$d}&show={$nuser}' target='blank'>{$user}</a></td></tr>";
            }
            $return .= "</table>";
            $return .= "</div></td></tr>";
        }
        
        if($typerep[0] == "accessurl" || $typerep[0] == "deniedurl"){
            $ips = explode(" ", str_replace("ips: ", "", $det[2]));
            unset($ips[count($ips) -1]);
            $users = explode(" ", str_replace("users: ", "", $det[3]));
            unset($users[count($users) -1]);
            ($typerep[0] == "accessurl"? $d = "aipuser" : $d = "dipuser");
            /*
            echo "<pre>";
            echo "{$det[0]} {$det[1]} <br/>{$det[2]} {$det[3]}";
            echo "</pre>";
            */
            if($line < 10001){
                $return .= "<tr style='cursor: pointer;' data-id='det{$line}'><td id='check'><input type='checkbox' value='{$line}' name='cline'/></td><td id='index'>{$line}</td><td class='break' style='color: #337ab7;'>{$link}</td><td style='text-align: right'>{$index}</td></tr>";
                $return .= "<tr id='det{$line}' class='hide-det'><td colspan='4' class='space-td'><div class='details-box-inline'>";
                $return .= "<table class='table table-bordered table-striped'>";
                $return .= "<tr><td colspan='2' class='table-table-details'>IP</td></tr>";
                foreach ($ips as $ip){
                    $nip = str_replace(".", "", $ip);
                    $return .= "<tr><td colspan='2'><a href='?d={$typerep[1]}&detail={$d}&show={$nip}' target='blank'>{$ip}</a></td></tr>";
                }
                $return .= "</table></div>";
                $return .= "<div class='details-box-inline'><table class='table table-bordered table-striped'>";
                $return .= "<tr><td colspan='2' class='table-table-details'>Usu&aacute;rio</td></tr>";
                foreach ($users as $user){
                    $nuser = str_replace(".", "", $user);
                    $return .= "<tr><td colspan='2'><a href='?d={$typerep[1]}&detail={$d}&show={$nuser}' target='blank'>{$user}</a></td></tr>";
                }
                $return .= "</table>";
                $return .= "</div></td></tr>";
            }
        }
        
        if($typerep[0] == "adownloads" || $typerep[0] == "ddownloads"){
            /*echo "<pre>";
            echo "{$det[0]}, {$det[1]}, {$det[2]}, {$det[3]}, {$det[4]}<br/>";
            echo "</pre>";*/
            $l = $det[2];
            (isset($det[0]))? $totalsize = $det[0]: $totalsize = 0;
            if($line < 10001){
                $return .= "<tr style='cursor: pointer;' data-id='det{$line}'><td id='check'><input type='checkbox' value='{$line}' name='cline'/><span></span></td><td id='index'>{$line}</td><td class='break' style='color: #337ab7;'>{$l}</td><td class='info-td'>{$det[1]}</td><td class='info-td' style='color: ".call_user_func(['Functions', 'getColorTamFile'], call_user_func(['Functions', 'convertSize'], $totalsize))."'>".call_user_func(['Functions', 'convertSize'], $totalsize)."</td></tr>";
                $return .= "<tr id='det{$line}' class='hide-det'><td colspan='5' class='space-td'><div class='details-box-inline'>";
                $return .= "<table class='table table-bordered table-striped'>";
                $return .= "<tr><td colspan='3' class='table-table-details'>IP</td></tr>";
                $ips = explode(" ", str_replace("ips: ", "", $det[3]));
                foreach ($ips as $IP){
                    $ip = explode("\\", $IP);
                    $return .= "<tr><td class='break'>{$ip[1]}</td><td style='text-align: center;'>{$ip[2]}</td><td class='info-td' style='color: ".call_user_func(['Functions', 'getColorTamFile'], call_user_func(['Functions', 'convertSize'], $ip[0]))."'>".call_user_func(['Functions', 'convertSize'], $ip[0])."</td></tr>";
                }
                $return .= "</table></div>";
                $return .= "<div class='details-box-inline'><table class='table table-bordered table-striped'>";
                $return .= "<tr><td colspan='3' class='table-table-details'>Usu&aacute;rio</td></tr>";
                $users = explode(" ", str_replace("users: ", "", $det[4]));
                foreach ($users as $USER){
                    $user = explode("\\", $USER);
                    $return .= "<tr><td class='break'>{$user[1]}</td><td style='text-align: center;'>{$user[2]}</td><td class='info-td' style='color: ".call_user_func(['Functions', 'getColorTamFile'], call_user_func(['Functions', 'convertSize'], $user[0]))."'>".call_user_func(['Functions', 'convertSize'], $user[0])."</td></tr>";
                }   
                $return .= "</table>";
                $return .= "</div></td></tr>";
            }
        }
        
        if($typerep[0] == "aipuser" || $typerep[0] == "dipuser"){
            $sites = explode(" ", $det[2]);
            unset($sites[count($sites) -1]);
            $urls = explode(" ", $det[3]);
            unset($urls[count($urls) -1]);
            $nip = str_replace(".", "", $link);
            $getTotalSize = explode(" ", $index);
            (isset($getTotalSize[0]))? $TotalSize = $getTotalSize[0]: $TotalSize=0;
            if($line < 10001){
                $return .= "<tr style='cursor: pointer;' id='{$nip}' data-id='det{$line}'><td id='check'><input type='checkbox' value='{$line}' name='cline'/><span></span></td><td id='index'>{$line}</td><td style='color: #337ab7;'>{$link}</td><td class='info-td'>{$getTotalSize[1]}</td><td class='info-td' style='color: ".call_user_func(['Functions', 'getColorTamFile'], call_user_func(['Functions', 'convertSize'], $TotalSize))."'>".call_user_func(['Functions', 'convertSize'], $TotalSize)."</td></tr>";
                $return .= "<tr id='det{$line}' class='hide-det'><td colspan='5' class='space-td'><div class='details-box-inline'>";
                $return .= "<table class='table table-bordered table-striped'>";
                $return .= "<tr><td colspan='4' class='table-table-details'>Sites</td></tr>";
                foreach ($sites as $site){
                    $s = explode("\\", $site);
                    $return .= "<tr><td colspan='2' class='break'>{$s[1]}</td><td style='text-align: center;'>{$s[2]}</td><td class='info-td' style='color: ".call_user_func(['Functions', 'getColorTamFile'], call_user_func(['Functions', 'convertSize'], $s[0]))."'>".call_user_func(['Functions', 'convertSize'], $s[0])."</td></tr>";
                }
                $return .= "</table></div>";
                $return .= "<div class='details-box-inline'><table class='table table-bordered table-striped'>";
                $return .= "<tr><td colspan='4' class='table-table-details'>Download</td></tr>";
                foreach ($urls as $url){
                    $u = explode("\\", $url);
                    $return .= "<tr><td colspan='2' class='break'>{$u[1]}</td><td style='text-align: center;'>{$u[2]}</td><td class='info-td' style='color: ".call_user_func(['Functions', 'getColorTamFile'], call_user_func(['Functions', 'convertSize'], $u[0]))."'>".call_user_func(['Functions', 'convertSize'], $u[0])."</td></tr>";
                }
                $return .= "</table>";
                $return .= "</div></td></tr>";
            }
        }
        
        if($typerep[0] == "ausername" || $typerep[0] == "dusername"){
            $sites = explode(" ", $det[2]);
            unset($sites[count($sites) -1]);
            $urls = explode(" ", $det[3]);
            unset($urls[count($urls) -1]);
            $getTotalSize = explode(" ", $index);
            (isset($getTotalSize[0]))? $TotalSize = $getTotalSize[0]: $TotalSize=0;
            if($line < 10001){
                $return .= "<tr style='cursor: pointer;' id='{$user}' data-id='det{$line}'><td id='check'><input type='checkbox' value='{$line}' name='cline'/></td><td id='index'>{$line}</td><td style='color: #337ab7;'>$link</td><td class='info-td'>{$getTotalSize[1]}</td><td class='info-td' style='color: ".call_user_func(['Functions', 'getColorTamFile'], call_user_func(['Functions', 'convertSize'], $TotalSize))."'>".call_user_func(['Functions', 'convertSize'], $TotalSize)."</td></tr>";
                $return .= "<tr id='det{$line}' class='hide-det'><td colspan='5' class='space-td'><div class='details-box-inline'>";
                $return .= "<table class='table table-bordered table-striped'>";
                $return .= "<tr><td colspan='4' class='table-table-details'>Sites</td></tr>";
                foreach ($sites as $site){
                    $s = explode("\\", $site);
                    $return .= "<tr><td colspan='2' class='break'>{$s[1]}</td><td style='text-align: center;'>{$s[2]}</td><td class='info-td' style='color: ".call_user_func(['Functions', 'getColorTamFile'], call_user_func(['Functions', 'convertSize'], $s[0]))."'>".call_user_func(['Functions', 'convertSize'], $s[0])."</td></tr>";
                }
                $return .= "</table></div>";
                $return .= "<div class='details-box-inline'><table class='table table-bordered table-striped'>";
                $return .= "<tr><td colspan='4' class='table-table-details'>URL</td></tr>";
                foreach ($urls as $url){
                    $u = explode("\\", $url);
                    $return .= "<tr><td colspan='2' class='break'>{$u[1]}</td><td style='text-align: center;'>{$u[2]}</td><td class='info-td' style='color: ".call_user_func(['Functions', 'getColorTamFile'], call_user_func(['Functions', 'convertSize'], $u[0]))."'>".call_user_func(['Functions', 'convertSize'], $u[0])."</td></tr>";
                }
                $return .= "</table>";
                $return .= "</div></td></tr>";
            }
        }
        
        if($typerep[0] == "mime"){
            $Line = explode(" \/ ", $detail);
            $nreturn = "";
            $mime = $Line[0];
            unset($Line[0]);
            foreach ($Line as $l){
                $t = explode("\\", explode(" | ", $l)[0]);
                $u = explode(" ", explode(" | ", $l)[1]);
                $total[] = $t[1];
                $tamfile[] = $t[2];
                #call_user_func(['Functions', 'switchChar'], $t[0].$mime)
                $nreturn .= "<tr data-id='det".call_user_func(['Functions', 'switchChar'], $t[0].$mime)."'><td id='check'><input type='checkbox' data-leg='leg-".call_user_func(['Functions', 'switchChar'], $t[0].$mime)."' value='".call_user_func(['Functions', 'switchChar'], $t[0].$mime)."' name='cline'/></td><td style='font-weight: 500;color:#4682B4' colspan='4'>{$t[0]}</td><td class='aligntd'>{$t[1]}</td><td class='aligntd' style='color: ".call_user_func(['Functions', 'getColorTamFile'], call_user_func(['Functions', 'convertSize'], $t[2]))."'>".call_user_func(['Functions', 'convertSize'], $t[2])."</td></tr>";
                $nreturn .= "<tr id='det".call_user_func(['Functions', 'switchChar'], $t[0].$mime)."' class='hide-det'><td colspan='8' class='space-td'><table class='table'>";
                foreach ($u as $ind => $Url){
                    #echo "{$ind} {$url}<br/>";
                    $url = explode("\\", $Url);
                    $nreturn .= "<tr><td class='break' colspan='4'>{$url[0]}</td><td>{$url[1]}</td><td style='white-space: nowrap;color: ".call_user_func(['Functions', 'getColorTamFile'], call_user_func(['Functions', 'convertSize'], $url[2]))."'>".call_user_func(['Functions', 'convertSize'], $url[2])."</td></tr>";
                }
                $nreturn .= "</table></td></tr>";
            }
            $total = array_sum($total);
            $tamfile = array_sum($tamfile);
            $this->band[] = $tamfile;
            $return .= "<tr id='th-{$line}' class='title-details-mime'><th id='leg-{$mime}' colspan='5'>{$mime}</th><th style='text-align: right'><span class='badge'>{$total}</span></th><th style='text-align: right;color: ".call_user_func(['Functions', 'getColorTamFile'], call_user_func(['Functions', 'convertSize'], $tamfile))."'>".call_user_func(['Functions', 'convertSize'], $tamfile)."</th></tr>";
            $return .= $nreturn;
        }
        
        return $return;
        
    }

    public function calendar($Date = NULL){
        $report = $this->getReports();
        $monthyear = $this->getMonthReports();
        if($Date != NULL)
            $gDate = explode ("-", $Date);
        else
            $gDate = (isset($_REQUEST['d']))? explode("-", $_REQUEST['d']): explode("-", date("m-Y"));
        
        $date = mktime(date("G"),date("i"),date("s"), $gDate[0],1,$gDate[1]);

        $d = date('d', $date);
        $m = date('n', $date);
        $y = date('Y', $date);

        $fday = mktime(0,0,0, $m, 1, $y);
        $wday = date("D", $fday);
        $daysmonth = date("t", $date);
        $gtitle = date("F", $fday);
        switch ($gtitle){
            case "January": $title = "Janeiro";break;
            case "February": $title = "Fevereiro";break;
            case "March": $title = "Mar&ccedil;o";break;
            case "April": $title = "Abril";break;
            case "May":  $title = "Maio";break;
            case "June":  $title = "Junho";break;
            case "July":  $title = "Julho";break;
            case "August":  $title = "Agosto";break;
            case "September":  $title = "Setembro";break;
            case "October":  $title = "Outubro";break;
            case "November":  $title = "Novembro";break;
            case "December":  $title = "Dezembro";break;
        }

        $prev = date("n-Y", strtotime('-1 months', strtotime("{$y}-{$m}")));
        $next = date("n-Y", strtotime('+1 months', strtotime("{$y}-{$m}")));

        switch ($wday){
            case "Dom": $blank = 0;            break;
            case "Seg": $blank = 1;            break;
            case "Ter": $blank = 2;            break;
            case "Qua": $blank = 3;            break;
            case "Qui": $blank = 4;            break;
            case "Sex": $blank = 5;            break;
            case "Sab": $blank = 6;            break;
        }

        switch ($m){
            case "01": $month = "Jan";            break;
            case "02": $month = "Fev";            break;
            case "03": $month = "Mar";            break;
            case "04": $month = "Abr";            break;
            case "05": $month = "Mai";            break;
            case "06": $month = "Jun";            break;
            case "07": $month = "Jul";            break;
            case "08": $month = "Ago";            break;
            case "09": $month = "Set";            break;
            case "10": $month = "Out";            break;
            case "11": $month = "Nov";            break;
            case "12": $month = "Dez";            break;
        }
        if(isset($monthyear[$y][$m])){
            echo "<input type=\"hidden\" value=\"?d={$m}-{$y}\" name=\"reporttrue\" id=\"reporttrue\" />";
        }
        echo "
            <input type=\"hidden\" value=\"{$prev}\" name=\"prev\" id=\"fprev\" />
            <input type=\"hidden\" value=\"{$next}\" name=\"next\" id=\"fnext\" />
            <input type=\"hidden\" value=\"{$title} / {$y}\" name=\"month\" id=\"month\" />
            <input type=\"hidden\" value=\"?d={$m}-{$y}\" name=\"my\" id=\"my\"/>
            <table class=\"table table-calendar\">
                <tr>
                    <td class=\"month-calendar\">Dom</td>
                    <td class=\"month-calendar\">Seg</td>
                    <td class=\"month-calendar\">Ter</td>
                    <td class=\"month-calendar\">Qua</td>
                    <td class=\"month-calendar\">Qui</td>
                    <td class=\"month-calendar\">Sex</td>
                    <td class=\"month-calendar\">Sab</td>
                </tr>
                <tr>
        ";
        $counter = 0;
        for ($i = 1; $i < $daysmonth+1; $i++, $counter++) {
        $timeStamp = strtotime("$y-$m-$i");
            if ( $i == 1) {
                $firstDay = date("w",$timeStamp);

                for($j = 0; $j < $firstDay; $j++, $counter++)
                        echo "<td>&nbsp;</td>";
            }
            if ($counter % 7 == 0)
                    echo "</tr><tr>";

            if ( $i == date('d') && $m == date("m") && $y == date('Y') and isset($report[$y][$m][$i])) {
                    echo "<td class=\"current event\"><a href=\"?d={$m}-{$y}-{$i}\"><div class=\"link-td\">$i</div></a></td>";
            }
            elseif ( $i == date('d') && $m == date("m") && $y == date('Y') ) {
                    echo "<td class=\"current\"><a href=\"?d={$m}-{$y}-{$i}\"><div class=\"link-td\">$i</div></a></td>";
            }
            else {
                if(isset($report[$y][$m][$i])){
                    echo "<td class=\"event\"><a href=\"?d={$m}-{$y}-{$i}\"><div class=\"link-td\">$i</div></a></td>";
                }
                else{
                    echo "<td class=\"day\"><a href=\"?d={$m}-{$y}-{$i}\"><div class=\"link-td\">$i</div></a></td>";
                }
            }
        }
        echo "
            </tr></table>
        ";
        
    }
    
    public function generateReport(){
        $date = explode("-",$_REQUEST['day']);
        $month = $date[0];
        $year = $date[1];
        (count($date) == 3)? $day = $date[2]: $day = "";
        system(WWW."report/report {$month} {$year} {$day}", $generate);
    }
    
    public function removeReport(){
        system("/bin/rm -rf ".WWW."report/dashboard/*.{$_REQUEST['day']}");
        system("/bin/rm -rf ".WWW."report/details/*.{$_REQUEST['day']}");
    }

    public function __destruct() {
        parent::__destruct();
    }
    protected function showMonth($month){
        switch ($month){
            case "01":return "Janeiro";
            case "02":return "Fevereiro";
            case "03":return "Mar&ccedil;o";
            case "04":return "Abril";
            case "05": return "Maio";
            case "06": return "Junho";
            case "07": return "Julho";
            case "08": return "Agosto";
            case "09": return "Setembro";
            case "10": return "Outubro";
            case "11": return "Novembro";
            case "12": return "Dezembro";
        }
    }
    protected function showReport($report){
        switch ($report){
            case "accesssites": return "Sites acessados por IP e Usu&aacute;rio";
            case "deniedsites": return "Sites negados por IP e Usu&aacute;rio";
            case "accessurl": return "URL's acessados por IP e Usu&aacute;rio";
            case "deniedurl": return "URL's negados por IP e Usu&aacute;rio";
            case "aipuser": return "Acessos por IP";
            case "dipuser": return "Negados por IP";
            case "ausername": return "Acessos por Usu&aacute;rio";
            case "dusername": return "Negados por Usu&aacute;rio";
            case "mime": return "Consumo de Banda";
        }
    }
}
