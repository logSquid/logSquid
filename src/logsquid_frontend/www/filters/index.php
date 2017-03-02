<?php 
$PATHS = array('class','css','js','img','functions','settings','realtime','filters','report','daemon','webgui','lang','graph','tmp','user');
$WWW = str_replace($PATHS, "", dirname(__FILE__));
require_once("{$WWW}functions/autoload.php");

?>
<html>
    <?php require_once ("../".WEB."header.php");?>
    <script type="text/javascript" src="<?php echo BASEURL.FILTERS ?>filter.js"></script>
    <script type="text/javascript" src="<?php echo BASEURL.FILTERS ?>ExportFile.js"></script>
    <script type="text/javascript">
        $(document).ready(function(){
            $("#filter").attr("class","active");
        });
    </script>
        <div class="container container-geral">
        <?php
            $logSquid = new logsquid();
            $filter = new filters();
            $header = new webgui();
            $header->headerFilter($logSquid->typelog);
        ?>
        </div><br/>
        <div class="container container-filter">
        <?php
            $header->FilterheaderReadlogSquid();
        ?>
        </div>
        <?php
            $header->modalFilterConf();
            $header->ExportFIlter();
        ?>
        <div id='area-TableExport'></div>
    </body>
</html>
