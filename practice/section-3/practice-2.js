function create_updated_collection(collection_a, object_b) {
  //在这里写入代码
  //var newArr = [];
  for(var i = 0; i < object_b.value.length; i++) {
      for(var j = 0; j < collection_a.length; j++) {
          if(object_b.value[i] == collection_a[j].key && collection_a[i].count >= 3) {
              collection_a[j].count -= Math.floor(collection_a[j].count/3);
              break;
          }
      }
  }
 // print(collection_a);
  return collection_a;
}



