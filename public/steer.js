$(document).ready(function(){
    //var data=[];
   //var a=0;
   // var x=0;
    autoclick();
    $("#b02").click(function(){
       var xml=$.ajax({
           url:'/data.txt',
           async:false
       })
      // $("#name").text(xml.responseText) 
      // $("#clock1").val(xml.responseText);
       $("#box").animate({height:xml.responseText*10});
       var $s = $(".minute");
       //d = new Date(),     
       s = xml.responseText*4;
       $s.val(s).trigger("change");
      /* data[a]=JSON.parse(xml.responseText);
       a++;
       return function(){   
        x=data[a-1];
        $("#data").text(x)    
       }*/

    })
    function autoclick(){
        $("#b01").click();  //让系统自动执行单击事件
        $autoFun = setTimeout(autoclick,60); //设置1秒钟之后再次执行函数
    }
    
})