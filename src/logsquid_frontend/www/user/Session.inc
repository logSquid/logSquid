<?php

class Session{
    public function __construct($session_name="logSquid"){
        session_name($session_name);
        if(!isset($_SESSION)){
            session_start();
        }
        if($this->hasField("timezone")){
            date_default_timezone_set($this->getField("timezone"));
        }
        else{
            date_default_timezone_set("Etc/UTC");
        }
    }
    
    public function setField($field, $value){
        $_SESSION[$field] = $value;
    }
    
    public function hasField($field){
        return isset($_SESSION[$field]);
    }

    public function getField($field){
        return $this->hasField($field)? $_SESSION[$field]: NULL;
    }
    
    public function setExpireTime($strtime){
        $this->setField('duration', $strtime);
        $this->setField('expire', strtotime("+$strtime"));
    }
    
    public function register($duration = "30 min"){
        $this->setExpireTime($duration);
    }
    
    public function expired(){
        if(time() > $this->getField('expire')){
            return TRUE;
        }
        return FALSE;
    }
    
    public function valid(){
        if($this->expired()){
            $this->destroy();
            return FALSE;
        }
        $this->renew();
        return TRUE;
    }
    
    public function renew(){
        $this->setExpireTime($this->getField('duration'));
    }

    public function destroy(){
        if(isset($_SESSION)){
            $_SESSION = [];
            session_destroy();
        }
    }
}
