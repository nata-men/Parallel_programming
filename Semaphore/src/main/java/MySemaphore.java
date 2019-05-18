import sun.awt.Mutex;

import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class MySemaphore extends Semaphore {
    private int permits;

    ReentrantLock locker;
    Condition condition;

    public MySemaphore(int permits) {
        super(permits);

        this.permits = permits;

        locker = new ReentrantLock(); // создаем блокировку
        condition = locker.newCondition(); // получаем условие, связанное с блокировкой
    }

    public MySemaphore(int permits, boolean fair) {
        super(permits, fair);
    }

    @Override
    public void acquire() {
        locker.lock();
        try{
            //пока нет слота, ожидаем
            while (permits < 1)
                condition.await();

            permits--;
        }
        catch (InterruptedException e){
            System.out.println(e.getMessage());
        }
        locker.unlock();
    }

    @Override
    public void release(){
        locker.lock();

        permits++;
        if(permits > 0)
            // сигнализируем
            condition.signalAll();

        locker.unlock();
    }


}
