<?php
$PATHS = array('class','css','js','img','functions','settings','realtime','filters','report','daemon','webgui','lang','graph','tmp','user');
$WWW = str_replace($PATHS, "", dirname(__FILE__));
$WWW_FE = "/usr/share/logSquid/logsquid_frontend/";

require_once("{$WWW}functions/autoload.php");

class logSquidconf{
    public $settingsxml = "settings.xml";
    public $conffile = "logsquid_frontend.conf";
    public $conf;
    public $settings;
    public $lines_settings;
    public $binsquid;
    public $pathsquid;
    public $pathlog;
    public $typelog = "logSquid";
    public $database;
    public $hostname;
    public $username;
    public $password;
    public $status;
    public $daemonfile = "/etc/init.d/logsquidd";
    public $bootdaemon;
    public $timezone;

    public function __construct() {
        if(!file_exists(WWW_FE.$this->conffile)){
            if($this->createConfFile())
                $this->conf = parse_ini_file(WWW_FE.$this->conffile);
        }
        else
            $this->conf = parse_ini_file(WWW_FE.$this->conffile);
    }
    public function createConfFile(){
        $conf = array();
        $conf['hostname'] = "";
        $conf['username'] = "";
        $conf['password'] = "";
        $conf['database'] = "";
        
        $lines = "[Database]\n";
        foreach ($conf as $k => $value){
            $lines .= "{$k} = {$value}\n";
        }
	$lines .= "\n[General]\n";
	$lines .= "timezone = \n";
        file_put_contents(WWW_FE.$this->conffile, $lines);
    }
    public function writeDataBase($hostname = null, $username = null, $password = null, $database = null, $timezone = null){
        $conf = $this->conf;
        $conf['Database']['hostname'] = $hostname;
        $conf['Database']['username'] = $username;
        $conf['Database']['password'] = $password;
        $conf['Database']['database'] = $database;
        $lines = "[Database]\n";
        foreach ($conf['Database'] as $k => $value){
            $lines .= "{$k} = {$value}\n";
        }
	$lines .= "\n[General]\n";
        $lines .= "timezone = {$timezone}\n";
        if(file_put_contents(WWW_FE.$this->conffile, $lines)){
            echo "<script>MsgSuccess('Configura&ccedil;&atilde;o do Banco de Dados gravada com sucesso')</script>";
            $this->status = TRUE;
        }
        else{
            echo "<script>NoticeDanger('Erro ao gravar as configura&ccedil;&otilde;es')</script>";
            $this->status = FALSE;
        }
    }
    public function readDataBase(){
        $this->hostname = $this->conf['hostname'];
        $this->username = $this->conf['username'];
        $this->password = $this->conf['password'];
        $this->database = $this->conf['database'];
	$this->timezone = $this->conf['timezone'];
    }
    public function get_list_timezone(){
        $list_timezone = array_merge(
            glob("/usr/share/zoneinfo/[A-Z]*"),
            glob("/usr/share/zoneinfo/*/*"),
            glob("/usr/share/zoneinfo/*/*/*")
        );
        if(!empty($list_timezone)){
            $list_timezone = array_filter($list_timezone, function($v){
                return !is_dir($v);
            });
        }
        $list_timezone = str_replace("/usr/share/zoneinfo/", '', $list_timezone);
        sort($list_timezone);
        
        return $list_timezone;
    }
}
