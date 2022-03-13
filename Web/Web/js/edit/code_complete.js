/**
 * author: 宋子慧
 * date: 2022-3-13
 * about:代码补全的前端处理
*/
//从返回的json解析出数据
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
  for(var i=0; i<res.length;i++){
    cc.innerHTML+='"<li id='+i+'>"'+res[i]+'</li>';
  }
  return 0;
}
//清空代码补全缓冲区
function clear_code_complete(cc){
  cc.innerHTML = "";
  return 0;
}
