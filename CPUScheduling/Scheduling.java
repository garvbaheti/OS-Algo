public class Scheduling {
 
    private int[] arrivalTime;
    private int[] burstTime;
    private int[] completionTime;
    private int[] waitingTime;
    private int[] turnAroundTime;
    private int[] processID;
    private int noOfProcesses;
 
    public Scheduling(int[] arrivalTime, int[] burstTime, int[] processID) {
        noOfProcesses = arrivalTime.length;
        this. arrivalTime = arrivalTime;
        this.burstTime = burstTime;
        this.processID = processID;
        waitingTime = new int[noOfProcesses];
        completionTime = new int[noOfProcesses];
        turnAroundTime = new int[noOfProcesses];
    }
 
    //First come first serve scheduling algorithm
    public void fcfs() {
        completionTime[0] = arrivalTime[0] + burstTime[0];
        turnAroundTime[0] = completionTime[0] - arrivalTime[0];
        waitingTime[0] = 0;
        for(int i=1; i<noOfProcesses; i++) {
            completionTime[i] = burstTime[i-1] + completionTime[i-1];
            waitingTime[i] = completionTime[i] - arrivalTime[i];
            turnAroundTime[i] = waitingTime[i] + burstTime[i];
        }
    }
 
    //Priority scheduling algorithm
    public void priorityScheduling() {
        int minProcess;
        for(int i=0; i<noOfProcesses; i++) {
            minProcess = i;
            for(int j=i+1; j<noOfProcesses; j++) {
                if(arrivalTime[j] < arrivalTime[minProcess]) {
                    minProcess = j;
                }
            }
 
            //swap arrival time
            int tempArrivalTime = arrivalTime[i];
            arrivalTime[i] = arrivalTime[minProcess];
            arrivalTime[minProcess] = tempArrivalTime;
 
            //swap burst time
            int tempBurstTime = burstTime[i];
            burstTime[i] = burstTime[minProcess];
            burstTime[minProcess] = tempBurstTime;
 
            //swap pid
            int tempProcessID = processID[i];
            processID[i] = processID[minProcess];
            processID[minProcess] = tempProcessID;
        }
 
        //find waiting time and completion time
        waitingTime[0] = 0;
        completionTime[0] = burstTime[0];
 
        turnAroundTime[0] = burstTime[0];
 
        for(int i=1; i<noOfProcesses; i++) {
            waitingTime[i] = completionTime[i-1] - arrivalTime[i];
            completionTime[i] = burstTime[i] + completionTime[i-1];
            turnAroundTime[i] = completionTime[i] - arrivalTime[i];
        }
    }
 
    //Shortest job first scheduling algorithm
    public void sjf() {
        int minProcess;
        for(int i=0; i<noOfProcesses; i++) {
            minProcess = i;
            for(int j=i+1; j<noOfProcesses; j++) {
                if(arrivalTime[j] < arrivalTime[minProcess]) {
                    minProcess = j;
                }
            }
 
            //swap arrival time
            int tempArrivalTime = arrivalTime[i];
            arrivalTime[i] = arrivalTime[minProcess];
            arrivalTime[minProcess] = tempArrivalTime;
 
            //swap burst time
            int tempBurstTime = burstTime[i];
            burstTime[i] = burstTime[minProcess];
            burstTime[minProcess] = tempBurstTime;
 
            //swap pid
            int tempProcessID = processID[i];
            processID[i] = processID[minProcess];
            processID[minProcess] = tempProcessID;
        }
 
        //find waiting time and completion time
        waitingTime[0] = 0;
        completionTime[0] = burstTime[0];
 
        for(int i=1; i<noOfProcesses; i++) {
            waitingTime[i] = completionTime[i-1] - arrivalTime[i];
            completionTime[i] = burstTime[i] + completionTime[i-1];
            turnAroundTime[i] = completionTime[i] - arrivalTime[i];
        }
    }
 
    //round robin scheduling algorithm
    public void roundRobin() {
        int initArrivalTime[] = new int[noOfProcesses];
        int initBurstTime[] = new int[noOfProcesses];
        int initProcessID[] = new int[noOfProcesses];
 
        for(int i=0; i<noOfProcesses; i++) {
            initArrivalTime[i] = arrivalTime[i];
            initBurstTime[i] = burstTime[i];
            initProcessID[i] = processID[i];
        }
 
        int q = 4;
 
        int t = 0;
        int minBurst = 999;
        int doneProcesses = 0;
        int count = 0;
 
        int i;
        while(doneProcesses != noOfProcesses) {
            for(i=0; i<noOfProcesses; i++) {
                if(initBurstTime[i] > 0 && initArrivalTime[i] <= t) {
                    if(initBurstTime[i] < minBurst) {
                        minBurst = initBurstTime[i];
                        count = i;
                    }
                }
            }
 
            if(initBurstTime[count] == minBurst && minBurst != 999) {
                doneProcesses++;
                t = t + minBurst;
                waitingTime[count] = t - initArrivalTime[count] - initBurstTime[count];
                turnAroundTime[count] = t - initArrivalTime[count];
                completionTime[count] = t;
                initBurstTime[count] = 0;
                minBurst = 999;
            }
            //if any process arrives at t time will go in this while loop
            while(t!=noOfProcesses) {
                for(i=0; i<noOfProcesses; i++) {
                    if(initArrivalTime[i] > t) {
                        waitingTime[i] = 0;
                        t++;
 
                    }
                    else if(initArrivalTime[i] == t) {
                        if(initBurstTime[i] <= 4) {
                            waitingTime[i] = 0;
                            turnAroundTime[i] = waitingTime[i] + initBurstTime[i];
                        }
                        else {
                            waitingTime[i] = 0;
                            turnAroundTime[i] = initBurstTime[i];
                        }
                        t++;
                    }
                }
            }
            for(i=0; i<noOfProcesses; i++) {
                if(completionTime[i] == 0 && initBurstTime[i] != 0) {
                    waitingTime[i] = t - arrivalTime[i];
                    t = t + initBurstTime[i];
                    turnAroundTime[i] = t - arrivalTime[i];
                    completionTime[i] = t;
                    initBurstTime[i] = 0;
                }
            }
        }
    }
 
    public int getAverageWaitingTime() {
        int sum = 0;
        for(int i=0; i<noOfProcesses; i++) {
            sum += waitingTime[i];
        }
        return sum/noOfProcesses;
    }
 
    public int getAverageTurnAroundTime() {
        int sum = 0;
        for(int i=0; i<noOfProcesses; i++) {
            sum += turnAroundTime[i];
        }
        return sum/noOfProcesses;
    }
 
    public void printWaitingTime() {
        System.out.println("Process\tWaiting Time\tTurnaround Time");
        for(int i=0; i<noOfProcesses; i++) {
            System.out.println("P[" + i +"]\t\t" + waitingTime[i] + "\t\t" + turnAroundTime[i]);
        }
        System.out.println("Average waiting time : " + getAverageWaitingTime());
        System.out.println("Average turnaround time : " + getAverageTurnAroundTime());
    }
 
    public static void main(String args[]) {
        int processID[] = {1, 2, 3, 4, 5};
        int burstTime[] = {2, 4, 1, 7, 3};
        int arrivalTime[] = {0,1,2,3,4};
 
        Scheduling scheduling = new Scheduling(arrivalTime, burstTime, processID);
        scheduling.fcfs();
        scheduling.printWaitingTime();
 
        scheduling = new Scheduling(arrivalTime, burstTime, processID);
        scheduling.priorityScheduling();
        scheduling.printWaitingTime();
 
        scheduling = new Scheduling(arrivalTime, burstTime, processID);
        scheduling.sjf();
        scheduling.printWaitingTime();
 
        scheduling = new Scheduling(arrivalTime, burstTime, processID);
        scheduling.roundRobin();
        scheduling.printWaitingTime();
 
    }
}