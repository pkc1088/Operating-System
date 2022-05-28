/*
�ϴ� synchronized�� ���ؼ�?ReentrantLock�� �ξ� ���������� ����ȭ�� �����մϴ�.�׸��� ���� ū ��������?synchronized�� �Ϲ����̰�, 
ReentrantLock�� ������̶�� ������.��� �޼ҵ尡 ��������� ǥ���Ǿ� �ְ�, �׷����ؼ� ����ϴ� �͵� ��������� ���˴ϴ�.

�� Lock Ŭ����
  - synchronized ���� �̿��� ����ȭ �� ���� �޼ҵ� ������ lock�� �� �� �ִٴ� ��������� �ذ��ϱ� ���� Ŭ�����̴�.
  - �̸� �̿��ϸ� ���� ���� ���·� �Ӱ迵���� �����ؾ� �ϴ� �Ѱ踦 �غ��� �� �ִ�.

�� Lock Ŭ������ ����
  - ReentrantLock Ŭ����
    . ������ ������ lock, ���� �Ϲ����� ��Ÿ lock
    . Ư�� ���ǿ��� lock�� Ǯ��, ���߿� �ٽ� lock�� ��� �Ӱ迵������ ���� ����
  - ReentrantReadWriteLock Ŭ����
    . �б⸦ ���� lock�� ���⸦ ���� lock�� ���� ����
    . �б⿡�� �������̰�, ���⿡�� ��Ÿ���� lock
    . �б� lock�� �ɷ��ִ� ���, �ٸ� ������鵵 �б��� ���� ���� (read-only)
    . �б� lock�� �ɷ��ִ� ���, �ٸ� �����尡 ���� lock�� ���� (������ ���� ����)
  - StampedLock Ŭ���� 
    . ReentrantReadWriteLock�� �������� lock�� ����� �߰�
    . �������� �б� lock�� ���� lock�� ���� �ٷ� ���� ����
    . ������ �б� lock�� ���� �ʰ�, ����� �бⰡ �浹�� ���� ���� �� �б� lock

�� Condition Ŭ����
  - Ư�� �����带 ���� Conditon �ν��Ͻ��� ����� ������ ���� wait pool�� ������ִ� ����� �Ѵ�.
  - �̸� �̿��Ͽ� ����� ���� Ư�� �����常 ����� ���� �����ϴ�.
*/ 

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

class Toilet {

    public int paper;

    public Toilet() {
        this.paper = 5;
    }

    public void setPaper(int paper) {
        this.paper = paper;
    }

    public int getPaper() {
        return paper;
    }

    public void usedPaper() {
        this.paper--;
    }

}

class Cleaner implements Runnable {

    private Toilet toilet;

    private ReentrantLock lock;
    private Condition forCleaner;
    private Condition forPerson;

    // �ش� û�Һΰ� �����ϴ� ȭ��� ���
    // lock, lock�� ���� Condition �ν��Ͻ� ����
    public Cleaner(Toilet toilet, ReentrantLock lock, Condition forCleaner, Condition forPerson) {
        this.toilet = toilet;
        this.lock = lock;
        this.forCleaner = forCleaner;
        this.forPerson = forPerson;
    }

    public void replacePaper(int p) {
        toilet.setPaper(p);
    }

    @Override
    public void run() {
        
        String name = Thread.currentThread().getName();
    
        while (true) {
            
            // ȭ����� ȥ�ڸ� ��� ����
            // ���� �����尡 �������� ���Ѵ�.
            // ����ִٸ� lock�� ���������� ��� ���
            lock.lock();
            try {
                
                // ������ ������ �ʿ䰡 ���ٸ� ���� �ʴ´�.
                if (toilet.getPaper() <= 0) {
                    System.out.println(name + " replaces toilet paper.");
                    replacePaper(5);
                    // �ٸ� ����鿡�� ȭ����� ��� �������� �˷��ش�.
                    System.out.println("Finish. Wake everybody.");
                    forPerson.signalAll();
                }
                
                try {
                    // ���� ������ ����ϸ� �ٷ� ȭ����� ���ͼ� �ڽ��� ���Ƿ� �̵�
                    System.out.println(name + " Go to wait.");
                    forCleaner.await();
                    Thread.sleep(500);
                    System.out.println(name + " wakes.");
                } 
                //
                catch (Exception e) {
                    e.printStackTrace();
                }

            }
            //
            finally {
                lock.unlock();
            }
        }
    }
}

class Person implements Runnable {

    private Toilet toilet;

    private ReentrantLock lock;
    private Condition forCleaner;
    private Condition forPerson;

    // ����ؾ��ϴ� ȭ����� ����
    // lock, lock�� ���� Condition �ν��Ͻ� ����
    public Person(Toilet toilet, ReentrantLock lock, Condition forCleaner, Condition forPerson) {
        this.toilet = toilet;
        this.lock = lock;
        this.forCleaner = forCleaner;
        this.forPerson = forPerson;

    }

    // ȭ����� ������ �ִ��� Ȯ��
    public boolean checkToilet() {
        return toilet.getPaper() >= 1;
    }

    public void usePaper() {
        // ���� �ϳ� ��� �� ������ ������
        toilet.usedPaper();
    }

    public void run() {
        
        String name = Thread.currentThread().getName();
        while (true) {
        
            // ȭ����� �ѻ���� ��� ����
            lock.lock();
            
            try {
                
                // ȭ��ǿ� ������ �ִ��� Ȯ��
                // ���� ������ ��� ���
                while (toilet.getPaper() < 1) {
                
                    System.out.println(name + " is waiting for replacing paper.");
                    
                    try {
                        // ��� ���� û�Һ� ��ȯ
                        forCleaner.signal();
                        // ������ �����Ƿ� ��� pool�� �̵�
                        forPerson.await();
                        Thread.sleep(500);
                        System.out.println(name + " wakes.");
                    }
                    //
                    catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            
                // ȭ��� �� ���� ���� ������ ��� �� ȭ��� �ÿ��� ����
                System.out.println(name + " uses toilet.");
                usePaper();
                try {
                    // ������ ������ �ٸ� ����� ���� û�Һο��� �˸���.
                    if (toilet.getPaper() <= 0) {
                        forCleaner.signal();
                    }
                    // �ڽ��� ȭ����� ������.
                    forPerson.await();
                    Thread.sleep(500);
                } 
                //
                catch (Exception e) {
                }
            } 
            //
            finally {
                lock.unlock();
            }
        }
    }
}

public class MainClass {

    private static Toilet toilet = new Toilet();
    private static ReentrantLock lock = new ReentrantLock();
    private static Condition forCleaner = lock.newCondition();
    private static Condition forPerson = lock.newCondition();

    public static void main(String[] args) {
        
        // �����ϴ� ȭ����� ����
        Cleaner cleaner = new Cleaner(toilet, lock, forCleaner, forPerson);
        Thread cleanerThread = new Thread(cleaner, "Cleaner");
        cleanerThread.start();

        Person[] people = new Person[5];
        for (int i = 0; i < people.length; i++) {
            // ��� ��ü ����, �� ����� ����ؾ��ϴ� ȭ��ǵ� ����
            people[i] = new Person(toilet, lock, forCleaner, forPerson);
            Thread th = new Thread(people[i], "Person-" + i);
            // ��� ��ü�� �ൿ��Ű�� �����带 ����
            th.start();
        }
    }
}
