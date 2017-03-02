$(document).ready(function(){
    $("#filter-generate-pdf").click(function(){
        ExportFile.__construct("pdf");
    });
    $("#filter-generate-html").click(function(){
        ExportFile.__construct("html");
    });
    $("#filter-generate-csv").click(function(){
        ExportFile.__construct("csv");
    });
    $("#export-filter").click(function(){
        $("#area-download").html("");
        ExportFile.eButtons();
    });
    $("a#btn-export").click(function(){
        $(this).remove();
    });
});

var ExportFile = {
    __construct: function(type){
        ExportFile.dButtons();
        lines = [];
        leg = [];
        $("input:checkbox[name=cline]").each(function(){
            if($(this).is(":checked")){
                lines.push($(this).val());
            }
        });
       if(lines.length == 0){
            MsgWarning("Escolha uma ou mais linhas para exportar");
            ExportFile.eButtons();
            $("#area-download").html("");
            return false;
        }
        else{
            setTimeout(function(){
                if(type == "pdf"){
                $("input:radio[name=orientation]").each(function(){
                    if($(this).is(":checked"))
                        orientation = $(this).val();
                });
                format = $("#format").val();
                ExportFile.getTable();
                ExportFile.removeTagToPdfHtml();
                ExportFile.getContent();
                ExportFile.GeneratePDF();
            }
            if(type == "html"){
                ExportFile.getTable();
                ExportFile.removeTagToPdfHtml();
                ExportFile.getContent();
                ExportFile.GenerateHTML();
            }
            if(type == "csv"){
                ExportFile.getTable();
                ExportFile.removeTagToCsv();
                ExportFile.GenerateCSV();
            }
            },500);
        }
        
    },
    getTable: function(){
        qlines = lines.length;
        $("#area-TableExport").html("<table class='table' id='table-export'>");
        for(i = 1; i <= qlines; i++){
            tr = "<tr>"+$("#filter-"+i).html()+"</tr>";
            $("#table-export").append(tr);
        }
    },
    removeTagToPdfHtml: function(){
        $("#table-export").find("tr").each(function(index){
            $(this).find("td").each(function(index){
                if($(this).attr("id") == "check"){
                    $(this).remove();
                }
                str = $(this).text();
                scolor = "";
                color = "";
                $(this).find('a').each(function(){
                    scolor = "color";
                    color = "#337ab7";
                });
                lenstr = str.length;
                tlenstr = Math.floor(lenstr / 50);
                nStr = [];
                if(lenstr > 50){
                    for(i=0; i<=tlenstr; i++){
                        if(i == 0){
                            start = 0;
                            end = 50;
                        }
                        else{
                            if(i == tlenstr){
                                start = i *50;
                                end = lenstr;
                            }
                            else{
                                start = i *50;
                                end = (i+1) *50;
                            }
                        }
                        nStr.push(str.slice(start, end));
                    }
                    nStr = nStr.join("<br/>");
                    $(this).html(nStr);
                }
                else{
                    $(this).html(str);
                }
                (color != "")? $(this).css({'color': color}): "";
                /*
                $(this).find("a").each(function(){
                    $(this).removeAttr("href");
                    $(this).removeAttr("target");
                    $(this).css({"color": "#337ab7"});
                    if($(this).html().length >= 50){
                        $(this).html($(this).html().slice(0, 100)+"...");
                    }
                });
                */
            });
        });
    },
    removeTagToCsv: function(){
        nData = new Array();
        $("#table-export").find("tr").each(function(index){
            line = new Array();
            $(this).find("td").each(function(index){
                if($(this).attr("id") == "check"){
                    $(this).remove();
                }
                if($(this).text() != ""){
                    line.push($(this).text());
                }
            });
            nData.push(line.join(";"));
        });
    },
    getContent: function(){
        table = $("#table-export").html();
        sizeTable = table.length;
        limitSize = 10000;
        contTable = [];
        if(sizeTable > limitSize){
            totalSize = Math.ceil(sizeTable / limitSize);
        }
        else{
            totalSize = 1;
        }
        for(i = 0; i <= totalSize; i++){
            start = 0 + (i * limitSize);
            end = start + limitSize;
            contSlice = table.slice(start, end);
            contTable[i] = contSlice;
        }
    },
    GeneratePDF: function(){
        $.post("./conectfilter.php",{"action": "generate-pdf", "orientation": orientation, "format": format, "Table": contTable},
        function(content){
            if(content == ""){
                MsgDanger("N&atilde;o foi poss&iacute;vel criar o arquivo");
                ExportFile.eButtons();
            }
            else if(content.indexOf("mPDF error") > 0){
                MsgDanger("N&atilde;o foi poss&iacute;vel criar o arquivo");
                ExportFile.eButtons();
            }
            else if(content.indexOf("Allowed memory size of") > 0){
                MsgDanger("Conte&uacute;do muito grande<br/>N&atilde;o foi poss&iacute;vel criar o arquivo");
                ExportFile.eButtons();
            }
            else{
                url = content.split("\\");
                $("#btn-download").attr("href", content);
                $("#area-download").html("<a href=\""+url[0]+"download.php?d="+url[1]+"&type=pdf\" id=\"btn-export\" class=\"btn btn-default\" target=\"_blank\">Download</a>");
                ExportFile.eButtons();
            }
        });
    },
    GenerateHTML: function(){
        $.post("./conectfilter.php",{"action": "generate-html", "Table": contTable},
        function(content){
            if(content == ""){
                MsgDanger("N&atilde;o foi poss&iacute;vel criar o arquivo");
                ExportFile.eButtons();
            }
            else if(content == "erro"){
                MsgDanger("N&atilde;o foi poss&iacute;vel criar o arquivo");
                ExportFile.eButtons();
            }
            else{
                url = content.split("\\");
                $("#btn-download").attr("href", content);
                $("#area-download").html("<a href=\""+url[0]+"download.php?d="+url[1]+"&type=html\" id=\"btn-export\" class=\"btn btn-default\" target=\"_blank\">Download</a>");
                ExportFile.eButtons();
            }
        });
    },
    GenerateCSV: function(){
        $.post("./conectfilter.php",{"action": "generate-csv", "Table": nData},
        function(content){
            if(content == ""){
                MsgDanger("N&atilde;o foi poss&iacute;vel criar o arquivo");
                ExportFile.eButtons();
            }
            else if(content == "erro"){
                MsgDanger("N&atilde;o foi poss&iacute;vel criar o arquivo");
                ExportFile.eButtons();
            }
            else{
                url = content.split("\\");
                $("#btn-download").attr("href", content);
                $("#area-download").html("<a href=\""+url[0]+"download.php?d="+url[1]+"&type=csv\" id=\"btn-export\" class=\"btn btn-default\" target=\"_blank\">Download</a>");
                ExportFile.eButtons();
            }
        });
    },
    
    dButtons: function(){
        loading();
        $("#area-download").html("gerando arquivo...");
        $("#filter-generate-pdf").attr("disabled", true);
        $("#filter-generate-html").attr("disabled", true);
        $("#filter-generate-csv").attr("disabled", true);
    },
    eButtons: function(){
        $("#filter-generate-pdf").removeAttr("disabled");
        $("#filter-generate-html").removeAttr("disabled");
        $("#filter-generate-csv").removeAttr("disabled");
        close_loading();
    }
};