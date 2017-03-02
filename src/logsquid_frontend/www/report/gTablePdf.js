$(document).ready(function(){
    $('input:checkbox[name=cline]').each(function(){
        //$(this).attr("checked", "checked");
    });
    var gTablePdf = {
        
        __construct: function(type){
            gTablePdf.dButtons();
            lines = [];
            leg = [];
            $("input:checkbox[name=cline]").each(function(){
                if($(this).is(":checked")){
                    lines.push($(this).val());
                    leg.push($(this).attr('data-leg'));
                }
            });
            if(lines.length == 0){
                MsgWarning("Escolha uma ou mais linhas para exportar");
                $("#area-download").html("");
                gTablePdf.eButtons();
                return false;
            }
            else{
                setTimeout(function(){
                    if(type == "pdf"){
                        gTablePdf.checkPdf();
                    }
                    else if(type == "html"){
                        gTablePdf.checkHtml();
                    }
                },500);
            }
                
        },

        checkPdf: function(){
            format = $("#format").val();
            $("input:radio[name=orientationd]").each(function(){
                if($(this).is(":checked"))
                    orientation = $(this).val();
            });
            qlines = lines.length;
            gTablePdf.getTable();
            gTablePdf.removeTagBreakDetails();
            gTablePdf.submitHtml();
            gTablePdf.generatePdf();
        },
        
        checkHtml: function(){
            gTablePdf.dButtons();
            qlines = lines.length;
            gTablePdf.getTable();
            gTablePdf.removeTagBreakDetails();
            gTablePdf.submitHtml();
            gTablePdf.generateHtml();
        },

        getTable: function(){
            $("#area-TableExport").html("<table class='table' id='table-export'>");
            for(i = 0; i < qlines; i++){
                det = "";
                Th = $("#"+leg[i]).html();
                if(Th !== undefined){
                    th = "<tr><th colspan='5'>"+Th+"</th></tr>";
                }
                else{
                    th = "";
                }
                tr = $("tr[data-id='det"+lines[i]+"']").html();
                gTablePdf.getTableDetails($("#det"+lines[i]));
                f = th+"<tr>"+tr+"</tr><tr>"+det+"</tr>";
                $("#table-export").append(f);
            }
        },
        
        getTableDetails: function(details){
            (orientation == "-L")? limitStr = 150: limitStr = 100;
            details.find('td').each(function(){
                $(this).find('table').each(function(){
                    $(this).find('tbody').each(function(){
                        $(this).find('tr').each(function(index){
                            if(index >= 501){
                                return false;
                            }
                            else{
                                td = "";
                                $(this).find("td").each(function(){
                                    ($(this).attr('colspan'))? colspan = " colspan='"+$(this).attr('colspan')+"'": colspan = "";
                                    ($(this).attr('style'))? style = " style='"+$(this).attr('style')+"'": style = "";
                                    
                                    if($(this).html().length > limitStr){
                                        str = $(this).text();
                                        lenstr = $(this).html().length;
                                        tlenstr = Math.floor(lenstr / limitStr);
                                        nStr = [];
                                        for(i=0; i<= tlenstr; i++){
                                            if(i == 0){
                                                start = 0;
                                                end = limitStr;
                                            }
                                            else{
                                               if(i == tlenstr){
                                                   start = (i *limitStr);
                                                   end = (lenstr);
                                               }
                                               else{
                                                   start = (i *limitStr);
                                                   end = ((i+1) * limitStr);
                                               }
                                            }
                                            nStr.push(str.slice(start, end));
                                        }
                                        nStr = (nStr.join("<br/>"));
                                        td += ("<td"+colspan+""+style+">"+nStr+"</td>");
                                    }
                                    else{
                                        td += ("<td"+colspan+""+style+">"+$(this).html()+"</td>");
                                        
                                    }
                                });
                                det += ("<tr>+"+td+"</tr>");
                            }
                        });
                    });
                });
            });
        },

        removeTagBreakDetails: function(){
            $('#table-export').find('tr').each(function(index){
                $(this).find('td').each(function(index){
                    if($(this).attr("id") == "check"){
                        $(this).remove();
                    }
                    if($(this).attr("id") == "index"){
                        $(this).remove();
                    }
                    /*$(this).find('input').each(function(){
                        $(this).remove();
                    });*/
                    $(this).find('table').each(function(index){
                        $(this).find('tr').each(function(){
                           $(this).find('td').each(function(){
                                text = $(this).text();
                                $(this).html(text);
                                if($(this).html().length >= 50){
                                    $(this).html(($(this).html()).slice(0, 100)+"...");
                                }
                           });
                        });
                    });
                    $(this).find('a').each(function(){
                        $(this).removeAttr("href");
                        $(this).removeAttr("target");
                        $(this).css({"color":"blue"});
                        if($(this).html().length >= 50){
                            $(this).html($(this).html().slice(0, 100)+"...");
                        }
                    });
                });
            });
        },
        
        submitHtml: function(){
            html = $("#table-export").html();
            sizeHtml = html.length;
            limitSize = 100000;
            contHtml = [];
            if(sizeHtml > limitSize){
                totalSize = Math.ceil(sizeHtml / limitSize);
            }
            else{
                totalSize = 1;
            }
            
            for(i = 0; i <= totalSize; i++){
                start = 0 + (i * limitSize);
                end = start + limitSize;
                contSlice = html.slice(start, end);
                contHtml[i] = contSlice;
            }
        },
        dButtons: function(){
            loading();
            $("#report-area-download").html("gerando arquivo...");
            $("#report-generate-pdf").attr("disabled", true);
            $("#report-generate-html").attr("disabled", true);
        },
        eButtons: function(){
            $("#report-generate-pdf").removeAttr("disabled");
            $("#report-generate-html").removeAttr("disabled");
            close_loading();
        },
    
        generatePdf: function(){
            $.post("conectreport.php", {'action': 'export-pdf', 'format': format, 'orientation': orientation, 'contHtml': contHtml},
            function(content){
                if(content == ""){
                    MsgDanger("N&atilde;o foi poss&iacute;vel criar o PDF, o conte&uacute;do &eacute; muito grande");
                    $("#report-area-download").html("");
                }
                else if(content == "erro"){
                    MsgDanger("N&atilde;o foi poss&iacute;vel criar o PDF");
                }
                else{
                    url = content.split("\\");
                    $("#btn-download").attr("href", content);
                    $("#report-area-download").html("<a href=\""+url[0]+"download.php?d="+url[1]+"&type=pdf\" id=\"btn-export\" class=\"btn btn-default\" target=\"_blank\">Download</a>");
                }
                gTablePdf.eButtons();
            });
        },
        
        generateHtml: function(){
            $.post("conectreport.php", {'action': 'export-html', 'contHtml': contHtml},
            function(content){
                if(content == ""){
                    MsgDanger("N&atilde;o foi poss&iacute;vel criar o HTML, o conte&uacute;do &eacute; muito grande");
                    $("#report-area-download").html("");
                }
                else if(content == "erro"){
                    MsgDanger("N&atilde;o foi poss&iacute;vel criar o HTML");
                }
                else{
                    url = content.split("\\");
                    $("#btn-download").attr("href", content);
                    $("#report-area-download").html("<a href=\""+url[0]+"download.php?d="+url[1]+"&type=html\" id=\"btn-export\" class=\"btn btn-default\" target=\"_blank\">Download</a>");
                }
                gTablePdf.eButtons();
            });
        }
        
    };
    $("#export-details").click(function(){
        $("#report-area-download").html("");
    });
    $("#generatePDF").click(function(){
        gTablePdf.__construct();
    });
    $("#report-generate-pdf").click(function(){
        gTablePdf.__construct('pdf');
    });
    $("#report-generate-html").click(function(){
        gTablePdf.__construct('html');
    });
    $("#deleteFile").click(function(ev){
        var file = $("#deleteFile").attr("data-file");
        $.post("export/download.php",{"r": file, "type":"pdf"},
        function(){
            $("#area-download").hide();
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
});

