#include<bits/stdc++.h>
using namespace std;

class VersionedStore {
	
private:
	
	int globalVersion = 1;
	
	struct Value {
		int value;
		int version;	
	};
	
	map<string,vector<Value> > _map;

	// Custom comparator for Value struct.
	static bool valueComparator(Value x, Value y) {
		return x.version < y.version;
	}
	
public:
	
	int getVersion() {
		return (this->globalVersion)-1; 
	}
	void put(string key, int value) {
		_map[key].push_back(Value{value, globalVersion}); 
		globalVersion++; // increment the global version
	}
	
	int get(string key) {
		if(_map[key].size()>0) {
			int _n = _map[key].size();
			return _map[key][_n-1].value;
		} 
		return INT_MIN;
	}
	
	int getForVersion(string key, int version) {
		if(_map[key].size()>0) {
			vector<Value> V = _map[key];
			vector<Value>::iterator it = lower_bound(V.begin(),V.end(), Value{0,version}, valueComparator);
			if(it->version == version) {
				return it->value;
			} else { 
				it--;
				if(it>=V.begin())
					return it->value;
				return get(key);
			}
		} 
		return INT_MIN;
	}
};

void process(VersionedStore& store,string queryType, string queryKey, int value) {
	if(queryType == "PUT") {
		store.put(queryKey,value);
		int version = store.getVersion();
		cout<<"PUT(#"<<version<<") "<<queryKey<<" = "<<value<<endl;
	} else {
		if(value == -1) {
			int res = store.get(queryKey);
			if(res!=INT_MIN)
				cout<<"GET "<<queryKey<<" = "<<res<<endl; 
			else 
				cout<<"GET "<<queryKey<<" = "<<"<NULL>"<<endl;
		} else {
			int res = store.getForVersion(queryKey, value);
			if(res!=INT_MIN)
				cout<<"GET "<<queryKey<<"(#"<<value<<")"<<" = "<<res<<endl; 
			else 
				cout<<"GET "<<queryKey<<"(#"<<value<<")"<<" = "<<"<NULL>"<<endl;
		}
	}
}

int main() {
	VersionedStore store;
	
	string query, queryType, queryKey;
	int value; // for GET query this var will act as version
	
	while(getline(cin, query)) {
		stringstream ss(query);
		value = -1;
		if(ss>>queryType) {}
		if(ss>>queryKey) {}
		if(ss>>value) {}
		process(store,queryType,queryKey,value);
	}
	
	return 0;
}