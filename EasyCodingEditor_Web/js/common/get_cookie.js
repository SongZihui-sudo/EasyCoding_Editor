/**
 * 日期：2022-3-3
 * 作者：宋子慧
 * 主要涉及页面中cookie的获取
*/
var module_path = "<script type =\"module\"src =\"../node_modules/js-cookie/dist/js.cookie.js\"></script>";
document.write(module_path);
debugger
//import Cookies from 'js-cookie';
function Get_cookie(name){
  return Cookies.get(name);
}
