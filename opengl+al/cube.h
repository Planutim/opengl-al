#pragma once
#include <glm/glm.hpp>
#include <string>
#include <AL/al.h>
#include "sound.h"
//#include <iostream>

class Cube {
public:
	Cube(glm::vec3 position, float size, std::string music_filename="") :position_(position), music_filename_(music_filename)
	{}
	Cube(float x, float y, float z, float size, std::string music_filename = "")
		
	{
		position_ = glm::vec3(x, y, z);
		size_ = size;
		music_filename_ = music_filename;
	}



	glm::mat4 getWorldMatrix()
	{
		glm::mat4 world = glm::mat4(1.0f);
		world = glm::translate(world, position_);
		world = glm::scale(world, glm::vec3(size_));
		return world;
	}

	void play_sound()
	{
		if (!initialized)
		{
			initSound();
			initialized = true;
		}
		alSourcePlay(source);
	}
private:
	int initSound()
	{
		ALuint buffer;
		buffer = LoadSound(music_filename_.c_str());

		//buffer = LoadSound("StarWars3.wav");
		if (!buffer)
		{
			CloseAL();
			std::cout << "SOMETHING WRONG WTFFFFFFF AT" << std::endl;
		}

		source = 0;
		alGenSources(1, &source);
		alSourcei(source, AL_BUFFER, (ALint)buffer);
		alSourcefv(source, AL_POSITION, &position_[0]);
		assert(alGetError() == AL_NO_ERROR && "Failed to setup sound source");

		return 0;
	}

	bool initialized = false;
	ALuint source;
	float size_;
	glm::vec3 position_;
	std::string music_filename_;
};
