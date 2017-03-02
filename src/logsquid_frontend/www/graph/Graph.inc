<?php
$PATHS = array('class','css','js','img','functions','settings','realtime','filters','report','daemon','webgui','lang','graph','tmp','user');
$WWW = str_replace($PATHS, "", dirname(__FILE__));
require_once("{$WWW}functions/autoload.php");
$band = "";
/**
 * @author Mauro Marssola - Vantage TI
 */
class Graph {
    public $SizeGraphX;
    public $SizeGraphY;
    public $FontTT = "ubuntu.ttf";
    public $ColorText = "DimGrey";
    public $FontSizeLabel = 11;
    public $FontSizeTitle = 13;
    public $Graph3D = 5;
    public $TypeGraph;
    public $data;
    public $graphic;
    public $report;
    public $SetTitle;
    public $legBand;
    public $filename;
            
    function __construct($x, $y) {
        $this->filename = call_user_func(['Functions', 'getNameFile']);

        $this->SizeGraphX = ($x -100);
        $this->SizeGraphY = ($y -100);
        $this->graphic = new PHPlot($this->SizeGraphX, $this->SizeGraphY);
        $this->graphic->SetDefaultTTFont($this->FontTT);
        $this->graphic->SetFontTTF("title", NULL, $this->FontSizeTitle);
        $this->graphic->SetFontTTF("y_label", NULL, $this->FontSizeLabel);
        $this->graphic->SetFontTTF("x_label", NULL, $this->FontSizeLabel);
        $this->graphic->SetFileFormat("png");
        
        $this->graphic->SetShading($this->Graph3D);
        $this->graphic->SetImageBorderType("none");
        
        $this->graphic->SetXTickPos("none");
        $this->graphic->SetYTickPos("none");
        
        $this->graphic->SetDrawXGrid(TRUE);
        $this->graphic->SetDrawYGrid(TRUE);
        $this->graphic->SetPlotBorderType("none");
    }
    
    public function GraphAccess(){
        ($this->TypeGraph == NULL)? $this->graphic->SetPlotType('bars'): $this->graphic->SetPlotType($this->TypeGraph);
        ($this->TypeGraph == "thinbarline" || $this->TypeGraph == "lines" || $this->TypeGraph == "linepoints")? $this->graphic->SetLineWidths(3): "";
        $this->graphic->SetTitle($this->SetTitle);
        $this->graphic->SetPlotAreaWorld(NULL, 0);
        $this->graphic->SetYDataLabelPos("plotin");
        
        $this->graphic->SetYLabel("Nº de Acessos");
        $this->graphic->SetXLabel($this->report);
        $this->graphic->SetXLabelAngle("90");
    }
    
    public function GraphBandWidth(){
        global $band;
        $band = $this->data;
        ($this->TypeGraph == NULL)? $this->graphic->SetPlotType('bars'): $this->graphic->SetPlotType($this->TypeGraph);
        ($this->TypeGraph == "thinbarline" || $this->TypeGraph == "lines" || $this->TypeGraph == "linepoints")? $this->graphic->SetLineWidths(3): "";
        $this->graphic->SetTitle($this->SetTitle);
        $this->graphic->SetCallback("draw_all", "GraphLegendBW", $this->graphic);
        $this->graphic->SetYLabel("Bytes");
        $this->graphic->SetXLabel($this->report);
        $this->graphic->SetXLabelAngle("90");
    }

    function __destruct() {
        $file = "../tmp/".$this->filename.".png";
        $this->graphic->SetDataValues($this->data);
        $this->graphic->SetIsInline(TRUE);
        $this->graphic->SetOutputFile($file);
        $this->graphic->DrawGraph();
        if(file_exists($file)){
            echo BASEURL.TMP."\\".$this->filename." ";
        }
        else{
            echo 'erro';
        }
    }
}
function GraphLegendBW($img, $graphic){
    global $band;
    $color = imagecolorresolve($img, 99, 99, 99);
    $fontsize = '5';
    foreach ($band as $x => $v){
        list($pos_x, $pos_y) = $graphic->GetDeviceXY(($x +0.4), ($band[$x][1]));
        imagestring($img, $fontsize, ($pos_x -15), ($pos_y -20 ), call_user_func(['Functions', 'convertSize'], $band[$x][1]), $color);
    }
}
