$(document).ready(function(){
    //var data=[];
   //var a=0;
   // var x=0;
    autoclick();
    $("#b03").click(function(){
       var xml1=$.ajax({
           url:'/cloud1.js',
           async:false
       })
       $("#name2").text(xml.responseText) 
       $("#clock2").val(xml.responseText);
       //$("#box").animate({height:xml1.responseText*10});
      // var $m = $(".minute");
       //d = new Date(),     
      // m = xml1.responseText*4;
     //  $m.val(m).trigger("change");
      /* data[a]=JSON.parse(xml.responseText);
       a++;
       return function(){   
        x=data[a-1];
        $("#data").text(x)    
       }*/

    })
    function autoclick(){
        $("#b03").click();
        $("#b03").hide();   //让系统自动执行单击事件
        $autoFun = setTimeout(autoclick,1000); //设置1秒钟之后再次执行函数
    }
    
})