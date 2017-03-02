$(document).ready(function(){
    $("#forgot-password").click(function(){
        NoticeWarning("<b>Para recuperar a senha do seu usu&aacute;rio, execute o seguinte comando no local em que o logSquid Server está instalado:</b><br/>logsquid_config --reset-password frontend");
    });
    $("form#login").submit(function(ev){
        username = $("input#username").val();
        password = $("input#password").val();
        msg = new Array();
        validate = 0;
        
        if(username == ""){
            msg.push("* Preencha o campo Usu&aacute;rio");
            if(validate == 0){
                $("input#username").focus();
            }
            validate =  +1;
        }
        if(password == ""){
            msg.push("* Preencha o campo Senha");
            if(validate == 0){
                $("input#password").focus();
            }
            validate =  +1;
        }
        if(validate > 0){
            MsgWarning(msg.join("<br/>"));
        }
        else{
            $.post("user/conectuser.php",{"action": "login", "username": username, "password": password},
            function(content){
                if(content.indexOf("logsquid") > 0){
                    location.href=content;
                }
                else{
                    MsgDanger(content);
                }
            });
        }
        ev.preventDefault();
    });
});
