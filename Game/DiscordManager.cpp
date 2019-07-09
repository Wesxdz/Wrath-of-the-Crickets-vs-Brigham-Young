#include "DiscordManager.h"

#include <Discord/discord.h>

#include <time.h> // For getting Time since Epoch
#include <functional> // For hashing of Party Invites
#include <array>
#include <Windows.h>

namespace {

	discord::Timestamp startTime;

	std::string joinSecret;
	std::string spectateSecret;
	std::string partyID;

	std::array<std::string, 4> discordImageKeys = {"arsonist", "birdwatcher", "farmer", "sculptor"};
}

void DiscordManager::Init() 
{
	// TESTING / DEBUG
	// PTB - Flame_Test
	//SetEnvironmentVariableA("DISCORD_INSTANCE_ID", "0"); // Changes which Client the SDK connects to

	// Up to Date (Canary) - Flameo326
	//SetEnvironmentVariableA("DISCORD_INSTANCE_ID", "1"); // Changes which Client the SDK connects to

	// Create
	{
		auto result = discord::Core::Create(client_id, DiscordCreateFlags_Default, &core);	
		std::cout << "Discord Create Result: " << (int)result << "\n";
	}

	// Init
	if (core) {
		srand(0);
		std::hash<char*> hash;

		// Variables
		startTime = time(0);
		joinSecret = std::to_string(hash("Join"));
		spectateSecret = std::to_string(hash("Spectate"));
		partyID = std::to_string(hash("Party"));

		// Log
		core->SetLogHook(discord::LogLevel::Debug, [](discord::LogLevel level, const char* data) {
			std::cerr << "Log(" << static_cast<uint32_t>(level) << "): " << data << "\n";
		});

		// User
		core->UserManager().OnCurrentUserUpdate.Connect([this]() {
			auto userResult = core->UserManager().GetCurrentUser(&user);
			std::cout << "Discord User Result: " << (int)userResult << "\n";
			if (userResult == discord::Result::Ok) {
				std::cout << "Discord Username: " << user.GetUsername() << "\n";
			}
		});

		// Register
		auto result = core->ActivityManager().RegisterCommand(slGame::inst.path.toAnsiString().c_str());
		std::cout << "Discord Register Command Result: " << (int)result << "\n";
	}

	// Activity
	if (core) {
		// Overlay
		//bool isEnabled = false;
		//core->OverlayManager().IsEnabled(&isEnabled);
		//if (!isEnabled) {
		//	core->OverlayManager().en
		//} 

		//bool isLocked = false;
		//core->OverlayManager().IsLocked(&isLocked);
		//if (isLocked) {
		//	core->OverlayManager().SetLocked(false, [](discord::Result result) {
		//		std::cout << "Unlocking Overlay: " << (int)result << "\n";
		//	});
		//} else {
		//	std::cout << "Overlay already unlocked\n";
		//}
	}	

	// Activity
	if (core) {
		// ALL DISCORD OBJECTS SHOULD BE DEFAULT INITIALIZED (aka do {} when creating them)
		discord::Activity activity{};
		activity.SetType(discord::ActivityType::Playing);
		activity.SetDetails("Working on Discord Networking");

		activity.GetTimestamps().SetStart(startTime);

		activity.GetParty().SetId(partyID.c_str());
		activity.GetParty().GetSize().SetCurrentSize(1);
		activity.GetParty().GetSize().SetMaxSize(4);

		activity.GetSecrets().SetJoin(joinSecret.c_str());
		activity.GetSecrets().SetSpectate(spectateSecret.c_str());

		int randomImageIndex = rand() % discordImageKeys.size();
		activity.GetAssets().SetLargeText(discordImageKeys[randomImageIndex].c_str());
		activity.GetAssets().SetLargeImage(discordImageKeys[randomImageIndex].c_str());

		core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {
			std::cout << "Discord Update Activity Result: " << (int)result << "\n";

			//	//core->OverlayManager().OpenActivityInvite(discord::ActivityActionType::Join, [](discord::Result result) {
			//	//	std::cout << "Acitivity Invite: " << (int)result << "\n";
			//	//});
		});
	}

	Reg(slRegister::UPDATE);
}

bool DiscordManager::Input(sf::Event* e)
{
	// No Input
	return false;
}

void DiscordManager::Update(float dt)
{
	if (core) {
		core->RunCallbacks();
	}
}

void DiscordManager::Draw()
{
	// No Draw
}