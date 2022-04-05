import java.util.*;
import java.io.*;
import java.util.concurrent.atomic.AtomicBoolean;

public class Main {
    static int count = 0;
    static int turn = 0;
    static AtomicBoolean[] flag;
    static {
        flag = new AtomicBoolean[2];
        for (int i = 0; i < flag.length; i++) {
            flag[i] = new AtomicBoolean();
        }
    }
    static class Producer implements Runnable {
        @Override
        public void run() {
            for(int i = 0; i < 1000000; i++) {
                flag[0].set(true);
                turn = 1;
                while(flag[1].get() && turn == 1)
                    ;

                count++;
                flag[0].set(false);
            }
        }
    }

    static class Consumer implements Runnable {
        @Override
        public void run() {
            for(int i = 0; i < 1000000; i++) {
                flag[1].set(true);
                turn = 0;
                while(flag[0].get() && turn == 0)
                    ;
                //이떄 flag는 atomic하기에 context switch가 일어나도
                //상호배제를 보장해줌
                count++;
                flag[1].set(false);
            }
        }
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        Thread t1 = new Thread(new Producer());
        Thread t2 = new Thread(new Consumer());
        t1.start(); t2.start();
        t1.join(); t2.join();
        System.out.println(Main.count);
    }


}
