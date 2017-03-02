<?php require_once ("../functions/autoload.php"); ?>
<html>
    <?php require_once ("../".WEB."header.php");?>
    <script type="text/javascript" src="report.js"></script>
    <script type="text/javascript" src="<?PHP echo BASEURL.JS; ?>masonry.js"></script>
    <script type="text/javascript" src="./gTablePdf.js"></script>
    <script type="text/javascript" src="./gTableGraph.js"></script>
    <script type="text/javascript" src="./ExportGraph.js"></script>
    <script type="text/javascript">
        $(document).ready(function(){
            $("#report").attr("class","active");
        });
    </script>
        <div class="container container-geral">
        <?php
            $logsquid = new logsquid();
            $header = new webgui();
            $header->headerReport($logsquid->typelog);
            $report = new report();
        ?>
        </div><br/>
        <div class="container">
            <?php
            if(isset($_REQUEST['d'])){
                $my = $_GET['d'];
            }
            else{
                $my = date("n-Y-j");
            }
            ?><input type="hidden" value="<?php echo $my; ?>" id="report-day" /><?php
            if(isset($_GET['detail'])){
            ?>
                <div class="container-detail">
                    <?php 
                        $report->listDetails($_REQUEST['detail'].".".$my);
                    ?>
                </div>
            <?php
            }
            else {
                ?><div class="grid">
                    <?php
                        $report->Dashboard($my);
                    ?>
                </div><?php
            }
        ?>
        </div>
        <?php
            $header->modalGraphDashboard();
            $header->modalCalendar();
            $report->modalReport();
            if(isset($_GET['show'])){
                ?>
                <script type="text/javascript">
                    $(document).ready(function(){
                        show = "<?php echo $_GET['show']; ?>";
                        id = $("#"+show).attr("data-id");
                        $("#"+id).toggle();
                    });
                </script>
                <?php
            }
            $header->ExportDetails();
            $header->modalExportGraphDashBoard();
        ?>
        <div id='area-TableExport'></div>
        <div id="teste"></div>
    </body>
</html>