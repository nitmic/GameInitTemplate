#pragma once
#include "irrAdapter.h"
#include "GLAS.h"
#include <vector>


namespace IrrAdapter{
	class ParticleSystem{
	public:
		ParticleSystem(){
			m_pNode = GetSingleton<IrrApp>()->accessSceneManager()->addParticleSystemSceneNode(false);

			irr::scene::IParticleEmitter* em = m_pNode->createBoxEmitter(
				irr::core::aabbox3d<irr::f32>(-0.1,0,-0.1,0.1,0.1,0.1), // emitter size
				irr::core::vector3df(0.0f,3,0.0f),    // initial direction
				80,100,                                   // emit rate
				irr::video::SColor(0,255,255,255),        // darkest color
				irr::video::SColor(0,255,255,255),        // brightest color
				20,100,5,                               // min and max age, angle
				irr::core::dimension2df(0.3f,0.3f),       // min size
				irr::core::dimension2df(1,1)        // max size
			);
			m_pNode->setEmitter(em); // this grabs the emitter
			em->drop(); // so we can drop it here without deleting it
			/*
			irr::scene::IParticleFadeOutAffector* paf = m_pNode->createFadeOutParticleAffector();
			paf->setFadeOutTime(2000);
			m_pNode->addAffector(paf); // same goes for the affector
			paf->drop();
			*/
			m_pNode->setPosition(irr::core::vector3df(0,0,0));
			m_pNode->setScale(irr::core::vector3df(2,2,2));
			m_pNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
			m_pNode->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
			m_pNode->setMaterialTexture(0, GetSingleton<IrrApp>()->accessVideoDriver()->getTexture("fire.bmp"));
			m_pNode->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
		};
		void setAttitude(Glas::Quaternion q){
			m_Attitude = q;
		}
		void setPosition(Glas::Vector3f v){
			m_pNode->setPosition(v);
		}
		void start(){
			m_pNode->getEmitter()->setMaxParticlesPerSecond(1000);
		}
		void stop(){
			m_pNode->getEmitter()->setMaxParticlesPerSecond(0);
		}
		void draw(){
			m_pNode->getEmitter()->setDirection(m_Attitude*Glas::Vector3f(0.0f,0.03f,0.0f));
			m_pNode->setVisible(true);
		}
	private:
		Glas::Quaternion m_Attitude;
		Glas::Vector3f m_Pos;
		irr::scene::IParticleSystemSceneNode * m_pNode;
	};
};