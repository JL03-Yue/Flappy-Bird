#include "Pipe.h"
#include "Definitions.h"

USING_NS_CC;

Pipe::Pipe()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

void Pipe::ShowPipe(cocos2d::Layer* layer)
{
	CCLOG("show pipe");

    //create pipe sprite
	auto topPipe = Sprite::create("C:/Users/Annie QY Li/Desktop/Cocos2dx/Bird/birds/Resources/Pipe.png");
    if (topPipe == nullptr)
    {
        problemLoading("'C:/Users/Annie QY Li/Desktop/Cocos2dx/Bird/birds/Resources/Pipe.png'");
    }

    auto buttomPipe = Sprite::create("C:/Users/Annie QY Li/Desktop/Cocos2dx/Bird/birds/Resources/Pipe.png");
    if (buttomPipe == nullptr)
    {
        problemLoading("'C:/Users/Annie QY Li/Desktop/Cocos2dx/Bird/birds/Resources/Pipe.png'");
    }

    //physics body for pipe sprite with PhysicsBoday
    auto topPipeBody = PhysicsBody::createBox(topPipe->getContentSize());
    auto buttomPipeBody = PhysicsBody::createBox(buttomPipe->getContentSize());

    //Generate the position of interval
    auto random = CCRANDOM_0_1();
    if (random < LOWER_SCREEN_PIPE_THRESHOLD)
    {
        random = LOWER_SCREEN_PIPE_THRESHOLD;
    }
    else if (random > UPPER_SCREEN_PIPE_THRESHOLD)
    {
        random = UPPER_SCREEN_PIPE_THRESHOLD;

    }
    
    //Set the position of two pipes
    
    topPipeBody->setDynamic(false);
    buttomPipeBody->setDynamic(false);

    //set collision detection
    topPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    buttomPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    topPipeBody->setContactTestBitmask(true);
    buttomPipeBody->setContactTestBitmask(true);
    

    topPipe->setPhysicsBody(topPipeBody);
    buttomPipe->setPhysicsBody(buttomPipeBody);

    auto pipeWidth = (visibleSize.width / topPipe->getContentSize().width) / 20;
    topPipe->setScaleX((visibleSize.width / topPipe->getContentSize().width) /20);
    buttomPipe->setScaleX((visibleSize.width / buttomPipe->getContentSize().width) /20);

    //auto pipeHeight = (visibleSize.height / topPipe->getContentSize().height) *0.2;
    topPipe->setScaleY(0.95);
    buttomPipe->setScaleY(0.95);
    auto topPipePosition = (random * visibleSize.height) + (topPipe->getContentSize().height/2);

    //Get the size of the bird
    auto bird = Sprite::create("C:/Users/Annie QY Li/Desktop/Cocos2dx/Bird/birds/Resources/bird.jpg");

    topPipe->setPosition(Vec2(visibleSize.width + pipeWidth +origin.x   , topPipePosition));
    buttomPipe->setPosition(Vec2(topPipe->getPositionX(), topPipePosition - 
        visibleSize.height/bird->getContentSize().height /100 *PIPE_GAP - 
    topPipe->getContentSize().height));
    

    //add pipe to layer
    layer->addChild(topPipe, 2);
    layer->addChild(buttomPipe, 2);

    //Add pipeMovement
    auto topPipeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width, Vec2(-visibleSize.width
        * 1.5, 0));
    auto buttomPipeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width, Vec2(-visibleSize.width
        * 1.5, 0));

    topPipe->runAction(topPipeAction);
    buttomPipe->runAction(buttomPipeAction);

    ////Detect if the player pass the pipe and add score
    //auto pointNode = Node::create();
    //auto pointBody = PhysicsBody::createBox(Size(1, bird->getContentSize().height * PIPE_GAP));

    //pointBody->setDynamic(false);
    //pointBody->setCollisionBitmask(POINT_COLLISION_BITMASK);
    //pointBody->setContactTestBitmask(true);
    //pointNode->setPhysicsBody(pointBody);
    //pointNode->setPosition(Point(topPipe->getPositionX(), topPipe->getPositionY() - (topPipe - < getContentsize().height / 2)
    //    - ((bird->getContentSize.height * PIPE_GAP) / 2)));
    //layer->addChild(pointNode);

    //auto pointNodeAction = 


    

}

