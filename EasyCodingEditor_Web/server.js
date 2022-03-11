/**
 * author: 宋子慧
 * date: 2022-3-11
 * about:socket的服务端
 * 使用了ws库
**/
const WebSocket = require('ws');
const as = require('./auto_save');
const wss = new WebSocket.Server({ port: 8080 });
const ass = new as();
var bit = 0;
var str = "";
wss.on('connection', function connection(ws) {
  ws.on('message', function incoming(message) {
    console.log('received: %s', message);
    if(message=="0"){
      console.log('str: %s',str);
      console.log('bit:%d',bit);
      var _path;
      if (bit == 1) {
        _path = "./TabNine_Client/Temporary_Files/file.out";
        console.log('_path: %s',_path);
      }
      else if(bit == 2) {
        _path = "./TabNine_Client/Temporary_Files/cur.out";
        console.log('_path: %s',_path);
      }
      ass.write(_path,str);
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
  });
  ws.send('ok!!!');
});

