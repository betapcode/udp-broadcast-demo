UDP Broadcast Example sử dụng C/C++
=============================================================================

Mô tả
-----------

An example of using UDP broadcast to discover clients on a local network.

Sử dụng:
-----

### Compile and run

```
> make all
g++ server.cpp -o server
g++ client.cpp -o client

> $ ./server
```


```
> $ ./client
Server : "Hello from server

- 172.16.2.5:30666
```