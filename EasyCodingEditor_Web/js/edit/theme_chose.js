/**
 *  日期：2022-2-27
 *  作者：宋子慧
 * 主要内容：
 * 关于编辑器的主题选择，直接通过js来切换，html各个组件的css样式颜色。
 * 可以通过拓展json文件的形式来拓展主题和修改主题
 * 
 */
 var json_data;
function theme_chose(value){
  debugger
  read_json(value);
  console.log(json_data);
  //var get_body = document.body;
  //get_body.style.background = json_data.background;
  return 0;
}
//读取相应的json文件
function read_json(file){
  $.ajax({
      url: "../json/theme/"+file+".json",
      type: "GET",
      dataType: "json",
      success: 
      function (data) {
        json_data = JSON.parse(data);
        displayData(data)
      }
  });
}
var displayData= function(data){
  console.log(data);
}
