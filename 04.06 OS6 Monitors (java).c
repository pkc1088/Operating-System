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
//�����尡 �� �и��� ���¿��� ȣ���ϴ°� ���ϴ� ���� �ȳ���
//������ �����忡 ���δٸ� �ν��Ͻ�(this)�� �ְ� count��� static��
//ȣ���ϸ� ���̽�������� �߻��ϴ°��� 
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
        //Counter counter = new Counter(); �ϰ�
		//for������ threads[i] = new Thread(new MyRunnable(counter));
		//�ϸ� ���� ī���͸� ������ �ذ�� (this 5���� ������ ����Ŵ) 
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
