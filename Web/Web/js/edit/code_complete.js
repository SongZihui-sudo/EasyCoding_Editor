/**
 * author: 宋子慧
 * date: 2022-3-13
 * about:代码补全的前端处理
*/
//从返回的json解析出数据
function send_message(){
  var ws = Websocket_("3");
  console.log('language:'+window.sessionStorage.getItem('language'));
  ws = Websocket_(window.sessionStorage.getItem('language'));
  ws = Websocket_("0");  
  var file = document.getElementById("text_cursor").childNodes;
  ws = Websocket_('2');
  for(var i = 0;i<file.length;i++){
    if(file[i].localName=='span'){
      ws = Websocket_(file[i].innerHTML);
    }
  }
  ws = Websocket_("0");
  ws = Websocket_("1");
  //console.log('cur:%s',get_lint.innerHTML); 
  //debugger 
  ws = Websocket_(file[pos_y].innerHTML);    
  ws = Websocket_("0");
  return 0;
}
function code_complete(json_data){
  debugger
  var code = [];
  for (var i = 0; i < json_data.results.length; i++){
    code.push(json_data.results[i].new_prefix);
  }
  return code;
}
//显示代码补全的结果
function show_results(res){
  debugger
  console.log(res);
  var cc = document.getElementById('code_complete');
  clear_code_complete(cc);
  cc.style.left = 0 +"px";
  cc.style.top = text_cursor.offsetTop + "px";
  if(res!=null){
    for(var i=0; i<res.length;i++){
      cc.innerHTML+='"<li id='+i+'>"'+res[i]+'</li>';
    }
  }
  return 0;
}
//清空代码补全缓冲区
function clear_code_complete(cc){
  cc.innerHTML = "";
  return 0;
}
