function collect_same_elements(collection_a, collection_b) {
  
  var newArr = [];
  for(var i = 0; i < collection_a.length; i++) {
      
      for(var j = 0; j < collection_b[0].length ; j++) {
          
          if(collection_b[0][j] === collection_a[i]) {
              
              newArr.push(collection_a[i]);
              break;
          }
      }
  }
  return newArr;
}

