/**
 *   日期：2022-2-27
 *   简介：主要在这里实现了代码高亮，借助了highlight.js库
 *   作者：宋子慧
 */
var str_bit = [];
function Codehightlight(language,str){
  var start = 0;
  var len = 0;
  if(language == "c"||"cpp"||"c++"||"cc"){
    for(let i = 0;i < hight_light.length;i++){
      if(start = str.search(hight_light[i])!=-1){
        len = hight_light[i].length();
        span_sqlite(start,len);
      }
      else{
        continue;
      }
    }
  }
  else{
    console.log("not found!!!");
  }
  return 0;
}

