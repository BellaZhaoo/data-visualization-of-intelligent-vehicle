$(document).ready(function(){
    //var data=[];
   //var a=0;
   // var x=0;
    autoclick();
    $("#b03").click(function(){
       var xml1=$.ajax({
           url:'/readdds.js',
           async:false
       })
      // $("#name").text(xml.responseText) 
      // $("#clock1").val(xml.responseText);
      $("#demos").text(xml1.responseText) 

    })
    function autoclick(){
        $("#b03").click();
        $("#b03").hide();
        $("#demos").hide();    //让系统自动执行单击事件
        $autoFun = setTimeout(autoclick,16); //设置1秒钟之后再次执行函数
    }
    
})