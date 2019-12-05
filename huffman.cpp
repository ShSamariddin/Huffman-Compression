#include "huffman.h"
#include<iostream>
#include<cstring>
#include<queue>
#include<memory>
#include<vector>
#include<algorithm>
#include<cstdio>

void HufType::add(const uint8_t* a, size_t si){
    for(size_t i = 0; i < si; i ++){
        cnt[a[i]]++;
    }
}

HufType::HufType(std::vector<std::pair<uint8_t, int>> const& tree){

    for(size_t i = 0; i < tree.size(); i ++){
        if(cnt[tree[i].first] != 0 || tree[i].second == 0)
            throw std::runtime_error("asdasd");
        cnt[(tree[i].first)] = tree[i].second;
    }
}

HufType::HufType(){

}

std::vector<std::pair<uint8_t, int> > HufType::info(){
    std::vector<std::pair<uint8_t, int> > res;
    for(int i = 0; i < len; i ++){
        if(cnt[i]){
            res.push_back({(uint8_t)i, cnt[i]});
        }
    }
    return res;
}
Huffman::Huffman(){

}

Huffman::Huffman(HufType rhs)
{

    std::priority_queue <std::pair<int, unsigned int> > st;
    for(int i = 0; i < len; i ++){
        if(rhs.cnt[i]){
            leftson[i] = -1;
            rightson[i] = -1;
            st.push({-rhs.cnt[i], i});
        }
    }
    symbolsize = len;
    if(st.size() == 1){
        std::pair<int,  int> fir = st.top();
        isrightson[fir.second] = true;
        parent[fir.second] = symbolsize;
        rightson[symbolsize] = fir.second;
        symbolsize++;
    }
    while(st.size() > 1){
        std::pair<int,  int> fir = st.top();
        st.pop();
        std::pair<int,  int> sec = st.top();
        st.pop();
        leftson[symbolsize] = fir.second;
        rightson[symbolsize] = sec.second;
        parent[fir.second] = parent[sec.second] = symbolsize;
        isrightson[sec.second] = true;
        isrightson[fir.second] = false;
        st.push({fir.first + sec.first,  symbolsize});
        symbolsize++;
    }
    symbolsize--;
}

std::pair<std::vector<uint8_t>, int> Huffman::encod(const uint8_t* a, size_t si){
    std::vector<uint8_t> res;
    uint8_t val = 0;
    int cnt = 0;
    for(size_t i = 0; i < si; i ++){
        int pos = a[i];
        while(pos != symbolsize){
            val <<= 1;
            val = val + (int) (isrightson[pos]);
            cnt++;
            if(cnt == 8){
                res.push_back(val);
                cnt = val = 0;
            }
            pos = parent[pos];
        }
    }

    int res_si = res.size() * 8 + cnt;
    if(cnt != 0){
        val <<= (8 - cnt);
        res.push_back(val);
    }
    return {res, res_si};
}


std::vector<uint8_t> Huffman::decod(const uint8_t* a, size_t si, int needbit){

       std::vector<uint8_t> ans;
       int pos = symbolsize;

       if(si != 0){
           uint8_t t = a[si - 1];
           t >>= needbit;
           int li = 8 - needbit;
           while(li != 0){
               if(t % 2 == 1){
                   pos = rightson[pos];
               } else{
                   pos = leftson[pos];
               }
               if(pos < 256){
                   ans.push_back(pos);
                   pos = symbolsize;
               }
               t /= 2;
               li--;
           }
       }
       for(int i = si - 2; i >= 0; i --){
           uint8_t t = a[i];
           int li = 8;
           while(li != 0){
                if(t % 2 == 1){
                   pos = rightson[pos];
                } else{
                   pos = leftson[pos];
                }
                if(pos < 256){
                    ans.push_back(pos);
                    pos = symbolsize;
                }
               t /= 2;
               li--;
           }
       }
       reverse(ans.begin(), ans.end());
     return ans;
}
