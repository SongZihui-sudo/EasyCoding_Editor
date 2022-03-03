/**
 *  日期：2022-3-2
 *  作者：宋子慧
 *  简介：主要涉及文件的保存
 */
//import { createRequire } from 'module';
//const require = createRequire(import.meta.url); 
//var FileSaver = require('file-saver');  
document.write("<script language=javascript src="+"../node_modules/file-saver/dist/FileSaver.min.js"+"></script>");
var file_data = "";
function _Output_file(filename){
  //debugger
  var Text = document.getElementById("Editor").contentWindow.body.childNodes[3].childNodes;
  //var from_text =window.frames['Editor'].document.getElementById("text_cursor");
  //var text_data = from_text.childNodes;
  for (let index = 0; index < Text.length; index++) {
    if(Text[index].localName=="br"){
      file_data+="\n";
    }
    else if(Text[index].localName=="span"){
      file_data+=Text[index].innerHTML;
    }
    else{
      continue;
    }
  }
  file_data = file_data.replace(/"&nbsp;"/g, " "); 
  file_data = file_data.replace(/&lt;/g, "<");    
  file_data = file_data.replace(/&gt;/g, ">");   
  var blob = new Blob([file_data], {type: "text/plain;charset=utf-8"});
  saveAs(blob,filename);
  alert('write ok'); 
  return 0;
}
/**
 *  
 */
