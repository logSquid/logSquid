$(document).ready(function(){
    var gTableGraph = {
        __construct: function(id, leg){
            idDB = id;
            legDB = leg;
            data = [];
            if($("#widthGraph").val() == ""){
                bWidth = $(document).width() -100;
                $("#widthGraph").val($(document).width() -100);
            }
            else{
                bWidth = $("#widthGraph").val();
            }
            if($("#heightGraph").val() == ""){
                bHeight = $('html').height();
                $("#heightGraph").val($('html').height());
            }
            else{
                bHeight = $("#heightGraph").val();
            }
            measures = new Array(bWidth, bHeight);
            typegraph = $("#typeGraph").val();
            $(".modal-img-graph").removeAttr("style");
            $(".modal-body-graph").removeAttr("style");
            
            $(".modal-img-graph").html("Gerando o Gr&aacute;fico");
            loading();
            gTableGraph.getData();
        },
        getData: function(){
            $("table#"+idDB).find("tbody").each(function(){
                $(this).find('tr').each(function(){
                    var c1 = $(this).find('td').html();
                    var c2 = $(this).find('td').next().html();
                    var c3 = $(this).find('td').next().next().html();
                    var d = new Array(c1, c2, c3);
                    data.push(d);
                });
            });
        },
        
        generateGraph: function(){
            $.post("conectgraph.php", {'action': 'gGraph', 'type': idDB, 'leg': legDB, 'measures': measures, data: data, typegraph: typegraph}, function(content){
                if(content == "erro"){
                    MsgDanger("N&atilde;o foi poss&iacute;vel gerar o Gráfico");
                }
                else{
                    imgs = content.split(" ");
                    if(imgs[1] == ""){
                        img = imgs[0].split("\\");
                        $(".modal-img-graph").html("<img src='"+img[0]+img[1]+".png' />");
                    }
                    else{
                        img0 = imgs[0].split("\\");
                        $(".modal-img-graph").html("<img src='"+img0[0]+img0[1]+".png' />");
                        img1 = imgs[1].split("\\");
                        $(".modal-img-graph").append("<img src='"+img1[0]+img1[1]+".png' />");
                    }
                    
                }
                gTableGraph.__destruct();
            });
        },
        
        __destruct: function(){
            $(".area-db-graph").css({'width': ($(document).width() -100)});
            $(".modal-body-graph").css({'height': $('html').height()-130, 'overflow': "auto"});
            close_loading();
        }
    };
    $(".icon-graph").click(function(){
        var typegraph = $(this).attr("data-info");
        var iddashboard = $(this).attr("id");
        $("#generate-graph").attr("data-info", typegraph);
        $("#generate-graph").attr("data-id", iddashboard);
        $("#typegraph-text").text(typegraph);
        gTableGraph.__construct(iddashboard, typegraph);
        gTableGraph.generateGraph();
    });
   $("form[name=optionsGraph]").submit(function(ev){
        var typegraph = $("#generate-graph").attr("data-info");
        var iddashboard = $("#generate-graph").attr("data-id");
        $("#typegraph-text").text(typegraph);
        gTableGraph.__construct(iddashboard, typegraph);
        gTableGraph.generateGraph();
        
        ev.preventDefault();
   });
   $("#closeModalGraph").click(function(){
       $("form[name=optionsGraph]")[0].reset();
   });
   $(".dashboard-graph").focus(function(){
       $(this).keydown(function(key){
            if(key.which == 27){
                $("form[name=optionsGraph]")[0].reset();
            }
        });
   });
    
});