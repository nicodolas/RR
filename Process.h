class Process_queue
{
public:
	int time;
	bool isInputBurst;
	bool isInInputQueue = false;
	bool isOutputBurst;
	bool isInOutputQueue = false;
	bool isCpuBurst;
	bool isIn_CPU_Queue = false;
};

class Process
{
private:
	int pid;
	int arrivalTime;
	int priority;
	int share;
	int exitTime = -1;

public:
	int totalBurstTime = 0;
	int remainingTime;
	int responseTime;
	int completionTime;
	int executionStartTime = -1;
	queue<Process_queue> burst_queue;

	int getTurnAroundTime()
	{
		// cout<<this->exitTime<<"-"<<this->arrivalTime<<endl;
		return this->exitTime - this->arrivalTime;
	}
	int getWaitingTime()
	{
		return this->getTurnAroundTime() - this->totalBurstTime + 1;
	}
	// TO DO
	int getResponseTime()
	{
		return (this->executionStartTime - this->arrivalTime);
	}

	void setExecutionStartTime(int t)
	{
		this->executionStartTime = t;
	}

	void setExitTime(int exitTime)
	{
		this->exitTime = exitTime;
	}

	void setPid(int pid)
	{
		this->pid = pid;
	}
	void setArrivalTime(int arrivalTime)
	{
		this->arrivalTime = arrivalTime;
	}
	void setPriority(int priority)
	{
		this->priority = priority;
	}
	void setShare(int share)
	{
		this->share = share;
	}

	int getPid()
	{
		return this->pid;
	}
	int getArrivalTime()
	{
		return this->arrivalTime;
	}
	int getExitTime()
	{
		return this->exitTime;
	}
	int getPriority()
	{
		return this->priority;
	}
	int getShare()
	{
		return this->share;
	}

	Process()
	{
	}
};

/*
TODO : add support for showing output
*/
class Chart
{
public:
	int value = -1;
	bool isCpu = false;
	bool isInput = false;
	bool isOutput = false;
};

void printGanttChart(queue<int> cpu, queue<int> input, queue<int> output, int size, int time)
{

	for (int i = 0; i <= time; i++)
	{
		cout << i << "   ";
	}
	cout << endl;

	Chart chart[size][time + 1];

	for (int j = 0; j <= time; j++)
	{
		for (int i = 0; i < size; i++)
		{

			if (cpu.size() > 0 && cpu.front() == i + 1)
			{
				chart[i][j].value = cpu.front();
				chart[i][j].isCpu = true;
			}

			if (input.size() > 0 && input.front() == i + 1)
			{
				chart[i][j].value = input.front();
				chart[i][j].isInput = true;
			}
			if (output.size() > 0 && output.front() == i + 1)
			{
				chart[i][j].value = output.front();
				chart[i][j].isOutput = true;
			}
		}
		if (cpu.size() > 0)
			cpu.pop();
		if (input.size() > 0)
			input.pop();
		if (output.size() > 0)
			output.pop();
	}

	for (int i = 0; i < size; i++)
	{

		string str = "    ";
		for (int j = 0; j < time; j++)
		{

			if (chart[i][j].value < 0)
			{
				cout << str;
			}
			if (chart[i][j].isCpu)
			{
				// red
				cout << "\033[1;41mp" << chart[i][j].value << "\033[0m  ";
				// cout << "p" << chart[i][j].value << "  ";
				//str = "W  ";
			}
			else if (chart[i][j].isInput)
			{
				// yellow
				cout << "\033[1;43mI" << chart[i][j].value << "\033[0m  ";
				// cout << "I" << chart[i][j].value << "  ";
			}
			else if (chart[i][j].isOutput)
			{
				// cyan
				cout << "\033[1;46mO" << chart[i][j].value << "\033[0m  ";
				// cout << "O" << chart[i][j].value << "  ";
			}
			if (j >= 10)
				cout << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void printChart(queue<int> q, string type)
{

	for (int i = 0; i < q.size(); i++)
	{
		cout << i << "  ";
	}
	cout << endl;

	int size = q.size();
	for (int i = 0; i < size; i++)
	{
		if (q.front() != -1)
		{

			if (type == "process")
				cout << "\033[1;41mp" << q.front() << "\033[0m  ";

			else if (type == "input")
				cout << "\033[1;43mI" << q.front() << "\033[0m  ";

			else
				cout << "\033[1;46mO" << q.front() << "\033[0m  ";
		}
		else
		{
			cout << "   ";
		}
		if (i >= 10)
		{
			cout << " ";
		}

		q.pop();
	}
}

void printTurnAroundTime(vector<Process> process_vector)
{
	int total = 0;
	for (int j = 0; j < process_vector.size(); j++)
	{
		int i = process_vector[j].getPid() - 1;
		cout << "P" << j + 1 << " turn around time : " << process_vector[i].getTurnAroundTime() << endl;
		total += process_vector[i].getTurnAroundTime();
	}
	cout << " total turn around time :" << total << endl
		<< fixed << setprecision(2);
	;
	int size = process_vector.size();
	cout << " average turn around time :" << (float)total / (float)size << endl;
}

void printWaitingTime(vector<Process> process_vector)
{
	int total = 0;
	for (int j = 0; j < process_vector.size(); j++)
	{
		int i = process_vector[j].getPid() - 1;
		cout << "P" << j + 1 << " waiting time : " << process_vector[i].getWaitingTime() << endl;
		total += process_vector[i].getWaitingTime();
	}
	cout << " total waiting time :" << total << endl
		<< fixed << setprecision(2);
	int size = process_vector.size();
	cout << " average waiting time :" << (float)total / (float)size << endl;
}

void printResponseTime(vector<Process> process_vector)
{
	int total = 0;
	for (int j = 0; j < process_vector.size(); j++)
	{
		int i = process_vector[j].getPid() - 1;
		cout << "P" << j + 1 << " response time : " << process_vector[i].getResponseTime() << endl;
		total += process_vector[i].getResponseTime();
	}
	cout << " total response time :" << total << endl
		<< fixed << setprecision(2);
	int size = process_vector.size();
	cout << " average response time :" << (float)total / (float)size << endl;
}

void printInput(vector<Process> process_vector)
{
	for (int i = 0; i < process_vector.size(); i++)
	{
		cout << process_vector[i].getPid() << " " << process_vector[i].getArrivalTime() << " " << process_vector[i].getPriority() << " " << process_vector[i].getShare();
		while (process_vector[i].burst_queue.size() > 0)
		{
			if (process_vector[i].burst_queue.front().isCpuBurst)
				cout << " C ";
			else
			{
				cout << " I/O ";
			}
			cout << process_vector[i].burst_queue.front().time;
			process_vector[i].burst_queue.pop();
		}
		cout << endl;
	}
}

bool haveAllProcessesExecuted(vector<Process> &process_vector)
{

	for (int i = 0; i < process_vector.size(); i++)
	{
		if (process_vector[i].burst_queue.size() > 0)
		{
			return false;
		}
	}
	return true;
}

void setExitTime(vector<Process> &process_vector, int time)
{

	for (int i = 0; i < process_vector.size(); i++)
	{

		if ((process_vector[i].burst_queue.size() == 0) && (process_vector[i].getExitTime() == -1))
			process_vector[i].setExitTime(time);
	}
}

class Io
{
private:
	bool isInputBurst;
	queue<int> io_queue; // pid

	void decrementBurst(int pid, vector<Process> &process_vector)
	{

		for (int i = 0; i < process_vector.size(); i++)
		{

			if (process_vector[i].getPid() == pid)
			{
				process_vector[i].burst_queue.front().time -= 1;

				//if burst has become zero pop from io_queue and from burst_queue

				if (process_vector[i].burst_queue.front().time <= 0)
				{
					process_vector[i].burst_queue.pop();
					this->io_queue.pop();
				}
				break;
			}
		}
	}

public:
	queue<int> gantt_io_queue;

	Io(string str)
	{
		if (str == "Input")
			isInputBurst = true;
		else
			isInputBurst = false;
	}

	void execute_IO(vector<Process> &process_vector, int time)
	{

		// find processes waiting for input/output & add them to io_queue
		for (int i = 0; i < process_vector.size(); i++)
		{

			// handle condition when burst queue is empty
			if (process_vector[i].burst_queue.size() == 0)
				continue;

			if (isInputBurst)
				if (process_vector[i].burst_queue.front().isInputBurst && process_vector[i].burst_queue.front().isInInputQueue == false && process_vector[i].getArrivalTime() <= time)
				{
					this->io_queue.push(process_vector[i].getPid());
					process_vector[i].burst_queue.front().isInInputQueue = true;

					if (process_vector[i].executionStartTime == -1)
						process_vector[i].setExecutionStartTime(time);
				}
			if (!isInputBurst)
				if (process_vector[i].burst_queue.front().isOutputBurst && process_vector[i].burst_queue.front().isInOutputQueue == false && process_vector[i].getArrivalTime() <= time)
				{

					this->io_queue.push(process_vector[i].getPid());
					process_vector[i].burst_queue.front().isInOutputQueue = true;

					if (process_vector[i].executionStartTime == -1)
						process_vector[i].setExecutionStartTime(time);
				}
		}

		if (this->io_queue.size() == 0)
		{
			this->gantt_io_queue.push(-1);
			return;
		}

		// extract process from io_queue and decrement its input

		int pid = this->io_queue.front();
		this->decrementBurst(pid, process_vector);
		this->gantt_io_queue.push(pid);
	}
};
// if no process is executing push -1 into g_queue
// public execute_IO(){io_queue.front().burstTime--; g_queue.push(io_queue.front().pid) };

void handleInput(vector<Process> &process_vector, ifstream &file)
{

	int text;
	file >> text;
	int processes = text;

	while (processes--)
	{
		Process process;

		file >> text;
		process.setPid(text);
		file >> text;
		process.setArrivalTime(text);
		file >> text;
		process.setPriority(text);
		file >> text;
		process.setShare(text);

		string str;
		Process_queue pq;

		while (file >> str)
		{
			if (str == "-1")
				break;
			else
			{
				file >> text;
				pq.time = text;
				process.totalBurstTime += text;
				if (str == "C")
				{
					pq.isCpuBurst = true;
					pq.isInputBurst = false;
					pq.isOutputBurst = false;
				}
				else if (str == "I")
				{
					pq.isCpuBurst = false;
					pq.isInputBurst = true;
					pq.isOutputBurst = false;
				}
				else if (str == "O")
				{
					pq.isCpuBurst = false;
					pq.isInputBurst = false;
					pq.isOutputBurst = true;
				}
				process.burst_queue.push(pq);
			}
		}
		process_vector.push_back(process);
	}
}

void handleOutput(queue<int> &gantt_cpu_queue, queue<int> &input_queue,
	queue<int> &output_queue, vector<Process> &process_vector, int time)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	// pass inputOutput as argument to print gantt
	cout << SCHEDULER << "\n";
	cout << "Gantt Chart\n";
	printGanttChart(gantt_cpu_queue, input_queue, output_queue, process_vector.size(), time);

	cout << "CPU Chart :\n";
	printChart(gantt_cpu_queue, "process");
	cout << endl;

	cout << "\nInput Chart :\n";
	printChart(input_queue, "input");
	cout << endl;

	cout << "\nOutput Chart :\n";
	printChart(output_queue, "output");
	cout << endl;

	// output turn around time
	cout << endl;
	printTurnAroundTime(process_vector);
	cout << endl;

	// output waiting time
	printWaitingTime(process_vector);
	cout << endl;

	// output response time
	printResponseTime(process_vector);
	cout << endl;
}