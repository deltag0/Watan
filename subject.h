#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include <memory>

class Player;

class Subject {
    protected:
    std::vector<std::unique_ptr<Player>> p_list;

    int num_observers = 0;

    void attach(std::unique_ptr<Player> observer);
    void detach(Player *observer);
    void notifyObservers();  

    virtual ~Subject() = 0;
};



#endif
