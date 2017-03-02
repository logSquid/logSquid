$(function(){
    $(".input-search").keyup(function(){
        var tabela = $(this).attr('alt');
        if( $(this).val() != ""){
            $("."+tabela+" tbody>tr").hide();
            $("."+tabela+" td:contains-ci('" + $(this).val() + "')").parent("tr").show();
        } else{
            $("."+tabela+" tbody>tr").show();
        }
    }); 
});
$.extend($.expr[":"], {
    "contains-ci": function(elem, i, match, array) {
        return (elem.textContent || elem.innerText || $(elem).text() || "").toLowerCase().indexOf((match[3] || "").toLowerCase()) >= 0;
    }
});
/*
$(document).ready(function(){
    function searchpg(){
        var totalreg = $("#totalreg").val();
        var showpg = $("#showpg").val();
        var goto = $("#goto").val();
        var totalpg = Math.floor(totalreg / showpg);
        $("#totalpg").val(totalpg);
        $("#sTotalpg").html(totalpg);
        $("#goto").attr("max",totalpg);
            $("#totalpgf").val(totalpg);
            $("#sTotalpgf").html(totalpg);
            $("#gotof").attr("max",totalpg);
            $("#showpgf").val(showpg);
            $("#gotof").val(goto);
        $.post("conectclass.php",{action: "searchpg", showpg: showpg, goto: goto},
        function(search){
            $("#listAccess tbody").html(search);
        });
    }
    function searchpgf(){
        var totalreg = $("#totalregf").val();
        var showpg = $("#showpgf").val();
        var goto = $("#gotof").val();
        var totalpg = Math.floor(totalreg / showpg);
        $("#totalpgf").val(totalpg);
        $("#sTotalpgf").html(totalpg);
        $("#gotof").attr("max",totalpg);
            $("#totalpg").val(totalpg);
            $("#sTotalpg").html(totalpg);
            $("#goto").attr("max",totalpg);
            $("#showpg").val(showpg);
            $("#goto").val(goto);
        $.post("conectclass.php",{action: "searchpg", showpg: showpg, goto: goto},
        function(search){
            $("#listAccess tbody").html(search);
        });
    }
    $("#showpg").keypress(function(e){
        if(e.which === 13){
            searchpg();
        }
    });
    $("#goto").keyup(function(e){
        if(e.which === 13){
            searchpg();
        }
    });
    $("#goto").click(function(){
        searchpg();
    });
    $("#showpg").click(function(){
        searchpg();
    });
    
    $("#showpgf").keypress(function(e){
        if(e.which === 13){
            searchpgf();
        }
    });
    $("#gotof").keyup(function(e){
        if(e.which === 13){
            searchpgf();
        }
    });
    $("#gotof").click(function(){
        searchpgf();
    });
    $("#showpgf").click(function(){
        searchpgf();
    });
});
*/