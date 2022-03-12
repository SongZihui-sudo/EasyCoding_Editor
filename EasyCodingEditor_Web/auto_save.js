/**
 * author: 宋子慧
 * date: 2022-3-11
 * about文件的自动保存
 */
const fs = require('fs')
function auto_save(){
  this.write = function(_path,data){  
    const content = data;
    fs.writeFile(_path, content, err => {
      if (err) {
        console.error(err)
        return -1;
      }
      //文件写入成功。
      else{
        console.log('auto_save:write succesfully!!!');
      }
    })
  }
}
module.exports = auto_save;
