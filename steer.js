$(document).ready(function(){
    //var data=[];
   //var a=0;
   // var x=0;
    autoclick();
    $("#b02").click(function(){
       var xml1=$.ajax({
           url:'/data.js',
           async:false
       })
      // $("#name").text(xml.responseText) 
      // $("#clock1").val(xml.responseText);
       $("#box").animate({height:xml1.responseText*10});
       var $m = $(".minute");
       //d = new Date(),     
       m = xml1.responseText;
       $m.val(m).trigger("change");
      /* data[a]=JSON.parse(xml.responseText);
       a++;
       return function(){   
        x=data[a-1];
        $("#data").text(x)    
       }*/

    })
    function autoclick(){
        $("#b02").click();
        $("#b02").hide();   //让系统自动执行单击事件
        $autoFun = setTimeout(autoclick,16); //设置1秒钟之后再次执行函数
    }
    
})