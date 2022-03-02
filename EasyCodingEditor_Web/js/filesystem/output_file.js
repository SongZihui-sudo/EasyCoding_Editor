/**
 *  日期：2022-3-2
 *  作者：宋子慧
 *  简介：主要涉及文件的操作，读入与保存
 */
//import { createRequire } from 'module';
//const require = createRequire(import.meta.url); 
//var FileSaver = require('file-saver');  
document.write("<script language=javascript src="+"..\/..\/node_modules/file-saver/dist/FileSaver.min.js"+"></script>");
function _Output_file(filename){
  debugger
  var Text = document.getElementById("Editor").contentWindow.body.childNodes[3].childNodes;
  //var from_text =window.frames['Editor'].document.getElementById("text_cursor");
  //var text_data = from_text.childNodes;
  for (let index = 0; index < Text.length; index++) {
    if(Text[index].localName=="br"){
      var blob = new Blob(["\n"], {type: "text/plain;charset=utf-8"});
      saveAs(blob,filename);
    }
    else if(Text[index].localName=="span"){
      var blob = new Blob([Text[index].innerHTML], {type: "text/plain;charset=utf-8"});
      saveAs(blob,filename);
    }
    else{
      continue;
    }
  }
  alert('write ok'); 
  return 0;
}
/**
 *  
 */
