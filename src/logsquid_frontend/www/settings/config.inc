<?php
$PATHS = array('class','css','js','img','functions','settings','realtime','filters','report','daemon','webgui','lang','graph','tmp','user');
$WWW = str_replace($PATHS, "", dirname(__FILE__));
require_once("{$WWW}functions/autoload.php");

class config{
    public $settingsxml = "/var/www/html/logsquid/settings.xml";
    public $settings;
    public $lines_settings;
    public $pathsquid;
    public $pathlog;
    public $typelog;
    public $status;
    
    
    public function __construct() {
        if(!file_exists($this->settingsxml)){
            $this->createSettings();
        }
        else{
            $this->settings = simplexml_load_file($this->settingsxml);
            $this->lines_settings = count($this->settings);
        }
    }
    
    public function createSettings(){
        $settings = new SimpleXMLElement("<logSquid></logSquid>");
        $settings->addChild("pathsquid");
        $settings->addChild("pathlog");
        $settings->addChild("typelog");
        file_put_contents($this->settingsxml, $settings->asXML());
        return true;
    }

    public function writeSettings($pathsquid=null, $pathlog=null, $typelog=null){
        $this->settings->pathsquid = ($pathsquid == "") ? trim(shell_exec("which squid")): $pathsquid;
        $this->settings->pathlog = $pathlog;
        $this->settings->typelog = $typelog;
        //file_put_contents($this->settingsxml, $this->settings->asXML());
        //return $this->status = true;
        echo "{$pathsquid} {$pathlog}";
    }
    
    public function readSettings(){
        $this->pathsquid = $this->settings->pathsquid;
        $this->pathlog = $this->settings->pathlog;
        $this->typelog = $this->settings->typelog;
    }
}
/*
echo "<pre>";
$xml = new config();
$xml->writeSettings("/usr/pbi/squid-amd64/local/sbin/squid", "/var/squid/logs/", "squid");
$xml->readSettings();

echo "{$xml->pathsquid} <br/>";
echo "{$xml->pathlog} <br/>";
echo "{$xml->typelog} <br/>";
*/
