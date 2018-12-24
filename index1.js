var http = require("http");
var url = require("url");
var path = require("path");
var util = require("util");
var qs = require("querystring");
var fs = require("fs");

http.createServer(function(req, res) {
    req.url = req.url == "/" ? "/index.html" : req.url;
    switch (req.url) {
      case "/test1.js":
        res.writeHead(200, {
          "Content-Type": "text/javascript"
        });
        res.end(fs.readFileSync("./test1.js"));
        break;

      case "/data.txt":
        res.writeHead(200, {
          "Content-Type": "text/plain"
        });
        res.end(fs.readFileSync("./data.txt"));
        break;
      case "/index.js":
        res.writeHead(200, {
          "Content-Type": "text/plain"
        });
        var note = new Date();
        // while(note){
        //res.end(JSON.stringify(note+1))
        // note=note-1;
        // }
        //setInterval(note+1),1000)
        res.end(JSON.stringify(note));

        break;
      default:
        res.writeHead(200, {
          "Content-Type": "text/html"
        });
        res.end(fs.readFileSync("./public" + req.url));
        //res.end('obj.name')
        break;
    }
  }).listen(8000);

console.log("listen at " + 8000);
