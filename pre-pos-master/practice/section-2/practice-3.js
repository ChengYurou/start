function count_same_elements(collection) {
  //在这里写入代码  
  var newCollection = replaceCollection(collection);
  
  var elements = [{name: newCollection[0], summary: 1}];  
  var index = 0
  
  for(var i = 1; i < newCollection.length; i++) {
      
     var temp = ifCreatElement(elements, newCollection[i]);
           
     if(temp == false) {         
          index ++;
          elements.push({name: newCollection[i], summary: 1});    
      }
  }
 print(elements);
 return elements;
}

function replaceCollection(collection) {
    
   
    for(var i = 0; i < collection.length; i++) {
        
        if(collection[i].length > 1) {
            
           var num = parseInt(collection[i].substring(2, collection[i].length));
           var words = collection[i].split(''); 
           
           for(j = 0; j < num; j++) {
              // collection.push(words[0])
              collection.splice(i, 0, words[0]);
           }
          
           collection.splice(i+num, 1);
        }       
    }
    console.log(collection);
    return collection;
}


function ifCreatElement(elements, collection_ele) {
    
    var temp = false;
    
    for(var j = 0; j < elements.length; j ++) {
          
        if(collection_ele == elements[j].name){
            elements[j].summary ++;
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
