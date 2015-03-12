##PAT RECODE

> This is built to recode the [pat datastruct](http://www.patest.cn/contests/ds) testing.  

1. [求集合数据的均方差（15）](http://www.patest.cn/contests/ds/2-05) : standard_deviation.py

2. [ 数列求和（20） ](http://www.patest.cn/contests/ds/2-06) : listsum.cpp

3. [素因子分解（20）](http://www.patest.cn/contests/ds/2-07) : factoring.cpp

4. [用扑克牌计算24点（25）](http://www.patest.cn/contests/ds/2-08) calc_24.cpp

5. [装箱问题模拟（20）](http://www.patest.cn/contests/ds/2-09) bin_packing_problem.cpp

6. [海盗分赃（25）](http://www.patest.cn/contests/ds/2-10) pirate_spoil.cpp

    WRONG 

7. [两个有序链表序列的合并（15）](http://www.patest.cn/contests/ds/2-11) merge_ordered_linked_list.cpp

8. [两个有序链表序列的交集（20）](http://www.patest.cn/contests/ds/2-12) intersect_ordered_linked_list.cpp

9. [两个有序序列的中位数（25）](http://www.patest.cn/contests/ds/2-13) middle_number_of_union_set.cpp

    !!根本不要去重！！ = =

10. [一元多项式的乘法与加法运算（20）](http://www.patest.cn/contests/ds/3-04) polynomial_add_and_mul.cpp

11. [求链式线性表的倒数第K项（15）](http://www.patest.cn/contests/ds/3-05) back_count_K.cpp

12. [表达式转换（25）](http://www.patest.cn/contests/ds/3-06) expr_trans.cpp

13. [求前缀表达式的值（25）](http://www.patest.cn/contests/ds/3-07) calc_prefix_expr.cpp

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








