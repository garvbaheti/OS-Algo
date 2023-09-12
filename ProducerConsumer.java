import java.util.concurrent.Semaphore; 
public class ProducerConsumer { 
    public static void main(String args[]) { 
        int bufferSize = 10; 
        Semaphore semaphore_prod = new Semaphore(1); 
        Semaphore semaphore_cons = new Semaphore(0); 
        Buffer buffer = new Buffer(bufferSize); 
        Consumer consumer = new Consumer(buffer, semaphore_prod, semaphore_cons); 
        Producer producer = new Producer(buffer, semaphore_prod, semaphore_cons); 
        producer.start(); 
        consumer.start(); 
    } 
} 
class Buffer { 
    private int bufferSize; 
    private int[] buffer; 
    private int count; 
    Buffer(int bufferSize) { 
        this.bufferSize = bufferSize; 
        this.count = 0; 
        this.buffer = new int[bufferSize]; 
    } 
    public void add(int value) { 
        this.buffer[count] = value; 
        count++; 
    } 
    public int remove() { 
        int value = this.buffer[0]; 
        for (int i = 0; i < count - 1; i++) { 
            this.buffer[i] = this.buffer[i + 1]; 
        } 
        count--; 
        return value; 
    } 
    public boolean isEmpty() { 
        return count == 0; 
    } 
    public boolean isFull() { 
        return count == this.bufferSize; 
    } 
} 
class Consumer extends Thread { 
    private Buffer buffer; 
    private Semaphore semaphore_prod; 
    private Semaphore semaphore_cons; 
    Consumer(Buffer buffer, Semaphore semaphore_prod, Semaphore semaphore_cons) { 
        this.buffer = buffer; 
        this.semaphore_prod = semaphore_prod; 
        this.semaphore_cons = semaphore_cons; 
    } 
    public void run() { 
        int value = 0; 
        for (int i = 0; i < 10; i++) { 
            try { 
                semaphore_cons.acquire(); 
                value = buffer.remove(); 
                System.out.println("Consumer Value: " + value); 
                semaphore_prod.release(); 
            } 
            catch(InterruptedException e) { 
                System.out.println(e); 
            } 
        } 
    } 
} 
class Producer extends Thread { 
    private Buffer buffer; 
    private Semaphore semaphore_prod; 
    private Semaphore semaphore_cons; 
    Producer(Buffer buffer, Semaphore semaphore_prod, Semaphore semaphore_cons) { 
        this.buffer = buffer; 
        this.semaphore_prod = semaphore_prod; 
        this.semaphore_cons = semaphore_cons; 
    } 
    public void run() { 
        for (int i = 0; i < 10; i++) { 
            try { 
                semaphore_prod.acquire(); 
                buffer.add(i); 
                System.out.println("Producer Value: " + i); 
                semaphore_cons.release(); 
            } 
            catch(InterruptedException e) { 
                System.out.println(e); 
            } 
        } 
    } 
}