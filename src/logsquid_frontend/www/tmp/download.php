<?php
if($_GET['d']){
    header("Content-type:text/{$_GET['type']}");
    header("Content-Disposition:attachment;filename='{$_GET['d']}.{$_GET['type']}");
    header("Pragma: no-cache");   
    readfile("{$_GET['d']}.{$_GET['type']}");
}

?>
