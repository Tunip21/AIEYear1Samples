#include "Critter.h"


Critter::Critter()
{
	m_position = Vector2{ 0, 0 };
	m_velocity = Vector2{ 0, 0 };
	m_radius = 0;
	m_isLoaded = false;
}

Critter::~Critter()
{
	//UnloadTexture(m_texture);
	m_isLoaded = false;
}

void Critter::Init(Vector2 position, Vector2 velocity, float radius, Texture2D texture, Critter critterArray[], int CRITTER_COUNT) //const char* originally
{
	
	m_position = position;
	m_velocity = velocity;
	m_radius = radius;
	m_texture = texture;
	//m_texture = LoadTexture(texture);	

	m_isLoaded = true;
	this->BeginOfArray(critterArray, CRITTER_COUNT);
}

void Critter::Init(Vector2 position, Vector2 velocity, float radius, Texture2D texture)
{
	m_position = position;
	m_velocity = velocity;
	m_radius = radius;
	m_texture = texture;
	//m_texture = LoadTexture(texture);	

	m_isLoaded = true;
}

void Critter::Destroy(Critter critterArray[], int CRITTER_COUNT)
{
	//UnloadTexture(m_texture);
	m_isLoaded = false;
	this->EndOfArray(critterArray, CRITTER_COUNT);
	
	
}

void Critter::Update(float dt)
{
	if (m_isLoaded == false)
		return;

	m_position.x += m_velocity.x * dt;
	m_position.y += m_velocity.y * dt;

	m_isDirty = false;
}


void Critter::Draw()
{
	if (m_isLoaded == false)
		return;

	DrawTexture(m_texture, m_position.x, m_position.y, WHITE);
}

void Critter::EndOfArray(Critter critterArray[], int CRITTER_COUNT)
{
	
	for (int n = CRITTER_COUNT; n != 2; --n)
	{
		critterArray[n - 1] = critterArray[n - 2];
		
	}
	critterArray[CRITTER_COUNT - 1] = *this;
	
}

void Critter::BeginOfArray(Critter critterArray[], int CRITTER_COUNT)
{
	for (int n = 0; n != CRITTER_COUNT - 1; ++n)
	{
		critterArray[n] = critterArray[n + 1];
	}
	critterArray[0] = *this;
}

