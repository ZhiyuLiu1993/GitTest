#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <iostream>

std::map<std::string, std::vector<std::string>> computeAdjacentWords(const std::vector<std::string> &words) {
    std::map<std::string, std::vector<std::string>> adjMap;
    std::map<int, std::vector<std::string>> wordsByLength;
    for (int i = 0; i < words.size(); ++i)
        wordsByLength[words[i].size()].push_back(words[i]);
    std::map<int, std::vector<std::string>>::const_iterator itr;
    for (itr = wordsByLength.begin(); itr != wordsByLength.end(); ++itr) {
        const std::vector<std::string> &groupsWords = (*itr).second;
        int groupNum = (*itr).first;
        for (int j = 0; j < groupNum; ++j) {
            std::map<std::string, std::vector<std::string>> repToWords;
            for (int k = 0; k < groupsWords.size(); ++k) {
                std::string rep = groupsWords[k];
                rep.erase(j, 1);
                repToWords[rep].push_back(groupsWords[k]);
            }
            std::map<std::string, std::vector<std::string>>::const_iterator itr2;
            for(itr2 = repToWords.begin(); itr2 != repToWords.end(); itr2++){
                const std::vector<std::string> clique = (*itr2).second; //& ???不行
                if(clique.size() > 1){
                    for (int l = 0; l < clique.size()-1; ++l) {
                        for (int k = l+1; k < clique.size(); ++k) {
                            adjMap[clique[l]].push_back(clique[k]);
                            adjMap[clique[k]].push_back(clique[l]);
                        }
                    }
                }
            }
        }
    }

    return adjMap;
}

bool oneCharOff(const std::string &word1, const std::string &word2){
    if(word1.size() != word2.size())
        return false;

    int diffs = 0;
    for (int i = 0; i < word1.size(); ++i) {
        if(word1[i] != word2[i]){
            if(++diffs > 1)
                return false;
        }
    }
    return diffs == 1;
}

std::map<std::string, std::vector<std::string>> computeAdjacentWords_medium(const std::vector<std::string> &words){
    std::map<std::string, std::vector<std::string>> adjWords;
    std::map<int, std::vector<std::string>> wordsBylength;

    for (int i = 0; i < words.size(); ++i) {
        wordsBylength[words[i].size()].push_back(words[i]);
    }
    std::map<int, std::vector<std::string>>::const_iterator itr;
    for(itr = wordsBylength.begin(); itr != wordsBylength.end(); ++itr){
        const std::vector<std::string> gropsWords = (*itr).second;

        for (int i = 0; i < gropsWords.size()-1; ++i) {
            for (int j = i+1; j < gropsWords.size(); ++j) {
                if(oneCharOff(gropsWords[i], gropsWords[j])){
                    adjWords[gropsWords[i]].push_back(gropsWords[j]);
                    adjWords[gropsWords[j]].push_back(gropsWords[i]);
                }
            }
        }
    }
    return adjWords;
}


int main(int argc, char* argv[]){
    std::vector<std::string> words = {"wine", "line", "fine", "mine", "ji", "ik", "il", "duck"};
    std::map<std::string, std::vector<std::string>> adj1 = computeAdjacentWords(words);
//    std::map<std::string, std::vector<std::string>> adj2 = computeAdjacentWords_medium(words);

    std::map<std::string, std::vector<std::string>>::const_iterator itr;
    std::ostream_iterator<std::string> out_iter(std::cout, " ");
    for(itr = adj1.begin(); itr != adj1.end(); ++itr){
        const std::vector<std::string> adjw1 = (*itr).second;


        std::cout<<(*itr).first<<":";
        std::copy(adjw1.begin(), adjw1.end(), out_iter);

        std::cout<<std::endl;

    }
//    std::cout<<"2"<<std::endl;
//
//    itr = adj2.begin();
//    const std::vector<std::string> adjw2 = (*itr).second;
//
//    std::copy(adjw2.begin(), adjw2.end(), out_iter);

    return 0;
}

