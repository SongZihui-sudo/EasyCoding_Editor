/**
 * 日期：2022-3-3
 * 作者：宋子慧
 * 主要涉及页面中cookie的获取
*/
//debugger
//import Cookies from '../../node_modules/js-cookie/dist/js.cookie';
function Get_storge(name){
  var res = window.sessionStorage.getItem(name);
  return res;
}
