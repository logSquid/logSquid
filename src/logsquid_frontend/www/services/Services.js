$(document).ready(function(){
    $(".edit-agent").click(function(){
        var id = $(this).attr("id-item-agent");
        $("#id-agent").val(id);
        $("#name-agent").val($("#td-agent-"+id).text());
    });
    $("#form-name-agent").submit(function(ev){
        loading();
        var id = $("#id-agent").val();
        var name = $("#name-agent").val();
        $.post("services/conectservices.php", {action: "setNameAgent", id: id, name: name},
        function(result){
            if(result == 1){
                MsgSuccess("Nome adicionado com sucesso");
                location.reload();
            }
            else if(result == 0){
                MsgDanger("Erro ao adicionar nome ao Host");
            }
            close_loading();
        });
        ev.preventDefault();
    });
    
    $(".edit-server").click(function(){
        var id = $(this).attr("id-item-server");
        $("#id-server").val(id);
        $("#name-server").val($("#td-server-"+id).text());
    });
    $("#form-name-server").submit(function(ev){
        loading();
        var id = $("#id-server").val();
        var name = $("#name-server").val();
        $.post("services/conectservices.php", {action: "setNameServer", id: id, name: name},
        function(result){
            if(result == 1){
                MsgSuccess("Nome adicionado com sucesso");
                location.reload();
            }
            else if(result == 0){
                MsgDanger("Erro ao adicionar nome ao Host");
            }
            close_loading();
        });
        ev.preventDefault();
    });
});