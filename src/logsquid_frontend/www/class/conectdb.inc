<?php
class conectdb{
    protected $db_Host;
    protected $db_User;
    protected $db_Pass;
    protected $db_Name;
    public  $status;
    public  $Con;

    public function setData($hostname, $username, $password, $database){
        $this->db_Host = "{$hostname}";
        $this->db_User = "{$username}";
        $this->db_Pass = "{$password}";
        $this->db_Name = "{$database}";
    }

    public function Conect(){
        $MyCon = mysql_connect("{$this->db_Host}", "{$this->db_User}", "{$this->db_Pass}");
        if($MyCon){
        $SelDB = @mysql_select_db($this->db_Name, $MyCon);
        if($SelDB){
            $this->Con = true;
            return $this->status = TRUE;
        }
        else{
            return "Sem conexao com a Tabela";
            }
        }
        else{
            return "Sem conexao com o Banco de Dados";
        }
    }
    public function Desconect(){
        if($this->Con){
            if(@mysql_close()){
                $this->Con = FALSE;
                return TRUE;
            }
            else{
                return FALSE;
            }
        }
    }
}
