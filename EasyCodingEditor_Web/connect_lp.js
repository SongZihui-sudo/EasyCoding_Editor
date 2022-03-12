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
      ass.write('./Web/json/code_complete.json',context);
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
    path = 'null';
    var message = '{"version": "1.0.0", "request": {"Autocomplete": {"before":'+'"'+str+'"'+', "after": "", "region_includes_beginning": true, "region_includes_end": true, "filename":'+path+', "correlation_id": 1}}}'//./Temporary_Files/file.out
    server.stdin.write(message+"\n");
    return server;
  }
}
module.exports = connect_lp;
