#pragma once
#include"Quest.hpp"
#include"Player.hpp"

class QuestCreator{
    public:
        QuestCreator(std::shared_ptr<Player> _player);
        void addQuest(Quest _quest);
        void update();  // Sprawdza czy quest został wykponany/przegrany itp.
        std::vector<Quest> activeQuests;
        std::vector<Quest> failedQuests;
        std::vector<Quest> completedQuests;
    private:
        std::shared_ptr<Player> player;
};