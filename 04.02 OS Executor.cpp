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
            //runnable �� �޸� return �� �� �� �ִ�
            ExecutorService pool = Executors.newSingleThreadExecutor();
            Future<Integer> result = pool.submit(new Summation(upper));
            //callable�½�ũ�� �����忡 ����(submit)�ϸ�, �����尡 ��ȯ�ϴ�
            //future��ü�� get() �޼ҵ带 ȣ���Ͽ� ����� ��ٸ���.
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
