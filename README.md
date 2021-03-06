##PAT RECORD

> This is built to record the [pat datastruct](http://www.patest.cn/contests/ds) testing.  

1. [求集合数据的均方差（15）](http://www.patest.cn/contests/ds/2-05) : standard_deviation.py

2. [ 数列求和（20） ](http://www.patest.cn/contests/ds/2-06) : listsum.cpp

3. [素因子分解（20）](http://www.patest.cn/contests/ds/2-07) : factoring.cpp

4. [用扑克牌计算24点（25）](http://www.patest.cn/contests/ds/2-08) calc_24.cpp

    >使用了暴力枚举

5. [装箱问题模拟（20）](http://www.patest.cn/contests/ds/2-09) bin_packing_problem.cpp

6. [海盗分赃（25）](http://www.patest.cn/contests/ds/2-10) pirate_spoil.cpp

    >WRONG 

7. [两个有序链表序列的合并（15）](http://www.patest.cn/contests/ds/2-11) merge_ordered_linked_list.cpp

8. [两个有序链表序列的交集（20）](http://www.patest.cn/contests/ds/2-12) intersect_ordered_linked_list.cpp

9. [两个有序序列的中位数（25）](http://www.patest.cn/contests/ds/2-13) middle_number_of_union_set.cpp

    >!!根本不要去重！！ = =

10. [一元多项式的乘法与加法运算（20）](http://www.patest.cn/contests/ds/3-04) polynomial_add_and_mul.cpp

11. [求链式线性表的倒数第K项（15）](http://www.patest.cn/contests/ds/3-05) back_count_K.cpp

12. [表达式转换（25）](http://www.patest.cn/contests/ds/3-06) expr_trans.cpp

    
    中缀表达式转后缀表达式，需要从左向右扫描中缀表达式：

    1. 如果是数字，直接输出

    2. 如果是操作符号，分情况讨论：

        a. 如果符号是'(' ， 入栈（其实，应该将‘（’优先级设为最低，这样最稳妥）

        b. 如果符号是')' ， 将栈内符号弹栈输出，直到栈顶是')' , 弹出')'.

        c. 如果符号运算操作符，则需要比较该运算操作符与栈顶操作符的优先级：

            i. 首先明确，栈顶可能是'(',所以为了方便，设定'('优先级最低

            ii. 如果栈顶的操作符优先级低于遇到的操作符，入栈

            iii. 如果栈顶的操作符高于或者等于遇到的操作符，开始出栈并输出，直到栈顶符号优先级低于遇到的符号或者栈为空为止。切记，出栈后将该操作符入栈！

    3. 扫描完毕后，弹出栈内全部符号！


13. [求前缀表达式的值（25）](http://www.patest.cn/contests/ds/3-07) calc_prefix_expr.cpp

    1. 从左往右扫串，如果遇到一个操作符后跟着两个操作数的情况，则对这两个操作数使用该操作符运算，然后将结果替换掉原来的三项；


    2. 继续下去，直到只剩一个操作数，即为结果


14. [堆栈模拟队列（25）](http://www.patest.cn/contests/ds/3-08) queue_by_2stack.cpp

    使用两个栈完成队列操作：
    
    关键： 将小容量的栈作为`入栈`，大容量栈用于`出栈`。最大时刻的队列容量为 2*small_size 

    入栈：

    1. 如果`入栈`不满，直接放入入栈中

    2. 如果`入栈`满，而`出栈`不满 ， 则将所有`入栈`放入`出栈`中(将有最大容量 `2*small_size`)，放入`入栈`中

    3. 如果`入栈`满，`出栈`满，则队列满
    
    出栈：

    1. 如果`出栈`不空，则输出`出栈`栈顶并弹出

    2. 如果`出栈`空，`入栈`不空，则将`入栈`全部放入`出栈`中，输出`出栈`栈顶并弹出

    3. 如果`出栈`空，`入栈`空，则队列空

15. [队列中的元素排序（20）](http://www.patest.cn/contests/ds/3-09) [sort_queue_elements.cpp](src/sort_queue_elements.cpp)

    开始使用的是插入排序的想法，超时。
    
    参看了 [Sigmainfy 烟客旅人](http://tech-wonderland.net/blog/pat-adt-3-09-sort-a-queue.html#comment-30401) 的文章
    
    使用了归并排序

16. [家谱处理（30）](http://www.patest.cn/contests/ds/4-05) [genealogy_processing.cpp](src/genealogy_processing.cpp)

    非常有意思的一道题~当初写树的时候完全没有这么有意思的题目！

    PAT因为考试关闭了提交，但是这个题库在考试后忘记开启啦~昨天写完了没法提交好难受，今天早上在网站上找到了陈老师的邮箱，历经两个回合，又开放啦~~

    好开心！

17. [搜索树判断（25）](http://www.patest.cn/contests/ds/4-06) [binary_search_tree_judgement.cpp](src/binary_search_tree_judgement.cpp)

    递归建树；递归遍历；

    镜像树就是先遍历右孩子再遍历左孩子节点。

18. [修理牧场（25）](http://www.patest.cn/contests/ds/4-07) [repair_farm.cpp](src/repair_farm.cpp)

    完全没有想到！

    优先队列也是第一次使用！

19. [目录树（30）](http://www.patest.cn/contests/ds/4-08) [dir_tree.cpp](src/dir_tree.cpp)

    写了两天。第一天写太着急，没看清要先输出目录再输出文件。后来又想得太多。

    第二天决定老老实实写if判断状态。但是写出一个的时候编译的时候犯了错：
    ```c++
    g++ -o dir_tree.cpp dir_tree.cpp
    ```
    直接将源代码覆盖了。欲哭无泪。于是上网照着这了个简单的Makefile。再写了一遍dir_tree.cpp。这一次写就非常顺利，思路也清晰了。

    但是还是遇到了坑，是我理解错了。就是关于string的构造函数

    ```
    string(const char* , size_t n)
    ```

    开始以为是指复制n个char*作为初始值呢！看了API文档才知道竟然是复制字符串的前n个字符作为初始值！！！难道是我把C++Primer记错了？

    ```
    string(size_t n , char )
    ```
    是正确的方式

20. [笛卡尔树（25）](http://www.patest.cn/contests/ds/4-09) [cartesian_tree.cpp](src/cartesian_tree.cpp)

    检测是否是最小堆和二叉搜索树的问题
    
    除了挨个比较相邻的父亲孩子节点的关系是否满足外 ，对于二叉搜索树，还需要：
    
    如果当前节点是左孩子，那么应该找到第一个是右孩子的祖先节点的父亲节点，如果左孩子比找到的父亲节点小，则不是二叉搜索树；

    如果是右孩子，则要找第一个是左孩子的祖先节点的父亲节点，如果右孩子比该父亲节点大，则不是二叉搜索树。

    应该还可以用中序遍历看下结果是否递增也行。

21. [QQ帐户的申请与登陆（25）](http://www.patest.cn/contests/ds/5-05) [qq_login_and_register.cpp](src/qq_login_and_register.cpp)

    直接用了MAP...

22. [航空公司VIP客户查询（25）](http://www.patest.cn/contests/ds/5-06) [airport_vip_query.cpp](src/airport_vip_query.cpp)

    第一天用MAP标准库超时；

    第二天自己写的hash还是超时；

    网上找了相关的代码，传上去过了！但是，自己怎么改，都是要超时！

    把动态内存申请改成游标法，把string改成char*，把hash函数改成相同，还是超时。我觉得是代码哪里写错了，但是为什么第一个示例又过了。

    ORZ，改了一下午！算了。

23. [新浪微博热门话题（30）](http://www.patest.cn/contests/ds/5-07) [weibo_hot_topic.cpp](src/weibo_hot_topic.cpp)

    写了两天

    HASH + 倒排

    看到和上一个一样的150ms，一直担心超时。结果没有。但是最后一个case不过。

    起初是段错误，把140个字符的限制稍稍加大为1，结果不段错误后，结果错误。看到话题不超过40字符，改了后依然不过。

    罢了。


