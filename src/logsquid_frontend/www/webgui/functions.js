$(document).ready(function(){
    $("#datetime-start").datetimepicker({format: 'yyyy-mm-dd hh:ii:ss',autoclose: true, todayBtn: true,});
    $("#datetime-end").datetimepicker({format: 'yyyy-mm-dd hh:ii:ss',autoclose: true, todayBtn: true,});
    
    $("#rangelines").click(function(){
        $("#showlines").val($(this).val());
    });
    $("#showlines").click(function(){
        $("#rangelines").val($(this).val());
    });
    $("#showlines").val($("#rangelines").val());
    $('#statuscode').tooltip();
    $("button#selectall").click(function(){
        if($(this).attr("data-info") == "checkall"){
            $('input[name=cline]').each(function(){
                $(this).prop("checked", true);
            });
            $(this).attr('data-info', 'nocheck');
        }
        else{
            $('input[name=cline]').each(function(){
                $(this).prop("checked", false);
            });
            $(this).attr('data-info', 'checkall');
        }
    });
});