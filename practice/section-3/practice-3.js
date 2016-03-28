function create_updated_collection(collection_a, object_b) {
  //在这里写入代码
//  var new_collection = replace_collection(collection_a);
  var elements = creat_newArr(collection_a);
  return count_calculate(elements, object_b);
}


function count_calculate(elements, object) {
    
    for(var i = 0; i < object.value.length; i++) {
        for(var j = 0; j < elements.length; j++) {
            if(elements[j].key == object.value[i] && elements[j].count >= 3) {
                elements[j].count -= Math.floor(elements[j].count/3);
            } 
        }
    }
    return elements;
}


function creat_newArr(newCollection) {
    
  var elements = [{key: newCollection[0], count: 1}];  
  
  for(var i = 1; i < newCollection.length; i++) {
      
     var temp = ifCreatElement(elements, newCollection[i]);
           
     if(temp == false) {         
          elements.push({key: newCollection[i], count: 1});    
      }
  }
 print(elements);
 return elements;
}


function ifCreatElement(elements, collection_ele) {
    
    var temp = false;
    
    for(var j = 0; j < elements.length; j ++) {
          
        if(collection_ele == elements[j].key){
            elements[j].count ++;
            temp = true; 
            break; 
        } 
    }
     
    return temp;
}


function print(array) {
    
    for(var i = 0; i < array.length; i++) {
      console.log(array[i]);
  }
}