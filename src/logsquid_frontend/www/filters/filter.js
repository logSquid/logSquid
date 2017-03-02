$(document).ready(function(){
    $("label").click(function(){
        var id = $(this).attr("for");
        atr = $("input[value="+id+"]").val();
        $("#ftypefilter").val(atr);
    });
    $("#fieldfilter").keypress(function(k){
        if(k.which === 13){
            getDataFilter();
            getNumPage();
        }
    });
    $("#bt-filter").click(function(){
        getDataFilter();
        getNumPage();
    });
    $("#showpg").keypress(function(e){
        if(e.which === 13){
            switchnPage();
            getDataFilter();
        }
    });
    $("#goto").keyup(function(e){
        if(e.which === 13){
            switchnPage();
            getDataFilter();
        }
    });
    $("#goto").change(function(){
        switchnPage();
        getDataFilter();
    });
    $("#showpg").change(function(){
        switchnPage();
        getDataFilter();
    });
    $("#showpgf").keypress(function(e){
        if(e.which === 13){
            switchnPagef();
            getDataFilter();
        }
    });
    $("#gotof").keyup(function(e){
        if(e.which === 13){
            switchnPagef();
            getDataFilter();
        }
    });
    $("#gotof").change(function(){
        switchnPagef();
        getDataFilter();
    });
    $("#showpgf").change(function(){
        switchnPagef();
        getDataFilter();
    });
    $("#export-pdf").click(function(){
        var search = $("#fieldfilter").val();
        var searchs = search.split(",");
        var typefilt = $("#lfilter").html();
        var typef = typefilt.split(", ");
        var ctypef = typef.length;
        var datestart = $("#fDatestart").val();
        var dateend = $("#fDateend").val();
        var timestart = $("#timestart").val();
        var timeend = $("#timeend").val();
        var id = new Array();
        for(i = 0; i < ctypef; i++){
            $("li").find("label").each(function(){
                if($(this).text() === typef[i]){
                    id.push($(this).attr("for"));
                }
            });
        }
        $("#showFilter thead tr").html($("<th>Of</th>"));
        $("#showFilter thead tr").append($("<th>Between</th>"));
        $("#showFilter thead tr").append($("<th>And</th>"));
        $("#showFilter thead tr").append($("<th>To</th>"));
        $("#showFilter tbody tr").html($("<td>"+datestart+"</td>"));
        $("#showFilter tbody tr").append($("<td>"+timestart+"</td>"));
        $("#showFilter tbody tr").append($("<td>"+timeend+"</td>"));
        $("#showFilter tbody tr").append($("<td>"+dateend+"</td>"));
        if(id != ""){
            for(x=0; x<ctypef; x++){
                var typefilter = id.toString();
                var typeFilter = typefilter.split(",");
                var ctypeFilter = typeFilter.length;
                var newTdthead = $("<th>"+typef[x]+"</th>");
                var newTdtbody = $("<td>"+searchs[x]+"</td>");
                $("#showFilter thead tr").append(newTdthead);
                $("#showFilter tbody tr").append(newTdtbody);
            }
        }
    });
    $("#export-to-pdf").submit(function(ev){
        GeneratePDF();
        ev.preventDefault();
    }); 
    $("#export-to-csv").submit(function(ev){
        GenerateCSV();
        ev.preventDefault();
    }); 
    $("#export-to-html").submit(function(ev){
        GenerateHTML();
        ev.preventDefault();
    }); 
    
    $("input[name=orderby]").click(function(){
        $("input[name=orderby]").each(function(){
            if($(this).is(":checked") && $(this).attr("text-order")){
                if($(this).hasClass("radio-orderby-ascending")){
                    $(this).removeClass("radio-orderby-ascending").addClass("radio-orderby-descending").removeAttr("text-order").attr("text-order", "DESC");
                }
                else if($(this).hasClass("radio-orderby-descending")){
                    $(this).removeClass("radio-orderby-descending").addClass("radio-orderby-ascending").removeAttr("text-order").attr("text-order", "ASC");
                }
            }
            else if($(this).is(":checked")){
                $("input[name=orderby]").each(function(){
                    $(this).removeAttr("text-order");
                });
                if($(this).hasClass("radio-orderby-ascending")){
                    $(this).removeAttr("text-oder").attr("text-order", "ASC");
                }
                else{
                    $(this).removeAttr("text-oder").attr("text-order", "DESC");
                }
                
            }
        });
        getDataFilter();
        getNumPage();
    });
    
    $("#applyconf").click(function(){
        $("input[name=configpage]").each(function(){
            if(!$(this).is(":checked")){
                $("#col-"+$(this).val()).hide();
            }
            else{
                $("#col-"+$(this).val()).show();
            }
        });
        if(!$("input[name='searchnull']").length){
            getDataFilter();
        }
    });
    
    $("#export-csv").click(function(){
        var search = $("#fieldfilter").val();
        var searchs = search.split(",");
        var typefilt = $("#lfilter").html();
        var typef = typefilt.split(", ");
        var ctypef = typef.length;
        var datestart = $("#fDatestart").val();
        var dateend = $("#fDateend").val();
        var timestart = $("#timestart").val();
        var timeend = $("#timeend").val();
        var id = new Array();
        for(i = 0; i < ctypef; i++){
            $("li").find("label").each(function(){
                if($(this).text() === typef[i]){
                    id.push($(this).attr("for"));
                }
            });
        }
        $("#showFilterCSV thead tr").html($("<th>Of</th>"));
        $("#showFilterCSV thead tr").append($("<th>Between</th>"));
        $("#showFilterCSV thead tr").append($("<th>And</th>"));
        $("#showFilterCSV thead tr").append($("<th>To</th>"));
        $("#showFilterCSV tbody tr").html($("<td>"+datestart+"</td>"));
        $("#showFilterCSV tbody tr").append($("<td>"+timestart+"</td>"));
        $("#showFilterCSV tbody tr").append($("<td>"+timeend+"</td>"));
        $("#showFilterCSV tbody tr").append($("<td>"+dateend+"</td>"));
        if(id != ""){
            for(x=0; x<ctypef; x++){
                var typefilter = id.toString();
                var typeFilter = typefilter.split(",");
                var ctypeFilter = typeFilter.length;
                var newTdthead = $("<th>"+typef[x]+"</th>");
                var newTdtbody = $("<td>"+searchs[x]+"</td>");
                $("#showFilterCSV thead tr").append(newTdthead);
                $("#showFilterCSV tbody tr").append(newTdtbody);
            }
        }
    });
    $("#export-html").click(function(){
        var search = $("#fieldfilter").val();
        var searchs = search.split(",");
        var typefilt = $("#lfilter").html();
        var typef = typefilt.split(", ");
        var ctypef = typef.length;
        var datestart = $("#fDatestart").val();
        var dateend = $("#fDateend").val();
        var timestart = $("#timestart").val();
        var timeend = $("#timeend").val();
        var id = new Array();
        for(i = 0; i < ctypef; i++){
            $("li").find("label").each(function(){
                if($(this).text() === typef[i]){
                    id.push($(this).attr("for"));
                }
            });
        }
        $("#showFilterHTML thead tr").html($("<th>Of</th>"));
        $("#showFilterHTML thead tr").append($("<th>Between</th>"));
        $("#showFilterHTML thead tr").append($("<th>And</th>"));
        $("#showFilterHTML thead tr").append($("<th>To</th>"));
        $("#showFilterHTML tbody tr").html($("<td>"+datestart+"</td>"));
        $("#showFilterHTML tbody tr").append($("<td>"+timestart+"</td>"));
        $("#showFilterHTML tbody tr").append($("<td>"+timeend+"</td>"));
        $("#showFilterHTML tbody tr").append($("<td>"+dateend+"</td>"));
        if(id != ""){
            for(x=0; x<ctypef; x++){
                var typefilter = id.toString();
                var typeFilter = typefilter.split(",");
                var ctypeFilter = typeFilter.length;
                var newTdthead = $("<th>"+typef[x]+"</th>");
                var newTdtbody = $("<td>"+searchs[x]+"</td>");
                $("#showFilterHTML thead tr").append(newTdthead);
                $("#showFilterHTML tbody tr").append(newTdtbody);
            }
        }
    });
    $("#deleteFile").click(function(ev){
        var file = $("#deleteFile").attr("data-file");
        $.post("export/download.php",{"r": file, "type":"pdf"},
        function(){
            $("#area-download").hide();
        });
        ev.preventDefault();
    });
    $("#deleteFileCSV").click(function(ev){
        var file = $("#deleteFileCSV").attr("data-file");
        $.post("export/download.php",{"r": file, "type":"csv"},
        function(){
            $("#area-downloadCSV").hide();
        });
        ev.preventDefault();
    });
    $("#deleteFileHTML").click(function(ev){
        var file = $("#deleteFileHTML").attr("data-file");
        $.post("export/download.php",{"r": file, "type":"html"},
        function(){
            $("#area-downloadHTML").hide();
        });
        ev.preventDefault();
    });
    $("#bt-viewsql").click(function(){
        NoticeInfo($("#get_sql").val());
    });
});

function switchnPage(){
    var totalreg = $("#totalreg").val();
    var showpg = $("#showpg").val();
    var goto = $("#goto").val();
    var totalpg = Math.ceil(totalreg / showpg);
    $("#totalpg").val(totalpg);
    $("#sTotalpg").html(totalpg);
    $("#goto").attr("max",totalpg);
        $("#totalpgf").val(totalpg);
        $("#sTotalpgf").html(totalpg);
        $("#gotof").attr("max",totalpg);
        $("#showpgf").val(showpg);
        $("#gotof").val(goto);
}
function switchnPagef(){
    var totalreg = $("#totalregf").val();
    var showpg = $("#showpgf").val();
    var goto = $("#gotof").val();
    var totalpg = Math.ceil(totalreg / showpg);
    $("#totalpgf").val(totalpg);
    $("#sTotalpgf").html(totalpg);
    $("#gotof").attr("max",totalpg);
        $("#totalpg").val(totalpg);
        $("#sTotalpg").html(totalpg);
        $("#goto").attr("max",totalpg);
        $("#showpg").val(showpg);
        $("#goto").val(goto);
}

function getNumPage(){
    $(".area-numpage").hide();
    $(".area-loading").remove();
    loading();
    $(".numpage").append("<div class=\"area-loading\">calculando</div>");
    var showpg = $("#showpg").val();
    var goto = $("#goto").val();
    var search = $("#fieldfilter").val();
    var typefilt = $("#lfilter").html();
    var typef = typefilt.split(", ");
    var ctypef = typef.length;
    var datetimestart = $("#datetime-start").val();
    var datetimeend = $("#datetime-end").val();
    var id = new Array();
    var agent;
    var listagents = $("#lagents").html();
    $("li").find("label").each(function(){
        if($(this).text() === listagents){
            agent = $("#"+$(this).attr("for")).val();
        }
    });
    for(i = 0; i < ctypef; i++){
        $("li").find("label").each(function(){
            if($(this).text() === typef[i]){
                id.push($(this).attr("for"));
            }
        });
    }
    var typefilter = id.toString();
    $.post("./conectfilter.php",{action: "getnumpg", showpg: showpg, goto: goto,typefilter: typefilter, search: search, datetimestart: datetimestart, datetimeend: datetimeend, agent: agent},
    function(numpg){
        var num = numpg.split(",");
        $("#totalreg").val(num[0]);
        $("#sTotalreg").html(num[0]);
        $("#showpg").val(num[2]);
        $("#goto").val(num[3]);
        $("#totalpg").val(num[1]);
        $("#sTotalpg").html(num[1]);
        $("#totalregf").val(num[0]);
        $("#sTotalregf").html(num[0]);
        $("#showpgf").val(num[2]);
        $("#gotof").val(num[3]);
        $("#totalpgf").val(num[1]);
        $("#sTotalpgf").html(num[1]);
            $("#totalpg").val(num[1]);
            $("#sTotalpg").html(num[1]);
            $("#goto").attr("max",num[1]);
            $("#totalpgf").val(num[1]);
            $("#sTotalpgf").html(num[1]);
            $("#gotof").attr("max",num[1]);
        $(".area-loading").remove();
        $(".area-numpage").show();
        close_loading();
    });
}

function getDataFilter(){
    $(".bt-viewsql").hide();
    $("#listAccess tbody").html("<tr><td colspan=\"11\" class=\"wfilter\"><span class=\"glyphicon glyphicon-filter\">Filtrando...</span></td></tr>");
    var showpg = $("#showpg").val();
    var goto = $("#goto").val();
    var search = $("#fieldfilter").val();
    var typefilt = $("#lfilter").html();
    var typef = typefilt.split(", ");
    var ctypef = typef.length;
    var datetimestart = $("#datetime-start").val();
    var datetimeend = $("#datetime-end").val();
    var agent;
    var listagents = $("#lagents").html();
    $("li").find("label").each(function(){
        if($(this).text() === listagents){
            agent = $("#"+$(this).attr("for")).val();
        }
    });
    var fields = new Array();
    $("input[name=configpage]").each(function(){
        if($(this).is(":checked")){
            fields.push($(this).val());
        }
    });
    $("input[name=orderby]").each(function(){
        if($(this).is(":checked")){
            orderby = $(this).val()+" "+$(this).attr("text-order");
        }
    });
    var id = new Array();
    for(i = 0; i < ctypef; i++){
        $("li").find("label").each(function(){
            if($(this).text() === typef[i]){
                id.push($(this).attr("for"));
            }
        });
    }
    var typefilter = id.toString();
    if(datetimestart === ""){
        MsgWarning("Escolha a Data de Inicio");
        $("#datetime-start").focus();
    }
    else if(datetimeend === ""){
        MsgWarning("Escolha a Data de Termino");
        $("#datetime-end").focus();
    }
    else{
        $.post("./conectfilter.php",{action: "filter", typefilter: typefilter, search: search, datetimestart: datetimestart, datetimeend: datetimeend,showpg: showpg, goto: goto, orderby: orderby, fields: fields, agent: agent},
        function(filter){
            $("#listAccess tbody").html(filter);
            $(".bt-viewsql").show();
        });
    }
}

function bDownloadPDF(filename){
    $("#area-download").show();
    $("#btn-download").attr("href","export/download.php?d="+filename+"&type=pdf");
    $("#btn-download").html("Download "+filename+".pdf");
    $("#deleteFile").attr("data-file", filename);
    $("#deleteFile").html("Delete "+filename+".pdf");
}
function bDownloadCSV(filename){
    $("#area-downloadCSV").show();
    $("#btn-downloadCSV").attr("href","export/download.php?d="+filename+"&type=csv");
    $("#btn-downloadCSV").html("Download "+filename+".csv");
    $("#deleteFileCSV").attr("data-file", filename);
    $("#deleteFileCSV").html("Delete "+filename+".csv");
}
function bDownloadHTML(filename){
    $("#area-downloadHTML").show();
    $("#btn-downloadHTML").attr("href","export/download.php?d="+filename+"&type=html");
    $("#btn-downloadHTML").html("Download "+filename+".html");
    $("#deleteFileHTML").attr("data-file", filename);
    $("#deleteFileHTML").html("Delete "+filename+".html");
}