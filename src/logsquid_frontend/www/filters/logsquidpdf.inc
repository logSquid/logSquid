<?php
$PATHS = array('class','css','js','img','functions','settings','realtime','filters','report','daemon','webgui','lang','graph','tmp','user');
$WWW = str_replace($PATHS, "", dirname(__FILE__));
require_once("{$WWW}functions/autoload.php");

class logsquidpdf{
    var $where ;
    var $settings;
    var $logsquid;
    
    public function __construct($where,$settings) {
        //, $view,$search,$typefilter,$pdfname
        $this->where = $where;
        $this->settings = $settings;
    }
    public function createStructure(){
        $this->logsquid = new logsquid();
        $this->logsquid->where = $this->where;
        $this->logsquid->numlimit = $this->settings['showpg'];
        $this->logsquid->goto = $this->settings['goto'];
        
        $this->headerPDF();
        $this->tableFilterPDF();
        $this->footerPDF();
    }
    public function headerPDF(){
        $typefilter = explode(",",$this->settings['typefilter']);
        $search = explode(",", $this->settings['search']);
        echo "
            <html>
                <head>
                    <title>PDF</title>
                    <meta charset=\"utf-8\" />
                    <link href=\"../css/logsquidpdf.css\" rel=\"stylesheet\" type=\"text/css\"/>
                </head>
                <body>
                    <div class=\"headerPDF\">
                        <span><img src=\"../img/logsquid-dark.jpg\"/></span>
                    </div>
                    <div class=\"container container-pdf\" style=\"margin-bottom: 10px;\">
                    <span>Filtered</span>
                    <table class=\"table table-header\">
                        <thead>
                            <tr>
                                <th>of</th>
                                <th>between</th>
                                <th>and</th>
                                <th>to</th>
        ";
                for($t = 0; $t < count($typefilter); $t++){
                        echo "<th>{$typefilter[$t]}</th>";
                }
        echo "
                            </tr>
                        </thead>
                        <tbody>
                            <tr>
                            <td>{$this->settings['datestart']}</td>
                            <td>{$this->settings['timestart']}</td>
                            <td>{$this->settings['timeend']}</td>
                            <td>{$this->settings['dateend']}</td>
        ";
                for($s = 0; $s < count($typefilter); $s++){
                    echo "<td>{$search[$s]}</td>";
                }
        echo "          </tr>
                        </tbody>
                    </table>
                    </div>
                    <div class=\"container container-pdf\" style=\"margin-top: 5px;\">
                ";
    }
    public function tableFilterPDF(){
        $this->logsquid->PDFselectLog($this->settings);
    }
    public function footerPDF(){
        echo "
                    </div>
                </body>
            </html>
            ";
    }
    
}
