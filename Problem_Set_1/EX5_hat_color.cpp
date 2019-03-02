#include <iostream>
#include <vector>
#include <algorithm>
#define NUM_PRISONERS 100
#define RED 0
#define BLUE 1
int main(){
    std::vector<int> hat_color;
    std::vector<int> hat_color_guess;
    for(int i=0; i<NUM_PRISONERS; i++){
        hat_color.push_back(rand()%2);
    }
    //first prisoner, count the hat in front of him, if Red is odd, then predict his as RED.
    int count = 0;
    for(auto i = hat_color.begin()+1; i!= hat_color.end(); i++){
        if(*i == RED) count++;
    }
    if(count%2==0)
        hat_color_guess.push_back(RED);
    else
        hat_color_guess.push_back(BLUE);

    //other prisoners, remember previous red hat num, count the number of red hat in front,  make decision based on the first person's predict.
    if(*hat_color_guess.begin()==RED){
        for(int i = 1; i <NUM_PRISONERS; i++){
            int count_red = 0;
            for(auto j = hat_color.begin()+1; j!=hat_color.end(); j++){
                if(*j == RED) count_red++;
            }
            for(auto k = hat_color_guess.begin()+1; k!=hat_color_guess.end(); k++){
                if(*k == RED) count_red++;
            }
            if(count_red%2 == 0) hat_color_guess.push_back(BLUE);
            else
                hat_color_guess.push_back(RED);
        }
    }

    if(*hat_color_guess.begin()==BLUE){
        for(int i = 1; i <NUM_PRISONERS; i++){
            int count_red = 0;
            for(auto j = hat_color.begin()+i+1; j!=hat_color.end(); j++){
                if(*j == RED) count_red++;
            }
            for(auto k = hat_color_guess.begin()+1; k!=hat_color_guess.end(); k++){
                if(*k == RED) count_red++;
            }
            if(count_red%2 == 0) hat_color_guess.push_back(RED);
            else
                hat_color_guess.push_back(BLUE);
        }
    }

        //print out predicted and true color
    for(auto i=hat_color.begin(); i!=hat_color.end(); i++)
        std::cout<<*i<<" ";
    std::cout<<std::endl;

    for(auto i=hat_color_guess.begin(); i!=hat_color_guess.end(); i++)
        std::cout<<*i<<" ";
    std::cout<<std::endl;

        // test if it is correct or not.
    if(std::equal(hat_color_guess.begin()+1, hat_color_guess.end(), hat_color.begin()+1)){
        std::cout<<"At least "<<NUM_PRISONERS-1<<" survives !"<<std::endl;
    }
    return 0;
}