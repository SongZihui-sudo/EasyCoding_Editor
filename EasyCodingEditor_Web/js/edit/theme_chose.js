/**
 *  日期：2022-2-27
 *  作者：宋子慧
 * 主要内容：
 * 关于编辑器的主题选择，直接通过js来切换，html各个组件的css样式颜色。
 * 可以通过拓展json文件的形式来拓展主题和修改主题
 * 
 */
function theme_chose(value){
  //debugger
  var json_data = read_json(value);
  var get_body = document.body;
  //get_body.style.background = json_data.background;
  return 0;
}
//读取相应的json文件
function read_json(file){
  var json;
  var url = "../theme/"+file+".json";/*json文件url，本地的就写本地的位置，如果是服务器的就写服务器的路径*/
  var request = new XMLHttpRequest();
  request.open("get", url);/*设置请求方法与路径*/
  request.send(null);/*不发送数据到服务器*/
  request.onload = function () {/*XHR对象获取到返回信息后执行*/
      if (request.status == 200) {/*返回状态为200，即为数据获取成功*/
          json = JSON.parse(request.responseText);
          for(var i=0;i<json.length;i++){
              console.log(json[i].name);
          }
          console.log(json);
      }
  }
  return json;
}
