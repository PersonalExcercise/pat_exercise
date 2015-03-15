##PAT RECORD

> This is built to recode the [pat datastruct](http://www.patest.cn/contests/ds) testing.  

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


