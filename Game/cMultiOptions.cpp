#include "cMultiOptions.h"
#include "cGuiTool.h"

#include "cMultiplayerPlay.h"
#include "cMultiplayerSetup.h"
#include "slEntity.h"
#include "slComponent.h"
#include "Gameplay.h"
#include "Packets.h"

void cMultiOptions::Init()
{
	multiplayer = slGame::inst.currentState->entities["multi"]->GetComponent<cMultiplayerSetup>();
	gui = GetSiblingComponent<cGuiTool>();
	multiplayer->options = this;
	sf::String defaultPort = "50666";
	mainWindow = sfg::Window::Create();
	mainWindow->SetTitle("Setup Multiplayer");
	auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);
	box->Pack(sfg::Label::Create("Username"));
	enterUsername = sfg::Entry::Create();
	box->Pack(enterUsername);
	box->Pack(sfg::Label::Create("Host Port"));
	auto enterHostPort = sfg::Entry::Create();
	enterHostPort->SetText(defaultPort);
	box->Pack(enterHostPort);
	auto host = sfg::Button::Create("Host");
	box->Pack(host);
	auto lblEnter = sfg::Label::Create("Enter IP and Port of Host");
	box->Pack(lblEnter);
	auto ipBox = sfg::Box::Create();
	auto enterIP = sfg::Entry::Create();
	enterIP->SetRequisition({ 100, 20 });
	ipBox->Pack(enterIP);
	ipBox->Pack(sfg::Label::Create(":"));
	auto enterPort = sfg::Entry::Create();
	enterPort->SetText(defaultPort);
	ipBox->Pack(enterPort);
	box->Pack(ipBox);
	auto join = sfg::Button::Create("Join");
	box->Pack(join);
	box->SetRequisition({ 250, 100 });
	mainWindow->Add(box);
	gui->desktop.Add(mainWindow);
	host->GetSignal(sfg::Button::OnLeftClick).Connect([this, enterHostPort] {
		if (multiplayer->HostGame(std::stoi(enterHostPort->GetText().toAnsiString().c_str()))) {
			hostWindow = sfg::Window::Create();
			hostWindow->SetTitle("Host");
			auto content = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);
			auto ip = sf::IpAddress("localhost");
			auto title = sfg::Label::Create("Hosting game on " + ip.getPublicAddress().toString() + ": " + enterHostPort->GetText());
			content->Pack(title);
			auto start = sfg::Button::Create("Start");
			content->Pack(start);
			hostWindow->Add(content);
			gui->desktop.Add(hostWindow);
			start->GetSignal(sfg::Button::OnLeftClick).Connect([this]() {
				sf::Packet p;
				pk::GameStart info;
				info.seed = time(NULL);
				p << info;
				multiplayer->client->SendToHost(p);
			});
			hostWindow->SetPosition({ 1280 - hostWindow->GetRequisition().x, 0.f });
		}
	});
	join->GetSignal(sfg::Button::OnLeftClick).Connect([this, enterIP, enterPort] {
		multiplayer->JoinGame(sf::IpAddress(enterIP->GetText()), std::stoi(enterPort->GetText().toAnsiString().c_str()));
	});
}

bool cMultiOptions::Input(sf::Event * e)
{
	return false;
}

void cMultiOptions::Update(float dt)
{
}

void cMultiOptions::Draw()
{
}

void cMultiOptions::StartLobby()
{
	if (!clientWindow) {
		clientWindow = sfg::Window::Create();
		clientWindow->SetTitle("Lobby");
		auto content = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);
		auto leave = sfg::Button::Create("Leave");
		content->Pack(leave);
		lobbyContent = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);
		content->Pack(lobbyContent);
		clientWindow->Add(content);
		gui->desktop.Add(clientWindow);
		mainWindow->SetPosition({ -1000, 0 });
		leave->GetSignal(sfg::Button::OnLeftClick).Connect([this]() {
			multiplayer->LeaveGame();
			mainWindow->SetPosition({ 0, 0 });
			gui->desktop.Remove(hostWindow);
			hostWindow.reset();
			gui->desktop.Remove(clientWindow);
			clientWindow.reset();
		});
	}
}
