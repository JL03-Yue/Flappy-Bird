#include "Bird.h"
#include "Definitions.h"

USING_NS_CC;

Bird::Bird(cocos2d::Layer*layer)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	

	//Create the physics body of the bird
	flappyBird = Sprite::create("C:/Users/Annie QY Li/Desktop/Cocos2dx/Bird/birds/Resources/bird.jpg");
	flappyBird->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	auto flappyBody = PhysicsBody::createCircle(flappyBird->getContentSize().width/2);
	flappyBody->setCollisionBitmask(BIRD_COLLISION_BITMASK);
	flappyBody->setContactTestBitmask(true);


	flappyBird->setPhysicsBody(flappyBody);

	layer->addChild(flappyBird, 100);
	isFalling = true;

	//add collision
	



}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

void Bird::Fall()
{
	if (isFalling == true)
	{
		flappyBird -> setPositionX(visibleSize.width / 2 + origin.x);
		flappyBird->setPositionY(flappyBird->getPositionY() - (BIRD_FALLING_SPEED * visibleSize.height));
	}
	else
	{
		flappyBird->setPositionX(visibleSize.width / 2 + origin.x);
		flappyBird->setPositionY(flappyBird->getPositionY() + (BIRD_FALLING_SPEED * visibleSize.height));
	}
}

