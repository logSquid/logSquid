<?php
$PATHS = array('class','css','js','img','functions','settings','realtime','filters','report','daemon','webgui','lang','graph','tmp','user');
$WWW = str_replace($PATHS, "", dirname(__FILE__));

require_once("{$WWW}functions/autoload.php");

class user extends conectdb{
    public $username;
    public $password;
    public $passwordnew;
    public $login = FALSE;
    public $nickname;
    public $theme;
    public $timezone;
    protected $Session;

    public function __construct() {
        $this->Session = new Session();
        $logSquidconf = new logSquidconf();
        $logSquidconf->readDataBase();
        $this->timezone = $logSquidconf->timezone;

        parent::setData(trim($logSquidconf->hostname), trim($logSquidconf->username), trim($logSquidconf->password), trim($logSquidconf->database));
        parent::Conect();
    }
    
    protected function checkHash(){
        $check_hash_select = "SELECT `hashCode` FROM users WHERE `username`='{$this->Session->getField('username')}' and `hashCode`='{$this->Session->getField('hash')}'";
        $check_hash_query = mysql_query($check_hash_select);
        $check_hash_rows = mysql_num_rows($check_hash_query);
        
        if($check_hash_rows != 1){
            exit("Voce não tem permissão");
        }
    }
    
    public function setUserPass($username = NULL, $password = NULL){
        $this->username = trim($username);
        $this->password = sha1(trim($password));
    }

    public function checkUser(){
        mysql_query("SET character_set_results = 'utf8', character_set_client = 'utf8', character_set_connection = 'utf8', character_set_database = 'utf8', character_set_server = 'utf8'");
        $user_select = "SELECT `username`, `nickname` FROM users WHERE `username`='{$this->username}'";
        $user_query = mysql_query($user_select);
        $user_result = mysql_num_rows($user_query);
        $user_get = mysql_fetch_assoc($user_query);
        if($user_result == 1){
            $pass_select = "SELECT `password`, `theme` FROM users WHERE `username`='{$this->username}' and `password`='{$this->password}'";
            $pass_query = mysql_query($pass_select);
            $pass_get = mysql_fetch_assoc($pass_query);
            $pass_result = mysql_num_rows($pass_query);
            if($pass_result == 1){
                $this->login = TRUE;
                $this->nickname = $user_get['nickname'];
                $this->theme = $pass_get['theme'];
            }
            else {
                $this->login = FALSE;
                echo "Senha inv&aacute;lida";
            }
        }
        else{
            $this->login = FALSE;
            echo "Usu&aacute;rio inv&aacute;lido";
        }
    }
    public function alterPassword(){
        $this->checkHash();
        mysql_query("SET character_set_results = 'utf8', character_set_client = 'utf8', character_set_connection = 'utf8', character_set_database = 'utf8', character_set_server = 'utf8'");
        $user_select = "UPDATE `users` SET `password`='{$this->passwordnew}' WHERE `username`='{$this->Session->getField('username')}' and `password`='{$this->password}'";
        $user_query = mysql_query($user_select);
        if(mysql_affected_rows() == 1)
            return TRUE;
        else {
            echo "A Senha atual n&atilde;o confere";
        }
    }
    public function validateLogin(){
        if($this->login == TRUE){
            mysql_query("SET character_set_results = 'utf8', character_set_client = 'utf8', character_set_connection = 'utf8', character_set_database = 'utf8', character_set_server = 'utf8'");
            $hash = "logSquid".sha1(uniqid(rand(), true));
            $hashCode = "UPDATE `users` SET `hashCode`='{$hash}' WHERE `username`='{$this->username}'";
            mysql_query($hashCode);
            if(mysql_affected_rows() == 1){
                $this->Session->register();
                $this->Session->setField("username", $this->username);
                $this->Session->setField("nickname", $this->nickname);
                $this->Session->setField("theme", $this->theme);
                $this->Session->setField("hash", $hash);
		$this->Session->setField("timezone", $this->timezone);
            }
            else{
                $this->logout();
                return false;
            }
        }
        else{
            $this->logout();
            return false;
        }
    }
    
    public function alterTheme(){
        $this->checkHash();
        mysql_query("SET character_set_results = 'utf8', character_set_client = 'utf8', character_set_connection = 'utf8', character_set_database = 'utf8', character_set_server = 'utf8'");
        $user_theme = "UPDATE `users` SET `theme`='{$this->theme}' WHERE `username`='{$this->Session->getField("username")}'";
        mysql_query($user_theme);
        if(mysql_affected_rows() == 1)
            return TRUE;
        else {
            return FALSE;
        }
    }
    
    public function updateUsername(){
        $this->checkHash();
        mysql_query("SET character_set_results = 'utf8', character_set_client = 'utf8', character_set_connection = 'utf8', character_set_database = 'utf8', character_set_server = 'utf8'");
        $username = "UPDATE `users` SET `nickname`='{$this->nickname}' WHERE `username`='{$this->Session->getField("username")}'";
        mysql_query($username);
        if(mysql_affected_rows() == 1)
            return TRUE;
        else {
            return mysql_error();
        }
    }
    
    public function getTheme(){
        mysql_query("SET character_set_results = 'utf8', character_set_client = 'utf8', character_set_connection = 'utf8', character_set_database = 'utf8', character_set_server = 'utf8'");
        $gettheme = "SELECT `theme` FROM users WHERE username='{$this->Session->getField("username")}'";
        $gettheme_query = mysql_query($gettheme);
        $gettheme_result = mysql_fetch_assoc($gettheme_query);
        return $gettheme_result['theme'];
    }
    
    public function checkStatus(){
        if($this->Session->valid() == TRUE){
            return TRUE;
        }
    }

    public function logout(){
        $this->Session->destroy();
    }
    
    public function __destruct() {
        parent::Desconect();
    }
}
