#include "AppClass.h"
void AppClass::ProcessKeyboard(void)
{
	//Flag for the modifier
	bool bModifier = false;

	//ON PRESS/RELEASE
#pragma region ON PRESS/RELEASE DEFINITION
	static bool	bLastF1 = false, bLastF2 = false, bLastF3 = false, bLastF4 = false, bLastF5 = false,
				bLastF6 = false, bLastF7 = false, bLastF8 = false, bLastF9 = false, bLastF10 = false,
				bLastEscape = false;
#define ON_KEY_PRESS_RELEASE(key, pressed_action, released_action){  \
			bool pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::key);			\
			if(pressed){											\
				if(!bLast##key) pressed_action;}/*Just pressed? */\
			else if(bLast##key) released_action;/*Just released?*/\
			bLast##key = pressed; } //remember the state


#pragma endregion
	
	//W Controllers
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_pCamera.MoveForward(0.05f);
	}

	//S Controllers
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_pCamera.MoveForward(-0.05f);
	}

	//A Controllers
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_pCamera.MoveSideways(0.05f);
	}

	//D Controllers
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_pCamera.MoveSideways(-0.05f);
	}

	//Q Controllers
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		m_pCamera.MoveVertical(-0.05f);
	}
	
	//E Controllers
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		m_pCamera.MoveVertical(0.05f);
	}

	//Z Controllers
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		{
			m_pCamera.ChangeRoll(-0.5f);
		}
		else {
			m_pCamera.ChangeRoll(0.5f);
		}
	}

	//X Controllers
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		{
			m_pCamera.ChangePitch(-0.5f);
		}
		else {
			m_pCamera.ChangePitch(0.5f);
		}
	}

	//Y Controllers
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		{
			m_pCamera.ChangeYaw(-0.5f);
		}
		else {
			m_pCamera.ChangeYaw(0.5f);
		}
	}

	//Exit the program
#pragma region Other Actions
	ON_KEY_PRESS_RELEASE(Escape, NULL, PostMessage(m_pWindow->GetHandler(), WM_QUIT, NULL, NULL))
#pragma endregion
}

void AppClass::ProcessMouse(void)
{
	//Flag for the modifier
	int xpos, ypos;

	
	//
}