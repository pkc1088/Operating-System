import java.util.concurrent.*;

class Summation implements Callable<Integer>
{
    private int upper;

    public Summation(int upper) {
        this.upper = upper;
    }

    public Integer call() {
        int sum = 0;
        for (int i = 1; i <= upper; i++)
            sum += i;

        return sum;
    }
}


public class Main
{
    public static void main(String[] args) {
            int upper = 10;
            //runnable 과 달리 return 을 할 수 있다
            ExecutorService pool = Executors.newSingleThreadExecutor();
            Future<Integer> result = pool.submit(new Summation(upper));
            //callable태스크를 스레드에 제출(submit)하면, 스레드가 반환하는
            //future객체의 get() 메소드를 호출하여 결과를 기다린다.
            try {
                System.out.println("sum = " + result.get());
            }
            catch (InterruptedException | ExecutionException ie) { }

            pool.shutdown();
    }
}

/*
import java.util.concurrent.*;

class Task implements Runnable
{
    public void run() {
        System.out.println(Thread.currentThread().getName());
    }
}

public class Sub
{
    public static void main(String[] args) {
        int numTasks = 5;

        ExecutorService pool = Executors.newCachedThreadPool();

        for (int i = 0; i < numTasks; i++)
            pool.execute(new Task());

        // The following invovles using a lambda function
        // pool.execute( () -> {System.out.println(Thread.currentThread().getName());});

        pool.shutdown();
    }
}
*/
