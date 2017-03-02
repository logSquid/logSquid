<?php
    $Session = new Session();
    if($Session->valid() == FALSE){
        header("Location: ".BASEURL."login.php");
        exit();
    }
    if(time() > $Session->getField('last_act')){
        session_regenerate_id(TRUE);
    }
    $Session->setField('last_act', time());
    clearstatcache();
?>
<head>
    <title>logSquid</title>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8"/> 
    <!-- no cache headers -->
    <meta http-equiv="cache-control" content="no-cache" />
    <meta http-equiv="pragma" content="no-cache" />
    <meta http-equiv="expires" content = "-1" />
    <!-- end no cache headers -->
    
    <link href="<?php echo BASEURL.CSS ?>bootstrap.css" rel="stylesheet" type="text/css"/>
    <link href="<?php echo BASEURL.CSS ?>logSquid.css" rel="stylesheet" type="text/css"/>
    <link href="<?php echo BASEURL.CSS ?>msgbox.css" rel="stylesheet" type="text/css"/>
    <link href="<?php echo BASEURL.CSS ?>fontawesome.css" rel="stylesheet">
    <link href="<?php echo BASEURL.CSS ?>dropdowns-enhancement.css"  rel="stylesheet" type="text/css"/>
    <link href="<?php echo BASEURL.CSS ?>htmlinput.css"  rel="stylesheet" type="text/css"/>
    <link href="<?php echo BASEURL.CSS ?>bootstrap-datetimepicker.css" rel="stylesheet"/>

    <script type="text/javascript" src="<?php echo BASEURL.JS ?>jquery.js"></script>
    <script type="text/javascript" src="<?php echo BASEURL.JS ?>bootstrap.js"></script>
    <script type="text/javascript" src="<?php echo BASEURL.JS ?>msgbox.js"></script>
    <script type="text/javascript" src="<?php echo BASEURL.JS ?>dropdown.js"></script>
    <script type="text/javascript" src="<?php echo BASEURL.WEB ?>functions.js"></script>
    <script type="text/javascript" src="<?php echo BASEURL.JS ?>dropdowns-enhancement.js"></script>
    <script type="text/javascript" src="<?php echo BASEURL.WEB ?>searchtable.js"></script>
    <script type="text/javascript" src="<?php echo BASEURL.JS ?>bootstrap-datetimepicker.js"></script>
    <script type="text/javascript" src="<?php echo BASEURL.JS ?>easter.js"></script>
    <script type="text/javascript">
        $(document).ready(function(){
            $("tr").click(function(){
                var id = $(this).attr("id");
                $("#"+id+"m1").toggle();
                $("#"+id+"m2").toggle();
            });
            $("#btn-logout").click(function(ev){
                $.post("<?php echo BASEURL.USER."conectuser.php"; ?>",{action: "logout"},
                function(){
                    location.href="<?php echo BASEURL."login.php" ?>";
                });
                ev.preventDefault();
            });
        });
    </script>
    </head>
    <?php
        if($Session->getField("theme") == "Dark"){
            ?><body class="dark-theme"><?php
        }
        else{
            ?><body><?php
        }
    ?>
<nav class="navbar navbar-inverse navbar-fixed-top">
    <div class="container container-fluid">
      <div class="navbar-header">
          <a class="navbar-brand" href="<?php echo BASEURL; ?>"><img src="<?php echo BASEURL.IMG ?>logsquid.png"/></a>
      </div>
      <div id="navbar" class="navbar-collapse collapse">
        <ul class="nav navbar-nav">
            <li id="realtime"><a href="<?php echo BASEURL.REALTIME; ?>"><span  class="bt-header glyphicon glyphicon-time"></span>Dados Recentes</a></li>
            <li id="filter"><a href="<?php echo BASEURL.FILTERS; ?>"> <span class="bt-header glyphicon glyphicon-filter"></span>Filtros</a></li>
            <li id="report"><a href="<?php echo BASEURL.REPORT; ?>"> <span class="bt-header glyphicon glyphicon-duplicate"></span>Relat&oacute;rios</a></li>
        </ul>
          <ul class="nav navbar-nav navbar-right">
              <li>
                  <span class="area-username">
                      <?php
                        if($_SESSION['nickname'] != NULL){
                            echo "{$_SESSION['nickname']} ({$_SESSION['username']})";
                        }
                        else{
                            echo "{$_SESSION['username']}";
                        }
                      ?>
                  </span>
              </li>
              <li id="config"><a href="<?php echo BASEURL.SET; ?>" class="glyphicon glyphicon-cog"></a></li>
              <li id="logout"><a href="#" id="btn-logout" class="glyphicon glyphicon-log-out"></a></li>
          </ul>
      </div>
    </div>
</nav>
<div class="areaMsg" id="area-msg"></div>
<div class="areaScript"></div>
<div class="areaLoading" id="area-loading"></div>