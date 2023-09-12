import java.util.*;
 
class Process
{
    int pid;
    int bt;
    int priority;
 
    public Process(int pid, int bt, int priority)
    {
        this.pid = pid;
        this.bt = bt;
        this.priority = priority;
    }
}
 
public class Main{
    public static void main(String[] args)
    {
        Scanner scan = new Scanner(System.in);
 
        System.out.println("Enter number of Processes :");
        int p = scan.nextInt();
 
        Process Pro[] = new Process[p];
        System.out.println("Enter Process Id, Burst Time and Priority :");
        for (int i = 0; i < p; i++)
        {
            int pid = scan.nextInt();
            int bt = scan.nextInt();
            int priority = scan.nextInt();
 
            Pro[i] = new Process(pid, bt, priority);
        }
 
        System.out.println("\nFCFS :");
        FCFS(Pro, p);
 
        // System.out.println("\nSJF :");
        // SJF(Pro, p);
 
        // System.out.println("\nRoundRobin :");
        // RoundRobin(Pro, p);
 
        // System.out.println("\nPriority :");
        // Priority(Pro, p);
    }
 
    public static void FCFS(Process Pro[], int p)
    {
        int wt[] = new int[p];
        int tat[] = new int[p];
        int total_wt = 0;
        int total_tat = 0;
 
        wt[0] = 0;
 
        for (int i = 1; i < p; i++) {
            wt[i] =  Pro[i-1].bt + wt[i-1];
        }
 
        for (int i = 0; i < p; i++) {
            tat[i] = Pro[i].bt + wt[i];
            total_wt = total_wt + wt[i];
            total_tat = total_tat + tat[i];
        }
 
        System.out.println("PID \t BT \t WT \t TAT");
        for (int i = 0; i < p; i++)
        {
            System.out.println(Pro[i].pid + "\t" + Pro[i].bt + "\t" + wt[i] + "\t" + tat[i]);
        }
 
        float s = (float)total_wt / p;
        float t = (float)total_tat / p;
        System.out.println("Average Waiting Time : " + s);
        System.out.println("Average Turnaround Time : " + t);
    }
 
    public static void SJF(Process Pro[], int p)
    {
        int wt[] = new int[p];
        int tat[] = new int[p];
        int total_wt = 0;
        int total_tat = 0;
 
        for (int i = 0; i < p; i++)
        {
            int pos = i;
            for (int j = i; j < p; j++)
            {
                if (Pro[j].bt < Pro[pos].bt)
                {
                    pos = j;
                }
            }
 
            int temp = Pro[i].bt;
            Pro[i].bt = Pro[pos].bt;
            Pro[pos].bt = temp;
 
            temp = Pro[i].pid;
            Pro[i].pid = Pro[pos].pid;
            Pro[pos].pid = temp;
        }
 
        wt[0] = 0;
 
        for (int i = 1; i < p; i++) {
            wt[i] =  Pro[i-1].bt + wt[i-1];
        }
 
        for (int i = 0; i < p; i++) {
            tat[i] = Pro[i].bt + wt[i];
            total_wt = total_wt + wt[i];
            total_tat = total_tat + tat[i];
        }
 
        System.out.println("PID \t BT \t WT \t TAT");
        for (int i = 0; i < p; i++)
        {
            System.out.println(Pro[i].pid + "\t" + Pro[i].bt + "\t" + wt[i] + "\t" + tat[i]);
        }
 
        float s = (float)total_wt / p;
        float t = (float)total_tat / p;
        System.out.println("Average Waiting Time : " + s);
        System.out.println("Average Turnaround Time : " + t);
    }
 
    public static void RoundRobin(Process Pro[], int p)
    {
        Scanner scan = new Scanner(System.in);
        System.out.println("Enter time quantum :");
        int tq = scan.nextInt();
 
        int wt[] = new int[p];
        int tat[] = new int[p];
        int total_wt = 0;
        int total_tat = 0;
 
        for (int i = 0; i < p; i++)
        {
            wt[i] = 0;
            tat[i] = 0;
        }
 
        int rt[] = new int[p];
 
        for (int i = 0; i < p; i++)
        {
            rt[i] = Pro[i].bt;
        }
 
        int remain = p;
        int curt = 0;
        while (remain != 0)
        {
            if (rt[curt] <= tq && rt[curt] > 0)
            {
                curt = curt + tq;
                rt[curt] = rt[curt] - tq;
            }
            else if (rt[curt] > 0)
            {
                curt = curt + rt[curt];
                rt[curt] = 0;
            }
 
            if (rt[curt] == 0 && remain != 0)
            {
                remain--;
                System.out.println("P" + Pro[curt].pid + " Complete");
                total_wt = total_wt + curt - Pro[curt].bt - Pro[curt].priority;
                total_tat = total_tat + curt - Pro[curt].priority;
                wt[curt] = curt - Pro[curt].bt - Pro[curt].priority;
                tat[curt] = curt - Pro[curt].priority;
            }
            if (curt == p)
            {
                curt = 0;
            }
            else if (Pro[curt+1].priority < Pro[curt].priority)
            {
                curt = curt + 1;
            }
        }
 
        System.out.println("PID \t BT \t WT \t TAT");
        for (int i = 0; i < p; i++)
        {
            System.out.println(Pro[i].pid + "\t" + Pro[i].bt + "\t" + wt[i] + "\t" + tat[i]);
        }
 
        float s = (float)total_wt / p;
        float t = (float)total_tat / p;
        System.out.println("Average Waiting Time : " + s);
        System.out.println("Average Turnaround Time : " + t);
    }
 
    public static void Priority(Process Pro[], int p)
    {
        int wt[] = new int[p];
        int tat[] = new int[p];
        int total_wt = 0;
        int total_tat = 0;
 
        for (int i = 0; i < p; i++)
        {
            int pos = i;
            for (int j = i; j < p; j++)
            {
                if (Pro[j].priority < Pro[pos].priority)
                {
                    pos = j;
                }
            }
 
            int temp = Pro[i].bt;
            Pro[i].bt = Pro[pos].bt;
            Pro[pos].bt = temp;
 
            temp = Pro[i].pid;
            Pro[i].pid = Pro[pos].pid;
            Pro[pos].pid = temp;
 
            temp = Pro[i].priority;
            Pro[i].priority = Pro[pos].priority;
            Pro[pos].priority = temp;
        }
 
        wt[0] = 0;
 
        for (int i = 1; i < p; i++) {
            wt[i] =  Pro[i-1].bt + wt[i-1];
        }
 
        for (int i = 0; i < p; i++) {
            tat[i] = Pro[i].bt + wt[i];
            total_wt = total_wt + wt[i];
            total_tat = total_tat + tat[i];
        }
 
        System.out.println("PID \t BT \t WT \t TAT");
        for (int i = 0; i < p; i++)
        {
            System.out.println(Pro[i].pid + "\t" + Pro[i].bt + "\t" + wt[i] + "\t" + tat[i]);
        }
 
        float s = (float)total_wt / p;
        float t = (float)total_tat / p;
        System.out.println("Average Waiting Time : " + s);
        System.out.println("Average Turnaround Time : " + t);
    }
}