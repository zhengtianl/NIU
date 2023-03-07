

#ifndef UNTITLED_COMPONENT_H
#define UNTITLED_COMPONENT_H

class GameObject;
class Component {
public:
    Component();
    virtual ~Component();

    GameObject* game_object(){return game_object_;}
    void set_game_object(GameObject* game_object){game_object_=game_object;}

    virtual void OnEnable();
    virtual void Awake();
    virtual void Update();

    /// 渲染之前
    virtual void OnPreRender();
    /// 渲染之后
    virtual void OnPostRender();

    virtual void OnDisable();
private:
    GameObject* game_object_;
};


#endif //UNTITLED_COMPONENT_H
