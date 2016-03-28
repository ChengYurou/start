// function count_same_elements(collection) {

//   var newArray = [];

//   var index = collection[0];
//   var count_same = 0;

//   for (var i = 0; i < collection.length; i++) {
  
//   	if (index === collection[i]) {

//   		count_same++;

//   		if(i === collection.length - 1){
//     		newArray.push({ key: index, count: count_same });
//   		}
//   	} else {

//       newArray.push({ key: index, count: count_same });

//   		index = collection[i];
//   	  count_same = 0;
//   	  i--;
//   	}
//   }

//   return newArray;
// }


function count_same_elements(collection) {

  var items = [];

  collection.forEach(function(key) {

    var existItem = findItem(key, items);
    if (existItem) {
      existItem.count++;
    } else {
      items.push({ key: key, count: 1 });
    }
  });

  return items;
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