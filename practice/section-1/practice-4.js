function collect_same_elements(collection_a, object_b) {
  //在这里写入代码
  var newArr = [];
  for(var  i = 0; i < collection_a.length; i++) {
      
      for(var j = 0; j < object_b.value.length; j++) {
        //  console.log(collection_a[i].key);
          if(collection_a[i].key == object_b.value[j]) {
              newArr.push(collection_a[i].key);
              break;
          }
      }
  }
  return newArr;
}
