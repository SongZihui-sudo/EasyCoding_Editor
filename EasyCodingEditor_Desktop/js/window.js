var a3 = document.getElementById("top7");
var a4 = document.getElementById("top5");
var a5 = document.getElementById("top6");
var max_num = 0;

a3.onclick = function CLOSE(){
  connect_main('close');
}

a4.onclick = function MAX(){
  max_num++;
  if (max_num%2) {
    connect_main('big');
  }
  else{
    connect_main('cancel_max');
  }
}
a5.onclick = function MINI(){
  connect_main('small');
}