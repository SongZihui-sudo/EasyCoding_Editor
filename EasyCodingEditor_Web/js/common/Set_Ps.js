//滚动到页面中指定的元素位置
//参数：指定的对象
//返回值：无
function setPS (e) {
    window.scrollTo (getPoint(e).x, getPoint(e).y);
}
