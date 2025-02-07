import com.sun.nio.sctp.SendFailedNotification;
import jdk.jfr.Threshold;

import java.util.concurrent.*;

class SumTask extends RecursiveTask<Integer> {
    private int begin;
    private int end;
    private int[] array;
    private final int Threshold = 1000;

    public SumTask(int begin, int end, int[] array) {
        this.begin = begin;
        this.end = end;
        this.array = array;
    }
    protected Integer compute() {

        if(end-begin < Threshold) {
            int sum = 0;
            for (int i = begin; i <= end; i++) {
                sum += array[i];
            }
            return sum;
        } else {
            int mid = (begin + end) / 2;
            SumTask leftTask = new SumTask(begin, mid, array);
            SumTask rightTask = new SumTask(mid + 1, end, array);
            leftTask.fork();
            rightTask.fork();

            return rightTask.join() + leftTask.join();
        }

    }
}


public class Main
{
    public static void main(String[] args) {
        int[] arr = {1, 2, 3, 4, 5};
        SumTask st = new SumTask(0, 4, arr);
        System.out.println(st.compute());
    }
}
