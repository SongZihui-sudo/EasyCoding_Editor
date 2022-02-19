const require = parent.window.require;
const ipcRenderer = require('electron').ipcRenderer;
function connect_main(str){
    ipcRenderer.on('render', function(event, arg) {
        console.log('render:'+arg+'\n'); // prints "我是主进程的test1" 
    });
    ipcRenderer.send('main', str);
}
