#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Pipe.h"
#include "Bird.h"

class GameScene: public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
private:
    void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; };
    void ShowPipe(float dt);

    //collision
    bool onContactBegin(cocos2d::PhysicsContact& contact);

    //touch to fly
    bool onTouchBegin(cocos2d::Touch* touch, cocos2d::Event* event);
    void StopFlying(float dt);
    void update(float dt);




    cocos2d::PhysicsWorld* sceneWorld;
    Pipe pipe;

    //Pointer to bird because it has no default constructor
    Bird *bird;
    

};

#endif // __GAME_SCENE_H__
