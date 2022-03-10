/**
 * author: 宋子慧
 * date: 2022-3-10
 * about:关于web socket客户端
 */
var ws;
function Websocket_init(){
  debugger
  ws = new WebSocket('ws://121.40.165.18:8800');
  ws.onopen = function () {
    console.log('ws onopen');
  };
  return 0;
}

function send(message){
  ws.send('from client:'+message);
  return 0;
}

function accept(){
  ws.onmessage = function (e) {
    console.log('ws onmessage');
    console.log('from server: ' + e.data);
  };
  return 0;
}
