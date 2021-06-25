#include "MainMenuScene.h"
#include "GameScene.h"
#include "Definitions.h"
#include <iostream>

using namespace std;
USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    return MainMenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create("C:/Users/Annie QY Li/Desktop/Cocos2dx/Bird/birds/Resources/MainBackground.jpg");
    if (backgroundSprite == nullptr)
    {
            cout << "Problem loading Background.jpg" << endl;
            problemLoading("'Background.jpg'");
    }
    else {
            backgroundSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
            /*backgroundSprite->setScale(1 / 20.0);*/
            this->addChild(backgroundSprite, -1);
    }


    auto label = Label::createWithTTF("Flappy Bird", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    //Add the play button in the menu
    //For multiple buttons, use menu


    auto playWord = MenuItemFont::create("Play", CC_CALLBACK_1(MainMenuScene::GoToGameScene, this));
    playWord->setFontSize(20);
    playWord->setFontName("C:/Users/Annie QY Li/Desktop/Cocos2dx/Bird/birds/Resources/fonts/Marker Felt.ttf");
    playWord->setPosition(Vec2(visibleSize.width / 3 + origin.x, visibleSize.height / 2 + origin.y));
    auto ScoreWord = MenuItemFont::create("Scores", CC_CALLBACK_1(MainMenuScene::GoToGameScene, this));
    playWord->setFontSize(24);
    playWord->setFontName("C:/Users/Annie QY Li/Desktop/Cocos2dx/Bird/birds/Resources/fonts/Marker Felt.ttf");
    playWord->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 4 * 2));
    auto SettingsWord = MenuItemFont::create("Settings", CC_CALLBACK_1(MainMenuScene::GoToGameScene, this));
    playWord->setFontSize(24);
    playWord->setFontName("C:/Users/Annie QY Li/Desktop/Cocos2dx/Bird/birds/Resources/fonts/Marker Felt.ttf");
    playWord->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 4 * 1));
   

    auto menu = Menu::create(playWord, ScoreWord, SettingsWord, NULL);
    menu->setPosition(Point::ZERO);

    this->addChild(menu, 1);



   
    return true;
}

//The function to go to the game scene
void MainMenuScene::GoToGameScene(cocos2d::Ref* Sender)
{
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));

}