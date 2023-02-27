
#ifndef UNTITLED_COMPONENT_H
#define UNTITLED_COMPONENT_H

class GameObject;
class Component {
public:
    Component();
    virtual ~Component();

    GameObject* game_object(){return game_object_;}
    void set_game_object(GameObject* game_object){game_object_=game_object;}

    virtual void Awake();
    virtual void Update();
private:
    GameObject* game_object_;
};


#endif //UNTITLED_COMPONENT_H
