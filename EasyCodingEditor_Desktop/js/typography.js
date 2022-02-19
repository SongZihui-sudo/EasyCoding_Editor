var pos_buf;
pos_buf = new Array;
pos_buf = [];
var id = 0;
//设置光标位置
function SetPos(x,y){  
    cursor.style.left=((x+1)*w_bit)/16+"em";
    cursor.style.top=y*h_bit+"px";
  }
  //设置内容显示位置
  function SetText(x,y){  
    text_cursor.style.left=(x+1)*w_bit+"px";
    text_cursor.style.top=(y)*h_bit+"px";
  }
  //指定位置输出输出函数
  function mvprinth(x,y,str){
    SetText(x,y);  
    printh(str);
    return 0;
  }
  //输出函数
  function printh(str){
    id++;  
    str = "<span"+" "+"id="+id+">"+str+"</span>";
    text_cursor.innerHTML =str; 
    //debugger
    span = document.getElementById(id);
    var len = span.offsetWidth;
    //debugger
    cursor.style.left = len+w_bit + "px";        
    cursor.style.top = parseInt(text_cursor.offsetTop) + "px";
    //debugger
    pos_buf.push(len+w_bit);
    pos_buf = unique(pos_buf);
    pos_x = pos_buf.length;
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
  
  function CLEAR(){
    var space = "";
    text_cursor.innerHTML = space;
  }
  
  function Set_color(str){
    text_cursor.style.color = str;
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