#include "GameScene.h"
#include "Definitions.h"
#include "GameOverScene.h"
#include <iostream>
using namespace std;

USING_NS_CC;

Scene* GameScene::createScene()
{
    //game scene is a physics world because there should be collisions
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    //Set own gravity for bird to fly
    scene->getPhysicsWorld()->setGravity(Vect(0, 0));
    
    auto layer = GameScene::create();
    layer->SetPhysicsWorld(scene->getPhysicsWorld());

    scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //the backgournd of game scene
    auto backgroundSprite = Sprite::create("C:/Users/Annie QY Li/Desktop/Cocos2dx/Bird/birds/Resources/GameBackGround.jpg");
    if (backgroundSprite == nullptr)
    {
        cout << "Problem loading Background.jpg" << endl;
        problemLoading("'Background.jpg'");
    }
    else {
        backgroundSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

        //set the image to fit the entire screen
        //Set the last parameter to 1 if fir the entire screen
        backgroundSprite->setScaleX((visibleSize.width / backgroundSprite->getContentSize().width) * 1);
        backgroundSprite->setScaleY((visibleSize.height / backgroundSprite->getContentSize().height) * 1);

        this->addChild(backgroundSprite, -1);
    }

    //Set the edge of the physics world

    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT,0, Vec2::ZERO);
    edgeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    edgeBody->setContactTestBitmask(true);

    auto edgeNode = Node::create();
    edgeNode->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);



    //Use scheduler to show pipes
    //Show frequency according to the width
    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::ShowPipe), PIPE_SHOW_FREQUENCY * visibleSize.width);


    //add bird
    bird = new Bird(this);

    //Collision listener
    //CC_CALLBACK_N: n is the number of parameters
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    //Touch Listener
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

    this->scheduleUpdate();

    return true;
}

void GameScene::ShowPipe(float dt)
{
    pipe.ShowPipe(this);
}


bool GameScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
    //a and b are two shapes colliding
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();

    if ((BIRD_COLLISION_BITMASK == a->getCollisionBitmask()) && (OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask())
        || (BIRD_COLLISION_BITMASK == b->getCollisionBitmask()) && (OBSTACLE_COLLISION_BITMASK == a->getCollisionBitmask()))
    {
        auto scene = GameOverScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    }
    return true;
}

bool GameScene::onTouchBegin(cocos2d::Touch* touch, cocos2d::Event* event)
{
    bird->Fly();

    this->scheduleOnce(CC_SCHEDULE_SELECTOR(GameScene::StopFlying),BIRD_FLY_DURATION);
    

    return true;
    
}

void GameScene::StopFlying(float dt)
{
    bird->StopFly();
}
void GameScene::update(float dt)
{
    bird->Fall();
}