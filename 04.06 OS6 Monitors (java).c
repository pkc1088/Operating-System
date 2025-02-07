import java.util.*;
import java.io.*;
import java.util.concurrent.atomic.AtomicBoolean;

public class Main {

    static class Counter {
        public static int count = 0;
        synchronized public static void increment() {
            count++;
        }
    }

    static class MyRunnable implements Runnable {
        @Override
        public void run() {
            for(int i = 0; i < 10000; i++) {
                Counter.increment();
            }
        }
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        Thread[] threads = new Thread[5];
        for (int i = 0; i < threads.length; i++) {
            threads[i] = new Thread(new MyRunnable());
            threads[i].start();
        }
        for (int i = 0; i < threads.length; i++) {
            threads[i].join();
        }
        System.out.println("Counter =  " + Counter.count);

    }
}

/////////////
//스레드가 다 분리된 상태에서 호출하는건 원하는 값이 안나옴
//각각의 스레드에 서로다른 인스턴스(this)를 주고 count라는 static을
//호출하면 레이스컨디션이 발생하는거임 
import java.util.*;
import java.io.*;
import java.util.concurrent.atomic.AtomicBoolean;

public class Main {

    static class Counter {
        public static int count = 0;
        public void increment() {
            synchronized (this) {
                Counter.count++;
            }
        }
    }

    static class MyRunnable implements Runnable {
        Counter counter;
        public MyRunnable(Counter counter) {
            this.counter = counter;
        }
        @Override
        public void run() {
            for(int i = 0; i < 10000; i++) {
                counter.increment();
            }
        }
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        Thread[] threads = new Thread[5];
        //Counter counter = new Counter(); 하고
		//for문에서 threads[i] = new Thread(new MyRunnable(counter));
		//하면 같은 카운터를 가지니 해결됨 (this 5개가 같은걸 가리킴) 
        for (int i = 0; i < threads.length; i++) {
            threads[i] = new Thread(new MyRunnable(new Counter()));
            threads[i].start();
        }
        for (int i = 0; i < threads.length; i++) {
            threads[i].join();
        }
        System.out.println("Counter =  " + Counter.count);

    }
}
