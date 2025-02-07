import java.util.*;
import java.io.*;
import java.util.concurrent.Semaphore;

class Main {
    public static void main(String[] args) throws IOException {
        Buffer bf = new Buffer(5);
        for (int i = 1; i <= 10; i++) {
            bf.insert(i);
            bf.remove();
        }
    }
}

class Buffer {
    int[] buf; // 배열 형태의 버퍼
    int size, count, in , out;
    Semaphore mutex, pro, con; // 세마포어 변수
    Buffer(int size) {
        buf = new int[size];
        this.size = size;
        count = in = out = 0;
        mutex = new Semaphore(1);
        pro = new Semaphore(size); // 생산자 세마포어
        con = new Semaphore(0); // 소비자 세마포어
    }
    void insert(int item) {
        try {
            pro.acquire(); // 버퍼의 남은 공간 검사
            mutex.acquire(); // 상호 배타
            count++;
            buf[in] = item;
            System.out.println(buf[in] + " produced");
            in = (in + 1) % size;
            mutex.release(); // 상호 배타 해제
            con.release(); // 버퍼에 요소 존재함
        } catch (InterruptedException e) {}
    }
    void remove() {
        try {
            con.acquire(); // 버퍼에 남은 요소 검사
            mutex.acquire(); // 상호 배타
            count--;
            System.out.println(buf[out] + " consumed");
            out = (out + 1) % size;
            mutex.release(); // 상호 배타 해제
            pro.release(); // 빈 버퍼 공간 확보됨
        } catch (InterruptedException e) {}
    }
}
