$(document).ready(function(){
    var Ctrl = false;
    var Shift = false;
    var keyUp = false;
    var keyDown = false;
    var keyL = false;
    
    $(document).keyup(function(k){
        if(k.which == 17) Ctrl = false;
        if(k.which == 16) Shift = false;
        if(k.which == 38) keyUp = false;
        if(k.which == 38) keyDown = false;
        if(k.which == 77) keyM = false;
        if(k.which == 76) keyL = false;
    });
    $(document).keydown(function(k){
        if(k.which == 17) Ctrl = true;
        if(k.which == 16) Shift = true;
        if(k.which == 38) keyUp = true;
        if(k.which == 40) keyDown = true;
        if(k.which == 76) keyL = true;
        
        if((keyUp == true) && (keyDown == true) && Ctrl == true && Shift == true){
            $("#area-msg").each(function(){
            $(this).find("div").each(function(){
                if($(this).attr("id") == "notice"){
                    $("body").append("<img class=\"easter-pangare\" src=\"img/pangare.png\"/>");
                    setTimeout(rPangare, 3000);
                    function rPangare(){
                        $(".easter-pangare").remove();
                    }
                }
            });
        });
        }
        if((keyUp == true) && (keyDown == true) && (keyL == true) && Ctrl == true && Shift == true){
            
        }
    });
});

