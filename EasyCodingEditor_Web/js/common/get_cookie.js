/**
 * 日期：2022-3-3
 * 作者：宋子慧
 * 主要涉及页面中cookie的获取
*/
//debugger
//import Cookies from '../../node_modules/js-cookie/dist/js.cookie';
document.write("<script type ='text/javascript' src ='../../node_modules/js-cookie/dist/js.cookie.js'></script> ");
function Get_cookie(name){
  var res = Cookies.get(name);
  return res;
}
