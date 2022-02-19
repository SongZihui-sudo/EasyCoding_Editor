/*
    采用了piece_table算法来进行文字处理
    日期:2022/2/18
    作者：宋子慧
    简介：
    如果我们只是将文本append到一个数组中，那么我们就不需要shift任何数据了，也就不会出现在中间插入的性能问题。append的复杂的是，而insert的复杂的是。
    不管是新编辑器还是以前的旧编辑器，piece table都是最为强大的数据结构。最大的特点就是piece table将所有的文本插入操作转换为了append的操作。
    撤销与重做，主要采用栈的方式来实现，两个栈交替pop或push
*/
var _BEGIN_BIT = 0;
class pieces{
  start;
  end;
  length;
  source;
};
class piece_table{//表结构
  //私有 pravite
  #original;//原始文档（如果是新建文件，则original为空）
  #_add;//添加（泛指一切修改）
  #_delete;//删除
  #nodes;//记录用户的输入历史
  #len;
  //共有 public
  //initlize 构造函数
  constructor(){
    //debugger
    this.buffers = [[]];
    this.#original = []; 
    this.#_add = [];
    this.#_delete = [];
    this.#nodes = [];
    var child_node = new pieces;
    child_node.start = 0;
    child_node.length = 0;
    child_node.end = 0;
    child_node.source = "original";
    this.#nodes.push(child_node);
    this.#len = 0;
  }
  //iterator 一个接口（查看内部元素的接口）
  iterator(bit){
    console.log(this.#nodes[bit]);
    return this.#nodes[bit];
  }
  //合并连续的删除或着插入的记录
  node_merge(last){
    //debugger
    if((last.start  == this.#nodes[this.length()-2].end||((last.start == this.#nodes[this.length()-2].start)&&(last.end == this.#nodes[this.length()-1].end)))&&(last.source==this.#nodes[this.length()-2].source)
    ){
      var table_merge = new pieces;
      table_merge.start = this.#nodes[this.length()-2].start;
      table_merge.end = last.end;
      table_merge.length = table_merge.end - table_merge.start;
      table_merge.source = "add";
      this.#nodes.pop();
      this.#nodes.pop();
      this.#nodes.push(table_merge);
    }
    else{
      return 1;
    }
    return 0;
  }
  //push_back
  push_insert(char){
    //debugger
    var end_end = [];
    var newchild_pirece = new pieces;
    newchild_pirece.source = "add";
    newchild_pirece.start = pos_x;    
    newchild_pirece.length = char.length;
    newchild_pirece.end = newchild_pirece.start+newchild_pirece.length; 
    //找到属于打一个区块中，把该区块一分为二
    if (pos_x<_BEGIN_BIT){
      //debugger 
      var max;
      for(var index = this.length()-1;index>=0;index--){
        end_end.push(this.#nodes[index].end-newchild_pirece.start);
      }
      var min;
      for(var index = 0;index<end_end.length;index++){
        min = index;
        if (end_end[index]>end_end[index+1]) {
          min = index+1;
        }
        else{
          continue;
        }
      }
      debugger
      var _end = this.#nodes[min].end; 
      this.#nodes[min].end = newchild_pirece.start-1;
      //this.#nodes[this.length()-1].length = ;
      //将原表一分为二 创建出一个新的pireces对象  
      var new_pireces = new pieces;
      new_pireces.start = newchild_pirece.end;      
      new_pireces.end = _end;
      new_pireces.length = new_pireces.end - new_pireces.start+1;
      new_pireces.source = this.#nodes[min].source; 
      newchild_pirece.end--;       
      this.#nodes.push(new_pireces);     
      this.#nodes.push(newchild_pirece);      
    }
    else{
      this.#nodes.push(newchild_pirece);
    }      
    this.#_add.push(char);
    this.node_merge(newchild_pirece);
    _BEGIN_BIT++;
    return 0;
  }
//pop_back
 pop_delete(){
    return 0;
  }
//length
  length(){
    return this.#len = this.#nodes.length;
  }
//begin()
  begin(){
    return this.iterator(0);
  }
//end
  end(){
    return this.iterator(this.#nodes.length); 
  }
//输出
  Text_Show(){
    var Print_str;
    var print_buf = [];
    //debugger
    for(var index = 0;index < this.#nodes.length;index++){
      const element = this.#nodes[index];
      //debugger
      if (element.source == "add") {
        for(var j = element.start;j <= element.end;j++){
          print_buf.push(this.#_add[j]);
        }
        Print_str = print_buf.toString();
        Print_str = Print_str.replace(/,/g, "");    
        Print_str = Print_str.replace(/\/n/g, "<br>");    
        Print_str = Print_str.replace(/\/s/g, "&nbsp;"); 
        Print_str = Print_str.replace(/</g, "&lt;");    
        Print_str = Print_str.replace(/>/g, "&gt;");       
        mvprinth(0,0,Print_str);
      }
      else if(element.source == "_delete"){
        continue;
      }
      else if(element.source == "original"){
        for(var j = element.start;j < element.end;j++){
          print_buf.push(this.#_add[j]);
        }
        Print_str = print_buf.toString();
        Print_str = Print_str.replace(/,/g, "");
        Print_str = Print_str.replace(/\/n/g, "<br>");    
        Print_str = Print_str.replace(/\/s/g, "&nbsp;"); 
        Print_str = Print_str.replace(/</g, "&lt;");    
        Print_str = Print_str.replace(/>/g, "&gt;");     
        if(Print_str!=""){
          mvprinth(0,pos_y,Print_str);
        }
        else{
          continue;
        }
      }
      else{
        console.log(element.source+" not find");
      }
    }
    return 0;
  }
};


    