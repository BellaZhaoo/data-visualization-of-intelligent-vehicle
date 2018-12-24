$(document).ready(function(){
    //var data=[];
   //var a=0;
   // var x=0;
    autoclick();
    $("#b05").click(function(){
       var xml1=$.ajax({
           url:'/indexcloud1.js',
           async:false
       })
      // $("#name").text(xml.responseText) 
      // $("#clock1").val(xml.responseText);
      $("#demos2").text(xml1.responseText) 

    })
    function autoclick(){
        $("#b05").click();
        $("#b05").hide();
        $("#demos2").hide();    //让系统自动执行单击事件
        $autoFun = setTimeout(autoclick,16); //设置1秒钟之后再次执行函数
    }
    
})