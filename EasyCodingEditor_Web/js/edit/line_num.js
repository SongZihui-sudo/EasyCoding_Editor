/**
 * author: 宋子慧
 * date: 2022-3-8
 * about:关于文件函数的统计
*/
//保存当前的行标
function save_linenum(){
  var linenum = pos_y+1;
  window.sessionStorage.setItem("linenum",linenum);
  return 0;
}
//读取当前的行标
function get_SessionSeorge(name) {
  var linenum = window.sessionStorage.getItem(name)
  if(linenum==null||!linenum||linenum==undefined){
    linenum = 1;
  }
  return linenum;
}
//显示当前行标
function show_linenum(number){ 
  //debugger
  var linenum = window.parent.document.getElementById('line_num');
  linenum.innerHTML = "";
  for(var i=0; i<number; i++){
    var line_cur = i+1;
    linenum.innerHTML +="<span class = Line id="+line_cur+">"+line_cur+"</span>"+"<br>";
  }
  return 0;
}

