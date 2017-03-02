<?php
/*
 * @author Mauro Marssola
 */
$PATHS = array('class','css','js','img','functions','settings','realtime','filters','report','daemon','webgui','lang','graph','tmp','user', 'services');
$WWW = str_replace($PATHS, "", dirname(__FILE__));
require_once("{$WWW}functions/autoload.php");

class Services extends logsquid{
    
    public function __construct() {
        parent::__construct();
    }
    
    public function getServicesServer(){
        mysql_query("SET character_set_results = 'utf8', character_set_client = 'utf8', character_set_connection = 'utf8', character_set_database = 'utf8', character_set_server = 'utf8'");
        $this->select = "SELECT * FROM `servers`";
        $query = mysql_query($this->select);
        while($this->result = mysql_fetch_assoc($query)){
        ?>
        <table class='table table-striped table-hover list-server'>
            <tr>
                <th>Nome: </th>
                <td id="td-server-<?php echo $this->result['id']; ?>"><?php echo ($this->result['name'] == NULL)? "Sem Nome": $this->result['name']; ?></td>
                <td style="width: 50px"><button type="button" id-item-server="<?php echo $this->result['id']; ?>" class="btn_simple edit-server" aria-label="Left Align" data-toggle="modal" data-target=".modal-edit-server"><span class="glyphicon glyphicon-pencil" aria-hidden="true"></span></button></td>
            </tr>
            <tr>
                <th>IP:</th>
                <td><?php echo $this->result['ipaddr']; ?></td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <th>In&iacute;cio da Sess&atilde;o:</th>
                <td><?php echo date("d/m/Y H:i:s", strtotime($this->result['start_session'])); ?></td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <th>Renova&ccedil;&atilde;o da Sess&atilde;o:</th>
                <td><?php echo date("d/m/Y H:i:s", strtotime($this->result['last_activity'])); ?></td>
                <td>&nbsp;</td>
            </tr>
            <tr>
                <th>Status:</th>
                <?php
                if(strtotime($this->result['last_activity']."+2 min") < strtotime(date("Y-m-d H:i:s"))){
                    echo "<td><span class='text-danger'>Offline</td>";
                }
                else{
                    echo "<td><span class='text-success'>Online</span></td>";
                }
                ?>
                <td>&nbsp;</td>
            </tr>
        </table>
        <?php
        }
        
    }
    
    public function getServicesAgents(){
        mysql_query("SET character_set_results = 'utf8', character_set_client = 'utf8', character_set_connection = 'utf8', character_set_database = 'utf8', character_set_server = 'utf8'");
        $this->select = "SELECT * FROM `agents` ORDER BY `ipaddr` ASC";
        $query = mysql_query($this->select);
        echo "<table class='table table-striped table-hover'>";
        while($this->result = mysql_fetch_assoc($query)){
        ?>
            <tr>
                <td id="td-agent-<?php echo $this->result['id']; ?>"><?php echo ($this->result['name'] == NULL)? "Sem Nome": $this->result['name']; ?></td>
                <td><?php echo $this->result['ipaddr']; ?></td>
                <td style="width: 50px"><button type="button" id-item-agent="<?php echo $this->result['id']; ?>" class="btn_simple edit-agent" aria-label="Left Align" data-toggle="modal" data-target=".modal-edit-agent"><span class="glyphicon glyphicon-pencil" aria-hidden="true"></span></button></td>
            </tr>
        <?php
        }
        echo "</table>";
    }
    
    public function modalEditAgent(){
    ?>
        <div class="modal fade modal-edit-agent" tabindex="-1" role="dialog" aria-labelledby="mySmallModalLabel">
            <div class="modal-dialog modal-lg" role="document">
                <div class="modal-content">
                    <div class="modal-header">
                        <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
                        <h4 class="modal-title" id="gridSystemModalLabel">Editar Agent</h4>
                    </div>
                    <form class="form-horizontal" id="form-name-agent">
                        <div class="modal-body" style="padding: 15px;">
                            <input type="hidden" value="" name="id-agent" id="id-agent" />
                            <div class="form-group">
                                <label for="inputEmail3" class="col-sm-2 control-label">Nome</label>
                                <div class="col-sm-8">
                                    <input type="text" class="form-control" id="name-agent">
                                </div>
                            </div>
                        </div>
                        <div class="modal-footer">
                            <input type="submit" value="Salvar" class="btn btn-primary" />
                        </div>
                    </form>
                </div>
            </div>
        </div>
    <?php
    }
    
    public function modalEditServer(){
    ?>
        <div class="modal fade modal-edit-server" tabindex="-1" role="dialog" aria-labelledby="mySmallModalLabel">
            <div class="modal-dialog modal-lg" role="document">
                <div class="modal-content">
                    <div class="modal-header">
                        <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
                        <h4 class="modal-title" id="gridSystemModalLabel">Editar Server</h4>
                    </div>
                    <form class="form-horizontal" id="form-name-server">
                        <div class="modal-body" style="padding: 15px;">
                            <input type="hidden" value="" name="id-agent" id="id-server" />
                            <div class="form-group">
                                <label for="inputEmail3" class="col-sm-2 control-label">Nome</label>
                                <div class="col-sm-8">
                                    <input type="text" class="form-control" id="name-server">
                                </div>
                            </div>
                        </div>
                        <div class="modal-footer">
                            <input type="submit" value="Salvar" class="btn btn-primary" />
                        </div>
                    </form>
                </div>
            </div>
        </div>
    <?php
    }
    
    public function getAgentsFilters(){
        mysql_query("SET character_set_results = 'utf8', character_set_client = 'utf8', character_set_connection = 'utf8', character_set_database = 'utf8', character_set_server = 'utf8'");
        $this->select = "SELECT * FROM agents ORDER BY name ASC";
        $query = mysql_query($this->select);
        while($this->result = mysql_fetch_assoc($query)){
        ?>
            <li>
                <input type="radio" id="agent-<?php echo $this->result['id']; ?>" name="typeagent" value="<?php echo $this->result['id']; ?>">
                <label for="agent-<?php echo $this->result['id']; ?>"><?php echo ($this->result['name'] == "")? $this->result['ipaddr']: $this->result['name']; ?></label>
            </li>
        <?php
        }
    }
    
    public function setNameAgents($id = NULL, $name = NULL){
        mysql_query("SET character_set_results = 'utf8', character_set_client = 'utf8', character_set_connection = 'utf8', character_set_database = 'utf8', character_set_server = 'utf8'");
        $this->update = "UPDATE `agents` SET `name`='{$name}' WHERE `id`='{$id}'";
        $this->result = mysql_query($this->update);
        $this->LinesAffected = mysql_affected_rows();
        if($this->LinesAffected == 1){
            return TRUE;
        }
        else{
            return FALSE;
        }
    }
    
    public function setNameServers($id = NULL, $name = NULL){
        mysql_query("SET character_set_results = 'utf8', character_set_client = 'utf8', character_set_connection = 'utf8', character_set_database = 'utf8', character_set_server = 'utf8'");
        $this->update = "UPDATE `servers` SET `name`='{$name}' WHERE `id`='{$id}'";
        $this->result = mysql_query($this->update);
        $this->LinesAffected = mysql_affected_rows();
        if($this->LinesAffected == 1){
            return TRUE;
        }
        else{
            return FALSE;
        }
    }
    
}
