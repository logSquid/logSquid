<?php
$PATHS = array('class','css','js','img','functions','settings','realtime','filters','report','daemon','webgui','lang','graph','tmp','user');
$WWW = str_replace($PATHS, "", dirname(__FILE__));
require_once("{$WWW}functions/autoload.php");

class logsquidcsv{
    var $where;
    var $settings;
    var $logsquid;
    
    public function __construct($where, $settings) {
        $this->where = $where;
        $this->settings = $settings;
    }
    public function createStructure(){
        $this->logsquid = new logsquid();
        $this->logsquid->where = $this->where;
        $this->logsquid->CSVselectLog($this->settings);
    }
}
