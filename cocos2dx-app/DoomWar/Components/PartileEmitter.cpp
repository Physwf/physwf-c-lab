#include "PartileEmitter.h"
#include "Engine.h"

ParticleTraceEmitter::ParticleTraceEmitter(CCSprite* layer)
{
	mLayer = layer;
}

ParticleTraceEmitter::~ParticleTraceEmitter()
{

}

ParticleTraceEmitter* ParticleTraceEmitter::create()
{
	CCSprite* layer = Engine::world->pve()->layerEffect();
	ParticleTraceEmitter* pRet = new ParticleTraceEmitter(layer);
	if (pRet && pRet->init())
	{
		pRet->autorelease();
	}
	return pRet;
}

bool ParticleTraceEmitter::initWithTotalParticles(unsigned int numberOfPartiles)
{
	if (CCParticleSystemQuad::initWithTotalParticles(numberOfPartiles))
	{
		// duration
		m_fDuration = kCCParticleDurationInfinity;

		// Gravity Mode
		this->m_nEmitterMode = kCCParticleModeGravity;

		this->m_ePositionType = kCCPositionTypeFree;

		// Gravity Mode: gravity
		this->modeA.gravity = ccp(0, 0);

		// Gravity Mode: radial acceleration
		this->modeA.radialAccel = 0;
		this->modeA.radialAccelVar = 0;

		// Gravity Mode: speed of particles
		this->modeA.speed = 0;
		this->modeA.speedVar = 0;

		// starting angle
		m_fAngle = 90;
		m_fAngleVar = 0;

		// emitter position
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		//this->setPosition(ccp(winSize.width / 2, 60));
		//this->m_tPosVar = ccp(40, 20);

		// life of particles
		m_fLife = 1;
		m_fLifeVar = 0.0f;


		// size, in pixels
		m_fStartSize = 30.0f;
		//m_fStartSizeVar = 54.0f;
		m_fEndSize = kCCParticleStartSizeEqualToEndSize;

		// emits per frame
		m_fEmissionRate = 40.0f;
		//m_uTotalParticles = 50;
		// color of particles
		m_tStartColor.r = 1.0f;
		m_tStartColor.g = 1.0f;
		m_tStartColor.b = 1.0f;
		m_tStartColor.a = 1.0f;
		m_tStartColorVar.r = 0.0f;
		m_tStartColorVar.g = 0.0f;
		m_tStartColorVar.b = 0.0f;
		m_tStartColorVar.a = 0.0f;
		m_tEndColor.r = 1.0f;
		m_tEndColor.g = 1.0f;
		m_tEndColor.b = 1.0f;
		m_tEndColor.a = 0.0f;
		m_tEndColorVar.r = 0.0f;
		m_tEndColorVar.g = 0.0f;
		m_tEndColorVar.b = 0.0f;
		m_tEndColorVar.a = 0.0f;

		setTexture(CCTextureCache::sharedTextureCache()->addImage("./Data/fire.png"));//.pvr");

		// additive
		this->setBlendAdditive(true);
		mLayer->addChild(this);
		return true;
	}
	return false;
}

ParticleHitEmitter::ParticleHitEmitter(CCSprite* layer)
{
	mLayer = layer;
}

ParticleHitEmitter::~ParticleHitEmitter()
{

}

ParticleHitEmitter* ParticleHitEmitter::create()
{
	CCSprite* layer = Engine::world->pve()->layerEffect();
	ParticleHitEmitter* pRet = new ParticleHitEmitter(layer);
	if (pRet && pRet->init())
	{
		pRet->autorelease();
	}
	return pRet;
}

bool ParticleHitEmitter::initWithTotalParticles(unsigned int numberOfPartiles)
{
	if (CCParticleSystemQuad::initWithTotalParticles(numberOfPartiles))
	{
		// duration
		m_fDuration = 0.1f;

		setEmitterMode(kCCParticleModeGravity);

		// Gravity Mode: gravity
		setGravity(ccp(0, 0));

		// Gravity Mode: speed of particles
		setSpeed(500);
		setSpeedVar(100);

		// Gravity Mode: radial
		setRadialAccel(-500);
		setRadialAccelVar(0);

		// Gravity Mode: tangential
		setTangentialAccel(0);
		setTangentialAccelVar(0);

		// angle
		m_fAngle = 90;
		m_fAngleVar = 360;

		// emitter position
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		this->setPosition(ccp(winSize.width / 2, winSize.height / 2));
		setPosVar(CCPointZero);

		// life of particles
		m_fLife = 0.3f;
		m_fLifeVar = 0;

		// size, in pixels
		m_fStartSize = 10;
		m_fStartSizeVar = 0.0f;
		m_fEndSize = kCCParticleStartSizeEqualToEndSize;

		// emits per second
		m_fEmissionRate = m_uTotalParticles / m_fDuration;
		//m_uTotalParticles = 50;
		// color of particles
		m_tStartColor.r = 1.0f;
		m_tStartColor.g = 1.0f;
		m_tStartColor.b = 1.0f;
		m_tStartColor.a = 1.0f;
		m_tStartColorVar.r = 0.0f;
		m_tStartColorVar.g = 0.0f;
		m_tStartColorVar.b = 0.0f;
		m_tStartColorVar.a = 0.0f;
		m_tEndColor.r = 1.0f;
		m_tEndColor.g = 1.0f;
		m_tEndColor.b = 1.0f;
		m_tEndColor.a = 0.0f;
		m_tEndColorVar.r = 0.0f;
		m_tEndColorVar.g = 0.0f;
		m_tEndColorVar.b = 0.0f;
		m_tEndColorVar.a = 0.0f;

		setTexture(CCTextureCache::sharedTextureCache()->addImage("./Data/fire.png"));//.pvr");

		// additive
		this->setBlendAdditive(true);
		mLayer->addChild(this);
		return true;
	}
	return false;
}