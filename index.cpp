#include <iostream>
#include <vector>
#include <climits>
#include <queue>
using namespace std;

void insert_values(int n, vector<int> &arrival_time, vector<int> &burst_time, vector<int> &priority_val, string priority = "No")
{

    int at, bt, pt;

    for (int i = 1; i <= n; i++)
    {
        if (priority == "Yes")
        {
            cout << "Enter priority for process p" << i << ": ";
            cin >> pt;
            priority_val.emplace_back(pt);
            cout << "Enter arrival time for process p" << i << ": ";
            cin >> at;
            arrival_time.emplace_back(at);
            cout << "Enter burst time for process p" << i << ": ";
            cin >> bt;
            burst_time.emplace_back(bt);
        }
        else
        {
            cout << "Enter arrival time for process p" << i << ": ";
            cin >> at;
            arrival_time.emplace_back(at);
            cout << "Enter burst time for process p" << i << ": ";
            cin >> bt;
            burst_time.emplace_back(bt);
        }
    }
}

void display_init(int n, vector<int> at, vector<int> bt, vector<int> pt = {0}, string ptr = "No")
{
    if (ptr == "Yes")
    {
        cout << "**********************************************" << endl;
        cout << "| Process Id   ";
        cout << "| Priority     ";
        cout << "| Arrival Time ";
        cout << "| Burst Time    |" << endl;
        cout << "**********************************************" << endl;
        for (int i = 0; i < n; i++)
        {
            cout << "| p" << (i + 1) << "     ";
            cout << "| " << pt[i] << "    ";
            cout << "| " << at[i] << "    ";
            cout << "| " << bt[i] << "     |";
            cout << endl;
        }
    }
    else
    {
        cout << "**********************************************" << endl;
        cout << "| Process Id   ";
        cout << "| Arrival Time ";
        cout << "| Burst Time   |" << endl;
        cout << "**********************************************" << endl;
        for (int i = 0; i < n; i++)
        {
            cout << "| p" << (i + 1) << "     ";
            cout << "| " << at[i] << "    ";
            cout << "| " << bt[i] << "     |";
            cout << endl;
        }
    }
}

void fcfs(int n, vector<int> arrival_time, vector<int> burst_time)
{
    float avg_wait = 0, avg_tat = 0;

    vector<int> tat;
    vector<int> wt;
    vector<int> ct;

    int cts = 0;

    for (int i = 0; i < n; i++)
    {
        cts += burst_time[i];
        ct.emplace_back(cts);
        int temp_tat = ct[i] - arrival_time[i];
        tat.emplace_back(temp_tat);
        int temp_wt = temp_tat - burst_time[i];
        wt.emplace_back(temp_wt);
    }

    cout << "Gantt Chart: " << endl;
    for (int i = 0; i < n; i++)
    {
        string temp = "P" + to_string(i + 1);
        string tr = to_string(ct[i]);

        string ans = "(" + temp + ", " + tr + "), ";
        cout << ans;
    }
    cout << endl;

    int sum = 0;
    int num;

    for (int i = 0; i < tat.size(); i++)
    {
        sum += tat[i];
    }

    num = tat.size();

    int sum1 = 0;

    for (int i = 0; i < wt.size(); i++)
    {
        sum1 += wt[i];
    }

    int num1 = wt.size();

    cout << "Final Result Table: \n";

    cout << "********************************************************************************************" << endl;
    cout << "| Process Id   ";
    cout << "| Arrival Time ";
    cout << "| Burst Time   ";
    cout << "| Completion   ";
    cout << "| Turn around  ";
    cout << "| waiting time |" << endl;
    cout << "********************************************************************************************" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "| p" << (i + 1) << "           ";
        cout << "| " << arrival_time[i] << "    ";
        cout << "| " << burst_time[i] << "      ";
        cout << "| " << ct[i] << "      ";
        cout << "| " << tat[i] << "      ";
        cout << "| " << wt[i] << "      ";
        cout << endl;
    }

    cout << "Average turn around time: " << sum / num << endl;
    cout << "Average waiting time: " << sum1 / num1 << endl;
}

int find_min(vector<int> bt)
{
    int min = INT_MAX;
    for (int i = 0; i < bt.size(); i++)
    {
        if (bt[i] < bt[min])
        {
            min = i;
        }
    }
    return min;
}

void sjf(int n, vector<int> at, vector<int> bt)
{

    vector<int> burst_time;
    burst_time = bt;

    int ref_ct, index;
    index = find_min(at);
    ref_ct = at[index];
    vector<int> ct(n, 0);
    int min_bt_index;

    for (int i = 0; i < n; i++)
    {
        min_bt_index = find_min(bt);
        vector<int> temp_bt;
        temp_bt = bt;
        while (ref_ct < at[min_bt_index])
        {
            temp_bt[min_bt_index] = INT_MAX;
            min_bt_index = find_min(temp_bt);
        }

        ct[min_bt_index] = ref_ct + bt[min_bt_index];
        ref_ct = ct[min_bt_index];
        bt[min_bt_index] = INT_MAX;
    }

    // cout << "Completion times: " << endl;

    // for (int i = 0; i < ct.size(); i++)
    // {
    //     cout << ct[i] << " ";
    // }
    // cout << endl;

    vector<int> tat;
    vector<int> wt;

    for (int i = 0; i < n; i++)
    {
        int temp_tat = ct[i] - at[i];
        tat.emplace_back(temp_tat);
        int temp_wt = temp_tat - burst_time[i];
        wt.emplace_back(temp_wt);
    }

    cout << "Gantt Chart: " << endl;
    for (int i = 0; i < n; i++)
    {
        string temp = "P" + to_string(i + 1);
        string tr = to_string(ct[i]);

        string ans = "(" + temp + ", " + tr + "), ";
        cout << ans;
    }
    cout << endl;

    int sum = 0;
    int num;

    for (int i = 0; i < tat.size(); i++)
    {
        sum += tat[i];
    }

    num = tat.size();

    int sum1 = 0;

    for (int i = 0; i < wt.size(); i++)
    {
        sum1 += wt[i];
    }

    int num1 = wt.size();

    cout << "Final Result Table: \n";

    cout << "********************************************************************************************" << endl;
    cout << "| Process Id   ";
    cout << "| Arrival Time ";
    cout << "| Burst Time   ";
    cout << "| Completion   ";
    cout << "| Turn around  ";
    cout << "| waiting time |" << endl;
    cout << "********************************************************************************************" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "| p" << (i + 1) << "           ";
        cout << "| " << at[i] << "    ";
        cout << "| " << burst_time[i] << "      ";
        cout << "| " << ct[i] << "      ";
        cout << "| " << tat[i] << "      ";
        cout << "| " << wt[i] << "      ";
        cout << endl;
    }

    cout << "Average turn around time: " << sum / num << endl;
    cout << "Average waiting time: " << sum1 / num1 << endl;
}

bool find(queue<int> q, int key)
{
    while (!q.empty())
    {
        int temp = q.front();
        if (temp == key)
        {
            return false;
        }
        q.pop();
    }
    return true;
}

void insert_in_q(int ct, vector<int> at, queue<int> &q, vector<int> bt)
{
    for (int i = 0; i < at.size(); i++)
    {
        if (at[i] <= ct && find(q, i) && bt[i] != 0)
        {
            q.push(i);
        }
    }
}

void round_robin(int n, vector<int> at, vector<int> bt)
{
    queue<int> q;

    vector<int> burst_time;

    burst_time = bt;

    int i = find_min(at);

    vector<int> ct(n, 0);

    int ref_ct;

    if (i != 0)
    {
        ref_ct = at[i];
    }
    else
    {
        ref_ct = 0;
    }

    q.push(i);

    int tq;
    cout << "Enter time quantum: ";
    cin >> tq;

    while (!q.empty())
    {
        i = q.front();
        if (tq <= bt[i])
        {
            bt[i] = bt[i] - tq;
            ref_ct += tq;
            insert_in_q(ref_ct, at, q, bt);
            q.pop();
            if (bt[i] != 0)
            {
                q.push(i);
            }
            else
            {
                ct[i] = ref_ct;
            }
        }
        else
        {
            ref_ct += bt[i];
            bt[i] = 0;
            ct[i] = ref_ct;
            insert_in_q(ref_ct, at, q, bt);
            q.pop();
        }
    }

    cout << "Completion times: " << endl;

    for (int i = 0; i < ct.size(); i++)
    {
        cout << ct[i] << " ";
    }
    cout << endl;

    vector<int> tat;
    vector<int> wt;

    for (int i = 0; i < n; i++)
    {
        int temp_tat = ct[i] - at[i];
        tat.emplace_back(temp_tat);
        int temp_wt = temp_tat - burst_time[i];
        wt.emplace_back(temp_wt);
    }

    cout << "Gantt Chart: " << endl;
    for (int i = 0; i < n; i++)
    {
        string temp = "P" + to_string(i + 1);
        string tr = to_string(ct[i]);

        string ans = "(" + temp + ", " + tr + "), ";
        cout << ans;
    }
    cout << endl;

    int sum = 0;
    int num;

    for (int i = 0; i < tat.size(); i++)
    {
        sum += tat[i];
    }

    num = tat.size();

    int sum1 = 0;

    for (int i = 0; i < wt.size(); i++)
    {
        sum1 += wt[i];
    }

    int num1 = wt.size();

    cout << "Final Result Table: \n";

    cout << "********************************************************************************************" << endl;
    cout << "| Process Id   ";
    cout << "| Arrival Time ";
    cout << "| Burst Time   ";
    cout << "| Completion   ";
    cout << "| Turn around  ";
    cout << "| waiting time |" << endl;
    cout << "********************************************************************************************" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "| p" << (i + 1) << "           ";
        cout << "| " << at[i] << "    ";
        cout << "| " << burst_time[i] << "      ";
        cout << "| " << ct[i] << "      ";
        cout << "| " << tat[i] << "      ";
        cout << "| " << wt[i] << "      ";
        cout << endl;
    }

    cout << "Average turn around time: " << sum / num << endl;
    cout << "Average waiting time: " << sum1 / num1 << endl;
}

void preemtive_priority(int n, vector<int> at, vector<int> bt, vector<int> pt)
{
    int ending = 0;
    int ref_ct = 0;

    vector<int> arrival_time;
    vector<int> burst_time;
    vector<int> priority_val;

    priority_val = pt;
    arrival_time = at;
    burst_time = bt;

    vector<int> ct(n, 0);

    for (int i = 0; i < bt.size(); i++)
    {
        ending += bt[i];
    }

    while (ref_ct != ending)
    {
        vector<int> ref_at;

        for (int i = 0; i < at.size(); i++)
        {
            if (at[i] <= ref_ct)
            {
                ref_at.emplace_back(i);
            }
        }

        int min = 0;

        for (int j = 0; j < ref_at.size(); j++)
        {
            if (pt[ref_at[j]] < pt[min])
            {
                min = ref_at[j];
            }
        }

        ref_ct += 1;
        bt[min] = bt[min] - 1;

        if (bt[min] == 0)
        {
            at[min] = INT_MAX;
            ct[min] = ref_ct;
            pt[min] = INT_MAX;
        }
    }

    cout << "Completion times: " << endl;

    for (int i = 0; i < ct.size(); i++)
    {
        cout << ct[i] << " ";
    }
    cout << endl;

    vector<int> tat;
    vector<int> wt;

    for (int i = 0; i < n; i++)
    {
        int temp_tat = ct[i] - arrival_time[i];
        tat.emplace_back(temp_tat);
        int temp_wt = temp_tat - burst_time[i];
        wt.emplace_back(temp_wt);
    }

    cout << "Gantt Chart: " << endl;
    for (int i = 0; i < n; i++)
    {
        string temp = "P" + to_string(i + 1);
        string tr = to_string(ct[i]);

        string ans = "(" + temp + ", " + tr + "), ";
        cout << ans;
    }
    cout << endl;

    int sum = 0;
    int num;

    for (int i = 0; i < tat.size(); i++)
    {
        sum += tat[i];
    }

    num = tat.size();

    int sum1 = 0;

    for (int i = 0; i < wt.size(); i++)
    {
        sum1 += wt[i];
    }

    int num1 = wt.size();

    cout << "Final Result Table: \n";

    cout << "********************************************************************************************" << endl;
    cout << "| Process Id   ";
    cout << "| Priority   ";
    cout << "| Arrival Time ";
    cout << "| Burst Time   ";
    cout << "| Completion   ";
    cout << "| Turn around  ";
    cout << "| waiting time |" << endl;
    cout << "********************************************************************************************" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "| p" << (i + 1) << "           ";
        cout << "| " << priority_val[i] << "    ";
        cout << "| " << arrival_time[i] << "    ";
        cout << "| " << burst_time[i] << "      ";
        cout << "| " << ct[i] << "      ";
        cout << "| " << tat[i] << "      ";
        cout << "| " << wt[i] << "      ";
        cout << endl;
    }

    cout << "Average turn around time: " << sum / num << endl;
    cout << "Average waiting time: " << sum1 / num1 << endl;
}

void preemtive_sjf(int n, vector<int> at, vector<int> bt)
{
    int ending = 0;
    int ref_ct = 0;

    vector<int> arrival_time;
    vector<int> burst_time;

    arrival_time = at;
    burst_time = bt;

    vector<int> ct(n, 0);

    for (int i = 0; i < bt.size(); i++)
    {
        ending += bt[i];
    }

    while (ref_ct != ending)
    {
        vector<int> ref_at;

        for (int i = 0; i < at.size(); i++)
        {
            if (at[i] <= ref_ct)
            {
                ref_at.emplace_back(i);
            }
        }

        int min = 0;

        for (int j = 0; j < ref_at.size(); j++)
        {
            if (bt[ref_at[j]] < bt[min])
            {
                min = ref_at[j];
            }
        }

        ref_ct += 1;
        bt[min] = bt[min] - 1;

        if (bt[min] == 0)
        {
            at[min] = INT_MAX;
            ct[min] = ref_ct;
            bt[min] = INT_MAX;
        }
    }

    cout << "Completion times: " << endl;

    for (int i = 0; i < ct.size(); i++)
    {
        cout << ct[i] << " ";
    }
    cout << endl;

    vector<int> tat;
    vector<int> wt;

    for (int i = 0; i < n; i++)
    {
        int temp_tat = ct[i] - arrival_time[i];
        tat.emplace_back(temp_tat);
        int temp_wt = temp_tat - burst_time[i];
        wt.emplace_back(temp_wt);
    }

    cout << "Gantt Chart: " << endl;
    for (int i = 0; i < n; i++)
    {
        string temp = "P" + to_string(i + 1);
        string tr = to_string(ct[i]);

        string ans = "(" + temp + ", " + tr + "), ";
        cout << ans;
    }
    cout << endl;

    int sum = 0;
    int num;

    for (int i = 0; i < tat.size(); i++)
    {
        sum += tat[i];
    }

    num = tat.size();

    int sum1 = 0;

    for (int i = 0; i < wt.size(); i++)
    {
        sum1 += wt[i];
    }

    int num1 = wt.size();

    cout << "Final Result Table: \n";

    cout << "********************************************************************************************" << endl;
    cout << "| Process Id   ";
    cout << "| Arrival Time ";
    cout << "| Burst Time   ";
    cout << "| Completion   ";
    cout << "| Turn around  ";
    cout << "| waiting time |" << endl;
    cout << "********************************************************************************************" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "| p" << (i + 1) << "           ";
        cout << "| " << arrival_time[i] << "    ";
        cout << "| " << burst_time[i] << "      ";
        cout << "| " << ct[i] << "      ";
        cout << "| " << tat[i] << "      ";
        cout << "| " << wt[i] << "      ";
        cout << endl;
    }

    cout << "Average turn around time: " << sum / num << endl;
    cout << "Average waiting time: " << sum1 / num1 << endl;
}

void non_preemtive_priority(int n, vector<int> at, vector<int> bt, vector<int> pt)
{
    int ending = 0;
    int ref_ct = 0;

    vector<int> arrival_time;
    vector<int> burst_time;
    vector<int> priority_val;

    priority_val = pt;
    arrival_time = at;
    burst_time = bt;

    vector<int> ct(n, 0);

    for (int i = 0; i < bt.size(); i++)
    {
        ending += bt[i];
    }

    while (ref_ct != ending)
    {
        vector<int> ref_at;

        for (int i = 0; i < at.size(); i++)
        {
            if (at[i] <= ref_ct)
            {
                ref_at.emplace_back(i);
            }
        }

        int min = 0;

        for (int j = 0; j < ref_at.size(); j++)
        {
            if (pt[ref_at[j]] < pt[min])
            {
                min = ref_at[j];
            }
        }

        ref_ct += bt[min];
        bt[min] = 0;

        if (bt[min] == 0)
        {
            at[min] = INT_MAX;
            ct[min] = ref_ct;
            pt[min] = INT_MAX;
        }
    }

    cout << "Completion times: " << endl;

    for (int i = 0; i < ct.size(); i++)
    {
        cout << ct[i] << " ";
    }
    cout << endl;

    vector<int> tat;
    vector<int> wt;

    for (int i = 0; i < n; i++)
    {
        int temp_tat = ct[i] - arrival_time[i];
        tat.emplace_back(temp_tat);
        int temp_wt = temp_tat - burst_time[i];
        wt.emplace_back(temp_wt);
    }

    cout << "Gantt Chart: " << endl;
    for (int i = 0; i < n; i++)
    {
        string temp = "P" + to_string(i + 1);
        string tr = to_string(ct[i]);

        string ans = "(" + temp + ", " + tr + "), ";
        cout << ans;
    }
    cout << endl;

    int sum = 0;
    int num;

    for (int i = 0; i < tat.size(); i++)
    {
        sum += tat[i];
    }

    num = tat.size();

    int sum1 = 0;

    for (int i = 0; i < wt.size(); i++)
    {
        sum1 += wt[i];
    }

    int num1 = wt.size();

    cout << "Final Result Table: \n";

    cout << "********************************************************************************************" << endl;
    cout << "| Process Id   ";
    cout << "| Priority   ";
    cout << "| Arrival Time ";
    cout << "| Burst Time   ";
    cout << "| Completion   ";
    cout << "| Turn around  ";
    cout << "| waiting time |" << endl;
    cout << "********************************************************************************************" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "| p" << (i + 1) << "           ";
        cout << "| " << priority_val[i] << "    ";
        cout << "| " << arrival_time[i] << "    ";
        cout << "| " << burst_time[i] << "      ";
        cout << "| " << ct[i] << "      ";
        cout << "| " << tat[i] << "      ";
        cout << "| " << wt[i] << "      ";
        cout << endl;
    }

    cout << "Average turn around time: " << sum / num << endl;
    cout << "Average waiting time: " << sum1 / num1 << endl;
}

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    string priority;
    cout << "Enter Yes if priority else No: ";
    cin >> priority;

    while (true)
    {
        if (priority == "Yes" || priority == "No")
        {
            break;
        }
        cout << "Enter correct choice: ";
        cin >> priority;
    }

    vector<int> arrival_time;
    vector<int> burst_time;
    vector<int> priority_val;

    insert_values(n, arrival_time, burst_time, priority_val, priority);

    if (priority == "Yes")
    {
        display_init(n, arrival_time, burst_time, priority_val, priority);
    }
    else
    {
        display_init(n, arrival_time, burst_time);
    }

    string valid;
    cout << "If correct enter Yes else No: " << endl;
    cin >> valid;
    vector<int> ctp;

    while (true)
    {
        if (valid == "Yes")
        {
            break;
        }
        else if (valid == "No")
        {
            arrival_time.clear();
            burst_time.clear();
            priority_val.clear();
            insert_values(n, arrival_time, burst_time, priority_val, priority);
            if (priority == "Yes")
            {
                display_init(n, arrival_time, burst_time, priority_val, priority);
            }
            else
            {
                display_init(n, arrival_time, burst_time);
            }
            cout << "Enter correct choice: ";
            cin >> valid;
        }
        else
        {
            cout << "Enter correct choice: ";
            cin >> valid;
        }
    }

    int choice;
    bool flag = true;

    while (flag)
    {
        if (priority == "Yes")
        {
            cout << "Select which algorithm to use: " << endl;
            cout << "1.Priority\n";
            cout << "2.Priority SJF\n";
            cout << "3.Preemptive Priority\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                cout << "Non- Preemptive Priority selected \n ";
                non_preemtive_priority(n, arrival_time, burst_time, priority_val);
                flag = false;
                break;
            case 3:
                cout << "Preemptive Priority selected \n";
                preemtive_priority(n, arrival_time, burst_time, priority_val);
                flag = false;
                break;
            default:
                cout << "Please enter correct choice \n";
            }
        }
        else
        {
            cout << "Select which algorithm to use: " << endl;
            cout << "1.FCFS\n";
            cout << "2.SJF\n";
            cout << "3.Preemptive SJF\n";
            cout << "4.Round Robin\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                cout << "FCFS selected \n ";
                fcfs(n, arrival_time, burst_time);
                flag = false;
                break;
            case 2:
                cout << "SJF selected \n";
                sjf(n, arrival_time, burst_time);
                flag = false;
                break;
            case 3:
                cout << "Preemptive SJF selected \n";
                preemtive_sjf(n, arrival_time, burst_time);
                flag = false;
                break;
            case 4:
                cout << "Round Robin selected \n";
                round_robin(n, arrival_time, burst_time);
                flag = false;
                break;
            default:
                cout << "Please enter correct choice \n";
            }
        }
    }

    return 0;
}