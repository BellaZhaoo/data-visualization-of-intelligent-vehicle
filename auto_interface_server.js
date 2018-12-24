/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

var PROTO_PATH = __dirname + '/../../protos/auto_interface.proto';

var grpc = require('grpc');
var hello_proto = grpc.load(PROTO_PATH).autointerface;
var _ = require('lodash');
var fs=require('fs');
var route_notes = {};
/////////////////////////////////////
var http = require("http");
var url = require("url");
var path = require("path");
var util = require("util");
var qs = require("querystring");
var bodyParser = require('body-parser');
/////////////////////////////////////
var i=0;
var j=0;
var k=0;
var zz=0;
var ww=0;
var ss=0;
var uu=0;
var vv=0;

function sayHello(call){
  call.on('data',function(note){
 
 
  //console.log('PacketSlam:' + 'lengthOfPlan:'+ note.lengthOfPlan+ 'lanelx:'+ note.lanelx+ 'lanely:'+ note.lanely+ 
  //'StopLaneDis:'+ note.StopLaneDis+ 'pathPoints:'+ note.pathPoints+ 'pathPointx:'+note.pathPointx)
  });
  call.on('data',function(noteagain){
 
 
  //console.log('PacketSlamgagin:' + 'lengthOfPlan:'+ noteagain.lengthOfPlan+ 'lanelx:'+ noteagain.lanelx+ 'lanely:'+ noteagain.lanely+ 
  //'pathPoints:'+ noteagain.pathPoints+ 'pathPointx:'+noteagain.pathPointx)
  });
  call.on('end',function(){
  call.end();
  });
 }
function sayHellog(call){
  call.on('data',function(note){
    

    //console.log('PacketReckon:'+ note.dX+ note.dY+ note.dThe)
  });
  call.on('end',function(){
    call.end();
  });
}
var sayHellohsteer=[];
var sayHellohspeed=[];
function sayHelloh(call){
  /*call.on('data',function(note){
      console.log('PacketCanMsg2:'+'sonicx:'+note.sonicx+'sonicy:'+ note.sonicy)
      sayHellohsonicx[i]=note.sonicx;
      i++;
  });
  call.on('data',function(note1){
    console.log('PacketCanMsg3:'+note1.rawdis)
  }); */

  call.on('data',function(note2){
   // console.log('PacketCanMsg:'+'steer:'+note2.steer+'speed:'+note2.speed)
    sayHellohspeed[i]=note2.speed;
    sayHellohsteer[i]=note2.steer;
    console.log('i'+i)
   // console.log('sayHellohspeed'+sayHellohspeed[i])
   // console.log('sayHellohsteer'+sayHellohsteer[i])
    i++;
    
    
  }); 
  call.on('end',function(){
    call.end();
  });
}

var sayHelloqibcontourx=[];
var sayHelloqibcontoury=[];
var indexcloud=[];
//var ibcontourx=[];
function sayHelloq(call){
  call.on('data',function(note){
    

   /* console.log('PacketIbeoVector:'+ note.index+ note.lengthOfObject+'--lengthOfContour--'+ note.lengthOfContour
    +'--ibx--'+ note.ibx+'--iby--'+ note.iby+'--ibw--'+ note.ibw+ note.ibl+ note.ibvx+ note.ibvy
    + note.ibvabx+ note.ibvaby+ note.ibcontournum+'--ibcontourx--'+ note.ibcontourx+'--ibcontoury--'+ note.ibcontoury)*/
   // console.log('------------'+'--lengthOfContour--'+ note.lengthOfContour)
   // console.log('------------'+'--ibcontourx--'+ note.ibcontourx)
   // console.log('------------'+'--ibcontoury--'+ note.ibcontoury)
   // console.log('------------'+'--index--'+ note.index)
    sayHelloqibcontourx[zz]=note.ibcontourx;
    indexcloud[zz]=note.index+1;
    sayHelloqibcontoury[zz]=note.ibcontoury;
    console.log('zz--'+zz)
   // console.log('ibcontourx--ibcontourx'+sayHelloqibcontourx[zz].length)
   // console.log('ibcontoury--ibcontoury'+sayHelloqibcontoury[zz].length)
    zz++;
   
    
    
  });
  call.on('end',function(){
    call.end();
  });
}

function sayHelloPacketOtherVehicleDatalist(call){
  call.on('data',function(note){
    

   /* console.log('PacketIbeoVector:'+ note.index+ note.lengthOfObject+'--lengthOfContour--'+ note.lengthOfContour
    +'--ibx--'+ note.ibx+'--iby--'+ note.iby+'--ibw--'+ note.ibw+ note.ibl+ note.ibvx+ note.ibvy
    + note.ibvabx+ note.ibvaby+ note.ibcontournum+'--ibcontourx--'+ note.ibcontourx+'--ibcontoury--'+ note.ibcontoury)*/
    
    
  });
  call.on('end',function(){
    call.end();
  });
}

function sayHelloOtherVehicleData(call){
  call.on('data',function(note){
    

   /* console.log('PacketIbeoVector:'+ note.index+ note.lengthOfObject+'--lengthOfContour--'+ note.lengthOfContour
    +'--ibx--'+ note.ibx+'--iby--'+ note.iby+'--ibw--'+ note.ibw+ note.ibl+ note.ibvx+ note.ibvy
    + note.ibvabx+ note.ibvaby+ note.ibcontournum+'--ibcontourx--'+ note.ibcontourx+'--ibcontoury--'+ note.ibcontoury)*/
    
    
  });
  call.on('end',function(){
    call.end();
  });
}


function getServer() {
  var server = new grpc.Server();
  server.addService(hello_proto.AutoInterface.service, {sayHello: sayHello,sayHellog: sayHellog,sayHelloh: sayHelloh,
  sayHelloq: sayHelloq,sayHelloPacketOtherVehicleDatalist:sayHelloPacketOtherVehicleDatalist,
  sayHelloOtherVehicleData:sayHelloOtherVehicleData});
  return server;
}

if (require.main === module) {
 
  var routeServer = getServer();
  routeServer.bind('0.0.0.0:50051', grpc.ServerCredentials.createInsecure());
  
  routeServer.start();
}

exports.getServer = getServer;




http.createServer(function(req, res) {
  req.url = req.url == "/" ? "/index.html" : req.url;
  
  
  switch (req.url) {
    case "/test1.js":
      res.writeHead(200, {
        "Content-Type": "text/javascript"
      });
      res.end(fs.readFileSync("./test1.js"));
      break;
    
      case "/steer.js":
      res.writeHead(200, {
        "Content-Type": "text/javascript"
      });
      res.end(fs.readFileSync("./steer.js"));
      break;
      case "/readdd.js":
      res.writeHead(200, {
        "Content-Type": "text/javascript"
      });
      res.end(fs.readFileSync("./readdd.js"));
      break;
      case "/readd.js":
      res.writeHead(200, {
        "Content-Type": "text/javascript"
      });
      res.end(fs.readFileSync("./readd.js"));
      break;
      case "/indexcloud.js":
      res.writeHead(200, {
        "Content-Type": "text/javascript"
      });
      res.end(fs.readFileSync("./indexcloud.js"));
      break;

      case "/indexcloud1.js":
      res.writeHead(200, {
        "Content-Type": "text/plain"
      });
      if(indexcloud[0]!=undefined){
        vv=(vv++)%36000;
      
        res.end(JSON.stringify(indexcloud[vv]));
   
        console.log('vv:'+vv++) 
      }
      break;
      case "/readdds.js":
      res.writeHead(200, {
        "Content-Type": "text/plain"
      });
      if(sayHelloqibcontourx[0]!=undefined){
        uu=(uu++)%36000;
     
        res.end(JSON.stringify(sayHelloqibcontourx[uu]));
   
        console.log('uu:'+uu++) 
      }
      break;
      case "/resss.js":
      res.writeHead(200, {
        "Content-Type": "text/plain"
      });
      if(sayHelloqibcontoury[0]!=undefined){
        ss=(ss++)%36000;
      
        res.end(JSON.stringify(sayHelloqibcontoury[ss]));
     
        console.log('ss:'+ss++) 
      }
      break;
    case "/data.js":
      res.writeHead(200, {
        "Content-Type": "text/plain"
      });
      if(sayHellohsteer[0]!=undefined){
        k=(k++)%36000;
        
        res.end(JSON.stringify(sayHellohsteer[k]));
     
        console.log(sayHellohsteer[k])
        console.log('k:'+k++) 
      }
      break;

    case "/index.js":
      res.writeHead(200, {
        "Content-Type": "text/plain"
      });
      //var note = new Date();
      if(sayHellohspeed[0]!=undefined){
        j=(j++)%36000;
        res.end(JSON.stringify(sayHellohspeed[j]));
     
        console.log(sayHellohspeed[j])
        console.log('j:'+j++) 
      }
      
      break;
    default:
      res.writeHead(200, {
        "Content-Type": "text/html"
      });
      res.end(fs.readFileSync("./public" + req.url));
      //res.end('obj.name')
      break;
  }

}).listen(8080);

console.log("listen at " + 8080);
