<?php
/**
 * @author Mauro Marssola - Vantage TI
 */
class Functions {
    public function FileSize($bytes) {
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
    public function getColorTamFile($size){
        if(eregi("KB", $size)){
            $color = "#7B68EE";
        }
        else if(eregi("MB", $size)){
            $color = "#006400";
        }
        else if(eregi("GB", $size)){
            $color = "#FF0000";
        }
        else if(eregi("TB", $size)){
            $color = "#8B0000";
        }
        else{
            $color = "#808080";
        }
        return $color;
    }
    public function switchChar($string){
        $return = preg_replace("/[^a-zA-Z0-9]/", "", $string);
        return $return;
    }
    public function convertSize($size, $reverse = NULL){
        if(ereg("GB", $size)){
            $size = str_replace("GB", "", $size) * 1073741824;
        }
        elseif(ereg("MB", $size)) {
            $size = str_replace("MB", "", $size) * 1048576;
        }
        elseif(ereg("KB", $size)){
            $size = str_replace("KB", "", $size) * 1024;
        }
        else{
            if($reverse == TRUE){
                $size = str_replace("B", "", $size);
                if ($size >= 1073741824){
                    $size = number_format($size / 1073741824, 2) . 'GB';
                }
                elseif ($size >= 1048576){
                    $size = number_format($size / 1048576, 2) . 'MB';
                }
                elseif ($size >= 1024){
                    $size = number_format($size / 1024, 2) . 'KB';
                }
                elseif ($size > 1){
                    $size = $size . '';
                }
                elseif ($size == 1){
                    $size = $size . '';
                }
                else{
                    $size = '0';
                }
            }
            else{
                $size = str_replace("B", "", $size);
                if ($size >= 1073741824){
                    $size = number_format($size / 1073741824, 2) . 'GB';
                }
                elseif ($size >= 1048576){
                    $size = number_format($size / 1048576, 2) . 'MB';
                }
                elseif ($size >= 1024){
                    $size = number_format($size / 1024, 2) . 'KB';
                }
                elseif ($size > 1){
                    $size = $size . 'B';
                }
                elseif ($size == 1){
                    $size = $size . 'B';
                }
                else{
                    $size = '0B';
                }
            }
        }
        return $size;
    }
    public function breakString($str){
        if(strlen($str) > 25){
            $str = wordwrap($str, 25, "<br/>", TRUE);
        }
        return $str;
    }
    
    public function getNameFile(){
        $getPath = glob("../tmp/*");
        $count = count($getPath);
        if($count != 0){
            foreach ($getPath as $file){
                $tsf = explode(".", explode("/", $file)[2])[0];
                $ts = strtotime("-1 hour");
                if($ts > $tsf){
                    if($tsf != "download"){
                        system("/bin/rm -rf {$file}");
                    }
                }
            }
        }
        return time();
    }
    
    public function sizeString($str){
        if(strlen($str) > 25){
            $str = substr($str, 0, 25);
        }
        return $str;
    }
    public function getVersion(){
        $current_version = "2.0_beta";
        //$available_version = simplexml_load_file("http://logsquid.com/version-dev.xml");
        //$available = $available_version->versions->available;

        //return "{$current_version} {$available}<br/>";

        /*if((string)$current_version == (string)$available){
            $return = "O logSquid beta est&aacute; atualizado<br/>"
                    . "Vers&atilde;o instalada: {$current_version}";
            return $return;
        }*/
        //else{
            $return = "Vers&atilde;o atual: {$current_version}";
            return $return;
        //}
    }    
}
