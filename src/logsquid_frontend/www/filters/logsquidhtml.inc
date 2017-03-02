<?php
$PATHS = array('class','css','js','img','functions','settings','realtime','filters','report','daemon','webgui','lang','graph','tmp','user');
$WWW = str_replace($PATHS, "", dirname(__FILE__));
require_once("{$WWW}functions/autoload.php");

class logsquidhtml{
    var $where;
    var $settings;
    var $logsquid;
    
    public function __construct($where, $settings) {
        $this->where = $where;
        $this->settings = $settings;
    }
    public function createStructure(){
        $this->logsquid = new logsquid();
        $this->logsquid->where = $this->where;
        
        $this->headerHTML();
        $this->tableFilterHTML();
        $this->footerFilterHTML();
    }
    protected function headerHTML(){
        $typefilter = explode(",", $this->settings['typefilter']);
        $search = explode(",", $this->settings['search']);
        echo "
            <html>
                <head>
                    <title>logSquid Filter - HTML</title>
                    <meta charset=\"utf-8\" />
                    <style type=\"text/css\">
                        *{
                            font-family: sans-serif;
                        }
                        table{
                            font-size: 0.8em;
                            color: #333;
                        }
                        .table{
                            position: relative;
                            width: 100%;
                            max-width: 100%;
                            border: 0px;
                            border-collapse: collapse !important;
                        }
                        .table-html tr td, .table-header tr td{
                            border-bottom: solid 1px #e0e0e0;
                            border-top: 0px;
                            border-right: 0px;
                            border-left: 0px;
                            padding: 5px 8px;
                        }
                        .table-html tr th{
                            background: #08c;
                            color: #fff;
                            padding: 5px 8px;
                            text-align: left;
                        }
                        .table-header tr th{
                            color: #666;
                            border-bottom: solid 1px #666;
                            padding: 5px 8px;
                            text-align: left;
                        }
                        .nowrap{
                            white-space: nowrap;
                        }
                        .break{
                            word-break: break-all;
                        }
                    </style>
                </head>
                <body>
                    <table class=\"table table-header\">
                        <thead>
                            <tr>
                                <th>of</th>
                                <th>between</th>
                                <th>and</th>
                                <th>to</th>
                ";
                    for($th = 0; $th < count($typefilter); $th++){
                        echo "<th>{$typefilter[$th]}</th>";
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
                    for($td = 0; $td < count($typefilter); $td++){
                        echo "<td>{$search[$td]}</td>";
                    }
        echo"
                            </td>
                        </tbody>
                    </table>
                </body>
            </html>
            ";
    }
    protected function tableFilterHTML(){
        $this->logsquid->HTMLselectLog($this->settings);
    }
    protected function footerFilterHTML(){
        
    }
}
