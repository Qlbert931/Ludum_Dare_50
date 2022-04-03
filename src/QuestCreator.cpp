#include"QuestCreator.hpp"
#include<cmath>

#define DISTANCE(A,B) std::sqrt(std::pow(A.x-B.x,2),std::pow(A.y-B.y,2)); 

QuestCreator::QuestCreator(std::shared_ptr<Player> _player){
    player=_player;
};

void QuestCreator::addQuest(Quest _quest){
    activeQuests.push_back(_quest);
};

void QuestCreator::update(){
    for(int i=0; i<activeQuests.size();i++){
        switch(activeQuests.at(i).returnQuestType()){
            case hug:
                if(std::sqrt(std::pow(player->getGlobalTransform().getPosition().x-activeQuests.at(i).returnQuestObjective()->getGlobalTransform().getPosition().x,2.f)+std::pow(player->getGlobalTransform().getPosition().y-activeQuests.at(i).returnQuestObjective()->getGlobalTransform().getPosition().y,2.f))<50.f){
                    activeQuests.at(i).setQuestAsDone();
                    completedQuests.push_back(activeQuests.at(i));
                    activeQuests.erase(activeQuests.begin()+i);
                    i=i-1;
                    continue;
                }
                break;
            case talk:
                break;
            case kill:
                if(activeQuests.at(i).returnQuestObjective()->isDead()){
                    activeQuests.at(i).setQuestAsDone();
                    completedQuests.push_back(activeQuests.at(i));
                    activeQuests.erase(activeQuests.begin()+i);
                    i=i-1;
                    continue;
                }
                break;
            case steal:
                break;
        }
        if(activeQuests.at(i).returnRemainingTime()<sf::seconds(0)){
            activeQuests.at(i).setQuestAsFailed();
            failedQuests.push_back(activeQuests.at(i));
            activeQuests.erase(activeQuests.begin()+i);
            i=i-1;
        }
    }


};