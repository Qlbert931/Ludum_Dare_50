#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "Player.hpp"
#include "Toolkit.hpp"

void Player::onUpdate(const sf::Time &delta)
{
    velocity = {0,0};
    if(isFaceingRight){
            colliders["KILL"]->setTranslation({30.f,0.f});
            colliders["TALK"]->setTranslation({30.f,0.f});
    }
        else{
            colliders["KILL"]->setTranslation({-30.f,0.f});
            colliders["TALK"]->setTranslation({-30.f,0.f});
        }
    if(animation.getCurrentAnimation() == DYING)
    {
        currentTime += delta.asSeconds();

        if(currentTime > dyingTime)
        {
            currentTime -= dyingTime;
            animation.changeAnimation(DEAD);
            snipersRedDot->setVisible(false);
        }
    }
    else if(animation.getCurrentAnimation() == PUNCHING)
    {   
        colliders["KILL"]->setActive(true);
        currentTime += delta.asSeconds();
        if(currentTime > punchTime)
        {
            colliders["KILL"]->setActive(false);
            currentTime -= punchTime;
            animation.changeAnimation(IDLE);
        }

        const float punchingSlow = 0.5;
        updateVelocty(delta * punchingSlow);
    }
    else if( animation.getCurrentAnimation() != DEAD)
    {
        updateVelocty(delta);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
            //colliders["100-unit"]->setActive(false);
            colliders["TALK"]->setActive(true);
        }else{
            //colliders["100-unit"]->setActive(true);
            colliders["TALK"]->setActive(false);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            //colliders["100-unit"]->setActive(false);
            colliders["KILL"]->setActive(true);
            animation.changeAnimation(PUNCHING);
            soundSystem.playSound(punchSoundDirectory);
        }
        else 
        {
            colliders["KILL"]->setActive(false);
            //colliders["100-unit"]->setActive(true);
            if(std::abs(velocity.x) > 0.0f || std::abs(velocity.y) > 0.0f)
            {
                animation.changeAnimation(RUN);
            }
            else
            {
                animation.changeAnimation(IDLE);
            }
        }
    }

    if(isFaceingRight)
        colliders["KILL"]->setTranslation({50.0,0.0});
    else
        colliders["KILL"]->setTranslation({-50.0,0.0});
        
    updateSinpersRedDot(delta);
    updateBody(delta);
}

Player::Player(SoundSystem& soundSystem,sf::Vector2f position, sf::Vector2f size, float _speed, Animation _animation, float _dyingTime, float _punchTime) : 
Character(soundSystem, position, size, _speed, _animation, _dyingTime), punchTime(_punchTime)
{
    offsetTexture({0.0, -20.0});

    snipersRedDot = std::make_shared<MovingCircle>(MovingCircle(position, 3));
    snipersRedDot->setName("snipers red dot");
    snipersRedDot->circle.setFillColor(sf::Color(255, 0, 0, 255));
    addChild(snipersRedDot);
    
    randHeadPositon();
    snipersRedDot->setTranslation(m_local_transform.getPosition() - sf::Vector2f(100, 100));
}

void Player::onDraw(sf::RenderTarget &target)
{
    target.draw(body,m_global_transform.getTransform());
}

void Player::randHeadPositon()
{
    headPosition = m_local_transform.getPosition();
    headPosition.x -= rand()%13 - 6;
    headPosition.y -= rand()%13 - 6 + 20;
}

void Player::updateSinpersRedDot(const sf::Time& delta)
{
    float snipersVelocityMultiplayer = 2;

    if(animation.getCurrentAnimation() != IDLE)
    {
        randHeadPositon();
        snipersVelocityMultiplayer = 40;
    }
    else if(std::abs(headPosition.x - snipersRedDot->m_local_transform.getPosition().x) + std::abs(headPosition.y - snipersRedDot->m_local_transform.getPosition().y) < 0.7)
    {
        randHeadPositon();
    }

    sf::Vector2f newVelocity(headPosition - snipersRedDot->m_local_transform.getPosition());
    newVelocity *= snipersVelocityMultiplayer;

    snipersRedDot->setVelocity(newVelocity);
}

Player::Player(SoundSystem& soundSystem)
: Player(soundSystem, {100,100}, {100, 100}, 300, Animation("./res/textures/Player", {0.15, 0.1, 0.1, 1, 0.1}, {29,45,53,54,63}), 1.1, 0.8)
{
    setName("player");
    setDyingSoundName("gunShotMono.wav");
    punchSoundDirectory = "punch.wav";
}

void Player::updateVelocty(const sf::Time& delta)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        velocity.x -= speed;
        isFaceingRight = false;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        velocity.x += speed;
        isFaceingRight = true;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        velocity.y -= speed;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        velocity.y += speed;
    }

    if(std::abs(velocity.x) > 0.0f && std::abs(velocity.y > 0.0f))
    {
        velocity.x /= std::sqrt(2);
        velocity.y /= std::sqrt(2);
    }
}
