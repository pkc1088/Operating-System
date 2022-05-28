/*
일단 synchronized에 비해서?ReentrantLock이 훨씬 세부적으로 동기화가 가능합니다.그리고 가장 큰 차이점은?synchronized는 암묵적이고, 
ReentrantLock은 명시적이라는 것이죠.모든 메소드가 명시적으로 표현되어 있고, 그로인해서 사용하는 것도 명시적으로 사용됩니다.

□ Lock 클래스
  - synchronized 블럭을 이용한 동기화 시 같은 메소드 내에만 lock을 걸 수 있다는 제약사항을 해결하기 위한 클래스이다.
  - 이를 이용하면 단일 블럭의 형태로 임계영역을 설정해야 하는 한계를 극복할 수 있다.

□ Lock 클래스의 종류
  - ReentrantLock 클래스
    . 재진입 가능한 lock, 가장 일반적인 배타 lock
    . 특정 조건에서 lock을 풀고, 나중에 다시 lock을 얻어 임계영역으로 진입 가능
  - ReentrantReadWriteLock 클래스
    . 읽기를 위한 lock과 쓰기를 위한 lock을 따로 제공
    . 읽기에는 공유적이고, 쓰기에는 배타적인 lock
    . 읽기 lock이 걸려있는 경우, 다른 스레드들도 읽기라면 진입 가능 (read-only)
    . 읽기 lock이 걸려있는 경우, 다른 스레드가 쓰기 lock은 금지 (데이터 변경 방지)
  - StampedLock 클래스 
    . ReentrantReadWriteLock에 낙관적인 lock의 기능을 추가
    . 낙관적인 읽기 lock은 쓰기 lock에 의해 바로 해제 가능
    . 무조건 읽기 lock을 걸지 않고, 쓰기와 읽기가 충돌할 때만 쓰기 후 읽기 lock

□ Condition 클래스
  - 특정 스레드를 위한 Conditon 인스턴스를 만들어 스레드 별로 wait pool을 만들어주는 기능을 한다.
  - 이를 이용하여 깨우고 싶은 특정 스레드만 깨우는 것이 가능하다.
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

    // 해당 청소부가 관리하는 화장실 등록
    // lock, lock을 위한 Condition 인스턴스 생성
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
            
            // 화장실은 혼자만 사용 가능
            // 여러 스레드가 접근하지 못한다.
            // 잠겨있다면 lock을 잡을때까지 잠시 대기
            lock.lock();
            try {
                
                // 휴지를 충전할 필요가 없다면 하지 않는다.
                if (toilet.getPaper() <= 0) {
                    System.out.println(name + " replaces toilet paper.");
                    replacePaper(5);
                    // 다른 사람들에게 화장실이 사용 가능함을 알려준다.
                    System.out.println("Finish. Wake everybody.");
                    forPerson.signalAll();
                }
                
                try {
                    // 아직 휴지가 충분하면 바로 화장실을 나와서 자신의 대기실로 이동
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

    // 사용해야하는 화장실을 지정
    // lock, lock을 위한 Condition 인스턴스 생성
    public Person(Toilet toilet, ReentrantLock lock, Condition forCleaner, Condition forPerson) {
        this.toilet = toilet;
        this.lock = lock;
        this.forCleaner = forCleaner;
        this.forPerson = forPerson;

    }

    // 화장실의 휴지가 있는지 확인
    public boolean checkToilet() {
        return toilet.getPaper() >= 1;
    }

    public void usePaper() {
        // 휴지 하나 사용 후 나머지 휴지를
        toilet.usedPaper();
    }

    public void run() {
        
        String name = Thread.currentThread().getName();
        while (true) {
        
            // 화장실은 한사람만 사용 가능
            lock.lock();
            
            try {
                
                // 화장실에 휴지가 있는지 확인
                // 휴지 없으면 계속 대기
                while (toilet.getPaper() < 1) {
                
                    System.out.println(name + " is waiting for replacing paper.");
                    
                    try {
                        // 대기 중인 청소부 소환
                        forCleaner.signal();
                        // 휴지가 없으므로 대기 pool로 이동
                        forPerson.await();
                        Thread.sleep(500);
                        System.out.println(name + " wakes.");
                    }
                    //
                    catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            
                // 화장실 볼 일을 보고 휴지를 사용 후 화장실 시용을 종료
                System.out.println(name + " uses toilet.");
                usePaper();
                try {
                    // 휴지가 없으면 다른 사람을 위해 청소부에게 알린다.
                    if (toilet.getPaper() <= 0) {
                        forCleaner.signal();
                    }
                    // 자신은 화장실을 나간다.
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
        
        // 관리하는 화장실을 지정
        Cleaner cleaner = new Cleaner(toilet, lock, forCleaner, forPerson);
        Thread cleanerThread = new Thread(cleaner, "Cleaner");
        cleanerThread.start();

        Person[] people = new Person[5];
        for (int i = 0; i < people.length; i++) {
            // 사람 객체 생성, 이 사람이 사용해야하는 화장실도 지정
            people[i] = new Person(toilet, lock, forCleaner, forPerson);
            Thread th = new Thread(people[i], "Person-" + i);
            // 사람 객체를 행동시키는 스레드를 실행
            th.start();
        }
    }
}
