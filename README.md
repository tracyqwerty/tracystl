# TracySTL
A tiny C++ standard template library. Powered by ChatGPT4.



## Allocator

![v2-59ed19947f0f359e9a7e1ec585958676_1440w](assets/v2-59ed19947f0f359e9a7e1ec585958676_1440w.webp)

[allocator's code](src/allocator.h)

## Iterator

![20200804102957172](assets/20200804102957172.png)

[iterator's code](src/iterator.h)

## Container

### vector

[vector's code](src/vector.h)

### list

[list's code](src/list.h)

Here

1. `data_allocator::destroy(mystl::address_of(p->value)); node_allocator::deallocate(p);`

   This method first calls `destroy` on the value contained in a node, which would call the destructor of the object (not the node itself). Then it calls `deallocate` on the node, which should free the memory associated with the node. This approach is consistent with the usual practice in C++ of first destroying an object before deallocating its memory.

2. `node_allocator::destroy(pos.node_->as_node()); node_allocator::deallocate(pos.node_->as_node());`

   Here, `destroy` is called directly on the node rather than on the value it contains. If the node contains any resources that require proper destruction (such as raw pointers), this approach would be necessary. However, if the node only contains simple data types or objects that manage their own resources, calling `destroy` on the node might not be needed. After the node has been destroyed, the method then deallocates the memory associated with the node.

## Testing

We used Google Test Framework for unit tests.



## TODO

* Instead of using ::operator new(), realize `alloc::allocate(n * sizeof(T))` and create a threadpool.
