<?php
class webgui{
    
    function headerReport($typelog){
        $this->headerReportlogSquid();
    }
    
    protected function headerReportSquid(){
        
    }
    
    protected function headerReportlogSquid(){
    ?>
    <div class="area-report">
        <div class="area-details">
            <div class="report-back">
                <?php
                if(isset($_REQUEST['detail'])){
                    ?><a href="?d=<?php echo $_REQUEST['d']; ?>" class="bt-back"><span class="glyphicon glyphicon-arrow-left"></span></a><?php
                }
                ?>
            </div>
            <div class="report-info">
                <a href="#" class="" data-toggle="modal" data-target=".calendar-report">
                    Mostrando detalhes de 
                    <?php 
                        if(isset($_REQUEST['d'])){
                            $date = explode("-", $_REQUEST['d']);
                            if(count($date) == 3){
                                echo "{$this->showMonth($date[0])} {$date[2]}, {$date[1]}";
                            }
                            elseif(count($date == 2)){
                                echo "{$this->showMonth($date[0])} {$date[1]}";
                            }
                        }
                        else{
                            $date = explode("-", date("d-n-Y"));
                            echo "{$this->showMonth($date[1])} {$date[0]}, {$date[2]}";
                        }
                    ?>
                    &nbsp;<span class="glyphicon glyphicon-calendar" aria-hidden="true"></span>
                </a>
            </div>
            <div class="report-details">
                <?php
                if(isset($_REQUEST['detail'])){
                    echo "{$this->showReport($_REQUEST['detail'])}";
                }
                ?>
            </div>
        </div>
        <div class="area-export">
            <?php
                if(isset($_REQUEST['detail'])){?>
                    <div class="exportfile">
                        <button class="btn btn-primary bt-export" id="export-details" data-toggle="modal" data-target=".export-details"><span class="glyphicon glyphicon-file"></span>Exportar</button>
                    </div>
                <?php }
                elseif (!isset($_REQUEST['detail'])) { ?>
                    <button class="btn btn-default bt-export" id="remove-report"><span class="glyphicon glyphicon-remove"></span>&nbsp;Remover</button>
                    <button class="btn btn-default bt-export" id="generate-report"><span class="glyphicon glyphicon-refresh"></span>&nbsp;Gerar</button>
                <?php }
            ?>
        </div>
    </div>
    <?php
    }
    public function modalGraphDashboard(){
    ?>
    <div class="modal fade dashboard-graph" tabindex="-1" role="dialog" aria-labelledby="dashboard-graph">
        <div class="modal-dialog modal-lg area-db-graph">
            <div class="modal-content">
                <div class="modal-header">
                    <button type="button" class="close" data-dismiss="modal" aria-label="Close" id="closeModalGraph"><span aria-hidden="true">×</span></button>
                    <h4 class="modal-title text-primary" id="title-report">Gr&aacute;fico - <span id="typegraph-text"></span></h4>
                </div>
                <div class="modal-body modal-body-graph">
                    <div class="modal-img-graph"></div>
                </div>
                <div class="modal-footer">
                    <div class="optionsGraph-left">
                        <form name="optionsGraph" id="optionsGraph">
                            <div class="form-inline">
                                <div class="form-group">
                                    <label>Largura</label>
                                    <input type="text" class="form-control" id="widthGraph" value="" />
                                </div>
                                <div class="form-group">
                                    <label>Altura</label>
                                    <input type="text" class="form-control" id="heightGraph" value="" />
                                </div>
                                <div class="form-group">
                                    <label>Tipo</label>
                                    <select id="typeGraph" class="form-control">
                                        <option value="bars">Barras</option>
                                        <option value="thinbarline">Barras Finas</option>
                                        <option value="lines">Linhas</option>
                                        <option value="linepoints">Linhas e Pontos</option>
                                        <option value="area">&Aacute;rea</option>
                                        <option value="points">Pontos</option>
                                    </select>
                                </div>
                                <div class="form-group">
                                    <input type="submit" value="Gerar Gr&aacute;fico" class="btn btn-primary" id="generate-graph" />
                                </div>
                            </div>
                        </form>
                    </div>
                    <div class="optionsGraph-right">
                        <button class="btn btn-primary bt-export" id="export-graph-dashboard" data-toggle="modal" data-target=".export-graph-dashboard"><span class="glyphicon glyphicon-file"></span>Exportar PDF</button>
                    </div>
                </div>
            </div>
        </div>
    </div>
    <?php
    }
    public function modalExportGraphDashBoard(){
    ?>
    <div class="modal fade export-graph-dashboard" tabindex="-1" role="dialog" aria-labelledby="myLargeModalLabel">
        <div class="modal-dialog modal-lg">
            <div class="modal-content">
                <div class="modal-header">
                  <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">×</span></button>
                  <h4 class="modal-title text-primary" id="myLargeModalLabel">Exportar este Gr&aacute;fico</h4>
                </div>
                <div class="modal-body" style="padding: 15px;">
                    <fieldset class="scheduler-border"><h4 class="text-info">PDF</h4>
                        <div style="padding-left: 20px;">
                            <div class="form-group col-sm-4">
                                <div class="input-group">
                                    <span class="input-group-addon">Formato</span>
                                    <select name="format" id="format" class="form-control">
                                        <option value="4A0">4A0</option>
                                        <option value="">2A0</option>
                                        <option value="2A0">A0</option>
                                        <option value="A1">A1</option>
                                        <option value="A2">A2</option>
                                        <option value="A3">A3</option>
                                        <option value="A4" selected>A4</option>
                                        <option value="A5">A5</option>
                                        <option value="A6">A6</option>
                                        <option value="A7">A7</option>
                                        <option value="A8">A8</option>
                                        <option value="A9">A9</option>
                                        <option value="A10">A10</option>
                                        <option value="B0">B0</option>
                                        <option value="B1">B1</option>
                                        <option value="B2">B2</option>
                                        <option value="B3">B3</option>
                                        <option value="B4">B4</option>
                                        <option value="B5">B5</option>
                                        <option value="B6">B6</option>
                                        <option value="B7">B7</option>
                                        <option value="B8">B8</option>
                                        <option value="B9">B9</option>
                                        <option value="B10">B10</option>
                                        <option value="C0">C0</option>
                                        <option value="C1">C1</option>
                                        <option value="C2">C2</option>
                                        <option value="C3">C3</option>
                                        <option value="C4">C4</option>
                                        <option value="C5">C5</option>
                                        <option value="C6">C6</option>
                                        <option value="C7">C7</option>
                                        <option value="C8">C8</option>
                                        <option value="C9">C9</option>
                                        <option value="C10">C10</option>
                                        <option value="RA0">RA0</option>
                                        <option value="RA1">RA1</option>
                                        <option value="RA2">RA2</option>
                                        <option value="RA3">RA3</option>
                                        <option value="RA4">RA4</option>
                                        <option value="SRA0">SRA0</option>
                                        <option value="SRA1">SRA1</option>
                                        <option value="SRA2">SRA2</option>
                                        <option value="SRA3">SRA3</option>
                                        <option value="SRA4">SRA4</option>
                                        <option value="LETTER">LETTER</option>
                                        <option value="LEGAL">LEGAL</option>
                                        <option value="EXECUTIVE">EXECUTIVE</option>
                                        <option value="FOLIO">FOLIO</option>
                                        <option value="DEMY">DEMY</option>
                                        <option value="ROYAL">ROYAL</option>
                                    </select>
                                </div>
                            </div>
                            <div class="form-group col-sm-6">
                                <div class="input-group" style="padding-left: 20px;">
                                    <span class="input-group-addon" style="text-transform: uppercase">Orienta&ccedil;&atilde;o:</span>
                                    <span class="input-group-addon">
                                        <label style="padding-left: 20px;padding-top: 5px">
                                            <input type="radio" value="-L" name="orientation" class="input-radio" id="portrait" checked />
                                            &nbsp;Paisagem
                                        </label>
                                        <label style="padding-left: 10px;padding-top: 5px">
                                            <input type="radio" value="" name="orientation" class="input-radio" id="portrait" />
                                            &nbsp;Retrato
                                        </label>
                                    </span>
                                </div>
                            </div>
                        </div>
                        <div class="form-group col-sm-5">
                            <button class="btn btn-primary" name="generate-pdf" id="graph-generate-pdf"><span class="glyphicon glyphicon-ok"></span>&nbsp;Gerar PDF</button>
                        </div>
                    </fieldset>
                    <div id="area-download-graph" class="area-download"></div>
                </div>
            </div>
        </div>
    </div>
    <?php
    }
    public function modalCalendar(){
        $report = new report();
    ?>
    <div class="modal fade calendar-report" tabindex="-1" role="dialog" aria-labelledby="calendar-report">
            <div class="modal-dialog modal-lg">
                <div class="modal-content">
                    <div class="modal-header">
                        <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">×</span></button>
                        <h4 class="modal-title text-primary" id="title-report">Calend&aacute;rio do Relat&oacute;rio</h4>
                    </div>
                    <div class="modal-body" style="padding: 15px; text-align: center">
                        <div class="header-calendar">
                            <table class="table table-calendar" style="border: 0px !important;">
                                <tr>
                                    <th class="title-calendar"><button class="bt-pncalendar" id="bt-prev"><span class="glyphicon glyphicon-triangle-left" aria-hidden="true"></span></button></th>
                                    <th class="title-calendar" colspan="5" id="month-year"></th>
                                    <th class="title-calendar"><button class="bt-pncalendar" id="bt-next"><span class="glyphicon glyphicon-triangle-right" aria-hidden="true"></span></button></th>
                                </tr>
                            </table>
                        </div>
                        <div id="calendar-area">
                            <?php 
                                $report->calendar();
                            ?>
                        </div>
                    </div>
                    <div class="modal-footer">
                        <span class="sreporttrue">Relat&oacute;rio gerado</span>
                        <button type="button" class="btn btn-default" data-dismiss="modal">Fechar</button>
                    </div>
                </div>
            </div>
        </div>
    <?php
    }
    
    public function exportsModReport(){
        
        /*$this->HtmlToPDFReport();
        $this->HtmlReport();*/
    }
    
    public function ExportDetails(){
    ?>
    <div class="modal fade export-details" tabindex="-1" role="dialog" aria-labelledby="myLargeModalLabel">
            <div class="modal-dialog modal-lg">
                <div class="modal-content">
                    <div class="modal-header">
                      <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">×</span></button>
                      <h4 class="modal-title text-primary" id="myLargeModalLabel">Exportar este Relat&oacute;rio</h4>
                    </div>
                    <div class="modal-body" style="padding: 15px;">
                        <fieldset class="scheduler-border"><h4 class="text-info">PDF</h4>
                            <div style="padding-left: 20px;">
                                <div class="form-group col-sm-4">
                                    <div class="input-group">
                                        <span class="input-group-addon">Formato</span>
                                        <select name="format" id="format" class="form-control">
                                            <option value="4A0">4A0</option>
                                            <option value="">2A0</option>
                                            <option value="2A0">A0</option>
                                            <option value="A1">A1</option>
                                            <option value="A2">A2</option>
                                            <option value="A3">A3</option>
                                            <option value="A4" selected>A4</option>
                                            <option value="A5">A5</option>
                                            <option value="A6">A6</option>
                                            <option value="A7">A7</option>
                                            <option value="A8">A8</option>
                                            <option value="A9">A9</option>
                                            <option value="A10">A10</option>
                                            <option value="B0">B0</option>
                                            <option value="B1">B1</option>
                                            <option value="B2">B2</option>
                                            <option value="B3">B3</option>
                                            <option value="B4">B4</option>
                                            <option value="B5">B5</option>
                                            <option value="B6">B6</option>
                                            <option value="B7">B7</option>
                                            <option value="B8">B8</option>
                                            <option value="B9">B9</option>
                                            <option value="B10">B10</option>
                                            <option value="C0">C0</option>
                                            <option value="C1">C1</option>
                                            <option value="C2">C2</option>
                                            <option value="C3">C3</option>
                                            <option value="C4">C4</option>
                                            <option value="C5">C5</option>
                                            <option value="C6">C6</option>
                                            <option value="C7">C7</option>
                                            <option value="C8">C8</option>
                                            <option value="C9">C9</option>
                                            <option value="C10">C10</option>
                                            <option value="RA0">RA0</option>
                                            <option value="RA1">RA1</option>
                                            <option value="RA2">RA2</option>
                                            <option value="RA3">RA3</option>
                                            <option value="RA4">RA4</option>
                                            <option value="SRA0">SRA0</option>
                                            <option value="SRA1">SRA1</option>
                                            <option value="SRA2">SRA2</option>
                                            <option value="SRA3">SRA3</option>
                                            <option value="SRA4">SRA4</option>
                                            <option value="LETTER">LETTER</option>
                                            <option value="LEGAL">LEGAL</option>
                                            <option value="EXECUTIVE">EXECUTIVE</option>
                                            <option value="FOLIO">FOLIO</option>
                                            <option value="DEMY">DEMY</option>
                                            <option value="ROYAL">ROYAL</option>
                                        </select>
                                    </div>
                                </div>
                                <div class="form-group col-sm-6">
                                    <div class="input-group" style="padding-left: 20px;">
                                        <span class="input-group-addon" style="text-transform: uppercase">Orienta&ccedil;&atilde;o:</span>
                                        <span class="input-group-addon">
                                            <label style="padding-left: 20px;padding-top: 5px">
                                                <input type="radio" value="-L" name="orientationd" class="input-radio" id="landscape" checked="" />&nbsp;&nbsp;Paisagem
                                            </label>
                                            <label style="padding-left: 10px;padding-top: 5px">
                                                <input type="radio" value="" name="orientationd" class="input-radio" id="portrait" />&nbsp;&nbsp;Retrato
                                            </label>
                                        </span>
                                    </div>
                                </div>
                            </div>
                            <div class="form-group col-sm-5">
                                <button class="btn btn-primary" name="generate-pdf" id="report-generate-pdf"><span class="glyphicon glyphicon-ok"></span>&nbsp;Gerar PDF</button>
                            </div>
                        </fieldset>

                        <fieldset class="scheduler-border"><h4 class="text-info">HTML</h4>
                            <div class="form-group col-sm-5">
                                <button class="btn btn-primary" name="generate-pdf" id="report-generate-html"><span class="glyphicon glyphicon-ok"></span>&nbsp;Gerar HTML</button>
                            </div>
                        </fieldset>
                        <div id="report-area-download" class="area-download"></div>
                    </div>
                </div>
            </div>
        </div>
    <?php
    }
    
    /*
    protected function HtmlReport(){
    ?>
        <div class="modal fade bs-export-html" tabindex="-1" role="dialog" aria-labelledby="myLargeModalLabel">
            <div class="modal-dialog modal-lg">
                <div class="modal-content">
                    <form id="export-to-html" class="form-horizontal">
                    <div class="modal-header">
                        <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">×</span></button>
                        <h4 class="modal-title text-primary" id="myLargeModalLabel">Exportar o filtro para HTML</h4>
                    </div>
                        <div class="modal-body" style="padding: 15px">
                            <fieldset class="scheduler-border"><h4 class="text-info">Configurar HTML</h4>
                                <div style="padding-left: 20px;">
                                    <div class="form-group col-sm-5">
                                        <div class="input-group">
                                            <span class="input-group-addon" id="basic-addon1">Nome</span>
                                            <input type="text" class="form-control" name="htmlname" id="htmlname" />
                                            <span class="input-group-addon">.html</span>
                                        </div>
                                    </div>
                                    <div class="form-group col-sm-7">
                                        <span class="text-danger" style="padding-left: 20px;">*n&atilde;o use espa&ccedil;o, caracteres especiais ou n&uacute;meros no nome do arquivo</span>
                                    </div>
                                </div>
                            </fieldset>
                        </div>
                        <div class="modal-footer">
                            <button class="btn btn-primary" name="generate-html" id="generate-html"><span class="glyphicon glyphicon-ok"></span>&nbsp;Gerar HTML</button>
                            <span id="area-downloadHTML" class="area-download">
                                <a href="" id="btn-downloadHTML" class="btn btn-default" target="_blank">Download</a>
                                <button class="btn btn-default" data-file="" id="deleteFileHTML">Remover</button>
                            </span>
                        </div>
                    </form>
                </div>
            </div>
        </div>
    <?php
    }
    
    protected function HtmlToPDFReport(){
    ?>
        <div class="modal fade bs-export-pdf" tabindex="-1" role="dialog" aria-labelledby="myLargeModalLabel">
            <div class="modal-dialog modal-lg">
                <div class="modal-content">
                    <form id="export-to-pdf" class="form-horizontal">
                        <div class="modal-header">
                          <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">×</span></button>
                          <h4 class="modal-title text-primary" id="myLargeModalLabel">Exportar este relat&oacute;rio para PDF</h4>
                        </div>
                        <div class="modal-body" style="padding: 15px;">
                            <fieldset class="scheduler-border"><h4 class="text-info">PDF</h4>
                                <div style="padding-left: 20px;">
                                    <div class="form-group col-sm-5">
                                        <div class="input-group">
                                            <span class="input-group-addon">Formato</span>
                                            <select name="format" id="format" class="form-control">
                                                <option value="4A0">4A0</option>
			<option value="">2A0</option>
			<option value="2A0">A0</option>
			<option value="A1">A1</option>
			<option value="A2">A2</option>
			<option value="A3">A3</option>
                                                <option value="A4" selected>A4</option>
                                                <option value="A5">A5</option>
			<option value="A6">A6</option>
			<option value="A7">A7</option>
			<option value="A8">A8</option>
			<option value="A9">A9</option>
			<option value="A10">A10</option>
			<option value="B0">B0</option>
			<option value="B1">B1</option>
			<option value="B2">B2</option>
			<option value="B3">B3</option>
			<option value="B4">B4</option>
			<option value="B5">B5</option>
			<option value="B6">B6</option>
			<option value="B7">B7</option>
			<option value="B8">B8</option>
			<option value="B9">B9</option>
			<option value="B10">B10</option>
			<option value="C0">C0</option>
			<option value="C1">C1</option>
			<option value="C2">C2</option>
			<option value="C3">C3</option>
			<option value="C4">C4</option>
			<option value="C5">C5</option>
			<option value="C6">C6</option>
			<option value="C7">C7</option>
			<option value="C8">C8</option>
			<option value="C9">C9</option>
			<option value="C10">C10</option>
			<option value="RA0">RA0</option>
			<option value="RA1">RA1</option>
			<option value="RA2">RA2</option>
			<option value="RA3">RA3</option>
			<option value="RA4">RA4</option>
			<option value="SRA0">SRA0</option>
			<option value="SRA1">SRA1</option>
			<option value="SRA2">SRA2</option>
			<option value="SRA3">SRA3</option>
			<option value="SRA4">SRA4</option>
			<option value="LETTER">LETTER</option>
			<option value="LEGAL">LEGAL</option>
			<option value="EXECUTIVE">EXECUTIVE</option>
			<option value="FOLIO">FOLIO</option>
			<option value="DEMY">DEMY</option>
			<option value="ROYAL">ROYAL</option>
                                            </select>
                                        </div>
                                    </div>
                                    <div class="form-group col-sm-5">
                                        <div class="input-group" style="padding-left: 20px;">
                                            <span class="input-group-addon">Orienta&ccedil;&atilde;o</span>
                                            <span class="input-group-addon">
                                                <label style="padding-left: 20px;padding-top: 5px">
                                                    <input type="radio" value="-L" name="orientation" id="orientation" checked />
                                                    &nbsp;Paisagem
                                                </label>
                                                <label style="padding-left: 10px;padding-top: 5px">
                                                    <input type="radio" value="" name="orientation" id="orientation" />
                                                    &nbsp;Retrato
                                                </label>
                                            </span>
                                        </div>
                                    </div>
                                    <div class="form-group col-sm-5">
                                        <div class="input-group">
                                            <span class="input-group-addon" id="basic-addon1">Nome</span>
                                            <input type="text" class="form-control" name="pdfname" id="pdfname" />
                                            <span class="input-group-addon">.pdf</span>
                                        </div>
                                    </div>
                                    <div class="form-group col-sm-7">
                                        <span class="text-danger" style="padding-left: 20px;">*n&atilde;o use espa&ccedil;o, caracteres especiais ou n&uacute;meros no nome do arquivo</span>
                                    </div>
                                </div>
                            </fieldset>
                        </div>
                        <div class="modal-footer">
                            <button class="btn btn-primary" name="generate-pdf" id="generate-pdf"><span class="glyphicon glyphicon-ok"></span>&nbsp;Gerar PDF</button>
                            <span id="area-download" class="area-download">
                                <a href="" id="btn-download" class="btn btn-default" target="_blank">Download</a>
                                <button class="btn btn-default" data-file="" id="deleteFile">Remover</button>
                            </span>
                        </div>
                    </form>
                </div>
            </div>
        </div>
    <?php
    }
    */   
    function headerFilter($typelog){
        $this->headerFilterlogSquid();
    }
    protected function headerFilterSquid(){
    ?>
    <div class="area-search area-search-r">
        <div class="searchfilter">
            <div class="input-group">
                <div class="input-group-btn">
                    <button class="btn btn-primary" data-label-placement id='lfilter'>Escolha uma ou mais op&cedil;&otilde;es</button>
                    <button class="btn btn-primary" data-toggle="dropdown">&nbsp;<span class="caret"></span>&nbsp;</button>
                    <ul class="dropdown-menu">
                        <li>
                            <input type="checkbox" id="client" name="typefilter" value="client">
                            <label for="client">IP</label>
                        </li>
                        <li>
                            <input type="checkbox" id="user" name="typefilter" value="user">
                            <label for="user">Usu&aacute;rio</label>
                        </li>
                        <li>
                            <input type="checkbox" id="url" name="typefilter" value="url">
                            <label for="url">URL</label>
                        </li>
                        <li>
                            <input type="checkbox" id="action" name="typefilter" value="action" >
                            <label for="action">Status</label>
                        </li>
                        <li>
                            <input type="checkbox" id="mime" name="typefilter" value="mime" >
                            <label for="mime">Tipo de Arquivo</label>
                        </li>
                    </ul>
                </div>
                <input type="text" class="form-control " id='fieldfilter' />
                <span class="input-group-addon calendar" id='bt-filter'>
                    <span class="glyphicon glyphicon-search"></span>
                </span>
            </div>
        </div>
        <div class="datefilter">
            <div class='input-group date' id='datestart'>
                <span class="input-group-addon calendar">
                    <span class="glyphicon glyphicon-calendar"></span>
                    de
                </span>
                <input type='text' class="form-control" id='fDatestart' value="<?php echo date("Y-m-d"); ?>" />
            </div>
        </div>
        <div class="timefilter">
            <div class='input-group'>
                <span class="input-group-addon calendar">
                    <span class="glyphicon glyphicon-time"></span>
                    entre
                </span>
                <input type='text' class="form-control" id='timestart' value="00:00:00" />
            </div>
        </div>
        <div class="timefilter">
            <div class='input-group'>
                <span class="input-group-addon calendar">
                    <span class="glyphicon glyphicon-time"></span>
                    e
                </span>
                <input type='text' class="form-control" value="23:59:59" id='timeend' />
            </div>
        </div>
        <div class="datefilter">
            <div class='input-group date' id='dateend'>
                <span class="input-group-addon calendar">
                    <span class="glyphicon glyphicon-calendar"></span>
                    at&eacute;
                </span>
                <input type='text' class="form-control" id='fDateend' value="<?php echo date("Y-m-d"); ?>" />
            </div>
        </div>
    </div>
    <?php
    }
    
    protected function headerFilterlogSquid(){
    ?>
    <div class="area-search area-search-r">
        
        <div class="search-datetime">
            <div class='input-group date'>
                <span class="input-group-addon calendar" id="Sdatetime">
                    <span class="glyphicon glyphicon-calendar"></span><span class="glyphicon glyphicon-time"></span>de
                </span>
                <input type="text" value="<?php echo date("Y-m-d 00:00:00"); ?>" class="form-control" id="datetime-start">
            </div>
        </div>
        <div class="search-datetime">
            <div class='input-group date'>
                <span class="input-group-addon calendar" id="Edatetime">
                    <span class="glyphicon glyphicon-calendar"></span><span class="glyphicon glyphicon-time"></span>at&eacute;
                </span>
                <input type="text" value="<?php echo date("Y-m-d 23:59:59"); ?>" class="form-control" id="datetime-end">
            </div>
        </div>
        <div class="search-list-agents">
            <div class="input-group-btn">
                <button class="btn btn-primary" data-label-placement id='lagents'>Agentes</button>
                <button class="btn btn-primary" id="lagentsd" data-toggle="dropdown">&nbsp;<span class="caret"></span>&nbsp;</button>
                <ul class="dropdown-menu">
                    <li>
                        <input type="radio" id="all" name="typeagent" value="">
                        <label for="all">Todos</label>
                    </li>
                    <?php
                        $Services = new Services();
                        $Services->getAgentsFilters();
                    ?>
                </ul>
            </div>
        </div>
        <div class="searchfilter">
            <div class="input-group">
                <div class="input-group-btn">
                    <button class="btn btn-primary" data-label-placement id='lfilter'>Filtros</button>
                    <button class="btn btn-primary" data-toggle="dropdown">&nbsp;<span class="caret"></span>&nbsp;</button>
                    <ul class="dropdown-menu">
                        <li>
                            <input type="checkbox" id="ipuser" name="typefilter" value="ipuser">
                            <label for="ipuser">IP</label>
                        </li>
                        <li>
                            <input type="checkbox" id="macaddress" name="typefilter" value="macaddress">
                            <label for="macaddress">Mac Address</label>
                        </li>
                        <li>
                            <input type="checkbox" id="username" name="typefilter" value="username">
                            <label for="username">Usu&aacute;rio</label>
                        </li>
                        <li>
                            <input type="checkbox" id="destination" name="typefilter" value="destination">
                            <label for="destination">Site</label>
                        </li>
                        <li>
                            <input type="checkbox" id="url" name="typefilter" value="url">
                            <label for="url">URL</label>
                        </li>
                        <li>
                            <input type="checkbox" id="ipdest" name="typefilter" value="ipdest">
                            <label for="ipdest">IP destino</label>
                        </li>
                        <li>
                            <input type="checkbox" id="mime" name="typefilter" value="mime" >
                            <label for="mime">Tipo de arquivo</label>
                        </li>
                        <li>
                            <input type="checkbox" id="size" name="typefilter" value="size" >
                            <label for="size">Tamanho</label>
                        </li>
                        <li>
                            <input type="checkbox" id="status" name="typefilter" value="status" >
                            <label for="status">Status</label>
                        </li>
                    </ul>
                </div>
                <input type="text" class="form-control " id='fieldfilter' />
                <span class="input-group-addon calendar" id='bt-filter'>
                    <span class="glyphicon glyphicon-search"></span>
                </span>
            </div>
        </div>
        <div class="search-config">
            <div class="exportfile">
                <button class="btn btn-primary bt-export" id="export-filter" data-toggle="modal" data-target=".export-filter"><span class="glyphicon glyphicon-file"></span>Exportar</button>
            </div>
            <div class="confpage">
                <button name="confpage" id="bt-confpage" class="btn bt-confpage" data-toggle="modal" data-target=".modal-confpage"></button>
            </div>
            <div class="viewsql">
                <button name="viewsql" id="bt-viewsql" class="btn bt-viewsql"></button>
            </div>
        </div>
    </div>
    <?php
    }
    
    public function ExportFIlter(){
    ?>
    <div class="modal fade export-filter" tabindex="-1" role="dialog" aria-labelledby="myLargeModalLabel">
            <div class="modal-dialog modal-lg">
                <div class="modal-content">
                    <div class="modal-header">
                      <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">×</span></button>
                      <h4 class="modal-title text-primary" id="myLargeModalLabel">Exportar este filtro</h4>
                    </div>
                    <div class="modal-body" style="padding: 15px;">
                        <fieldset class="scheduler-border"><h4 class="text-info">PDF</h4>
                            <div style="padding-left: 20px;">
                                <div class="form-group col-sm-4">
                                    <div class="input-group">
                                        <span class="input-group-addon">Formato</span>
                                        <select name="format" id="format" class="form-control">
                                            <option value="4A0">4A0</option>
                                            <option value="">2A0</option>
                                            <option value="2A0">A0</option>
                                            <option value="A1">A1</option>
                                            <option value="A2">A2</option>
                                            <option value="A3">A3</option>
                                            <option value="A4" selected>A4</option>
                                            <option value="A5">A5</option>
                                            <option value="A6">A6</option>
                                            <option value="A7">A7</option>
                                            <option value="A8">A8</option>
                                            <option value="A9">A9</option>
                                            <option value="A10">A10</option>
                                            <option value="B0">B0</option>
                                            <option value="B1">B1</option>
                                            <option value="B2">B2</option>
                                            <option value="B3">B3</option>
                                            <option value="B4">B4</option>
                                            <option value="B5">B5</option>
                                            <option value="B6">B6</option>
                                            <option value="B7">B7</option>
                                            <option value="B8">B8</option>
                                            <option value="B9">B9</option>
                                            <option value="B10">B10</option>
                                            <option value="C0">C0</option>
                                            <option value="C1">C1</option>
                                            <option value="C2">C2</option>
                                            <option value="C3">C3</option>
                                            <option value="C4">C4</option>
                                            <option value="C5">C5</option>
                                            <option value="C6">C6</option>
                                            <option value="C7">C7</option>
                                            <option value="C8">C8</option>
                                            <option value="C9">C9</option>
                                            <option value="C10">C10</option>
                                            <option value="RA0">RA0</option>
                                            <option value="RA1">RA1</option>
                                            <option value="RA2">RA2</option>
                                            <option value="RA3">RA3</option>
                                            <option value="RA4">RA4</option>
                                            <option value="SRA0">SRA0</option>
                                            <option value="SRA1">SRA1</option>
                                            <option value="SRA2">SRA2</option>
                                            <option value="SRA3">SRA3</option>
                                            <option value="SRA4">SRA4</option>
                                            <option value="LETTER">LETTER</option>
                                            <option value="LEGAL">LEGAL</option>
                                            <option value="EXECUTIVE">EXECUTIVE</option>
                                            <option value="FOLIO">FOLIO</option>
                                            <option value="DEMY">DEMY</option>
                                            <option value="ROYAL">ROYAL</option>
                                        </select>
                                    </div>
                                </div>
                                <div class="form-group col-sm-6">
                                    <div class="input-group" style="padding-left: 20px;">
                                        <span class="input-group-addon" style="text-transform: uppercase">Orienta&ccedil;&atilde;o:</span>
                                        <span class="input-group-addon">
                                            <label style="padding-left: 20px;padding-top: 5px">
                                                <input type="radio" value="-L" name="orientation" class="input-radio" id="portrait" checked />
                                                &nbsp;Paisagem
                                            </label>
                                            <label style="padding-left: 10px;padding-top: 5px">
                                                <input type="radio" value="" name="orientation" class="input-radio" id="portrait" />
                                                &nbsp;Retrato
                                            </label>
                                        </span>
                                    </div>
                                </div>
                            </div>
                            <div class="form-group col-sm-5">
                                <button class="btn btn-primary" name="generate-pdf" id="filter-generate-pdf"><span class="glyphicon glyphicon-ok"></span>&nbsp;Gerar PDF</button>
                            </div>
                        </fieldset>

                        <fieldset class="scheduler-border"><h4 class="text-info">HTML</h4>
                            <div class="form-group col-sm-5">
                                <button class="btn btn-primary" name="generate-pdf" id="filter-generate-html"><span class="glyphicon glyphicon-ok"></span>&nbsp;Gerar HTML</button>
                            </div>
                        </fieldset>
                        <fieldset class="scheduler-border"><h4 class="text-info">CSV</h4>
                            <div class="form-group col-sm-5">
                                <button class="btn btn-primary" name="generate-pdf" id="filter-generate-csv"><span class="glyphicon glyphicon-ok"></span>&nbsp;Gerar CSV</button>
                            </div>
                        </fieldset>
                        <div id="area-download" class="area-download"></div>
                    </div>
                    <div class="modal-footer">
                        <span class="obs">* n&atilde;o escolha mais que 1000 linhas para exportar de uma só vez, voc&ecirc; pode comprometer a velocidade do seu navegador ou n&atilde;o conseguir gerar o arquivo.</span>
                    </div>
                </div>
            </div>
        </div>
    <?php
    }
            
    public function headerRealTimelogSquid(){
    ?>
    <div class="area-search area-search-r">
        <div class="search-list-agents">
            <div class="input-group-btn">
                <button class="btn btn-primary" data-label-placement id='lagents'>Agentes</button>
                <button class="btn btn-primary" id="lagentsd" data-toggle="dropdown">&nbsp;<span class="caret"></span>&nbsp;</button>
                <ul class="dropdown-menu">
                    <li>
                        <input type="radio" id="all" name="typeagent" value="">
                        <label for="all">Todos</label>
                    </li>
                    <?php
                        $Services = new Services();
                        $Services->getAgentsFilters();
                    ?>
                </ul>
            </div>
        </div>
        <div class="searchfilter">
            <div class="input-group">
                <input type="text" class="form-control " id='fieldfilter' />
                    <span class="input-group-addon calendar" id='bt-filter'>
                        <span class="glyphicon glyphicon-search"></span>
                    </span>
            </div>
        </div>
        <div class="optionsfilter">
            <div class="input-group">
                <span class="input-group-addon" style="width: 50%;">
                    <input type="range" value="20" max="400" min="10" step="10" id="rangelines" />
                </span>
                <input type="number" value="" max="400" min="10" step="10" class="form-control" id="showlines" style="text-align: center;" />
                <span class="input-group-addon" style="">Linhas</span>
            </div>
        </div>
        <div class="search-config">
            <div class="confpage">
                <button name="confpage" id="bt-confpage" class="btn bt-confpage" data-toggle="modal" data-target=".modal-confpage"></button>
            </div>
        </div>
    </div>
    <input type="hidden" id="fields" value="" name="fields" />
    <table id="listAccess" class="table table-hover">
        <thead>
            <tr>
                <th id="col-datetime">Data/Hora</th>
                <th id="col-ipuser">IP</th>
                <th id="col-macaddress">MAC Address</th>
                <th id="col-username">Usu&aacute;rio</th>
                <th id="col-destination">Destino</th>
                <th id="col-url">URL</th>
                <th id="col-ipdest" nowrap>IP Destino</th>
                <th id="col-mime">Tipo de arquivo</th>
                <th id="col-size">Tamanho</th>
                <th id="col-status" width="8%">Status</th>
            </tr>
        </thead>
        <tbody></tbody>
    </table>
    <?php
    }
    
    protected function showMonth($month){
        switch ($month){
            case "01":return "Janeiro";
            case "02":return "Fevereiro";
            case "03":return "Mar&ccedil;o";
            case "04":return "Abril";
            case "05": return "Maio";
            case "06": return "Junho";
            case "07": return "Julho";
            case "08": return "Agosto";
            case "09": return "Setembro";
            case "10": return "Outubro";
            case "11": return "Novembro";
            case "12": return "Dezembro";
        }
    }
    protected function showReport($report){
        switch ($report){
            case "accesssites": return "Sites acessados por IP e Usu&aacute;rio";
            case "deniedsites": return "Sites negados por IP e Usu&aacute;rio";
            case "accessurl": return "URL's acessados por IP e Usu&aacute;rio";
            case "deniedurl": return "URL's negados por IP e Usu&aacute;rio";
            case "aipuser": return "Acessos por IP";
            case "dipuser": return "Negados por IP";
            case "ausername": return "Acessos por Usu&aacute;rio";
            case "dusername": return "Negados por Usu&aacute;rio";
            case "mime": return "Consumo de Banda";
        }
    }
    public function FilterheaderReadlogSquid(){?>
        <div class="area-search">
            <div class="search">
                <input type="text" class="input-search form-control" alt="table" placeholder="Procurar por qualquer item na p&aacute;gina" />
            </div>
            <?php webgui::FiltershownPage(); ?>
        </div>
        <table id="listAccess" class="table table-hover">
                <thead>
                    <tr class="">
                        <th id="check"><button class="selectall" name="selectall" id="selectall" data-info="checkall"><span class="bt-selectall"></span></button></th>
                        <th id="col-datetime"><span class="text-order">Data/Hora</span><input type="radio" name="orderby" class="radio-orderby-descending" text-order="DESC" value="datetime" checked="checked" /></th>
                        <th id="col-ipuser"><span class="text-order">IP</span><input type="radio" name="orderby" class="radio-orderby-descending" value="ipuser" /></th>
                        <th id="col-macaddress"><span class="text-order">MAC Address</span><input type="radio" name="orderby" class="radio-orderby-descending" value="macaddress" /></th>
                        <th id="col-username"><span class="text-order">Usu&aacute;rio</span><input type="radio" name="orderby" class="radio-orderby-descending" value="username" /></th>
                        <th id="col-destination"><span class="text-order">Site</span><input type="radio" name="orderby" class="radio-orderby-descending" value="destination" /></th>
                        <th id="col-url"><span class="text-order">URL</span><input type="radio" name="orderby" class="radio-orderby-descending" value="url" /></th>
                        <th id="col-ipdest" nowrap><span class="text-order">IP destino</span><input type="radio" name="orderby" class="radio-orderby-descending" value="ipdest" /></th>
                        <th id="col-mime"><span class="text-order">Tipo</span><input type="radio" name="orderby" class="radio-orderby-descending" value="mime" /></th>
                        <th id="col-size"><span class="text-order">Tamanho</span><input type="radio" name="orderby" class="radio-orderby-descending" value="size" /></th>
                        <th id="col-status"><span class="text-order">Status</span><input type="radio" name="orderby" class="radio-orderby-descending" value="status" /></th>
                    </tr>
                </thead>
                <tbody>
                    <tr>
                        <td colspan="11" class="wfilter"><input type="hidden" value="null" name="searchnull"/>Nenhum pesquisa feita.</td>
                    </tr>
                </tbody>
        </table>
        <div class="area-search area-search-det">
            <div class="search">&nbsp;</div>
            <?php webgui::FiltershownPagef(); ?>
        </div>
        <?php
    }
    
    public function FiltershownPage(){
        ?>
        <div class="numpage" id="area-numpage">
            <div class="area-numpage">
                <span class="group-text group-text-border">
                    <span class="text-info"><b><input type="hidden" value="0" id="totalreg" /><span id="sTotalreg">0</span>&nbsp;</b></span>
                    <span class="text-info">registros</span>
                </span>
                <span class="group-text group-text-border">
                    <span class="text-info">exibir&nbsp;</span>
                    <span class="text-info"><input type="number" step="10" min="10" value="100" name="showpg" id="showpg" class="form-control input-showpg" /></span>
                </span>
                <span class="group-text">
                    <span class="text-info">ir p/&nbsp;</span>
                    <span class="text-info"><input type="number" value="1" min="1" max="1" name="goto" id="goto" class="form-control input-showpg" /></span>
                    <span class="text-info">de</span>
                    <span class="text-info"><b><input type="hidden" value="0" id="totalpg"/><span id="sTotalpg">0</span></b></span>
                </span>
            </div>
        </div>
    <?php
    }
    
    public function modalFilterConf(){
    ?>
    <div class="modal fade modal-confpage" tabindex="-1" role="dialog" aria-labelledby="myLargeModalLabel">
        <div class="modal-dialog modal-lg">
            <div class="modal-content">
                <div class="modal-header">
                  <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">×</span></button>
                  <h4 class="modal-title text-primary" id="myLargeModalLabel">Configurar p&aacute;gina</h4>
                </div>
                <div class="modal-body" style="padding: 15px;">
                    <h4 class="text-info">Visualizar</h4>
                    <div class="row">
                        <div class="col-xs-5 col-sm-3"><input type="checkbox" name="configpage" class="checkbox-ls" value="datetime" checked="" /><span class="text-primary">Data/Hora</span></div>
                        <div class="col-xs-5 col-sm-3"><input type="checkbox" name="configpage" class="checkbox-ls" value="ipuser" checked="" /><span class="text-primary">IP</span></div>
                        <div class="col-xs-5 col-sm-3"><input type="checkbox" name="configpage" class="checkbox-ls" value="macaddress" checked="" /><span class="text-primary">MAC Address</span></div>
                        <div class="col-xs-5 col-sm-3"><input type="checkbox" name="configpage" class="checkbox-ls" value="username" checked="" /><span class="text-primary">Usu&aacute;rio</span></div>
                        <div class="col-xs-5 col-sm-3"><input type="checkbox" name="configpage" class="checkbox-ls" value="destination" checked="" /><span class="text-primary">Site</span></div>
                        <div class="col-xs-5 col-sm-3"><input type="checkbox" name="configpage" class="checkbox-ls" value="url" checked="" /><span class="text-primary">URL</span></div>
                        <div class="col-xs-5 col-sm-3"><input type="checkbox" name="configpage" class="checkbox-ls" value="ipdest" checked="" /><span class="text-primary">IP Destino</span></div>
                        <div class="col-xs-5 col-sm-3"><input type="checkbox" name="configpage" class="checkbox-ls" value="mime" checked="" /><span class="text-primary">Tipo de Arquivo</span></div>
                        <div class="col-xs-5 col-sm-3"><input type="checkbox" name="configpage" class="checkbox-ls" value="size" checked="" /><span class="text-primary">Tamanho</span></div>
                        <div class="col-xs-5 col-sm-3"><input type="checkbox" name="configpage" class="checkbox-ls" value="status" checked="" /><span class="text-primary">Status</span></div>
                    </div>
                </div>
                <div class="modal-footer">
                    <button class="btn btn-primary" name="applyconf" id="applyconf"><span class="glyphicon glyphicon-ok"></span>&nbsp;Aplicar</button>
                </div>
            </div>
        </div>
    </div>
    <?php   
    }
    public function FiltershownPagef(){
    ?>
        <div class="numpage">
            <div class="area-numpage">
                <span class="group-text group-text-border">
                    <span class="text-info"><b><input type="hidden" value="0" id="totalregf" /><span id="sTotalregf">0</span>&nbsp;</b></span>
                    <span class="text-info">registros</span>
                </span>
                <span class="group-text group-text-border">
                    <span class="text-info">exibir&nbsp;</span>
                    <span class="text-info"><input type="number" step="10" min="10" value="100" name="showpgf" id="showpgf" class="form-control input-showpg" /></span>
                </span>
                <span class="group-text">
                    <span class="text-info">ir p/&nbsp;</span>
                    <span class="text-info"><input type="number" value="1" min="1" max="1" name="gotof" id="gotof" class="form-control input-showpg" /></span>
                    <span class="text-info">de</span>
                    <span class="text-info"><b><input type="hidden" value="0" id="totalpgf"/><span id="sTotalpgf">0</span></b></span>
                </span>
            </div>
        </div>
    <?php
    }
}