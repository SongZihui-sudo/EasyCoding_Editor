/*
*    采用了piece_table算法来进行文字处理
*    日期:2022/2/18
*    作者：宋子慧
*    简介：
*    这里是编辑器的数据结构区，主要采用了pieces table的数据结构
*    在打印时，会先将要打印输出的内容，输出进入打印缓冲区，之后与屏幕缓冲区比较，如果不一样则
*    覆盖屏幕缓冲区，在html页面上显示出新内容。 
*/
class pieces_node{
  start;    //逻辑起始位置
  len;      //逻辑结束位置
  source;   //type
/*
*   采用链表来保存表的节点
*/
  right;
  //构造函数，初始化
  constructor(){
    this.right = null;
    this.start = 0;
    this.len = 0;
    this.source = null;
  };
}

class piece_table_link{//表结构
  buffer //屏幕缓冲区
  //私有 pravite
  #original;//原始文档（如果是新建文件，则original为空）
  #_add;//添加（泛指一切修改）
  piece_link_root;//第二个节点
  #Print_str;//输出字符串
  #print_buf;//输出缓存
  head;//头节点
  #move_bit;//中间插入的位置
  #moveback_bit;//中间删除的位置
  #linkbuffer;//多书写的以行为单位的链表缓冲
  //共有 public
  //initlize 构造函数
  constructor(){
    //debugger
    //各种初始化
    this.#original = []; 
    this.#_add = [];
    this.head = new pieces_node(); //初始化根节点
    this.piece_link_root = new pieces_node();
    this.piece_link_root.source = "original";
    this.#Print_str = "";
    this.#print_buf = [];
    this.#original.push("");
    this.head.right = this.piece_link_root;
    this.head.source = "head";
    this.head.len = 1;
    this.#move_bit = 0;
    this.buffer = [];
    this.#linkbuffer = [];
    this.#linkbuffer.push(this.head);
  }
  //迭代器
  iterator(link,index){
    if(index<0||index-1>this.length()){
      return null;
    }
    else if(index==0){
      return link; 
    }
    else{
      //遍历到需要的位置
      let cur = link;
      while (index!=0) {
        cur = cur.right;
        index--;
      }    
      return cur;
    }
  }
  //头节点
  begin(){
    return this.iterator(this.head,0);
  }
  //最后一个节点
  end(){
    return this.iterator(this.head,this.length());
  }
  //长度
  length(){
    return this.head.len-1;
  }
  //push_back
  push_insert(char){
    //创建一个新结点
    //debugger
    var new_child = new pieces_node();
    var res = 0;
    if(res = this.find_str(this.#_add,char)){
      //debugger
      new_child.start = res-1;
    }
    else{
      new_child.start = this.#_add.push(char)- 1;      
    }
    new_child.len = 1;
    new_child.source = "add";   
    //debugger     
    if(!pos_x){
      pos_x++;
    }
    //debugger
    if (pos_x<this.head.len){    
      //debugger
      //中间插入
      //把插入的表断开成两个
      let previous;
      previous = this.iterator(this.head,pos_x-1);   
      let current = this.iterator(this.head,pos_x);   
      new_child.right = current;
      previous.right = new_child;
      this.#move_bit = pos_x;
    }
    else{
      //在结尾插入
      if (!this.head) {
        this.head = new_child;
      } 
      else{
        //debugger
        let cur = this.end(); 
        //debugger
        cur.right = new_child;
      }
    }      
    pos_x++;
    this.head.len++;
    this.#linkbuffer.splice(pos_y,1,this.head);
    this.Text_Show();
    return 0;
  }
//pop_back
 pop_delete(){
   if(pos_x==1){
     this.Link_mrege();     
     refresh();
     pos_y--;
     return 1;
   }
   if(this.head.len == 1){
     return 1;
   }
  //debugger
  //中间删除
  if(pos_x<this.head.len){
    let previous = this.iterator(this.head,pos_x-2); 
    if(previous == null){
      this.head.source = "head";
      this.head.len = 1;
      this.head.right = null;
      return 0;
    }  
    let current = this.iterator(this.head,pos_x); 
    if(current==null){
      previous.right = null;
    }  
    else{
      previous.right = current;
    }
    this.#moveback_bit = pos_x;
  }
  //结尾删除
  else{
    let last = this.iterator(this.head,this.length()-1);
    last.right = null;
  }
  pos_x--;
  this.head.len--;
  if(this.head.len==1){
    var _getlinespan = document.getElementById("y"+pos_y);
    _getlinespan.innerHTML = "";
    SetPos(0,pos_y);
  }
  pos_buf.pop();
  this.Text_Show();
  return 0;
}
//遍历输出
  Text_Show(){
    var root = null;
    //debugger
    root = this.#linkbuffer[pos_y];  
    while(root!=null){
      if(root!=null){
        //构造要输出的内容
        this.#Print_str = this._toString(root);
        root = root.right; 
      }        
    }        
    //将内容打印输出到打印缓冲区
    printh(this.#Print_str);  
    //debugger
    //判断是否需要刷新屏幕缓冲区
    update_buffer(this.#Print_str);
  //移动x光标
    if(this.#move_bit){
      //debugger
      cursor.style.left = pos_buf[this.#move_bit]+"px";
      pos_x = this.#move_bit+1;
      this.#move_bit = 0;
    }  
    else if(this.#moveback_bit){
      //debugger
      cursor.style.left = pos_buf[this.#moveback_bit-2]+"px";
      pos_x = this.#moveback_bit-1;
      this.#moveback_bit = 0;
    }  
  //模拟\r\n 
    else if(bit_enter){
      cursor.style.left = w_bit+"px";
      bit_enter = 0;
    }
    this.clearPrintBuf(); //清空打印缓冲区
    return 0;
  }
  #_link_index
  //根据元素的物理位置，判断在哪一个表中
  Search(localtion){
    let cur = this.head;
    while (cur) {
      if (localtion.start>cur.start&&localtion.len+localtion.start<cur.len+cur.start) 
        return cur;
      cur = cur.right;
      this.#_link_index++;
    }
    this.#_link_index = 0;
    return null;
  }
  //查找add中是否有字串
  //只保存数组中没有的内容
  find_str(array,char){
    var left = 0;
    var right = array.length;
    while (left<=right) {
      if (char == array[left]) {
        return left+1;
      }
      else if(char == array[right]){
        return right+1;
      }
      else{
        left++;
        right--;
      }
    }
    return 0;
  }
  //清空输出缓冲区
  clearPrintBuf(){
    //debugger
    while (this.#print_buf.length!=0) {
      this.#print_buf.pop();
    }
    this.#Print_str = "";
    return 0;
  }
  //换行 断开这一行的表
  Sqilt(){
    if(!pos_x){
      pos_x++;
    }
    if(pos_x>=this.head.len&&pos_x!=1){
      if(pos_y){
        this.#linkbuffer.push(this.head);
      }
      this.clear(this.head);
    }
    else{
      //从中间切开链表
      //debugger
      link_len = this.length();
      var a_head = new pieces_node();
      a_head.source = "head";
      let cur = this.iterator(this.head,pos_x);
      let new_head = this.iterator(this.head,pos_x-1);
      new_head.right = null;
      //a_head.len = this.head.len - pos_x;      
      a_head.right = cur;
      this.#linkbuffer.splice(pos_y+1,0,a_head);
      this.#linkbuffer[pos_y] = this.head;
      var buf_var = this.head;
      this.head = a_head;
      this.head.len = pos_x;
      //debugger
      while(buf_var!=null){
        cur_line = this._toString(buf_var);
        buf_var = buf_var.right;
      }
      this.clearPrintBuf(); //清空打印缓冲区
      if (pos_x!=1) {
        pre_line = this._toString(cur);
      }
      else{
        while (cur!=null) {
          pre_line = this._toString(cur);
          cur = cur.right;
        }
      }
      this.clearPrintBuf(); //清空打印缓冲区    
      //debugger
      //this.head = this.#linkbuffer[pos_y+1];
    }
    if(this.head.right==null&&!this.head.len){
      this.head.len = 1;
      this.head.right = new pieces_node();
      this.head.right.len = 1;
    }
    return 0;
  }
  //清空
  clear(){
    this.head = null;
    this.piece_link_root = null;
    var new_head = new pieces_node();
    new_head.len = 1;
    new_head.source = "head";
    this.head = new_head;
    return 0;
  }
  //合并同一行上的链表
  Link_mrege(){
    //debugger
    this.head = this.#linkbuffer[pos_y-1];
    this.head.len =this.head.len+this.#linkbuffer[pos_y].len-2;
    let _end = this.end();
    if(_end!=null){
      _end.right = this.#linkbuffer[pos_y];
    }
    else{
      _end = new pieces_node();
      _end = this.#linkbuffer[pos_y];
    }
    this.#linkbuffer.splice(pos_y,1);
    var p_end = _end;
    while (p_end!=null) {
      cur_str = this._toString(p_end);
      p_end = p_end.right;
    }
    this.clearPrintBuf();
    delete_aspan();
    //debugger
    var new_pos_buf = [];
    var last = line_pos_buf[line_pos_buf.length-1][line_pos_buf[line_pos_buf.length-1].length-1];
    for (let index = 0; index < line_pos_buf[pos_y].length+1; index++) {
      line_pos_buf[pos_y-1].push(Number(last+line_pos_buf[pos_y].shift()));
    }
    line_pos_buf.splice(pos_y,1);
    line_pos_buf[pos_y-1].unshift(0);    
    line_pos_buf[pos_y-1] = unique(line_pos_buf[pos_y-1]);
    pos_buf = line_pos_buf[pos_y-1];
    pos_x = pos_buf.length;
    cursor.style.top = (pos_y-1)*h_bit+"px";
    cursor.style.left = pos_x*w_bit+"px";
    return 0;
  }
  change_head(){
    this.head = this.#linkbuffer[pos_y];
    return 0;
  }
  //pieces表转字符串
  _toString(root){
    if(root.source == "add"){
      for(var index = root.start;index<root.len+root.start;index++){
        const element = this.#_add[index];
        this.#print_buf.push(element)
      }
    }
    else{
      for(var index = root.start;index<root.len+root.start;index++){
        const element = this.#original[index];
        this.#print_buf.push(element)
      }
    }
    if(this.#print_buf.length){
      this.#Print_str = this.#print_buf.toString();
    }
    if(this.#Print_str){
      //替换字符
      this.#Print_str = this.#Print_str.replace(/,/g, "");    
      this.#Print_str = this.#Print_str.replace(/" "/g, "&nbsp;"); 
      this.#Print_str = this.#Print_str.replace(/</g, "&lt;");    
      this.#Print_str = this.#Print_str.replace(/>/g, "&gt;");     
    }
    return this.#Print_str;
  }
}
