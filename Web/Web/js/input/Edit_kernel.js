/*
*    日期：2022-2-18
*    作者：宋子慧
*    编辑器核心
*    涉及按键读取。。。。。。。。
*/
var body = document.getElementById("win");  //div win
var text_cursor = document.getElementById("text_cursor"); //编辑器显示区    
var cursor = document.getElementById("cursor"); //光标div
var line = 0; 
var cow = 0;
var w_bit = 7;
var h_bit = 20;
var span;
var id_ = 0;
var WindosSize = {
    w:0,
    h:0
}
// 获取窗口的宽度和高度，不包括滚动条
WindosSize.h = document.documentElement.clientHeight;
WindosSize.w = document.documentElement.clientWidth;  
line = (WindosSize.h)/h_bit;
cow = (WindosSize.w)/w_bit; 
/**
 *  编辑器核心
 */
function right(){  
  //debugger
  pos_x++;
  //pos_x++;
  if(pos_x-1>=pos_buf.length){
    pos_x = pos_buf.length;
    cursor.style.left = pos_buf[pos_x]+"px";
    //SetPos(pos_buf[pos_x],pos_y);
    return 1;
  }  
  cursor.style.left = pos_buf[pos_x-1]+"px";
  return 0;
}
function left(){ 
  //debugger
  pos_x--;
  //pos_x--; 
  if (pos_x<=0) {
    pos_x=1;
    cursor.style.left = 0 + "px";
    return 1;
  }  
  cursor.style.left = pos_buf[pos_x-1]+"px";
  console.log("x"+pos_x);
  return 0;
}
function up() {
  //debugger
  cursor.style.top = cursor.offsetTop-h_bit+"px";
  if (pos_y<=0) {
    pos_y=0;
    SetPos(pos_x,0);
  }  
  line_pos_buf[pos_y] = pos_buf;
  //line_pos_buf.splice(pos_y,0,pos_buf);  
  pos_buf = line_pos_buf[pos_y-1];
  pos_x = pos_buf.length;
  cursor.style.left = pos_buf[pos_x-1]+'px';
  pos_y = parseInt((cursor.offsetTop)/h_bit);
  //pos_y--;
  FileBuf.change_head();
  return 0;
}
function down(){
  cursor.style.top = cursor.offsetTop+h_bit+"px";
  //line_pos_buf.splice(pos_y,0,pos_buf);  
  line_pos_buf[pos_y] = pos_buf;
  pos_buf = line_pos_buf[pos_y+1];
  pos_x = pos_buf.length;
  cursor.style.left = pos_buf[pos_x-1]+'px';
  pos_y = parseInt((cursor.offsetTop)/h_bit);  
  //pos_y++;
  FileBuf.change_head();
  return 0;
}
//回车
var bit_enter = 0;
var link_len = 0;
function Enter(){
  //debugger
  //更新x坐标方向缓存
  if(!line_pos_buf[pos_y].length){
    line_pos_buf.push(pos_buf);
  }
  else{
    line_pos_buf[pos_y] = pos_buf;
  }
  if(pos_x<FileBuf.head.len||pos_x==1){ 
    FileBuf.Sqilt();
    //debugger
    insert_new_span();    
    var index = 0;
    if(link_len){
      index = absolute_value(pos_x-link_len-1);
    }
    else{
      index = absolute_value(pos_x - FileBuf.head.len);
    }
    var new_linebuf = [];
    //debugger
    while(index&&index<=line_pos_buf[pos_y-1].length){
      //处理x方向的坐标缓存
      new_linebuf.unshift(line_pos_buf[pos_y-1].pop());
      index--;
    }
    //debugger
    line_pos_buf.splice(pos_y+1,0,new_linebuf);
    pos_buf = line_pos_buf[pos_y];
    //解决换行的偏移
    for (let index = 0; index < pos_buf.length; index++) {
      pos_buf[index] = pos_buf[index] - line_pos_buf[pos_y-1][line_pos_buf[pos_y-1].length-1];
    }
    pos_buf.unshift(0);
    pos_buf = unique(pos_buf);
    cursor.style.left = pos_buf[pos_buf.length-1]+"px";
    pos_x = pos_buf.length;
    var get_text = document.getElementById("y"+pos_y);
    h_bit = get_text.offsetHeight;
    SetPos(pos_x-1,pos_y);
  }
  else{
    //debugger
    CLEAR();
    span_buffer="";
    FileBuf.Sqilt();
    update_screen("","",0);
    pos_y++;  
    pos_x = 1;
    cursor.style.left = 0 + "px";
    var get_text = document.getElementById("y"+pos_y);
    h_bit = get_text.offsetHeight;
    cursor.style.top = pos_y*h_bit+"px";
    pos_buf = unique(pos_buf);
    //debugger
    line_pos_buf[pos_y-1] = pos_buf;
    //debugger
    line_pos_buf.splice(pos_y,0,[0]);
    pos_buf = [];
    pos_buf.push(0);
  }
  bit_enter++;
  sort_id();
  refresh(); 
  save_linenum(pos_y);
  show_linenum(get_SessionSeorge('linenum'));
  return 0;
}
//退格键
function BackSpace(){
  //debugger
  FileBuf.pop_delete();
  return 0;
}
//Tab键
function Tab(){
  FileBuf.push_insert(" ");
  FileBuf.push_insert(" ");
  FileBuf.push_insert(" ");
  FileBuf.push_insert(" ");
  return 0;
}
//空格键
function Space(){
  //debugger
  FileBuf.push_insert(" ");
  return 0;
}
//长度的绝对值
function absolute_value(num){
  var res = 0;
  if(num>=0){
    return res = num;
  }
  else{
    return res = -num;
  }
}
