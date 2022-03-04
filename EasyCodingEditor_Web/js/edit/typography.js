/*
*     typography.js
*     author:宋子慧
*     关于字符串在html页面上的渲染
*---------------------------------------------------
*/
var pos_buf = [];//存一行内的光标位置 
pos_buf.push(0);
var line_pos_buf; //存全部文件内的光标位置
line_pos_buf = [];
line_pos_buf.push([0]);
var pos_x = 0;//x方向位置
var pos_y = 0;//y方向位置
var text_cursor = document.getElementById("text_cursor");
//设置光标位置
function SetPos(x,y){  
    cursor.style.left=((x+1)*w_bit)/16+"em";
    cursor.style.top=y*h_bit+"px";
}
var span_buffer = "";
//输出函数
var input_num = 0;
function printh(str){
  //debugger
  input_num++;
  if(bit_enter||input_num==1){    
    var span = "<span class = \"text\" id="+"y"+pos_y+">"+"</span>";
    text_cursor.innerHTML += span; 
    bit_enter = 0;
    cursor.style.left = text_cursor.offsetWidth+"px";
    cursor.style.top = h_bit*pos_y + "px";
    pos_x++;
  }
  else{
    var span_text = document.getElementById("y"+pos_y);  
    if(!span_text.innerText){
      span_text.innerHTML = str;   
    }
  }
  span_buffer = "<span class = \"text\" id="+"y"+pos_y+">"+str+"</span>";    
  return 0;
}
//获取光标位置
function get_cursor(){
  var postion = {
    x : 0,
    y : 0
  };
  postion.x = cursor.style.left;
  postion.y = cursor.style.top;
  return postion;
} 
//清空内容
function CLEAR(){
  var space = "";
  text_cursor.innerHTML = space;
}
//数组去重
function unique(arr){
  var res = [];
  var obj = {};
  for(var i=0; i<arr.length; i++){
    if( !obj[arr[i]] ){
      obj[arr[i]] = 1;
      res.push(arr[i]);
    }
  } 
  return res;
}
//插入一个新的span
var pre_line = null;
var cur_line = null;
function insert_new_span(){
  CLEAR();
  //debugger
  //pre_line = "<span class = \"text\" id="+"y"+pos_y+">"+pre_line+"</span>";
  for (let index = 0; index < pos_y; index++) {
    const element = FileBuf.buffer[index];
    text_cursor.innerHTML+=element+"<br>";
    var _changespaicalchar = document.getElementById("y"+index);
        //处理一下特殊字符
    _changespaicalchar.innerHTML = _changespaicalchar.innerHTML.replace(/,/g, "");    
    _changespaicalchar.innerHTML = _changespaicalchar.innerHTML.replace(/" "/g, "&nbsp;"); 
    _changespaicalchar.innerHTML = _changespaicalchar.innerHTML.replace(/</g, "&lt;");    
    _changespaicalchar.innerHTML = _changespaicalchar.innerHTML.replace(/>/g, "&gt;");   
  }
  if(cur_line!=null&&pre_line!=null){
    cur_line = "<span class = \"text\" id="+"y"+pos_y+">"+cur_line+"</span>";
    text_cursor.innerHTML += cur_line +"<br>";
    //var insert_span = document.getElementById("y"+pos_y); 
    pos_y++;
    text_cursor.innerHTML+="<span class = \"text\" id="+"y"+pos_y+">"+"</span>"+"<br>";
    var change_lastspan = document.getElementById("y"+pos_y);
    change_lastspan.innerHTML = pre_line;
  }
  else{
    cur_line = "<span class = \"text\" id="+"y"+pos_y+">"+"</span>";
    pos_y++;
    pre_line = "<span class = \"text\" id="+"y"+pos_y+">"+"</span>";
    text_cursor.innerHTML+=cur_line+"<br>"+pre_line+"<br>";
  }  
  for (let index = pos_y; index < FileBuf.buffer.length; index++) {
    const element = FileBuf.buffer[index];
    text_cursor.innerHTML.id = "y"+index;
    text_cursor.innerHTML+=element+"<br>";
    var _changespaicalchar = document.getElementById("y"+index);
        //处理一下特殊字符
    _changespaicalchar.innerHTML = _changespaicalchar.innerHTML.replace(/,/g, "");    
    _changespaicalchar.innerHTML = _changespaicalchar.innerHTML.replace(/" "/g, "&nbsp;"); 
    _changespaicalchar.innerHTML = _changespaicalchar.innerHTML.replace(/</g, "&lt;");    
    _changespaicalchar.innerHTML = _changespaicalchar.innerHTML.replace(/>/g, "&gt;");   
  }
  return 0;
}
var cur_str = "";
function delete_aspan(){
  //debugger
  CLEAR();
  for (let index = 0; index < pos_y-1; index++) {
    const element = FileBuf.buffer[index];
    text_cursor.innerHTML+=element+"<br>";
    var _changespaicalchar = document.getElementById("y"+index);
          //处理一下特殊字符
    _changespaicalchar.innerHTML = _changespaicalchar.innerHTML.replace(/,/g, "");    
    _changespaicalchar.innerHTML = _changespaicalchar.innerHTML.replace(/" "/g, "&nbsp;"); 
    _changespaicalchar.innerHTML = _changespaicalchar.innerHTML.replace(/</g, "&lt;");    
    _changespaicalchar.innerHTML = _changespaicalchar.innerHTML.replace(/>/g, "&gt;");   
  }
  if(cur_str!=null){
    cur_str = "<span class = \"text\" id="+"y"+(pos_y-1)+">"+cur_str+"</span>";
    text_cursor.innerHTML+=cur_str+"<br>";
  }
  for (let index = pos_y+1; index < FileBuf.buffer.length; index++) {
    const element = FileBuf.buffer[index];
    text_cursor.innerHTML.id = "y"+index -1;
    text_cursor.innerHTML+=element+"<br>";
    var _changespaicalchar = document.getElementById("y"+index);
          //处理一下特殊字符
     _changespaicalchar.innerHTML = _changespaicalchar.innerHTML.replace(/,/g, "");    
    _changespaicalchar.innerHTML = _changespaicalchar.innerHTML.replace(/" "/g, "&nbsp;"); 
    _changespaicalchar.innerHTML = _changespaicalchar.innerHTML.replace(/</g, "&lt;");    
    _changespaicalchar.innerHTML = _changespaicalchar.innerHTML.replace(/>/g, "&gt;");   
  }
  return 0;
}
//去除0以前的元素
function shift_before_zero(array){
  //debugger
  if(!array,length)
    return array;
  for (let index = 0; index < array.length; index++) {
    const element = array[index];
    if (element!=0) {
      array.shift();
    }
    else{
      break;
    }
  }
  return array;
}
//显示
function update_buffer(str){
  var ischange = str;
  FileBuf.clearPrintBuf();
  var get_text = document.getElementById("y"+pos_y);
  if(ischange!=get_text.innerHTML){
    //debugger
    get_text.innerHTML = "";
    //debugger
    get_text.innerHTML = ischange;    
    FileBuf.buffer[pos_y] = "<span class = \"text\" id="+"y"+pos_y+">"+ischange+"</span>";
  }
  //debugger
  var len = get_text.offsetWidth;
  h_bit = get_text.offsetHeight;
  cursor.style.left = len + "px";        
  cursor.style.top = pos_y*h_bit + "px";
  //debugger
  pos_buf.push(len);      
  pos_buf = unique(pos_buf);
  pos_buf = shift_before_zero(pos_buf);
  if(pos_buf.length){
    pos_x = pos_buf.length;    
  }
  else{
    pos_x = 0;
    pos_buf.push(0);
  }
  return 0;
}
//更新屏幕缓冲区
function refresh(){
  //debugger
  var childs = text_cursor.childNodes;
  var j = 0;
  for (let index = 0; index < childs.length; index++) {
    var element = "<span class = \"text\" id="+"y"+j+">"+childs[index].innerHTML+"</span>"
    if(childs[index].localName == "br"){
      continue;
    }
    else if(FileBuf.buffer[j]!=element){
      FileBuf.buffer[j] = element;
      j++;
    }
    else if(FileBuf.buffer[j]==element){
      j++;
    }
    else{
      continue;
    }
  }
  return 0;
}
var code_highlight_buffer = [];
var chl_num = 0;
//分割span，进行代码高亮显示
function span_cover(fstart,cur_str,y){
  //debugger
  chl_num++;
  var code_highlight_span = "<span class=\"codehightlight\" id="+chl_num+">"+cur_str+"</span>";
  var div_codehighlight = document.getElementById("code_highlight");
  if(code_highlight_buffer[chl_num]){
    code_highlight_buffer[chl_num] = code_highlight_span;
  }
  else{
    code_highlight_buffer.push(code_highlight_span);
  }
  div_codehighlight.innerHTML+=code_highlight_span;
  location_code_highlight(fstart,y);
  return 0;
}
var code_highlight_y_buffer = [];
//确定代码高亮位置
var font_color;
function location_code_highlight(sstart,y){
  //debugger
  var Get_code_highlight_span = document.getElementById(chl_num);
  Get_code_highlight_span.style.left = pos_buf[sstart]+"px";
  Get_code_highlight_span.style.top = y+"px";
    //在设计上高亮颜色跟随编辑器主题
  Get_code_highlight_span.style.color = font_color;
  return 0;
}
//进行代码高亮
function to_Code_highlight(){
  //debugger
  Clear_code_highlight();
  var element_childs = text_cursor.childNodes;
  for (let index = 0; index < element_childs.length; index++) {
    if(element_childs[index].localName=="span"){
      var y_site = document.getElementById(element_childs[index].id);
      //debugger
      language = Get_cookie("language");
      Codehightlight(language,y_site.innerHTML,y_site.offsetTop);
    }
    else{
      continue;
    }
  }
  //return 0;
}
//代码高亮清除
function Clear_code_highlight(){
  var highlight = document.getElementById("code_highlight");
  highlight.innerHTML = "";
  return 0;
}
