#include "../include/Markdown_parser.h"

using namespace mpt;

int Markdown_parser::Lexical_analysis(deque <deque <string>> ready_convety){
    convert_arr = ready_convety;
    int bit = 0;
    for (int i = 0; i < ready_convety.size(); i++){
        for (int j = 0; j < ready_convety[i].size(); j++){
            for (int k = 0; k < ready_convety[i][j].size(); k++){
                if (ready_convety[i][k][0] == '#'){
                    for (int n = 0; n < ready_convety[i][j].size(); n++){
                            if(ready_convety[i][k][n]!='#'){
                                title_num = n;
                                bit = 1;
                                state.push_back(bit);
                        }
                    }                    
                }
                else if (ready_convety[i][k][0] == '*'){
                    for (int n = 0; n < ready_convety[i][j].size(); n++){
                            if(ready_convety[i][k][n]!='*'){
                                strong_num = n;
                                if (strong_num == 3){
                                    bit = 3;
                                }
                                else if(strong_num == 1){
                                    bit = 4;
                                }
                                else if (strong_num == 2){
                                    bit = 2;
                                }
                                else{
                                    break;
                                }
                                state.push_back(bit);
                        }
                    } 
                }
                else if(ready_convety[i][k][0] == '>'){
                    state.push_back(bit);
                }
                else if(ready_convety[i][k][0] == '-'){
                    state.push_back(bit);
                }
                else if(ready_convety[i][k][0] == '`'){
                    for (int n = 0; n < ready_convety[i][k].size(); n++){
                        if (ready_convety[i][k][n] == '`'){
                            code_num++;
                        }
                        else if(code_num==3){
                            state.push_back(bit);
                        }
                        else{
                            continue;
                        }
                    }
                }
                else if(ready_convety[i][k][0] == '['){
                    state.push_back(bit);
                }
                else if(ready_convety[i][k][0] == '!'&&ready_convety[i][k][1] == '['){
                    state.push_back(bit);
                }
                else{
                    continue;
                }
            }
        }
    }
    return 0;
}

deque <deque <string>> Markdown_parser::syntax_conversion(int state_bit,deque <deque <string> > ready_convety){
    for (int i = 0; i < state.size(); i++){
        state_bit = state[i];
        switch (state_bit){
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        default:
            break;
        } 
    }
    return ready_convety;
}