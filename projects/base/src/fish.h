#include "SFML/Graphics.hpp"
#include "cmath"
#include "kf/kf_log.h"
#include "qgf2d/system.h"
#include "qgf2d/anim.h"

using namespace std;
using namespace qgf;
using namespace kf;
using namespace sf;

class Fish
{
public:
	Fish();
	~Fish();
	Fish(float mX, float mY, Sprite *mSp, int mSi, bool mDe);
	void update(float deltaT);
	float moveX;
	float moveY;
	Sprite *mSprite;
	int mSize;
	bool mDead;
};

Fish::Fish()
{

}
Fish::~Fish()
{

}

Fish::Fish(float mX, float mY, Sprite *mS,int mSi, bool mD)
{
	moveX = mX;
	moveY = mY;
	mSprite = mS;
	mSize = mSi;
	mDead = mD;
	mSprite->setOrigin(mSprite->getTextureRect().width / 2, mSprite->getTextureRect().height / 2);
}

