/**
 *  日期：2022-2-27
 *  作者：宋子慧
 * 主要内容：
 * 关于编辑器的主题选择，直接通过js来切换，html各个组件的css样式颜色。
 * 可以通过拓展json文件的形式来拓展主题和修改主题
 * 
 */
//读取相应的json文件
function read_json(url,file,bit){
  var json_data;
  var Uurl;
  //debugger
  if(bit==1){
    Uurl = "../json/theme/"+file+".json";
  }
  else if(bit==2){
    Uurl = url+file;
  }
  $.ajax({
      url: Uurl,
      type: "GET",
      dataType: "json",
      success: 
      function (data) {
        json_data = data;
        displayData(json_data);
        if(bit==1){
          theme_chose(json_data);
        }        
        else if(bit==2){
          show_results(code_complete(json_data));
        }
      }
  });
}
var displayData= function(json_data){
  console.log(json_data);
}
//初始化为默认主题
var default_theme = {
  "bit":"1",
  "backgroundculor": "#24426E",
  "sidemenucolor": "#143669",
  "fontcolor":"#FFFFFF",
  "hightcorlor":"#FFFF00",
  "hovercolor":"#3366FF",
  "cursorcolor":"#00FF33"
};
var theme_data = {
  "bit":undefined,
  "backgroundculor":undefined,
  "sidemenucolor":undefined,
  "fontcolor":undefined,
  "hightcorlor":undefined,
  "hovercolor":undefined,
  "cursorcolor":undefined
};
//进行主题切换
function theme_chose(_json_data){
  //debugger
  if(theme_data == null||theme_data==undefined||_json_data==undefined||_json_data==null){
    return 0;
  }
  //debugger
  var get_body = document.body;
  get_body.style.backgroundColor = _json_data.backgroundculor;
  var body_childs = document.all;
  for (let index = 0; index < body_childs.length; index++) {
    if(body_childs[index].id == "top_menu"){
      body_childs[index].style.backgroundColor = _json_data.sidemenucolor;
      honer_change('top_menu',_json_data.hightcorlor,_json_data.sidemenucolor);
    }
    else if(body_childs[index].id == "bottom_menu"){
      body_childs[index].style.backgroundColor = _json_data.sidemenucolor;
    }
    else if(body_childs[index].id == "shelldark"){
      body_childs[index].style.backgroundColor = _json_data.sidemenucolor;
      honer_change('shelldark',_json_data.hightcorlor,_json_data.sidemenucolor);
    }
    else if(body_childs[index].id == "right_menu"){
      body_childs[index].style.backgroundColor = _json_data.sidemenucolor;
    }
    else if(body_childs[index].id == "menu_start"){
      body_childs[index].style.backgroundColor = _json_data.backgroundculor;
      //debugger
      body_childs[index].style.color = _json_data.fontcolor;
    }
    else if(body_childs[index].id == "cursur"){
      body_childs[index].style.backgroundColor = _json_data.cursorcolor;
    }
    else if(body_childs[index].id == "text_cursor"){
      body_childs[index].style.backgroundColor = _json_data.backgroundculor;
      body_childs[index].style.color = _json_data.fontcolor;
    }
    else if(body_childs[index].id == "set-menu"){
      body_childs[index].style.color = _json_data.fontcolor;
    }
    else{
      continue;
    }
  }
  //debugger
  font_color = _json_data.hightcorlor;
  save_theme(_json_data);
  return 0;
}
//刷新主题
function refresh_theme(){
  //debugger
  var bit = window.sessionStorage.getItem("bit");
  if(bit==undefined||bit==null){
    theme_data = assignment(theme_data,default_theme);
  }
  else{
    theme_data.backgroundculor = window.sessionStorage.getItem("backgroundculor");
    theme_data.bit = bit;
    theme_data.cursorcolor = window.sessionStorage.getItem("cursorcolor");
    theme_data.fontcolor = window.sessionStorage.getItem("fontcorlor");
    theme_data.hightcorlor = window.sessionStorage.getItem("hightfontcolor");
    //font_color = theme_data.hightcorlor;
    theme_data.hovercolor = window.sessionStorage.getItem("hovercolor");
    theme_data.sidemenucolor = window.sessionStorage.getItem("sidemenucolor");
  }
  theme_chose(theme_data);
  return 0;
}
//js 操作hover
function honer_change(id,color1,color2){
    //获取所有的li标签
  var list = document.getElementById(id).childNodes;
  for (var i = 0; i < list.length; i++) {
    //为li注册鼠标进入事件
    list[i].onmouseover = function () {
    //设置其背景颜色为黄色
      this.style.backgroundColor = color1;
    };
  //为li注册鼠标离开事件
    list[i].onmouseout = function () {
      //恢复到这个标签默认的颜色
      this.style.backgroundColor = color2;
    };
  }
  return 0;
}
//赋值
function assignment(_theme_data,data){
  //debugger
  _theme_data.backgroundculor = data.backgroundculor;
  _theme_data.cursorcolor = data.cursorcolor;
  _theme_data.fontcolor = data.fontcolor;
  _theme_data.hightcorlor = data.hightcorlor;
  _theme_data.hovercolor = data.hovercolor;
  _theme_data.sidemenucolor = data.sidemenucolor;
  return _theme_data;
}
//保存主题信息
function save_theme(change_data){
  //debugger
  window.sessionStorage.setItem("bit",change_data.bit);
  window.sessionStorage.setItem("backgroundculor", change_data.backgroundculor);
  window.sessionStorage.setItem("cursorcolor", change_data.cursorcolor);
  window.sessionStorage.setItem("fontcorlor", change_data.fontcolor);
  window.sessionStorage.setItem("hightfontcolor", change_data.hightcorlor);
  window.sessionStorage.setItem("hovercolor", change_data.honer_change);
  window.sessionStorage.setItem("sidemenucolor", change_data.sidemenucolor);
  return 0;
}
