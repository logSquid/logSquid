$(document).ready(function(){
    monthyear = $("#my").val();
    reporttrue = $("#reporttrue").val();
    $("#month-year").html("<a href='"+$("#my").val()+"'>"+$("#month").val()+"</a>");
    if(monthyear == reporttrue){
        $("#month-year").addClass("reporttrue");
    }
    else{
        $("#month-year").removeClass("reporttrue");
    }
    
    $('.grid').masonry({
        itemSelector: '.box-dashboard'
    });
    $("label").click(function(){
        var id = $(this).attr("for");
        atr = $("input[value="+id+"]").val();
        $("#freport").val(atr);
    });
    $("#bt-report").click(function(){
        logReport();
    });
    $("#fieldreport").keypress(function(k){
        if(k.which === 13){
            logReport();
        }
    });
    $(".show-tr").click(function(){
        var id = ($(this).attr("data-id"));
        $("#"+id).toggle();
    });
    $(".details-line").click(function(){
        var id = ($(this).attr("data-id"));
        $("#"+id).toggle();
    });
    $(".bt-report").click(function(){
        $("#report-result").removeAttr("style");
        var id = $(this).attr("id");
        loading();
        $.post("conectreport.php",{'action': 'getReport', 'showReport': id},
        function(report){
            $("#report-result").html(report);
            var ff = navigator.userAgent;
            if(ff.indexOf("Firefox") > -1){
                setTimeout(function(){var height = $("#report-result").height();if(height > 900){$("#report-result").css({"height":"80%"});} alert();},2000);
                $("#report-result").css({"height":"80%"});
            }
            $("#report-result").css({'overflow-y':'auto'});
            close_loading();
        });
    });
    $("#bt-report").click(function(){
        $("input:radio[name='typefilter']").each(function(){
            if($(this).is(":checked"))
                typereport = $(this).val();
        });
        var fieldreport = $("#fieldreport").val();
        var datestart = $("#fDatestart").val();
        var dateend = $("#fDateend").val();
        var timestart = $("#timestart").val();
        var timeend = $("#timeend").val();
        
        alert(typereport+" - "+fieldreport+" - "+datestart+" - "+dateend+" - "+timestart+" - "+timeend);
    });
    $("tr").click(function(){
        var id = $(this).attr("data-id");
        $("#"+id).toggleClass();
    });
    
    $("#bt-prev").click(function(){
        date = $("#fprev").val();
        $.post("conectreport.php",{'action': 'switchMonthCalendar', 'date': date}, function(ret){
            $("#calendar-area").html(ret);
            $("#month-year").html("<a href='"+$("#my").val()+"'>"+$("#month").val()+"</a>");
            var my = $("#my").val();
            var rt = $("#reporttrue").val();
            if(my == rt){
                $("#month-year").addClass("reporttrue");
            }
            else{
                $("#month-year").removeClass("reporttrue");
            }
        });
    });
    $("#bt-next").click(function(){
        date = $("#fnext").val();
        $.post("conectreport.php",{'action': 'switchMonthCalendar', 'date': date}, function(ret){
            $("#calendar-area").html(ret);
            $("#month-year").html("<a href='"+$("#my").val()+"'>"+$("#month").val()+"</a>");
            var my = $("#my").val();
            var rt = $("#reporttrue").val();
            //alert(my+" "+rt);
            if(my == rt){
                $("#month-year").addClass("reporttrue");
            }
            else{
                $("#month-year").removeClass("reporttrue");
            }
        });
    });
    $("#generate-report").click(function(){
        $(this).removeClass("btn-primary");
        $(this).addClass("btn-default");
        $(this).attr("disabled", "true");
        $(this).html("Gerando");
        loading();
        $.post("conectreport.php", {"action": "generateReport", "day": $("#report-day").val()}, function(ret){
            close_loading();
            window.location.reload();
        });
    });
    $("#generate-report-msg").click(function(){
        $(this).removeClass("btn-primary");
        $(this).addClass("btn-default");
        $(this).attr("disabled", "true");
        $(this).html("Gerando");
        loading();
        $.post("conectreport.php", {"action": "generateReport", "day": $("#report-day").val()}, function(ret){
            close_loading();
            window.location.reload();
        });
        
    });
    $("#remove-report").click(function(){
        $(this).attr("disabled", "true");
        $(this).html("Removendo");
        loading();
        $.post("conectreport.php", {"action": "removeReport", "day": $("#report-day").val()}, function(ret){
            window.location.reload();
        });
    });
});
function logReport(){
    loading();
    var datestart = $("#fDatestart").val();
    var timestart =$("#timestart").val();
    var timeend = $("#timeend").val();
    var dateend = $("#fDateend").val();
    var lfilter = $("#lfilter").html();
    var freport = $("#freport").val();
    var fieldreport = $("#fieldreport").val();
    $.post("conectreport.php", {"action": "report", "datestart": datestart, "dateend": dateend, "timestart": timestart, "timeend": timeend, "lfilter": lfilter, "freport": freport, "fieldreport": fieldreport},
    function(report){
        $(".container-report").html(report);
        close_loading();
    });
}