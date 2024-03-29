#pragma once

#include "slComponent.h"

#include <map>
#include <SFML/Audio.hpp>

class cResources : public slComponent
{

public:
	sf::String resourcePath;
	sf::String texturesFile;
	sf::String soundsFile;
	sf::String fontsFile;
	sf::String shadersFile;
	// TODO: Make this resource manager generic enough to manage any type
	std::map<sf::String, sf::Texture> textures;
	std::map<sf::String, sf::SoundBuffer> sounds;
	std::map<sf::String, sf::Font> fonts;
	std::map<sf::String, sf::Shader*> shaders;

public:
	cResources();
	~cResources();
	// Inherited via slComponent
	virtual void Init() override;
	virtual bool Input(sf::Event * e) override;
	virtual void Update(float dt) override;
	virtual void Draw() override;

	inline sf::Texture* LoadTexture(sf::String asset)
	{
		if (textures.count(asset)) {
			return &textures[asset];
		}
		sf::Texture texture;
		texture.loadFromFile(resourcePath + "/" + texturesFile + "/" + asset);
		textures[asset] = texture;
		return &textures[asset];
	}

	inline sf::Font* LoadFont(sf::String asset)
	{
		if (fonts.count(asset)) {
			return &fonts[asset];
		}
		sf::Font font;
		font.loadFromFile(resourcePath + "/" + fontsFile + "/" + asset);
		fonts[asset] = font;
		return &fonts[asset];
	}

	inline sf::SoundBuffer* LoadSoundBuffer(sf::String asset)
	{
		if (sounds.count(asset)) {
			return &sounds[asset];
		}
		sf::SoundBuffer sound;
		sound.loadFromFile(resourcePath + "/" + soundsFile + "/" + asset);
		sounds[asset] = sound;
		return &sounds[asset];
	}

	inline sf::Shader* LoadShader(sf::String asset)
	{
		if (shaders.count(asset)) {
			return shaders[asset];
		}
		sf::Shader* shader = new sf::Shader;
		shader->loadFromFile(resourcePath + "/" + shadersFile + "/" + asset + ".vert", resourcePath + "/" + shadersFile + "/" + asset + ".frag");
		shaders[asset] = shader;
		return shaders[asset];
	}

};