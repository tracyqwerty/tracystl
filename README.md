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

## Testing

We used Google Test Framework for unit tests.



## TODO

* Instead of using ::operator new(), realize `alloc::allocate(n * sizeof(T))` and create a threadpool.
