$(document).ready(function(){
    $("#confUsername").submit(function(ev){
        username = $("#field-username").val();
        validate = 0;
        msg = new Array();
        
        if(username == ""){
            msg.push("* Informe o nome para o usu&aacute;rio");
            $("#field-username").focus();
            validate = +1;
        }
        if(validate > 0){
            MsgWarning(msg.join("<br/>"));
        }
        else{
            $.post("../user/conectuser.php", {action: "updateUser", name: username},
            function(content){
                if(content == ""){
                    MsgInfo("Nome do usu&aacute;rio atualiza com sucesso");
                    $("#confUsername")[0].reset();
                    location.reload();
                }
                else{
                    MsgDanger(content);
                }
            });
        }
        ev.preventDefault();
    });
    $("#confPassword").submit(function(ev){
        pwdcurrent = $("#password-current").val();
        pwdnew = $("#password-new").val();
        pwdconfirm = $("#password-confirm").val();
        validate = 0;
        msg = new Array();
        
        if(pwdcurrent == ""){
            msg.push("* Informe a Senha Atual");
            $("#password-current").focus();
            validate = +1;
        }
        if(pwdnew == ""){
            msg.push("* Informe a Nova Senha");
            if(validate == 0){
                $("#password-new").focus();
            }
            validate = +1;
        }
        if(pwdconfirm == ""){
            msg.push("* Confirme a Nova Senha");
            if(validate == 0){
                $("#password-confirm").focus();
            }
            validate = +1;
        }
        if(pwdnew !== pwdconfirm){
            msg.push("* As Senhas n&atilde;o s&atilde;o iguais");
            if(validate == 0){
                $("#password-new").val("");
                $("#password-confirm").val("");
                $("#password-new").focus();
            }
            validate = +1;
        }
        
        if(validate > 0){
            MsgWarning(msg.join("<br/>"));
        }
        else{
            $.post("../user/conectuser.php",{action: "alterPass", pwdcurrent: pwdcurrent, pwdnew: pwdnew},
            function(content){
                if(content == ""){
                    MsgInfo("Senha alterada com sucesso");
                    $("#confPassword")[0].reset();
                }
                else{
                    MsgDanger(content);
                }
            });
        }
        
        ev.preventDefault();
    });
});