#! https://zhuanlan.zhihu.com/p/480221124
# 文本编辑器设计--TabNine客户端的开发

现在市面上已经存在了很多代码补全的软件，例如[1]国外的Kite、Codota、TabNine、GitHub Copilot、微软IntelliCode，国内的阿里云Cosy、AIXcoder。在这里我们采用了TabNine来进行代码补全服务器的开发。
## 开始
## 一. 安装TabNine的二进制文件
我们访问TabNine的github主页([TabNine](https://github.com/codota/TabNine)),之后把这个代码仓库克隆到本地。[2]根据官方教程，我们直接运行```dl_binaries.sh```，这样会下载好```windows，linux，mac```这三种平台上的TabNine程序。  
## 二. TabNine的api
[2]根据官方教程，对TabNine的请求都是json的形式，我们可以输入官方给的测试语句
```json
{"version": "1.0.0", "request": {"Autocomplete": {"before": "Hello H", "after": "", "region_includes_beginning": true, "region_includes_end": true, "filename": null, "correlation_id": 1}}}
```   
我们可以得到回复：   
```json
{"old_prefix":"H","results":[{"new_prefix":"Hello","old_suffix":"","new_suffix":""}],"user_message":[],"correlation_id":1}
```
### 官方解释：
```js
A few things to note:
    The protocol is versioned. The protocol versions are the same as TabNine versions. To guarantee forward compatibility with future versions of TabNine, pass the current TabNine version (or any previous version) as the protocol version.  
    The completion position is specified by giving the strings before and after the cursor. If these strings are very long, you can truncate them. In this case you should set region_includes_beginning or region_includes_end to false to indicate that the strings do not extend to the beginning or end of the file, respectively.  
    The recommended threshold for truncation is 100 KB.
    Autocomplete responses contain a field user_message which is a message that should be displayed to the user. For example, this is used to inform the user when a language server fails to start, or when TabNine hits the index size limit.
    The correlation_id field can be passed as a verification token that will be returned in response.

    AutocompleteArgs {
        before: string,
        after: string,
        filename: string | null,
        region_includes_beginning: bool,
        region_includes_end: bool,
        max_num_results: int | null,
        correlation_id: int | null,
    }

```
### 我的理解：    
#### request:
```before``` 后为当前的输入（光标前的内容），类型为string，泛指用户在编辑器中的输入。    
```after``` 可以为空，也可以为string，也可认为是光标后的内容。     
```filename``` 可以为null，也可以为string，但其不为null时，TabNine会根据filename所指明的文件进行更加个性化的代码补全。     
#### reply:
```old_prefix``` 光标前的内容（未补全的内容）   
```result``` TabNine代码补全的结果   
```new_prefix``` 代码补全的内容   
```user_message``` TabNine返回给用户的一些信息。（主要包含一些错误提示）    
#### 注意：
1.错误提示:（以C/C++为例） 
```js
Type TabNine::sem to enable semantic completion for C/C++.","The completion backend is `clangd`, which you will need to install manually.","Type TabNine::no_sem to suppress this message.","To learn more about semantic completion, see https://tabnine.com/semantic."
``` 
错误提示要我们在编辑器中输入```TabNine::sem```来开启C/C++的代码补全，但是因为我们是要开发一个第三方的TabNine客户端，我们在上层并没有编辑器，所以我们在TabNine的标准输入中把请求json的before的值设为```TabNine::sem```这样TabNine就会开启相应语言的补全并开始下载相应的语言服务器。   
## 三.与TabNine.exe的通讯    
在Web端的开发中我采用了nodejs与TabNine的交互。   
我们可以打开```server\```下的language_server.js文件与connect_lp.js文件。在这里我们实现了与TabNine.exe的交互。     

首先我们在Web端与server端建立起socket连接，这样我们就可以在服务端接收到用户的实时输入。     
```标志位为1```时我们发送当前行（用户的输入）。    
```标志位为2```时我们会自动保存下用户当前输入的当前文件内容（用来获得更加精准的代码补全）。     
```标志位为3```时，我们发送用户当前编辑的文件的编程语言。     
```标志位为0```时。我们停止发送数据。这是connect_lp.js开始工作，通过nodejs的spawn函数来调用TabNine.exe,在通过nodejs提供的标准输入输出管道，向TabNine.exe的标准输入进行写入，之后获取到TabNine.exe的输出，再把输出写入为json发送给前端，在前端对json进行解析，完成代码补全。   
## references
[1][史上最全智能代码补全工具汇总](https://zhuanlan.zhihu.com/p/456957593)    
[2][HowToWriteAClient.md](https://github.com/codota/TabNine/blob/master/HowToWriteAClient.md)   
[3]connect_lp.js   
```js
/**
 * author: 宋子慧
 * date: 2022-3-12
 * about:关于nodejs服务端与语言服务器的交互
 **/
const { spawn } = require('child_process');
const as = require('./auto_save');
var ass = new as();
function connect_lp(){
  this.connection = function(filename,str,path){
    const server = spawn(filename);
    server.stdout.on('data', (data) => {     
      console.log('language server:start success!!!'); 
      var context = data.toString();
      if(context!='null'){
        ass.write('../Web/json/codecomplete/code_complete.json',context);
      }
      console.log(`language server: ${data}`);
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
    var message = '{"version": "1.0.0", "request": {"Autocomplete": {"before":'+'"'+str+'"'+', "after": "", "region_includes_beginning": true, "region_includes_end": true, "filename":'+path+', "correlation_id": 1}}}'//./Temporary_Files/file.out
    server.stdin.write(message+"\n");
    return server;
  }
}
module.exports = connect_lp;
```
[4]language_server.js 
```js
/**
 * author: 宋子慧
 * date: 2022-3-11
 * about:socket的服务端
 * 使用了ws库
**/
const WebSocket = require('ws');
const as = require('./auto_save');
const clp = require('./connect_lp');
const wss = new WebSocket.Server({ port: 8081 });
const ass = new as();
const clps = new clp();
var bit = 0;
var str = "";
var language;
wss.on('connection', function connection(ws) {
  //console.log('socket connect success!!!');
  ws.on('message', function incoming(message) {
    console.log('language server received: %s', message);
    if(message=="0"){
      //console.log('str: %s',str);
      //console.log('bit:%d',bit);
      var _path;
      if (bit == 1) {
        _path = "../Temporary_Files/file."+language;
        ass.write(_path,str);
      }
      else if(bit == 2) {
        _path = "../Temporary_Files/cur."+language;
        ass.write(_path,str);
      }
      //console.log('_path: %s',_path);
      if(str&&bit==2) {
        if(language=="null")  
          _path = "null";
        clps.connection("../4.1.16/bin/TabNine.exe",str,_path);
        ws.send('1');
        console.log('language server:send success!!!');
      }
      bit = 0;
    }
    else if(message=="2"||bit==1){
      if(bit){
        str+=message+"\n";
      }
      bit = 1;
    }
    else if(message=="1"||bit==2){
      if(bit){
        str = message;
      }
      bit = 2;
    }
    else if(message=="3"||bit==3){
      language = message;
      bit = 3;
    }
  });
});
```
[5][简·编辑器](https://github.com/SongZihui-sudo/EasyCoding_Editor)
