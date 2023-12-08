#pragma once

#include <iostream>
#include <stdio.h>
#include <string>
#include <map>

#include <fmod.hpp>
#include <fmod_errors.h>

class AudioManager {
	public:
		AudioManager();
		~AudioManager();

		std::string audioName;
		std::map<std::string, FMOD::Sound*> sounds;

		void Load(const std::string& filePath, bool asStream);
		void Play(const std::string& filePath);
		void Play(const std::string& filePath, bool is3D, FMOD_VECTOR pos);
		void Pause(const std::string& filePath, bool isPaused);

		void Update(float elapsed);

		void SetVolume(float vol);
		void SetLooping(const std::string& filePath, bool isLooping);
		void Set3D(const std::string& filePath, bool is3D, FMOD_VECTOR pos);

		std::map<std::string, FMOD::Sound*>::iterator FindSound(const std::string& filePath);

		FMOD_RESULT result;
		FMOD::System*	system = nullptr;

		FMOD::Sound*	sound = nullptr;
		FMOD::Channel	*channel = 0;

		float			DISTANCE_FACTOR = 1.0f;
		bool			listenerFlag = true;
		FMOD_VECTOR		listenerPos = { 0.0f, 0.0f, -1.0f * DISTANCE_FACTOR };
		FMOD_VECTOR		vel = { 0.0f, 0.0f, 0.0f };



};
