#coding=utf-8
import sys

def main() :
    try :
        total_num = int(sys.stdin.readline())
    except ValueError , e :
        print >> sys.stderr ,  str(e)
        return -1
    num_str = sys.stdin.readline()
    num_list = [float(x) for x in num_str.split()]
    num_sum_val = sum(num_list)
    num_avg_val = num_sum_val / total_num 
    num_divi_sum = sum([(x - num_avg_val)**2 for x in num_list])
    num_divi_avg = num_divi_sum / total_num
    num_standard_devi = num_divi_avg ** .5
    print "%.5f" %num_standard_devi
    
if __name__ == "__main__" :
    main()
    