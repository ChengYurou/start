// function create_updated_collection(collection_a, object_b) {
//   //在这里写入代码

//   for (var i = 0; i < collection_a.length; i++) {


//   	if(isExisted(collection_a[i].key,object_b.value)){

//        collection_a[i].count--;


//   	}
 
//   }
//   return collection_a;
// }

// function isExisted(item, collection) {

// 	for (var i = 0; i < collection.length; i++) {

// 		if (collection[i] === item) {

// 			return true;
// 		}
// 	}

// 	return false;
// }


function create_updated_collection(collection_a, object_b) {

  object_b.value.forEach(function(key) {

    var existItem = findItem(key, collection_a);
    if (existItem) {
      existItem.count--;
    }
  });

  return collection_a;
}

function findItem(key, items) {

  var existItem;

  items.forEach(function(item) {
    if (item.key === key) {
      existItem = item;
    }
  });

  return existItem;
}