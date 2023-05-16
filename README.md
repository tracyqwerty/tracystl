# TracySTL
A tiny C++ standard template library.



## Allocator

![v2-59ed19947f0f359e9a7e1ec585958676_1440w](assets/v2-59ed19947f0f359e9a7e1ec585958676_1440w.webp)

## Iterator

![20200804102957172](assets/20200804102957172.png)

## Testing

We used Google Test Framework for testing.



## TODO

* Instead of using ::operator new(), realize `alloc::allocate(n * sizeof(T))` and create a threadpool.
