/**
 * author: 宋子慧
 * date: 2022-3-10
 * about:关于web socket客户端
 */
function Websocket(message){
  var ws = new WebSocket('ws://127.0.0.1:4000');
  ws.onopen = function () {
    console.log('ws onopen');
    ws.send('from client:'+message);
  };
  ws.onmessage = function (e) {
    console.log('ws onmessage');
    console.log('from server: ' + e.data);
  };
  return 0;
}
