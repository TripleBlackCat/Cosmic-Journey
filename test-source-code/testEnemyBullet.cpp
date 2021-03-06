#include "Grid.h"
#include "EnemyBullet.h"
#include "Enemy.h"
#include <memory>

using std::shared_ptr;
using std::make_shared;


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

TEST_CASE("EnemyBullet is initialized with the correct attributes")
{
    Grid grid{800, 600};
    shared_ptr<IMovingEntity> enemy_ptr = make_shared<Enemy>(grid);
    shared_ptr<IMovingEntity> enemyBullet_ptr = make_shared<EnemyBullet>(enemy_ptr->getPosition() ,grid);
    
    CHECK(enemyBullet_ptr->getEntityType() == EntityType::ENEMY_BULLET);
    CHECK(enemyBullet_ptr->isAlive());
    CHECK_FALSE(enemyBullet_ptr->getRespawn());
    CHECK(enemyBullet_ptr->getHitRadius() == 6);    
}

TEST_CASE("EnemyBullet spawns at player position")
{
    Grid grid{800, 600};
    shared_ptr<IMovingEntity> enemy_ptr = make_shared<Enemy>(grid);
    shared_ptr<IMovingEntity> enemyBullet_ptr = make_shared<EnemyBullet>(enemy_ptr->getPosition() ,grid);
    
    auto enemyPosX = enemy_ptr->getPosition().getXpos;
    auto enemyPosY = enemy_ptr->getPosition().getYpos;
    auto enemyBulletPosX = enemyBullet_ptr->getPosition().getXpos;
    auto enemyBulletPosY = enemyBullet_ptr->getPosition().getYpos;
    
    CHECK(enemyBulletPosX == enemyPosX);
    CHECK(enemyBulletPosY == enemyPosY);
}

TEST_CASE("EnemyBullet can move")
{
    Grid grid{800, 600};
    shared_ptr<IMovingEntity> enemy_ptr = make_shared<Enemy>(grid);
    shared_ptr<IMovingEntity> enemyBullet_ptr = make_shared<EnemyBullet>(enemy_ptr->getPosition() ,grid);
    
    auto xPosBefore = enemyBullet_ptr->getPosition().getXpos();
    auto yPosBefore = enemyBullet_ptr->getPosition().getYpos();
    enemyBullet_ptr->move();
    auto xPosAfter = enemyBullet_ptr->getPosition().getXpos();
    auto yPosAfter = enemyBullet_ptr->getPosition().getYpos();
    
    bool isPositionDifferent = (xPosAfter != xPosBefore || yPosAfter != yPosBefore);
    
    CHECK(isPositionDifferent);    
}

TEST_CASE("EnemyBullet can be set dead")
{
    Grid grid{800, 600};
    shared_ptr<IMovingEntity> enemy_ptr = make_shared<Enemy>(grid);
    shared_ptr<IMovingEntity> enemyBullet_ptr = make_shared<EnemyBullet>(enemy_ptr->getPosition() ,grid);
        
    enemyBullet_ptr->setDead();
    
    CHECK_FALSE(enemyBullet_ptr->isAlive());
}

TEST_CASE("EnemyBullet is set dead when it reaches the circumference of playing circle")
{
    Grid grid{800, 600};
    shared_ptr<IMovingEntity> enemy_ptr = make_shared<Enemy>(grid);
    shared_ptr<IMovingEntity> enemyBullet_ptr = make_shared<EnemyBullet>(enemy_ptr->getPosition() ,grid);
        
    while(enemyBullet_ptr->getPosition().getRadius() < grid.getRadius()) enemyBullet_ptr->move();
    enemyBullet_ptr->move();
    
    CHECK_FALSE(enemyBullet_ptr->isAlive());
    CHECK_FALSE(enemyBullet_ptr->getRespawn());
    
}

TEST_CASE("EnemyBullet fires at same angle as Enemy")
{
    Grid grid{800, 600};
    shared_ptr<IMovingEntity> enemy_ptr = make_shared<Enemy>(grid);
    shared_ptr<IMovingEntity> enemyBullet_ptr = make_shared<EnemyBullet>(enemy_ptr->getPosition() ,grid);
    
    auto enemyAngle = enemy_ptr->getPosition().getAngle();
    auto enemyBulletAngle = enemyBullet_ptr->getPosition().getAngle();
    CHECK(enemyBulletAngle == enemyAngle);
}
