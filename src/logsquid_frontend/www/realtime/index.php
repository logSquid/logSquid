<?php 
$PATHS = array('class','css','js','img','functions','settings','realtime','filters','report','daemon','webgui','lang','graph','tmp','user');
$WWW = str_replace($PATHS, "", dirname(__FILE__));
require_once("{$WWW}functions/autoload.php");
?>
<html>
    <?php require_once ("../".WEB."header.php");?>
    <script type="text/javascript">
        $(document).ready(function(){
            $("#realtime").attr("class","active");
            var fields = new Array();
            $("#applyconf").click(function(){
                $("input[name=configpage]").each(function(){
                    if(!$(this).is(":checked")){
                        $("#col-"+$(this).val()).hide();
                    }
                    else{
                        $("#col-"+$(this).val()).show();
                    }
                });
                $("input[name=configpage]").each(function(){
                    if($(this).is(":checked")){
                        fields.push($(this).val());
                    }
                });
                $("#fields").val(fields.join(", "));
            });
            function RealTime(){
               setInterval(function(){
                    var search = $("#fieldfilter").val();
                    var showlines = $("#showlines").val();
                    var fields = $("#fields").val();
                    var agent = "";
                    var listagents = $("#lagents").html();
                    $("li").find("label").each(function(){
                        if($(this).text() === listagents){
                            agent = $("#"+$(this).attr("for")).val();
                        }
                    });
                   $.post("<?php echo BASEURL.FUNC; ?>conectclass.php",{action: "getRealTime", search: search, showlines: showlines, fields: fields, agent: agent},
                   function(realtime){
                       $("#listAccess tbody").html(realtime);
                   });
               }, 1000);
           }
           RealTime();
        });
    </script>
    <div id="area-realtime" class="container container-geral">
    <?php
        $logsquid = new logsquid();
        $header = new webgui();
        $header->headerRealTimelogSquid();
        $header->modalFilterConf();
    ?>
    </div><br/>
    </body>
</html>
