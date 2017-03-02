function MsgInfo(msg){
    boxMsg("info", msg);
}
function MsgInfoF(msg){
    boxMsgF("info", msg);
}
function MsgWarning(msg){
    boxMsg("warning", msg);
}
function MsgWarningF(msg){
    boxMsgF("warning", msg);
}
function MsgDanger(msg){
    boxMsg("danger", msg);
}
function MsgDangerF(msg){
    boxMsgF("danger", msg);
}
function MsgSuccess(msg){
    boxMsg("success", msg);
}
function MsgSuccessF(msg){
    boxMsgF("success", msg);
}
function NoticeWarning(msg){
    Notice("warning", msg);
}
function NoticeInfo(msg){
    Notice("info", msg);
}
function NoticeDanger(msg){
    Notice("danger", msg);
}
function Notice(type, msg){
    buttonclose = "<button type=\"button\" class=\"close-notice\">×</button>";
    $("<div id=\"notice\" class=\"alert alert-"+type+"\">"+buttonclose+"<div class=\"msg-text\">"+msg+"</div></div>").appendTo("#area-msg");
    $(".close-notice").click(function(){
        $(this).parent().remove();
    });
}
function boxMsg(type,msg){
    $("<div id=\"msg\" class=\"alert alert-"+type+" msgbox\">"+msg+"</div>").appendTo("#area-msg");
    setTimeout(closeMsg, 6000);
    function closeMsg(){
        $("#msg").remove();
    }
}
function boxMsgF(type,msg){
    $("<div id=\"msg\" class=\"alert alert-"+type+" msgbox\">"+msg+"</div>").appendTo("#area-msg");
}
function loading(){
    $("<div class=\"area-img-loading\" id=\"boxloading\"></div>").appendTo("#area-loading");
    $("#area-loading").show();
}
function close_loading(){
    $("#boxloading").remove();
    $(".areaLoading").hide();
}