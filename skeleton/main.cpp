#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"

#include <iostream>

#include "Particle.h"
#include "AliExpressParticleSystem.h"
#include "Gravity.h"
#include "Wind.h"
#include "Whirlwind.h"
#include "Explosion.h"
#include "DynamicRigidBody.h"
#include "PlayerSystem.h"
#include "StellarSystem.h"

std::string display_text = "This is a test";

#define M_PI 3.14159265358979323846

using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

//std::vector<Particle*> vParticles_;
//Particle* p = nullptr;

//AliExpressParticleSystem* ps = nullptr;
//ForceGenerator* gravity = nullptr;
//ForceGenerator* wind = nullptr;
//ForceGenerator* whirlwind = nullptr;
//ForceGenerator* explosion = nullptr;

//bool lighted = false;

static StellarSystem* ss = nullptr;
static PlayerSystem* ps = nullptr;
static DynamicRigidBody* player = nullptr;

// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, 0.0f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	/*gravity = new Gravity();
	wind = new Wind(Vector3(-20, 0, 0), 0.5, 0.1, Vector3(100, -120, -120), Vector3(120, 120, 120));
	whirlwind = new Whirlwind(0.5, 0.1, Vector3(-100, -100, -100), Vector3(100, 100, 100), 2, Vector3(0, 0, 0));
	explosion = new Explosion(100, Vector3(0, 0, 0), 1000, 2);*/


	ps = new PlayerSystem(Vector3(4500, 50, 1), gPhysics, gScene);
	ps->generate();
	double orbitalSpeed = sqrt((G * 4e15) / 4500);

	/*physx::PxVec3 tangentialVelocity = (player->position() - Vector3(0, 0, 0)).getNormalized().cross(Vector3(0, 1, 0));
	tangentialVelocity.normalize();
	tangentialVelocity *= orbitalSpeed;
	player->set_linear_velocity(-tangentialVelocity);*/

	//std::cout << player->position().x << " " << player->position().y << " " << player->position().z << std::endl;

	ss = new StellarSystem(Vector3(0, 0, 0), gPhysics, gScene, ps->player());
	ss->generate();

	
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);
	gScene->simulate(t);
	gScene->fetchResults(true);

	ss->update(t);
	ps->update(t);
	//std::cout << player->position().x << " " << player->position().y << " " << player->position().z << std::endl;
# pragma region curso
	/*;

	gravity->apply_force_particle(t);
	wind->apply_force_particle(t);
	whirlwind->apply_force_particle(t);
	if (lighted) {
		explosion->apply_force_particle(t);
		lighted = false;
	}
	if (ps != nullptr) ps->update(t);*/

	//p->integrate(t);
	/*for(const auto a : vParticles_)
	{
		a->integrate(t);
	}*/

#pragma endregion 
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	//delete gSphere;
	//delete p;
	/*for (auto a : vParticles_)
		delete a;*/

	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	case 'O':
	{
		ps->move();
		break;
	}
	case 'F':
	{
		/*if (ps != nullptr) delete ps;
		ps = new AliExpressParticleSystem(physx::PxVec3(0.0, 0.0, 0.0), 'f');
		gravity->register_particle_system(ps);
		whirlwind->register_particle_system(ps);*/
		break;
	}
	/*case 'N':
	{
		if (ps != nullptr) delete ps;
		ps = new AliExpressParticleSystem(physx::PxVec3(0.0, 0.0, 0.0), 'n');
		explosion->register_particle_system(ps);
		gravity->register_particle_system(ps);
		break;
	}
	case 'E':
	{
		if (ps != nullptr) delete ps;
		ps = new AliExpressParticleSystem(physx::PxVec3(0.0, 0.0, 0.0), 'e');
		wind->register_particle_system(ps);
		break;
	}
	case 'M':
	{
		if (ps != nullptr) delete ps;
		ps = new AliExpressParticleSystem(physx::PxVec3(0.0, 0.0, 0.0), 'm');
		gravity->register_particle_system(ps);
		break;
	}
	case 'B':
	{
		if (ps != nullptr) delete ps;
		ps = new AliExpressParticleSystem(physx::PxVec3(0.0, 0.0, 0.0), 'b');
		gravity->register_particle_system(ps);
		break;
	}
	case 'P':
	{
		lighted = true;
	}*/
	default:
		break;
	}
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}


int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}