###简介

这个设计思路是对《linux体系与编程》一书的第11章的设计思路总结

###设计思路

![微博服务器设计](http://i.imgur.com/FypiqVZ.png)

各个组件的说明：

- 用户请求产生自客户端
- 线程accept和解析用户请求属于请求处理线程池
- 登录队列处理线程池
- 获取最新微博线程池
- 发表微博线程池
- 还有其他微博功能，都有对应的线程池来处理其队列
- 处理请求的状态返回给用户的处理线程池



