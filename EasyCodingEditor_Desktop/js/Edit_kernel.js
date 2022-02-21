/*
    日期：2022-2-18
    作者：宋子慧
    编辑器核心
    只要涉及，文字的读取，还有按键读取等等。。
*/
var body = document.getElementById("win");
var text_cursor = document.getElementById("text_cursor");    
var cursor = document.getElementById("cursor");
var pos_x = 0;
var pos_y = 0;
var line = 0;
var cow = 0;
const w_bit = 7;
const h_bit = 20;
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
 * 定义piece_table
 */
//编辑器核心  
function right(){  
  pos_x++;
  //pos_x++;
  if(pos_x>=pos_buf.length){
    pos_x = pos_buf.length;
    SetPos(pos_buf[pos_x],pos_y);
  }  
  cursor.style.left = pos_buf[pos_x]+"px";
  connect_main("x"+(pos_x).toString());
}
function left(){ 
  pos_x--;
  //pos_x--; 
  if (pos_x-1<0) {
    pos_x=0;
    SetPos(0,pos_y);
  }  
  cursor.style.left = pos_buf[pos_x-1]+"px";
  connect_main("x"+(pos_x).toString());
}
function up() {  
  cursor.style.top = cursor.offsetTop-h_bit+"px";
  pos_y = parseInt((cursor.offsetTop)/h_bit);
  if (pos_y<=0) {
    pos_y=0;
    SetPos(pos_x,0);
  }  
  connect_main("y"+(pos_y).toString());
}

function down(){   
  cursor.style.top = cursor.offsetTop+h_bit+"px";
  pos_y = parseInt((cursor.offsetTop)/h_bit);  
  connect_main("y"+(pos_y).toString());
}
//回车
function Enter(){
  FileBuf.push_insert('/n');  
  FileBuf.Text_Show(FileBuf.piece_link_root);
  pos_y++;
  return 0;
}
//退格键
function BackSpace(){
  FileBuf.pop_delete();
  FileBuf.Text_Show(FileBuf.piece_link_root);
  return 0;
}
//Tab键
function Tab(){
  FileBuf.push_insert("/s");
  FileBuf.push_insert("/s");
  FileBuf.push_insert("/s");
  FileBuf.push_insert("/s");
  pos_x++;
  FileBuf.Text_Show(FileBuf.piece_link_root);
}
//空格键
function Space(){
  //debugger
  FileBuf.push_insert("/s");
  pos_x++;
  pos_y++;
  FileBuf.Text_Show();
  return 0;
}
//翻页键
function Page_up(){
  return 0;
}
//翻页键下
function Page_down(){
  return 0;
}