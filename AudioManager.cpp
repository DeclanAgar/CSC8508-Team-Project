// Code inspired from: https://subscription.packtpub.com/book/game-development/9781849699099/2/ch02lvl1sec19/project-1-building-a-simple-audio-manager
//

#include "AudioManager.h"

AudioManager::AudioManager() {
	result = FMOD::System_Create(&system);
	if (result != FMOD_OK)
	{
		std::cout << "FMOD error!\n" << result << FMOD_ErrorString(result);
		exit(-1);
	}
	result = system->init(512, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_OK)
	{
		std::cout << "FMOD error!\n" << result << FMOD_ErrorString(result);
		exit(-1);
	}
	std::cout << "Initialisation Successful\n";
};

AudioManager::~AudioManager() {
	std::map<std::string, FMOD::Sound*>::iterator i;

	for (i = sounds.begin(); i != sounds.end(); i++)
		i->second->release();
	
	sounds.clear();

	system->release();
	system = nullptr;
}

void AudioManager::Load(const std::string& filePath, bool asStream) {
	if (sounds.find(filePath) != sounds.end())
		return;

	if (asStream)
		system->createStream(filePath.c_str(), FMOD_DEFAULT, 0, &sound);
	else
		system->createSound(filePath.c_str(), FMOD_DEFAULT, 0, &sound);

	sounds.insert(std::make_pair(filePath, sound));
}

void AudioManager::Play(const std::string& filePath) {
	result = system->playSound(FindSound(filePath)->second, 0, false, &channel);
	std::cout << "Playing Sound\n";
}

void AudioManager::Play(const std::string& filePath, bool is3D, FMOD_VECTOR pos) {
	if (!is3D) {
		result = system->playSound(FindSound(filePath)->second, 0, is3D, &channel);
		std::cout << "Playing Sound\n";
	}
	else {
		Set3D(filePath, true, pos);
		result = system->playSound(FindSound(filePath)->second, 0, is3D, &channel);
		result = channel->set3DAttributes(&pos, &vel);
		result = channel->setPaused(false);
		std::cout << "Playing Sound in 3D\n";
	}

	
}

void AudioManager::Set3D(const std::string& filePath, bool is3D, FMOD_VECTOR pos) {
	FindSound(filePath)->second->setMode(is3D ? FMOD_3D : FMOD_2D);
	result = system->set3DSettings(1.0f, DISTANCE_FACTOR, 1.0f);

	result = FindSound(filePath)->second->set3DMinMaxDistance(0.5f * DISTANCE_FACTOR, 5000.0f * DISTANCE_FACTOR);
	pos.x *= DISTANCE_FACTOR;
}

void AudioManager::Pause(const std::string& filePath, bool isPaused) {
	system->playSound(FindSound(filePath)->second, 0, isPaused, &channel);
	
	if (isPaused)
		std::cout << "Pausing...\n";
	else
		std::cout << "Unpausing...\n";

	channel->stop();
}

void AudioManager::Update(float elapsed) {
	system->update();
}

void AudioManager::SetVolume(float vol) {
	channel->setVolume(vol);
}

void AudioManager::SetLooping(const std::string& filePath, bool isLooping) {
	FindSound(filePath)->second->setMode(isLooping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
}

std::map<std::string, FMOD::Sound*>::iterator AudioManager::FindSound(const std::string& filePath)
{
	std::map<std::string, FMOD::Sound*>::iterator i;

	i = sounds.find(filePath);

	if (i == sounds.end()) {
		std::cout << "Sound not found!\n";
	}

	return i;
}

