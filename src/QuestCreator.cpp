#include"QuestCreator.hpp"
#include<cmath>
#include<random>

#define DISTANCE(A,B) std::sqrt(std::pow(A.x-B.x,2),std::pow(A.y-B.y,2)); 

QuestCreator::QuestCreator(std::shared_ptr<Player> _player, std::shared_ptr<Node> _objects){
    player=_player;
    loaded_objects = _objects;
};

void QuestCreator::addQuest(Quest _quest){
    activeQuests.push_back(_quest);
};
// NEEDS TESTING
void QuestCreator::update(){

    for(int i=0; i<activeQuests.size();i++){
        switch(activeQuests.at(i).returnQuestType()){
            case hug:
                if(activeQuests.at(i).returnQuestObjective()==nullptr){
                    if(lastPulse.pulseType==HUG && lastPulse.pulseEmitter==activeQuests.at(i).returnQuestObjectiveType()){
                        activeQuests.at(i).setQuestAsDone();
                        completedQuests.push_back(activeQuests.at(i));
                        activeQuests.erase(activeQuests.begin()+i);
                        i=i-1;
                        continue;
                    }
                }//else
                // if(std::sqrt(std::pow(player->getGlobalTransform().getPosition().x-activeQuests.at(i).returnQuestObjective()->getGlobalTransform().getPosition().x,2.f)+std::pow(player->getGlobalTransform().getPosition().y-activeQuests.at(i).returnQuestObjective()->getGlobalTransform().getPosition().y,2.f))<50.f){
                //     activeQuests.at(i).setQuestAsDone();
                //     completedQuests.push_back(activeQuests.at(i));
                //     activeQuests.erase(activeQuests.begin()+i);
                //     i=i-1;
                //     continue;
                // }
                break;
            case talk:
                if(activeQuests.at(i).returnQuestObjective()==nullptr){
                    if(lastPulse.pulseType==TALK && lastPulse.pulseEmitter==activeQuests.at(i).returnQuestObjectiveType()){
                        activeQuests.at(i).setQuestAsDone();
                        completedQuests.push_back(activeQuests.at(i));
                        activeQuests.erase(activeQuests.begin()+i);
                        i=i-1;
                        continue;
                    }
                }
                break;
            case kill:
                if(activeQuests.at(i).returnQuestObjective()==nullptr){
                    if(lastPulse.pulseType==KILL && lastPulse.pulseEmitter==activeQuests.at(i).returnQuestObjectiveType()){
                        activeQuests.at(i).setQuestAsDone();
                        completedQuests.push_back(activeQuests.at(i));
                        activeQuests.erase(activeQuests.begin()+i);
                        i=i-1;
                        continue;
                    }
                }
                // if(activeQuests.at(i).returnQuestObjective()->isDead()){
                //     activeQuests.at(i).setQuestAsDone();
                //     completedQuests.push_back(activeQuests.at(i));
                //     activeQuests.erase(activeQuests.begin()+i);
                //     i=i-1;
                //     continue;
                // }
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
    if (activeQuests.size() == 0 and failedQuests.size() == 0)
        addQuest(generateRandomQuest());
    sendPulse(CLEAR,"");
};
void QuestCreator::sendPulse(PulseType _pulse, std::string _name){
    lastPulse = {_pulse,_name};
};

Quest QuestCreator::generateRandomQuest()
{
    std::random_device randomizer;

    if(loaded_objects->getChildren()->size() <= 1)
        return Quest("None");

    std::uniform_int_distribution<> obj(0, loaded_objects->getChildren()->size() - 1);
    std::uniform_int_distribution<> t(0, 2);

    auto target = loaded_objects->getChildren()->at(obj(randomizer));
    while (target == player)
    {
        target = loaded_objects->getChildren()->at(obj(randomizer));
    }

    Quest q(target->getName(), QuestType(t(randomizer)), 30 * 1000);
    return q;

}