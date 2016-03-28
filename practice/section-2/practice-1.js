
function count_same_elements(collection) {
  //在这里写入代码
  var elements = [{key: collection[0], count: 1}];  
  var index = 0
  
  for(var i = 1; i < collection.length; i++) {
      
     var temp = ifCreatElement(elements, collection[i]);
           
     if(temp == false) {         
          index ++;
          elements.push({key: collection[i], count: 1});    
      }
  }
  
 return elements;
}

function ifCreatElement(elements, collection) {
    
    var temp = false;
    
    for(var j = 0; j < elements.length; j ++) {
          
        if(collection == elements[j].key){
            elements[j].count ++;
            temp = true; 
            break; 
        } 
    }
     
    return temp;
}
    

       
        
      /*    ========最初写法=======
function count_same_elements(collection) {
  //在这里写入代码
  var elements = [{key: collection[0], count: 1}];
  
  var index = 0
  for(var i = 1; i < collection.length; i++) {
      
      var temp = false;
      for(var j = 0; j < elements.length; j ++) {
          
          if(collection[i] == elements[j].key){
              
              elements[j].count ++;
              temp = true; 
              break; 
          } 
      }
      
     if(temp == false) {
          
          index ++;
          elements.push({key: collection[i], count: 1});
      
      }
  }
 
 return elements;
}
*/
