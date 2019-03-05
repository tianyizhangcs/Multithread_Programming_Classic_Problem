/* compile: g++ -o main main.cpp
 * execute: ./main
 * Name : Tianyi Zhang
 * File: main.cpp main
 */
#include <iostream>
#include <vector>
#include <algorithm>
#define  PAGE_FRAME 4
int dis_opt(int cur, int x, std::vector<int> v){
    int dis=0;
    for(auto it=cur+1;it!=v.size();it++){
        if(x!=v[it]){dis++;}
        else return dis;
    }
    return dis;
}
int max_dis_opt(int cur, std::vector<int> opt,std::vector<int> v){
    int maxdis, max;
    for(auto it=0;it!=opt.size();++it){
        if(dis_opt(cur,opt[it],v)>=maxdis) {maxdis=dis_opt(cur,opt[it],v);max=it;}
    }
    return max;
}

int dis_lru(int cur, int x, std::vector<int> v){
    int dis=0;
    for(auto it = cur-1; it!=-1;it--){
        if(x!=v[it]){dis++;}
        else return dis;
    }
    return dis;
}

int max_dis_lru(int cur, std::vector<int> lru, std::vector<int> v){
    int maxdis, max;
    for(auto it=0;it!=lru.size();++it){
        if(dis_lru(cur,lru[it],v)>=maxdis){maxdis=dis_lru(cur,lru[it],v); max=it;}
    }
    return max;
}

int main() {
    int page_fault_FIFO, page_fault_OPT,page_fault_LRU;
    std::vector<int> pr={0, 1, 2, 3, 2, 4, 5, 2, 4, 1, 6, 3, 7, 8, 3, 8, 4, 9, 7, 8, 1, 2, 9, 6, 4, 5, 0, 2, 5, 1, 9};
    std::vector<int> fifo, opt,lru;
    std::cout<<"Using FIFO: \n";
    for(auto it=0;it!=pr.size();++it){
        auto found=std::find(fifo.begin(),fifo.end(),pr[it]);
        if(found!=fifo.end()) std::cout<<pr[it]<<" is not a page fault\n";
        else if(fifo.size()<PAGE_FRAME){ page_fault_FIFO++; fifo.push_back(pr[it]);std::cout<<pr[it]<<" is a page fault, fill in\n";}
        else {std::cout<<pr[it]<<" is a page fault, replacing "<<fifo[page_fault_FIFO%PAGE_FRAME]<<std::endl;
            fifo[page_fault_FIFO%PAGE_FRAME]=pr[it];
            page_fault_FIFO++;}
    }
    std::cout<<"FIFO number of page fault: "<<page_fault_FIFO<<std::endl;
    std::cout<<std::endl;

    std::cout<<"Using OPT: \n";
    for(auto it=0;it!=pr.size();++it){
        auto found=std::find(opt.begin(),opt.end(),pr[it]);
        if(found!=opt.end()) std::cout<<pr[it]<<" is not a page fault\n";
        else if(opt.size()<PAGE_FRAME){page_fault_OPT++;opt.push_back(pr[it]);std::cout<<pr[it]<<" is a page fault, fill in\n";}
        else {
            std::cout<<pr[it]<<" is a page fault, replacing "<<opt[max_dis_opt(it,opt,pr)]<<std::endl;
            opt[max_dis_opt(it,opt,pr)]=pr[it];
            page_fault_OPT++;
            }
    }
    std::cout<<"OPT number of page fault: "<<page_fault_OPT<<std::endl;
    std::cout<<std::endl;

    std::cout<<"Using LRU: \n";
    for(auto it=0;it!=pr.size();++it){
        if(it == 7 )
        {
            int a=9;
        }
        auto found=std::find(lru.begin(),lru.end(),pr[it]);
        if(found!=lru.end()) std::cout<<pr[it]<<" is not a page fault\n";
        else if(lru.size()<PAGE_FRAME){page_fault_LRU++;lru.push_back(pr[it]);std::cout<<pr[it]<<" is a page fault, fill in\n";}
        else {
            std::cout<<pr[it]<<" is a page fault, replacing "<<lru[max_dis_lru(it,lru,pr)]<<std::endl;
            lru[max_dis_lru(it,lru,pr)]=pr[it];
            page_fault_LRU++;}
    }
    std::cout<<"LRU number of page fault:"<<page_fault_LRU<<std::endl;
    return 0;
}