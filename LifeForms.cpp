#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

class index_rank {
public:
    int index, pre, lat;
};

class lcp_class {
public:
    int len, pre, lat;
};

bool mycomp (index_rank i, index_rank j) {
    if (i.pre == j.pre)
        return (i.lat < j.lat);
    else
        return (i.pre < j.pre);
}

void build_sa (vector<int> &sa, string &str);
void build_height (vector<int> &sa, vector<lcp_class> &height, string &str);
bool is_height(vector<lcp_class> &height, int len, int num);
void print_height(vector<int> &sa, vector<lcp_class> &height, int len, int num, string &str);

int main () {
    int n;
    int is_space = 0;

    while (cin >> n && n) {
        int x = -127;
        if (n == 1){
            string out;
            cin >> out;
            cout << out << endl << endl;
            continue;
        }

        string str;
        for (int i = 0; i < n; i++){
            string s;
            cin >> s;
            s += x;
            str += s;
            x++;                        //change the delimiter
        }
        str.back() = -128;              // the last character should be the smallest

        vector<int> sa (str.size());
        build_sa(sa, str);

        vector<lcp_class> height (str.size());
        build_height(sa, height, str);

        int low, res, mid;
        int high = int(str.size());
        low = res = 0;
        while (low <= high){
            mid = (low + high) / 2;
            if (is_height(height, mid, n)){
                res = mid;
                low = mid + 1;
            } else
                high = mid - 1;
        }

        if (is_space)
            cout << endl;
        if (res == 0)
            cout << "?" << endl;
        else
            print_height(sa, height, res, n, str);
        is_space = 1;

    }
}

void build_sa (vector<int> &sa, string &str){
    vector<int> index (str.size());
    vector<index_rank> rank (str.size());

    for (int i = 0; i < str.size(); i++){
        rank[i].index = i;
        rank[i].pre = rank[i].lat = int(str[i]);
    }

    for (int i = 1; i < str.size(); i*=2){
        sort(rank.begin(), rank.end(), mycomp);
        int nutch = 0;
        index[rank[0].index] = 0;
        for (int j = 1; j < rank.size(); j++) {
            if (rank[j].pre != rank[j-1].pre || rank[j].lat != rank[j-1].lat)
                nutch++;
            index[rank[j].index] = nutch;
        }

        for (int j = 0; j < rank.size(); j++){
            rank[j].pre = index[rank[j].index];
            if (rank[j].index+i < index.size())
                rank[j].lat = index[rank[j].index+i];
            else
                rank[j].lat = -128;
        }
        //
//        for (int k = 0; k < sa.size(); k++)
//            cout << "(" << rank[k].pre << "," <<rank[k].lat << ")" << " ";
//        cout << endl << "-----------" << endl;
        //
    }

    sort(rank.begin(), rank.end(), mycomp);
    for (int i = 0; i < sa.size(); i++){
        sa[i] = rank[i].index;
    }

}


void build_height (vector<int> &sa, vector<lcp_class> &height, string &str){
    for (int i = 1; i < height.size(); i++){
        height[i].len = height[i].pre = height[i].lat = 0;
        int pre = sa[i], lat = sa[i-1];
        while (str[pre++] == str[lat++])
            height[i].len++;
        pre--;
        while (str[pre++] > 0)
            ;
        height[i].pre = str[--pre];
        lat--;
        while (str[lat++] > 0)
            ;
        height[i].lat = str[--lat];
    }

}


bool is_height(vector<lcp_class> &height, int len, int num){
    set<int> forms;

    for (int i = 1; i < height.size(); i++){
        if (height[i].len >= len){
            forms.insert(height[i].pre);
            forms.insert(height[i].lat);
            if (2*forms.size() > num)
                return true;
        } else
            forms.clear();
    }

    return false;
}


void print_height(vector<int> &sa, vector<lcp_class> &height, int len, int num, string &str){
    set<int> forms;
    int is_print = 0;

    for (int i = 1; i < height.size(); i++){
        if (height[i].len >= len){
            forms.insert(height[i].pre);
            forms.insert(height[i].lat);
            if (2*forms.size() > num && !is_print){
                cout << str.substr((unsigned int)sa[i], (unsigned int)len) << endl;
                is_print = 1;
            }
        } else{
            is_print = 0;
            forms.clear();
        }
    }
}