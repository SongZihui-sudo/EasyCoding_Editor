const electron = require('electron');
const app = electron.app;
const BrowserWindow = electron.BrowserWindow;
const Menu = electron.Menu;
let appPath = app.getPath('exe');
var window = null;
const dialog = require('electron').remote;
const net = require( 'net' );
const exec = require('child_process').exec
const ipcMain = require('electron').ipcMain;
const ipcMain2 = require('electron').ipcMain;

// 本地需要启动的后台服务名称
let cmdStr = 'main.exe'
let cmdPath = './socket_server/src/'
let workerProcess
var bit_edit = 0;

const template = [
  {
    label:"       "
  },
  {
    label:'帮助',
    submenu:[{
      label:'关于',
      click:()=>{
      dialog.showOpenDialog(
      {
        type: "info",//图标类型
        title: "帮助",//信息提示框标题
        message: "简·编辑器（Windows v1.1.0） 基于Electron 13.6.0\n这是一个简单的文本编辑器，在操作上类似vim。 该程序主要应用于Linux平台，也有Windows版本。 ",//信息提示框内容
      })}
      },
      {
        label:'开源地址',
        click:()=>{
          dialog.showOpenDialog({
            type: "info",//图标类型
            title: "帮助",//信息提示框标题
            message: "Github:\nhttps://github.com/SongZihui-sudo/EasyCoding_Editor",//信息提示框内容
          })
        },
      },
      {
        label:'说明文档',
        click:()=>{
          shell.openItem("../README.md");
        }
      }
      ]},
  {
    label:"文件",
    submenu:[
      {
        label:"新建文件",
          click:()=>{
            //window.location.href="./EasyHtmlEditor.html";  
            window.loadFile('../html/EasyHtmlEditor.html');  
            bit_edit = 1;
            conect_server('edit');
          }
        },
      {
        label:'保存文件',
          click:()=>{

          }
      },
      {
        label:"打开文件",
          click:()=>{

          }
      }
    ]
  },
  {
    label:'编辑',
    submenu:[
      {
        label:"上一步"
      },
      {
        label:"下一步"
      }
    ]
  }
];
//const menu = Menu.buildFromTemplate(template);
//Menu.setApplicationMenu(menu);
Menu.setApplicationMenu(null) //取消菜单栏
app.on('ready', function() {  
  window = new BrowserWindow({
    width: 1200, height: 800,       
    icon : '../favicon.ico', 
    frame: false,    
    webPreferences: {
    // 设置为TRUE
      nodeIntegration : true,
      contextIsolation:false,  //  把这一项加上错误就会消失
      webviewTag: true
    }});  
  window.loadFile('../html/index.html');  
  //window.loadURL('file://' + __dirname+'/../html/' + 'index.html');
  window.openDevTools();
  connect_index();  
});

//打开服务端
function runExec () {
  // 执行命令行，如果命令不需要路径，或就是项目根目录，则不需要cwd参数：
  workerProcess = exec(cmdStr, {cwd: cmdPath})
  // 不受child_process默认的缓冲区大小的使用方法，没参数也要写上{}：workerProcess = exec(cmdStr, {})
  // 打印正常的后台可执行程序输出
  workerProcess.stdout.on('data', function (data) {
    console.log('stdout: ' + data)
  })
  // 打印错误的后台可执行程序输出
  workerProcess.stderr.on('data', function (data) {
    console.log('stderr: ' + data)
  })
  // 退出之后的输出
  workerProcess.on('close', function (code) {
    console.log('out code：' + code)
  })
}  

const port = 2250;
const hostname = '127.0.0.1';
var bit_recv = 0;

function connect_index(){
  ipcMain.on('main', function(event, arg) {
    console.log('main1:'+arg+'\n');  // prints "我是渲染进程的test2"
    event.sender.send('render', 'main:get');
    if (arg == "close") {
      window.close();
      app.quit();
    }
    else if(arg == "big"){
      window.maximize(); 
    }
    else if(arg == "small"){
      window.minimize(); 
    }
    else if(arg == "cancel_max"){
      window.unmaximize(); 
    }
    else{
      console.log("not find!");
    }
  });
}


