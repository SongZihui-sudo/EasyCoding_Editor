/**
 *   日期：2022-2-27
 *   简介：主要在这里实现了代码高亮
 *   作者：宋子慧
 */
var str_bit = [];
function Codehightlight(language,str,y){
  debugger
  var len = 0;
  var fstart = 0;
  if(language == "c"||"cpp"||"c++"||"cc"){
    for(let i = 0;i < hight_light.length;i++){
      fstart = str.search(hight_light[i]);
      if(fstart!=-1){
        find_bit = 1;
        len = hight_light[i].length;
        span_cover(fstart,hight_light[i],y);
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

