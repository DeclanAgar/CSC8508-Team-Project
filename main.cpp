#include <fmod.hpp>
#include <fmod_errors.h>

#include "AudioManager.h"

int main() {
    AudioManager audioManager;
	bool exit = false;
	while (!exit) {
		int command = 0;
		std::cout << "Enter a number to perform the following commands:\n1. Load audio files.\n2. Play applause.mp3\n3. Play bicycle background music.\n4. Enable looping for bicycle.mp3\n5. Play applause in 3D to the right.\n6. Play applause in 3D to the left.\n7. Play all sounds together.\n8. Play sounds in  3D.\n9. Exit.\n";
		std::cin >> command;

		switch (command)
		{
		case 1:
			audioManager.Load("applause.mp3", false);
			audioManager.Load("bicycle.mp3", true);
			audioManager.Load("spawn.mp3", false);
			audioManager.Load("beamshot.mp3", false);
			audioManager.Load("damage.mp3", false);
			audioManager.Load("death.mp3", false);
			std::cout << "Audio files loaded.\n";
			break;
		case 2: 
			audioManager.Play("applause.mp3");
			audioManager.SetVolume(0.1f);
			break;
		case 3:
			audioManager.Play("bicycle.mp3");
			audioManager.SetVolume(0.2f);
			break;
		case 4: 
			audioManager.SetLooping("bicycle.mp3", true);
			break;
		case 5:
			audioManager.Play("applause.mp3", true, { 10.0f, 0.0f, 0.0f });
			audioManager.SetVolume(0.1f);
			break;
		case 6:
			audioManager.Play("applause.mp3", true, { -10.0f, 0.0f, 0.0f });
			audioManager.SetVolume(0.1f);
			break;
		case 7:
			audioManager.Play("applause.mp3", true, { -10.0f, 0.0f, 0.0f });
			audioManager.SetVolume(0.1f);
			audioManager.Play("spawn.mp3");
			audioManager.SetVolume(0.1f);
			audioManager.Play("beamshot.mp3");
			audioManager.SetVolume(0.1f);
			audioManager.Play("damage.mp3");
			audioManager.SetVolume(0.1f);
			audioManager.Play("death.mp3");
			audioManager.SetVolume(0.1f);
			break;
		case 8:
			audioManager.Play("applause.mp3", true, { -10.0f, 0.0f, 0.0f });
			audioManager.SetVolume(0.1f);
			audioManager.Play("spawn.mp3", true, { 10.0f, 0.0f, 0.0f });
			audioManager.SetVolume(0.1f);
			audioManager.Play("beamshot.mp3", true, { 0.0f, 0.0f, -10.0f });
			audioManager.SetVolume(0.1f);
			audioManager.Play("death.mp3", true, { 0.0f, 0.0f, 10.0f });
			audioManager.SetVolume(0.1f);
			break;
		case 9: // Exit interface
			std::cout << "Exiting...";
			return 0;
		default:
			std::cout << "Invalid input provided. Please enter a valid number.\n";
			break;
		}
	}

	return 0;
}

