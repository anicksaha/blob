#include<bits/stdc++.h>
using namespace std;

struct Job {
	int startTime;
	int endTime;
	int jobId;
	int workerId;	
	bool operator<(const Job &X) const { 
        return endTime>X.endTime;
    }
};

bool comp(Job X, Job Y) { 
	return X.startTime<Y.startTime;
}

int main() {
	
	int N, start, duration, end;
	cin>>N;
	vector<Job> jobs;
	
	for(int i=0;i<N;i++) {
		cin>>start>>duration;
		int H, M;
		H = start/100; M = start%100;
		M+=duration; H+=(M/60); M =(M%60);
		end = (H*100) + M;
		jobs.push_back(Job{start,end,i});
	}
	
	sort(jobs.begin(),jobs.end(),comp); // sort by start time
	
	int ans = 0;
	int ctr = 0;
	
	set<int>::iterator it;
	set<int> freeWorkers;
	
	// set some dummyworkers;
	for(int i=0;i<N;i++) freeWorkers.insert(i);
	
	priority_queue<Job> activeJobs;
	vector<pair<int, int> > ANS;
	int _maxWorkerId = INT_MIN;
	
	for(int i=0;i<N;i++) {
		Job curr = jobs[i];
		
		while(!activeJobs.empty()) {
			Job x = activeJobs.top();
			if(curr.startTime>=x.endTime) {
				activeJobs.pop();
				freeWorkers.insert(x.workerId);
			} else {
				break;
			}
		}
		
		// pick the lowest index one from the free workers.
		curr.workerId = *(freeWorkers.begin());
		freeWorkers.erase(curr.workerId);
		_maxWorkerId = max(_maxWorkerId, curr.workerId);
		activeJobs.push(curr);
		ANS.push_back(make_pair(curr.jobId,curr.workerId));
	}
	
	// Max workers required
	cout<<_maxWorkerId+1<<endl;
	
	sort(ANS.begin(), ANS.end());
	for(int i=0;i<N;i++)
		cout<<"J"<<ANS[i].first<<" W"<<ANS[i].second<<endl;
	return 0;
}