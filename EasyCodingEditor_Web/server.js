/**
 * author: 宋子慧
 * date: 2022-3-11
 * about:socket的服务端
 * 使用了ws库
**/
const WebSocket = require('ws');
const as = require('./auto_save');
const clp = require('./connect_lp');
const wss = new WebSocket.Server({ port: 8080 });
const ass = new as();
const clps = new clp();
var bit = 0;
var str = "";
var language;
wss.on('connection', function connection(ws) {
  //console.log('socket connect success!!!');
  ws.on('message', function incoming(message) {
    console.log('received: %s', message);
    if(message=="0"){
      //console.log('str: %s',str);
      //console.log('bit:%d',bit);
      var _path;
      if (bit == 1) {
        _path = "./Temporary_Files/file."+language;
        ass.write(_path,str);
      }
      else if(bit == 2) {
        _path = "./Temporary_Files/cur."+language;
        ass.write(_path,str);
      }
      //console.log('_path: %s',_path);
      if(str&&bit==2) {
        clps.connection("./TabNine_Client/bin/TabNine.exe",str,_path);
      }
      bit = 0;
    }
    else if(message=="2"||bit==1){
      if(bit){
        str+=message+"\n";
      }
      bit = 1;
    }
    else if(message=="1"||bit==2){
      if(bit){
        str = message;
      }
      bit = 2;
    }
    else if(message=="3"||bit==3){
      language = message;
      bit = 3;
    }
  });
  ws.send('ok!!!');
});

