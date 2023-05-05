#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct task{  int  task_id;
  /* alphabetic tid can be obtained as 'A'+(task_counter++) */
int arrival_time;
int service_time;
int remaining_time;
int completion_time;
int response_time;
int wait_time;
};

int main(int argc, char* argv[]){

  vector<task> buffer;
  string input;
  int loops = 0;
  while(getline(cin,input)){
    stringstream stream(input);
    int first;
    int second;
    stream >> first >> second;
    task next;
    next.arrival_time = first;
    next.service_time = second;
    next.task_id = 'A' + loops;
    next.wait_time = 0;
    buffer.push_back(next);
    loops++;
  }


  string choice = argv[1];
  vector<task> cpu;
  vector<task> ready;
  vector<task> completed;
  if(choice.compare("-fifo") == 0){

    cout << "FIFO scheduling results\n";
    cout << "time\tcpu\tready\tqueue\t(tid/rst)\n";
    cout << "----------------------------------\n";
    int time = 0;
    while(!buffer.empty() || !cpu.empty() || !ready.empty()){
        cout << time << "\t";
        int size = buffer.size();
        for(int i = 0; i < size; i++){
          if(buffer[i].arrival_time == time){
            ready.push_back(buffer[i]);
            buffer.erase(buffer.begin());
            i--;
            size--;
          }
          if(buffer[i].arrival_time > time){
            break;
          }
        }
        if(cpu.empty() && !ready.empty()){
          cpu.push_back(ready[0]);
          ready.erase(ready.begin());

        }

        if(cpu.empty()){
          cout << "\t";
        } else {
          cout << (char)cpu[0].task_id << cpu[0].service_time << "\t";
          cpu[0].service_time = cpu[0].service_time - 1;
          if(cpu[0].service_time == 0){
            cpu[0].completion_time = time + 1;
            completed.push_back(cpu[0]);
            cpu.erase(cpu.begin());
          }
        }

        if(ready.empty()){
          cout << "--\n";
        } else {
          for(int i = 0; i < ready.size(); i++){
            cout << (char)ready[i].task_id << ready[i].service_time;
            if(i+1 < ready.size()){
              cout << ", ";
            }
            ready[i].wait_time = ready[i].wait_time + 1;
          }
          cout << endl;
        }


        time++;
    }

    cout << endl;

    for(int i = 0; i < completed.size(); i++){
      for(int j = 0; j < completed.size(); j++){
        if(j+1 < completed.size()){
          if(completed[j].task_id > completed[j+1].task_id){
            task temp = completed[j];
            completed[j] = completed[j+1];
            completed[j+1] = temp;
          }
        }
      }
    }

    cout << "\tarrival\tservice\tcompletion\tresponse\twait\n";
    cout << "tid\ttime\ttime\ttime\t\ttime\t\ttime\n";
    cout << "---------------------------------------------\n";
    for(int i = 0; i < completed.size(); i++){
        int service = completed[i].completion_time - completed[i].arrival_time - completed[i].wait_time;
        completed[i].service_time = service;
        completed[i].response_time = completed[i].service_time + completed[i].wait_time;
    }

    for(int i = 0; i < completed.size(); i++){
        cout << (char)completed[i].task_id << "\t" << completed[i].arrival_time
        << "\t" << completed[i].service_time << "\t" << completed[i].completion_time
        << "\t\t" << completed[i].response_time << "\t\t" << completed[i].wait_time << endl;
    }

    cout << "\n";
    cout << "service\twait\n";
    cout << "time\ttime\n";
    cout << "------------\n";
    for(int i = completed.size(); i > 0 ; i--){
      cout << completed[i-1].service_time << "\t" << completed[i-1].wait_time << endl;
    }

  } else if(choice.compare("-sjf") == 0){
    cout << "SJF(preemptive) scheduling results\n";
    cout << "time\tcpu\tready\tqueue\t(tid/rst)\n";
    cout << "----------------------------------\n";
    int time = 0;
    while(!buffer.empty() || !cpu.empty() || !ready.empty()){
        cout << time << "\t";
        int size = buffer.size();
        for(int i = 0; i < size; i++){
          if(buffer[i].arrival_time == time){
            ready.push_back(buffer[i]);
            buffer.erase(buffer.begin());
            i--;
            size--;
          }
          if(buffer[i].arrival_time > time){
            break;
          }
        }
        if(!ready.empty()){
          for(int i = 0; i < ready.size(); i++){
            for(int j = 0; j < ready.size(); j++){
              if(j+1 < ready.size()){
                if(ready[j].service_time > ready[j+1].service_time){
                  task temp = ready[j];
                  ready[j] = ready[j+1];
                  ready[j+1] = temp;
                }
              }
            }
          }
        }

        if(cpu.empty() && !ready.empty()){
          cpu.push_back(ready[0]);
          ready.erase(ready.begin());

        }

        if(cpu.empty()){
          cout << "\t";
        } else {
          cout << (char)cpu[0].task_id << cpu[0].service_time << "\t";
          cpu[0].service_time = cpu[0].service_time - 1;
          if(cpu[0].service_time == 0){
            cpu[0].completion_time = time + 1;
            completed.push_back(cpu[0]);
            cpu.erase(cpu.begin());
          }
        }

        if(ready.empty()){
          cout << "--\n";
        } else {
          for(int i = 0; i < ready.size(); i++){
            cout << (char)ready[i].task_id << ready[i].service_time;
            if(i+1 < ready.size()){
              cout << ", ";
            }
            ready[i].wait_time = ready[i].wait_time + 1;
          }
          cout << endl;
        }


        time++;
    }

    for(int i = 0; i < completed.size(); i++){
      for(int j = 0; j < completed.size(); j++){
        if(j+1 < completed.size()){
          if(completed[j].task_id > completed[j+1].task_id){
            task temp = completed[j];
            completed[j] = completed[j+1];
            completed[j+1] = temp;
          }
        }
      }
    }
    cout << endl;
    cout << "\tarrival\tservice\tcompletion\tresponse\twait\n";
    cout << "tid\ttime\ttime\ttime\t\ttime\t\ttime\n";
    cout << "---------------------------------------------\n";
    for(int i = 0; i < completed.size(); i++){
        int service = completed[i].completion_time - completed[i].arrival_time - completed[i].wait_time;
        completed[i].service_time = service;
        completed[i].response_time = completed[i].service_time + completed[i].wait_time;
    }

    for(int i = 0; i < completed.size(); i++){
        cout << (char)completed[i].task_id << "\t" << completed[i].arrival_time
        << "\t" << completed[i].service_time << "\t" << completed[i].completion_time
        << "\t\t" << completed[i].response_time << "\t\t" << completed[i].wait_time << endl;
    }

    vector<task> inorder = completed;

    for(int i = 0; i < inorder.size(); i++){
      for(int j = 0; j < inorder.size(); j++){
        if(j+1 < inorder.size()){
          if(inorder[j].service_time == inorder[j+1].service_time){
            if(inorder[j].wait_time < inorder[j+1].wait_time){
              task temp = inorder[j];
              inorder[j] = inorder[j+1];
              inorder[j+1] = temp;
            }
          }
        }
      }
    }

    cout << "\n";
    cout << "service\twait\n";
    cout << "time\ttime\n";
    cout << "------------\n";
    for(int i = inorder.size(); i > 0 ; i--){
      cout << inorder[i-1].service_time << "\t" << inorder[i-1].wait_time << endl;
    }

  } else if (choice.compare("-rr") == 0){
    cout << "RR scheduling results (time slice is 1)\n";
    cout << "time\tcpu\tready\tqueue\t(tid/rst)\n";
    cout << "----------------------------------\n";
    int time = 0;
    while(!buffer.empty() || !cpu.empty() || !ready.empty()){
        cout << time << "\t";
        int size = buffer.size();
        for(int i = 0; i < size; i++){
          if(buffer[i].arrival_time == time){
            ready.push_back(buffer[i]);
            buffer.erase(buffer.begin());
            i--;
            size--;
          }
          if(buffer[i].arrival_time > time){
            break;
          }
        }

        if(!cpu.empty() && !ready.empty()){
          ready.push_back(cpu[0]);
          cpu[0] = ready[0];
          ready.erase(ready.begin());
        }

        if(cpu.empty() && !ready.empty()){
          cpu.push_back(ready[0]);
          ready.erase(ready.begin());

        }



        if(cpu.empty()){
          cout << "\t";
        } else {
          cout << (char)cpu[0].task_id << cpu[0].service_time << "\t";
          cpu[0].service_time = cpu[0].service_time - 1;
          if(cpu[0].service_time == 0){
            cpu[0].completion_time = time + 1;
            completed.push_back(cpu[0]);
            cpu.erase(cpu.begin());
          }
        }

        if(ready.empty()){
          cout << "--\n";
        } else {
          for(int i = 0; i < ready.size(); i++){
            cout << (char)ready[i].task_id << ready[i].service_time;
            if(i+1 < ready.size()){
              cout << ", ";
            }
            ready[i].wait_time = ready[i].wait_time + 1;
          }
          cout << endl;
        }



        time++;
    }

    for(int i = 0; i < completed.size(); i++){
      for(int j = 0; j < completed.size(); j++){
        if(j+1 < completed.size()){
          if(completed[j].task_id > completed[j+1].task_id){
            task temp = completed[j];
            completed[j] = completed[j+1];
            completed[j+1] = temp;
          }
        }
      }
    }
    cout << endl;
    cout << "\tarrival\tservice\tcompletion\tresponse\twait\n";
    cout << "tid\ttime\ttime\ttime\t\ttime\t\ttime\n";
    cout << "---------------------------------------------\n";
    for(int i = 0; i < completed.size(); i++){
        int service = completed[i].completion_time - completed[i].arrival_time - completed[i].wait_time;
        completed[i].service_time = service;
        completed[i].response_time = completed[i].service_time + completed[i].wait_time;
    }

    for(int i = 0; i < completed.size(); i++){
        cout << (char)completed[i].task_id << "\t" << completed[i].arrival_time
        << "\t" << completed[i].service_time << "\t" << completed[i].completion_time
        << "\t\t" << completed[i].response_time << "\t\t" << completed[i].wait_time << endl;
    }

    vector<task> inorder = completed;

    for(int i = 0; i < inorder.size(); i++){
      for(int j = 0; j < inorder.size(); j++){
        if(j+1 < inorder.size()){
          if(inorder[j].service_time == inorder[j+1].service_time){
            if(inorder[j].wait_time < inorder[j+1].wait_time){
              task temp = inorder[j];
              inorder[j] = inorder[j+1];
              inorder[j+1] = temp;
            }
          }
        }
      }
    }

    cout << "\n";
    cout << "service\twait\n";
    cout << "time\ttime\n";
    cout << "------------\n";
    for(int i = inorder.size(); i > 0 ; i--){
      cout << inorder[i-1].service_time << "\t" << inorder[i-1].wait_time << endl;
    }
  }
}
