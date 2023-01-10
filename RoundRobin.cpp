#include <iostream>
#include <utility> 
#include <queue>
using namespace std;

struct Process {
	int pid; //Process ID
	int arr; //Arrival time
	int bur; //Burst time
	int start; //Start time
	int fin; //Finish time
	int tat; //Turnaround time
	int wt; //Waiting time
	int remain_time;
	int flag;
	int check;
};
Process p[10];
//sap xep theo thoi gian den cua process
void sortarr(int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (p[j].arr < p[i].arr)
				swap(p[i], p[j]);
		}
	}
}
//sap xep theo pid
void sortpid(int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (p[j].pid < p[i].pid)
				swap(p[i], p[j]);
		}
	}
}
void output(int n, float sumtat, float sumwt)
{
	for (int i = 0; i < n; i++)
	{
		sumtat += p[i].tat;
		sumwt += p[i].wt;
	}
	float tottat = sumtat / n;
	float totwt = sumwt / n;
	cout << "\nPID\tArrival time\tBurst time\tStart time\tFinish time\tWaiting time\tTurnaroud time";
	for (int i = 0; i < n; i++)
	{
		cout << endl << p[i].pid << "\t" << p[i].arr << "\t\t" << p[i].bur << "\t\t" << p[i].start << "\t\t" << p[i].fin << "\t\t" << p[i].wt << "\t\t" << p[i].tat;
	}
	cout << "\nTotal turnaround time : " << tottat;
	cout << "\nTotal waiting time : " << totwt;
}
int main()
{
	queue<Process> PQueue;
	int n, q;//so tien trinh, quantum time
	float tottat = 0, totwt = 0;
	cout << "Enter the number of processes: ";
	cin >> n;
	cout << "Enter time quantum: ";
	cin >> q;
	//nhap thong tin cac tien trinh
	
	for (int i = 0; i < n; i++)
	{
		cout << "Enter arrival time, burst time of process " << i + 1 << ": ";
		p[i].pid = i+1 ;
		cin >> p[i].arr;
		cin >> p[i].bur;
		p[i].remain_time = p[i].bur;
		p[i].fin = 0;
		p[i].start = 0;
		p[i].tat = 0;
		p[i].wt = 0;//
		p[i].flag = 0;
		p[i].check = 0;
	}
	//sap xep tien trinh theo thoi gian den
	sortarr(n);
	
	int time = 0; //current time
	int done = 0;//so tien trinh da hoan thanh
	//int remain = n;
	int pending = 0;//ktra so process da vao hang doi
	Process tmp;
	//bat dau
	PQueue.push(p[0]);
	p[0].flag = 1;
	//remain--;
	pending++;
	time = p[0].arr;
	while (done < n)
	{
		//int change = 0;
		for (int k = pending; k < n; k++)
		{
			if (p[k].flag == 0 && pending < n && p[k].arr <= time)
			{
				PQueue.push(p[k]);
				p[k].flag = 1;
				//remain--;
				pending++;
			}
			else
				break;
		}
		if (!PQueue.empty())
		{
				//neu la chay lan dau
				if (PQueue.front().check == 0)
				{
					PQueue.front().start = time;
					PQueue.front().check = 1;
				}
				//case 1: remaining_time <= quantum time
				if (PQueue.front().remain_time <= q)
				{
					time += PQueue.front().remain_time;
					PQueue.front().fin = time;
					PQueue.front().tat = PQueue.front().fin - PQueue.front().arr;
					PQueue.front().wt = PQueue.front().tat - PQueue.front().bur;
					PQueue.front().remain_time = 0;
					for (int i = 0; i < n; i++)
					{
						if (PQueue.front().pid == p[i].pid)
						{
							p[i] = PQueue.front();
							break;
						}
					}
						PQueue.pop();
						done++;
				}
				else //case 2: remaining_time > q
				{
					time += q;
					PQueue.front().remain_time -= q;
					tmp = PQueue.front();
					PQueue.pop();						
					for (int j = pending; j < n; j++)
					{
						if (p[j].arr <= time)
						{
							PQueue.push(p[j]);
							p[j].flag == 0;
							pending++;
						}
						else
							break;
					}
					PQueue.push(tmp);
				}

					//change++;
		}
			//if (change == 0)//khong co tien trinh nao trong hang doi
		else
			time++;
	}
	sortpid(n);
	float sumtat = 0, sumwt = 0;
	output(n, sumtat, sumwt);
	return 0;
}