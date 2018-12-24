$(document).ready(function(){
    //var data=[];
   //var a=0;
   // var x=0;
    autoclick();
    $("#b01").click(function(){
       var xml=$.ajax({
           url:'/index.js',
           async:false
       })
       $("#name").text(xml.responseText) 
       $("#name1").text(xml.responseText)
       $("#clock1").val(xml.responseText);
       $("#box").animate({height:xml.responseText*10});
       var $s = $(".second");
       //d = new Date(),     
       s = xml.responseText;
       $s.val(s).trigger("change");
      /* data[a]=JSON.parse(xml.responseText);
       a++;
       return function(){   
        x=data[a-1];
        $("#data").text(x)    
       }*/

    })
    function autoclick(){
        $("#b01").click();
        $("#b01").hide();
        $("#name").hide(); 
        $("#name1").hide();
        $("#name2").hide();
         //让系统自动执行单击事件
     
        $autoFun = setTimeout(autoclick,16); //设置1秒钟之后再次执行函数
    }
    
})
//$(":text").css("background-color","#B2E0FF");
//$("#btn3").click(function(){
//    $("#clock1").val("Dolly Duck");
//  });
  

