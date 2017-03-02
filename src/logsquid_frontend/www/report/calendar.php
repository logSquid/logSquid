<style type="text/css">
    *{
        font: normal 1em Ubuntu;
    }
    a{
        text-decoration: none;
        color: #fff;
    }
    table{
        border-collapse: collapse;
    }
    .title-calendar{
        background: #0088CC;
        color: #fff;
        font-weight: bold;
        padding: 10px 10px;
    }
    td{
        padding: 15px 10px;
        min-width: 30px;
        min-height: 30px;
        text-align: center;
    }
    .day{
        background: #f9f9f9;
        color: #666;
    }
    .current{
        background: #0088cc;
        color: #fff;
    }
    .event{
        background: #B00000;
        color: #fff;
    }
</style>
<?php
    $gDate = ($_REQUEST['d'])? explode("-", $_REQUEST['d']): explode("-", date("m-Y"));
    
    $date = mktime(date("G"),date("i"),date("s"), $gDate[0],1,$gDate[1]);
    
    $d = date('d', $date);
    $m = date('n', $date);
    $y = date('Y', $date);
    
    $fday = mktime(0,0,0, $m, 1, $y);
    $title = date("F", $fday);
    $wday = date("D", $fday);
    $daysmonth = date("t", $date);
    
    $prev = date("n-Y", strtotime('-1 months', strtotime("{$y}-{$m}")));
    $next = date("n-Y", strtotime('+1 months', strtotime("{$y}-{$m}")));
    
    $report = array(
        '2015' => array(
            '10' => array(
                '1' => true,
                '5' => true,
                '7' => true,
                '8' => true,
                '10' => true,
                '11' => true
            ),
            '9' => array(
                '1' => true,
                '3' => true,
                '8' => true,
                '10' => true,
                '15' => true
            )
        )
    );
    
    switch ($wday){
        case "Sun": $blank = 0;            break;
        case "Mon": $blank = 1;            break;
        case "Tue": $blank = 2;            break;
        case "Wed": $blank = 3;            break;
        case "Thu": $blank = 4;            break;
        case "Fri": $blank = 5;            break;
        case "Sat": $blank = 6;            break;
    }
    
    switch ($m){
        case "01": $month = "Jan";            break;
        case "02": $month = "Feb";            break;
        case "03": $month = "Mar";            break;
        case "04": $month = "Apr";            break;
        case "05": $month = "May";            break;
        case "06": $month = "Jun";            break;
        case "07": $month = "Jul";            break;
        case "08": $month = "Aug";            break;
        case "09": $month = "Sep";            break;
        case "10": $month = "Oct";            break;
        case "11": $month = "Nov";            break;
        case "12": $month = "Dec";            break;
    }
    
    echo "
        <table border='0'>
            <tr>
                <th class=\"title-calendar\"><a href=\"?d={$prev}\"><<</a></th>
                <th class=\"title-calendar\" colspan=\"5\">{$title} / {$y}</th>
                <th class=\"title-calendar\"><a href=\"?d={$next}\">>></a></th>
            </tr>
            <tr>
                <td>Sun</td>
                <td>Mon</td>
                <td>Tue</td>
                <td>Wed</td>
                <td>Thu</td>
                <td>Fri</td>
                <td>Sat</td>
            </tr>
            <tr>
    ";
    for ($i = 1; $i < $daysmonth+1; $i++, $counter++) {
    $timeStamp = strtotime("$y-$m-$i");
        if ( $i == 1) {
            $firstDay = date("w",$timeStamp);

            for($j = 0; $j < $firstDay; $j++, $counter++)
                    echo "<td>&nbsp;</td>";
        }

        if ($counter % 7 == 0)
                echo "</tr><tr>";

        if ( $i == date('d') && $m == date("m") && $y == date('Y') ) {
                echo "<td class=\"current\">$i</td>";
        }
        else {
            if($report[$y][$m][$i]){
                echo "<td class=\"event\">{$i}</td>";
            }
            else{
                echo "<td class=\"day\">$i</td>";
            }
        }
    }
        
    echo "
        </tr></table>
    ";
    
    
?>
