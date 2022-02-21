/*
    采用了piece_table算法来进行文字处理
    日期:2022/2/18
    作者：宋子慧
    简介：
    如果我们只是将文本append到一个数组中，那么我们就不需要shift任何数据了，也就不会出现在中间插入的性能问题。append的复杂的是，而insert的复杂的是。
    不管是新编辑器还是以前的旧编辑器，piece table都是最为强大的数据结构。最大的特点就是piece table将所有的文本插入操作转换为了append的操作。
    撤销与重做，主要采用栈的方式来实现，两个栈交替pop或push
*/
class pieces_node{
  start;    //逻辑起始位置
  len;      //逻辑结束位置
  source;   //type
/*
*   采用链表来保存表的节点-----------二叉搜索树
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

var dep_root = new pieces_node();

class piece_table_link{//表结构
  //私有 pravite
  #original;//原始文档（如果是新建文件，则original为空）
  #_add;//添加（泛指一切修改）
  piece_link_root;
  #Print_str;
  #print_buf;
  #len;
  #head;
  move_bit;
  #LineStart;
  //共有 public
  //initlize 构造函数
  constructor(){
    //debugger
    this.#original = []; 
    this.#_add = [];
    //初始化根节点
    this.#head = new pieces_node();
    this.piece_link_root = new pieces_node();
    this.piece_link_root.source = "original";
    this.piece_link_root.depth = 0;
    this.#Print_str = "";
    this.#print_buf = [];
    this.#original.push("");
    this.#len = 0;
    this.#head.right = this.piece_link_root;
    this.#head = this.piece_link_root;
    this.move_bit = 0;
    this.#LineStart = [];
  }
  //迭代器
  iterator(index){
    let cur = this.#head;
    while (index!=0) {
      cur = cur.right;
      index--;
    }
    return cur;
  }
  //头节点
  begin(){
    return this.iterator(0);
  }
  //最后一个节点
  end(){
    return this.iterator(this.length()-1);
  }
  //长度
  length(){
    return this.#len;
  }
  //合并连续的删除或着插入的记录  有问题，当输入一定长度后，会合并错误
  /* 
  node_merge(pre,last){
    if(last.start == pre.start+pre.len&&last.source == pre.source){
      pre.len += last.len;
      last = null;
      this.#len--;
      return pre;
    }
    else{
      return null;
    }
  }
  */
  //push_back
  push_insert(char){
    //创建一个新结点
    this.#len++;
    //debugger
    var new_child = new pieces_node();
    var res = 0;
    //new_child.start = this.#len;
    if(res = this.find_str(char)){
      //debugger
      new_child.start = res-1;
    }
    else{
      new_child.start = this.#_add.push(char)- 1;      
    }
    new_child.len = 1;
    new_child.source = "add";   
    //debugger     
    if (pos_x+1<this.length()){    
      let previous;
      previous = this.iterator(pos_x);   
      let current = this.iterator(pos_x+1);   
      new_child.right = current;
      previous.right = new_child;
      this.move_bit = pos_x;
    }
    else{
      if (!this.#head) {
        this.head = new_child;
      } 
      else {
        //var stage;
        let cur = this.end();
       // stage = this.node_merge(cur,new_child);
       // if (stage) {
         // cur = stage;
        //}
        //else{
          cur.right = new_child;
       // }
      }
    }      
    pos_x++;
    return 0;
  }
//pop_back
 pop_delete(){
  //debugger
  if(pos_x+1<=this.length()){
    let previous;
    previous = this.iterator(pos_x-1); 
    if(previous == null){
      this.#head = null;
      pos_x--
      this.#len--;
      return 0;
    }  
    let current = this.iterator(pos_x+1); 
    if(current==null){
      previous.right = null;
    }  
    else{
      previous.right = current;
    }
    this.move_bit = pos_x;
  }
  else{
    let last = this.iterator(this.length()-1);
    last.right = null;
  }
  pos_x--
  this.#len--;
  if(!this.#len){
    CLEAR();
    SetPos(0,0);
  }
  return 0;
  }
//遍历输出
  Text_Show(root){
    //debugger
    if(root!=null){
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
    }
    else{
      return 1;
    }
    if(this.#print_buf.length)
      this.#Print_str = this.#print_buf.toString();
    if(this.#Print_str){
      this.#Print_str = this.#Print_str.replace(/,/g, "");    
      this.#Print_str = this.#Print_str.replace(/\/n/g, "<br>");    
      this.#Print_str = this.#Print_str.replace(/\/s/g, "&nbsp;"); 
      this.#Print_str = this.#Print_str.replace(/</g, "&lt;");    
      this.#Print_str = this.#Print_str.replace(/>/g, "&gt;");     
      mvprinth(0,pos_y,this.#Print_str);     
    }
    this.Text_Show(root.right);      
    this.clearPrintBuf(); //清空打印缓冲区
    if(this.move_bit){
      //debugger
      cursor.style.left = pos_buf[this.move_bit]+"px";
      pos_x = this.move_bit+1;
      this.move_bit = 0;
    }  
    return 0;
  }
  #_link_index
  //根据元素的物理位置，判断在哪一个表中
  Search(localtion){
    let cur = this.#head;
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
  find_str(char){
    var left = 0;
    var right = this.#_add.length;
    while (left<=right) {
      if (char == this.#_add[left]) {
        return left+1;
      }
      else if(char == this.#_add[right]){
        return right+1;
      }
      else{
        left++;
        right--;
      }
    }
    return 0;
  }
  clearPrintBuf(){
    //debugger
    while (this.#print_buf.length!=0) {
      this.#print_buf.pop();
    }
    this.#Print_str = "";
    return 0;
  }
};


    