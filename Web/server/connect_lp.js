/**
 * author: 宋子慧
 * date: 2022-3-12
 * about:关于nodejs服务端与语言服务器的交互
 **/
const { spawn } = require('child_process');
const as = require('./auto_save');
var ass = new as();
//消息对象
class message_node{
  bit;
  result;
  details;
  //构造函数，初始化
  constructor(){
    this.bit = 0;
    this.result = [];
    this.details = 0;
  };
}
function connect_lp(){
  var message_line = new Message_Line();
  this.connection = function(filename,str,path){
    var index = 0;
    const server = spawn(filename);
    var message = '{"version": "1.0.0", "request": {"Autocomplete": {"before":'+'"'+str+'"'+', "after": "", "region_includes_beginning": true, "region_includes_end": true, "filename":'+path+', "correlation_id": 1}}}'//./Temporary_Files/file.out
    server.stdin.write(message+"\n");
    server.stdout.on('data', (data) => {    
      console.log('language server:start success!!!'); 
      //setTimeout(() => console.log('sleeping....'), 10);
      var context = data.toString();
      if(context!='null'){
        var mes_node = new message_node();
        mes_node.details = index;
        mes_node.bit = 1;
        mes_node.result = context;
        message_line.push(mes_node);
        console.log('Message Line:push success!!!');
        //message_line.iterater(message_line.whichsend())
        var cur = message_line.whichsend();
        console.log('Message Line: %s',cur.result);
        //ass.write('../Web/json/codecomplete/code_complete.json',message_line.iterater(message_line.whichsend()));
      }
      console.log(`language server: ${data}`);
      index++; 
    });
    server.stderr.on('data', (data) => {
      console.error(`language server:${data}`);
    });
    server.on('close', (code) => {
      server.kill();
      if (code !== 0) {
        console.log(`language server process exited with code ${code}`);
      }
    });
    //test example
    //str = 'Hello H';
    //path = 'null';
    return server;
  }
}
//消息队列
class Message_Line{
  //ptivate:
  #message_line;
  #len;
   //构造函数
  constructor(){
    this.#len = 0;
    this.#message_line = [];
  };
  push=function(mes){
    return this.#message_line.push(mes);;
  }
  //public:
  clear=function(){
    this.#message_line = [];
    return 0;
  }
  unshift=function(){
    return this.#message_line.unshift();
  }
  shift=function(){
    this.#message_line.shift();
  }
  pop=function(){
    return this.#message_line.pop();
  }
  //根据detials进行冒泡排序
  whichsend = function(){
    for (var index = 0; index < this.#len-1; index++) {
      for(var j = 0;j < this.#len-1-index; j++) {
        var from = null;
        if(this.#message_line[j].details>this.#message_line[j+1].details){
          from = this.#message_line[j];
          this.#message_line[j] = this.#message_line[j+1];
          this.#message_line[j+1] = from;
        }
      }
    }
    console.log(this.#message_line);
    return this.shift();
  }
  iterater = function(index){
    if(index<0||index>this.length()-1){
      return null;
    }
    else{
      return this.#message_line[index];
    }
  }
  length = function(){
    return this.#len = this.#message_line.length-1;
  }
}
module.exports = connect_lp;
