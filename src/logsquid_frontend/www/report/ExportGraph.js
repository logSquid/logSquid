$(document).ready(function(){
    $("#graph-generate-pdf").click(function(){
        ExportGraphDashboard.__construct();
    });
    $("#export-graph-dashboard").click(function(){
        $("#area-download-graph").html("");
    });
});

var ExportGraphDashboard = {
    __construct: function(){
        ExportGraphDashboard.dButtons();
        idDB = $("#generate-graph").attr("data-id");
        tDashBoard = [];
        imgGraph = [];
        ExportGraphDashboard.getDashboard();
        ExportGraphDashboard.prepareContent();
        ExportGraphDashboard.GeneratePDF();
    },
    getDashboard: function(){
        $("#area-TableExport").html("<table class='table' id='table-export'>"+$("table#"+idDB).html()+"</table>");
        $("#table-export").find("tbody").each(function(){
            $(this).find("tr").each(function(){
                $(this).find("th").each(function(){
                    if($(this).hasClass("area-bt-report")){
                        $(this).html("");
                    }
                });
            });
        });
        tDashBoard = $("#area-TableExport").html();
        //imgGraph = $(".modal-img-graph").html();
        $(".modal-img-graph").find("img").each(function(){
            imgGraph.push($(this).attr("src"));
        });
    },
    
    prepareContent: function(){
        sizeTable = tDashBoard.length;
        limitSize = 100000;
        contTable = [];
        
        if(sizeTable > limitSize){
            totalSize = Math.ceil(sizeTable / limitSize);
        }
        else{
            totalSize = 1;
        }
        for(i = 0; i <= totalSize; i++){
            start = 0 + (i *limitSize);
            end = start + limitSize;
            contSlice = tDashBoard.slice(start, end);
            contTable[i] = contSlice;
        }
    },
    GeneratePDF: function(){
        $("input:radio[name=orientation]").each(function(){
            if($(this).is(":checked"))
                orientation = $(this).val();
        });
        format = $("#format").val();
        $.post("conectgraph.php",{'action': "generate-pdf", 'orientation': orientation, 'format': format, 'Table': contTable, 'imgGraph': imgGraph},
        function(content){
            if(content.indexOf("mPDF error") > 0){
                MsgDanger("N&atilde;o foi poss&iacute;vel criar o PDF");
            }
            else{
                url = content.split("\\");
                //$("#btn-download").attr("href", content);
                $("#area-download-graph").html("<a href=\""+url[0]+"download.php?d="+url[1]+"&type=pdf\" id=\"btn-export\" class=\"btn btn-default\" target=\"_blank\">Download</a>");
                ExportGraphDashboard.eButtons();
                $("#area-TableExport").html("");
            }
        });
    },
    dButtons: function(){
        $("#area-download-graph").html("gerando o arquivo...");
        $("#graph-generate-pdf").attr("disabled", true);
    },
    eButtons: function(){
        $("#graph-generate-pdf").removeAttr("disabled");
        close_loading();
    }
};