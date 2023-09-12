public class Main{
    public static void main(String args[])
    {
        //Define the arrays
        int A[] = {0,5,8,9,10};
        int B[] = {6,8,7,3,5};
        int N = A.length;
        
        //Compute the waiting time and turnaround time
        nonPreemptive(A,B,N);
    }
    
    static void nonPreemptive(int[] A, int[] B, int N)
    {
        //Burst time of first process is considered as its execution time
        int completionTime[] = new int[N];
        completionTime[0] = B[0];
        
        //Turnaround time for the first process is its burst time
        int turnaroundTime[] = new int[N];
        turnaroundTime[0] = B[0];
        
        //For the remaining processes
        for(int i= 1; i< N; i++)
        {
            //Arrival time of ith processes
            completionTime[i] = completionTime[i-1] + B[i];
         
            //Turnaround time is difference between correct completion time and arrival time
            turnaroundTime[i] = completionTime[i] - A[i];
            
            //Waiting time is difference between turnaround time and burst time
            System.out.print("Process " + i + " Waiting time = " + (turnaroundTime[i] - B[i]));
            System.out.println();
        }
        
        //Print the average waiting time and average turnaround time
        int totalWaitingTime = 0;
        int totalTurnaroundTime = 0;
        
        for(int i=0; i< N; i++)
        { 
            //Sum all the waiting times
            totalWaitingTime += turnaroundTime[i] - B[i];
            
            //Sum all the turnaround times
            totalTurnaroundTime += turnaroundTime[i];  
        }
        
        System.out.println("Average Waiting time = " + (double)totalWaitingTime / N);  //Divide the total waiting time by number of processes
        System.out.println("Average Turnaround time = " + (double)totalTurnaroundTime / N); //Divide the total turnaround time by number of processes
    }
}